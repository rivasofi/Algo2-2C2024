#include "pa2m.h"
#include "src/hash.h"
#include "string.h"

/*Funcion comparadora pruebas*/

bool tieneMenosDeCincoLetras(char *clave, void *valor, void *ctx)
{
	return strlen(clave) <= 5;
}

bool siempre_verdadero(char *clave, void *valor, void *ctx)
{
	return true;
}

void hashSeCreaVacio()
{
	hash_t *hash = hash_crear(0);
	pa2m_afirmar(hash != NULL, "Puedo crear un hash vacio");
	pa2m_afirmar(hash_cantidad(hash) == 0,
		     "El hash vacio tiene 0 elementos");
	hash_destruir(hash);
}

void hashCrearConCapacidadEspecifica()
{
	hash_t *hash = hash_crear(10);
	pa2m_afirmar(hash != NULL,
		     "Puedo crear un hash con capacidad inicial específica");
	pa2m_afirmar(hash_cantidad(hash) == 0,
		     "El hash recién creado tiene 0 elementos");
	hash_destruir(hash);
}

void hashCrearConCapacidadCero()
{
	hash_t *hash = hash_crear(0);
	pa2m_afirmar(
		hash != NULL,
		"Puedo crear un hash con capacidad inicial de 0 (se ajusta internamente)");
	pa2m_afirmar(hash_cantidad(hash) == 0,
		     "El hash creado con capacidad de 0 tiene 0 elementos");
	hash_destruir(hash);
}

void hashInsertarElemento()
{
	hash_t *hash = hash_crear(0);
	char *clave = "clave";
	char *valor = "valor";
	void *encontrado = NULL;
	pa2m_afirmar(hash_insertar(hash, clave, valor, &encontrado),
		     "Puedo insertar un elemento en el hash");
	hash_destruir(hash);
}

void insertarClaveNulaEnHash()
{
	hash_t *hash = hash_crear(0);
	char *clave = NULL;
	char *valor = "valor";
	void *encontrado = NULL;
	pa2m_afirmar(!hash_insertar(hash, clave, valor, &encontrado),
		     "No puedo insertar una clave nula en el hash");
	hash_destruir(hash);
}

void insertarElementoConClaveVacia()
{
	hash_t *hash = hash_crear(0);
	char *clave = "";
	char *valor = "valor";
	void *encontrado = NULL;
	pa2m_afirmar(hash_insertar(hash, clave, valor, &encontrado),
		     "Puedo insertar un elemento con clave vacía en el hash");
	hash_destruir(hash);
}

void insertarElementoDuplicadoEnHash()
{
	hash_t *hash = hash_crear(0);
	char *clave = "clave";
	char *valor1 = "valor1";
	char *valor2 = "valor2";
	void *encontrado = NULL;

	pa2m_afirmar(hash_insertar(hash, clave, valor1, &encontrado),
		     "Puedo insertar un elemento en el hash");
	pa2m_afirmar(
		hash_insertar(hash, clave, valor2, &encontrado),
		"Puedo insertar un elemento con clave existente y reemplazar el valor");
	pa2m_afirmar(
		encontrado == valor1,
		"El valor antiguo se devuelve al insertar clave existente");

	hash_destruir(hash);
}

void insertarVariosElementosEnHash()
{
	hash_t *hash = hash_crear(0);
	char *clave1 = "clave1";
	char *valor1 = "valor1";
	char *clave2 = "clave2";
	char *valor2 = "valor2";
	char *clave3 = "clave3";
	char *valor3 = "valor3";
	void *encontrado = NULL;

	pa2m_afirmar(hash_insertar(hash, clave1, valor1, &encontrado),
		     "Puedo insertar el primer elemento en el hash");
	pa2m_afirmar(hash_insertar(hash, clave2, valor2, &encontrado),
		     "Puedo insertar el segundo elemento en el hash");
	pa2m_afirmar(hash_insertar(hash, clave3, valor3, &encontrado),
		     "Puedo insertar el tercer elemento en el hash");

	pa2m_afirmar(hash_cantidad(hash) == 3,
		     "La cantidad de elementos en el hash es correcta");

	hash_destruir(hash);
}

