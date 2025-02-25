<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# TP 2

## Repositorio de Rivas Sofia Belen - 112216 - srivas@fi.uba.ar

- Para compilar:

```bash
gcc -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -g src/*.c tp2.c engine.o -o tp2
```

- Para ejecutar:

```bash
./tp2 archivo_csv
```

- Para ejecutar con valgrind:
```bash
valgrind --leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes -s ./tp2 archivo_csv
```
---
El presente trabajo práctico tiene como objetivo la implementación de un juego utilizando TDAs y bibliotecas, aplicando de esa forma lo aprendido a lo largo de la materia.

# TDAs creados

## TDA Jugador

El TDA `Jugador` representa/modela al usuario que hace uso del juego, gestionando su estado, movimientos y estadísticas. Su interfaz y su implementación permiten:

### Crear y destruir un jugador
La función `crear_jugador` inicializa un jugador con valores por defecto, asignando memoria dinámica para sus estadísticas y estructuras asociadas.

La función `destruir_jugador` libera los recursos asociados al jugador, evitando leaks de memoria.
Gestión de movimientos:

El jugador puede desplazarse por el tablero de juego mediante la función `mover_jugador`, que controla las posiciones dentro de los límites definidos, actualizando su posición y el conteo de movimientos realizados.

### Gestión de puntuación y multiplicadores

**Suma de puntos**: La función `sumar_puntos_jugador` permite incrementar la puntuación del jugador en función del valor del pokemon capturado y el multiplicador actual.

**Multiplicador**: A  el pokemon capturado más reciente y su multravés las funciones `incrementar_multiplicador_jugador` y `resetear_multiplicador_jugador` se puede, como su nombre lo indica, aumentar o reiniciar el valor del multiplicador.

**Registro de estadísticas**: El jugador almacena información sobre su combo más largo, el pokemon capturado más reciente y su multiplicador más alto alcanzado.

**Interacción con un pokemon:** Las funciones `actualizar_ultimo_capturado` y `obtener_ultimo_capturado_jugador` facilitan el manejo del último pokemon capturado, permitiendo su almacenamiento y recuperación para cualquier estadística donde esto se requiera.

Otras funcionalidades destacadas:

Visualización del combo más largo a través de mostrar_combo_mas_largo, una lista dinámica que almacena los pokemones involucrados en el mejor combo.

## TDA Menu
El TDA `Menu` se encarga de gestionar las opciones disponibles en el juego, permitiendo que el usuario interactúe con el sistema mediante diferentes acciones.

### Crear y destruir un menú
La función `crear_menu` inicializa un menú con una lista de acciones vacía, asignando memoria dinámica para el menú y sus componentes. Este proceso prepara el menú para ser usado durante el juego.

La función `destruir_menu` libera todos los recursos asociados al menú, incluidas las acciones que se han agregado, evitando leaks de memoria.

### Gestión de acciones del menú
**Agregar acción al menú**: La función `menu_agregar_accion` permite agregar una nueva acción al menú, asignando memoria dinámica para la acción y añadiéndola a la lista de acciones disponibles.

**Interacción con el menú**: La función `interactuar_menu` permite al jugador interactuar con el menú, eligiendo una opción. Dependiendo de la opción seleccionada, se ejecuta la función asociada a la acción correspondiente, facilitando la interacción dinámica entre el jugador y el sistema del juego.

**Imprimir opciones del menú**: La función `imprimir_menu` muestra las opciones disponibles en el menú, proporcionando al jugador una lista de las acciones que puede realizar, como mostrar la Pokedex, jugar, usar una semilla para jugar o salir.

### Gestión de acciones específicas
**Acciones del menú**: Cada acción está representada por un índice y una función asociada. La función `accion_crear` permite crear una nueva acción con su índice y la función asociada, para luego ser agregada al menú.

**Ejecutar función de la acción**: Cuando el jugador selecciona una opción, la función `interactuar_menu` se encarga de buscar la acción correspondiente en la lista y ejecutar la función asociada, asegurando que el flujo del juego continúe según lo solicitado por el jugador.

### Funciones adicionales
**Liberar recursos**: La función `liberar_todo` es responsable de liberar todos los recursos utilizados en el menú, como la Pokedex, el jugador, el archivo CSV y otros componentes relacionados. Se la llama cuando el jugador decide salir del juego.

**Comparación de acciones**: La función `comparador_char` se utiliza para comparar las acciones basadas en su índice, permitiendo que se identifiquen y seleccionen correctamente cuando el jugador interactúa con el menú.

