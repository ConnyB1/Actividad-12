#include <stdio.h>
#include "Funciones.h"

#define MAX_REGISTROS 1500
typedef struct _Talum {
    int status;
    int matricula;
    char ApPat[30];
    char ApMat[30];
    char Nombre[60];  // Nombre completo, se pueden unir ambos nombres
    int edad;  // Edad es un entero
    char sexo[7];
} reg;

int n = 0;  
reg registros[MAX_REGISTROS]; 

void Creaarchivo();
void generarArchivo(reg registros[], int n);
void eliminarRegistro(reg curp[], int *n, int matricula);
void buscarPorMatricula(reg curp[], int n, int matricula);
void ordenarPorMatricula(reg curp[], int n);
char *nombres(char genero);
void agregarAutomatico(reg registros[], int *n);
void impr_reg(reg alum[], int n);
char *apellidos();
int estaOrdenadoPorMatricula(reg curp[], int n);
void ordenarPorMatriculaSeleccion(reg curp[], int n);
void ordenarPorMatriculaBurbuja(reg curp[], int n);
void llenarreg();
void createtxtfile();
void borrarContenidoArchivo(const char *nombreArchivo);
void mostrarBorrados(reg registros[], int n);

int main()
{
    srand(time(NULL));
    int op, archivoCargado = 0, matricula;
    

    do
    {
        printf("\n\tmenu\n");
        printf("1.- Cargar Archivo\n");
        printf("2.- Agregar \n");
        printf("3.- Eliminar\n");
        printf("4.- Buscar\n");
        printf("5.- Ordenar \n");
        printf("6.- Mostrar Todo \n");
        printf("7.- Generar Archivo\n");
        printf("8.- Cantidad de registrps en Archivo \n");
        printf("9.- Mostrar Borrados\n");
        printf("\n0.- Salir\n");
        op= valinum(0, 9);


        if(op == 1)
        {
            if(archivoCargado) 
            {
                printf("El archivo ya se ha cargado previamente.\n");
            } 
            else 
            {
                llenarreg();
                archivoCargado = 1;
            }
        }
        else
        {
            if(op == 2)
            {
                agregarAutomatico(registros, &n);
            }
            else
            {
                if (op == 3)
                {
                    printf("\ningresa la matricula que deseas borrar: ");
                    matricula = valinum(300000, 399999);
                    eliminarRegistro(registros, &n, matricula);
                    printf("\n\n");
                    system("pause");
                    system("cls");
                    
                }
                else
                {
                    if (op == 4)
                    {
                        printf("Ingrese la matricula que desea buscar: ");
                        matricula = valinum(300000, 399999);
                        buscarPorMatricula(registros, n, matricula);
                        printf("\n\n");
                        system("pause");
                        system("cls");
                    }
                    else
                    {
                        if (op == 5)
                        {
                            ordenarPorMatricula(registros, n);
                            
                        }
                        else
                        {
                            if (op == 6)
                            {
                                impr_reg(registros, n);
                            }
                            else
                            {
                                if (op == 7)
                                {
                                    generarArchivo(registros, n);
                                }
                                else
                                {
                                    if (op == 8)
                                    {
                                        Creaarchivo();
                                    }
                                    else
                                    {
                                        if (op == 9)
                                        {
                                            mostrarBorrados(registros, n);
                                        }
                                        
                                    }
                                    
                                }
                                
                            }
                            
                        }
                        
                    }
                    
                }
            }
        }
    } while (op != 0);

    const char *nombreDelArchivo = "registros eliminados.txt";
    borrarContenidoArchivo(nombreDelArchivo);
    createtxtfile();
    

    return 0;
}

void createtxtfile(void) 
{
    FILE *archivo;
    archivo = fopen("C:\\Users\\costco\\Documents\\Programacion estructurada\\Actividad 12\\registros eliminados.txt", "w");

    if (archivo != NULL) 
    {
        fprintf(archivo, "%-12s %-15s %-15s %-15s %-15s %-10s\n", "N° Registro", "Matrícula", "Nombre", "Ap. Paterno", "Ap. Materno", "Sexo");
        for (int i = 0; i < n; i++) 
        {
            if (registros[i].status == 0) 
            {
                fprintf(archivo, "%-12d %-15d %-15s %-15s %-15s %-15s\n", i + 1, registros[i].matricula, registros[i].Nombre, registros[i].ApPat, registros[i].ApMat, registros[i].sexo);
            }
        }
        fclose(archivo);
    } 
    else 
    {
        printf("No se pudo abrir el archivo para escritura.\n");
    }
}



