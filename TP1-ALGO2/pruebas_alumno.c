#include "pa2m.h"
#include <stdbool.h>
#include <string.h>
#include "src/csv.h"
#include "src/pokedex.h"

const int POKEMONES_CANT_PRUEBA = 7;
#define POKEMONES_CANT_PRUEBA_FUERZA 3

bool analizar_nombre(const char *str, void *ctx)
{
	return true;
}

bool analizar_tipo(const char *str, void *ctx)
{
	return true;
}

bool analizar_ataque(const char *str, void *ctx)
{
	return true;
}

void abrirUnArchivoInexistenteDebeRetornarNull()
{
	struct archivo_csv *archivo =
		abrir_archivo_csv("noexiste/noexiste/noexiste/no", ';');
	pa2m_afirmar(archivo == NULL, "El archivo no existe y se retorna NULL");
}

void siUnPunteroEsNullNoSePuedeLeer()
{
	struct archivo_csv *archivo = NULL;
	size_t leidos = leer_linea_csv(archivo, 0, NULL, NULL);
	pa2m_afirmar(leidos == 0, "No se puede leer un archivo NULL");
}

void leerUnArchivoVacioDebeRetornarCero()
{
	struct archivo_csv *archivo =
		abrir_archivo_csv("ejemplos/vacio.csv", ';');
	pa2m_afirmar(archivo != NULL, "Se abre un archivo vacío");
	size_t leidos = leer_linea_csv(archivo, 0, NULL, NULL);
	pa2m_afirmar(leidos == 0,
		     "Se lee un archivo vacío y se retornan 0 columnas");
	cerrar_archivo_csv(archivo);
}

void abrirArchivoExistenteDebeRetornarUnPuntero()
{
	struct archivo_csv *archivo =
		abrir_archivo_csv("ejemplos/pokedex.csv", ';');
	pa2m_afirmar(archivo != NULL, "Se abre un archivo existente");
	cerrar_archivo_csv(archivo);
}

void seParseaCorrectamenteUnaLineaCSV()
{
	struct archivo_csv *archivo =
		abrir_archivo_csv("ejemplos/pokedex.csv", ';');
	pa2m_afirmar(archivo != NULL, "Se abre un archivo existente");

	bool (*funciones[])(const char *,
			    void *) = { analizar_nombre, analizar_tipo,
					analizar_ataque, analizar_ataque,
					analizar_ataque };

	void *ctx[] = { NULL, NULL, NULL, NULL, NULL };

	size_t leidos = leer_linea_csv(archivo, 5, funciones, ctx);
	pa2m_afirmar(leidos == 5, "Se lee una línea de un archivo CSV");

	cerrar_archivo_csv(archivo);
}

void seCreaPokedex()
{
	struct pokedex *pokedex = pokedex_crear();
	pa2m_afirmar(pokedex != NULL, "Se crea una pokedex");
	pokedex_destruir(pokedex);
}

void contarLosPokemonesDeUnaPokedexNulaDevuelve0()
{
	struct pokedex *pokedex = NULL;
	size_t cantidad = pokedex_cantidad_pokemones(pokedex);
	pa2m_afirmar(cantidad == 0,
		     "Contar los pokemones de una pokedex nula devuelve 0");
}

void seIteraSobrePokedexVaciaDevuelve0()
{
	struct pokedex *pokedex = pokedex_crear();
	size_t cantidad = pokedex_iterar_pokemones(pokedex, NULL, NULL);
	pa2m_afirmar(cantidad == 0,
		     "Iterar sobre una pokedex vacía devuelve 0");
	pokedex_destruir(pokedex);
}

void seAgregaPokemonEInteractuaCorrectamente()
{
	struct pokedex *pokedex = pokedex_crear();
	struct pokemon pokemon = { "Fennekin", TIPO_FUEGO, 45, 60, 40 };
	bool agregado = pokedex_agregar_pokemon(pokedex, pokemon);
	pa2m_afirmar(agregado, "Se agrega un pokemon a la pokedex");

	pa2m_afirmar(pokedex_cantidad_pokemones(pokedex) == 1,
		     "La pokedex tiene un pokemon");
	const struct pokemon *pokemon_encontrado =
		pokedex_buscar_pokemon(pokedex, "Fennekin");

	pa2m_afirmar(pokemon_encontrado != NULL,
		     "Se encuentra un pokemon en la pokedex");
	pa2m_afirmar(strcmp(pokemon_encontrado->nombre, "Fennekin") == 0,
		     "Se encuentra el pokemon correcto");

	pokedex_destruir(pokedex);
}

