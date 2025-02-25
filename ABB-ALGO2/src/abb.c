#include "abb.h"
#include "abb_estructura_privada.h"

#define SALIR 0
#define IGUALES 0

void destruir_nodos_rec(nodo_t *nodo)
{
	if (!nodo)
		return;

	destruir_nodos_rec(nodo->izq);
	destruir_nodos_rec(nodo->der);

	free(nodo);
}

void destruir_nodos_elementos_rec(nodo_t *nodo, void (*destructor)(void *))
{
	if (!nodo)
		return;

	destruir_nodos_elementos_rec(nodo->izq, destructor);
	destruir_nodos_elementos_rec(nodo->der, destructor);

	if (destructor)
		destructor(nodo->elemento);
	free(nodo);
}

void comparar_recursivo(nodo_t *nodo, void *elemento,
			int (*comparador)(void *, void *), void **encontrado)
{
	if (!nodo)
		return;

	if (comparador(elemento, nodo->elemento) == IGUALES) {
		*encontrado = nodo->elemento;
		return;
	}

	if (comparador(elemento, nodo->elemento) < 0)
		comparar_recursivo(nodo->izq, elemento, comparador, encontrado);
	else
		comparar_recursivo(nodo->der, elemento, comparador, encontrado);
}

bool abb_insertar_recursivo(abb_t *abb, nodo_t *nodo, nodo_t *actual)
{
	if (!actual) {
		abb->raiz = nodo;
		abb->nodos++;
		return true;
	}

	if (abb->comparador(nodo->elemento, actual->elemento) < 0) {
		if (!actual->izq) {
			actual->izq = nodo;
			abb->nodos++;
			return true;
		} else {
			return abb_insertar_recursivo(abb, nodo, actual->izq);
		}
	} else {
		if (!actual->der) {
			actual->der = nodo;
			abb->nodos++;
			return true;
		} else {
			return abb_insertar_recursivo(abb, nodo, actual->der);
		}
	}
}

size_t inorden_recursivo(nodo_t *nodo, bool (*f)(void *, void *), void *ctx,
			 bool *detener)
{
	if (!nodo || *detener || !f)
		return SALIR;

	size_t cantidad = inorden_recursivo(nodo->izq, f, ctx, detener);
	if (*detener)
		return cantidad;

	cantidad++;
	if (!f(nodo->elemento, ctx)) {
		*detener = true;
		return cantidad;
	}

	return cantidad + inorden_recursivo(nodo->der, f, ctx, detener);
}

size_t preorden_recursivo(nodo_t *nodo, bool (*f)(void *, void *), void *ctx,
			  bool *detener)
{
	if (!nodo || *detener || !f)
		return SALIR;

	size_t cantidad = 1;
	if (!f(nodo->elemento, ctx)) {
		*detener = true;
		return cantidad;
	}

	cantidad += preorden_recursivo(nodo->izq, f, ctx, detener);
	if (*detener)
		return cantidad;

	return cantidad + preorden_recursivo(nodo->der, f, ctx, detener);
}

size_t postorden_recursivo(nodo_t *nodo, bool (*f)(void *, void *), void *ctx,
			   bool *detener)
{
	if (!nodo || *detener || !f)
		return SALIR;

	size_t cantidad = postorden_recursivo(nodo->izq, f, ctx, detener);
	if (*detener)
		return cantidad;

	cantidad += postorden_recursivo(nodo->der, f, ctx, detener);
	if (*detener)
		return cantidad;

	cantidad++;
	if (!f(nodo->elemento, ctx))
		*detener = true;

	return cantidad;
}

void quitar_nodo_hoja(abb_t *abb, nodo_t *actual, nodo_t *padre)
{
	if (padre) {
		if (padre->izq == actual)
			padre->izq = NULL;
		else
			padre->der = NULL;
	} else {
		abb->raiz = NULL;
	}
	free(actual);
	abb->nodos--;
}

void reemplazar_con_hijo(abb_t *abb, nodo_t *actual, nodo_t *padre)
{
	nodo_t *hijo = actual->izq ? actual->izq : actual->der;
	if (padre) {
		if (padre->izq == actual)
			padre->izq = hijo;
		else
			padre->der = hijo;
	} else {
		abb->raiz = hijo;
	}
	free(actual);
	abb->nodos--;
}

nodo_t *buscar_mayor(nodo_t *nodo, nodo_t **padre)
{
	*padre = nodo;
	nodo_t *actual = nodo->izq;

	while (actual->der) {
		*padre = actual;
		actual = actual->der;
	}
	return actual;
}

void actualizar_nodo(nodo_t *actual, nodo_t *reemplazo, nodo_t *padre_reemplazo)
{
	actual->elemento = reemplazo->elemento;

	if (padre_reemplazo->izq == reemplazo) {
		padre_reemplazo->izq = reemplazo->izq;
	} else {
		padre_reemplazo->der = reemplazo->izq;
	}
	free(reemplazo);
}

bool quitar_recursivo(abb_t *abb, nodo_t *actual, nodo_t *padre, void *buscado,
		      void **encontrado)
{
	if (!actual) {
		return false;
	}

	int comparacion = abb->comparador(buscado, actual->elemento);

	if (comparacion == IGUALES) {
		if (encontrado) {
			*encontrado = actual->elemento;
		}

		if (!actual->izq && !actual->der) {
			quitar_nodo_hoja(abb, actual, padre);
			return true;
		}

		if (!actual->izq || !actual->der) {
			reemplazar_con_hijo(abb, actual, padre);
			return true;
		}

		nodo_t *padre_reemplazo;
		nodo_t *reemplazo = buscar_mayor(actual, &padre_reemplazo);

		actualizar_nodo(actual, reemplazo, padre_reemplazo);

		abb->nodos--;
		return true;
	} else if (comparacion < 0) {
		return quitar_recursivo(abb, actual->izq, actual, buscado,
					encontrado);
	} else {
		return quitar_recursivo(abb, actual->der, actual, buscado,
					encontrado);
	}
}