void llenarreg() 
{
    FILE *file = fopen("C:\\Users\\costco\\Documents\\Programacion estructurada\\Actividad 12\\datos.txt", "r");
    if (file == NULL) 
    {
        printf("No se pudo abrir el archivo 'datos.txt' para lectura.\n");
        return;
    }

    int indice = n;
    while (fscanf(file, "%*d.- %d %29s %29s %59s %d %9s", &registros[indice].matricula, registros[indice].ApPat, registros[indice].ApMat, registros[indice].Nombre, &registros[indice].edad, registros[indice].sexo) == 6) 
    {
        registros[indice].status = 1;
        indice++;
        if (indice >= MAX_REGISTROS) 
        {
            printf("Se ha alcanzado el máximo de registros permitidos.\n");
            break;
        }
    }
    n = indice;  
    fclose(file);
}

void impr_reg(reg registros[], int n) 
{
    int registrosPorPagina = 40;
    int paginas = (n + registrosPorPagina - 1) / registrosPorPagina; 

    for (int pagina = 0; pagina < paginas; pagina++) 
    {
        int inicio = pagina * registrosPorPagina;
        int fin = (pagina + 1) * registrosPorPagina;
        if (fin > n) {
            fin = n;
        }
        printf("Listado de registros:\n\n");
        printf("%-12s %-15s %-15s %-15s %-15s %-15s %-15s\n", "N", "Matrícula", "Nombre", "Ap. Paterno", "Ap. Materno", "Edad", "Sexo");
        for (int i = inicio; i < fin; i++) 
        {
        if (registros[i].status == 1) 
        {
            printf("%-12d %-15d %-15s %-15s %-15s %-15d %-15s \n", i + 1, registros[i].matricula, registros[i].Nombre, registros[i].ApPat, registros[i].ApMat, registros[i].edad, registros[i].sexo);
        }
    }

        if (pagina < paginas - 1) 
        {
            printf("Presiona Enter para continuar...");
            while (getch() != 13) {} 
            system("cls");
        }
    }
}



void ordenarPorMatricula(reg registros[], int n)
{
    if (estaOrdenadoPorMatricula(registros, n))
    {
        printf("El arreglo ya está ordenado por matrícula. No es necesario ordenarlo de nuevo.\n");
    }
    else
    {
        int tamanio = n;

        if (tamanio <= 100)
        {
            ordenarPorMatriculaSeleccion(registros, tamanio);
            printf("El arreglo ha sido ordenado por matrícula utilizando el algoritmo de selección.\n");
        }
        else
        {
            ordenarPorMatriculaBurbuja(registros, tamanio);
            printf("El arreglo ha sido ordenado por matrícula utilizando el algoritmo de burbuja.\n");
        }
    }
}
int estaOrdenadoPorMatricula(reg registros[], int n)
{
    for (int i = 1; i < n; i++)
    {
        if (registros[i].matricula < registros[i - 1].matricula)
        {
            return 0; 
        }
    }
    return 1;
}

void ordenarPorMatriculaSeleccion(reg registros[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (registros[j].status == 1 && (registros[j].matricula < registros[minIndex].matricula))
            {
                minIndex = j;
            }
        }
        if (minIndex != i)
        {
            reg temp = registros[i];
            registros[i] = registros[minIndex];
            registros[minIndex] = temp;
        }
    }
}

void ordenarPorMatriculaBurbuja(reg registros[], int n)
{
    int intercambio;
    for (int i = 0; i < n - 1; i++)
    {
        intercambio = 0;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (registros[j].status == 1 && (registros[j].matricula > registros[j + 1].matricula))
            {
                reg temp = registros[j];
                registros[j] = registros[j + 1];
                registros[j + 1] = temp;
                intercambio = 1;
            }
        }
        if (intercambio == 0)
        {
            break; 
        }
    }
}

void borrarContenidoArchivo(const char *nombreArchivo) 
{
    FILE *archivo;
    archivo = fopen(nombreArchivo, "w");

    fprintf(archivo, " "); 

    fclose(archivo);
}

