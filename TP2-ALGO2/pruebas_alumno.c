#include "pa2m.h"
#include "src/menu.h"
#include "src/pokedex.h"
#include "src/csv.h"
#include "src/jugador.h"
#include "src/logica.h"
#include "extra/ansi.h"

#include <string.h>

void auxiliar_accion(void *contexto)
{
	(void)contexto;
}

/*MENU*/

void menuSeCreaCorrectamente()
{
	menu_t *menu = crear_menu();
	pa2m_afirmar(menu != NULL, "El menu se crea correctamente");
	destruir_menu(menu);
}

void menuNuloNoSePuedeAgregarAccion()
{
	menu_t *menu = NULL;
	accion_t *accion = accion_crear('a', auxiliar_accion);
	pa2m_afirmar(!menu_agregar_accion(menu, accion),
		     "El menu nulo no se puede agregar accion");
	destruir_accion(accion);
}

void menuSeDestruyeCorrectamente()
{
	menu_t *menu = crear_menu();
	destruir_menu(menu);
	pa2m_afirmar(1, "El menu se destruye correctamente");
}

void menuSeAgregaAccionMultipleVeces()
{
	menu_t *menu = crear_menu();
	accion_t *accion1 = accion_crear('a', auxiliar_accion);
	accion_t *accion2 = accion_crear('b', auxiliar_accion);
	pa2m_afirmar(menu_agregar_accion(menu, accion1),
		     "La primera accion se agrega correctamente");
	pa2m_afirmar(menu_agregar_accion(menu, accion2),
		     "La segunda accion se agrega correctamente");
	destruir_menu(menu);
}

void accionSeCreaCorrectamente()
{
	accion_t *accion = accion_crear('a', auxiliar_accion);
	pa2m_afirmar(accion != NULL, "La accion se crea correctamente");
	destruir_accion(accion);
}

void accionSeAgregaCorrectamente()
{
	menu_t *menu = crear_menu();
	accion_t *accion = accion_crear('a', auxiliar_accion);
	pa2m_afirmar(menu_agregar_accion(menu, accion),
		     "La accion se agrega correctamente");
	destruir_menu(menu);
}

void accionNulaNoSePuedeAgregar()
{
	menu_t *menu = crear_menu();
	pa2m_afirmar(!menu_agregar_accion(menu, NULL),
		     "La accion nula no se agrega correctamente");
	destruir_menu(menu);
}

void accionSeDestruyeCorrectamente()
{
	accion_t *accion = accion_crear('a', auxiliar_accion);
	destruir_accion(accion);
	pa2m_afirmar(1, "La accion se destruye correctamente");
}

/*--------------------------------------*/

/*Pokedex*/

void pokedexSeCreaCorrectamente()
{
	pokedex_t *pokedex = crear_pokedex();
	pa2m_afirmar(pokedex != NULL, "El pokedex se crea correctamente");
	destruir_pokedex(pokedex);
}

void pokedexSeCargaCorrectamente()
{
	pokedex_t *pokedex = crear_pokedex();
	struct archivo_csv *archivo =
		abrir_archivo_csv("datos/pokedex.csv", ',');
	cargar_pokedex(pokedex, archivo);
	pa2m_afirmar(1, "El pokedex se carga correctamente");
	cerrar_archivo_csv(archivo);
	destruir_pokedex(pokedex);
}

void pokedexSeMuestraCorrectamente()
{
	pokedex_t *pokedex = crear_pokedex();
	struct archivo_csv *archivo =
		abrir_archivo_csv("datos/pokedex.csv", ',');
	cargar_pokedex(pokedex, archivo);
	mostrar_pokedex(pokedex);
	pa2m_afirmar(1, "El pokedex se muestra correctamente");
	cerrar_archivo_csv(archivo);
	destruir_pokedex(pokedex);
}

void pokedexSeObtieneCantidadCorrectamente()
{
	pokedex_t *pokedex = crear_pokedex();
	struct archivo_csv *archivo =
		abrir_archivo_csv("datos/pokedex.csv", ',');
	cargar_pokedex(pokedex, archivo);
	size_t cantidad = obtener_cantidad_pokemones(pokedex);
	pa2m_afirmar(cantidad == 10,
		     "La cantidad de una pokedex con 10 pokemones es correcta");
	cerrar_archivo_csv(archivo);
	destruir_pokedex(pokedex);
}

