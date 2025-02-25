#include "pa2m.h"
#include "src/lista.h"
#include "src/cola.h"
#include "src/pila.h"

int comparador_enteros(void *a, void *b)
{
	int *int_a = (int *)a;
	int *int_b = (int *)b;
	return (*int_a - *int_b);
}

bool callback(void *elemento, void *ctx)
{
	return true;
}

/*PRUEBAS LISTA*/

void seCreaLista()
{
	Lista *lista = lista_crear();
	pa2m_afirmar(lista != NULL, "Puedo crear una lista");
	lista_destruir(lista);
}

void seAgregaElemento()
{
	Lista *lista = lista_crear();
	int elemento = 5;
	pa2m_afirmar(lista_agregar_elemento(lista, 0, &elemento),
		     "Puedo agregar un elemento a la lista");
	lista_destruir(lista);
}

void seAgregaElementoAlFinal()
{
	Lista *lista = lista_crear();
	int elemento = 5;
	pa2m_afirmar(lista_agregar_al_final(lista, &elemento),
		     "Puedo agregar un elemento al final de la lista");
	lista_destruir(lista);
}

void seAgregaEnPosicionEspecifica()
{
	Lista *lista = lista_crear();
	int elemento = 5;
	pa2m_afirmar(lista_agregar_elemento(lista, 0, &elemento),
		     "Puedo agregar un elemento en una posicion especifica");
	lista_destruir(lista);
}

void seAgregaEnPosicionNegativa()
{
	Lista *lista = lista_crear();
	int elemento = 5;
	pa2m_afirmar(!lista_agregar_elemento(lista, (size_t)-1, &elemento),
		     "No puedo agregar un elemento en una posicion negativa");
	lista_destruir(lista);
}

void seEncuentraElemento()
{
	Lista *lista = lista_crear();
	int elemento = 5;
	lista_agregar_al_final(lista, &elemento);
	int buscado = 5;
	void *elemento_encontrado =
		lista_buscar_elemento(lista, &buscado, comparador_enteros);
	pa2m_afirmar(elemento_encontrado != NULL,
		     "Puedo encontrar un elemento en la lista");
	lista_destruir(lista);
}

void seObtieneElemento()
{
	Lista *lista = lista_crear();
	int elemento = 5;
	lista_agregar_al_final(lista, &elemento);
	void *elemento_obtenido = NULL;
	pa2m_afirmar(lista_obtener_elemento(lista, 0, &elemento_obtenido),
		     "Puedo obtener un elemento de la lista");
	lista_destruir(lista);
}

void buscarEnListaVacia()
{
	Lista *lista = lista_crear();
	int buscado = 5;
	void *elemento_encontrado =
		lista_buscar_elemento(lista, &buscado, comparador_enteros);
	pa2m_afirmar(
		elemento_encontrado == NULL,
		"Si se busca un elemento en una lista vacia no se encuentra");
	lista_destruir(lista);
}

void seIteraElementos()
{
	Lista *lista = lista_crear();
	int elemento = 5;
	lista_agregar_al_final(lista, &elemento);
	size_t iterados = lista_iterar_elementos(lista, NULL, NULL);
	pa2m_afirmar(iterados == 1, "Puedo iterar los elementos de la lista");
	lista_destruir(lista);
}

void seIteraTresElementos()
{
	Lista *lista = lista_crear();
	int elementos[3] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_agregar_al_final(lista, &elementos[i]);
	}

	size_t iterados = lista_iterar_elementos(lista, callback, NULL);

	pa2m_afirmar(iterados == 3, "Se recorren los 3 elementos de la lista");

	lista_destruir(lista);
}

void seCreaIteradorExterno()
{
	Lista *lista = lista_crear();
	int elemento = 5;
	lista_agregar_al_final(lista, &elemento);
	Lista_iterador *iterador = lista_iterador_crear(lista);
	pa2m_afirmar(iterador != NULL, "Puedo crear un iterador externo");
	lista_destruir(lista);
	lista_iterador_destruir(iterador);
}

