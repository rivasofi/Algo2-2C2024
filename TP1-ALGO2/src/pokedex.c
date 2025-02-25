#include "pokedex.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const int CANT_NULA = 0;
const int COMPARACION_MENOR = 0;
const int IGUALES = 0;

struct pokedex {
	struct pokemon *pokemones;
	size_t cantidad;
};

/*Pre: "puntero" debe ser devuelto por una función de memoria dinámica. Debe ser válido o NULL.*/
/*Pos: Devuelve true si "puntero" no es NULL, caso contrario devuelve false.*/

bool realloc_exitoso(void *puntero)
{
	return puntero != NULL;
}

/*Pre: "nombre" debe ser un puntero a un string válido.*/
/*Pos: Devuelve un puntero a un string duplicado.*/

char *duplicar_nombre(const char *nombre)
{
	if (!nombre)
		return NULL;
	size_t longitud = strlen(nombre) + 1;
	char *nombre_copia = (char *)malloc(longitud);
	if (nombre_copia) {
		strcpy(nombre_copia, nombre);
	}
	return nombre_copia;
}

/*Pre: "pokedex" debe ser un puntero válido que apunte a un struct del tipo pokedex inicializado y con valores válidos/coherentes. Además no debe ser NULL.*/
/*Pos: Ordena los pokemones de la pokedex alfabéticamente.*/

void ordenar_pokemones_alfabeticamente(struct pokedex *pokedex)
{
	for (size_t i = 0; i < pokedex->cantidad; i++) {
		for (size_t j = i + 1; j < pokedex->cantidad; j++) {
			if (strcmp(pokedex->pokemones[i].nombre,
				   pokedex->pokemones[j].nombre) > CANT_NULA) {
				struct pokemon aux = pokedex->pokemones[i];
				pokedex->pokemones[i] = pokedex->pokemones[j];
				pokedex->pokemones[j] = aux;
			}
		}
	}
}

/*Pre: "pokedex" debe ser un puntero válido que apunte a un struct del tipo pokedex inicializado y con valores válidos/coherentes. Además no debe ser NULL.*/
/*Pos: Devuelve true si los pokemones de la pokedex están ordenados alfabéticamente, caso contrario devuelve false.*/

bool pokemones_ordenados(struct pokedex *pokedex)
{
	if (pokedex == NULL || pokedex->pokemones == NULL ||
	    pokedex->cantidad <= 1) {
		return true;
	}

	size_t i = CANT_NULA;
	bool ordenados = true;

	while (i < pokedex->cantidad - 1 && ordenados) {
		if (strcmp(pokedex->pokemones[i].nombre,
			   pokedex->pokemones[i + 1].nombre) > CANT_NULA)
			ordenados = false;
		i++;
	}

	return ordenados;
}

/*Pre: "pokedex" debe ser un puntero válido que apunte a un struct del tipo pokedex inicializado y con valores válidos/coherentes. Además no debe ser NULL.*/
/*Pos: Ordena los pokemones de la pokedex alfabéticamente si no están ordenados.*/

void ordenar_si_necesario(struct pokedex *pokedex)
{
	if (!pokemones_ordenados(pokedex))
		ordenar_pokemones_alfabeticamente(pokedex);
}

/*Pre: "pokedex" debe ser un puntero válido que apunte a un struct del tipo pokedex inicializado y con valores válidos/coherentes. Además no debe ser NULL.
		El parámetro pos debe ser menor a la cantidad de pokemones*/
/*Pos: Desplaza los pokemones para una inserción ordenada.*/

void desplazar_pokemones(struct pokedex *pokedex, size_t pos)
{
	for (size_t i = pokedex->cantidad; i > pos; i--) {
		pokedex->pokemones[i] = pokedex->pokemones[i - 1];
	}
}

/*Pre: "pokedex" debe ser un puntero válido que apunte a un struct del tipo pokedex correctamente inicializado y con valores válidos/coherentes. Además no debe ser NULL.
		El parámetro "nombre" debe ser un string válido.*/
/*Pos: Devuelve la posición en la que se debe insertar un pokemon en la pokedex para que siga ordenada alfabéticamente.*/

size_t encontrar_pos_insertar(struct pokedex *pokedex, const char *nombre)
{
	size_t i = 0;
	while (i < pokedex->cantidad &&
	       strcmp(pokedex->pokemones[i].nombre, nombre) < COMPARACION_MENOR)
		i++;
	return i;
}