void insertarElementoConValorNulo()
{
	hash_t *hash = hash_crear(0);
	char *clave = "clave";
	void *valor = NULL;
	void *encontrado = NULL;

	pa2m_afirmar(hash_insertar(hash, clave, valor, &encontrado),
		     "Puedo insertar un elemento con valor nulo en el hash");

	hash_destruir(hash);
}

void insertarElementoEnHashLleno()
{
	hash_t *hash = hash_crear(1);
	char *clave1 = "clave1";
	char *valor1 = "valor1";
	char *clave2 = "clave2";
	char *valor2 = "valor2";
	void *encontrado = NULL;

	pa2m_afirmar(
		hash_insertar(hash, clave1, valor1, &encontrado),
		"Puedo insertar un elemento en un hash con capacidad inicial pequeña");
	pa2m_afirmar(
		hash_insertar(hash, clave2, valor2, &encontrado),
		"Puedo insertar un segundo elemento que hace que deba redimensionarse el hash");

	hash_destruir(hash);
}

void redimensionamientoDelHashCuandoEstaLleno()
{
	hash_t *hash = hash_crear(2);
	char *clave1 = "clave1";
	char *valor1 = "valor1";
	char *clave2 = "clave2";
	char *valor2 = "valor2";
	char *clave3 = "clave3";
	char *valor3 = "valor3";

	hash_insertar(hash, clave1, valor1, NULL);
	hash_insertar(hash, clave2, valor2, NULL);

	pa2m_afirmar(
		hash_insertar(hash, clave3, valor3, NULL),
		"El hash se redimensiona al insertar más elementos que su capacidad inicial");

	pa2m_afirmar(
		hash_contiene(hash, clave1),
		"La clave1 sigue estando presente después de redimensionar");
	pa2m_afirmar(hash_buscar(hash, clave1) == valor1,
		     "El valor asociado a clave1 sigue siendo correcto");

	hash_destruir(hash);
}

void redimensionamientoNoAfectaElementosExistentes()
{
	hash_t *hash = hash_crear(1);
	char *clave = "clave";
	char *valor = "valor";

	hash_insertar(hash, clave, valor, NULL);
	pa2m_afirmar(hash_contiene(hash, clave),
		     "El elemento sigue en el hash después de la redimensión");
	pa2m_afirmar(
		hash_buscar(hash, clave) == valor,
		"El valor asociado sigue correcto después de la redimensión");

	hash_destruir(hash);
}

void redimensionamientoYEliminacion()
{
	hash_t *hash = hash_crear(2);
	char *clave1 = "clave1";
	char *valor1 = "valor1";
	char *clave2 = "clave2";
	char *valor2 = "valor2";

	hash_insertar(hash, clave1, valor1, NULL);
	hash_insertar(hash, clave2, valor2, NULL);
	hash_quitar(hash, clave1);

	pa2m_afirmar(
		!hash_contiene(hash, clave1),
		"La clave1 no está presente después de eliminarla tras la redimensión");
	pa2m_afirmar(
		hash_contiene(hash, clave2),
		"La clave2 sigue presente después de la redimensión y eliminación de clave1");

	hash_destruir(hash);
}

void cantidadElementosEnHashVacio()
{
	hash_t *hash = hash_crear(0);
	pa2m_afirmar(hash_cantidad(hash) == 0,
		     "La cantidad de elementos en un hash vacío es 0");
	hash_destruir(hash);
}

void cantidadElementosDespuesDeInsertar()
{
	hash_t *hash = hash_crear(0);
	char *clave1 = "clave1";
	char *valor1 = "valor1";
	char *clave2 = "clave2";
	char *valor2 = "valor2";

	hash_insertar(hash, clave1, valor1, NULL);
	hash_insertar(hash, clave2, valor2, NULL);

	pa2m_afirmar(
		hash_cantidad(hash) == 2,
		"La cantidad de elementos es correcta después de insertar dos elementos");
	hash_destruir(hash);
}

