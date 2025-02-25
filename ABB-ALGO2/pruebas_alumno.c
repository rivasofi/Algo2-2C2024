#include "pa2m.h"
#include "src/abb.h"
#include <string.h>

int comparador(void *elemento1, void *elemento2)
{
	return strcmp((char *)elemento1, (char *)elemento2);
}

void crearArbol()
{
	abb_t *arbol = abb_crear(comparador);
	pa2m_afirmar(arbol != NULL, "Puedo crear un arbol");
	abb_destruir(arbol);
}

void insertarElemento()
{
	abb_t *arbol = abb_crear(comparador);
	char *elemento = "elemento";
	pa2m_afirmar(abb_insertar(arbol, elemento),
		     "Puedo insertar un elemento");
	abb_destruir(arbol);
}

void buscarElemento()
{
	abb_t *arbol = abb_crear(comparador);
	char *elemento = "elemento";
	abb_insertar(arbol, elemento);
	pa2m_afirmar(abb_obtener(arbol, elemento) == elemento,
		     "Puedo buscar un elemento");
	abb_destruir(arbol);
}

void buscarInexistente()
{
	abb_t *arbol = abb_crear(comparador);
	char *elemento = "elemento";
	abb_insertar(arbol, elemento);
	pa2m_afirmar(abb_obtener(arbol, "elemento2") == NULL,
		     "Buscar un elemento inexistente devuelve NULL");
	abb_destruir(arbol);
}

void quitarDeABB()
{
	abb_t *arbol = abb_crear(comparador);
	char *elemento = "elemento";
	abb_insertar(arbol, elemento);
	void *elemento_quitar = NULL;
	pa2m_afirmar(abb_quitar(arbol, elemento, &elemento_quitar),
		     "Puedo quitar un elemento");
	abb_destruir(arbol);
}

void quitarDeABBVacio()
{
	abb_t *arbol = abb_crear(comparador);
	void *elemento_quitar = NULL;
	pa2m_afirmar(!abb_quitar(arbol, "elemento", &elemento_quitar),
		     "No puedo quitar un elemento de un arbol vacio");
	abb_destruir(arbol);
}

void quitarUnicoNodo()
{
	abb_t *arbol = abb_crear(comparador);
	char *elemento = "elemento";
	abb_insertar(arbol, elemento);
	void *elemento_quitar = NULL;
	pa2m_afirmar(abb_quitar(arbol, elemento, &elemento_quitar),
		     "Puedo quitar el único elemento del ABB");
	pa2m_afirmar(abb_cantidad(arbol) == 0,
		     "El ABB queda vacío tras quitar el único elemento");
	abb_destruir(arbol);
}

void quitarInexistente()
{
	abb_t *arbol = abb_crear(comparador);
	char *elemento = "elemento";
	abb_insertar(arbol, elemento);
	void *elemento_quitar = NULL;
	pa2m_afirmar(!abb_quitar(arbol, "elemento2", &elemento_quitar),
		     "Intentar quitar elemento inexistente devuelve false");
	abb_destruir(arbol);
}

void borrarNodoConDosHijosLoReemplazaConElPredecesorInorden()
{
	abb_t *arbol = abb_crear(comparador);
	char *elemento1 = "elemento1";
	char *elemento2 = "elemento2";
	char *elemento3 = "elemento3";
	abb_insertar(arbol, elemento2);
	abb_insertar(arbol, elemento1);
	abb_insertar(arbol, elemento3);
	void *elemento_quitar = NULL;
	pa2m_afirmar(abb_quitar(arbol, elemento2, &elemento_quitar),
		     "Puedo quitar un nodo con dos hijos");
	abb_destruir(arbol);
}

void cantidadABB()
{
	abb_t *arbol = abb_crear(comparador);
	char *elemento1 = "elemento1";
	char *elemento2 = "elemento2";
	char *elemento3 = "elemento3";
	abb_insertar(arbol, elemento1);
	abb_insertar(arbol, elemento2);
	abb_insertar(arbol, elemento3);
	pa2m_afirmar(abb_cantidad(arbol) == 3,
		     "Puedo contar la cantidad de nodos en el arbol");
	abb_destruir(arbol);
}

// PUNTEROS NULL

void arbolNuloDevuelveCeroElementos()
{
	pa2m_afirmar(abb_cantidad(NULL) == 0,
		     "Un arbol nulo no tiene elementos");
}

void agregarElementoABBNuloDevuelveFalse()
{
	pa2m_afirmar(!abb_insertar(NULL, NULL),
		     "Agregar elemento en ABB nulo devuelve false");
}

void quitarElementoABBNuloDevuelveFalse()
{
	void *elemento = NULL;
	pa2m_afirmar(!abb_quitar(NULL, NULL, &elemento),
		     "Quitar elemento en ABB nulo devuelve false");
}

void obtenerElementoEnArbolNuloDevuelveNULL()
{
	pa2m_afirmar(abb_obtener(NULL, NULL) == NULL,
		     "Buscar en ABB nulo retorna NULL");
}

