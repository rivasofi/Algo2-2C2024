#include "logica.h"
#include "comm_user.h"
#include <time.h>

#define CANT_INICIAL 0
#define MAX_X 15
#define MAX_Y 32

#define MAXIMA_FILA 14
#define MAXIMA_COLUMNA 31

#define ARRIBA 'N'
#define ABAJO 'S'
#define DERECHA 'E'
#define IZQUIERDA 'O'
#define JUGADOR 'J'
#define INVERTIDO 'I'
#define RANDOM 'R'
#define CANTIDAD_POKEMONES_JUEGO 7
#define MOVIMIENTOS_SIMPLES_POSIBLES 4

typedef struct {
	char **tablero;
	int entrada;
} ctx;

struct contexto_captura {
	jugador_t *jugador;
	pokedex_t *pokedex;
	char **tablero;
	abb_t *pokemones_en_juego;
	Lista *pokemones_capturados;
	pokemon_t *pokemon_capturado;
};

int max(int a, int b)
{
	return a > b ? a : b;
}

int min(int a, int b)
{
	return a < b ? a : b;
}

int generar_posicion_aleatoria(int min, int max)
{
	return min + rand() % (max - min + 1);
}

void ubicar_en_tablero(pokemon_t *pokemon, char **tablero)
{
	if (!pokemon || !tablero) {
		return;
	}

	int x = obtener_x_pokemon(pokemon);
	int y = obtener_y_pokemon(pokemon);

	if (x < 0 || x >= MAX_X || y < 0 || y >= MAX_Y) {
		return;
	}

	tablero[x][y] = obtener_inicial_pokemon(pokemon);
}

void ubicar_aleatorio(pokedex_t *pokedex, char **tablero,
		      abb_t *pokemones_en_juego)
{
	if (!pokedex || !tablero || !pokemones_en_juego) {
		return;
	}

	if (abb_cantidad(pokemones_en_juego) > CANTIDAD_POKEMONES_JUEGO) {
		return;
	}

	size_t total_pokemones = obtener_cantidad_pokemones(pokedex);
	size_t indice_aleatorio = (size_t)rand() % total_pokemones;

	abb_t *arbol_pokemones = obtener_arbol_pokemones(pokedex);
	pokemon_t *pokemon =
		obtener_pokemon_por_indice(arbol_pokemones, indice_aleatorio);
	if (!pokemon)
		return;

	int x = generar_posicion_aleatoria(0, MAX_X - 1);
	int y = generar_posicion_aleatoria(0, MAX_Y - 1);
	asignar_x_pokemon(pokemon, x);
	asignar_y_pokemon(pokemon, y);

	pokemon_t *copia = copiar_pokemon(pokemon);
	if (!copia)
		return;

	if (abb_insertar(pokemones_en_juego, copia)) {
		ubicar_en_tablero(pokemon, tablero);
	} else {
		liberar_pokemon(copia);
	}
}

void ubicar_pokemones_aleatorios(pokedex_t *pokedex, char **tablero,
				 abb_t *pokemones_en_juego)
{
	if (!pokedex || !tablero || !pokemones_en_juego)
		return;

	for (size_t i = 0; i < CANTIDAD_POKEMONES_JUEGO; i++) {
		ubicar_aleatorio(pokedex, tablero, pokemones_en_juego);
	}
}

void imprimir_pokedex(void *contexto)
{
	if (!contexto) {
		return;
	}

	pokedex_t *pokedex = (pokedex_t *)contexto;
	mostrar_bienvenida();
	titulo_pokedex();
	printf("\t\t\t%-45s %-40s %-45s %-55s\n", "Nombre", "Puntos", "Color",
	       "Movimiento");
	mostrar_pokedex(pokedex);
}

void iniciar_juego(void *contexto)
{
	if (!contexto) {
		return;
	}

	(void)contexto;
	printf("Iniciando el juego 🎮\n");
}

void jugar_con_semilla(void *contexto)
{
	if (!contexto) {
		return;
	}

	unsigned int semilla;
	printf("Ingrese una semilla para iniciar el juego: ");
	int result = scanf("%u", &semilla);

	if (result != 1) {
		return;
	} else {
		printf("Iniciando el juego con semilla %u 🌱\n", semilla);
	}

	srand(semilla);
}

void realizar_movimiento_aleatorio(int x, int y)
{
	int movimiento = rand() % MOVIMIENTOS_SIMPLES_POSIBLES;

	switch (movimiento) {
	case 0:
		x--;
		break;
	case 1:
		x++;
		break;
	case 2:
		y++;
		break;
	case 3:
		y--;
		break;
	}
}

