#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include "src/lista.h"
#include "src/csv.h"
#include "src/comm_user.h"

const int MAX_NOMBRE_ARCHIVO = 100;
const int PUDO_LEER = 1;
const int COLUMNAS_POKEDEX = 5;
const char CANT_INICIAL = 0;
const char NO_LEYO = 0;
const int BUSCAR_POKEMON = 1;
const int MOSTRAR_POKEMONES = 2;
const char CARACTER_VACIO = '\0';

#define MAX_NOMBRE_POKEMON 50

struct pokemon {
	char *nombre;
	char tipo;
	int fuerza;
	int destreza;
	int resistencia;
};

/* Pos: Vacía el buffer*/

void limpiar_buffer()
{
	while (getchar() != '\n')
		;
}

/* Pre: "str" debe finalizar en '\0'. "ctx" debe ser un ptr válido, no debe ser NULL.*/

/* Pos: Devuelve true si el parseo fue exitoso, caso contrario devuelve false.*/

bool leer_int(const char *str, void *ctx)
{
	return sscanf(str, "%d", (int *)ctx) == PUDO_LEER;
}

/* Pre: "str" debe finalizar en '\0' y ni str ni ctx pueden ser NULL*/

/* Pos: Devuelve true cuando ctx es un ptr a un string que tiene una copia de str. En caso de fallo devuelve false.*/

bool crear_string_nuevo(const char *str, void *ctx)
{
	char *nuevo = malloc(strlen(str) + 1);
	if (nuevo == NULL) {
		return false;
	}
	strcpy(nuevo, str);
	*(char **)ctx = nuevo;
	return true;
}

/* Pre: "str" debe ser un caracter válido. "ctx" debe ser un ptr válido, no debe ser NULL.*/

/* Pos: Devuelve true si el parseo fue exitoso, caso contrario devuelve false.*/

bool leer_caracter(const char *str, void *ctx)
{
	*(char *)ctx = str[0];
	return true;
}

/* Pos: Devuelve true si se pasó el archivo a trabajar como argumento, caso contrario devuelve false.*/

bool se_paso_archivo_argumento(int argc)
{
	return argc >= 2;
}

/* Pre: "separador" no puede ser NULL. */

/* Pos: "separador" contendrá el carácter ingresado por el usuario.*/

void pedir_separador(char *separador)
{
	printf("Ingrese el separador del archivo: ");
	int c = getchar();

	if (c != EOF) {
		*separador = (char)c;
	}
}

/* Pos: Retorna el separador que se utilizará para la lectura del csv */

char seleccionar_separador()
{
	char separador = CARACTER_VACIO;
	pedir_separador(&separador);
	return separador;
}

/* Pre: "separador" no puede ser NULL.*/

/* Pos: Devuelve 's' si se eligió la opción de ingresar un separador, o 'n' si se eligió no hacerlo. */

int obtener_opcion_separador(char *separador)
{
	int opcion_separador = getchar();
	opcion_separador = tolower(opcion_separador);

	while (opcion_separador != 's' && opcion_separador != 'n') {
		limpiar_buffer();
		printf(ROJO "Opción inválida. Reingrese: " RESET);
		opcion_separador = getchar();
		opcion_separador = tolower(opcion_separador);
	}

	if (opcion_separador == 's') {
		limpiar_buffer();
		pedir_separador(separador);
	}

	return opcion_separador;
}

/* Pre: "nombre_archivo" debe ser un array de caracteres que puede almacenar el nombre del archivo.
	   "argc" debe ser mayor o igual a 0 y "argv" no puede ser NULL. */

/* Pos: Si se pasó el archivo como argumento, se copia el nombre del archivo en "nombre_archivo". Sino, da como opción al usuario cerrar el programa o
		pasarlo por terminal.*/

void seleccionar_archivo(char nombre_archivo[], int argc, char *argv[],
			 char separador)
{
	if (se_paso_archivo_argumento(argc)) {
		strcpy(nombre_archivo, argv[1]);
	} else {
		mostrar_no_selecciono_archivo();
		mostrar_opciones_ingreso();
		int ingreso = getchar();
		ingreso = tolower(ingreso);

		while (ingreso != 'e' && ingreso != 'q') {
			limpiar_buffer();
			printf(ROJO "Opción inválida. Reingrese: " RESET);
			ingreso = getchar();
			ingreso = tolower(ingreso);
		}

		if (ingreso == 'e') {
			limpiar_buffer();
			mostrar_seleccionar_archivo();
			mostrar_aclaracion_seleccionar_archivo();
			int resultado_scanf = scanf("%s", nombre_archivo);
			if (resultado_scanf != 1) {
				limpiar_buffer();
			}
			limpiar_buffer();

			mostrar_opcion_seleccionar_separador();
			obtener_opcion_separador(&separador);

		} else if (ingreso == 'q') {
			exit(0);
		}
	}
}

/* Pre: "a" y "b" no pueden ser NULL.*/

/* Pos: Devuelve 0 si los strings son iguales (ignorando mayúsculas y minúsculas),
	   un valor menor que 0 si "a" es menor que "b", y un valor mayor que 0 si "a" es mayor que "b". */

