#include "pokedex.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define COLUMNAS_POKEDEX 4
#define NO_LEYO 0
#define PUDO_LEER 1
#define ERROR -1
#define CANTIDAD_INICIAL 0

struct Pokemon {
	char *nombre;
	int puntos;
	char *color;
	char *movimiento;
	int x;
	int y;
	int indice;
};

struct Pokedex {
	abb_t *pokemones;
	size_t cantidad;
};

int comparar_case_insensitive(const char *a, const char *b)
{
	if (!a || !b) {
		return ERROR;
	}

	while (*a && *b &&
	       tolower((unsigned char)*a) == tolower((unsigned char)*b)) {
		a++;
		b++;
	}
	return tolower((unsigned char)*a) - tolower((unsigned char)*b);
}

int comparar_nombre_pokemon(void *_pokemon1, void *_pokemon2)
{
	if (!_pokemon1 || !_pokemon2) {
		return ERROR;
	}

	pokemon_t *pokemon1 = (pokemon_t *)_pokemon1;
	pokemon_t *pokemon2 = (pokemon_t *)_pokemon2;

	return comparar_case_insensitive(pokemon1->nombre, pokemon2->nombre);
}

abb_t *obtener_arbol_pokemones(pokedex_t *pokedex)
{
	if (!pokedex) {
		return NULL;
	}

	return pokedex ? pokedex->pokemones : NULL;
}

/*----*/

bool leer_int(const char *str, void *ctx)
{
	if (!str || !ctx) {
		return false;
	}

	return sscanf(str, "%d", (int *)ctx) == PUDO_LEER;
}

bool crear_string_nuevo(const char *str, void *ctx)
{
	if (!str || !ctx) {
		return false;
	}

	char *nuevo = malloc(strlen(str) + 1);
	if (!nuevo) {
		return false;
	}
	strcpy(nuevo, str);
	*(char **)ctx = nuevo;
	return true;
}

bool parsear_datos_pokemon(struct archivo_csv *archivo, char **string,
			   int *puntos, char **color, char **movimiento)
{
	if (!archivo || !string || !puntos || !color || !movimiento) {
		return false;
	}

	bool (*funciones[])(const char *,
			    void *) = { crear_string_nuevo, leer_int,
					crear_string_nuevo, crear_string_nuevo,
					crear_string_nuevo };
	void *ptrs[] = { string, puntos, color, movimiento };

	size_t leidos =
		leer_linea_csv(archivo, COLUMNAS_POKEDEX, funciones, ptrs);
	if (leidos == NO_LEYO) {
		return false;
	}
	if (leidos != COLUMNAS_POKEDEX) {
		return false;
	}
	return true;
}

/*----*/

pokedex_t *crear_pokedex()
{
	pokedex_t *pokedex = malloc(sizeof(pokedex_t));
	if (pokedex == NULL) {
		fprintf(stderr, "Error al reservar memoria para el pokedex\n");
		return NULL;
	}

	pokedex->pokemones = abb_crear(comparar_nombre_pokemon);
	if (pokedex->pokemones == NULL) {
		free(pokedex);
		fprintf(stderr, "Error al reservar memoria para el pokedex\n");
		return NULL;
	}

	pokedex->cantidad = 0;

	return pokedex;
}

void cargar_pokedex(pokedex_t *pokedex, struct archivo_csv *archivo)
{
	if (!pokedex || !archivo) {
		return;
	}

	int indice = CANTIDAD_INICIAL;
	pokedex->cantidad = CANTIDAD_INICIAL;

	char *nombre = NULL;
	int puntos = CANTIDAD_INICIAL;
	char *color = NULL;
	char *movimiento = NULL;

	while (parsear_datos_pokemon(archivo, &nombre, &puntos, &color,
				     &movimiento) &&
	       indice <= abb_cantidad(pokedex->pokemones)) {
		if (nombre && color && movimiento) {
			abb_insertar(pokedex->pokemones,
				     crear_pokemon(nombre, puntos, color,
						   movimiento, indice));
			free(nombre);
			free(color);
			free(movimiento);
			indice++;
			pokedex->cantidad++;
		}
	}
}

void mostrar_pokedex(pokedex_t *pokedex)
{
	if (!pokedex) {
		return;
	}

	abb_iterar_inorden(pokedex->pokemones,
			   (bool (*)(void *, void *))imprimir_pokemon, NULL);
}

size_t obtener_cantidad_pokemones(pokedex_t *pokedex)
{
	if (!pokedex) {
		return 0;
	}

	return pokedex->cantidad;
}

void destruir_pokedex(pokedex_t *pokedex)
{
	if (!pokedex) {
		return;
	}

	if (pokedex->pokemones) {
		abb_destruir_todo(pokedex->pokemones, liberar_pokemon);
	}
	free(pokedex);
}