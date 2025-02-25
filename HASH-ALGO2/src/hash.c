#include "hash.h"
#include "hash_aux.h"

#include <stdio.h>
#include <ctype.h>

#define IGUALES 0
#define CAPACIDAD_MINIMA 3
#define CANTIDAD_INICIAL 0
#define FACTOR_CARGA_REHASH 0.75
#define FLAG_BORRADO ((nodo_hash_t *)-1)

hash_t *hash_crear(size_t capacidad_inicial)
{
	if (capacidad_inicial < CAPACIDAD_MINIMA) {
		capacidad_inicial = CAPACIDAD_MINIMA;
	}

	hash_t *hash = malloc(sizeof(hash_t));
	if (!hash) {
		return NULL;
	}

	hash->tabla = inicializar_tabla(capacidad_inicial);
	if (!hash->tabla) {
		free(hash);
		return NULL;
	}

	hash->capacidad = capacidad_inicial;
	hash->cantidad = CANTIDAD_INICIAL;
	return hash;
}

size_t hash_cantidad(hash_t *hash)
{
	if (!hash) {
		return 0;
	}
	return hash->cantidad;
}

bool hash_insertar(hash_t *hash, char *clave, void *valor, void **encontrado)
{
	if (!hash || !clave) {
		return false;
	}

	size_t pos = funcion_hash(clave) % hash->capacidad;
	Lista_iterador *iter = lista_iterador_crear(hash->tabla[pos]);

	while (lista_iterador_hay_siguiente(iter)) {
		nodo_hash_t *nodo =
			lista_iterador_obtener_elemento_actual(iter);
		lista_iterador_avanzar(iter);

		if (nodo && nodo->clave &&
		    strcmp(nodo->clave, clave) == IGUALES) {
			lista_iterador_destruir(iter);
			return actualizar_nodo(nodo, clave, valor, encontrado);
		}
	}

	lista_iterador_destruir(iter);

	nodo_hash_t *nuevo_nodo = crear_nodo(clave, valor);
	if (!nuevo_nodo) {
		return false;
	}

	lista_agregar_al_final(hash->tabla[pos], nuevo_nodo);
	hash->cantidad++;

	double factor_de_carga =
		(double)hash->cantidad / (double)hash->capacidad;
	if (factor_de_carga > FACTOR_CARGA_REHASH) {
		redimensionar_hash(hash);
	}

	if (encontrado) {
		*encontrado = NULL;
	}

	return true;
}

void *hash_buscar(hash_t *hash, char *clave)
{
	if (!hash || !clave) {
		return NULL;
	}

	size_t pos = funcion_hash(clave) % hash->capacidad;
	nodo_hash_t *nodo = buscar_nodo(hash->tabla[pos], clave);

	if (nodo) {
		return nodo->valor;
	} else {
		return NULL;
	}
}

bool hash_contiene(hash_t *hash, char *clave)
{
	if (!hash || !clave) {
		return false;
	}
	return hash_buscar(hash, clave) != NULL;
}

void *hash_quitar(hash_t *hash, char *clave)
{
	if (!hash || !clave) {
		return NULL;
	}

	size_t pos = funcion_hash(clave) % hash->capacidad;
	Lista_iterador *iterador = lista_iterador_crear(hash->tabla[pos]);
	size_t index = 0;

	while (lista_iterador_hay_siguiente(iterador)) {
		nodo_hash_t *nodo =
			lista_iterador_obtener_elemento_actual(iterador);
		if (nodo == NULL) {
			lista_iterador_avanzar(iterador);
			continue;
		}

		if (strcmp(nodo->clave, clave) == 0) {
			void *valor = nodo->valor;

			lista_quitar_elemento(hash->tabla[pos], index, NULL);

			free(nodo->clave);
			free(nodo);

			hash->cantidad--;
			lista_iterador_destruir(iterador);
			return valor;
		}
		index++;
		lista_iterador_avanzar(iterador);
	}

	lista_iterador_destruir(iterador);
	return NULL;
}

size_t hash_iterar(hash_t *hash, bool (*f)(char *, void *, void *), void *ctx)
{
	if (!hash || !f) {
		return 0;
	}

	size_t cantidad = 0;

	for (size_t i = 0; i < hash->capacidad; i++) {
		Lista_iterador *iter = lista_iterador_crear(hash->tabla[i]);
		while (lista_iterador_hay_siguiente(iter)) {
			nodo_hash_t *nodo =
				lista_iterador_obtener_elemento_actual(iter);
			if (nodo == NULL) {
				lista_iterador_avanzar(iter);
				continue;
			}
			cantidad++;
			if (!f(nodo->clave, nodo->valor, ctx)) {
				lista_iterador_destruir(iter);
				return cantidad;
			}
			lista_iterador_avanzar(iter);
		}
		lista_iterador_destruir(iter);
	}

	return cantidad;
}

void hash_destruir(hash_t *hash)
{
	destruir_hash(hash, NULL);
	free(hash);
}

void hash_destruir_todo(hash_t *hash, void (*destructor)(void *))
{
	if (!hash) {
		return;
	}

	destruir_hash(hash, destructor);
	free(hash);
}