int comparar_case_insensitive(const char *a, const char *b)
{
	while (*a && *b &&
	       tolower((unsigned char)*a) == tolower((unsigned char)*b)) {
		a++;
		b++;
	}
	return tolower((unsigned char)*a) - tolower((unsigned char)*b);
}

/* Pre: "_p1" y "_p2" deben ser punteros no nulos a estructuras "pokemon". 
	   Las estructuras deben tener un campo "nombre" que apunte a una cadena de caracteres válida. */

/* Pos: Devuelve 0 si los strings son iguales (ignorando mayúsculas y minúsculas),
	   un valor menor que 0 si "a" es menor que "b", y un valor mayor que 0 si "a" es mayor que "b". */

int comparar_nombre_pokemon(void *_pokemon1, void *_pokemon2)
{
	struct pokemon *pokemon1 = _pokemon1;
	struct pokemon *pokemon2 = _pokemon2;

	return comparar_case_insensitive(pokemon1->nombre, pokemon2->nombre);
}

/* Pos: Devuelve la opción elegida por el usuario luego de chequear su validez. */

int obtener_opcion_menu()
{
	int opcion;
	int resultado_scanf;

	do {
		resultado_scanf = scanf("%d", &opcion);
	} while (resultado_scanf != 1 ||
		 (opcion != BUSCAR_POKEMON && opcion != MOSTRAR_POKEMONES));

	return opcion;
}

/* Pre: "nombre" no puede ser NULL y debe ser una cadena de caracteres válida. 
	   "tipo" debe ser un char válido. "fuerza", "destreza" y "resistencia" deben ser ints. */

/* Pos: Devuelve un puntero a un struct "pokemon" que contiene los valores proporcionados. 
	   Si ocurre un error al reservar memoria, devuelve NULL. */

struct pokemon *crear_pokemon(const char *nombre, char tipo, int fuerza,
			      int destreza, int resistencia)
{
	struct pokemon *nuevo_pokemon = malloc(sizeof(struct pokemon));
	if (nuevo_pokemon == NULL) {
		fprintf(stderr,
			"Error al reservar memoria para un nuevo pokemon\n");
		return NULL;
	}

	nuevo_pokemon->nombre = malloc(strlen(nombre) + 1);
	if (nuevo_pokemon->nombre == NULL) {
		free(nuevo_pokemon);
		fprintf(stderr,
			"Error al reservar memoria para el nombre del pokemon\n");
		return NULL;
	}
	strcpy(nuevo_pokemon->nombre, nombre);

	nuevo_pokemon->tipo = tipo;
	nuevo_pokemon->fuerza = fuerza;
	nuevo_pokemon->destreza = destreza;
	nuevo_pokemon->resistencia = resistencia;

	return nuevo_pokemon;
}

/* Pre: "archivo" no puede ser NULL y debe apuntar a un archivo CSV válido.
	   "string", "caracter", "fuerza", "destreza" y "resistencia" deben ser punteros válidos donde se almacenarán los datos. */

/* Pos: Devuelve true si se leyeron correctamente todos los datos del pokemon. 
	   Si ocurre un error en la lectura, devuelve false. Los punteros de salida contendrán los valores leídos. */

bool parsear_datos_pokemon(struct archivo_csv *archivo, char **string,
			   char *caracter, int *fuerza, int *destreza,
			   int *resistencia)
{
	bool (*funciones[])(const char *, void *) = { crear_string_nuevo,
						      leer_caracter, leer_int,
						      leer_int, leer_int };
	void *ptrs[] = { string, caracter, fuerza, destreza, resistencia };

	size_t leidos =
		leer_linea_csv(archivo, COLUMNAS_POKEDEX, funciones, ptrs);
	if (leidos == NO_LEYO) {
		return false;
	}
	if (leidos != COLUMNAS_POKEDEX) {
		fprintf(stderr, "Error al leer los datos del pokemon\n");
		return false;
	}
	return true;
}

/* Pre: "pokedex" no puede ser NULL y debe ser un puntero a una lista válida. "string" debe ser una cadena de caracteres válida. "caracter" debe ser un
		carácter válido. "fuerza", "destreza" y "resistencia" deben ser enteros. */

/* Pos: Si se crea el nuevo pokemon correctamente, se agrega a la lista "pokedex". 
	   No se realizan cambios si la creación del pokemon falla. */

void agregar_pokemones_a_lista(Lista *pokedex, char *string, char caracter,
			       int fuerza, int destreza, int resistencia)
{
	struct pokemon *nuevo_pokemon =
		crear_pokemon(string, caracter, fuerza, destreza, resistencia);
	if (nuevo_pokemon != NULL) {
		lista_agregar_al_final(pokedex, nuevo_pokemon);
	}
}

/* Pre: "archivo" no puede ser NULL y debe apuntar a un archivo CSV válido.
	   "pokedex" no puede ser NULL y debe ser un puntero a una lista válida. */

/* Pos: Se agregan los pokemon leídos del archivo CSV a la lista "pokedex". 
	   Se libera la memoria de "string" después de usarla. 
	   Si hay un error en la lectura del archivo, el proceso se detiene. */