void seEliminaElemento()
{
	Lista *lista = lista_crear();
	int elemento = 5;
	lista_agregar_al_final(lista, &elemento);
	void *elemento_quitado = NULL;
	pa2m_afirmar(lista_quitar_elemento(lista, 0, &elemento_quitado),
		     "Puedo quitar un elemento de la lista");
	lista_destruir(lista);
}

void seELiminaDePosicionEspecifica()
{
	Lista *lista = lista_crear();
	int elementos[3] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_agregar_al_final(lista, &elementos[i]);
	}

	void *elemento_quitado = NULL;
	pa2m_afirmar(lista_quitar_elemento(lista, 1, &elemento_quitado),
		     "Puedo quitar un elemento de una posicion especifica");
	lista_destruir(lista);
}

void siSeELiminaDeListaVaciaNoSeEliminaNada()
{
	Lista *lista = lista_crear();
	void *elemento_quitado = NULL;
	pa2m_afirmar(
		!lista_quitar_elemento(lista, 0, &elemento_quitado),
		"Si se intenta quitar un elemento de una lista vacia no se elimina nada");
	lista_destruir(lista);
}

void seEliminaUnicoElementoQuedaVacia()
{
	Lista *lista = lista_crear();
	int elemento = 5;
	lista_agregar_al_final(lista, &elemento);
	void *elemento_quitado = NULL;
	lista_quitar_elemento(lista, 0, &elemento_quitado);
	size_t cantidad = lista_cantidad_elementos(lista);
	pa2m_afirmar(cantidad == 0,
		     "Si se elimina el unico elemento queda vacia");
	lista_destruir(lista);
}

void siLaListaEstaVaciaLaCantidadEsCero()
{
	Lista *lista = lista_crear();
	size_t cantidad = lista_cantidad_elementos(lista);
	pa2m_afirmar(cantidad == 0,
		     "Si la lista esta vacia la cantidad de elementos es 0");
	lista_destruir(lista);
}

void iterarSobreVaciaDevuelveCero()
{
	Lista *lista = lista_crear();
	size_t iterados = lista_iterar_elementos(lista, NULL, NULL);
	pa2m_afirmar(
		iterados == 0,
		"Si se itera sobre una lista vacia se recorren 0 elementos");
	lista_destruir(lista);
}

void elIteradorExternoAvanza()
{
	Lista *lista = lista_crear();
	int elementos[3] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_agregar_al_final(lista, &elementos[i]);
	}

	Lista_iterador *iterador = lista_iterador_crear(lista);
	pa2m_afirmar(lista_iterador_hay_siguiente(iterador),
		     "El iterador externo tiene siguiente");
	lista_iterador_avanzar(iterador);
	pa2m_afirmar(lista_iterador_hay_siguiente(iterador),
		     "El iterador externo tiene siguiente");
	lista_iterador_avanzar(iterador);
	pa2m_afirmar(lista_iterador_hay_siguiente(iterador),
		     "El iterador externo tiene siguiente");
	lista_iterador_avanzar(iterador);
	pa2m_afirmar(!lista_iterador_hay_siguiente(iterador),
		     "El iterador externo no tiene siguiente");
	lista_destruir(lista);
	lista_iterador_destruir(iterador);
}

/*PRUEBAS PILA*/

void seCreaPila()
{
	Pila *pila = pila_crear();
	pa2m_afirmar(pila != NULL, "Puedo crear una pila");
	pila_destruir(pila);
}

void seAgregaElementoAPila()
{
	Pila *pila = pila_crear();
	int elemento = 5;
	pa2m_afirmar(pila_apilar(pila, &elemento),
		     "Puedo agregar un elemento a la pila");
	pila_destruir(pila);
}

void seApilaNull()
{
	Pila *pila = pila_crear();
	pa2m_afirmar(pila_apilar(pila, NULL),
		     "Puedo agregar un elemento NULL a la pila");
	pila_destruir(pila);
}

void seEncuentraElementoEnPila()
{
	Pila *pila = pila_crear();
	int elemento = 5;
	pila_apilar(pila, &elemento);
	void *elemento_encontrado = pila_tope(pila);
	pa2m_afirmar(elemento_encontrado != NULL,
		     "Puedo encontrar un elemento en la pila");
	pila_destruir(pila);
}