void vaciar_posicion_anterior_pokemon(pokemon_t *pokemon, char **tablero)
{
	if (!pokemon || !tablero) {
		return;
	}

	tablero[obtener_x_pokemon(pokemon)][obtener_y_pokemon(pokemon)] = ' ';
}

char **crear_tablero(size_t filas, size_t columnas)
{
	char **tablero = malloc(filas * sizeof(char *));
	for (size_t i = 0; i < filas; i++) {
		tablero[i] = malloc(columnas * sizeof(char));
	}
	return tablero;
}

void definir_tablero_vacio(char **tablero, size_t filas, size_t columnas)
{
	if (!tablero) {
		return;
	}

	for (size_t i = 0; i < filas; i++) {
		for (size_t j = 0; j < columnas; j++) {
			tablero[i][j] = ' ';
		}
	}
}

void imprimir_tablero(char **tablero, size_t filas, size_t columnas,
		      abb_t *pokemones)
{
	if (!tablero) {
		return;
	}

	for (size_t j = 0; j < columnas; j++) {
		printf("🌲 ");
	}
	printf("🌲🌲\n");

	for (size_t i = 0; i < filas; i++) {
		printf("🌲");

		for (size_t j = 0; j < columnas; j++) {
			char inicial = tablero[i][j];

			if (inicial == '\0' || inicial == ' ') {
				printf("   ");
			} else {
				pokemon_t *pokemon =
					buscar_pokemon_por_coordenadas(
						pokemones, i, j);

				if (pokemon) {
					char *codigo_color =
						devolver_codigo_color_pokemon(
							pokemon);
					if (codigo_color) {
						printf(" %s%c%s ", codigo_color,
						       inicial,
						       ANSI_COLOR_RESET);
					} else {
						printf(" %c ", inicial);
					}
				} else {
					printf(" %c ", inicial);
				}
			}
		}

		printf("🌲\n");
	}

	for (size_t j = 0; j < columnas; j++) {
		printf("🌲 ");
	}
	printf("🌲🌲\n");
}

void destruir_tablero(char **tablero, size_t filas)
{
	if (!tablero) {
		return;
	}

	for (size_t i = 0; i < filas; i++) {
		free(tablero[i]);
	}
	free(tablero);
}

void ubicar_jugador(char **tablero, size_t x, size_t y)
{
	if (!tablero) {
		return;
	}

	tablero[x][y] = 'J';
}

void mostrar_ultimo_capturado(jugador_t *jugador)
{
	if (!jugador) {
		return;
	}

	pokemon_t *pokemon = obtener_ultimo_capturado_jugador(jugador);
	if (!pokemon) {
		printf("\nNo se ha capturado ningún pokémon aún.\n");
		return;
	}

	printf("\nÚltimo pokémon capturado: %s\n",
	       obtener_nombre_pokemon(pokemon));
}

void cargar_acciones_menu(menu_t *menu)
{
	if (!menu) {
		return;
	}

	accion_t *accion_mostrar_pokedex = accion_crear('P', imprimir_pokedex);
	menu_agregar_accion(menu, accion_mostrar_pokedex);

	accion_t *accion_jugar = accion_crear('J', iniciar_juego);
	menu_agregar_accion(menu, accion_jugar);

	accion_t *accion_jugar_semilla = accion_crear('S', jugar_con_semilla);
	menu_agregar_accion(menu, accion_jugar_semilla);
}