size_t vectorizar_inorden_rec(nodo_t *nodo, void **vector, size_t tamaño,
			      size_t *cantidad)
{
	if (!nodo || *cantidad >= tamaño)
		return SALIR;

	vectorizar_inorden_rec(nodo->izq, vector, tamaño, cantidad);

	if (*cantidad < tamaño)
		vector[(*cantidad)++] = nodo->elemento;

	vectorizar_inorden_rec(nodo->der, vector, tamaño, cantidad);

	return *cantidad;
}

size_t vectorizar_preorden_rec(nodo_t *nodo, void **vector, size_t tamaño,
			       size_t *cantidad)
{
	if (!nodo || *cantidad >= tamaño)
		return SALIR;

	if (*cantidad < tamaño)
		vector[(*cantidad)++] = nodo->elemento;

	vectorizar_preorden_rec(nodo->izq, vector, tamaño, cantidad);
	vectorizar_preorden_rec(nodo->der, vector, tamaño, cantidad);

	return *cantidad;
}

size_t vectorizar_postorden_rec(nodo_t *nodo, void **vector, size_t tamaño,
				size_t *cantidad)
{
	if (!nodo || *cantidad >= tamaño)
		return SALIR;

	vectorizar_postorden_rec(nodo->izq, vector, tamaño, cantidad);
	vectorizar_postorden_rec(nodo->der, vector, tamaño, cantidad);

	if (*cantidad < tamaño)
		vector[(*cantidad)++] = nodo->elemento;

	return *cantidad;
}

abb_t *abb_crear(int (*comparador)(void *, void *))
{
	if (!comparador)
		return NULL;
	abb_t *abb = malloc(sizeof(abb_t));
	if (!abb)
		return NULL;
	abb->nodos = 0;
	abb->raiz = NULL;
	abb->comparador = comparador;
	return abb;
}

void abb_destruir(abb_t *abb)
{
	if (!abb)
		return;

	destruir_nodos_rec(abb->raiz);

	free(abb);
}

void abb_destruir_todo(abb_t *abb, void (*destructor)(void *))
{
	if (!abb)
		return;

	destruir_nodos_elementos_rec(abb->raiz, destructor);
	free(abb);
}

bool abb_insertar(abb_t *abb, void *elemento)
{
	if (!abb)
		return false;

	nodo_t *nodo = malloc(sizeof(nodo_t));
	if (!nodo)
		return false;

	nodo->elemento = elemento;
	nodo->izq = NULL;
	nodo->der = NULL;

	if (!abb->raiz) {
		abb->raiz = nodo;
		abb->nodos++;
		return true;
	}

	nodo_t *actual = abb->raiz;
	return abb_insertar_recursivo(abb, nodo, actual);
}

bool abb_quitar(abb_t *abb, void *buscado, void **encontrado)
{
	if (!abb || !abb->raiz)
		return false;

	return quitar_recursivo(abb, abb->raiz, NULL, buscado, encontrado);
}

void *abb_obtener(abb_t *abb, void *elemento)
{
	if (!abb || !abb->raiz)
		return NULL;

	nodo_t *actual = abb->raiz;
	void *encontrado = NULL;
	comparar_recursivo(actual, elemento, abb->comparador, &encontrado);
	return encontrado;
}

size_t abb_cantidad(abb_t *abb)
{
	if (!abb)
		return SALIR;

	return abb->nodos;
}

size_t abb_iterar_inorden(abb_t *abb, bool (*f)(void *, void *), void *ctx)
{
	if (!abb || !abb->raiz)
		return SALIR;

	bool detener = false;
	return inorden_recursivo(abb->raiz, f, ctx, &detener);
}

size_t abb_iterar_preorden(abb_t *abb, bool (*f)(void *, void *), void *ctx)
{
	if (!abb || !abb->raiz)
		return SALIR;

	bool detener = false;
	return preorden_recursivo(abb->raiz, f, ctx, &detener);
}

size_t abb_iterar_postorden(abb_t *abb, bool (*f)(void *, void *), void *ctx)
{
	if (!abb || !abb->raiz)
		return SALIR;

	bool detener = false;
	return postorden_recursivo(abb->raiz, f, ctx, &detener);
}

size_t abb_vectorizar_inorden(abb_t *abb, void **vector, size_t tamaño)
{
	if (!abb || !abb->raiz)
		return SALIR;

	size_t cantidad = 0;
	return vectorizar_inorden_rec(abb->raiz, vector, tamaño, &cantidad);
}

size_t abb_vectorizar_preorden(abb_t *abb, void **vector, size_t tamaño)
{
	if (!abb || !abb->raiz)
		return SALIR;

	size_t cantidad = 0;
	return vectorizar_preorden_rec(abb->raiz, vector, tamaño, &cantidad);
}

size_t abb_vectorizar_postorden(abb_t *abb, void **vector, size_t tamaño)
{
	if (!abb || !abb->raiz)
		return SALIR;

	size_t cantidad = 0;
	return vectorizar_postorden_rec(abb->raiz, vector, tamaño, &cantidad);
}