void pokedexVaciaSeObtieneCantidadCorrectamente()
{
	pokedex_t *pokedex = crear_pokedex();
	size_t cantidad = obtener_cantidad_pokemones(pokedex);
	pa2m_afirmar(
		cantidad == 0,
		"La cantidad de pokemones en una pokedex vacia es correcta");
	destruir_pokedex(pokedex);
}

void pokedexNulaSeObtieneCantidadCorrectamente()
{
	pokedex_t *pokedex = NULL;
	size_t cantidad = obtener_cantidad_pokemones(pokedex);
	pa2m_afirmar(cantidad == 0,
		     "La cantidad de pokemones en una pokedex nula es cero");
}

void pokedexSeObtieneArbolCorrectamente()
{
	pokedex_t *pokedex = crear_pokedex();
	struct archivo_csv *archivo =
		abrir_archivo_csv("datos/pokedex.csv", ',');
	cargar_pokedex(pokedex, archivo);
	abb_t *abb = obtener_arbol_pokemones(pokedex);
	pa2m_afirmar(abb != NULL,
		     "El arbol de pokemones se obtiene correctamente");
	cerrar_archivo_csv(archivo);
	destruir_pokedex(pokedex);
}

void pokedexSeObtieneArbolVacioCorrectamente()
{
	pokedex_t *pokedex = crear_pokedex();
	abb_t *abb = obtener_arbol_pokemones(pokedex);
	pa2m_afirmar(abb != NULL,
		     "El arbol de pokemones se obtiene correctamente");
	destruir_pokedex(pokedex);
}

void pokedexSeDestruyeCorrectamente()
{
	pokedex_t *pokedex = crear_pokedex();
	destruir_pokedex(pokedex);
	pa2m_afirmar(1, "El pokedex se destruye correctamente");
}

/*--------------------------------------*/

/*Pokemon*/

void pokemonSeCreaCorrectamente()
{
	pokemon_t *pokemon =
		crear_pokemon("Pikachu", 100, "amarillo", "NSJ", 25);
	pa2m_afirmar(pokemon != NULL, "El pokemon se crea correctamente");
	liberar_pokemon(pokemon);
}

void pokemonNombreNuloNoSePuedeCrear()
{
	pokemon_t *pokemon = crear_pokemon(NULL, 100, "amarillo", "NSJ", 25);
	pa2m_afirmar(pokemon == NULL,
		     "El pokemon con nombre nulo no se puede crear");
}

void pokemonColorNuloNoSePuedeCrear()
{
	pokemon_t *pokemon = crear_pokemon("Pikachu", 100, NULL, "NSJ", 25);
	pa2m_afirmar(pokemon == NULL,
		     "El pokemon con color nulo no se puede crear");
}

void pokemonMovimientosNuloNoSePuedeCrear()
{
	pokemon_t *pokemon =
		crear_pokemon("Pikachu", 100, "amarillo", NULL, 25);
	pa2m_afirmar(pokemon == NULL,
		     "El pokemon con movimientos nulos no se puede crear");
}

void pokemonNuloNoSePuedeCopiar()
{
	pokemon_t *pokemon = NULL;
	pokemon_t *copia = copiar_pokemon(pokemon);
	pa2m_afirmar(copia == NULL, "El pokemon nulo no se puede copiar");
}

void pokemonSeCopiaCorrectamente()
{
	pokemon_t *pokemon =
		crear_pokemon("Pikachu", 100, "amarillo", "NSJ", 25);
	pokemon_t *copia = copiar_pokemon(pokemon);
	pa2m_afirmar(copia != NULL, "El pokemon se copia correctamente");
	liberar_pokemon(pokemon);
	liberar_pokemon(copia);
}

void pokemonSeObtieneInicialCorrectamente()
{
	pokemon_t *pokemon =
		crear_pokemon("Pikachu", 100, "amarillo", "NSJ", 25);
	char inicial = obtener_inicial_pokemon(pokemon);
	pa2m_afirmar(inicial == 'P', "La inicial del pokemon es correcta");
	liberar_pokemon(pokemon);
}

void pokemonNuloNoSePuedeObtenerInicial()
{
	pokemon_t *pokemon = NULL;
	char inicial = obtener_inicial_pokemon(pokemon);
	pa2m_afirmar(inicial == '\0', "La inicial de un pokemon nulo es nula");
}

void pokemonSeObtieneCodigoColorCorrectamente()
{
	pokemon_t *pokemon =
		crear_pokemon("Pikachu", 100, "AMARILLO", "NROS", 25);
	char *codigo = devolver_codigo_color_pokemon(pokemon);
	pa2m_afirmar(strcmp(codigo, ANSI_COLOR_YELLOW) == 0,
		     "El código de color del pokemon es correcto");
	liberar_pokemon(pokemon);
}

