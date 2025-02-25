#include "extra/engine.h"
#include "extra/ansi.h"
#include "src/menu.h"
#include "src/logica.h"
#include "src/jugador.h"
#include "src/comm_user.h"

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define FILAS_TABLERO 15
#define COLUMNAS_TABLERO 32

struct datos_juego {
	jugador_t *jugador;
	char **tablero;
	abb_t *pokemones_en_juego;
	pokedex_t *pokedex;
};

int flujo(int entrada, void *datos, pokedex_t *pokedex)
{
	struct datos_juego *datos_juego = (struct datos_juego *)datos;
	jugador_t *jugador = datos_juego->jugador;
	char **tablero = datos_juego->tablero;
	abb_t *poke_en_juego = datos_juego->pokemones_en_juego;
	pokedex_t *pokedex_juego = datos_juego->pokedex;

	borrar_pantalla();

	if (entrada == TECLA_DERECHA || entrada == TECLA_IZQUIERDA ||
	    entrada == TECLA_ARRIBA || entrada == TECLA_ABAJO) {
		mover_jugador(entrada, jugador, tablero);
		mover_pokemones(tablero, poke_en_juego, entrada);
		capturar_pokemones(jugador, poke_en_juego, pokedex_juego,
				   tablero);
	} else if (entrada == 'q' || entrada == 'Q') {
		return 1;
	}

	incrementar_iteraciones_jugador(jugador);

	printf("Utilice las flechas para moverse\n");
	printf("Presione " ANSI_COLOR_RED ANSI_COLOR_BOLD "Q" ANSI_COLOR_RESET
	       " para salir\n\n");
	printf("⏱️ : %d\t\t\t\t👣: %d\t\t\t\t🪙: %d\t\t\t\t✖️ : %d\n\n",
	       obtener_iteraciones_jugador(jugador) / 5,
	       obtener_movimientos_jugador(jugador),
	       obtener_puntos_jugador(jugador),
	       obtener_multiplicador_jugador(jugador));

	ubicar_jugador(tablero, (size_t)obtener_x_jugador(jugador),
		       (size_t)obtener_y_jugador(jugador));

	imprimir_tablero(tablero, FILAS_TABLERO, COLUMNAS_TABLERO,
			 poke_en_juego);

	mostrar_ultimo_capturado(jugador);

	esconder_cursor();

	return entrada == 'q' || entrada == 'Q' ||
	       obtener_iteraciones_jugador(jugador) / 5 == 60;
}

int flujo_wrapper(int entrada, void *datos)
{
	struct datos_juego *datos_juego = (struct datos_juego *)datos;
	pokedex_t *pokedex = datos_juego->pokedex;
	return flujo(entrada, datos, pokedex);
}

int main(int argc, char *argv[])
{
	srand((unsigned int)time(NULL));
	menu_t *menu = crear_menu();
	pokedex_t *pokedex = crear_pokedex();
	abb_t *pokemones_en_juego = abb_crear(comparar_pokemon);
	jugador_t *jugador = crear_jugador();
	const char *nombre_archivo = argv[1];
	struct archivo_csv *archivo = abrir_archivo_csv(nombre_archivo, ',');

	cargar_pokedex(pokedex, archivo);

	unsigned int *semilla_ptr = NULL;

	struct contexto_menu contexto = { .pokedex = pokedex,
					  .jugador = jugador,
					  .pokemones_en_juego =
						  pokemones_en_juego,
					  .semilla = semilla_ptr };

	cargar_acciones_menu(menu);
	mostrar_inicio();
	sleep(1);
	imprimir_menu();
	interactuar_menu(menu, &contexto, archivo);

	borrar_pantalla();

	char **tablero = crear_tablero(FILAS_TABLERO, COLUMNAS_TABLERO);
	definir_tablero_vacio(tablero, FILAS_TABLERO, COLUMNAS_TABLERO);
	ubicar_pokemones_aleatorios(pokedex, tablero, pokemones_en_juego);
	imprimir_tablero(tablero, FILAS_TABLERO, COLUMNAS_TABLERO,
			 pokemones_en_juego);

	struct datos_juego datos_juego = { jugador, tablero, pokemones_en_juego,
					   pokedex };

	animacion_pikachu();
	game_loop(flujo_wrapper, &datos_juego);

	mostrar_stats_pokemon();

	printf(ANSI_COLOR_RED "Juego finalizado\n" RESET);
	printf("Puntos obtenidos: %d\n", obtener_puntos_jugador(jugador));
	printf("El multiplicador mas alto fue: %d\n",
	       obtener_multiplicador_mas_alto_jugador(jugador));
	char *ultimo_capturado = obtener_nombre_ultimo_capturado(jugador);
	if (!ultimo_capturado) {
		printf(ANSI_COLOR_RED "No atrapaste ningún pokemon!\n" RESET);
	} else {
		printf("El último pokemon capturado fue: %s\n",
		       ultimo_capturado);
	}
	printf("Tu multiplicador final fue: %d\n",
	       obtener_multiplicador_jugador(jugador));
	printf("Jugaste durante %d segundos\n",
	       obtener_iteraciones_jugador(jugador) / 5);
	printf("Realizaste %d movimientos\n",
	       obtener_movimientos_jugador(jugador));
	printf(ANSI_COLOR_MAGENTA "¡Gracias por jugar!\n" RESET);

	destruir_pokedex(pokedex);
	destruir_tablero(tablero, FILAS_TABLERO);
	destruir_jugador(jugador);
	if (pokemones_en_juego) {
		abb_destruir_todo(pokemones_en_juego, liberar_pokemon);
	}
	cerrar_archivo_csv(archivo);
	destruir_menu(menu);

	return 0;
}
