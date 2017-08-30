#define TRUE 1
#define FALSE 0

struct Cola_elementos
{
    int clave;
    struct Cola_elementos *sig;
};
typedef struct Cola_elementos _cajita;

//Prototipos de funciones para las Colas

_cajita *crearCola(_cajita *registro);
_cajita *acolar(_cajita *registro, int numero);
_cajita *desencolar(_cajita *registro, int numero);
_cajita *destruirCola(_cajita *registro);
_cajita *finDeCola(_cajita *registro);
int buscarEnCola(_cajita *registro, int numero);
int esColaVacia(_cajita *registro);
void mostrarCola(_cajita *registro);

//Funci�n buscar en Cola
int buscarEnCola(_cajita *registro, int numero)
{
    _cajita *aux;
    int posicion;
    aux = registro;
    posicion = 1;

    while (!esColaVacia(aux))
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

//Funcion Mostrar Cola
void mostrarCola(_cajita *registro)
{
    _cajita *aux;
    aux = registro;
    system("cls");
    while (!esColaVacia(aux))
    {
        printf("%d\n", aux->clave);
        aux = aux->sig;
    }
}

//Funcion Destruir Cola
_cajita *destruirCola(_cajita *registro)
{
    _cajita *aux;
    aux = registro;
    while (!esColaVacia(aux))
    {
        registro = aux->sig;
        free(aux);
        aux = registro;
    }
    return registro;
}