void pokemonNuloNoSePuedeObtenerCodigoColor()
{
	pokemon_t *pokemon = NULL;
	char *codigo = devolver_codigo_color_pokemon(pokemon);
	pa2m_afirmar(codigo == NULL,
		     "El código de color de un pokemon nulo es nulo");
}

void pokemonSeObtieneXCorrectamente()
{
	pokemon_t *pokemon =
		crear_pokemon("Pikachu", 100, "amarillo", "NSJ", 25);
	asignar_x_pokemon(pokemon, 0);
	int x = obtener_x_pokemon(pokemon);
	pa2m_afirmar(x == 0, "La coordenada x del pokemon es correcta");
	liberar_pokemon(pokemon);
}

void pokemonSeObtieneYCorrectamente()
{
	pokemon_t *pokemon =
		crear_pokemon("Pikachu", 100, "amarillo", "NSJ", 25);
	asignar_y_pokemon(pokemon, 0);
	int y = obtener_y_pokemon(pokemon);
	pa2m_afirmar(y == 0, "La coordenada y del pokemon es correcta");
	liberar_pokemon(pokemon);
}

void pokemonNuloNoSePuedeObtenerX()
{
	pokemon_t *pokemon = NULL;
	int x = obtener_x_pokemon(pokemon);
	pa2m_afirmar(x == -1, "La coordenada x de un pokemon nulo es -1");
}

void pokemonNuloNoSePuedeObtenerY()
{
	pokemon_t *pokemon = NULL;
	int y = obtener_y_pokemon(pokemon);
	pa2m_afirmar(y == -1, "La coordenada y de un pokemon nulo es -1");
}

void pokemonSeObtieneIndiceCorrectamente()
{
	pokemon_t *pokemon =
		crear_pokemon("Pikachu", 100, "amarillo", "NSJ", 25);
	int indice = obtener_indice_pokemon(pokemon);
	pa2m_afirmar(indice == 25, "El indice del pokemon es correcto");
	liberar_pokemon(pokemon);
}

void pokemonNuloNoSePuedeObtenerIndice()
{
	pokemon_t *pokemon = NULL;
	int indice = obtener_indice_pokemon(pokemon);
	pa2m_afirmar(indice == -1, "El indice de un pokemon nulo es -1");
}

void pokemonSeObtienePuntosCorrectamente()
{
	pokemon_t *pokemon =
		crear_pokemon("Pikachu", 100, "amarillo", "NSJ", 25);
	int puntos = obtener_puntos_pokemon(pokemon);
	pa2m_afirmar(puntos == 100, "Los puntos del pokemon son correctos");
	liberar_pokemon(pokemon);
}

void pokemonNuloNoSePuedeObtenerPuntos()
{
	pokemon_t *pokemon = NULL;
	int puntos = obtener_puntos_pokemon(pokemon);
	pa2m_afirmar(puntos == -1, "Los puntos de un pokemon nulo son -1");
}

void pokemonSeAsignaXCorrectamente()
{
	pokemon_t *pokemon =
		crear_pokemon("Pikachu", 100, "amarillo", "NSJ", 25);
	asignar_x_pokemon(pokemon, 5);
	int x = obtener_x_pokemon(pokemon);
	pa2m_afirmar(x == 5,
		     "La coordenada x del pokemon se asigna correctamente");
	liberar_pokemon(pokemon);
}

void pokemonNuloNoSePuedeAsignarX()
{
	pokemon_t *pokemon = NULL;
	asignar_x_pokemon(pokemon, 5);
	int x = obtener_x_pokemon(pokemon);
	pa2m_afirmar(
		x == -1,
		"La coordenada x de un pokemon nulo se mantiene en -1 incluso si se quiere asignar una nueva");
}

void pokemonSeAsignaYCorrectamente()
{
	pokemon_t *pokemon =
		crear_pokemon("Pikachu", 100, "amarillo", "NSJ", 25);
	asignar_y_pokemon(pokemon, 5);
	int y = obtener_y_pokemon(pokemon);
	pa2m_afirmar(y == 5,
		     "La coordenada y del pokemon se asigna correctamente");
	liberar_pokemon(pokemon);
}

void pokemonNuloNoSePuedeAsignarY()
{
	pokemon_t *pokemon = NULL;
	asignar_y_pokemon(pokemon, 5);
	int y = obtener_y_pokemon(pokemon);
	pa2m_afirmar(
		y == -1,
		"La coordenada y de un pokemon nulo se mantiene en -1 incluso si se quiere asignar una nueva");
}

