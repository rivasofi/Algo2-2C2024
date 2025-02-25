#ifndef JUGADOR_H
#define JUGADOR_H

#include "pokedex.h"
#include "csv.h"
#include "../extra/engine.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b);
int min(int a, int b);

typedef struct jugador jugador_t;

/* Pos: Se crea un jugador con valores iniciales predeterminados y se retorna el puntero al jugador creado. */
jugador_t *crear_jugador();

/* Pre: El jugador debe ser un puntero válido, y el pokemon debe ser un puntero válido. */
/* Pos: Incrementa los puntos del jugador, sumando los puntos del pokemon multiplicados por el multiplicador del jugador. */
void sumar_puntos_jugador(jugador_t *jugador, pokemon_t *pokemon);

/* Pre: El jugador debe ser un puntero válido. */
/* Pos: Incrementa las iteraciones del jugador. */
void incrementar_iteraciones_jugador(jugador_t *jugador);

/* Pre: El jugador debe ser un puntero válido, y el tablero debe ser un puntero válido de un arreglo de cadenas. */
/* Pos: Mueve al jugador según la entrada (derecha, izquierda, arriba, abajo) y actualiza su posición en el tablero. */
void mover_jugador(int entrada, jugador_t *jugador, char **tablero);

/* Pre: El jugador debe ser un puntero válido. */
/* Pos: Libera los recursos del jugador y de su estructura de stats. */
void destruir_jugador(jugador_t *jugador);

/* Pre: El jugador debe ser un puntero válido. */
/* Pos: Retorna la posición X del jugador. */
int obtener_x_jugador(jugador_t *jugador);

/* Pre: El jugador debe ser un puntero válido. */
/* Pos: Retorna la posición Y del jugador. */
int obtener_y_jugador(jugador_t *jugador);

/* Pre: El jugador debe ser un puntero válido. */
/* Pos: Retorna los puntos acumulados por el jugador. */
int obtener_puntos_jugador(jugador_t *jugador);

/* Pre: El jugador debe ser un puntero válido. */
/* Pos: Retorna la cantidad de movimientos realizados por el jugador. */
int obtener_movimientos_jugador(jugador_t *jugador);

/* Pre: El jugador debe ser un puntero válido. */
/* Pos: Retorna la cantidad de iteraciones realizadas en la partida del actual jugador. */
int obtener_iteraciones_jugador(jugador_t *jugador);

/* Pre: El jugador debe ser un puntero válido. */
/* Pos: Retorna el multiplicador actual del jugador. */
int obtener_multiplicador_jugador(jugador_t *jugador);

/* Pre: El jugador debe ser un puntero válido, y el pokemon debe ser un puntero válido. */
/* Pos: Incrementa el multiplicador del jugador, actualizando también el combo. */
void incrementar_multiplicador_jugador(jugador_t *jugador, pokemon_t *pokemon);

/* Pre: El jugador debe ser un puntero válido. */
/* Pos: Resetea el multiplicador del jugador a 1. */
void resetear_multiplicador_jugador(jugador_t *jugador);

/* Pre: El jugador debe ser un puntero válido. */
/* Pos: Retorna el combo más largo del jugador. */
int obtener_multiplicador_mas_alto_jugador(jugador_t *jugador);

/* Pre: El jugador debe ser un puntero válido. */
/* Pos: Retorna el puntero al último pokemon capturado por el jugador. */
pokemon_t *obtener_ultimo_capturado_jugador(jugador_t *jugador);

/* Pre: El jugador debe ser un puntero válido, y el pokemon debe ser un puntero válido. */
/* Pos: Actualiza el último pokemon capturado por el jugador. */
void actualizar_ultimo_capturado(jugador_t *jugador, pokemon_t *pokemon);

/* Pre: El jugador debe ser un puntero válido*/
/* Pos: Devuelve el nombre del último pokemon capturado por el jugador. */
char *obtener_nombre_ultimo_capturado(jugador_t *jugador);

#endif // JUGADOR_H