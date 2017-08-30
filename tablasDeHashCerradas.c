/********************************************************************
 *                                                                  *
 *  Este programa implementa una tabla de Hash cerrada manejando    *
 *  como mecanismo para colisiones el doble hashing                 *
 ********************************************************************/

#include <stdio.h>  // Librer�a para la entrada y salida de datos
#include <stdlib.h> // Librer�a de funciones est�ndar

#undef CORRER_UNIX
#undef MODO_DEBUG
//#define CORRER_UNIX
//#define MODO_DEBUG

#define NO_SELECT -1 // Indica la opci�n de no selecci�n
#define FALSE 0		 // Definicion del FALSE (C no maneja booleanos)
#define TRUE 1		 // Definicion del TRUE (C no maneja booleanos)

#define MAX_LINE_MENU 6		// N�mero de l�neas a imprimir
#define MAX_LINE_PRINTER 50 // N�m. caracteres en por l�nea

#define NUMERO_DE_OPCIONES 4 // N�mero de opciones del men�

#define TAM_TABLA 11 // Tama�o de la tabla de hash

/* La constante a continuaci�n es la que se imprimir� en
   la funci�n "menu" del programa 
*/
const char Texto_Menu[MAX_LINE_MENU][MAX_LINE_PRINTER] =
	{
		"MENU - TABLAS DE HASH CERRADAS -:",
		" 1 - Introducir un elemento en la tabla",
		" 2 - Eliminar un elemento de la tabla",
		" 3 - Buscar un elemento en la tabla",
		" 4 - SALIR",
		"Por favor, introduzca su eleccion (1,2,3 o 4)-> "};

/* Aqu� se declara la estructura 'caja' que ser� la
   base para definir la tabla
*/
struct caja
{
	int elem;
	int esCasillaVacia;
};

/* Aqu� se define la estructura registro que es del tipo 
   'caja' declarado arriba
*/
typedef struct caja registro;

/* Aqu� se colocan las definiciones de prototipos de cada una de
   las funciones de nuestro programa
*/
int fhash(int clave);
int frehash(int clave, int hashLineal);
int esTablaLlena(registro tabla[]);
int esTablaVacia(registro tabla[]);
void mostrarTabla(registro tabla[]);
void crearTabla(registro tabla[]);
void insertarEnTabla(int clave, registro tabla[]);
void eliminarDeTabla(int clave, registro tabla[]);
int buscarEnTabla(int clave, registro tabla[]);
void destruirTabla(registro tabla[]);
int menu();

void clrscr();
void pausa();

/* Declaraci�n global de un entero llamado k :
   Contendr� la variable que se incrementar� a
   medida que se llame a la funci�n de rehash
*/
int k = 0;

/**
 * Funci�n fhash(int clave) : Devuelve el resultado de evaluar
 * la clave recibida como par�metro
 */
int fhash(int clave)
{
	return ((clave + 5) % TAM_TABLA);
}

/**
 * Funci�n frehash(int clave, int hashLineal) : Devuelve el resultado de evaluar
 * la clave recibida como par�metro. Si el hash es no lineal (hashLineal == FALSE)
 * se aplica rehash, de lo contrario (hashLineal == TRUE) se devuelve 1 (ello
 * implica que se usar� exploraci�n lineal)
 */
int frehash(int clave, int hashLineal)
{
	if (hashLineal)
		return 1;

	return ((clave % 5) + 3);
}

/**
 * Funci�n esTablaLlena(registro tabla[]) : Devuelve TRUE si la
 * tabla est� completamente llena. Si en la tabla existe al menos 
 * una casilla vac�a se devuelve FALSE
 */
int esTablaLlena(registro tabla[])
{
	int i;

	for (i = 0; i < TAM_TABLA; i++)
	{
		if (tabla[i].esCasillaVacia)
			return FALSE;
	}

	return TRUE;
}

/**
 * Funci�n esTablaVacia(registro tabla[]) : Devuelve TRUE si la
 * tabla est� vac�a. Si en la tabla existe al menos un elemento
 * se devuelve FALSE
 */
int esTablaVacia(registro tabla[])
{
	int i;

	for (i = 0; i < TAM_TABLA; i++)
	{
		if (!tabla[i].esCasillaVacia)
			return FALSE;
	}

	return TRUE;
}

/**
 * Funci�n mostrarTabla(registro tabla[]) : Imprime el 
 * contenido de cada uno de los registros que componen la tabla 
 * de hash.
 */
