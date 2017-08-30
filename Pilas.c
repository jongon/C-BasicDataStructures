#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define TRUE 1
#define FALSE 0

struct Pila_elementos
{
    int clave;
    struct Pila_elementos *sig;
};

typedef struct Pila_elementos _cajita;

//Prototipos de funciones para las Pilas

_cajita *crearPila(_cajita *registro);
_cajita *apilar(_cajita *registro, int numero);
_cajita *desapilar(_cajita *registro, int numero);
_cajita *destruirPila(_cajita *registro);
_cajita *finDePila(_cajita *registro);
int buscarEnPila(_cajita *registro, int numero);
int esPilaVacia(_cajita *registro);
void mostrarPila(_cajita *registro);

//Funci�n crear Pila
_cajita *crearPila(_cajita *registro)

{
    return registro = NULL;
}

//Funci�n insertar en Pila
_cajita *apilar(_cajita *registro, int numero)

{
    _cajita *nuevoregistro;
    _cajita *aux;
    nuevoregistro = (_cajita *)malloc(sizeof(_cajita));
    nuevoregistro->clave = numero;
    nuevoregistro->sig = NULL;

    if (esPilaVacia(registro) == TRUE)
    {
        registro = nuevoregistro;
    }
    else
    {
        registro = aux;
        registro = nuevoregistro;
        nuevoregistro->sig = aux;
    }

    return registro;
}

//Funci�n Pila vacia
int esPilaVacia(_cajita *registro)
{
    if (registro == NULL)
        return TRUE;
    else
        return FALSE;
}

//Funci�n buscar en Pila
int buscarEnPila(_cajita *registro, int numero)
{
    _cajita *aux;
    int posicion;
    aux = registro;
    posicion = 1;

    while (!esPilaVacia(aux))
    {
        if (aux->clave == numero)
        {
            return posicion;
        }
        else
        {
            aux = aux->sig;
            posicion++;
        }
    }
    return FALSE;
}

//Funcion Eliminar en Pila
_cajita *desapilar(_cajita *registro)
{
    _cajita *aux;
    aux = registro;

    registro = aux->sig;
    free(aux);
    return registro;
}

//Funci�n Fin de Pila
_cajita *finDePila(_cajita *registro)
{
    _cajita *aux;
    aux = registro;
    while (!esPilaVacia(aux->sig))
    {
        aux = aux->sig;
    }
    return aux;
}

//Funcion Mostrar Pila
void mostrarPila(_cajita *registro)
{
    _cajita *aux;
    aux = registro;
    system("cls");
    while (!esPilaVacia(aux))
    {
        printf("%d\n", aux->clave);
        aux = aux->sig;
    }
}

//Funcion Destruir Pila
_cajita *destruirPila(_cajita *registro)
{
    _cajita *aux;
    aux = registro;
    while (!esPilaVacia(aux))
    {
        registro = aux->sig;
        free(aux);
        aux = registro;
    }
    return registro;
}

void main()

