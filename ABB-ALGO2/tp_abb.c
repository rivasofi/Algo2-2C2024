#include "src/abb.h"
#include "src/csv.h"
#include "src/comm_user.h"
#include <ctype.h>
#include <string.h>

const int MAX_NOMBRE_ARCHIVO = 100;
const int PUDO_LEER = 1;
const int COLUMNAS_POKEDEX = 4;
const char CANT_INICIAL = 0;
const char NO_LEYO = 0;
const int BUSCAR_POKEMON = 1;
const int MOSTRAR_POKEMONES = 2;
const char CARACTER_VACIO = '\0';
#define ERROR -1
#define MAX_NOMBRE_POKEMON 50

struct pokemon {
	char *nombre;
	int puntaje;
	char* color;
	char* movimiento;
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

struct pokemon *crear_pokemon(const char *nombre, int puntaje, char* color,
			      char* movimiento)
{
	struct pokemon *nuevo_pokemon = malloc(sizeof(struct pokemon));
	if (nuevo_pokemon == NULL) {
		fprintf(stderr,
			"Error al reservar memoria para un nuevo pokemon\n");
		return NULL;
	}

	nuevo_pokemon->nombre = malloc(strlen(nombre) + 1);
	nuevo_pokemon->color = malloc(strlen(color) + 1);
	nuevo_pokemon->movimiento = malloc(strlen(movimiento) + 1);
	
	if (nuevo_pokemon->nombre == NULL) {
		free(nuevo_pokemon);
		fprintf(stderr,
			"Error al reservar memoria para el nombre del pokemon\n");
		return NULL;
	}

	if (color == NULL || movimiento == NULL) {
		free(nuevo_pokemon->nombre);
		free(nuevo_pokemon);
		fprintf(stderr, "Error al reservar memoria para el pokemon\n");
		return NULL;
	}

	strcpy(nuevo_pokemon->nombre, nombre);
	strcpy(nuevo_pokemon->color, color);
	strcpy(nuevo_pokemon->movimiento, movimiento);

	nuevo_pokemon->puntaje = puntaje;
	

	return nuevo_pokemon;
}

/* Pre: "archivo" no puede ser NULL y debe apuntar a un archivo CSV válido.
	   "string", "caracter", "fuerza", "destreza" y "resistencia" deben ser punteros válidos donde se almacenarán los datos. */

/* Pos: Devuelve true si se leyeron correctamente todos los datos del pokemon. 
	   Si ocurre un error en la lectura, devuelve false. Los punteros de salida contendrán los valores leídos. */

bool parsear_datos_pokemon(struct archivo_csv *archivo, char **string,
			   int *puntaje, char **color, char **movimiento)
{
	bool (*funciones[])(const char *, void *) = { crear_string_nuevo,
						      leer_int, crear_string_nuevo, crear_string_nuevo, crear_string_nuevo };
	void *ptrs[] = { string, puntaje, color, movimiento };

	size_t leidos =
		leer_linea_csv(archivo, COLUMNAS_POKEDEX, funciones, ptrs);
	if (leidos == NO_LEYO) {
		return false;
	}
	if (leidos != COLUMNAS_POKEDEX) {
		printf("Se leyeron %zu columnas en lugar de %d\n", leidos,
		       COLUMNAS_POKEDEX);
		return false;
	}
	return true;
}

/* Pre: "archivo" no puede ser NULL y debe apuntar a un archivo CSV válido.
	   "pokedex" no puede ser NULL y debe ser un puntero a un ABB válido. */

/* Pos: Se agregan los pokemon leídos del archivo CSV al ABB "pokedex". 
	   Se libera la memoria de "string" después de usarla. 
	   Si hay un error en la lectura del archivo, el proceso se detiene. */

void procesar_pokemones(struct archivo_csv *archivo, abb_t *pokedex)
{
	char *string = NULL;
	int puntaje = CANT_INICIAL;
	char* color = NULL;
	char* movimiento = NULL;

	while (parsear_datos_pokemon(archivo, &string, &puntaje, &color,
				     &movimiento)) {
		if (string) {
			abb_insertar(pokedex,
				     crear_pokemon(string, puntaje, color,
						   movimiento));
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
	printf("\t\t\t\t Tipo: %i ", pokemon->puntaje);
	printf("\t\t\t Fuerza: %s ", pokemon->color);
	printf("\t\t\t Destreza: %s ", pokemon->movimiento);
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

/* Pre: "pokedex" no puede ser NULL y debe apuntar a un ABB válido que contenga elementos. */

/* Pos: Imprime los detalles de cada pokemon en la "pokedex". 
	   Si ocurre un error al crear el iterador, se imprime un mensaje de error. */

void imprimir_pokemones(abb_t *pokedex)
{
	if (!pokedex) {
		return;
	}

	abb_iterar_inorden(pokedex, (bool (*)(void *, void *))imprimir_pokemon,
			   NULL);
}

/* Pre: "pokedex" no puede ser NULL y debe apuntar a un ABB válido que contenga elementos.*/

/* Pos: Devuelve 0 si la búsqueda se realiza correctamente. 
	   Si el Pokémon se encuentra, se imprimen sus detalles; 
	   si no se encuentra, se muestra un mensaje correspondiente. 
	   Si hay un error al reservar memoria, se muestra un mensaje de error y se devuelve -1.*/

int buscar_pokemon(abb_t *pokedex)
{
	char nombre[MAX_NOMBRE_POKEMON];
	printf("Ingrese el nombre del pokemon a buscar: ");
	int resultado_scanf = scanf("%s", nombre);

	if (resultado_scanf != 1) {
		limpiar_buffer();
		return ERROR;
	}

	animacion_pikachu();

	struct pokemon buscado;
	buscado.nombre = malloc(MAX_NOMBRE_POKEMON * sizeof(char));
	if (!buscado.nombre) {
		mostrar_error();
		return ERROR;
	}
	strcpy(buscado.nombre, nombre);

	struct pokemon *encontrado = abb_obtener(pokedex, &buscado);

	if (encontrado != NULL) {
		mostrar_pokemon_buscado();
		imprimir_pokemon(encontrado);
	} else {
		mostrar_no_encontrado();
	}

	free(buscado.nombre);
	return 0;
}

/* Pre: "pokedex" debe ser un puntero válido a un ABB.*/

/* Pos: Muestra la cantidad de total de pokemones en la pokedex.*/

void imprimir_cantidad_pokemones(abb_t *pokedex)
{
	size_t cantidad = abb_cantidad(pokedex);
	printf("\n\t\t\t Cantidad total de pokemones: %zu\n", cantidad);
}

/* Pre: "pokemon_void" debe ser un puntero válido a una estructura pokemon que contiene el tipo del Pokémon en el campo "tipo". El struct pokemon debe tener
        correctamente definido el campo "tipo" con un caracter que represente alguno de los siguientes tipos: agua, fuego, planta, roca, electrico, normal, lucha*/

/* Pos: Incrementa el contador correspondiente al tipo del Pokémon en el array de punteros "tipos".*/

// bool contar_pokemon_tipo(void *pokemon_void, void *tipos_void)
// {
// 	struct pokemon *pokemon = (struct pokemon *)pokemon_void;
// 	size_t **tipos = (size_t **)tipos_void;

// 	switch (pokemon->tipo) {
// 	case 'A':
// 		(*(size_t *)tipos[0])++;
// 		break;
// 	case 'F':
// 		(*(size_t *)tipos[1])++;
// 		break;
// 	case 'P':
// 		(*(size_t *)tipos[2])++;
// 		break;
// 	case 'R':
// 		(*(size_t *)tipos[3])++;
// 		break;
// 	case 'E':
// 		(*(size_t *)tipos[4])++;
// 		break;
// 	case 'N':
// 		(*(size_t *)tipos[5])++;
// 		break;
// 	case 'L':
// 		(*(size_t *)tipos[6])++;
// 		break;
// 	default:
// 		break;
// 	}

// 	return true;
// }

/* Pre: "pokedex" debe ser un puntero válido a un ABB.*/

/* Pos: Muestra la cantidad de cada tipo de pokemon en la pokedex.*/

// void imprimir_cantidad_tipo(abb_t *pokedex)
// {
// 	size_t cantidad_agua = CANT_INICIAL;
// 	size_t cantidad_fuego = CANT_INICIAL;
// 	size_t cantidad_planta = CANT_INICIAL;
// 	size_t cantidad_roca = CANT_INICIAL;
// 	size_t cantidad_electricos = CANT_INICIAL;
// 	size_t cantidad_normales = CANT_INICIAL;
// 	size_t cantidad_lucha = CANT_INICIAL;

// 	size_t *tipos[] = { &cantidad_agua,	  &cantidad_fuego,
// 			    &cantidad_planta,	  &cantidad_roca,
// 			    &cantidad_electricos, &cantidad_normales,
// 			    &cantidad_lucha };

// 	abb_iterar_inorden(pokedex, contar_pokemon_tipo, tipos);

// 	printf("\n" AZUL_BOLD "\t\t\t Cantidad de pokemones de agua: %zu" RESET
// 	       "\n",
// 	       cantidad_agua);
// 	printf(ROJO_BOLD "\t\t\t Cantidad de pokemones de fuego: %zu" RESET
// 			 "\n",
// 	       cantidad_fuego);
// 	printf(VERDE_BOLD "\t\t\t Cantidad de pokemones de planta: %zu" RESET
// 			  "\n",
// 	       cantidad_planta);
// 	printf(CYAN_BOLD "\t\t\t Cantidad de pokemones de roca: %zu" RESET "\n",
// 	       cantidad_roca);
// 	printf(MARRON_BOLD "\t\t\t Cantidad de pokemones eléctricos: %zu" RESET
// 			   "\n",
// 	       cantidad_electricos);
// 	printf(MAGENTA_BOLD "\t\t\t Cantidad de pokemones normales: %zu" RESET
// 			    "\n",
// 	       cantidad_normales);
// 	printf(ROJO_BOLD "\t\t\t Cantidad de pokemones de lucha: %zu" RESET
// 			 "\n\n",
// 	       cantidad_lucha);
// }

int main(int argc, char *argv[])
{
	char nombre_archivo[MAX_NOMBRE_ARCHIVO];
	char separador = ',';

	mostrar_inicio();
	mostrar_aclaracion_separador();

	seleccionar_archivo(nombre_archivo, argc, argv, separador);

	struct archivo_csv *archivo =
		abrir_archivo_csv(nombre_archivo, separador);
	if (!archivo) {
		mostrar_error();
		return ERROR;
	}

	abb_t *pokedex =
		abb_crear((int (*)(void *, void *))comparar_nombre_pokemon);

	procesar_pokemones(archivo, pokedex);

	// mostrar_bienvenida();

	mostrar_seleccionar_funcionalidad();

	int opcion = obtener_opcion_menu();

	if (opcion == MOSTRAR_POKEMONES) {
		// animacion_pikachu();
		titulo_pokedex();
		imprimir_pokemones(pokedex);
		imprimir_cantidad_pokemones(pokedex);
		// imprimir_cantidad_tipo(pokedex);
	} else {
		if (buscar_pokemon(pokedex) == ERROR) {
			return ERROR;
		}
	}

	cerrar_archivo_csv(archivo);
	abb_destruir_todo(pokedex, (void (*)(void *))liberar_pokemon);

	return 0;
}