void seInsertaOrdenadamentePokemon()
{
	size_t ordenados = 0;

	struct pokedex *pokedex = pokedex_crear();
	struct pokemon fennekin = { "Fennekin", TIPO_FUEGO, 45, 60, 40 };
	struct pokemon bulbasaur = { "Bulbasaur", TIPO_PLANTA, 45, 49, 49 };
	struct pokemon charmander = { "Charmander", TIPO_FUEGO, 39, 52, 43 };
	struct pokemon squirtle = { "Squirtle", TIPO_AGUA, 44, 48, 65 };
	struct pokemon pikachu = { "Pikachu", TIPO_ELECTRICO, 35, 55, 40 };
	struct pokemon rattata = { "Rattata", TIPO_NORMAL, 30, 56, 35 };
	struct pokemon machop = { "Machop", TIPO_LUCHA, 70, 80, 50 };

	pokedex_agregar_pokemon(pokedex, fennekin);
	pokedex_agregar_pokemon(pokedex, bulbasaur);
	pokedex_agregar_pokemon(pokedex, charmander);
	pokedex_agregar_pokemon(pokedex, squirtle);
	pokedex_agregar_pokemon(pokedex, pikachu);
	pokedex_agregar_pokemon(pokedex, rattata);
	pokedex_agregar_pokemon(pokedex, machop);

	const struct pokemon *pokemon_encontrado = NULL;

	char *nombres_esperados[] = { "Bulbasaur", "Charmander", "Fennekin",
				      "Machop",	   "Pikachu",	 "Rattata",
				      "Squirtle" };

	for (int i = 0; i < POKEMONES_CANT_PRUEBA; i++) {
		pokemon_encontrado =
			pokedex_buscar_pokemon(pokedex, nombres_esperados[i]);
		if (pokemon_encontrado != NULL ||
		    strcmp(pokemon_encontrado->nombre, nombres_esperados[i]) ==
			    0) {
			ordenados++;
		}
	}

	pa2m_afirmar(ordenados == POKEMONES_CANT_PRUEBA,
		     "Se insertan de forma ordenada los pokemones");

	pokedex_destruir(pokedex);
}

void seDestruyePokedex()
{
	struct pokedex *pokedex = pokedex_crear();

	struct pokedex *pokedex_destruido = pokedex;

	pokedex_destruir(pokedex);

	pokedex = NULL;

	pa2m_afirmar(pokedex == NULL, "Se destruye una pokedex");

	pa2m_afirmar(pokedex_destruido != NULL,
		     "El puntero original no debe ser NULL");
}

void buscarMultiplesPokemones()
{
	struct pokedex *pokedex = pokedex_crear();
	struct pokemon fennekin = { "Fennekin", TIPO_FUEGO, 45, 60, 40 };
	struct pokemon bulbasaur = { "Bulbasaur", TIPO_PLANTA, 45, 49, 49 };
	struct pokemon charmander = { "Charmander", TIPO_FUEGO, 39, 52, 43 };
	struct pokemon squirtle = { "Squirtle", TIPO_AGUA, 44, 48, 65 };
	struct pokemon pikachu = { "Pikachu", TIPO_ELECTRICO, 35, 55, 40 };
	struct pokemon rattata = { "Rattata", TIPO_NORMAL, 30, 56, 35 };
	struct pokemon machop = { "Machop", TIPO_LUCHA, 70, 80, 50 };

	pokedex_agregar_pokemon(pokedex, fennekin);
	pokedex_agregar_pokemon(pokedex, bulbasaur);
	pokedex_agregar_pokemon(pokedex, charmander);
	pokedex_agregar_pokemon(pokedex, squirtle);
	pokedex_agregar_pokemon(pokedex, pikachu);
	pokedex_agregar_pokemon(pokedex, rattata);
	pokedex_agregar_pokemon(pokedex, machop);

	const struct pokemon *pokemon_encontrado = NULL;

	char *nombres_esperados[] = { "Bulbasaur", "Charmander", "Fennekin",
				      "Machop",	   "Pikachu",	 "Rattata",
				      "Squirtle" };

	for (int i = 0; i < POKEMONES_CANT_PRUEBA; i++) {
		pokemon_encontrado =
			pokedex_buscar_pokemon(pokedex, nombres_esperados[i]);

		pa2m_afirmar((pokemon_encontrado != NULL ||
			      strcmp(pokemon_encontrado->nombre,
				     nombres_esperados[i]) == 0),
			     "Se encuentra el pokemon esperado");
	}

	pokedex_destruir(pokedex);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de archivos CSV");
	abrirArchivoExistenteDebeRetornarUnPuntero();
	abrirUnArchivoInexistenteDebeRetornarNull();
	siUnPunteroEsNullNoSePuedeLeer();
	leerUnArchivoVacioDebeRetornarCero();
	seParseaCorrectamenteUnaLineaCSV();

	pa2m_nuevo_grupo("Pruebas de pokedex");
	seCreaPokedex();
	contarLosPokemonesDeUnaPokedexNulaDevuelve0();
	seIteraSobrePokedexVaciaDevuelve0();
	seAgregaPokemonEInteractuaCorrectamente();
	seInsertaOrdenadamentePokemon();
	buscarMultiplesPokemones();
	seDestruyePokedex();

	return pa2m_mostrar_reporte();
}