{

    int opcion, entero, boole;
    _cajita *inicioPila;
    _cajita *auxPila;
    boole = FALSE;
    do
    {
        do
        {
            system("cls");
            printf("Este programa implementa las funciones principales de Pilas, pilas o Pilas\n");
            printf("1) Crear Pila\n");
            printf("2) Insertar en Pila\n");
            printf("3) Mostrar Pila\n");
            printf("4) Eliminar de Pila\n");
            printf("5) Buscar en Pila\n");
            printf("6) Es Pila vacia\n");
            printf("7) Destruir Pila\n");
            printf("8) Fin de listta\n");
            printf("9) Salir\n");
            scanf("%d", &opcion);
            fflush(stdin);
        } while (opcion < 1 || opcion > 9);
        switch (opcion)
        {
        case 1: //Working
            if (boole == TRUE)
                inicioPila = destruirPila(inicioPila);

            inicioPila = (crearPila(inicioPila));
            printf("Pila creada\n");
            system("PAUSE");
            boole = TRUE;
            break;
        case 2: //Working
            do
            {
                system("cls");
                if (boole == TRUE)
                {
                    printf("introduzca el valor a insertar\n");
                    scanf("%d", &entero);
                    fflush(stdin);
                    inicioPila = apilar(inicioPila, entero);
                    printf("Desea insertar otro elemento a la Pila? (Presione S para aceptar, cualquier tecla para continuar\n");
                }
                else
                {
                    printf("La Pila no ha sido creada, por favor crear la Pila antes de insertar\n");
                    system("PAUSE");
                }
            } while (getch() == 's');
            break;
        case 3: //Working
            if (boole == TRUE)
            {
                if (esPilaVacia(inicioPila) == TRUE)
                {
                    printf("La Pila se encuentra vacia\n");
                    system("PAUSE");
                }
                else
                    mostrarPila(inicioPila);
                system("PAUSE");
            }
            else
            {
                printf("La Pila no ha sido creada, por favor crear la Pila antes de mostrar\n");
                system("PAUSE");
            }
            break;
        case 4: //Working
            if (boole == TRUE)
                do
                    if (!esPilaVacia(inicioPila))
                    {
                        system("cls");
                        inicioPila = desapilar(inicioPila);
                        printf("ha sido eliminado un elemento de la Pila\n");
                        printf("Desea eliminar otra clave de la Pila? (Pulse S para aceptar cualquier tecla para continuar)\n");
                    }
                    else
                    {
                        printf("la Pila est� vacia\n");
                        printf("Presione Enter para continuar\n");
                    }

                while (getch() == 's');
            else
                printf("La Pila no ha sido creada\n");
            break;

        case 5: //Working
            if (boole == TRUE)
                if (!esPilaVacia(inicioPila))
                    do
                    {
                        system("cls");
                        printf("Introduzca el elemento a ser buscando en la Pila\n");
                        scanf("%d", &entero);
                        fflush(stdin);
                        if (buscarEnPila(inicioPila, entero) > 0)
                            printf("El elemento se encontr� en la posici�n %d\n", buscarEnPila(inicioPila, entero));
                        else
                            printf("El elemento no se encontr�\n");

                        printf("Desea realizar la busqueda de otro elemento? (presione S para aceptar, cualquier tecla para continuar)\n");

                    } while (getch() == 's');
                else
                {
                    printf("La Pila se encuentra vacia\n");
                    system("PAUSE");
                }
            else
            {
                printf("La Pila no se ha creado\n");
                system("PAUSE");
            }
            break;
        case 6: //Working
            if (boole == TRUE)
                if (esPilaVacia(inicioPila) == TRUE)
                {
                    printf("La Pila se encuentra vacia\n");
                    system("PAUSE");
                }
                else
                {
                    printf("La Pila no se encuentra vacia\n");
                    system("PAUSE");
                }
            else
            {
                printf("No se ha creado una Pila\n");
                system("PAUSE");
            }
            break;
        case 7: //Working
            if (boole == TRUE)
                if (esPilaVacia(inicioPila) == FALSE)
                {
                    inicioPila = destruirPila(inicioPila);
                    printf("La Pila fue destruida satisfactoriamente\n");
                    boole = FALSE;
                    system("PAUSE");
                }
                else
                {
                    printf("La Pila se encuentra vacia no hay elementos para destruir\n");
                    system("PAUSE");
                }
            else
            {
                printf("No se ha creado la Pila\n");
                system("PAUSE");
            }
            break;
        case 8: //Working
            if (boole == TRUE)
            {
                if (!esPilaVacia(inicioPila))
                {
                    auxPila = NULL;
                    auxPila = finDePila(inicioPila);
                    printf("El final de la Pila es %d\n", auxPila->clave);
                    system("PAUSE");
                }
                else
                {
                    printf("La Pila se encuentra vacia\n");
                    system("PAUSE");
                }
            }
            else
            {
                printf("La Pila no ha sido creada\n");
                system("PAUSE");
            }
            break;
        default:
            printf("Ha finalizado el programa\n");
            system("PAUSE");
        }
    } while (opcion != 9);
}