void pokemonSeObtienePorIndiceCorrectamente()
{
	pokedex_t *pokedex = crear_pokedex();
	struct archivo_csv *archivo =
		abrir_archivo_csv("datos/pokedex.csv", ',');
	cargar_pokedex(pokedex, archivo);
	abb_t *pokemones = obtener_arbol_pokemones(pokedex);
	pokemon_t *pokemon = obtener_pokemon_por_indice(
		pokemones, obtener_cantidad_pokemones(pokedex) - 1);
	pa2m_afirmar(pokemon != NULL,
		     "El pokemon se obtiene por indice correctamente");
	cerrar_archivo_csv(archivo);
	destruir_pokedex(pokedex);
}

void noSePuedeObtenerPokemonPorIndiceEnArbolNulo()
{
	abb_t *pokemones = NULL;
	pokemon_t *pokemon = obtener_pokemon_por_indice(pokemones, 0);
	pa2m_afirmar(
		pokemon == NULL,
		"No se puede obtener un pokemon por indice en un arbol nulo");
}

void pokemonSeBuscaPorCoordenadasCorrectamente()
{
	pokedex_t *pokedex = crear_pokedex();
	struct archivo_csv *archivo =
		abrir_archivo_csv("datos/pokedex.csv", ',');
	cargar_pokedex(pokedex, archivo);
	abb_t *pokemones = obtener_arbol_pokemones(pokedex);
	pokemon_t *pokemon = buscar_pokemon_por_coordenadas(pokemones, 16, 33);
	pa2m_afirmar(pokemon != NULL,
		     "El pokemon se busca por coordenadas correctamente");
	cerrar_archivo_csv(archivo);
	destruir_pokedex(pokedex);
}

void noSePuedeBuscarPokemonEnArbolNulo()
{
	abb_t *pokemones = NULL;
	pokemon_t *pokemon = buscar_pokemon_por_coordenadas(pokemones, 0, 0);
	pa2m_afirmar(pokemon == NULL,
		     "No se puede buscar un pokemon en un arbol nulo");
}

void pokemonSeObtieneMovimientosCorrectamente()
{
	pokemon_t *pokemon =
		crear_pokemon("Pikachu", 100, "amarillo", "NSJ", 25);
	char *movimientos = obtener_movimientos_pokemon(pokemon);
	pa2m_afirmar(strcmp(movimientos, "NSJ") == 0,
		     "Los movimientos del pokemon son correctos");
	liberar_pokemon(pokemon);
}

void pokemonNuloNoSePuedeObtenerMovimientos()
{
	pokemon_t *pokemon = NULL;
	char *movimientos = obtener_movimientos_pokemon(pokemon);
	pa2m_afirmar(movimientos == NULL,
		     "Los movimientos de un pokemon nulo son nulos");
}

void pokemonSeObtieneCantidadMovimientosCorrectamente()
{
	pokemon_t *pokemon =
		crear_pokemon("Pikachu", 100, "amarillo", "NSJ", 25);
	int cantidad = obtener_cantidad_movimientos_pokemon(pokemon);
	pa2m_afirmar(cantidad == 3,
		     "La cantidad de movimientos del pokemon es correcta");
	liberar_pokemon(pokemon);
}

void pokemonNuloNoSePuedeObtenerCantidadMovimientos()
{
	pokemon_t *pokemon = NULL;
	int cantidad = obtener_cantidad_movimientos_pokemon(pokemon);
	pa2m_afirmar(cantidad == -1,
		     "La cantidad de movimientos de un pokemon nulo es -1");
}

void pokemonSeObtieneNombreCorrectamente()
{
	pokemon_t *pokemon =
		crear_pokemon("Pikachu", 100, "amarillo", "NSJ", 25);
	char *nombre = obtener_nombre_pokemon(pokemon);
	pa2m_afirmar(strcmp(nombre, "Pikachu") == 0,
		     "El nombre del pokemon es correcto");
	liberar_pokemon(pokemon);
}

void pokemonNuloNoSePuedeObtenerNombre()
{
	pokemon_t *pokemon = NULL;
	char *nombre = obtener_nombre_pokemon(pokemon);
	pa2m_afirmar(nombre == NULL, "El nombre de un pokemon nulo es nulo");
}