void buscarPorMatricula(reg registros[], int n, int matricula) 
{
    int encontrado = 0;

    if (n <= 100) 
    {
        ordenarPorMatriculaSeleccion(registros, n);
        printf("\nUtilizando el metodo de búsqueda por seleccion.\n\n");
    } 
    else 
    {
        ordenarPorMatriculaBurbuja(registros, n);
        printf("\nUtilizando el metodo de búsqueda por burbuja.\n\n");
    }

    int izquierda = 0;
    int derecha = n - 1;

    while (izquierda <= derecha) 
    {
        int medio = izquierda + (derecha - izquierda) / 2;

        if (registros[medio].matricula == matricula && registros[medio].status == 1) 
        {
            printf("Registro encontrado:\n");
            printf("%-12s %-15s %-15s %-15s %-15s %-15s %-15s\n", "N", "Matrícula", "Nombre", "Ap. Paterno", "Ap. Materno", "Edad", "Sexo");
            printf("%-12d %-15d %-15s %-15s %-15s %-15d %-15s \n", medio + 1, registros[medio].matricula, registros[medio].Nombre, registros[medio].ApPat, registros[medio].ApMat, registros[medio].edad, registros[medio].sexo);
            encontrado = 1;  
            break;
        } 
        else 
        {
            if (registros[medio].matricula < matricula) 
            {
                izquierda = medio + 1;
            } 
            else 
            {
                derecha = medio - 1;
            } 
        }
    }

    if (!encontrado) 
    {
        printf("No se encontró un registro con la matrícula %d.\n", matricula);
    }
}


void agregarAutomatico(reg registros[], int *n) 
{
    if (*n + 100 > MAX_REGISTROS) 
    {
        printf("No se pueden agregar 100 registros automáticamente, ya que superaría el límite de registros.\n");
        return;
    }

    int indice = *n;
    for (int i = 0; i < 100; i++) 
    {
        if (indice >= MAX_REGISTROS) 
        {
            printf("Se ha alcanzado el máximo de registros permitidos.\n");
            break;
        }
        registros[indice].status = 1;
        registros[indice].matricula = valinumran(300000, 399999);
        char gen = (rand() % 2 == 0) ? 'M' : 'F';
        if (gen == 'F')
        {
            strcpy(registros[indice].sexo, "MUJER");
        }
        if (gen == 'M')
        {
            strcpy(registros[indice].sexo, "HOMBRE");
        }
        char *nombreGenerado = nombres(gen);
        strcpy(registros[indice].Nombre, nombreGenerado);
        strcpy(registros[indice].ApPat, apellidos());
        strcpy(registros[indice].ApMat, apellidos());
        registros[indice].edad = valinumran(0, 100);
        indice++;
    }
    *n = indice; 
}


char *nombres(char genero)
{
    char nombresMas[][30] = {
        "Juan", "Carlos", "Luis", "Segismundo", "Diego",
        "Andres", "Soponcio", "Jose", "Felipe", "Rafael",
        "Obama", "Adolfo", "Fernando", "Cipriano", "Francisco",
        "David", "Emilio", "Miguel", "Alberto", "Roberto"
    };

    char nombresFem[][30] = {
        "Maria", "Ana", "Sofia", "Laura", "Isabel",
        "Digna", "Clara", "Adriana", "Valeria", "Daniela",
        "Carolina", "Paola", "Camila", "Natalia", "Andrea",
        "Lucia", "Verónica", "Ana", "Beatriz", "Marciana"
    };

    char *nombreElegido = (char *)malloc(31);
    if (genero == 'M')
    {
        int nom = rand() % 20;
        strcpy(nombreElegido, nombresMas[nom]);
    }
    else
    {
        int nom = rand() % 20;
        strcpy(nombreElegido, nombresFem[nom]);
    }

    return nombreElegido;

}

char *apellidos()
{
    char listaApellidos[][30] = {
        "Garcia", "Martinez", "Lopez", "Rodriguez", "Perez",
        "Fernandez", "Gonzalez", "Sánchez", "Ramirez", "Torres",
        "Jimenez", "Díaz", "Vargas", "Romero", "Suarez",
        "Mendoza", "Ortega", "Hernández", "Silva", "Rojas",
        "Cruz", "Morales", "Núñez", "Guerrero", "Paredes",
        "Salazar", "Estrvez", "Figueroa", "Valencia", "Molina"
    };

    char *apellidoElegido = (char *)malloc(31); 
    int indice = rand() % 30;
    strcpy(apellidoElegido, listaApellidos[indice]);

    return apellidoElegido;
}

