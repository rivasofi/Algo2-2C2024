# Trabajo práctico 0 - Split
### Trabajo de Sofia Belen Rivas - Padrón 112216
## Objetivo
El objetivo principal del presente trabajo fue desarrollar una función en lenguaje C que permita dividir un string en partes, utilizando un caracter separador. La función resultante debía manejar eficientemente la memoria, evitando leaks, y devolver un struct con información relacionada al string inicial (los substrings y la cantidad de estos). Además, se buscaba que la función pudiera manejar adecuadamente una variedad de casos especiales, como strings vacíos o nulos.

## Descripción general del código

- **Struct Partes**: Se da con la consigna un struct de nombre Partes que contiene dos elementos: un arreglo de punteros a char, donde se almacenan los substrings resultantes, y un entero que indica la cantidad de estos substrings. Este struct facilita la manipulación y el acceso a las partes generadas por la función.

- **Función principal**: La función principal del código es dividir_string. Su tarea es recibir un string y un separador, y dividir el string original en substrings utilizando el carácter separador. La lógica implementada permite:
    
    - Contabilizar cuántas partes se generarán a partir de el string original.

    - Asignar memoria dinámicamente para cada parte.

    - Manejar casos especiales, como cuando el string es nulo o está vacío.

    - Garantizar la liberación de memoria en caso de que ocurra un error durante el proceso.

- **Manejo de memoria**: Uno de los aspectos clave en la implementación fue asegurar que toda la memoria dinámica asignada se maneje correctamente. Se implementaron funciones auxiliares para verificar las asignaciones y liberar los recursos en caso de error, previniendo leaks de memoria.

## Lógica implementada
La lógica general del código se basa en la identificación de los separadores dentro del string y la creación de nuevos substrings. Se realizaron comprobaciones constantes para asegurar que las operaciones de memoria sean seguras y eficientes. Además, se contemplaron los casos de borde, como cuando el string no contiene separadores o cuando el string de entrada es nulo. Podemos dividirlo en los siguientes cinco ítems:

- **Búsqueda del separador**:  La función buscar_posicion_separador recorre el string original para encontrar la posición del carácter separador o el final del string.
- **Contabilización de separadores**: Para determinar cuántas subcadenas se generarán, la función contabilizar_separadores recorre el string y cuenta cuántas veces aparece el separador.
- **Creación de los substrings**: Una vez identificadas las posiciones de los separadores, se procede a crear los substrings mediante la función crear_substring.
- **Copia del contenido de los substrings**: La función copiar_contenido_substring se encarga de copiar los caracteres correspondientes del string original al substring recién creado, asegurando que esta termine en un carácter nulo (\0)
- **Manejo de casos especiales estipulados en las pruebas**