void recorrerABBNuloDevuelveCeroElementos()
{
	pa2m_afirmar(abb_iterar_inorden(NULL, NULL, NULL) == 0,
		     "Recorrer ABB nulo con inorden devuelve 0 elementos");
	pa2m_afirmar(abb_iterar_preorden(NULL, NULL, NULL) == 0,
		     "Recorrer ABB nulo con preorden devuelve 0 elementos");
	pa2m_afirmar(abb_iterar_postorden(NULL, NULL, NULL) == 0,
		     "Recorrer ABB nulo con postorden devuelve 0 elementos");
}

void vectorizarABBNuloDevuelveCeroElementos()
{
	void *vector[10];
	pa2m_afirmar(abb_vectorizar_inorden(NULL, vector, 10) == 0,
		     "Vectorizar ABB nulo con inorden devuelve 0 elementos");
	pa2m_afirmar(abb_vectorizar_preorden(NULL, vector, 10) == 0,
		     "Vectorizar ABB nulo con preorden devuelve 0 elementos");
	pa2m_afirmar(abb_vectorizar_postorden(NULL, vector, 10) == 0,
		     "Vectorizar ABB nulo con postorden devuelve 0 elementos");
}

void recorrerInorden()
{
	abb_t *arbol = abb_crear(comparador);
	char *elemento1 = "gato";
	char *elemento2 = "perro";
	char *elemento3 = "elefante";
	abb_insertar(arbol, elemento1);
	abb_insertar(arbol, elemento2);
	abb_insertar(arbol, elemento3);

	void *vector_inorden[3];
	size_t cantidad_inorden =
		abb_vectorizar_inorden(arbol, vector_inorden, 3);
	pa2m_afirmar(cantidad_inorden == 3, "Puedo recorrer en inorden");
	pa2m_afirmar(strcmp(vector_inorden[0], "elefante") == 0,
		     "El primer elemento en inorden es correcto");
	pa2m_afirmar(strcmp(vector_inorden[1], "gato") == 0,
		     "El segundo elemento en inorden es correcto");
	pa2m_afirmar(strcmp(vector_inorden[2], "perro") == 0,
		     "El tercer elemento en inorden es correcto");
	abb_destruir(arbol);
}

void recorrerPreorden()
{
	abb_t *arbol = abb_crear(comparador);
	char *elemento1 = "gato";
	char *elemento2 = "perro";
	char *elemento3 = "elefante";
	abb_insertar(arbol, elemento1);
	abb_insertar(arbol, elemento2);
	abb_insertar(arbol, elemento3);

	void *vector_preorden[3];
	size_t cantidad_preorden =
		abb_vectorizar_preorden(arbol, vector_preorden, 3);
	pa2m_afirmar(cantidad_preorden == 3, "Puedo recorrer en preorden");
	pa2m_afirmar(strcmp(vector_preorden[0], "gato") == 0,
		     "El primer elemento en preorden es correcto");
	pa2m_afirmar(strcmp(vector_preorden[1], "elefante") == 0,
		     "El segundo elemento en preorden es correcto");
	pa2m_afirmar(strcmp(vector_preorden[2], "perro") == 0,
		     "El tercer elemento en preorden es correcto");

	abb_destruir(arbol);
}

void recorrerPostorden()
{
	abb_t *arbol = abb_crear(comparador);
	char *elemento1 = "gato";
	char *elemento2 = "perro";
	char *elemento3 = "elefante";
	abb_insertar(arbol, elemento1);
	abb_insertar(arbol, elemento2);
	abb_insertar(arbol, elemento3);

	void *vector_postorden[3];
	size_t cantidad_postorden =
		abb_vectorizar_postorden(arbol, vector_postorden, 3);
	pa2m_afirmar(cantidad_postorden == 3, "Puedo recorrer en postorden");
	pa2m_afirmar(strcmp(vector_postorden[0], "elefante") == 0,
		     "El primer elemento en postorden es correcto");
	pa2m_afirmar(strcmp(vector_postorden[1], "perro") == 0,
		     "El segundo elemento en postorden es correcto");
	pa2m_afirmar(strcmp(vector_postorden[2], "gato") == 0,
		     "El tercer elemento en postorden es correcto");

	abb_destruir(arbol);
}

int main()
{
	pa2m_nuevo_grupo(
		"============== Implementación básica ABB ===============");
	crearArbol();
	insertarElemento();
	buscarElemento();
	buscarInexistente();
	quitarDeABB();
	quitarDeABBVacio();
	quitarUnicoNodo();
	quitarInexistente();
	borrarNodoConDosHijosLoReemplazaConElPredecesorInorden();
	cantidadABB();

	pa2m_nuevo_grupo("============== Pruebas con NULL ===============");
	arbolNuloDevuelveCeroElementos();
	agregarElementoABBNuloDevuelveFalse();
	quitarElementoABBNuloDevuelveFalse();
	obtenerElementoEnArbolNuloDevuelveNULL();
	recorrerABBNuloDevuelveCeroElementos();
	vectorizarABBNuloDevuelveCeroElementos();

	pa2m_nuevo_grupo("============== Iteraciones ===============");
	recorrerInorden();
	recorrerPreorden();
	recorrerPostorden();

	return pa2m_mostrar_reporte();
}