void pokemonSeObtieneColorCorrectamente()
{
	pokemon_t *pokemon =
		crear_pokemon("Pikachu", 100, "amarillo", "NSJ", 25);
	char *color = obtener_color_pokemon(pokemon);
	pa2m_afirmar(strcmp(color, "amarillo") == 0,
		     "El color del pokemon es correcto");
	liberar_pokemon(pokemon);
}

void pokemonNuloNoSePuedeObtenerColor()
{
	pokemon_t *pokemon = NULL;
	char *color = obtener_color_pokemon(pokemon);
	pa2m_afirmar(color == NULL, "El color de un pokemon nulo es nulo");
}

void pokemonSeImprimeCorrectamente()
{
	pokemon_t *pokemon =
		crear_pokemon("Pikachu", 100, "amarillo", "NSJ", 25);
	imprimir_pokemon(pokemon);
	pa2m_afirmar(1, "El pokemon se imprime correctamente");
	liberar_pokemon(pokemon);
}

void pokemonSeComparaCorrectamente()
{
	pokemon_t *pokemon1 =
		crear_pokemon("Pikachu", 100, "amarillo", "NSJ", 25);
	pokemon_t *pokemon2 =
		crear_pokemon("Charmander", 100, "rojo", "lanzallamas", 4);
	int comparacion = comparar_pokemon(pokemon1, pokemon2);
	pa2m_afirmar(comparacion > 0,
		     "La comparacion de pokemones es correcta");
	liberar_pokemon(pokemon1);
	liberar_pokemon(pokemon2);
}

void noPuedoCompararDosNulos()
{
	pokemon_t *pokemon1 = NULL;
	pokemon_t *pokemon2 = NULL;
	int comparacion = comparar_pokemon(pokemon1, pokemon2);
	pa2m_afirmar(comparacion == -1,
		     "La comparacion de dos pokemones nulos es -1");
}

void pokemonSeLiberaCorrectamente()
{
	pokemon_t *pokemon =
		crear_pokemon("Pikachu", 100, "amarillo", "NSJ", 25);
	liberar_pokemon(pokemon);
	pa2m_afirmar(1, "El pokemon se libera correctamente");
}

/*-----------------------------------*/

/*Jugador*/

void jugadorSeCreaCorrectamente()
{
	jugador_t *jugador = crear_jugador();
	pa2m_afirmar(jugador != NULL, "El jugador se crea correctamente");
	destruir_jugador(jugador);
}

void jugadorSeSumanPuntosCorrectamente()
{
	jugador_t *jugador = crear_jugador();
	pokemon_t *pokemon =
		crear_pokemon("Pikachu", 100, "amarillo", "NSJ", 25);
	sumar_puntos_jugador(jugador, pokemon);
	int puntos = obtener_puntos_jugador(jugador);
	pa2m_afirmar(puntos == 100,
		     "Los puntos del jugador se suman correctamente");
	destruir_jugador(jugador);
	liberar_pokemon(pokemon);
}

void noSePuedenSumarPuntosConPokemonNulo()
{
	jugador_t *jugador = crear_jugador();
	pokemon_t *pokemon = NULL;
	sumar_puntos_jugador(jugador, pokemon);
	int puntos = obtener_puntos_jugador(jugador);
	pa2m_afirmar(puntos == 0,
		     "No se pueden sumar puntos con un pokemon nulo");
	destruir_jugador(jugador);
}

void jugadorSeIncrementanIteracionesCorrectamente()
{
	jugador_t *jugador = crear_jugador();
	incrementar_iteraciones_jugador(jugador);
	int iteraciones = obtener_iteraciones_jugador(jugador);
	pa2m_afirmar(
		iteraciones == 1,
		"Las iteraciones del jugador se incrementan correctamente");
	destruir_jugador(jugador);
}

void noSePuedenIncrementarIteracionesConJugadorNulo()
{
	jugador_t *jugador = NULL;
	incrementar_iteraciones_jugador(jugador);
	int iteraciones = obtener_iteraciones_jugador(jugador);
	pa2m_afirmar(
		iteraciones == -1,
		"No se pueden incrementar las iteraciones con un jugador nulo");
}

void jugadorSeObtieneXCorrectamente()
{
	jugador_t *jugador = crear_jugador();
	int x = obtener_x_jugador(jugador);
	pa2m_afirmar(x == 0, "La coordenada x del jugador es correcta");
	destruir_jugador(jugador);
}

void noSePuedeObtenerXConJugadorNulo()
{
	jugador_t *jugador = NULL;
	int x = obtener_x_jugador(jugador);
	pa2m_afirmar(x == -1, "La coordenada x de un jugador nulo es -1");
}

