#include "csv.h"
#include <stdio.h>
#include <string.h>

#define CARACTERES_POR_LINEA 2048
const int CARACTER_NULO = '\0';

struct archivo_csv {
	FILE *archivo;
	char separador;
};

/*Pre: "separador" debe ser un delimitador válido para archivos CSV.*/
/*Pos: Devuelve un puntero a una estructura de tipo archivo_csv inicializada con el separador recibido. En caso de error devuelve NULL.*/

struct archivo_csv *inicializar_estructura_csv(char separador)
{
	struct archivo_csv *archivo = malloc(sizeof(struct archivo_csv));
	if (!archivo)
		return NULL;
	archivo->separador = separador;
	archivo->archivo = NULL;
	return archivo;
}

/*Pre: "nombre_archivo" debe ser un string válido.*/
/*Pos: Devuelve un puntero a un archivo abierto en modo lectura. En caso de error devuelve NULL.*/

FILE *abrir_archivo(const char *nombre_archivo)
{
	FILE *archivo = fopen(nombre_archivo, "r");
	return archivo;
}

/*Pre: "archivo" debe ser un struct válido y apuntar a un archivo abierto, "funciones" debe ser un array válido de punteros que acepten correctamente sus
		respectivos parámetros y devuelvan un booleano.*/
/*Pos: Devuelve true si los argumentos son válidos, caso contrario devuelve false.*/

bool son_argumentos_validos(struct archivo_csv *archivo,
			    bool (*funciones[])(const char *, void *),
			    void *ctx[])
{
	return archivo && archivo->archivo && funciones && ctx;
}

/*Pre: "archivo" debe ser un struct válido y apuntar a un archivo abierto, "linea" debe ser un string válido y "long_linea" debe ser mayor a 0.*/
/*Pos: Devuelve true si la línea es válida, caso contrario devuelve false.*/

bool es_linea_valida(struct archivo_csv *archivo, char *linea, int long_linea)
{
	return fgets(linea, long_linea, archivo->archivo) != NULL;
}

/*Pre: "linea" debe ser un string (terminar en '\0')*/
/*Pos: Devuelve la posición del primer separador en el linea, si este es NULL se devuelve directamente la longitud de la línea leida.*/

size_t buscar_posicion_separador(const char *linea, char separador)
{
	size_t pos = 0;

	while (linea[pos] != '\0' && linea[pos] != separador) {
		pos++;
	}

	return pos;
}

/* Pre: "ptr" debe ser un puntero válido a un str, "posicion_separador" debe estar en el rango [0, long_linea), 
		"long_linea" debe ser mayor que "posicion_separador", "separador" debe ser un char válido, y "fin_columna" debe ser un puntero válido a un 
		puntero de char. */
/* Pos: Si "posicion_separador" < "long_linea" y "ptr[posicion_separador]" es igual a "separador", se escribe "CARACTER_NULO" en "*fin_columna" y 
		se incrementa "*fin_columna". De lo contrario, se escribe "CARACTER_NULO" en "*fin_columna" sin incrementar el puntero. */

void procesar_separador(char *ptr, size_t posicion_separador, size_t long_linea,
			char separador, char **fin_columna)
{
	if (posicion_separador < long_linea &&
	    ptr[posicion_separador] == separador) {
		*(*fin_columna) = CARACTER_NULO;
		(*fin_columna)++;
	} else {
		*(*fin_columna) = CARACTER_NULO;
	}
}

/* Pre: "funciones" debe ser un array de punteros a funciones que toman un const char * y un void * como argumentos. "columna_actual" debe ser un
		índice válido dentro de "funciones". */
/* Pos: Devuelve true si "funciones[columna_actual]" no es NULL; en caso contrario, devuelve false. */

bool es_funcion_valida(bool (*funciones[])(const char *, void *),
		       size_t columna_actual)
{
	return funciones[columna_actual] != NULL;
}

/* Pre: "funciones" debe ser un array de punteros a funciones que toman un const char * y un void * como argumentos. "ctx" debe ser un array de
		punteros void válidos. "columna_actual" debe ser un índice válido dentro de "funciones". "ptr" debe ser un puntero a un str válido. */
/* Pos: Devuelve el resultado de llamar a la función apuntada por "funciones[columna_actual]" con "ptr" y "ctx[columna_actual]" como argumentos. */

bool es_resultado_verdadero(bool (*funciones[])(const char *, void *),
			    void *ctx[], size_t columna_actual, const char *ptr)
{
	return funciones[columna_actual](ptr, ctx[columna_actual]);
}

/* Pre: "archivo" debe ser un puntero válido a un struct archivo_csv con un archivo abierto. "linea" debe ser válida y de tamaño "tam_linea".
		"tam_linea" debe ser mayor a 0. "long_linea" y "ptr" deben ser punteros válidos. */