/*Pos: Devuelve un puntero a un struct del tipo pokedex inicializado de forma correcta y vacío. En caso de que el malloc falle devuelve NULL.*/

struct pokedex *pokedex_crear()
{
	struct pokedex *pokedex = malloc(sizeof(struct pokedex));
	if (pokedex) {
		pokedex->pokemones = NULL;
		pokedex->cantidad = CANT_NULA;
	}
	return pokedex;
}

/*Pre: "pokedex" debe ser un puntero válido que apunte a un struct pokedex inicializado.*/
/*Pos: Devuelve true si el pokemon ha sido agregado exitosamente a la pokedex, caso contrario devuelve false.*/

bool pokedex_agregar_pokemon(struct pokedex *pokedex, struct pokemon pokemon)
{
	if (!pokedex || !pokemon.nombre)
		return false;

	struct pokemon *pokedex_actualizada =
		realloc(pokedex->pokemones,
			sizeof(struct pokemon) * (pokedex->cantidad + 1));

	if (!realloc_exitoso(pokedex_actualizada)) {
		return false;
	} else {
		pokedex->pokemones = pokedex_actualizada;
	}

	size_t pos = encontrar_pos_insertar(pokedex, pokemon.nombre);

	desplazar_pokemones(pokedex, pos);

	pokedex->pokemones[pos].nombre = duplicar_nombre(pokemon.nombre);
	if (!pokedex->pokemones[pos].nombre) {
		return false;
	}

	pokedex->pokemones[pos].tipo = pokemon.tipo;
	pokedex->pokemones[pos].fuerza = pokemon.fuerza;
	pokedex->pokemones[pos].destreza = pokemon.destreza;
	pokedex->pokemones[pos].resistencia = pokemon.resistencia;

	pokedex->cantidad++;

	return true;
}

/*Pre: "pokedex" debería ser un puntero válido que apunte a un struct pokedex inicializado. (De igual forma, hay chequeo sobre eso)*/
/*Pos: Devuelve la cantidad de pokemones que hay en la pokedex.*/

size_t pokedex_cantidad_pokemones(struct pokedex *pokedex)
{
	if (!pokedex)
		return 0;
	return pokedex->cantidad;
}

/*Pre: "pokedex" debe ser un puntero válido que apunte a un struct pokedex inicializado. Además no debe ser NULL.*/
/*Pos: Devuelve la posición del pokemón a buscar.*/

const struct pokemon *pokedex_buscar_pokemon(struct pokedex *pokedex,
					     const char *nombre)
{
	if (!pokedex || !nombre)
		return NULL;

	for (size_t i = 0; i < pokedex->cantidad; i++) {
		if (strcmp(pokedex->pokemones[i].nombre, nombre) == IGUALES)
			return &pokedex->pokemones[i];
	}

	return NULL;
}

/*Pre: "pokedex" debe ser un puntero válido que apunte a un struct pokedex inicializado. Además no debe ser NULL.
		"funcion" debe ser un puntero válido a una función que tome un puntero a struct pokemon y un puntero a void, y devuelva un bool.*/
/*Pos: Itera sobre los pokemones de la pokedex y ejecuta la función pasada por parámetro. 
		Devuelve el número de pokemones recorridos exitosamente, si termina de iterar correctamente devuelve pokedex->cantidad.*/

size_t pokedex_iterar_pokemones(struct pokedex *pokedex,
				bool (*funcion)(struct pokemon *, void *),
				void *ctx)
{
	ordenar_si_necesario(pokedex);

	size_t iterados = CANT_NULA;
	if (!pokedex || !funcion)
		return 0;

	for (size_t i = 0; i < pokedex->cantidad; i++) {
		bool resultado = funcion(&pokedex->pokemones[i], ctx);

		if (resultado) {
			iterados++;
		} else {
			return iterados + 1;
		}
	}

	return pokedex->cantidad;
}

/*Pre: "pokedex" debe ser un puntero válido que apunte a un struct pokedex inicializado. Además no debe ser NULL.*/
/*Pos: Destruye la pokedex liberando la memoria utilizada.*/

void pokedex_destruir(struct pokedex *pokedex)
{
	if (!pokedex)
		return;

	for (size_t i = 0; i < pokedex->cantidad; i++) {
		free(pokedex->pokemones[i].nombre);
	}

	free(pokedex->pokemones);
	free(pokedex);
}