void cantidadElementosDespuesDeEliminar()
{
	hash_t *hash = hash_crear(0);
	char *clave1 = "clave1";
	char *valor1 = "valor1";
	char *clave2 = "clave2";
	char *valor2 = "valor2";

	hash_insertar(hash, clave1, valor1, NULL);
	hash_insertar(hash, clave2, valor2, NULL);
	hash_quitar(hash, clave1);

	pa2m_afirmar(
		hash_cantidad(hash) == 1,
		"La cantidad de elementos es correcta después de eliminar un elemento");

	hash_destruir(hash);
}

void cantidadElementosTrasInsertarMismaClave()
{
	hash_t *hash = hash_crear(0);
	char *clave = "clave";
	char *valor1 = "valor1";
	char *valor2 = "valor2";

	hash_insertar(hash, clave, valor1, NULL);
	hash_insertar(hash, clave, valor2, NULL);

	pa2m_afirmar(
		hash_cantidad(hash) == 1,
		"La cantidad de elementos sigue siendo 1 al insertar una clave existente");

	hash_destruir(hash);
}

void buscarElementoEnHashVacio()
{
	hash_t *hash = hash_crear(0);
	char *clave = "clave";
	pa2m_afirmar(!hash_contiene(hash, clave),
		     "No se encuentra la clave en un hash vacio");
	pa2m_afirmar(
		hash_buscar(hash, clave) == NULL,
		"No se encontro ningun valor asociado a la clave en un hash vacio");
	hash_destruir(hash);
}

void buscarElementoExistenteEnHash()
{
	hash_t *hash = hash_crear(0);
	char *clave = "clave";
	char *valor = "valor";
	hash_insertar(hash, clave, valor, NULL);
	pa2m_afirmar(hash_contiene(hash, clave),
		     "Se encuentra la clave en el hash");
	pa2m_afirmar(hash_buscar(hash, clave) == valor,
		     "Se encontro el valor asociado a la clave");
	hash_destruir(hash);
}

void buscarElementoInexistenteEnHash()
{
	hash_t *hash = hash_crear(0);
	char *clave = "clave";
	char *valor = "valor";
	hash_insertar(hash, clave, valor, NULL);
	pa2m_afirmar(
		!hash_contiene(hash, "clave2"),
		"Buscando elemento inexistente no se encuentra la clave en el hash");
	pa2m_afirmar(
		hash_buscar(hash, "clave2") == NULL,
		"Buscando elemento inexistente no se encontro ningun valor asociado a la clave");
	hash_destruir(hash);
}

void buscarElementoDespuesDeEliminar()
{
	hash_t *hash = hash_crear(0);
	char *clave = "clave";
	char *valor = "valor";
	hash_insertar(hash, clave, valor, NULL);
	hash_quitar(hash, clave);

	pa2m_afirmar(!hash_contiene(hash, clave),
		     "La clave eliminada ya no se encuentra en el hash");
	pa2m_afirmar(
		hash_buscar(hash, clave) == NULL,
		"El valor asociado a la clave eliminada no se encuentra en el hash");

	hash_destruir(hash);
}

void buscarElementoConClavesSimilares()
{
	hash_t *hash = hash_crear(0);
	char *clave1 = "clave";
	char *valor1 = "valor1";
	char *clave2 = "clave_";
	char *valor2 = "valor2";

	hash_insertar(hash, clave1, valor1, NULL);
	hash_insertar(hash, clave2, valor2, NULL);

	pa2m_afirmar(hash_contiene(hash, clave1),
		     "Se encuentra la clave1 en el hash");
	pa2m_afirmar(hash_buscar(hash, clave1) == valor1,
		     "Se encontró el valor asociado a la clave1");

	pa2m_afirmar(hash_contiene(hash, clave2),
		     "Se encuentra la clave2 en el hash");
	pa2m_afirmar(hash_buscar(hash, clave2) == valor2,
		     "Se encontró el valor asociado a la clave2");

	hash_destruir(hash);
}

