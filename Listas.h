#define TRUE  1
#define FALSE 0

struct lista_elementos
{
    int clave;
    struct lista_elementos *sig;
};

typedef struct lista_elementos _cajita;

//Prototipos de funciones para las listas

_cajita *crearLista (_cajita *registro);
_cajita *insertarEnLista (_cajita *registro, int numero);
_cajita *eliminarDeLista (_cajita *registro, int numero);
_cajita *destruirLista (_cajita *registro);
_cajita *finDeLista (_cajita *registro);
int buscarEnLista (_cajita *registro, int numero);
int esListaVacia (_cajita *registro);
void mostrarLista (_cajita *registro);

//Función crear lista
_cajita *crearLista (_cajita *registro)

{
	return registro= NULL;
}

//Función insertar en Lista
_cajita *insertarEnLista (_cajita *registro, int numero)

{
    _cajita *nuevoregistro;
    _cajita *aux;
    nuevoregistro=(_cajita *)malloc(sizeof(_cajita));
    nuevoregistro->clave= numero;
    nuevoregistro->sig= NULL;

    if (esListaVacia(registro)==TRUE)
        {
            registro=nuevoregistro;
        }   
    else
        {
            aux=finDeLista(registro);
            aux->sig = nuevoregistro;
        }
            
return registro;
}

//Función lista vacia
int esListaVacia (_cajita *registro)
{
    if (registro==NULL)
        return TRUE;
    else
        return FALSE;
}

//Función buscar en lista
int buscarEnLista (_cajita *registro, int numero)
{
_cajita *aux;
int posicion;
aux=registro;
posicion=1;

while (!esListaVacia(aux))
 {
    if (aux->clave==numero)
    {
        return posicion;
    }
    else
    {
        aux=aux->sig;
        posicion++;
    }
 }
return FALSE;
}

//Funcion Eliminar en lista
_cajita *eliminarDeLista (_cajita *registro, int numero)
{
	int cont;
    _cajita *aux;
    _cajita *nodoBorrar;
    aux=registro;
    
    //Si el elemento es el primero en la lista:
    if (registro->clave==numero)
    {
        registro=aux->sig;
        free (aux);
        return registro;
    }
    //En caso contrario se procede a buscar el elemento
    else
    {
		while (!esListaVacia(aux->sig))
			if (aux->sig->clave==numero)
			{
				nodoBorrar=aux->sig;
				aux->sig=nodoBorrar->sig;
				free (nodoBorrar);
				return registro;
			}
			else
				aux=aux->sig;
	}
	return NULL;
}

//Función Fin de Lista
_cajita *finDeLista (_cajita *registro)
{
    _cajita *aux;
    aux=registro;
    while (!esListaVacia(aux->sig))
    {
        aux=aux->sig;
    }
    return aux;
}

//Funcion Mostrar lista
void mostrarLista (_cajita *registro)
{
	_cajita *aux;
	aux=registro;
	system ("cls");
    while (!esListaVacia(aux))
    {
        printf("%d\n",aux->clave);
        aux=aux->sig;
    }
}

//Funcion Destruir Lista
_cajita *destruirLista (_cajita *registro)
{
    _cajita *aux;
    aux=registro;
    while (!esListaVacia(aux))
    {
        registro=aux->sig;
        free(aux);
        aux=registro;
    }
    return registro;
}

