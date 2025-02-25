#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include "src/hash.h"
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

/* Pre: "str" debe finalizar en '\0'.*/
/* Pos: Convierte todos los caracteres del string en minúsculas.*/

void string_en_minusculas(char *str)
{
	for (int i = 0; str[i]; i++) {
		str[i] = (char)tolower((unsigned char)str[i]);
	}
}

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

/* Pre: "pokedex" no puede ser NULL y debe ser un puntero a un hash válido. "string" debe ser una cadena de caracteres válida. "caracter" debe ser un
		carácter válido. "fuerza", "destreza" y "resistencia" deben ser enteros. */

/* Pos: Si se crea el nuevo pokemon correctamente, se agrega al hash "pokedex". 
	   No se realizan cambios si la creación del pokemon falla. */

void agregar_pokemones_a_hash(hash_t *pokedex, char *string, char caracter,
			      int fuerza, int destreza, int resistencia)
{
	struct pokemon *nuevo_pokemon =
		crear_pokemon(string, caracter, fuerza, destreza, resistencia);
	if (nuevo_pokemon != NULL) {
		hash_insertar(pokedex, nuevo_pokemon->nombre, nuevo_pokemon,
			      NULL);
	}
}

/* Pre: "archivo" no puede ser NULL y debe apuntar a un archivo CSV válido.
	   "pokedex" no puede ser NULL y debe ser un puntero a un hash válido. */

/* Pos: Se agregan los pokemon leídos del archivo CSV al hash "pokedex". 
	   Se libera la memoria de "string" después de usarla. 
	   Si hay un error en la lectura del archivo, el proceso se detiene. */

void procesar_pokemones(struct archivo_csv *archivo, hash_t *pokedex)
{
	char *string = NULL;
	char caracter = CANT_INICIAL;
	int fuerza = CANT_INICIAL;
	int destreza = CANT_INICIAL;
	int resistencia = CANT_INICIAL;

	while (parsear_datos_pokemon(archivo, &string, &caracter, &fuerza,
				     &destreza, &resistencia)) {
		if (string) {
			string_en_minusculas(string);
			agregar_pokemones_a_hash(pokedex, string, caracter,
						 fuerza, destreza, resistencia);
			free(string);
		}
	}
}

/* Pre: "pokemon" no puede ser NULL y debe apuntar a un struct "pokemon" válido 
	   con campos inicializados (nombre, tipo, fuerza, destreza, resistencia). */

/* Pos: Imprime los datos del pokemon*/

bool imprimir_pokemon(char *clave, void *valor, void *ctx)
{
	struct pokemon *pokemon = (struct pokemon *)valor;
	if (!pokemon) {
		return false; // Manejo de caso nulo, si es necesario
	}

	printf("\t\t\t Nombre: %s ", pokemon->nombre);
	printf("\t\t\t\t Tipo: %c ", pokemon->tipo);
	printf("\t\t\t Fuerza: %d ", pokemon->fuerza);
	printf("\t\t\t Destreza: %d ", pokemon->destreza);
	printf("\t\t\t Resistencia: %d\n\n", pokemon->resistencia);

	return true; // Para continuar iterando
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

/* Pre: "pokedex" no puede ser NULL y debe apuntar a un hash que contenga elementos. */

/* Pos: Imprime los detalles de cada pokemon en la "pokedex". 
	   Si ocurre un error al crear el iterador, se imprime un mensaje de error. */

void imprimir_pokemones(hash_t *pokedex)
{
	hash_iterar(pokedex, imprimir_pokemon, NULL);
}

/* Pre: "pokedex" no puede ser NULL y debe apuntar a un ABB válido que contenga elementos.*/

/* Pos: Devuelve 0 si la búsqueda se realiza correctamente. 
	   Si el Pokémon se encuentra, se imprimen sus detalles; 
	   si no se encuentra, se muestra un mensaje correspondiente. 
	   Si hay un error al reservar memoria, se muestra un mensaje de error y se devuelve -1.*/

int buscar_pokemon(hash_t *pokedex)
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
	string_en_minusculas(nombre);
	strcpy(buscado.nombre, nombre);

	struct pokemon *encontrado = hash_buscar(pokedex, buscado.nombre);

	if (encontrado != NULL) {
		mostrar_pokemon_buscado();
		imprimir_pokemon(buscado.nombre, encontrado, NULL);
	} else {
		mostrar_no_encontrado();
	}

	free(buscado.nombre);
	return 0;
}

