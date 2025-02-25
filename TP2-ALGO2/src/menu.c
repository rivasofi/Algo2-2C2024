#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "menu.h"
#include "logica.h"

#define CAPACIDAD_INICIAL 4

struct Accion {
	char indice;
	void (*funcion)(void *contexto);
};

struct Menu {
	Lista *acciones;
};

void destruir_accion(accion_t *Accion)
{
	if (!Accion)
		return;
	free(Accion);
}

void liberar_todo(menu_t *menu, struct contexto_menu *ctx,
		  struct archivo_csv *archivo)
{
	if (!menu || !ctx || !archivo) {
		return;
	}

	destruir_menu(menu);
	abb_destruir_todo(ctx->pokemones_en_juego, liberar_pokemon);
	destruir_jugador(ctx->jugador);
	destruir_pokedex(ctx->pokedex);
	cerrar_archivo_csv(archivo);
	exit(0);
}

int comparador_char(void *a, void *b)
{
	if (!a || !b)
		return 0;
	return *(char *)a - *(char *)b;
}

/*----*/

menu_t *crear_menu()
{
	menu_t *menu = malloc(sizeof(accion_t));
	if (!menu) {
		fprintf(stderr, "Error al crear el menú.\n");
		return NULL;
	}

	menu->acciones = lista_crear();
	if (!menu->acciones) {
		free(menu);
		fprintf(stderr, "Error al crear la lista de acciones.\n");
		return NULL;
	}

	return menu;
}

accion_t *accion_crear(char indice, void (*funcion)(void *))
{
	if (!funcion)
		return NULL;

	accion_t *accion = malloc(sizeof(accion_t));
	if (!accion)
		return NULL;

	accion->indice = indice;
	accion->funcion = funcion;
	return accion;
}

void imprimir_menu()
{
	printf("\n\n\t\t\t\t\t\t\t\t   __  __              __        _                         _                                \n");
	printf("\t\t\t\t\t\t\t\t  |  \\/  | ___ _ __  _/_/_    __| | ___    ___  _ __   ___(_) ___  _ __   ___  ___          \n");
	printf("\t\t\t\t\t\t\t\t  | |\\/| |/ _ \\ '_ \\| | | |  / _` |/ _ \\  / _ \\| '_ \\ / __| |/ _ \\| '_ \\ / _ \\/ __|     \n");
	printf("\t\t\t\t\t\t\t\t  | |  | |  __/ | | | |_| | | (_| |  __/ | (_) | |_) | (__| | (_) | | | |  __/\\__ \\         \n");
	printf("\t\t\t\t\t\t\t\t  |_|  |_|\\___|_| |_|\\__,_|  \\__,_|\\___|  \\___/| .__/ \\___|_|\\___/|_| |_|\\___||___/       \n");

	printf("\t\t\t\t\t\t\t\t   ____    __  __           _                  |_|___       _            _                  \n");
	printf("\t\t\t\t\t\t\t\t  |  _ \\  |  \\/  | ___  ___| |_ _ __ __ _ _ __  |  _ \\ ___ | | _____  __| | _____  __       \n");
	printf("\t\t\t\t\t\t\t\t  | |_) | | |\\/| |/ _ \\/ __| __| '__/ _` | '__| | |_) / _ \\| |/ / _ \\/ _` |/ _ \\ \\/ /       \n");
	printf("\t\t\t\t\t\t\t\t  |  __/  | |  | | (_) \\__ \\ |_| | | (_| | |    |  __/ (_) |   <  __/ (_| |  __/>  <        \n");
	printf("\t\t\t\t\t\t\t\t  |_| (_) |_|  |_|\\___/|___/\\__|_|  \\__,_|_|    |_|   \\___/|_|\\_\\___|\\__,_|\\___/_/\\_\\   \n");
	printf("\t\t\t\t\t\t\t\t      | |      | |_   _  __ _  __ _ _ __                                                    \n");
	printf("\t\t\t\t\t\t\t\t   _  | |   _  | | | | |/ _` |/ _` | '__|                                                   \n");
	printf("\t\t\t\t\t\t\t\t  | |_| |  | |_| | |_| | (_| | (_| | |                                                      \n");
	printf("\t\t\t\t\t\t\t\t   \\___(_)  \\___/ \\__,_|\\__, |\\__,_|_|                                          _ _ _       \n");
	printf("\t\t\t\t\t\t\t\t  / ___|       | |_   _ |___/  __ _ _ __    ___ ___  _ __    ___  ___ _ __ ___ (_) | | __ _ \n");
	printf("\t\t\t\t\t\t\t\t  \\___ \\    _  | | | | |/ _` |/ _` | '__|  / __/ _ \\| '_ \\  / __|/ _ \\ '_ ` _ \\| | | |/ _` |\n");
	printf("\t\t\t\t\t\t\t\t   ___) |  | |_| | |_| | (_| | (_| | |    | (_| (_) | | | | \\__ \\  __/ | | | | | | | | (_| |\n");
	printf("\t\t\t\t\t\t\t\t  |____(_)  \\___/ \\__,_|\\__, |\\__,_|_|     \\___\\___/|_| |_| |___/\\___|_| |_| |_|_|_|_|\\__,_|\n");
	printf("\t\t\t\t\t\t\t\t    ___      ____       |___/                                                               \n");
	printf("\t\t\t\t\t\t\t\t   / _ \\    / ___|  __ _| (_)_ __                                                           \n");
	printf("\t\t\t\t\t\t\t\t  | | | |   \\___ \\ / _` | | | '__|                                                          \n");
	printf("\t\t\t\t\t\t\t\t  | |_| |_   ___) | (_| | | | |                                                             \n");
	printf("\t\t\t\t\t\t\t\t   \\__\\_(_) |____/ \\__,_|_|_|_|                                                             \n");
}