void jugadorSeObtieneYCorrectamente()
{
	jugador_t *jugador = crear_jugador();
	int y = obtener_y_jugador(jugador);
	pa2m_afirmar(y == 0, "La coordenada y del jugador es correcta");
	destruir_jugador(jugador);
}

void noSePuedeObtenerYConJugadorNulo()
{
	jugador_t *jugador = NULL;
	int y = obtener_y_jugador(jugador);
	pa2m_afirmar(y == -1, "La coordenada y de un jugador nulo es -1");
}

void jugadorSeObtienePuntosCorrectamente()
{
	jugador_t *jugador = crear_jugador();
	int puntos = obtener_puntos_jugador(jugador);
	pa2m_afirmar(puntos == 0, "Los puntos del jugador son correctos");
	destruir_jugador(jugador);
}

void noSePuedeObtenerPuntosConJugadorNulo()
{
	jugador_t *jugador = NULL;
	int puntos = obtener_puntos_jugador(jugador);
	pa2m_afirmar(puntos == -1, "Los puntos de un jugador nulo son -1");
}

void jugadorSeObtieneMovimientosCorrectamente()
{
	jugador_t *jugador = crear_jugador();
	int movimientos = obtener_movimientos_jugador(jugador);
	pa2m_afirmar(movimientos == 0,
		     "Los movimientos del jugador son correctos");
	destruir_jugador(jugador);
}

void noSePuedeObtenerMovimientosConJugadorNulo()
{
	jugador_t *jugador = NULL;
	int movimientos = obtener_movimientos_jugador(jugador);
	pa2m_afirmar(movimientos == -1,
		     "Los movimientos de un jugador nulo son -1");
}

void jugadorSeObtieneIteracionesCorrectamente()
{
	jugador_t *jugador = crear_jugador();
	int iteraciones = obtener_iteraciones_jugador(jugador);
	pa2m_afirmar(iteraciones == 0,
		     "Las iteraciones del jugador son correctas");
	destruir_jugador(jugador);
}

void noSePuedeObtenerIteracionesConJugadorNulo()
{
	jugador_t *jugador = NULL;
	int iteraciones = obtener_iteraciones_jugador(jugador);
	pa2m_afirmar(iteraciones == -1,
		     "Las iteraciones de un jugador nulo son -1");
}

void jugadorSeObtieneMultiplicadorCorrectamente()
{
	jugador_t *jugador = crear_jugador();
	int multiplicador = obtener_multiplicador_jugador(jugador);
	pa2m_afirmar(multiplicador == 1,
		     "El multiplicador del jugador es correcto");
	destruir_jugador(jugador);
}

void noSePuedeObtenerMultiplicadorConJugadorNulo()
{
	jugador_t *jugador = NULL;
	int multiplicador = obtener_multiplicador_jugador(jugador);
	pa2m_afirmar(multiplicador == -1,
		     "El multiplicador de un jugador nulo es -1");
}

void jugadorSeIncrementaMultiplicadorCorrectamente()
{
	jugador_t *jugador = crear_jugador();
	pokemon_t *pokemon =
		crear_pokemon("Pikachu", 100, "amarillo", "NSJ", 25);
	incrementar_multiplicador_jugador(jugador, pokemon);
	int multiplicador = obtener_multiplicador_jugador(jugador);
	pa2m_afirmar(
		multiplicador == 2,
		"El multiplicador del jugador se incrementa correctamente");
	destruir_jugador(jugador);
	liberar_pokemon(pokemon);
}

void jugadorSeReseteaMultiplicadorCorrectamente()
{
	jugador_t *jugador = crear_jugador();
	pokemon_t *pokemon =
		crear_pokemon("Pikachu", 100, "amarillo", "NSJ", 25);
	incrementar_multiplicador_jugador(jugador, pokemon);
	resetear_multiplicador_jugador(jugador);
	int multiplicador = obtener_multiplicador_jugador(jugador);
	pa2m_afirmar(multiplicador == 1,
		     "El multiplicador del jugador se resetea correctamente");
	destruir_jugador(jugador);
	liberar_pokemon(pokemon);
}

void jugadorSeObtieneMultiplicadorMasAltoCorrectamente()
{
	jugador_t *jugador = crear_jugador();
	pokemon_t *pokemon =
		crear_pokemon("Pikachu", 100, "amarillo", "NSJ", 25);
	incrementar_multiplicador_jugador(jugador, pokemon);
	int multiplicador = obtener_multiplicador_mas_alto_jugador(jugador);
	pa2m_afirmar(multiplicador == 2,
		     "El multiplicador mas alto del jugador es correcto");
	destruir_jugador(jugador);
	liberar_pokemon(pokemon);
}