void buscarElementoDespuesDeInsertarMultiples()
{
	hash_t *hash = hash_crear(0);
	char *clave1 = "clave1";
	char *valor1 = "valor1";
	char *clave2 = "clave2";
	char *valor2 = "valor2";
	char *clave3 = "clave3";
	char *valor3 = "valor3";

	hash_insertar(hash, clave1, valor1, NULL);
	hash_insertar(hash, clave2, valor2, NULL);
	hash_insertar(hash, clave3, valor3, NULL);

	pa2m_afirmar(hash_contiene(hash, clave2),
		     "Se encuentra la clave2 en el hash");
	pa2m_afirmar(hash_buscar(hash, clave2) == valor2,
		     "Se encontró el valor asociado a la clave2");

	hash_destruir(hash);
}

void buscarEnHashConRehash()
{
	hash_t *hash = hash_crear(1);
	char *clave1 = "clave1";
	char *valor1 = "valor1";
	char *clave2 = "clave2";
	char *valor2 = "valor2";
	char *clave3 = "clave3";
	char *valor3 = "valor3";

	hash_insertar(hash, clave1, valor1, NULL);
	hash_insertar(hash, clave2, valor2, NULL);
	hash_insertar(hash, clave3, valor3, NULL);

	pa2m_afirmar(hash_contiene(hash, clave3),
		     "Se encuentra la clave3 después del rehash");
	pa2m_afirmar(
		hash_buscar(hash, clave3) == valor3,
		"Se encontró el valor asociado a la clave3 después del rehash");

	hash_destruir(hash);
}

void buscarElementoEnHashGrande()
{
	hash_t *hash = hash_crear(0);
	char clave[100];
	char *valor = "valor";
	int cantidad = 1000;

	for (int i = 0; i < cantidad; i++) {
		snprintf(clave, sizeof(clave), "clave%d", i);
		hash_insertar(hash, clave, valor, NULL);
	}

	snprintf(clave, sizeof(clave), "clave500");
	pa2m_afirmar(hash_contiene(hash, clave),
		     "Se encuentra una clave en un hash grande");
	pa2m_afirmar(
		hash_buscar(hash, clave) == valor,
		"Se encontró el valor asociado a una clave en un hash grande");

	hash_destruir(hash);
}

void hashNoContieneElementoEnHashVacio()
{
	hash_t *hash = hash_crear(0);
	char *clave = "clave";

	pa2m_afirmar(!hash_contiene(hash, clave),
		     "No se encuentra la clave en un hash vacío");

	hash_destruir(hash);
}

void hashContieneElementoExistente()
{
	hash_t *hash = hash_crear(0);
	char *clave = "clave";
	char *valor = "valor";

	hash_insertar(hash, clave, valor, NULL);

	pa2m_afirmar(hash_contiene(hash, clave),
		     "Se encuentra la clave en el hash después de insertar");

	hash_destruir(hash);
}

void hashNoContieneElementoInexistente()
{
	hash_t *hash = hash_crear(0);
	char *clave = "clave";
	char *valor = "valor";
	char *clave_inexistente = "clave_inexistente";

	hash_insertar(hash, clave, valor, NULL);

	pa2m_afirmar(
		!hash_contiene(hash, clave_inexistente),
		"No se encuentra una clave que no fue insertada en el hash");

	hash_destruir(hash);
}

void hashNoContieneDespuesDeEliminar()
{
	hash_t *hash = hash_crear(0);
	char *clave = "clave";
	char *valor = "valor";

	hash_insertar(hash, clave, valor, NULL);
	hash_quitar(hash, clave);

	pa2m_afirmar(
		!hash_contiene(hash, clave),
		"La clave no se encuentra en el hash después de eliminarla");

	hash_destruir(hash);
}