## TDA Pokedex

Representa una colección de pokemones almacenados en un ABB, lo que permite organizar los pokemones de manera eficiente y realizar búsquedas rápidas por nombre

### Crear y destruir un Pokedex
La función `crear_pokedex` inicializa una estructura de tipo `pokedex_t`, reservando memoria para la estructura principal y creando un ABB para almacenar los pokemones. Si se encuentra algún error durante la reserva de memoria, la función retorna `NULL`.

La función `destruir_pokedex` libera los recursos asociados a la estructura de la Pokedex. Primero destruye el árbol de pokemones, liberando cada pokemon almacenado, y luego libera la memoria asignada para la estructura `pokedex_t`.

### Gestión de pokemones en la Pokedex
**Agregar pokemon al Pokedex**: La función `cargar_pokedex` permite cargar pokemones desde un archivo CSV. Utiliza la función `parsear_datos_pokemon` para extraer los datos de cada pokemon y luego los inserta en el ABB pokemones. Los pokemones se almacenan en el ABB según su nombre, utilizando una comparación insensible a mayúsculas y minúsculas.

**Mostrar pokemones de la Pokedex**: La función `mostrar_pokedex` recorre el ABB de los pokemones y los imprime en orden mediante un recorrido inorden, utilizando la función `imprimir_pokemon`.

**Obtener cantidad de pokemones**: La función `obtener_cantidad_pokemones` devuelve el número de pokemones almacenados en la Pokedex, proporcionado por el campo cantidad de la estructura `pokedex_t`.

### Gestión del árbol de pokemones
**Obtener árbol de pokemones**: La función `obtener_arbol_pokemones` devuelve el árbol de pokemones (`abb_t`) almacenado en la Pokedex. Si la Pokedex es NULL, retorna NULL.

### Funciones auxiliares
**Comparación de pokemones por nombre**: La función `comparar_nombre_pokemon` compara dos pokemones por su nombre de manera insensible a mayúsculas y minúsculas, utilizando la función `comparar_case_insensitive`.

**Parseo de datos de pokemon desde CSV**: La función `parsear_datos_pokemon` es responsable de extraer los datos de un pokemon desde una línea de un archivo CSV, utilizando funciones auxiliares como `crear_string_nuevo` y `leer_int`. La función recibe un archivo CSV y almacena los datos correspondientes en las variables string, puntos, color y movimiento.

### Funciones auxiliares para manejo de memoria
**Crear un nuevo string**: La función `crear_string_nuevo` crea un string, asignando memoria dinámica y copiando el contenido del string pasado como parámetro. Si ocurre algún error en la asignación, retorna false.

**Leer un entero**: La función `leer_int` convierte un string en un número entero, almacenando el resultado en un puntero a entero. Si la conversión no es exitosa, retorna false.

### Otras funcionalidades destacadas
**Liberación de recursos**: La función `liberar_pokemon` se utiliza para liberar la memoria asociada a un pokemon individual. Esta función es invocada al destruir el árbol de pokemones durante la destrucción de la Pokedex.

**Iteración sobre el árbol de pokemones**: Se utiliza la función `abb_iterar_inorden` para iterar sobre el ABB y ejecutar una función sobre cada pokemon almacenado. En este caso, se utiliza para imprimir los pokemones con un recorrido inorden.

## TDA Pokemon
El TDA pokemon representa un conjunto de pokemones, cada uno definido por atributos como su nombre, puntos, color, movimientos y coordenadas. Este TDA permite la creación, manipulación y destrucción de objetos pokemon, y proporciona funcionalidades para comparar, copiar y liberar recursos asociados a cada pokemon.

### Crear y destruir un pokemon
**Crear un pokemon**: La función crear_pokemon crea un nuevo pokemon con los atributos proporcionados, como el nombre, puntos, color, movimiento y coordenadas (x, y).

**Destruir un pokemon**: La función `liberar_pokemon` libera la memoria asociada a un pokemon individual. Esto incluye la liberación de todos sus atributos dinámicos, como el nombre, color y movimiento, además de liberar el objeto pokemon mismo.

### Gestión de pokemon
**Comparación de pokemon**: La función `comparar_pokemon` compara dos pokemon en base a su nombre, y si los nombres son idénticos, compara sus coordenadas (x, y).

**Copiar un pokemon**: La función `copiar_pokemon` crea una copia exacta de un pokemon existente, replicando sus atributos.

