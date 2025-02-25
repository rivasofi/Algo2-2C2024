#include "pokemon.h"
#define SON_IGUALES 0
#define ERROR -1
#define FILA_EXCEDIDA 16
#define COLUMNA_EXCEDIDA 33

struct Pokemon {
	char *nombre;
	int puntos;
	char *color;
	char *movimiento;
	int x;
	int y;
	int indice;
};

struct contexto {
	size_t contador;
	size_t indice;
	pokemon_t *pokemon;
};

int comparar_pokemon(void *a, void *b)
{
	if (!a || !b) {
		return ERROR;
	}

	pokemon_t *pokemon_a = (pokemon_t *)a;
	pokemon_t *pokemon_b = (pokemon_t *)b;

	int comparacion = strcmp(pokemon_a->nombre, pokemon_b->nombre);
	if (comparacion != SON_IGUALES) {
		return comparacion;
	}

	if (pokemon_a->x != pokemon_b->x) {
		return pokemon_a->x - pokemon_b->x;
	}
	return pokemon_a->y - pokemon_b->y;
}

char *duplicar_cadena(char *cadena)
{
	if (!cadena) {
		return NULL;
	}

	size_t longitud = strlen(cadena);
	char *copia = malloc((longitud + 1) * sizeof(char));
	if (!copia) {
		return NULL;
	}

	for (size_t i = 0; i <= longitud; i++) {
		copia[i] = cadena[i];
	}
	return copia;
}

pokemon_t *copiar_pokemon(pokemon_t *original)
{
	if (!original) {
		return NULL;
	}

	pokemon_t *copia = malloc(sizeof(pokemon_t));
	if (!copia) {
		return NULL;
	}

	copia->nombre = duplicar_cadena(original->nombre);
	if (!copia->nombre) {
		free(copia);
		return NULL;
	}

	copia->color = duplicar_cadena(original->color);
	if (!copia->color) {
		free(copia->nombre);
		free(copia);
		return NULL;
	}

	copia->movimiento = duplicar_cadena(original->movimiento);
	if (!copia->movimiento) {
		free(copia->nombre);
		free(copia->color);
		free(copia);
		return NULL;
	}

	copia->puntos = original->puntos;
	copia->x = original->x;
	copia->y = original->y;
	copia->indice = original->indice;

	return copia;
}

int obtener_x_pokemon(pokemon_t *pokemon)
{
	if (!pokemon) {
		return ERROR;
	}

	int x = pokemon ? pokemon->x : ERROR;
	return x;
}

int obtener_y_pokemon(pokemon_t *pokemon)
{
	if (!pokemon) {
		return ERROR;
	}

	int y = pokemon ? pokemon->y : ERROR;
	return y;
}

int obtener_indice_pokemon(pokemon_t *pokemon)
{
	if (!pokemon) {
		return ERROR;
	}
	return pokemon->indice;
}

void asignar_x_pokemon(pokemon_t *pokemon, int x)
{
	if (!pokemon) {
		return;
	}

	pokemon->x = x;
}

void asignar_y_pokemon(pokemon_t *pokemon, int y)
{
	if (!pokemon) {
		return;
	}

	pokemon->y = y;
}

bool _obtener_pokemon_por_indice_helper(void *elemento, void *contexto)
{
	if (!elemento || !contexto) {
		return true;
	}

	struct contexto *ctx = contexto;
	if (ctx->contador == ctx->indice) {
		ctx->pokemon = (pokemon_t *)elemento;
		return false;
	}
	ctx->contador++;
	return true;
}

pokemon_t *obtener_pokemon_por_indice(abb_t *abb, size_t indice)
{
	if (!abb) {
		return NULL;
	}

	struct contexto ctx = { 0, indice, NULL };
	abb_iterar_inorden(abb, _obtener_pokemon_por_indice_helper, &ctx);
	return ctx.pokemon;
}

int obtener_puntos_pokemon(pokemon_t *pokemon)
{
	if (!pokemon) {
		return ERROR;
	}

	return pokemon->puntos;
}

char *obtener_movimientos_pokemon(pokemon_t *pokemon)
{
	if (!pokemon) {
		return NULL;
	}

	if (!pokemon->movimiento) {
		return NULL;
	}

	return pokemon->movimiento;
}

int obtener_cantidad_movimientos_pokemon(pokemon_t *pokemon)
{
	if (!pokemon) {
		return ERROR;
	}

	return (int)strlen(obtener_movimientos_pokemon(pokemon));
}

bool buscar_por_coordenadas(void *elemento, void *ctx)
{
	if (!elemento || !ctx) {
		return true;
	}

	struct contexto *contexto = (struct contexto *)ctx;
	pokemon_t *pokemon = (pokemon_t *)elemento;

	if (obtener_x_pokemon(pokemon) == contexto->contador &&
	    obtener_y_pokemon(pokemon) == contexto->indice) {
		contexto->pokemon = pokemon;
		return false;
	}
	return true;
}

