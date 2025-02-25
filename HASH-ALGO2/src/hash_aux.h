#ifndef HASH_AUX_H
#define HASH_AUX_H

#include "lista.h"
#include "hash.h"

#include <stddef.h>
#include <string.h>

struct hash {
	size_t cantidad;
	size_t capacidad;
	Lista **tabla;
};

typedef struct nodo_hash {
	char *clave;
	void *valor;
} nodo_hash_t;

size_t funcion_hash(const char *clave);
void redimensionar_hash(hash_t *hash);
Lista **inicializar_tabla(size_t capacidad);
nodo_hash_t *crear_nodo(const char *clave, void *valor);
bool actualizar_nodo(nodo_hash_t *nodo, const char *clave, void *valor,
		     void **encontrado);
nodo_hash_t *buscar_nodo(Lista *lista, const char *clave);
void destruir_nodos_lista(Lista *lista, void (*destructor)(void *));
void destruir_hash(hash_t *hash, void (*destructor)(void *));

#endif // HASH_AUX_H