**Obtener atributos de un pokemon**:
**Nombre**: La función `obtener_nombre_pokemon` retorna el nombre de un pokemon.
**Color**: La función `obtener_color_pokemon` retorna el color de un pokemon.
**Coordenadas**: Las funciones `obtener_x_pokemon` y `obtener_y_pokemon` retornan las coordenadas (x, y) de un pokemon.
**Obtener índice de un pokemon**: La función `obtener_indice_pokemon` devuelve el índice único de un pokemon.

### Gestión de pokemon en estructuras de datos
**Buscar un pokemon por índice**: La función `obtener_pokemon_por_indice` permite buscar un pokemon dentro de un ABB utilizando su índice único.

**Buscar un pokemon por coordenadas**: La función `buscar_pokemon_por_coordenadas` busca un pokemon dentro del árbol de pokemones utilizando sus coordenadas (x, y).

### Funciones auxiliares
**Comparar nombre de pokemon**: La función `comparar_nombre_pokemon` compara dos pokemon por su nombre de manera insensible a mayúsculas y minúsculas.

**Crear un nuevo string**: La función `crear_string_nuevo` permite crear un string mediante asignación dinámica, copiando el contenido del string pasado como parámetro.

**Leer un entero**: La función `leer_int` convierte un string a un número entero.

### Iteración sobre los pokemones
**Iterar sobre el árbol de pokemones**: Se utiliza la función `abb_iterar_inorden` para recorrer el árbol de pokemones y aplicar una función sobre cada uno. Esta función es útil para operaciones como la impresión de los pokemones en orden.

### Otras funcionalidades destacadas
**Liberación de recursos**: Durante la destrucción del ABB de pokemones, la función `liberar_pokemon` se invoca para liberar la memoria de cada pokemon individualmente antes de destruir el árbol.

# TDAs reutilizados
Para la realización del trabajo se reutilizaron dos TDA: **ABB** y **lista**.
## TDA ABB
El TDA ABB se reutilizó con el fin de:
- **Almacenar y organizar los pokemones**: El ABB es una estructura de datos que permite almacenar los pokemones en orden alfabético según su nombre. Esto facilita *búsquedas rápidas*, *inserciones* y *eliminaciones* de pokemones en el árbol, manteniendo el orden de los elementos.
- **Optimizar las búsquedas**: Dado que el ABB sigue la propiedad de orden, donde los elementos a la izquierda son menores y los de la derecha son mayores que el nodo actual, permite realizar búsquedas de pokemones por nombre de manera eficiente en O(log n), lo que mejora el rendimiento en comparación con otras estructuras de datos como listas no ordenadas.
- **Recorridos en orden (inorden)**: El ABB permite recorrer los pokemones en orden alfabético de manera sencilla mediante un recorrido en inorden. Esto es útil para imprimir todos los pokemones almacenados de manera ordenada y para otros procesos que necesiten mantener un orden específico. Se pensó principalmente en esto debido a la opción 'P', que permite mostrar todos los pokemones cargados.
- **Gestión de memoria dinámica**: El ABB permite un manejo flexible y eficiente de memoria, ya que las inserciones y eliminaciones de nodos se realizan de forma dinámica, adaptándose a la cantidad de pokemones almacenados.

## TDA Lista
El TDA Lista se reutilizó con el fin de:
- **Gestión de colecciones temporales de pokemones**: En situaciones en las que es necesario manejar un conjunto de pokemones de forma temporal (como por ejemplo, almacenar una lista de pokemones para ser procesada antes de ser insertada en el ABB), se utiliza el TDA Lista. Esta estructura permite insertar, eliminar y acceder a los elementos de manera eficiente, con complejidad O(1) en inserciones al inicio o al final de la lista.
- **Recorridos secuenciales**: La lista permite recorrer de manera secuencial todos los elementos almacenados. Este tipo de recorrido es ideal para situaciones donde no es necesario acceder a los elementos en posiciones aleatorias, sino que se necesita procesar los elementos en el orden en el que fueron añadidos.
- **Facilitar la manipulación de datos**: Al ser una estructura flexible y de tamaño dinámico, la lista facilita el manejo de colecciones de pokemones sin necesidad de preocuparse por los límites de tamaño. Además, la implementación de la lista proporciona funciones para gestionar los pokemones de forma sencilla, permitiendo la iteración de forma más fácil sobre sus elementos.