#include "src/csv.h"
#include "src/pokedex.h"
#include "src/comm_user.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

const int MAX_NOMBRE_ARCHIVO = 100;
const int COLUMNAS_POKEDEX = 5;
const int PUDO_LEER = 1;
const int MIN_ARGUMENTOS_SI_PASA_ARCHIVO = 2;
const size_t LONGITUD_EXTENSION = 4;
const int NOMBRE_VACIO = 0;
const int SON_MISMO_STR = 0;
const char NO_LEYO = 0;
const char FIN_STR = '\0';
const char CANT_INICIAL = 0;

#define MAX_NOMBRE_POKEMON 50

/*Pre: "str" debe finalizar en '\0'. "ctx" debe ser un ptr válido, no debe ser NULL.*/
/*Pos: Devuelve true si el parseo fue exitoso, caso contrario devuelve false.*/

bool leer_int(const char *str, void *ctx)
{
	return sscanf(str, "%d", (int *)ctx) == PUDO_LEER;
}

/*Pre: "str" debe finalizar en '\0' y ni str ni ctx pueden ser NULL*/
/*Pos: Devuelve true cuando ctx es un ptr a un string que tiene una copia de str. En caso de fallo devuelve false.*/

bool crear_string_nuevo(const char *str, void *ctx)
{
	static char nuevo[MAX_NOMBRE_POKEMON];
	if (strlen(str) >= MAX_NOMBRE_POKEMON) {
		return false;
	}
	strcpy(nuevo, str);
	*(char **)ctx = nuevo;
	return true;
}

/*Pre: "str" debe ser un caracter válido. "ctx" debe ser un ptr válido, no debe ser NULL.*/
/*Pos: Devuelve true si el parseo fue exitoso, caso contrario devuelve false.*/

bool leer_caracter(const char *str, void *ctx)
{
	*(char *)ctx = str[0];
	return true;
}

/*Pre: argc debe ser mayor a 0.*/
/*Pos: Devuelve true si "argc" es mayor a 1, caso contrario devuelve false.*/

bool se_paso_archivo_argumento(int argc)
{
	return argc >= MIN_ARGUMENTOS_SI_PASA_ARCHIVO;
}

/*Pre: "separador" debe ser un ptr válido.*/
/*Pos: Modifica el valor de "separador" con el caracter leído por getchar().*/

void pedir_separador(char *separador)
{
	*separador = '\0';

	int c = getchar();

	if (c != EOF) {
		*separador = (char)c;
	}
}

/*Pre: "nombre_archivo" debe ser un ptr a un string válido.*/
/*Pos: Verifica que el nombre del archivo no tenga la extensión .csv.*/

void verificar_validez_nombre_archivo(char *nombre_archivo)
{
	bool valido = false;

	while (!valido) {
		size_t longitud_nombre = strlen(nombre_archivo);

		if ((longitud_nombre == NOMBRE_VACIO) ||
		    (longitud_nombre >= LONGITUD_EXTENSION &&
		     strcmp(&nombre_archivo[longitud_nombre - LONGITUD_EXTENSION],
			    ".csv") == SON_MISMO_STR)) {
			printf(ROJO
			       "¡Recorda que no hay que poner la extensión .csv!\n" RESET);
			if (fgets(nombre_archivo, MAX_NOMBRE_ARCHIVO, stdin) ==
			    NULL) {
				printf(ROJO
				       "Error al leer el nombre del archivo\n" RESET);
				return;
			}

			nombre_archivo[strcspn(nombre_archivo, "\n")] = '\0';
		} else {
			valido = true;
		}
	}
}

/*Pre: "nombre_archivo" debe ser un ptr a un string (finalizar en '\0')*/
/*Pos: Copia el valor del input a nombre_archivo y verifica su validez.*/

void pedir_archivo(char *nombre_archivo)
{
	if (fgets(nombre_archivo, MAX_NOMBRE_ARCHIVO, stdin) != NULL) {
		nombre_archivo[strcspn(nombre_archivo, "\n")] = FIN_STR;
	}

	verificar_validez_nombre_archivo(nombre_archivo);
}

/*Pre: "nombre_archivo" debe ser un ptr a un string (finalizar en '\0')*/
/*Pos: Modifica el valor de "nombre_archivo" con el nombre del archivo leído por fgets().*/

