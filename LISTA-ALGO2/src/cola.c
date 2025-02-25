#include "cola.h"
#include "lista.h"

struct cola {
	Lista *lista;
};

Cola *cola_crear()
{
	Cola *cola = malloc(sizeof(Cola));
	if (!cola)
		return NULL;

	cola->lista = lista_crear();
	if (!cola->lista) {
		free(cola);
		return NULL;
	}

	return cola;
}

void cola_destruir(Cola *cola)
{
	if (cola) {
		lista_destruir(cola->lista);
		free(cola);
	}
}

void cola_destruir_todo(Cola *cola, void (*f)(void *))
{
	if (cola) {
		lista_destruir_todo(cola->lista, f);
		free(cola);
	}
}

size_t cola_cantidad(Cola *cola)
{
	if (!cola)
		return 0;
	return lista_cantidad_elementos(cola->lista);
}

void *cola_frente(Cola *cola)
{
	if (!cola)
		return NULL;

	void *elemento = NULL;
	lista_obtener_elemento(cola->lista, 0, &elemento);
	return elemento;
}

bool cola_encolar(Cola *cola, void *elemento)
{
	if (!cola)
		return false;
	return lista_agregar_al_final(cola->lista, elemento);
}

void *cola_desencolar(Cola *cola)
{
	void *elemento = NULL;
	if (cola_cantidad(cola) != 0) {
		lista_quitar_elemento(cola->lista, 0, &elemento);
	}
	return elemento;
}

bool cola_esta_vacía(Cola *cola)
{
	if (!cola)
		return true;
	return lista_cantidad_elementos(cola->lista) == 0;
}