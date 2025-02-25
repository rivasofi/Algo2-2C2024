#include "hash_aux.h"

#define SEMILLA_HASH_DJB2 5381
#define DESPLAZAMIENTO_HASH_DJB2 5
#define DOBLE 2
#define SON_IGUALES 0

size_t funcion_hash(const char *clave)
{
	size_t hash = SEMILLA_HASH_DJB2;
	unsigned char c;

	while ((c = (unsigned char)*clave++))
		hash = ((hash << DESPLAZAMIENTO_HASH_DJB2) + hash) + c;

	return hash;
}

void redimensionar_hash(hash_t *hash)
{
	if (hash->cantidad < hash->capacidad) {
		return;
	}

	size_t nueva_capacidad = hash->capacidad * DOBLE;
	Lista **nueva_tabla = malloc(sizeof(Lista *) * nueva_capacidad);
	if (!nueva_tabla) {
		return;
	}

	for (size_t i = 0; i < nueva_capacidad; i++) {
		nueva_tabla[i] = lista_crear();
		if (!nueva_tabla[i]) {
			for (size_t j = 0; j < i; j++) {
				lista_destruir(nueva_tabla[j]);
			}
			free(nueva_tabla);
			return;
		}
	}

	for (size_t i = 0; i < hash->capacidad; i++) {
		Lista_iterador *iter = lista_iterador_crear(hash->tabla[i]);
		while (lista_iterador_hay_siguiente(iter)) {
			nodo_hash_t *nodo =
				lista_iterador_obtener_elemento_actual(iter);
			if (nodo == NULL || nodo->clave == NULL) {
				lista_iterador_avanzar(iter);
				continue;
			}

			size_t pos =
				funcion_hash(nodo->clave) % nueva_capacidad;
			lista_agregar_al_final(nueva_tabla[pos], nodo);
			lista_iterador_avanzar(iter);
		}
		lista_iterador_destruir(iter);
		lista_destruir(hash->tabla[i]);
	}

	free(hash->tabla);
	hash->tabla = nueva_tabla;
	hash->capacidad = nueva_capacidad;
}

Lista **inicializar_tabla(size_t capacidad)
{
	Lista **tabla = malloc(sizeof(Lista *) * capacidad);
	if (!tabla) {
		return NULL;
	}
	for (size_t i = 0; i < capacidad; i++) {
		tabla[i] = lista_crear();
		if (!tabla[i]) {
			for (size_t j = 0; j < i; j++) {
				lista_destruir(tabla[j]);
			}
			free(tabla);
			return NULL;
		}
	}
	return tabla;
}

nodo_hash_t *crear_nodo(const char *clave, void *valor)
{
	nodo_hash_t *nodo = malloc(sizeof(nodo_hash_t));
	if (!nodo) {
		return NULL;
	}
	nodo->clave = malloc(strlen(clave) + 1);
	if (!nodo->clave) {
		free(nodo);
		return NULL;
	}
	strcpy(nodo->clave, clave);
	nodo->valor = valor;
	return nodo;
}

bool actualizar_nodo(nodo_hash_t *nodo, const char *clave, void *valor,
		     void **encontrado)
{
	if (encontrado) {
		*encontrado = nodo->valor;
	}
	free(nodo->clave);
	nodo->clave = malloc(strlen(clave) + 1);
	if (!nodo->clave) {
		return false;
	}
	strcpy(nodo->clave, clave);
	nodo->valor = valor;
	return true;
}

nodo_hash_t *buscar_nodo(Lista *lista, const char *clave)
{
	Lista_iterador *iter = lista_iterador_crear(lista);
	if (!iter) {
		return NULL;
	}

	while (lista_iterador_hay_siguiente(iter)) {
		nodo_hash_t *nodo =
			lista_iterador_obtener_elemento_actual(iter);
		if (nodo && strcmp(nodo->clave, clave) == SON_IGUALES) {
			lista_iterador_destruir(iter);
			return nodo;
		}
		lista_iterador_avanzar(iter);
	}

	lista_iterador_destruir(iter);
	return NULL;
}

void destruir_nodos_lista(Lista *lista, void (*destructor)(void *))
{
	Lista_iterador *iter = lista_iterador_crear(lista);
	while (lista_iterador_hay_siguiente(iter)) {
		nodo_hash_t *nodo =
			lista_iterador_obtener_elemento_actual(iter);

		if (nodo) {
			if (nodo->clave) {
				free(nodo->clave);
			}

			if (destructor) {
				destructor(nodo->valor);
			}

			free(nodo);
		}

		lista_iterador_avanzar(iter);
	}

	lista_iterador_destruir(iter);
}

void destruir_hash(hash_t *hash, void (*destructor)(void *))
{
	if (!hash || !hash->tabla) {
		return;
	}

	for (size_t i = 0; i < hash->capacidad; i++) {
		destruir_nodos_lista(hash->tabla[i], destructor);
		lista_destruir(hash->tabla[i]);
	}

	free(hash->tabla);
}
