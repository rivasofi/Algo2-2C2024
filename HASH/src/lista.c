#include "lista.h"

struct lista {
	struct nodo *primero;
	struct nodo *ultimo;
	size_t cantidad;
};

struct nodo {
	void *elemento;
	struct nodo *siguiente;
};

struct lista_iterador {
	struct nodo *actual;
};

Lista *lista_crear()
{
	Lista *lista = malloc(sizeof(Lista));
	if (!lista)
		return NULL;
	lista->primero = NULL;
	lista->ultimo = NULL;
	lista->cantidad = 0;
	return lista;
}

void lista_destruir(Lista *lista)
{
	if (!lista)
		return;
	struct nodo *actual = lista->primero;
	while (actual != NULL) {
		struct nodo *siguiente = actual->siguiente;
		free(actual);
		actual = siguiente;
	}
	free(lista);
}

void lista_destruir_todo(Lista *lista, void (*destructor)(void *))
{
	if (!lista)
		return;
	struct nodo *actual = lista->primero;
	while (actual != NULL) {
		struct nodo *siguiente = actual->siguiente;
		if (destructor)
			destructor(actual->elemento);
		free(actual);
		actual = siguiente;
	}
	free(lista);
}

size_t lista_cantidad_elementos(Lista *lista)
{
	if (!lista)
		return 0;
	return lista->cantidad;
}

bool lista_agregar_elemento(Lista *lista, size_t posicion, void *cosa)
{
	if (!lista || posicion > lista->cantidad)
		return false;
	struct nodo *nodo_nuevo = malloc(sizeof(struct nodo));
	if (!nodo_nuevo)
		return false;
	nodo_nuevo->elemento = cosa;
	nodo_nuevo->siguiente = NULL;
	if (posicion == 0) {
		nodo_nuevo->siguiente = lista->primero;
		lista->primero = nodo_nuevo;
		if (lista->cantidad == 0)
			lista->ultimo = nodo_nuevo;
	} else if (posicion == lista->cantidad) {
		lista->ultimo->siguiente = nodo_nuevo;
		lista->ultimo = nodo_nuevo;
	} else {
		struct nodo *anterior = lista->primero;
		for (size_t i = 1; i < posicion; i++) {
			anterior = anterior->siguiente;
		}
		nodo_nuevo->siguiente = anterior->siguiente;
		anterior->siguiente = nodo_nuevo;
	}
	lista->cantidad++;
	return true;
}

bool lista_agregar_al_final(Lista *lista, void *cosa)
{
	if (!lista)
		return false;
	return lista_agregar_elemento(lista, lista->cantidad, cosa);
}

bool lista_quitar_elemento(Lista *lista, size_t posicion,
			   void **elemento_quitado)
{
	if (!lista || posicion >= lista->cantidad)
		return false;

	struct nodo *nodo_quitar;
	if (posicion == 0) {
		nodo_quitar = lista->primero;
		lista->primero = nodo_quitar->siguiente;
		if (lista->cantidad == 1)
			lista->ultimo = NULL;
	} else {
		struct nodo *anterior = lista->primero;
		for (size_t i = 1; i < posicion; i++) {
			anterior = anterior->siguiente;
		}
		nodo_quitar = anterior->siguiente;
		anterior->siguiente = nodo_quitar->siguiente;
		if (posicion == lista->cantidad - 1)
			lista->ultimo = anterior;
	}

	if (elemento_quitado)
		*elemento_quitado = nodo_quitar->elemento;

	free(nodo_quitar);

	lista->cantidad--;
	return true;
}

void *lista_buscar_elemento(Lista *lista, void *buscado,
			    int (*comparador)(void *, void *))
{
	if (!lista || !comparador)
		return NULL;

	struct nodo *actual = lista->primero;
	for (size_t i = 0; i < lista->cantidad; i++) {
		if (comparador(actual->elemento, buscado) == 0)
			return actual->elemento;
		actual = actual->siguiente;
	}

	return NULL;
}

bool lista_obtener_elemento(Lista *lista, size_t posicion,
			    void **elemento_encontrado)
{
	if (!lista || posicion >= lista->cantidad)
		return false;

	struct nodo *actual = lista->primero;
	for (size_t i = 0; i < posicion; i++) {
		actual = actual->siguiente;
	}

	if (elemento_encontrado)
		*elemento_encontrado = actual->elemento;

	return true;
}

size_t lista_iterar_elementos(Lista *lista, bool (*f)(void *, void *),
			      void *ctx)
{
	if (!lista)
		return 0;

	size_t iterados = 0;
	struct nodo *actual = lista->primero;
	while (actual != NULL) {
		if (f && !f(actual->elemento, ctx))
			return iterados + 1;
		actual = actual->siguiente;
		iterados++;
	}

	return iterados;
}

Lista_iterador *lista_iterador_crear(Lista *lista)
{
	if (!lista)
		return NULL;
	Lista_iterador *iterador = malloc(sizeof(Lista_iterador));
	if (!iterador)
		return NULL;
	iterador->actual = lista->primero;
	return iterador;
}

bool lista_iterador_hay_siguiente(Lista_iterador *iterador)
{
	if (!iterador)
		return false;
	return iterador->actual != NULL;
}

void lista_iterador_avanzar(Lista_iterador *iterador)
{
	if (!iterador || !iterador->actual)
		return;
	iterador->actual = iterador->actual->siguiente;
}

void *lista_iterador_obtener_elemento_actual(Lista_iterador *iterador)
{
	if (!iterador || !iterador->actual)
		return NULL;
	return iterador->actual->elemento;
}

void lista_iterador_destruir(Lista_iterador *iterador)
{
	if (iterador)
		free(iterador);
}