void imprimir_cantidad_pokemones(hash_t *pokedex)
{
	size_t cantidad = hash_cantidad(pokedex);
	printf("\n\t\t\t Cantidad total de pokemones: %zu\n", cantidad);
}

/* Pre: "pokemon_void" debe ser un puntero válido a una estructura pokemon que contiene el tipo del Pokémon en el campo "tipo". El struct pokemon debe tener
        correctamente definido el campo "tipo" con un caracter que represente alguno de los siguientes tipos: agua, fuego, planta, roca, electrico, normal, lucha*/

/* Pos: Incrementa el contador correspondiente al tipo del Pokémon en el array de punteros "tipos".*/

bool contar_pokemon_tipo(char *key, void *pokemon_void, void *tipos_void)
{
	struct pokemon *pokemon = (struct pokemon *)pokemon_void;
	size_t **tipos = (size_t **)tipos_void;

	switch (pokemon->tipo) {
	case 'A':
		(*(size_t *)tipos[0])++;
		break;
	case 'F':
		(*(size_t *)tipos[1])++;
		break;
	case 'P':
		(*(size_t *)tipos[2])++;
		break;
	case 'R':
		(*(size_t *)tipos[3])++;
		break;
	case 'E':
		(*(size_t *)tipos[4])++;
		break;
	case 'N':
		(*(size_t *)tipos[5])++;
		break;
	case 'L':
		(*(size_t *)tipos[6])++;
		break;
	default:
		break;
	}

	return true;
}

/* Pre: "pokedex" debe ser un puntero válido a un Hash.*/

/* Pos: Muestra la cantidad de cada tipo de pokemon en la pokedex.*/

void imprimir_cantidad_tipo(hash_t *pokedex)
{
	size_t cantidad_agua = CANT_INICIAL;
	size_t cantidad_fuego = CANT_INICIAL;
	size_t cantidad_planta = CANT_INICIAL;
	size_t cantidad_roca = CANT_INICIAL;
	size_t cantidad_electricos = CANT_INICIAL;
	size_t cantidad_normales = CANT_INICIAL;
	size_t cantidad_lucha = CANT_INICIAL;

	size_t *tipos[] = { &cantidad_agua,	  &cantidad_fuego,
			    &cantidad_planta,	  &cantidad_roca,
			    &cantidad_electricos, &cantidad_normales,
			    &cantidad_lucha };

	hash_iterar(pokedex, contar_pokemon_tipo, tipos);

	printf("\n" AZUL_BOLD "\t\t\t Cantidad de pokemones de agua: %zu" RESET
	       "\n",
	       cantidad_agua);
	printf(ROJO_BOLD "\t\t\t Cantidad de pokemones de fuego: %zu" RESET
			 "\n",
	       cantidad_fuego);
	printf(VERDE_BOLD "\t\t\t Cantidad de pokemones de planta: %zu" RESET
			  "\n",
	       cantidad_planta);
	printf(CYAN_BOLD "\t\t\t Cantidad de pokemones de roca: %zu" RESET "\n",
	       cantidad_roca);
	printf(MARRON_BOLD "\t\t\t Cantidad de pokemones eléctricos: %zu" RESET
			   "\n",
	       cantidad_electricos);
	printf(MAGENTA_BOLD "\t\t\t Cantidad de pokemones normales: %zu" RESET
			    "\n",
	       cantidad_normales);
	printf(ROJO_BOLD "\t\t\t Cantidad de pokemones de lucha: %zu" RESET
			 "\n\n",
	       cantidad_lucha);
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

	hash_t *pokedex = hash_crear(100);

	procesar_pokemones(archivo, pokedex);

	mostrar_bienvenida();

	mostrar_seleccionar_funcionalidad();

	int opcion = obtener_opcion_menu();

	if (opcion == MOSTRAR_POKEMONES) {
		animacion_pikachu();
		titulo_pokedex();
		imprimir_pokemones(pokedex);
		imprimir_cantidad_pokemones(pokedex);
		imprimir_cantidad_tipo(pokedex);
	} else {
		if (buscar_pokemon(pokedex) == -1) {
			return -1;
		}
	}

	cerrar_archivo_csv(archivo);
	hash_destruir_todo(pokedex, (void (*)(void *))liberar_pokemon);

	return 0;
}