void seleccionar_nombre_archivo(char *nombre_archivo)
{
	pedir_archivo(nombre_archivo);
	strcat(nombre_archivo, ".csv");
}

/*Pos: Solicita el separador al usuario y lo retorna como un char almacenado por memoria dinámica.*/

char *seleccionar_separador()
{
	char *separador = malloc(sizeof(char));
	pedir_separador(separador);
	return separador;
}

/*Pre: "archivo" debe ser un ptr a un struct de tipo archivo_csv, "separador" debe ser un ptr válido a un char y pokedex un ptr válido a un struct del tipo pokedex*/
/*Pos: Si el archivo es NULL, muestra un mensaje de error, libera la memoria asignada a pokedex y separador y finaliza el programa.*/

void manejar_error_archivo(struct archivo_csv *archivo, char *separador,
			   struct pokedex *pokedex)
{
	if (archivo == NULL) {
		mostrar_mensaje_carga_fallida();
		sleep(1);
		mostrar_error_abrir_archivo();
		free(separador);
		free(pokedex);
		exit(1);
	}
}

/*Pos: "Retorna true si la reserva de memoria fue exitosa, caso contrario retorna false."*/

bool malloc_pokedex_exitoso(struct pokedex *pokedex)
{
	return pokedex != NULL;
}

/*Pre: Tanto "pokedex" como "separador" deben haber sido asignados por memoria dinámica.*/
/*Pos: Si la reserva de memoria para pokedex falla, muestra un mensaje de error, libera la memoria asignada a separador y finaliza el programa.*/

void manejar_error_memoria_pokedex(struct pokedex *pokedex, char *separador)
{
	if (!malloc_pokedex_exitoso(pokedex)) {
		mostrar_mensaje_fracaso_pokedex();
		free(separador);
		exit(1);
	}
}

/*Pre: "nombre" debe ser un ptr a un string válido que contiene el nombre del pokemon, "tipo" debe ser un char que represente el tipo del pokemón
		y los parámetros restantes deben representar sus estadísticas.*/
/*Pos: Retorna un nuevo pokemon con los datos pasados por parámetro.*/

struct pokemon *crear_pokemon(char *nombre, char tipo, int fuerza, int destreza,
			      int resistencia)
{
	struct pokemon *nuevo_pokemon = malloc(sizeof(struct pokemon));
	if (nuevo_pokemon == NULL) {
		fprintf(stderr,
			"Error al reservar memoria para un nuevo pokemon\n");
		return NULL;
	}
	nuevo_pokemon->nombre = nombre;
	nuevo_pokemon->tipo = tipo;
	nuevo_pokemon->fuerza = fuerza;
	nuevo_pokemon->destreza = destreza;
	nuevo_pokemon->resistencia = resistencia;

	return nuevo_pokemon;
}

/*Pre: Los campos de "pokemon" deben haber sido previamente llenados.*/
/*Pos: Imprime los datos del pokemon pasado por parámetro.*/

bool imprimir_pokemon(struct pokemon *pokemon, void *ctx)
{
	(void)ctx;

	printf("\t\t\t Nombre: %s ", pokemon->nombre);
	printf("\t\t\t\t Tipo: %c ", pokemon->tipo);
	printf("\t\t\t Fuerza: %d ", pokemon->fuerza);
	printf("\t\t\t Destreza: %d ", pokemon->destreza);
	printf("\t\t\t Resistencia: %d\n\n", pokemon->resistencia);

	return true;
}

/*Pre: "archivo" debe ser un puntero a una estructura archivo_csv válida y correctamente inicializada.
    	"pokedex" debe ser un puntero a una estructura pokedex válida y correctamente inicializada. 
        El array de funciones "funciones" debe contener punteros a funciones que acepten una cadena y un puntero a contexto, y devuelvan un bool.*/
/*Pos: Procesa cada línea del archivo CSV usando las funciones de lectura proporcionadas, crea nuevos objetos pokemon con los datos leídos, 
       los agrega a la estructura pokedex y muestra la información de cada uno.*/