void seObtieneElementoDePila()
{
	Pila *pila = pila_crear();
	int elemento = 5;
	pila_apilar(pila, &elemento);
	void *elemento_obtenido = pila_desapilar(pila);
	pa2m_afirmar(elemento_obtenido != NULL,
		     "Puedo obtener un elemento de la pila");
	pila_destruir(pila);
}

void seIteraElementosDePila()
{
	Pila *pila = pila_crear();
	int elemento = 5;
	pila_apilar(pila, &elemento);
	size_t iterados = pila_cantidad(pila);
	pa2m_afirmar(iterados == 1, "Puedo iterar los elementos de la pila");
	pila_destruir(pila);
}

void seIteraTresElementosDePila()
{
	Pila *pila = pila_crear();
	int elementos[3] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		pila_apilar(pila, &elementos[i]);
	}

	size_t iterados = pila_cantidad(pila);

	pa2m_afirmar(iterados == 3, "Se recorren los 3 elementos de la pila");

	pila_destruir(pila);
}

void desapilarDePilaVacia()
{
	Pila *pila = pila_crear();
	void *elemento = pila_desapilar(pila);
	pa2m_afirmar(
		elemento == NULL,
		"Si se intenta desapilar de una pila vacia no se elimina nada");
	pila_destruir(pila);
}

void seDesapilaHastaVaciar()
{
	Pila *pila = pila_crear();
	int elementos[3] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		pila_apilar(pila, &elementos[i]);
	}

	void *elemento = pila_desapilar(pila);
	elemento = pila_desapilar(pila);
	elemento = pila_desapilar(pila);
	elemento = pila_desapilar(pila);
	pa2m_afirmar(elemento == NULL, "Se vació la pila");
	pila_destruir(pila);
}

void seAgregaYDesapilaElemento()
{
	Pila *pila = pila_crear();
	int elemento = 5;
	pila_apilar(pila, &elemento);
	void *elemento_obtenido = pila_desapilar(pila);
	pa2m_afirmar(elemento_obtenido != NULL,
		     "Puedo agregar y desapilar un elemento de la pila");
	pila_destruir(pila);
}

void seObtieneTopeDePilaVacia()
{
	Pila *pila = pila_crear();
	void *elemento = pila_tope(pila);
	pa2m_afirmar(
		elemento == NULL,
		"Si se intenta obtener el tope de una pila vacia no se obtiene nada");
	pila_destruir(pila);
}

void seEliminaElementoDePila()
{
	Pila *pila = pila_crear();
	int elemento = 5;
	pila_apilar(pila, &elemento);
	void *elemento_quitado = pila_desapilar(pila);
	pa2m_afirmar(elemento_quitado != NULL,
		     "Puedo quitar un elemento de la pila");
	pila_destruir(pila);
}

/*PRUEBAS COLA*/

void seCreaCola()
{
	Cola *cola = cola_crear();
	pa2m_afirmar(cola != NULL, "Puedo crear una cola");
	cola_destruir(cola);
}

void seAgregaElementoACola()
{
	Cola *cola = cola_crear();
	int elemento = 5;
	pa2m_afirmar(cola_encolar(cola, &elemento),
		     "Puedo agregar un elemento a la cola");
	cola_destruir(cola);
}

void seAgregaNullACola()
{
	Cola *cola = cola_crear();
	pa2m_afirmar(cola_encolar(cola, NULL),
		     "Puedo agregar un elemento NULL a la cola");
	cola_destruir(cola);
}

void seEncuentraElementoEnCola()
{
	Cola *cola = cola_crear();
	int elemento = 5;
	cola_encolar(cola, &elemento);
	void *elemento_encontrado = cola_frente(cola);
	pa2m_afirmar(elemento_encontrado != NULL,
		     "Puedo encontrar un elemento en la cola");
	cola_destruir(cola);
}

void seObtieneElementoDeCola()
{
	Cola *cola = cola_crear();
	int elemento = 5;
	cola_encolar(cola, &elemento);
	void *elemento_obtenido = cola_desencolar(cola);
	pa2m_afirmar(elemento_obtenido != NULL,
		     "Puedo obtener un elemento de la cola");
	cola_destruir(cola);
}

