#include "split.h"
#include <stdlib.h>
#include <string.h>

#define CANT_INICIAL 1
#define ERROR NULL

/*Pre: El struct "partes" debe idealmente haber sido inicializado incluso si esto se verifica al llamar a "liberar_partes". */

/*Post: Si ptr es NULL, libera la memoria asociada a "partes" y devuelve ERROR, caso contrario simplemente devuelve ptr. */

void *verificar_memoria(void *ptr, struct Partes *partes)
{
	if (!ptr) {
		liberar_partes(partes);
		return ERROR;
	}
	return ptr;
}

/*Pre: El parámetro "cantidad" debe ser igual a la cantidad de elementos asignados. */

/*Post: Si string no es NULL, todos los punteros del arreglo hasta la posición [cantidad] se liberan, junto a la memoria en sí del array "string". */

void liberar_elementos_string(char **string, size_t cantidad)
{
	if (string) {
		for (size_t i = 0; i < cantidad; i++) {
			free(string[i]);
		}
		free(string);
	}
}

/*Pre: El parámetro "string" debe ser no-nulo y "longitud_string" debe ser coherente a la longitud máxima del string a usar. */

/*Post: Devuelve la posición del primer separador encontrado en caso de haber uno, sino devuelve la longitud recorrida. */

size_t buscar_posicion_separador(const char *string, char separador,
				 size_t longitud_string)
{
	size_t i = 0;
	while (string[i] != separador && string[i] != '\0' &&
	       i < longitud_string) {
		i++;
	}
	return i;
}

/*Pre: El parámetro "string" no debe ser nulo. */

/*Post: Devuelve la cantidad total de separadores presentes en el string. */

size_t contabilizar_separadores(const char *string, char separador)
{
	size_t cant_separadores = 0;
	while (*string) {
		if (*string == separador) {
			cant_separadores++;
		}
		string++;
	}
	return cant_separadores;
}

/*Pre: El parámetro "longitud" debe ser un valor mayor o igual a cero. */

/*Post: Devuelve un puntero a un bloque de memoria. */

char *inicializar_substring(size_t longitud)
{
	return malloc(longitud + 1);
}

/*Pre: El parámetro "substring" debe ser válido y apuntar a un bloque de memoria suficiente, "inicio" también debe ser válido y "longitud" debe tener un valor coherente a los otros dos parámetros. */

/*Post: Si "substring" no es NULL, copia "longitud" caracteres desde inicio a substring, luego termina con un '\0' para indicar el final del string.*/

void copiar_contenido_substring(char *substring, const char *inicio,
				size_t longitud)
{
	if (substring) {
		strncpy(substring, inicio, longitud);
		substring[longitud] = '\0';
	}
}

/*Pre: El parámetro "inicio" debe ser un puntero válido, además "longitud" debe tener un valor coherente al largo del string original (que no exceda). */

/*Post: Devuelve un puntero a un nuevo substring. */

char *crear_substring(const char *inicio, size_t longitud)
{
	char *substring = inicializar_substring(longitud);

	if (substring)
		copiar_contenido_substring(substring, inicio, longitud);

	return substring;
}

/*Pre: El caracter "separador" debe ser un caracter válido que se usará para dividir la cadena. */

/*Post: Devuelve un struct que contiene información sobre el string que fue separado (substrings y cantidad de estos). Además maneja casos especiales en los que el string puede ser nulo o estar vacío. */

struct Partes *dividir_string(const char *string, char separador)
{
	struct Partes *partes = malloc(sizeof(struct Partes));

	if (!verificar_memoria(partes, NULL))
		return ERROR;

	if (!string) {
		partes->cantidad = 0;
		partes->string = NULL;
		return partes;
	}

	size_t longitud_string = strlen(string);

	if (longitud_string == 0) {
		partes->cantidad = CANT_INICIAL;
		partes->string =
			verificar_memoria(malloc(sizeof(char *)), partes);
		if (!partes->string)
			return ERROR;

		partes->string[0] =
			verificar_memoria(malloc(sizeof(char)), partes);
		if (!partes->string[0])
			return ERROR;

		partes->string[0][0] = '\0';
		return partes;
	}

	size_t cantidad =
		CANT_INICIAL + contabilizar_separadores(string, separador);

	partes->cantidad = cantidad;
	partes->string =
		verificar_memoria(malloc(sizeof(char *) * cantidad), partes);
	if (!partes->string)
		return ERROR;

	size_t inicio = 0;
	size_t fin =
		buscar_posicion_separador(string, separador, longitud_string);

	for (size_t i = 0; i < cantidad; i++) {
		size_t longitud_substring = fin - inicio;
		partes->string[i] = verificar_memoria(
			malloc(sizeof(char) * (fin - inicio + 1)), partes);

		if (!partes->string[i])
			return ERROR;

		char *substring =
			crear_substring(&string[inicio], longitud_substring);

		if (!verificar_memoria(substring, partes))
			return ERROR;

		copiar_contenido_substring(partes->string[i], substring,
					   longitud_substring);
		free(substring);

		inicio = fin + 1;
		fin = buscar_posicion_separador(&string[inicio], separador,
						longitud_string - inicio) +
		      inicio;
	}

	if (partes)
		return partes;

	return NULL;
}

/*Pre: No tiene precondición, la función está hecha para realizar tanto el caso como en el que "partes" es NULL como en el que no lo es. */

/*Post: Si "partes" no es NULL, libera cada string en el array "partes->string", el array en sí mismo y la estructura "partes" en sí. */

void liberar_partes(struct Partes *partes)
{
	if (partes) {
		liberar_elementos_string(partes->string, partes->cantidad);
		free(partes);
	}
}