void imprimir_menu_simple()
{
	printf("\n\n\t\t\t\t\t\t\t\t   Elije una opción\n");
	printf("\t\t\t\t\t\t\t\t   P - Mostrar Pokédex\n");
	printf("\t\t\t\t\t\t\t\t   J - Jugar\n");
	printf("\t\t\t\t\t\t\t\t   S - Jugar con semilla\n");
	printf("\t\t\t\t\t\t\t\t   Q - Salir\n");
}

void interactuar_menu(menu_t *menu, void *contexto, struct archivo_csv *archivo)
{
	if (!menu || !contexto || !archivo) {
		return;
	}

	struct contexto_menu *ctx = (struct contexto_menu *)contexto;

	char opcion;
	printf("\n\n\t\t\t\t\t\t\t\t   Ingrese una opción: ");
	if (scanf(" %c", &opcion) != 1) {
		fprintf(stderr, "Error al leer la opción\n");
		return;
	}

	opcion = (char)toupper((unsigned char)opcion);

	if (opcion == 'Q') {
		liberar_todo(menu, ctx, archivo);
	}

	if (opcion != 'P' && opcion != 'J' && opcion != 'S') {
		printf("\n\n\t\t\t\t\t\t\t\t   Opción inválida. Intente nuevamente.\n");
		interactuar_menu(menu, ctx, archivo);
	}

	accion_t *accion =
		lista_buscar_elemento(menu->acciones, &opcion, comparador_char);
	if (accion && menu->acciones && accion->funcion) {
		accion->funcion(ctx->pokedex);
		if (opcion == 'P') {
			imprimir_menu_simple();
			interactuar_menu(menu, ctx, archivo);
		}
	} else {
		printf("\n\n\t\t\t\t\t\t\t\t   Opción inválida. Intente nuevamente.\n");
	}
}

bool menu_agregar_accion(menu_t *menu, accion_t *accion)
{
	if (!menu || !accion)
		return false;
	return lista_agregar_al_final(menu->acciones, accion);
}

void destruir_menu(menu_t *menu)
{
	if (!menu) {
		return;
	}

	lista_destruir_todo(menu->acciones, (void (*)(void *))destruir_accion);
	free(menu);
}