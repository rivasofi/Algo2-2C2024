#ifndef POKEDEX_H
#define POKEDEX_H

#include "abb.h"
#include "csv.h"
#include "pokemon.h"
#include "../extra/ansi.h"

typedef struct Pokedex pokedex_t;

/* Pos: Devuelve un puntero a una nueva pokedex con un árbol de pokemones vacío y cantidad inicializada en 0. */
pokedex_t *crear_pokedex();

/* Pre: El archivo CSV debe ser un puntero válido y contener los datos de los pokemones. */
/* Pos: Carga los pokemones del archivo CSV en el pokedex, insertándolos en el árbol correspondiente. */
void cargar_pokedex(pokedex_t *pokedex, struct archivo_csv *archivo);

/* Pre: La pokedex debe ser un puntero válido. */
/* Pos: Muestra la lista de pokemones de la pokedex recorriendo el árbol. */
void mostrar_pokedex(pokedex_t *pokedex);

/* Pre: La pokedex debe ser un puntero válido. */
/* Pos: Devuelve la cantidad de pokemones en la pokedex. */
size_t obtener_cantidad_pokemones(pokedex_t *pokedex);

/* Pre: La pokedex debe ser un puntero válido. */
/* Pos: Destruye la pokedex y libera la memoria utilizada por el árbol de pokemones. */
void destruir_pokedex(pokedex_t *pokedex);

/* Pre: La pokedex debe ser un puntero válido. */
/* Pos: Devuelve el árbol de pokemones almacenado en la pokedex. */
abb_t *obtener_arbol_pokemones(pokedex_t *pokedex);

#endif // POKEDEX_H