void mostrarTabla(registro tabla[])
{
	int i;

	clrscr();

	for (i = 0; i < TAM_TABLA; i++)
	{
		if (tabla[i].esCasillaVacia)
			printf("Posicion: %d	Valor: NULO\n", i);
		else
			printf("Posicion: %d	Valor: %d\n", i, tabla[i].elem);
	}

	pausa();

	return;
}

/**
 * Funci�n crearTabla(registro tabla[]) : Esta funci�n 
 * permite crear la tabla de hash, indicando que cada una de las 
 * casillas de la misma est� vac�a y disponible.
 */
void crearTabla(registro tabla[])
{
	int i;

	for (i = 0; i < TAM_TABLA; i++)
	{
		tabla[i].elem = 0;
		tabla[i].esCasillaVacia = TRUE;
	}

	return;
}

/**
 * Funci�n insertarEnTabla(int clave,registro tabla[]) : Permite 
 * insertar cada uno de los elementos que formar�n la tabla.
 *
 * Criterios para insertar:
 * 1- Si la posici�n devuelta por la tabla de hash est� disponible
 *    (vac�a) se procede a insertar el elemento en esa posici�n y
 *    se indica que dicha posici�n ahora se encuentra ocupada.
 * 2- Si la posici�n est� ocupada se cae en el ciclo while para
 *    tratar de encontrar otra posici�n vac�a (rehaahing). Si se genera
 *    un ciclo, entonces se pasa a exploraci�n lineal. Si a�n as� se encuentra
 *    un ciclo, no se puede insertar elementos en la tabla (tabla llena).
 */
void insertarEnTabla(int clave, registro tabla[])
{
	int posicion, posicionOriginal, ciclar, hashLineal;

	k = 0;

	posicionOriginal = posicion = fhash(clave);
	ciclar = TRUE;

	hashLineal = FALSE;

	/* Si tabla[posicion].esCasillaVacia != FALSE entonces esa casilla
	   ya est� ocupada por lo que se procede a ciclar hasta
	   encontrar alguna disponible
	*/
	while (ciclar && !tabla[posicion].esCasillaVacia)
	{
		k++;
		posicion = (fhash(clave) + (k * frehash(clave, hashLineal))) % TAM_TABLA;

#ifdef MODO_DEBUG
		printf("Posicion = (fhash(%d) + (%d*frehash(%d, %d))) MOD %d\n", clave, k, clave, hashLineal, TAM_TABLA);
		printf("Posicion = %d\n", posicion);
		pausa();
#endif

		/* Se gener� un ciclo, es decir, se exploraron todas las casillas con rehash o con exploraci�n lineal
		*/
		if (posicion == posicionOriginal)
		{
			/* Si se gener� un ciclo con exploraci�n lineal, sencillamente se deja de ciclar (la tabla est� llena).
			   De lo contrario, quiere decir que se produjo el ciclo con el rehash, por lo que se cambia a
			   exploraci�n lineal
			*/
			if (hashLineal == TRUE)
				ciclar = FALSE;
			else
			{
				/* Se cambia a exploraci�n lineal y se comienza desde la posici�n original
				*/
				hashLineal = TRUE;
				k = 0;

#ifdef MODO_DEBUG
				printf("ATENCION: SE APLICARA HASH LINEAL\n");
				pausa();
#endif
			}
		}
	}

	/* Si la salida del ciclo se produce porque 
	   tabla[posicion].esCasillaVacia == 0 es porque esa casilla
	   est� libre por lo que se procede a insertar la clave all�
	*/
	if (tabla[posicion].esCasillaVacia)
	{
		tabla[posicion].elem = clave;
		tabla[posicion].esCasillaVacia = FALSE;
	}
	else
	{
		printf("Imposible insertar la clave %d en la tabla de Hash\n", clave);
		pausa();
	}

	return;
}

/**
 * Funci�n eliminarDeTabla(int clave, registro tabla[]) : Permite 
 * eliminar una clave de la tabla. Para ello basta con colocar como 
 * vac�a dicha casilla (haciendo que tabla[posicion].esCasillaVacia sea
 * igual a TRUE)
 */