void eliminarRegistro(reg registros[], int *n, int matricula)
{
    int encontrado = 0;

    for (int i = 0; i < *n; i++)
    {
        if (registros[i].matricula == matricula && registros[i].status == 1)
        {
            printf("Registro encontrado:\n");
            printf("Matrícula: \t%d\n", registros[i].matricula);
            printf("Nombre 1: \t%s\n", registros[i].Nombre);
            printf("Apellido Paterno: \t%s\n", registros[i].ApPat);
            printf("Apellido Materno: \t%s\n", registros[i].ApMat);
            printf("Sexo: \t%s\n", registros[i].sexo);
            printf("¿Desea eliminar este registro (s/n)? ");
            int salir = 0;
            do
            {
                char respuesta = getch();
                respuesta = tolower(respuesta);
                if (isalpha(respuesta))
                {
                    if (respuesta == 's')
                    {
                        printf("%c", respuesta);
                    }
                    else
                    {
                        if (respuesta == 'n')
                        {
                            printf("%c", respuesta);
                        }   
                    }
                }
                if (respuesta == 's')
                {
                    registros[i].status = 0; 
                    printf("\n\nRegistro con matrícula %d eliminado de forma lógica.\n", matricula);
                    salir = 1;
                }
                else
                {
                    if (respuesta == 'n')
                    {
                        salir = 1;
                    }
                    
                }
            } while (salir != 1);
            
            
            encontrado = 1;
        }
    }
    if (!encontrado)
    {
        printf("No se encontró un registro activo con la matrícula %d.\n", matricula);
    }
}

void generarArchivo(reg registros[], int n) 
{
    
    char nombreArchivo[50];
    printf("Ingresa el nombre del archivo (sin la extensión .txt): ");
    leercadena( nombreArchivo, sizeof(nombreArchivo));

    borrarContenidoArchivo(nombreArchivo);

    FILE *archivo;
    char nombreCompleto[100]; 
    sprintf(nombreCompleto, "C:\\Users\\costco\\Documents\\Programacion estructurada\\Actividad 12\\%s.txt", nombreArchivo);


    archivo = fopen(nombreCompleto, "w");

    if (archivo != NULL) 
    {
        fprintf(archivo, "%-12s %-15s %-15s %-15s %-15s %-15s %-15s\n", "N", "Matrícula", "Nombre", "Ap. Paterno", "Ap. Materno", "Edad", "Sexo");
        for (int i = 0; i < n; i++) 
        {
            if (registros[i].status == 1) 
            {
                fprintf(archivo, "%-12d %-15d %-15s %-15s %-15s %-15d %-15s \n", i + 1, registros[i].matricula, registros[i].Nombre, registros[i].ApPat, registros[i].ApMat, registros[i].edad, registros[i].sexo);
            }
        }
        fclose(archivo);
        printf("\n\nArchivo '%s' generado con éxito.\n", nombreCompleto);
    } 
    else 
    {
        printf("No se pudo abrir el archivo para escritura.\n");
    }
}

void Creaarchivo() 
{
    char nombreArchivo[50];
    printf("Ingrese el nombre del archivo: ");
    leercadena( nombreArchivo, sizeof(nombreArchivo));

    int cantidadRegistros = contarRegistrosEnArchivo(nombreArchivo);

    if (cantidadRegistros >= 0) 
    {
        printf("El archivo '%s' contiene %d registros.\n", nombreArchivo, cantidadRegistros);
    } else 
    {
        printf("El archivo no se pudo abrir o está vacío.\n");
    }

}   

void mostrarBorrados(reg registros[], int n) 
{
    printf("Listado de registros eliminados:\n\n");
    printf("%-12s %-15s %-15s %-15s %-15s %-15s %-15s\n", "N", "Matrícula", "Nombre", "Ap. Paterno", "Ap. Materno", "Edad", "Sexo");
    int encontrado = 0;
    for (int i = 0; i < n; i++) 
    {
        if (registros[i].status == 0) 
        {
            encontrado = 1;
            printf("%-12d %-15d %-15s %-15s %-15s %-15d %-15s \n", i + 1, registros[i].matricula, registros[i].Nombre, registros[i].ApPat, registros[i].ApMat, registros[i].edad, registros[i].sexo);
        }
    }
    if (!encontrado) 
    {
        printf("No se encontraron registros eliminados.\n");
    }
}
