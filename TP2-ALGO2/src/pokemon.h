#ifndef POKEMON_H
#define POKEMON_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "abb.h"
#include "../extra/ansi.h"

typedef struct Pokemon pokemon_t;

/* Pre: Los punteros `a` y `b` deben ser válidos y apuntar a estructuras `pokemon_t` correctamente inicializadas. */
/* Pos: Devuelve un valor negativo si `a` es menor que `b` (por nombre), positivo si es mayor, o cero si son iguales. */
int comparar_pokemon(void *a, void *b);

/* Pre: Los punteros `nombre`, `color`, y `movimiento` deben ser cadenas no nulas. El valor `puntos` debe ser un número entero válido. */
/* Pos: Crea una nueva estructura `pokemon_t` con los datos proporcionados. Si no se puede asignar memoria, devuelve `NULL`. */
pokemon_t *crear_pokemon(const char *nombre, int puntos, char *color,
			 char *movimiento, int indice);

/* Pre: El puntero `original` debe ser válido y apuntar a una estructura `pokemon_t` correctamente inicializada. */
/* Pos: Devuelve un puntero a una nueva estructura `pokemon_t` que es una copia de `original`. Si no se puede asignar memoria, devuelve `NULL`. */
pokemon_t *copiar_pokemon(pokemon_t *original);

/* Pre: El puntero `pokemon` debe ser válido y apuntar a una estructura `pokemon_t` correctamente asignada. */
/* Pos: Libera toda la memoria utilizada por `pokemon_t`, incluyendo sus campos `nombre`, `color` y `movimiento`. */
void liberar_pokemon(void *pokemon);

/* Pre: El puntero `pokemon` debe ser válido y apuntar a una estructura `pokemon_t` correctamente inicializada. */
/* Pos: Devuelve el primer caracter del nombre del `pokemon`. Si `pokemon` es `NULL`, se devuelve `'\0'`. */
char obtener_inicial_pokemon(pokemon_t *pokemon);

/* Pre: El puntero `pokemon` debe ser válido y apuntar a una estructura `pokemon_t` con el campo `color` inicializado. */
/* Pos: Devuelve un código de color ANSI según el valor de `color`. Si el color no es válido, devuelve el valor de reset. */
char *devolver_codigo_color_pokemon(pokemon_t *pokemon);

/* Pre: El puntero `pokemon` debe ser válido y apuntar a una estructura `pokemon_t` inicializada. */
/* Pos: Devuelve el valor de la coordenada `x` del `pokemon`. Si `pokemon` es `NULL`, devuelve `ERROR`. */
int obtener_x_pokemon(pokemon_t *pokemon);

/* Pre: El puntero `pokemon` debe ser válido y apuntar a una estructura `pokemon_t` inicializada. */
/* Pos: Devuelve el valor de la coordenada `y` del `pokemon`. Si `pokemon` es `NULL`, devuelve `ERROR`. */
int obtener_y_pokemon(pokemon_t *pokemon);

/* Pre: El puntero `pokemon` debe ser válido y apuntar a una estructura `pokemon_t` correctamente inicializada. */
/* Pos: Devuelve el índice del `pokemon` dentro de la estructura o la colección. Si `pokemon` es `NULL`, devuelve `-1`. */
int obtener_indice_pokemon(pokemon_t *pokemon);

/* Pre: El puntero `pokemon` debe ser válido y apuntar a una estructura `pokemon_t` correctamente inicializada. */
/* Pos: Devuelve los puntos del `pokemon`. Si `pokemon` es `NULL`, devuelve `-1`. */
int obtener_puntos_pokemon(pokemon_t *pokemon);

/* Pre: El puntero `pokemon` debe ser válido y apuntar a una estructura `pokemon_t` inicializada. El valor `x` debe ser un número entero válido. */
/* Pos: Asigna el valor `x` a la coordenada `x` del `pokemon`. Si `pokemon` es `NULL`, no se realiza ninguna acción. */
void asignar_x_pokemon(pokemon_t *pokemon, int x);

/* Pre: El puntero `pokemon` debe ser válido y apuntar a una estructura `pokemon_t` inicializada. El valor `x` debe ser un número entero válido. */
/* Pos: Asigna el valor `y` a la coordenada `y` del `pokemon`. Si `pokemon` es `NULL`, no se realiza ninguna acción. */
void asignar_y_pokemon(pokemon_t *pokemon, int y);

/* Pre: El puntero `abb` debe ser válido y apuntar a un árbol de búsqueda binaria (ABB). El `indice` debe ser válido y dentro de los límites. */
/* Pos: Devuelve el puntero al `pokemon_t` en la posición `indice` del árbol. Si no se encuentra, devuelve `NULL`. Si `abb` es `NULL`, devuelve `NULL`. */
pokemon_t *obtener_pokemon_por_indice(abb_t *abb, size_t indice);

/* Pre: El puntero `arbol_pokemones` debe ser válido y apuntar a un árbol de búsqueda binaria (ABB). Los valores `x` y `y` deben ser válidos. */
/* Pos: Devuelve el puntero al `pokemon_t` que tiene las coordenadas `x` y `y` en el árbol. Si no se encuentra, devuelve `NULL`. */
pokemon_t *buscar_pokemon_por_coordenadas(abb_t *arbol_pokemones, size_t x,
					  size_t y);

/* Pre: El puntero `pokemon` debe ser válido y apuntar a una estructura `pokemon_t` correctamente inicializada. */
/* Pos: Devuelve un puntero a la cadena que representa los movimientos del `pokemon`. Si `pokemon` es `NULL`, devuelve `NULL`. */
char *obtener_movimientos_pokemon(pokemon_t *pokemon);

/* Pre: El puntero `pokemon` debe ser válido y apuntar a una estructura `pokemon_t` correctamente inicializada. */
/* Pos: Devuelve la cantidad de movimientos que el `pokemon` puede realizar. Si `pokemon` es `NULL`, devuelve `0`. */
int obtener_cantidad_movimientos_pokemon(pokemon_t *pokemon);

/* Pre: El puntero `pokemon` debe ser válido y apuntar a una estructura `pokemon_t` correctamente inicializada. */
/* Pos: Devuelve un puntero al nombre del `pokemon`. Si `pokemon` es `NULL`, devuelve `NULL`. */
char *obtener_nombre_pokemon(pokemon_t *pokemon);

/* Pre: El puntero `pokemon` debe ser válido y apuntar a una estructura `pokemon_t` correctamente inicializada. */
/* Pos: Devuelve un puntero al color del `pokemon`. Si `pokemon` es `NULL`, devuelve `NULL`. */
char *obtener_color_pokemon(pokemon_t *pokemon);

/* Pre: El puntero `pokemon` debe ser válido y apuntar a una estructura `pokemon_t` correctamente inicializada. */
/* Pos: Imprime en consola los detalles del `pokemon_t`. Si `pokemon` es `NULL`, no se imprime nada. */
void imprimir_pokemon(pokemon_t *pokemon);

#endif // POKEMON_H