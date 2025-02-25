#ifndef LOGICA_H
#define LOGICA_H

#include "menu.h"
#include "pokedex.h"
#include "pokemon.h"
#include "csv.h"
#include "jugador.h"
#include "../extra/engine.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Pre: El puntero `menu` debe ser un puntero válido a una estructura de tipo `menu_t`. */
/* Pos: Carga las acciones correspondientes al menú en la estructura `menu`. */
void cargar_acciones_menu(menu_t *menu);

/* Pre: Las variables `filas` y `columnas` deben ser mayores que 0. */
/* Pos: Retorna un puntero a una matriz dinámica de caracteres de tamaño `filas x columnas`. */
char **crear_tablero(size_t filas, size_t columnas);

/* Pre: `tablero` debe ser un puntero válido a una matriz de caracteres, 
   y `filas` y `columnas` deben ser mayores que 0. */
/* Pos: Inicializa la matriz `tablero` con valores vacíos en todas las posiciones. */
void definir_tablero_vacio(char **tablero, size_t filas, size_t columnas);

/* Pre: `tablero` debe ser un puntero válido a una matriz de caracteres, 
   y `filas` y `columnas` deben ser mayores que 0.
   `pokemones` debe ser un puntero válido a un árbol binario de búsqueda de pokemones. */
/* Pos: Imprime el tablero de juego en la salida estándar con los pokemones colocados en el tablero. */
void imprimir_tablero(char **tablero, size_t filas, size_t columnas,
		      abb_t *pokemones);

/* Pre: `tablero` debe ser un puntero válido a una matriz de caracteres, 
   `pokemones_en_juego` debe ser un puntero válido a un árbol binario de búsqueda de pokemones,
   y `entrada` debe ser un valor numérico correspondiente a una acción válida. */
/* Pos: Los pokemones se mueven según la acción indicada por `entrada` en el tablero. */
void mover_pokemones(char **tablero, abb_t *pokemones_en_juego, int entrada);

/* Pre: `tablero` debe ser un puntero válido a una matriz de caracteres, 
   y `filas` debe ser mayor que 0. */
/* Pos: Se libera la memoria de la matriz `tablero`. */
void destruir_tablero(char **tablero, size_t filas);

/* Pre: `jugador` debe ser un puntero válido a un objeto de tipo `jugador_t`. */
/* Pos: Muestra el último pokemon capturado por el jugador. */
void mostrar_ultimo_capturado(jugador_t *jugador);

/* Pre: `pokedex` debe ser un puntero válido a una estructura de tipo `pokedex_t`, 
   `tablero` debe ser una matriz de caracteres válida, 
   y `pokemones_en_juego` debe ser un puntero válido a un árbol binario de búsqueda de pokemones. */
/* Pos: Ubica los pokemones aleatoriamente en el tablero. */
void ubicar_pokemones_aleatorios(pokedex_t *pokedex, char **tablero,
				 abb_t *pokemones_en_juego);

/* Pre: `jugador` debe ser un puntero válido a un objeto de tipo `jugador_t`, 
   `pokemones_en_juego` debe ser un puntero válido a un árbol binario de búsqueda de pokemones,
   `pokedex` debe ser un puntero válido a una estructura de tipo `pokedex_t`, 
   y `tablero` debe ser una matriz de caracteres válida. */
/* Pos: El jugador captura un pokemon del tablero, actualizando su estado y el del tablero. */
void capturar_pokemones(jugador_t *jugador, abb_t *pokemones_en_juego,
			pokedex_t *pokedex, char **tablero);

/* Pre: `tablero` debe ser un puntero válido a una matriz de caracteres, 
   y `x`, `y` deben ser índices válidos dentro de las dimensiones del tablero. */
/* Pos: El jugador se ubica en las coordenadas `(x, y)` en el tablero. */
void ubicar_jugador(char **tablero, size_t x, size_t y);

#endif // LOGICA_H