/* Pos: Lee una línea del archivo y la almacena en "linea". Si la lectura fue exitosa, asigna la longitud de la línea a "*long_linea" y el puntero a
		"linea" a "*ptr", devolviendo true. Caso contrario, devuelve false. */

bool leer_linea(struct archivo_csv *archivo, char *linea, int tam_linea,
		size_t *long_linea, char **ptr)
{
	if (!fgets(linea, tam_linea, archivo->archivo)) {
		return false;
	}
	*long_linea = strlen(linea);
	*ptr = linea;
	return true;
}

/* Pre: "archivo" debe ser un puntero válido a un struct archivo_csv con un archivo abierto. "linea" debe ser válida y de tamaño "tam_linea". 
		tam_linea" debe ser mayor a 0. "long_linea" y "ptr" deben ser punteros válidos. "fin_columna" debe ser un puntero a un carácter válido.
		"columna_actual" debe ser un índice válido dentro del rango de columnas. "columnas" debe ser el número total de columnas. */
/* Pos: Si "*fin_columna" es igual a "CARACTER_NULO" y "columna_actual" es menor que "columnas", llama a "leer_linea" para leer una nueva línea en "linea",
		actualiza "*long_linea" y "*ptr", y pone "*fin_columna" a "CARACTER_NULO". Devuelve true si se cumple esta condición o si no se necesitaba leer una
		nueva línea. */

bool procesar_linea(struct archivo_csv *archivo, char *linea, int tam_linea,
		    size_t *long_linea, char **ptr, char *fin_columna,
		    size_t columna_actual, size_t columnas)
{
	if (*fin_columna == CARACTER_NULO && columna_actual < columnas) {
		if (!leer_linea(archivo, linea, tam_linea, long_linea, ptr)) {
			return false;
		}
		*fin_columna = CARACTER_NULO;
	}
	return true;
}

/*Pre: "nombre_archivo" debe ser un string válido junto al char "separador"*/
/*Pos: Devuelve un puntero a una estructura de tipo archivo_csv inicializada con el archivo abierto y el separador recibido. En caso de error devuelve NULL.*/

struct archivo_csv *abrir_archivo_csv(const char *nombre_archivo,
				      char separador)
{
	struct archivo_csv *archivo = inicializar_estructura_csv(separador);

	if (!archivo) {
		return NULL;
	}

	archivo->archivo = abrir_archivo(nombre_archivo);

	if (!archivo->archivo) {
		free(archivo);
		return NULL;
	}

	return archivo;
}

/*Pre: "archivo" debe ser un struct válido y apuntar a un archivo abierto, "funciones" debe ser un array válido de punteros que acepten correctamente sus
		respectivos parámetros y devuelvan un booleano.
		"columnas" debe ser mayor a 0.*/
/*Pos: Lee una línea del archivo CSV y aplica las funciones correspondientes a cada columna. Devuelve la cantidad de columnas leídas correctamente.*/

size_t leer_linea_csv(struct archivo_csv *archivo, size_t columnas,
		      bool (*funciones[])(const char *, void *), void *ctx[])
{
	size_t columna_actual = 0;
	char linea[CARACTERES_POR_LINEA];

	if (!son_argumentos_validos(archivo, funciones, ctx) ||
	    !es_linea_valida(archivo, linea, sizeof(linea))) {
		return 0;
	}

	size_t long_linea = strlen(linea);
	char *posicion_actual = linea;

	while (columna_actual < columnas && *posicion_actual != CARACTER_NULO) {
		size_t posicion_separador = buscar_posicion_separador(
			posicion_actual, archivo->separador);
		char *fin_columna = posicion_actual + posicion_separador;

		procesar_separador(posicion_actual, posicion_separador,
				   long_linea, archivo->separador,
				   &fin_columna);

		if (!es_funcion_valida(funciones, columna_actual) ||
		    !es_resultado_verdadero(funciones, ctx, columna_actual,
					    posicion_actual)) {
			return columna_actual;
		}

		columna_actual++;
		posicion_actual = fin_columna;

		if (!procesar_linea(archivo, linea, sizeof(linea), &long_linea,
				    &posicion_actual, fin_columna,
				    columna_actual, columnas)) {
			return columna_actual;
		}
	}

	return columna_actual;
}

/*Pre: "archivo" debería idealmente ser un struct inicializado y válido.*/
/*Pos: Cierra el archivo y libera la memoria del struct.*/

void cerrar_archivo_csv(struct archivo_csv *archivo)
{
	if (archivo != NULL) {
		if (archivo->archivo != NULL) {
			fclose(archivo->archivo);
			archivo->archivo = NULL;
		}
		free(archivo);
	}
}