void procesar_lineas_csv(struct archivo_csv *archivo, struct pokedex *pokedex)
{
	bool (*funciones[])(const char *, void *) = { crear_string_nuevo,
						      leer_caracter, leer_int,
						      leer_int, leer_int };

	int fuerza = CANT_INICIAL;
	int destreza = CANT_INICIAL;
	int resistencia = CANT_INICIAL;
	char caracter = CANT_INICIAL;
	char *string = NULL;

	void *ptrs[5] = { &string, &caracter, &fuerza, &destreza,
			  &resistencia };

	size_t leidos =
		leer_linea_csv(archivo, COLUMNAS_POKEDEX, funciones, ptrs);
	while (leidos != NO_LEYO) {
		if (leidos == COLUMNAS_POKEDEX) {
			struct pokemon *nuevo_pokemon =
				crear_pokemon(string, caracter, fuerza,
					      destreza, resistencia);
			if (nuevo_pokemon != NULL) {
				pokedex_agregar_pokemon(pokedex,
							*nuevo_pokemon);
				free(nuevo_pokemon);
			}
		}
		leidos = leer_linea_csv(archivo, COLUMNAS_POKEDEX, funciones,
					ptrs);
	}

	pokedex_iterar_pokemones(pokedex, imprimir_pokemon, NULL);
}

/*Pre: "pokemon" debe ser un puntero válido a una estructura pokemon que contiene el tipo del Pokémon en el campo "tipo".
		"tipos_void" debe ser un puntero a un array de punteros a size_t, donde cada puntero se utiliza para contar la cantidad de Pokémon de un tipo 
		específico.*/
/*Pos: Incrementa el contador correspondiente al tipo del Pokémon en el array de punteros "tipos".*/

bool contar_pokemon_tipo(struct pokemon *pokemon, void *tipos_void)
{
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

/* Pre: "pokedex" debe ser un puntero válido a una estructura pokedex.
   Pos: Muestra la cantidad de Pokémon por tipo en la pokedex.*/

void imprimir_cantidad_por_tipo(struct pokedex *pokedex)
{
	size_t cantidad_agua = CANT_INICIAL;
	size_t cantidad_fuego = CANT_INICIAL;
	size_t cantidad_planta = CANT_INICIAL;
	size_t cantidad_roca = CANT_INICIAL;
	size_t cantidad_electricos = CANT_INICIAL;
	size_t cantidad_normales = CANT_INICIAL;
	size_t cantidad_lucha = CANT_INICIAL;

	size_t *tipos[7] = { &cantidad_agua,	   &cantidad_fuego,
			     &cantidad_planta,	   &cantidad_roca,
			     &cantidad_electricos, &cantidad_normales,
			     &cantidad_lucha };

	pokedex_iterar_pokemones(pokedex, contar_pokemon_tipo, tipos);

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

int main(int argc, char const *argv[])
{
	mostrar_inicio();
	sleep(1);

	char nombre_archivo[MAX_NOMBRE_ARCHIVO];
	char *separador = NULL;
	bool ingreso_usuario = false;

	if (se_paso_archivo_argumento(argc)) {
		strcpy(nombre_archivo, argv[1]);
		separador = ";";
	} else {
		mostrar_seleccionar_archivo();
		mostrar_aclaracion_seleccionar_archivo();
		seleccionar_nombre_archivo(nombre_archivo);
		mostrar_seleccionar_separador();
		separador = seleccionar_separador();
		ingreso_usuario = true;
	}

	sleep(1);
	mostrar_cargando();
	sleep(1);
	limpiar_pantalla();
	mostrar_mensaje_inicio();
	sleep(1);

	struct archivo_csv *archivo =
		abrir_archivo_csv(nombre_archivo, *separador);

	struct pokedex *pokedex = pokedex_crear();

	manejar_error_archivo(archivo, separador, pokedex);

	mostrar_mensaje_post_exito();
	sleep(1);
	mostrar_mensaje_creando_pokedex();
	sleep(2);

	manejar_error_memoria_pokedex(pokedex, separador);

	mostrar_mensaje_exito_pokedex();
	sleep(1);
	mostrar_mensaje_carga();
	sleep(2);
	mostrar_mensaje_carga_exito();
	sleep(1);
	mostrar_dirigiendo_a_pokedex();
	sleep(1);
	mostrar_titulo_pokedex();

	procesar_lineas_csv(archivo, pokedex);

	imprimir_cantidad_por_tipo(pokedex);
	cerrar_archivo_csv(archivo);
	if (ingreso_usuario) {
		free(separador);
	}
	pokedex_destruir(pokedex);

	return 0;
}