void eliminarDeTabla(int clave, registro tabla[])
{
	int posicion, posicionOriginal, ciclar, hashLineal;

	k = 0;

	posicionOriginal = posicion = fhash(clave);
	ciclar = TRUE;

	hashLineal = FALSE;

#ifdef MODO_DEBUG
	if (ciclar)
		printf("ciclar = TRUE\n");
	else
		printf("ciclar = FALSE");
	printf("clave = %d ; posicion = %d ; tabla[posicion].elem = %d\n", clave, posicion, tabla[posicion].elem);

	if (tabla[posicion].esCasillaVacia)
		printf("tabla[posicion].esCasillaVacia = TRUE\n");
	else
		printf("tabla[posicion].esCasillaVacia = FALSE\n");
#endif

	/* La condicion del || se coloca para evitar borrar por error una
	   casilla que seg�n la bandera est� disponible (vac�a)
	*/
	while (ciclar && (tabla[posicion].elem != clave || tabla[posicion].esCasillaVacia))
	{
		k++;
		posicion = (fhash(clave) + (k * frehash(clave, hashLineal))) % TAM_TABLA;

#ifdef MODO_DEBUG
		printf("Posicion = (fhash(%d) + (%d*frehash(%d, %d))) MOD %d\n", clave, k, clave, hashLineal, TAM_TABLA);
		printf("Posicion = %d\n", posicion);
		pausa();
#endif

		/* Se gener� un ciclo, es decir, se exploraron todas las casillas con rehash o con exploraci�n lineal
		*/
		if (posicion == posicionOriginal)
		{
			/* Si se gener� un ciclo con exploraci�n lineal, sencillamente se deja de ciclar (la tabla est� llena).
			   De lo contrario, quiere decir que se produjo el ciclo con el rehash, por lo que se cambia a
			   exploraci�n lineal
			*/
			if (hashLineal == TRUE)
				ciclar = FALSE;
			else
			{
				hashLineal = TRUE;
				k = 0;

#ifdef MODO_DEBUG
				printf("ATENCION: SE APLICARA HASH LINEAL\n");
				pausa();
#endif
			}
		}
	}

	/* Si la salida del ciclo se produce porque 
	   tabla[posicion].elem == clave es porque se encontr� una
	   casilla con la clave buscada y dicha casilla est� ocupada
	   (no vac�a)
	*/
	if (tabla[posicion].elem == clave)
		tabla[posicion].esCasillaVacia = TRUE;

	return;
}

/**
 * Funci�n buscarEnTabla(int clave,registro tabla[]) : Permite 
 * buscar un elemento dentro de la tabla
 */
int buscarEnTabla(int clave, registro tabla[])
{
	int posicion, posicionOriginal, ciclar, hashLineal;

	k = 0;

	posicionOriginal = posicion = fhash(clave);
	ciclar = TRUE;

	hashLineal = FALSE;

#ifdef MODO_DEBUG
	if (ciclar)
		printf("ciclar = TRUE\n");
	else
		printf("ciclar = FALSE");
	printf("clave = %d ; posicion = %d ; tabla[posicion].elem = %d\n", clave, posicion, tabla[posicion].elem);

	if (tabla[posicion].esCasillaVacia)
		printf("tabla[posicion].esCasillaVacia = TRUE\n");
	else
		printf("tabla[posicion].esCasillaVacia = FALSE\n");
#endif

	/* La condicion del || se coloca para evitar localizar por error 
	   una casilla que seg�n la bandera est� disponible (vac�a)
	*/
	while (ciclar && (tabla[posicion].elem != clave || tabla[posicion].esCasillaVacia))
	{
		k++;
		posicion = (fhash(clave) + (k * frehash(clave, hashLineal))) % TAM_TABLA;

#ifdef MODO_DEBUG
		if (ciclar)
			printf("ciclar = TRUE\n");
		else
			printf("ciclar = FALSE");
		printf("clave = %d ; posicion = %d ; tabla[posicion].elem = %d\n", clave, posicion, tabla[posicion].elem);

		if (tabla[posicion].esCasillaVacia)
			printf("tabla[posicion].esCasillaVacia = TRUE\n");
		else
			printf("tabla[posicion].esCasillaVacia = FALSE\n");
#endif

#ifdef MODO_DEBUG
		printf("Posicion = (fhash(%d) + (%d*frehash(%d, %d))) MOD %d\n", clave, k, clave, hashLineal, TAM_TABLA);
		printf("Posicion = %d\n", posicion);
		pausa();
#endif

		/* Se gener� un ciclo, es decir, se exploraron todas las casillas con rehash o con exploraci�n lineal
		*/
		if (posicion == posicionOriginal)
		{
			/* Si se gener� un ciclo con exploraci�n lineal, sencillamente se deja de ciclar (la tabla est� llena).
			   De lo contrario, quiere decir que se produjo el ciclo con el rehash, por lo que se cambia a
			   exploraci�n lineal
			*/
			if (hashLineal == TRUE)
				ciclar = FALSE;
			else
			{
				hashLineal = TRUE;
				k = 0;

#ifdef MODO_DEBUG
				printf("ATENCION: SE APLICARA HASH LINEAL\n");
				pausa();
#endif
			}
		}
	}

	/* Si la salida del ciclo se produce porque 
	   tabla[posicion].elem == clave y tabla[posicion].esCasillaVacia == FALSE
	   es porque se encontr� una casilla con la clave buscada y dicha casilla 
	   est� ocupada (no vac�a)
	*/
	if (tabla[posicion].elem == clave)
		return posicion;

	return NO_SELECT;
}

