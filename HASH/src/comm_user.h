#ifndef COMM_USER_H
#define COMM_USER_H

#include <stdio.h>
#include <stdlib.h>

#define ROJO "\x1b[31m"
#define ROJO_BOLD "\033[1;31m"
#define VERDE "\x1b[32m"
#define VERDE_BOLD "\033[1;32m"
#define MARRON "\x1b[33m"
#define MARRON_BOLD "\033[1;33m"
#define AZUL "\x1b[34m"
#define AZUL_BOLD "\033[1;34m"
#define MAGENTA "\x1b[35m"
#define MAGENTA_BOLD "\033[1;35m"
#define CYAN "\x1b[36m"
#define CYAN_BOLD "\033[1;36m"
#define RESET "\x1b[0m"

void limpiar_pantalla();
void mostrar_inicio();
void mostrar_aclaracion_separador();
void mostrar_seleccionar_archivo();
void mostrar_aclaracion_seleccionar_archivo();
void mostrar_no_selecciono_archivo();
void mostrar_opciones_ingreso();
void mostrar_opcion_seleccionar_separador();
void mostrar_seleccionar_separador();
void mostrar_bienvenida();
void mostrar_seleccionar_funcionalidad();
void animacion_pikachu();
void mostrar_pokemon_buscado();
void titulo_pokedex();
void mostrar_no_encontrado();
void mostrar_error();

#endif // COMM_USER_H