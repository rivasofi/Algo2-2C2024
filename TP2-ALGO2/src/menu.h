#ifndef MENU_H
#define MENU_H

#include "lista.h"
#include "csv.h"
#include "pokedex.h"
#include "jugador.h"
#include "abb.h"

typedef struct Accion accion_t;
typedef struct Menu menu_t;

struct contexto_menu {
	pokedex_t *pokedex;
	jugador_t *jugador;
	abb_t *pokemones_en_juego;
	unsigned int *semilla;
};

/* Pre: El puntero `menu` debe ser un puntero válido a una estructura de tipo `menu_t`. */
/* Pos: Crea e inicializa un menú con una lista de acciones vacía. */
menu_t *crear_menu();

/* Pre: El puntero `funcion` debe ser un puntero válido a una función de tipo `void (*)(void *)`. */
/* Pos: Crea una acción con el índice `indice` y la función `funcion` asociada. */
accion_t *accion_crear(char indice, void (*funcion)(void *));

/* Pos: Imprime el menú de opciones disponible en la terminal. */
void imprimir_menu();

/* Pre: El puntero `menu` debe ser un puntero válido a una estructura de tipo `menu_t`, 
   `contexto` debe ser un puntero válido a la estructura `contexto_menu` y 
   `archivo` debe ser un puntero válido a una estructura `archivo_csv`. */
/* Pos: Permite al usuario seleccionar una opción del menú y ejecuta la acción asociada. */
void interactuar_menu(menu_t *menu, void *contexto,
		      struct archivo_csv *archivo);

/* Pre: El puntero `menu` debe ser un puntero válido a una estructura de tipo `menu_t`, 
   y `accion` debe ser un puntero válido a una estructura de tipo `accion_t`. */
/* Pos: Agrega la acción `accion` al menú `menu`. */
bool menu_agregar_accion(menu_t *menu, accion_t *accion);

/* Pre: El puntero `Accion` debe ser un puntero válido a una estructura de tipo `accion_t`. */
/* Pos: Libera la memoria de la acción `Accion`. */
void destruir_accion(accion_t *Accion);

/* Pre: El puntero `menu` debe ser un puntero válido a una estructura de tipo `menu_t`. */
/* Pos: Libera los recursos utilizados por el menú `menu`. */
void destruir_menu(menu_t *menu);

#endif // MENU_H