void hashContieneConClaveNula()
{
	hash_t *hash = hash_crear(0);

	pa2m_afirmar(!hash_contiene(hash, NULL),
		     "No se puede buscar una clave nula en el hash");

	hash_destruir(hash);
}

void quitarElementoEnHashVacio()
{
	hash_t *hash = hash_crear(0);
	char *clave = "clave";
	pa2m_afirmar(hash_quitar(hash, clave) == NULL,
		     "No se puede quitar un elemento de un hash vacio");
	hash_destruir(hash);
}

void quitarElementoInexistenteEnHash()
{
	hash_t *hash = hash_crear(0);
	char *clave = "clave";
	char *valor = "valor";
	hash_insertar(hash, clave, valor, NULL);
	pa2m_afirmar(hash_quitar(hash, "clave2") == NULL,
		     "No se puede quitar un elemento inexistente en el hash");
	hash_destruir(hash);
}

void quitarElementoExistenteEnHash()
{
	hash_t *hash = hash_crear(0);
	char *clave = "clave";
	char *valor = "valor";
	hash_insertar(hash, clave, valor, NULL);
	pa2m_afirmar(hash_quitar(hash, clave) == valor,
		     "Se puede quitar un elemento existente en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 0, "El hash tiene 0 elementos");
	pa2m_afirmar(!hash_contiene(hash, clave),
		     "El hash no contiene la clave");
	pa2m_afirmar(hash_buscar(hash, clave) == NULL,
		     "No se encontro ningun valor asociado a la clave");
	hash_destruir(hash);
}

void quitarMultiplesElementos()
{
	hash_t *hash = hash_crear(0);
	char *clave1 = "clave1";
	char *valor1 = "valor1";
	char *clave2 = "clave2";
	char *valor2 = "valor2";
	char *clave3 = "clave3";
	char *valor3 = "valor3";

	hash_insertar(hash, clave1, valor1, NULL);
	hash_insertar(hash, clave2, valor2, NULL);
	hash_insertar(hash, clave3, valor3, NULL);

	pa2m_afirmar(hash_quitar(hash, clave2) == valor2,
		     "Se puede quitar un elemento existente en el medio");
	pa2m_afirmar(!hash_contiene(hash, clave2),
		     "El elemento quitado ya no está en el hash");
	pa2m_afirmar(
		hash_cantidad(hash) == 2,
		"La cantidad de elementos en el hash es 2 después de quitar uno");

	hash_destruir(hash);
}

void quitarTodosLosElementos()
{
	hash_t *hash = hash_crear(0);
	char *claves[] = { "clave1", "clave2", "clave3" };
	char *valores[] = { "valor1", "valor2", "valor3" };

	for (int i = 0; i < 3; i++) {
		hash_insertar(hash, claves[i], valores[i], NULL);
	}

	for (int i = 0; i < 3; i++) {
		pa2m_afirmar(hash_quitar(hash, claves[i]) == valores[i],
			     "Se puede quitar un elemento del hash");
	}

	pa2m_afirmar(
		hash_cantidad(hash) == 0,
		"El hash queda vacío después de quitar todos los elementos");

	hash_destruir(hash);
}

void iteroSobreHashVacio()
{
	hash_t *hash = hash_crear(0);
	size_t cantidad = hash_iterar(hash, NULL, NULL);
	pa2m_afirmar(cantidad == 0, "No se itera sobre un hash vacio");
	hash_destruir(hash);
}

void hashConCincoElementosDevuelveCantidadCorrecta()
{
	hash_t *hash = hash_crear(0);
	char *claves[] = { "clave1", "clave2", "clave3", "clave4", "clave5" };
	char *valores[] = { "valor1", "valor2", "valor3", "valor4", "valor5" };
	void *encontrado = NULL;
	for (int i = 0; i < 5; i++) {
		hash_insertar(hash, claves[i], valores[i], &encontrado);
	}
	pa2m_afirmar(
		hash_cantidad(hash) == 5,
		"Se iteró el hash entero si ninguna función devolvió false");
	hash_destruir(hash);
}

void recorroLasPrimerasClaves()
{
	hash_t *hash = hash_crear(0);
	char *claves[] = { "clave1", "clave2", "clave3", "clave4", "clave5" };
	char *valores[] = { "valor1", "valor2", "valor3", "valor4", "valor5" };
	void *encontrado = NULL;
	for (int i = 0; i < 5; i++) {
		hash_insertar(hash, claves[i], valores[i], &encontrado);
	}
	size_t cantidad = hash_iterar(hash, tieneMenosDeCincoLetras, NULL);
	pa2m_afirmar(
		cantidad == 1,
		"Itero sobre 1 elemento si el primer elemento devuelve false");
	hash_destruir(hash);
}

void iterarSinFuncionDeCorte()
{
	hash_t *hash = hash_crear(0);
	char *claves[] = { "clave1", "clave2", "clave3" };
	char *valores[] = { "valor1", "valor2", "valor3" };
	void *encontrado = NULL;
	for (int i = 0; i < 3; i++) {
		hash_insertar(hash, claves[i], valores[i], &encontrado);
	}

	size_t cantidad = hash_iterar(hash, NULL, NULL);
	pa2m_afirmar(cantidad == 0, "No puedo iterar sin función de corte");
	hash_destruir(hash);
}

int main()
{
	pa2m_nuevo_grupo("============== Pruebas de Hash ===============");
	pa2m_nuevo_grupo(
		"============== Pruebas sobre la creación del hash ===============");
	hashSeCreaVacio();
	hashCrearConCapacidadEspecifica();
	hashCrearConCapacidadCero();
	pa2m_nuevo_grupo(
		"============== Pruebas de inserción de elementos ===============");
	hashInsertarElemento();
	insertarClaveNulaEnHash();
	insertarElementoConClaveVacia();
	insertarElementoDuplicadoEnHash();
	insertarVariosElementosEnHash();
	pa2m_nuevo_grupo(
		"============== Pruebas de redimensionamiento del hash ===============");
	redimensionamientoDelHashCuandoEstaLleno();
	redimensionamientoNoAfectaElementosExistentes();
	redimensionamientoYEliminacion();
	pa2m_nuevo_grupo(
		"============== Pruebas de cantidad de elementos ===============");
	cantidadElementosEnHashVacio();
	cantidadElementosDespuesDeInsertar();
	cantidadElementosDespuesDeEliminar();
	cantidadElementosTrasInsertarMismaClave();
	pa2m_nuevo_grupo(
		"============== Pruebas de búsqueda de elementos ===============");
	buscarElementoEnHashVacio();
	buscarElementoExistenteEnHash();
	buscarElementoInexistenteEnHash();
	buscarElementoDespuesDeEliminar();
	buscarElementoConClavesSimilares();
	buscarElementoDespuesDeInsertarMultiples();
	buscarEnHashConRehash();
	buscarElementoEnHashGrande();
	pa2m_nuevo_grupo(
		"============== Pruebas de elementos contenidos ===============");
	hashNoContieneElementoEnHashVacio();
	hashContieneElementoExistente();
	hashNoContieneElementoInexistente();
	hashNoContieneDespuesDeEliminar();
	hashContieneConClaveNula();
	pa2m_nuevo_grupo(
		"============== Pruebas sobre quitar elementos ===============");
	quitarElementoEnHashVacio();
	quitarElementoInexistenteEnHash();
	quitarElementoExistenteEnHash();
	quitarMultiplesElementos();
	quitarTodosLosElementos();
	pa2m_nuevo_grupo(
		"============== Pruebas de iterador interno ===============");
	iteroSobreHashVacio();
	hashConCincoElementosDevuelveCantidadCorrecta();
	recorroLasPrimerasClaves();
	iterarSinFuncionDeCorte();

	return pa2m_mostrar_reporte();
}