void mover_pokemon(pokemon_t *pokemon, char **tablero, int entrada)
{
	if (!pokemon || !tablero) {
		return;
	}

	char *movimientos = obtener_movimientos_pokemon(pokemon);
	int cantidad_movimientos =
		obtener_cantidad_movimientos_pokemon(pokemon);

	int x = obtener_x_pokemon(pokemon);
	int y = obtener_y_pokemon(pokemon);

	vaciar_posicion_anterior_pokemon(pokemon, tablero);

	for (int i = 0; i < cantidad_movimientos; i++) {
		if (movimientos[i] == ARRIBA) {
			x--;
		} else if (movimientos[i] == ABAJO) {
			x++;
		} else if (movimientos[i] == DERECHA) {
			y++;
		} else if (movimientos[i] == IZQUIERDA) {
			y--;
		} else if (movimientos[i] == INVERTIDO) {
			if (entrada == TECLA_ARRIBA) {
				x++;
			} else if (entrada == TECLA_ABAJO) {
				x--;
			} else if (entrada == TECLA_DERECHA) {
				y--;
			} else if (entrada == TECLA_IZQUIERDA) {
				y++;
			}
		} else if (movimientos[i] == JUGADOR) {
			if (entrada == TECLA_ARRIBA) {
				x--;
			} else if (entrada == TECLA_ABAJO) {
				x++;
			} else if (entrada == TECLA_DERECHA) {
				y++;
			} else if (entrada == TECLA_IZQUIERDA) {
				y--;
			}
		} else if (movimientos[i] == RANDOM) {
			int direccion = rand() % MOVIMIENTOS_SIMPLES_POSIBLES;
			if (direccion == 0)
				x--;
			else if (direccion == 1)
				x++;
			else if (direccion == 2)
				y++;
			else if (direccion == 3)
				y--;
		}
	}

	x = min(MAXIMA_FILA, max(0, x));
	y = min(MAXIMA_COLUMNA, max(0, y));

	asignar_x_pokemon(pokemon, x);
	asignar_y_pokemon(pokemon, y);

	ubicar_en_tablero(pokemon, tablero);
}

void ubicar_actualizados(pokemon_t *pokemon, ctx *contexto)
{
	if (!pokemon || !contexto) {
		return;
	}

	mover_pokemon(pokemon, contexto->tablero, contexto->entrada);
	ubicar_en_tablero(pokemon, contexto->tablero);
}

void mover_pokemones(char **tablero, abb_t *pokemones_en_juego, int entrada)
{
	if (!tablero || !pokemones_en_juego) {
		return;
	}
	ctx contexto = { tablero, entrada };
	abb_iterar_inorden(pokemones_en_juego,
			   (bool (*)(void *, void *))ubicar_actualizados,
			   &contexto);
}

bool generar_si_capture(void *elemento, void *ctx)
{
	if (!elemento || !ctx) {
		return false;
	}

	struct contexto_captura *contexto = (struct contexto_captura *)ctx;
	pokemon_t *pokemon = (pokemon_t *)elemento;

	if (obtener_x_pokemon(pokemon) ==
		    obtener_x_jugador(contexto->jugador) &&
	    obtener_y_pokemon(pokemon) ==
		    obtener_y_jugador(contexto->jugador)) {
		contexto->pokemon_capturado = pokemon;

		pokemon_t *ultimo_capturado =
			obtener_ultimo_capturado_jugador(contexto->jugador);
		if (ultimo_capturado) {
			if (obtener_inicial_pokemon(pokemon) ==
				    obtener_inicial_pokemon(ultimo_capturado) ||
			    strcmp(obtener_color_pokemon(pokemon),
				   obtener_color_pokemon(ultimo_capturado)) ==
				    0) {
				incrementar_multiplicador_jugador(
					contexto->jugador, pokemon);
			} else {
				resetear_multiplicador_jugador(
					contexto->jugador);
			}
		}

		sumar_puntos_jugador(contexto->jugador, pokemon);

		actualizar_ultimo_capturado(contexto->jugador, pokemon);

		if (!lista_agregar_al_final(contexto->pokemones_capturados,
					    pokemon)) {
			fprintf(stderr,
				"Error al agregar Pokémon a la lista de eliminación\n");
		}

		ubicar_aleatorio(contexto->pokedex, contexto->tablero,
				 contexto->pokemones_en_juego);
	}

	return true;
}

void capturar_pokemones(jugador_t *jugador, abb_t *pokemones_en_juego,
			pokedex_t *pokedex, char **tablero)
{
	if (!jugador || !pokemones_en_juego || !pokedex || !tablero)
		return;

	Lista *pokemones_capturados = lista_crear();
	if (!pokemones_capturados)
		return;

	struct contexto_captura contexto = {
		.jugador = jugador,
		.pokedex = pokedex,
		.tablero = tablero,
		.pokemones_en_juego = pokemones_en_juego,
		.pokemones_capturados = pokemones_capturados,
		.pokemon_capturado = NULL
	};

	abb_iterar_inorden(pokemones_en_juego, generar_si_capture, &contexto);

	size_t cantidad_eliminados =
		lista_cantidad_elementos(pokemones_capturados);
	for (size_t i = 0; i < cantidad_eliminados; i++) {
		pokemon_t *capturado = NULL;
		if (!lista_quitar_elemento(pokemones_capturados, 0,
					   (void **)&capturado))
			continue;

		abb_quitar(pokemones_en_juego, capturado, NULL);
		liberar_pokemon(capturado);
	}

	lista_destruir(pokemones_capturados);
}