/**
 * Funci�n destruirTabla(registro tabla[]) : Esta funci�n 
 * permite destruir el contenido de la tabla de hash, haciendo que
 * cada casilla est� disponible (tabla[i].esCasillaVacia = TRUE).
 */
void destruirTabla(registro tabla[])
{
	int i;

	for (i = 0; i < TAM_TABLA; i++)
		tabla[i].esCasillaVacia = TRUE;

	return;
}

/**
 * Funci�n menu() : Permite generar el menu del sistema
 */
int menu()
{
	int eleccion, i;

	do
	{
		clrscr();

		for (i = 0; i < MAX_LINE_MENU; i++)
		{
			printf("%s", Texto_Menu[i]);
			if (i != MAX_LINE_MENU - 1)
				printf("\n");
		}
		scanf("%d", &eleccion);
		fflush(stdin);
	} while (eleccion < 1 || eleccion > NUMERO_DE_OPCIONES);

	return (eleccion);
}

/**
 * Funci�n clrscr(): Esta funci�n borra la pantalla dependiendo
 * del sistema operativo donde se est� corriendo el programa (gracias
 * a la MACRO)
 */
void clrscr()
{
#ifdef CORRER_UNIX
	system("clear");
#else
	system("cls");
#endif
}

/**
 * Funci�n pausa(): Esta funci�n genera una pausa dependiendo
 * del sistema operativo donde se est� corriendo el programa (gracias
 * a la MACRO)
 */
void pausa()
{
#ifdef CORRER_UNIX
	system("read -p 'Presione alguna tecla para continuar'");
#else
	system("PAUSE");
#endif
}

/**
 * Funci�n main() : Es la funci�n principal del programa. Ser�
 * la funci�n main() la que haga las diferentes llamadas a las
 * otras funciones
 */
int main()
{
	registro tabla[TAM_TABLA];
	int eleccion, elemento, posicion;

	/* Se crea la tabla
	*/
	crearTabla(tabla);

	do
	{
		clrscr();

		eleccion = menu();

		switch (eleccion)
		{

		case 1:
			if (!esTablaLlena(tabla))
			{
				printf("Por favor, introduzca el elemento a insertar -> ");
				scanf("%d", &elemento);
				fflush(stdin);
				insertarEnTabla(elemento, tabla);
			}
			else
			{
				clrscr();
				printf("La tabla esta llena. Por favor elimine elementos\n");
				pausa();
			}
			mostrarTabla(tabla);
			break;

		case 2:
			if (!esTablaVacia(tabla))
			{
				printf("Por favor, introduzca el elemento a eliminar -> ");
				scanf("%d", &elemento);
				fflush(stdin);
				eliminarDeTabla(elemento, tabla);
			}
			else
			{
				printf("La tabla esta vacia. Por favor introduzca elementos antes de eliminar\n");
				pausa();
			}
			mostrarTabla(tabla);
			break;

		case 3:
			if (!esTablaVacia(tabla))
			{
				printf("Por Favor, introduzca el elemento a buscar-> ");
				scanf("%d", &elemento);
				fflush(stdin);
				posicion = buscarEnTabla(elemento, tabla);

				clrscr();

				if (posicion != NO_SELECT)
					printf("El elemento %d se encuentra en la tabla en la posicion #%d\n", elemento, posicion);
				else
					printf("El elemento %d no se encuentra en la tabla\n", elemento);

				pausa();
			}
			else
			{
				printf("La tabla esta vacia. Por favor introduzca elementos antes de buscar\n");
				pausa();
			}

			mostrarTabla(tabla);
			break;

		default: /*finalizar las operaciones*/
			printf("FIN de las operaciones\n");
			printf("QUE TENGA UN BUEN DIA\n");
			pausa();
			destruirTabla(tabla);
		}
	} while (eleccion != NUMERO_DE_OPCIONES);

	return EXIT_SUCCESS;
}