void seIteraElementosDeCola()
{
	Cola *cola = cola_crear();
	int elemento = 5;
	cola_encolar(cola, &elemento);
	size_t iterados = cola_cantidad(cola);
	pa2m_afirmar(iterados == 1, "Puedo iterar los elementos de la cola");
	cola_destruir(cola);
}

void seIteraTresElementosDeCola()
{
	Cola *cola = cola_crear();
	int elementos[3] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		cola_encolar(cola, &elementos[i]);
	}

	size_t iterados = cola_cantidad(cola);

	pa2m_afirmar(iterados == 3, "Se recorren los 3 elementos de la cola");

	cola_destruir(cola);
}

void desencolarDeColaVacia()
{
	Cola *cola = cola_crear();
	void *elemento = cola_desencolar(cola);
	pa2m_afirmar(
		elemento == NULL,
		"Si se intenta desencolar de una cola vacia no se elimina nada");
	cola_destruir(cola);
}

void seDesencolaHastaVaciar()
{
	Cola *cola = cola_crear();
	int elementos[3] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		cola_encolar(cola, &elementos[i]);
	}

	void *elemento = cola_desencolar(cola);
	elemento = cola_desencolar(cola);
	elemento = cola_desencolar(cola);
	elemento = cola_desencolar(cola);
	pa2m_afirmar(elemento == NULL, "Se vació la cola");
	cola_destruir(cola);
}

void seObtieneFrenteDeColaVacia()
{
	Cola *cola = cola_crear();
	void *elemento = cola_frente(cola);
	pa2m_afirmar(
		elemento == NULL,
		"Si se intenta obtener el frente de una cola vacia no se obtiene nada");
	cola_destruir(cola);
}

void seAgregaYDesencolaElemento()
{
	Cola *cola = cola_crear();
	int elemento = 5;
	cola_encolar(cola, &elemento);
	void *elemento_obtenido = cola_desencolar(cola);
	pa2m_afirmar(elemento_obtenido != NULL,
		     "Puedo agregar y desencolar un elemento de la cola");
	cola_destruir(cola);
}

void seEliminaElementoDeCola()
{
	Cola *cola = cola_crear();
	int elemento = 5;
	cola_encolar(cola, &elemento);
	void *elemento_quitado = cola_desencolar(cola);
	pa2m_afirmar(elemento_quitado != NULL,
		     "Puedo quitar un elemento de la cola");
	cola_destruir(cola);
}

int main()
{
	pa2m_nuevo_grupo("============== Pruebas de lista ===============");
	seCreaLista();
	siLaListaEstaVaciaLaCantidadEsCero();
	seAgregaElemento();
	seAgregaEnPosicionEspecifica();
	seAgregaElementoAlFinal();
	seAgregaEnPosicionNegativa();
	seEncuentraElemento();
	seObtieneElemento();
	buscarEnListaVacia();
	seIteraElementos();
	seIteraTresElementos();
	seCreaIteradorExterno();
	seEliminaElemento();
	siSeELiminaDeListaVaciaNoSeEliminaNada();
	seEliminaUnicoElementoQuedaVacia();
	seELiminaDePosicionEspecifica();
	iterarSobreVaciaDevuelveCero();
	elIteradorExternoAvanza();

	pa2m_nuevo_grupo("============== Pruebas de pila ===============");
	seCreaPila();
	seApilaNull();
	seAgregaElementoAPila();
	seEncuentraElementoEnPila();
	seObtieneElementoDePila();
	seIteraElementosDePila();
	seIteraTresElementosDePila();
	desapilarDePilaVacia();
	seDesapilaHastaVaciar();
	seAgregaYDesapilaElemento();
	seObtieneTopeDePilaVacia();
	seEliminaElementoDePila();

	pa2m_nuevo_grupo("============== Pruebas de cola ===============");
	seCreaCola();
	seAgregaElementoACola();
	seAgregaNullACola();
	seEncuentraElementoEnCola();
	seObtieneElementoDeCola();
	seIteraElementosDeCola();
	seIteraTresElementosDeCola();
	desencolarDeColaVacia();
	seDesencolaHastaVaciar();
	seObtieneFrenteDeColaVacia();
	seAgregaYDesencolaElemento();
	seEliminaElementoDeCola();

	return pa2m_mostrar_reporte();
}