void noSePuedeObtenerMultiplicadorMasAltoConJugadorNulo()
{
	jugador_t *jugador = NULL;
	int multiplicador = obtener_multiplicador_mas_alto_jugador(jugador);
	pa2m_afirmar(multiplicador == -1,
		     "El multiplicador mas alto de un jugador nulo es -1");
}

void jugadorSeObtieneUltimoCapturadoCorrectamente()
{
	jugador_t *jugador = crear_jugador();
	pokemon_t *pokemon =
		crear_pokemon("Pikachu", 100, "amarillo", "NSJ", 25);
	actualizar_ultimo_capturado(jugador, pokemon);
	pokemon_t *ultimo = obtener_ultimo_capturado_jugador(jugador);
	pa2m_afirmar(ultimo != NULL,
		     "El ultimo pokemon capturado se obtiene correctamente");
	destruir_jugador(jugador);
	liberar_pokemon(pokemon);
}

void jugadorSeActualizaUltimoCapturadoCorrectamente()
{
	jugador_t *jugador = crear_jugador();
	pokemon_t *pokemon =
		crear_pokemon("Pikachu", 100, "amarillo", "NSJ", 25);
	actualizar_ultimo_capturado(jugador, pokemon);
	pokemon_t *ultimo = obtener_ultimo_capturado_jugador(jugador);
	pa2m_afirmar(ultimo != NULL,
		     "El ultimo pokemon capturado se actualiza correctamente");
	destruir_jugador(jugador);
	liberar_pokemon(pokemon);
}

void jugadorSeDestruyeCorrectamente()
{
	jugador_t *jugador = crear_jugador();
	destruir_jugador(jugador);
	pa2m_afirmar(1, "El jugador se destruye correctamente");
}

/*-----------------------------------*/

/*TERRENO*/

void tableroSeCreaCorrectamente()
{
	size_t filas = 5;
	size_t columnas = 5;
	char **tablero = crear_tablero(filas, columnas);

	pa2m_afirmar(tablero != NULL, "El tablero se crea correctamente");
	for (size_t i = 0; i < filas; i++) {
		pa2m_afirmar(tablero[i] != NULL,
			     "Cada fila del tablero se crea correctamente");
	}

	for (size_t j = 0; j < columnas; j++) {
		pa2m_afirmar(tablero[j] != NULL,
			     "Cada columna del tablero se crea correctamente");
	}

	destruir_tablero(tablero, filas);
}

void tableroSeDefineVacioCorrectamente()
{
	size_t filas = 5;
	size_t columnas = 5;
	char **tablero = crear_tablero(filas, columnas);
	definir_tablero_vacio(tablero, filas, columnas);

	int vacio = 1;
	for (size_t i = 0; i < filas && vacio; i++) {
		for (size_t j = 0; j < columnas && vacio; j++) {
			if (tablero[i][j] != ' ') {
				vacio = 0;
			}
		}
	}

	pa2m_afirmar(vacio, "El tablero se define como vacío correctamente");
	destruir_tablero(tablero, filas);
}

void tableroSeDestruyeCorrectamente()
{
	size_t filas = 5;
	size_t columnas = 5;
	char **tablero = crear_tablero(filas, columnas);

	destruir_tablero(tablero, filas);
	pa2m_afirmar(1, "El tablero se destruye correctamente");
}

void ubicarJugadorSeUbicaCorrectamente()
{
	size_t filas = 5, columnas = 5;
	char **tablero = crear_tablero(filas, columnas);
	definir_tablero_vacio(tablero, filas, columnas);
	size_t x = 2, y = 2;
	ubicar_jugador(tablero, x, y);
	pa2m_afirmar(tablero[x][y] == 'J',
		     "El jugador se ubica correctamente en el tablero");
	destruir_tablero(tablero, filas);
}

/*-----------------------------------*/

