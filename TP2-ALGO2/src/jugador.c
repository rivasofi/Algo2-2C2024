#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "pokedex.h"
#include "jugador.h"

#define NO_VACIA 0
#define VALORES_INICIALES 0
#define MULTIPLICADOR_INICIAL 1
#define ERROR -1
#define MAXIMA_FILA 14
#define MAXIMA_COLUMNA 31

typedef struct stats {
	int movimientos;
	int puntos;
	int multiplicador;
	int multiplicador_mas_alto;
	pokemon_t *ultimo_capturado;
	Lista *combo_mas_largo;
} stats_t;

struct jugador {
	int x;
	int y;
	int iteraciones;
	stats_t *stats;
};

void vaciar_combo(Lista *lista)
{
	if (!lista) {
		return;
	}
	while (lista_cantidad_elementos(lista) > NO_VACIA) {
		lista_quitar_elemento(lista, 0, NULL);
	}
}

void inicializar_jugador(jugador_t *jugador)
{
	if (!jugador) {
		return;
	}

	jugador->stats = malloc(sizeof(stats_t));

	if (!jugador->stats) {
		return;
	}

	jugador->x = VALORES_INICIALES;
	jugador->y = VALORES_INICIALES;
	jugador->iteraciones = VALORES_INICIALES;

	jugador->stats->movimientos = VALORES_INICIALES;
	jugador->stats->puntos = VALORES_INICIALES;
	jugador->stats->multiplicador = MULTIPLICADOR_INICIAL;
	jugador->stats->multiplicador_mas_alto = MULTIPLICADOR_INICIAL;
	jugador->stats->ultimo_capturado = NULL;
	jugador->stats->combo_mas_largo = lista_crear();
}

int obtener_x_jugador(jugador_t *jugador)
{
	if (!jugador) {
		return ERROR;
	}

	return jugador->x;
}

int obtener_y_jugador(jugador_t *jugador)
{
	if (!jugador) {
		return ERROR;
	}

	return jugador->y;
}

int obtener_movimientos_jugador(jugador_t *jugador)
{
	if (!jugador) {
		return ERROR;
	}

	return jugador->stats->movimientos;
}

int obtener_iteraciones_jugador(jugador_t *jugador)
{
	if (!jugador) {
		return ERROR;
	}

	return jugador->iteraciones;
}

int obtener_puntos_jugador(jugador_t *jugador)
{
	if (!jugador) {
		return ERROR;
	}

	return jugador->stats->puntos;
}

int obtener_multiplicador_jugador(jugador_t *jugador)
{
	if (!jugador) {
		return ERROR;
	}

	return jugador->stats->multiplicador;
}

void incrementar_combo(jugador_t *jugador, pokemon_t *pokemon)
{
	if (!jugador || !pokemon) {
		return;
	}

	size_t longitud_combo_actual =
		lista_cantidad_elementos(jugador->stats->combo_mas_largo);

	if (longitud_combo_actual < jugador->stats->multiplicador) {
		vaciar_combo(jugador->stats->combo_mas_largo);
		lista_agregar_al_final(jugador->stats->combo_mas_largo,
				       pokemon);
	} else {
		lista_agregar_al_final(jugador->stats->combo_mas_largo,
				       pokemon);
	}
}

void incrementar_multiplicador_jugador(jugador_t *jugador, pokemon_t *pokemon)
{
	if (!jugador || !pokemon) {
		return;
	}

	jugador->stats->multiplicador++;

	if (jugador->stats->multiplicador >
	    jugador->stats->multiplicador_mas_alto) {
		jugador->stats->multiplicador_mas_alto =
			jugador->stats->multiplicador;
		incrementar_combo(jugador, pokemon);
	} else {
		lista_agregar_al_final(jugador->stats->combo_mas_largo,
				       pokemon);
	}
}

void resetear_multiplicador_jugador(jugador_t *jugador)
{
	if (!jugador) {
		return;
	}

	jugador->stats->multiplicador = MULTIPLICADOR_INICIAL;
}

int obtener_multiplicador_mas_alto_jugador(jugador_t *jugador)
{
	if (!jugador) {
		return ERROR;
	}

	return jugador->stats->multiplicador_mas_alto;
}

void actualizar_ultimo_capturado(jugador_t *jugador, pokemon_t *pokemon)
{
	if (!jugador || !pokemon) {
		return;
	}

	if (jugador->stats->ultimo_capturado) {
		liberar_pokemon(jugador->stats->ultimo_capturado);
	}
	jugador->stats->ultimo_capturado = copiar_pokemon(pokemon);
}

pokemon_t *obtener_ultimo_capturado_jugador(jugador_t *jugador)
{
	if (jugador && jugador->stats) {
		return jugador->stats->ultimo_capturado;
	}
	return NULL;
}

char *obtener_nombre_ultimo_capturado(jugador_t *jugador)
{
	if (!jugador || !jugador->stats || !jugador->stats->ultimo_capturado) {
		return NULL;
	}

	return obtener_nombre_pokemon(jugador->stats->ultimo_capturado);
}

jugador_t *crear_jugador()
{
	jugador_t *jugador = malloc(sizeof(jugador_t));
	if (!jugador) {
		return NULL;
	}

	inicializar_jugador(jugador);

	return jugador;
}

void sumar_puntos_jugador(jugador_t *jugador, pokemon_t *pokemon)
{
	if (!jugador || !pokemon) {
		return;
	}

	int puntos = obtener_puntos_pokemon(pokemon);
	jugador->stats->puntos += puntos * jugador->stats->multiplicador;
}

void mover_jugador(int entrada, jugador_t *jugador, char **tablero)
{
	if (!jugador || !tablero) {
		return;
	}

	tablero[jugador->x][jugador->y] = ' ';

	if (entrada == TECLA_DERECHA) {
		jugador->y++;
	} else if (entrada == TECLA_IZQUIERDA) {
		jugador->y--;
	} else if (entrada == TECLA_ARRIBA) {
		jugador->x--;
	} else if (entrada == TECLA_ABAJO) {
		jugador->x++;
	}

	jugador->x = min(MAXIMA_FILA, max(0, jugador->x));
	jugador->y = min(MAXIMA_COLUMNA, max(0, jugador->y));
	jugador->stats->movimientos++;
}

void incrementar_iteraciones_jugador(jugador_t *jugador)
{
	if (!jugador) {
		return;
	}

	jugador->iteraciones++;
}

void destruir_jugador(jugador_t *jugador)
{
	if (!jugador) {
		return;
	}

	if (jugador->stats) {
		lista_destruir(jugador->stats->combo_mas_largo);
		liberar_pokemon(jugador->stats->ultimo_capturado);
		free(jugador->stats);
	}

	free(jugador);
}