void procesar_pokemones(struct archivo_csv *archivo, Lista *pokedex)
{
	char *string = NULL;
	char caracter = CANT_INICIAL;
	int fuerza = CANT_INICIAL;
	int destreza = CANT_INICIAL;
	int resistencia = CANT_INICIAL;

	while (parsear_datos_pokemon(archivo, &string, &caracter, &fuerza,
				     &destreza, &resistencia)) {
		if (string) {
			agregar_pokemones_a_lista(pokedex, string, caracter,
						  fuerza, destreza,
						  resistencia);
			free(string);
		}
	}
}

/* Pre: "pokemon" no puede ser NULL y debe apuntar a un struct "pokemon" válido 
	   con campos inicializados (nombre, tipo, fuerza, destreza, resistencia). */

/* Pos: Imprime los datos del pokemon*/

void imprimir_pokemon(struct pokemon *pokemon)
{
	printf("\t\t\t Nombre: %s ", pokemon->nombre);
	printf("\t\t\t\t Tipo: %c ", pokemon->tipo);
	printf("\t\t\t Fuerza: %d ", pokemon->fuerza);
	printf("\t\t\t Destreza: %d ", pokemon->destreza);
	printf("\t\t\t Resistencia: %d\n\n", pokemon->resistencia);
}

/* Pre: "pokemon" puede ser NULL o debe apuntar a un struct "pokemon" válido que ha sido previamente asignado de forma dinámica. */

/* Pos: Libera la memoria asignada para el nombre del pokemon y para el struct "pokemon". 
	   Si "pokemon" era NULL, no se realiza ninguna acción. */

void liberar_pokemon(struct pokemon *pokemon)
{
	if (pokemon) {
		free(pokemon->nombre);
		free(pokemon);
	}
}

/* Pre: "pokedex" no puede ser NULL y debe apuntar a una lista válida que contenga elementos. */

/* Pos: Imprime los detalles de cada pokemon en la "pokedex". 
	   Si ocurre un error al crear el iterador, se imprime un mensaje de error. */

void imprimir_pokemones(Lista *pokedex)
{
	Lista_iterador *iterador = lista_iterador_crear(pokedex);
	if (!iterador) {
		fprintf(stderr, "Error al crear el iterador\n");
		return;
	}

	while (lista_iterador_hay_siguiente(iterador)) {
		struct pokemon *pokemon =
			lista_iterador_obtener_elemento_actual(iterador);
		if (pokemon != NULL) {
			imprimir_pokemon(pokemon);
		}
		lista_iterador_avanzar(iterador);
	}

	lista_iterador_destruir(iterador);
}

/* Pre: "pokedex" no puede ser NULL y debe apuntar a una lista válida que contenga elementos.*/

/* Pos: Devuelve 0 si la búsqueda se realiza correctamente. 
	   Si el Pokémon se encuentra, se imprimen sus detalles; 
	   si no se encuentra, se muestra un mensaje correspondiente. 
	   Si hay un error al reservar memoria, se muestra un mensaje de error y se devuelve -1.*/

int buscar_pokemon(Lista *pokedex)
{
	char nombre[MAX_NOMBRE_POKEMON];
	printf("Ingrese el nombre del pokemon a buscar: ");
	int resultado_scanf = scanf("%s", nombre);

	if (resultado_scanf != 1) {
		limpiar_buffer();
		return -1;
	}

	animacion_pikachu();

	struct pokemon buscado;
	buscado.nombre = malloc(MAX_NOMBRE_POKEMON * sizeof(char));
	if (!buscado.nombre) {
		mostrar_error();
		return -1;
	}
	strcpy(buscado.nombre, nombre);

	struct pokemon *encontrado = lista_buscar_elemento(
		pokedex, &buscado.nombre, comparar_nombre_pokemon);

	if (encontrado != NULL) {
		mostrar_pokemon_buscado();
		imprimir_pokemon(encontrado);
	} else {
		mostrar_no_encontrado();
	}

	free(buscado.nombre);
	return 0;
}

int main(int argc, char *argv[])
{
	char nombre_archivo[MAX_NOMBRE_ARCHIVO];
	char separador = ';';

	mostrar_inicio();
	mostrar_aclaracion_separador();

	seleccionar_archivo(nombre_archivo, argc, argv, separador);

	struct archivo_csv *archivo =
		abrir_archivo_csv(nombre_archivo, separador);
	if (!archivo) {
		mostrar_error();
		return -1;
	}

	Lista *pokedex = lista_crear();

	procesar_pokemones(archivo, pokedex);

	mostrar_bienvenida();

	mostrar_seleccionar_funcionalidad();

	int opcion = obtener_opcion_menu();

	if (opcion == MOSTRAR_POKEMONES) {
		animacion_pikachu();
		titulo_pokedex();
		imprimir_pokemones(pokedex);
	} else {
		if (buscar_pokemon(pokedex) == -1) {
			return -1;
		}
	}

	cerrar_archivo_csv(archivo);
	lista_destruir_todo(pokedex, (void (*)(void *))liberar_pokemon);

	return 0;
}