int main()
{
	pa2m_nuevo_grupo("============== Pruebas de menu ===============");
	menuSeCreaCorrectamente();
	menuNuloNoSePuedeAgregarAccion();
	menuSeAgregaAccionMultipleVeces();
	menuSeDestruyeCorrectamente();
	accionSeCreaCorrectamente();
	accionSeAgregaCorrectamente();
	accionNulaNoSePuedeAgregar();
	accionSeDestruyeCorrectamente();

	pa2m_nuevo_grupo("============== Pruebas de pokedex ===============");
	pokedexSeCreaCorrectamente();
	pokedexSeCargaCorrectamente();
	pokedexSeMuestraCorrectamente();
	pokedexSeObtieneCantidadCorrectamente();
	pokedexVaciaSeObtieneCantidadCorrectamente();
	pokedexNulaSeObtieneCantidadCorrectamente();
	pokedexSeObtieneArbolCorrectamente();
	pokedexSeObtieneArbolVacioCorrectamente();
	pokedexSeDestruyeCorrectamente();

	pa2m_nuevo_grupo("============== Pruebas de pokemon ===============");
	pokemonSeCreaCorrectamente();
	pokemonNombreNuloNoSePuedeCrear();
	pokemonColorNuloNoSePuedeCrear();
	pokemonMovimientosNuloNoSePuedeCrear();
	pokemonNuloNoSePuedeCopiar();
	pokemonSeCopiaCorrectamente();
	pokemonSeObtieneInicialCorrectamente();
	pokemonNuloNoSePuedeObtenerInicial();
	pokemonSeObtieneCodigoColorCorrectamente();
	pokemonNuloNoSePuedeObtenerCodigoColor();
	pokemonSeObtieneXCorrectamente();
	pokemonSeObtieneYCorrectamente();
	pokemonNuloNoSePuedeObtenerX();
	pokemonNuloNoSePuedeObtenerY();
	pokemonSeObtieneIndiceCorrectamente();
	pokemonNuloNoSePuedeObtenerIndice();
	pokemonSeObtienePuntosCorrectamente();
	pokemonNuloNoSePuedeObtenerPuntos();
	pokemonSeAsignaXCorrectamente();
	pokemonNuloNoSePuedeAsignarX();
	pokemonSeAsignaYCorrectamente();
	pokemonNuloNoSePuedeAsignarY();
	pokemonSeObtienePorIndiceCorrectamente();
	noSePuedeObtenerPokemonPorIndiceEnArbolNulo();
	pokemonSeBuscaPorCoordenadasCorrectamente();
	noSePuedeBuscarPokemonEnArbolNulo();
	pokemonSeObtieneMovimientosCorrectamente();
	pokemonSeObtieneCantidadMovimientosCorrectamente();
	pokemonNuloNoSePuedeObtenerMovimientos();
	pokemonSeObtieneNombreCorrectamente();
	pokemonNuloNoSePuedeObtenerNombre();
	pokemonSeObtieneColorCorrectamente();
	pokemonNuloNoSePuedeObtenerColor();
	pokemonSeImprimeCorrectamente();
	pokemonSeComparaCorrectamente();
	noPuedoCompararDosNulos();
	pokemonSeLiberaCorrectamente();

	pa2m_nuevo_grupo("============== Pruebas de jugador ===============");
	jugadorSeCreaCorrectamente();
	jugadorSeSumanPuntosCorrectamente();
	noSePuedenSumarPuntosConPokemonNulo();
	jugadorSeIncrementanIteracionesCorrectamente();
	noSePuedenIncrementarIteracionesConJugadorNulo();
	jugadorSeObtieneXCorrectamente();
	noSePuedeObtenerXConJugadorNulo();
	jugadorSeObtieneYCorrectamente();
	noSePuedeObtenerYConJugadorNulo();
	jugadorSeObtienePuntosCorrectamente();
	noSePuedeObtenerPuntosConJugadorNulo();
	jugadorSeObtieneMovimientosCorrectamente();
	noSePuedeObtenerMovimientosConJugadorNulo();
	jugadorSeObtieneIteracionesCorrectamente();
	jugadorSeObtieneMultiplicadorCorrectamente();
	noSePuedeObtenerMultiplicadorConJugadorNulo();
	jugadorSeIncrementaMultiplicadorCorrectamente();
	jugadorSeReseteaMultiplicadorCorrectamente();
	jugadorSeObtieneMultiplicadorMasAltoCorrectamente();
	noSePuedeObtenerMultiplicadorMasAltoConJugadorNulo();
	jugadorSeObtieneUltimoCapturadoCorrectamente();
	jugadorSeActualizaUltimoCapturadoCorrectamente();
	jugadorSeDestruyeCorrectamente();

	pa2m_nuevo_grupo(
		"============== Pruebas enfocadas en el terreno ===============");
	tableroSeCreaCorrectamente();
	tableroSeDefineVacioCorrectamente();
	tableroSeDestruyeCorrectamente();
	ubicarJugadorSeUbicaCorrectamente();

	return pa2m_mostrar_reporte();
}