pokemon_t *buscar_pokemon_por_coordenadas(abb_t *arbol_pokemones, size_t x,
					  size_t y)
{
	if (!arbol_pokemones) {
		return NULL;
	}

	struct contexto contexto = { .contador = x,
				     .indice = y,
				     .pokemon = NULL };

	abb_iterar_inorden(arbol_pokemones, buscar_por_coordenadas, &contexto);

	return contexto.pokemon;
}

char *obtener_nombre_pokemon(pokemon_t *pokemon)
{
	if (!pokemon) {
		return NULL;
	}

	if (!pokemon->nombre) {
		return NULL;
	}

	return pokemon->nombre;
}

char *obtener_color_pokemon(pokemon_t *pokemon)
{
	if (!pokemon) {
		return NULL;
	}

	if (!pokemon->color) {
		return NULL;
	}

	return pokemon->color;
}

pokemon_t *crear_pokemon(const char *nombre, int puntos, char *color,
			 char *movimiento, int indice)
{
	if (!nombre || !color || !movimiento) {
		return NULL;
	}

	pokemon_t *nuevo_pokemon = malloc(sizeof(pokemon_t));
	if (nuevo_pokemon == NULL) {
		return NULL;
	}

	nuevo_pokemon->nombre = malloc(strlen(nombre) + 1);
	nuevo_pokemon->color = malloc(strlen(color) + 1);
	nuevo_pokemon->movimiento = malloc(strlen(movimiento) + 1);

	if (nuevo_pokemon->nombre == NULL) {
		free(nuevo_pokemon);
		return NULL;
	}

	if (color == NULL || movimiento == NULL) {
		free(nuevo_pokemon->nombre);
		free(nuevo_pokemon);
		return NULL;
	}

	strcpy(nuevo_pokemon->nombre, nombre);
	strcpy(nuevo_pokemon->color, color);
	strcpy(nuevo_pokemon->movimiento, movimiento);

	nuevo_pokemon->puntos = puntos;
	nuevo_pokemon->indice = indice;
	nuevo_pokemon->x = FILA_EXCEDIDA;
	nuevo_pokemon->y = COLUMNA_EXCEDIDA;

	return nuevo_pokemon;
}

void imprimir_pokemon(pokemon_t *pokemon)
{
	if (!pokemon) {
		return;
	}

	printf("\t\t\t%-45s %-40i %-45s %-55s\n", pokemon->nombre,
	       pokemon->puntos, pokemon->color, pokemon->movimiento);
}

char obtener_inicial_pokemon(pokemon_t *pokemon)
{
	if (!pokemon || !(pokemon->nombre) || *(pokemon->nombre) == '\0') {
		return '\0';
	}
	return pokemon->nombre[0];
}

bool buscar_inicial(void *elemento, void *ctx)
{
	if (!elemento || !ctx) {
		return true;
	}

	struct contexto *contexto = (struct contexto *)ctx;
	pokemon_t *pokemon = (pokemon_t *)elemento;

	if (obtener_inicial_pokemon(pokemon) == contexto->contador) {
		contexto->pokemon = pokemon;
		return false;
	}
	return true;
}

pokemon_t *buscar_pokemon_por_inicial(abb_t *arbol_pokemones, char inicial)
{
	if (!arbol_pokemones)
		return NULL;

	struct contexto contexto = { .contador = (size_t)inicial,
				     .indice = 0,
				     .pokemon = NULL };

	abb_iterar_inorden(arbol_pokemones, buscar_inicial, &contexto);

	return contexto.pokemon;
}

char *devolver_codigo_color_pokemon(pokemon_t *pokemon)
{
	if (!pokemon) {
		return NULL;
	}

	if (!pokemon->color) {
		return ANSI_COLOR_RESET;
	}

	if (strcmp(pokemon->color, "NEGRO") == SON_IGUALES) {
		return ANSI_COLOR_BLACK;
	} else if (strcmp(pokemon->color, "ROJO") == SON_IGUALES) {
		return ANSI_COLOR_RED;
	} else if (strcmp(pokemon->color, "VERDE") == SON_IGUALES) {
		return ANSI_COLOR_GREEN;
	} else if (strcmp(pokemon->color, "AMARILLO") == SON_IGUALES) {
		return ANSI_COLOR_YELLOW;
	} else if (strcmp(pokemon->color, "AZUL") == SON_IGUALES) {
		return ANSI_COLOR_BLUE;
	} else if (strcmp(pokemon->color, "MAGENTA") == SON_IGUALES) {
		return ANSI_COLOR_MAGENTA;
	} else if (strcmp(pokemon->color, "CYAN") == SON_IGUALES) {
		return ANSI_COLOR_CYAN;
	} else if (strcmp(pokemon->color, "BLANCO") == SON_IGUALES) {
		return ANSI_COLOR_WHITE;
	}

	return ANSI_COLOR_RESET;
}

void liberar_pokemon(void *pokemon)
{
	pokemon_t *poke = pokemon;
	if (poke) {
		free(poke->nombre);
		free(poke->color);
		free(poke->movimiento);
		free(poke);
	} else {
		return;
	}
}