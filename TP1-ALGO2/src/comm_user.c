#include "comm_user.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void limpiar_pantalla()
{
	printf("\033[H\033[J");
}

void mostrar_inicio()
{
	limpiar_pantalla();

	printf(AZUL_BOLD
	       "\n\n\n\n\n\n\n\n\n\n\n\n\n\n				                                                                         .*@-                                                               \n");
	printf("				                                                                        =@##@=                                                              \n");
	printf("				                                                                      -%%%%-  =@#.                                                            \n");
	printf("				                                                     .. ..          .#@+   :+%%@*                                                            \n");
	printf("				                  ..:----:.                    .:=*#@@=.%%@*:       +@%%::=#@#+:     ........+#######:                                        \n");
	printf("				            :=*#%%@@@%%%%#%%%%%%@@@#=.          .+*%%@@%%#+=@@=%%@+#@#-     +@@@@@%%*=-.    .@@%%%%%%%%%%@@@+:::+@*         =+=-:.                         \n");
	printf("				        :+#@@%%*=:.          -+@@#:        -@%%-.     %%@@%%.  .*@%%=.=#@@#*+==+*%%@%%+. +@*     :@@    .@@         *@##%%@@@%%#+=  .                \n");
	printf("				     .*@@%%+:                   -@@+       -@@*#     #@*      .*@@@*:         .=%%@+%%@-      %%*     %%@-        *@=.   .:-@@-=@@%%#*+-:.        \n");
	printf("				      *@%%.                      .@@:      .#*@@.    +-       -%%@#.  .*##%%%%=   -%%@@@@       +-     +@*     .. -*@#      +@#%%@.:-=+*@@+       \n");
	printf("				       +@@-            %%@%%%%#-    +@*   ..:.. @@-           -%%@@%%    @+ =%%=  :%%@@-+@#       .      :@@-+#@%%%%%%%%@#@+      .@@@+     =@%%        \n");
	printf("				        -@@= :-        +@: +@.   #@*+#@%%#**#@@@+         -%%@**@+   .@*%%+  :#@#%%@#%%@=               @@%%+::-.   :#@+      *@@.    .@@:        \n");
	printf("				         :%%@@@@=        @%%.#@   =@@@+: ::    :#@=       *@@#=*@*    :*. .+#+:  -%%@@=             .%%@= .%%@    .  +@+     :@*     #@*         \n");
	printf("				          .=:-@@-       -@@*.  +@@+  :%%%%    :  +@-        :=+#@@=               :%%@%%:   =.       %%@:  =@@*--=%%   @@      %%.    =@%%          \n");
	printf("				              -@@:       -   -%%@@=   +@@#==*%%   @%%   .        .#@#-          :+%%@@+     %%%%   =- -@+    +%%@@@#:   @@  :   .    .@@:          \n");
	printf("				               =@@:        =%%@%%@%%     +%%@@@*.   @%%   #@#=:      :*@@%%*+++*#%%@@#*@@.    :@@# :@+ -@+       .     *@=  +        #@+           \n");
	printf("				                +@@.      +@@::@%%              +@=   #@*#@@#=:     :-=#@%%+=-.  =@%%.    +@@@*@@%%  %%@:          .#@=  =+       -@%%            \n");
	printf("				                 *@%%       @@: #@-           .*@*    *@-  :=*@@#+:    +@#      +##%%@@%%%%@%%.%%@%%@@: .#@*-.    :=#@#.   #*       %%@:            \n");
	printf("				                  *@#      +@# .#@*.       -*@@@*    *@-      .=*@@#+:+@#            .::: .#.#@+   .+%%@@@@@%%*@@.   .@*      *@+             \n");
	printf("				                   #@*     .@@-  -#@%%#**#%%@@*-:@%%++*#@@-          .=*@@@#                    +@@@%%##*#@%%     @@=-::+@#     -@%%              \n");
	printf("				                    %%@+     +@%%     :-==-:.    #*++=--:               :==                       .:-==+*#     =++*##%%@#     %%@:              \n");
	printf("				                    .@@+   .-@@=                                                                                   .@%%-.  *@*               \n");
	printf("				                     :@@*#@@@#*-                                                                                    =*#@@%%@%%                \n");
	printf("				                      -#*=-.                                                                                            .:=:                \n" RESET);
}

void mostrar_seleccionar_archivo()
{
	limpiar_pantalla();

	printf("\n\n\n\n\n\t						        ___                                       _                         _              \n");
	printf("\t						       |_ _|_ __   __ _ _ __ ___  ___  ___    ___| |  _ __   ___  _ __ ___ | |__  _ __ ___ \n");
	printf("\t						        | || '_ \\ / _` | '__/ _ \\/ __|/ _ \\  / _ \\ | | '_ \\ / _ \\| '_ ` _ \\| '_ \\| '__/ _ \\ \n");
	printf("\t						        | || | | | (_| | | |  __/\\__ \\  __/ |  __/ | | | | | (_) | | | | | | |_) | | |  __/\n");
	printf("\t						       |___|_| |_|\\__, |_|  \\___||___/\\___|  \\___|_| |_| |_|\\___/|_| |_| |_|_.__/|_|  \\___|\n");
	printf("\t						                  |___/                                                                    \n");
	printf("\t							           _     __                  _     _               ____ ______     __             \n");
	printf("\t							        __| | ___| |   __ _ _ __ ___| |__ (_)_   _____    / ___/ ___\\ \\   / /             \n");
	printf("\t							       / _` |/ _ \\ |  / _` | '__/ __| '_ \\| \\ \\ / / _ \\  | |   \\___ \\\\ \\ / /              \n");
	printf("\t							      | (_| |  __/ | | (_| | | | (__| | | | |\\ V / (_) | | |___ ___) |\\ V /               \n");
	printf("\t							       \\__,_|\\___|_|  \\__,_|_|  \\___|_| |_|_| \\_/ \\___/   \\____|____/  \\_/                \n\n\n\n");

	printf("						█▀█ █▀█ █▀█ █▀▀ █░█ █▀█ █▀▀   █▀█ █░█ █▀▀   █▀ █▀▀   █▀▀ █▄░█ █▀▀ █░█ █▀▀ █▄░█ ▀█▀ █▀█ █▀▀   █▀▀ █▄░█   █▀▀ █▀ ▀█▀ █▀▀\n");
	printf("						█▀▀ █▀▄ █▄█ █▄▄ █▄█ █▀▄ ██▄   ▀▀█ █▄█ ██▄   ▄█ ██▄   ██▄ █░▀█ █▄▄ █▄█ ██▄ █░▀█ ░█░ █▀▄ ██▄   ██▄ █░▀█   ██▄ ▄█ ░█░ ██▄\n\n");

	printf("						      █▀▄ █ █▀█ █▀▀ █▀▀ ▀█▀ █▀█ █▀█ █ █▀█   █▄█   ▀█▀ █▀▀ █▄░█ █▀▀ ▄▀█   █▀ █░█ █▀   █▀▀ ▄▀█ █▀▄▀█ █▀█ █▀█ █▀\n");
	printf("						      █▄▀ █ █▀▄ ██▄ █▄▄ ░█░ █▄█ █▀▄ █ █▄█   ░█░   ░█░ ██▄ █░▀█ █▄█ █▀█   ▄█ █▄█ ▄█   █▄▄ █▀█ █░▀░█ █▀▀ █▄█ ▄█\n\n");

	printf("							       █▀▀ █▀█ █▀▄▀█ █▀█ █░░ █▀▀ ▀█▀ █▀█ █▀   █▄█   █▀█ █▀█ █▀▄ █▀▀ █▄░█ ▄▀█ █▀▄ █▀█ █▀\n");
	printf("							       █▄▄ █▄█ █░▀░█ █▀▀ █▄▄ ██▄ ░█░ █▄█ ▄█   ░█░   █▄█ █▀▄ █▄▀ ██▄ █░▀█ █▀█ █▄▀ █▄█ ▄█\n\n\n");

	printf(ROJO
	       "									Por favor, no incluir la extensión .csv en el nombre del archivo.\n\n" RESET);
}

void mostrar_aclaracion_seleccionar_archivo()
{
	printf(ROJO
	       "\t\t\t\t\t\t\t\tSi el archivo está en otro directorio especificarlo como: directorio/nombre_archivo\n" RESET);
	printf(ROJO
	       "\t\t\t\t\t\t\t\t\t\t\tPor ejemplo, ejemplos/pokedex\n" RESET);
}

void mostrar_seleccionar_separador()
{
	printf("							   _____               _ _                  _                                      _            \n");
	printf("							  | ____|___  ___ _ __(_) |__   __ _    ___| |  ___  ___ _ __   __ _ _ __ __ _  __| | ___  _ __ \n");
	printf("							  |  _| / __|/ __| '__| | '_ \\ / _` |  / _ \\ | / __|/ _ \\ '_ \\ / _` | '__/ _` |/ _` |/ _ \\| '__|\n");
	printf("							  | |___\\__ \\ (__| |  | | |_) | (_| | |  __/ | \\__ \\  __/ |_) | (_| | | | (_| | (_| | (_) | |   \n");
	printf("							  |_____|___/\\___|_|  |_|_.__/ \\__,_|  \\___|_| |___/\\___| .__/ \\__,_|_|  \\__,_|\\__,_|\\___/|_|   \n");
	printf("							                                                        |_|                                     \n\n\n");
}

void mostrar_cargando()
{
	printf("\n\n										     █▀▀ ▄▀█ █▀█ █▀▀ ▄▀█ █▄░█ █▀▄ █▀█ \n");
	printf("										     █▄▄ █▀█ █▀▄ █▄█ █▀█ █░▀█ █▄▀ █▄█ ▄ ▄ ▄\n");
}

void mostrar_error_abrir_archivo()
{
	printf(ROJO
	       "\n\t\t\t\t\t\t\t\t█▀▀ █▀█ █▀█ █▀█ █▀█   ▄▀█ █▄▄ █▀█ █ █▀▀ █▄░█ █▀▄ █▀█   ▄▀█ █▀█ █▀▀ █░█ █ █░█ █▀█\n");
	printf("\t\t\t\t\t\t\t\t██▄ █▀▄ █▀▄ █▄█ █▀▄   █▀█ █▄█ █▀▄ █ ██▄ █░▀█ █▄▀ █▄█   █▀█ █▀▄ █▄▄ █▀█ █ ▀▄▀ █▄█\n" RESET);
}

void mostrar_mensaje_inicio()
{
	limpiar_pantalla();

	printf(AZUL_BOLD
	       "\n\n\n\n\n\n\t\t\t\t\t\t\t\t     ____  _                           _     _   ____            _       \n");
	printf("\t\t\t\t\t\t\t\t    | __ )(_) ___ _ ____   _____ _ __ (_) __| | / __ \\    __ _  | | __ _ \n");
	printf("\t\t\t\t\t\t\t\t    |  _ \\| |/ _ \\ '_ \\ \\ / / _ \\ '_ \\| |/ _` |/ / _` |  / _` | | |/ _` |\n");
	printf("\t\t\t\t\t\t\t\t    | |_) | |  __/ | | \\ V /  __/ | | | | (_| | | (_| | | (_| | | | (_| |\n");
	printf("\t\t\t\t\t\t\t\t    |____/|_|\\___|_| |_|\\_/ \\___|_| |_|_|\\__,_|\\ \\__,_|  \\__,_| |_|\\__,_|\n");
	printf("\t\t\t\t\t\t\t\t                                                \\____/                   \n");

	printf("\n\n\t\t\t\t\t\t\t\t                     ____       _            _           \n");
	printf("\t\t\t\t\t\t\t\t                    |  _ \\ ___ | | _____  __| | _____  __\n");
	printf("\t\t\t\t\t\t\t\t                    | |_) / _ \\| |/ / _ \\/ _` |/ _ \\ \\/ /\n");
	printf("\t\t\t\t\t\t\t\t                    |  __/ (_) |   <  __/ (_| |  __/>  < \n");
	printf("\t\t\t\t\t\t\t\t                    |_|   \\___/|_|\\_\\___|\\__,_|\\___/_/\\_\\" RESET);

	printf(ROJO
	       "\n\n\n\t\t\t\t\t\t\t\t                                :=+**********+=:            \n");
	printf("\t\t\t\t\t\t\t\t                            .=#*=-.          .:=*#=.        \n");
	printf("\t\t\t\t\t\t\t\t                          -##=....................-*#-      \n");
	printf("\t\t\t\t\t\t\t\t                        -o*-::::::::::::::::::::::::-*#-    \n");
	printf("\t\t\t\t\t\t\t\t                       *o=----------------------------=o*   \n");
	printf("\t\t\t\t\t\t\t\t                      ##================================##  \n");
	printf("\t\t\t\t\t\t\t\t                     #o+===========++++++++++============## \n");
	printf("\t\t\t\t\t\t\t\t                    =o*++++++**##ooooooooooooooo##*+++++++o-\n");
	printf("\t\t\t\t\t\t\t\t                    ##***##oooooooooooooooooooooooooo##***##\n");
	printf("\t\t\t\t\t\t\t\t                    @o#oooooooooooooooooooooooooooooooooooo@\n");
	printf("\t\t\t\t\t\t\t\t                    @oooooooooooooooooooooooooooooooooooooo@\n");
	printf("\t\t\t\t\t\t\t\t                    *o@oooooooooooooooooooooooooooooooooo@#+\n");
	printf("\t\t\t\t\t\t\t\t                    -.+@@ooooooooooooo@@@@ooooooooooooo@o=.-\n");
	printf("\t\t\t\t\t\t\t\t                     =  -*o@@ooooooo@#-::-*@oooooo@@@o+:  = \n");
	printf("\t\t\t\t\t\t\t\t                      =    .-+#o@@@@#..  ..+@@@@o*+-.    =  \n");
	printf("\t\t\t\t\t\t\t\t                       =.        ..=#.    .*+.         .=   \n");
	printf("\t\t\t\t\t\t\t\t                        :-          -*+--=*=          -:    \n");
	printf("\t\t\t\t\t\t\t\t                          :-.          ..          .-:      \n");
	printf("\t\t\t\t\t\t\t\t                            .::.                .::.        \n");
	printf("\t\t\t\t\t\t\t\t                                ::::::::::::::::            \n\n\n" RESET);
}

void mostrar_mensaje_post_exito()
{
	limpiar_pantalla();

	printf(AZUL_BOLD
	       "\n\n\n\n\n\n\t\t\t\t\t\t\t\t     ____  _                           _     _   ____            _       \n");
	printf("\t\t\t\t\t\t\t\t    | __ )(_) ___ _ ____   _____ _ __ (_) __| | / __ \\    __ _  | | __ _ \n");
	printf("\t\t\t\t\t\t\t\t    |  _ \\| |/ _ \\ '_ \\ \\ / / _ \\ '_ \\| |/ _` |/ / _` |  / _` | | |/ _` |\n");
	printf("\t\t\t\t\t\t\t\t    | |_) | |  __/ | | \\ V /  __/ | | | | (_| | | (_| | | (_| | | | (_| |\n");
	printf("\t\t\t\t\t\t\t\t    |____/|_|\\___|_| |_|\\_/ \\___|_| |_|_|\\__,_|\\ \\__,_|  \\__,_| |_|\\__,_|\n");
	printf("\t\t\t\t\t\t\t\t                                                \\____/                   \n");

	printf("\n\n\t\t\t\t\t\t\t\t                     ____       _            _           \n");
	printf("\t\t\t\t\t\t\t\t                    |  _ \\ ___ | | _____  __| | _____  __\n");
	printf("\t\t\t\t\t\t\t\t                    | |_) / _ \\| |/ / _ \\/ _` |/ _ \\ \\/ /\n");
	printf("\t\t\t\t\t\t\t\t                    |  __/ (_) |   <  __/ (_| |  __/>  < \n");
	printf("\t\t\t\t\t\t\t\t                    |_|   \\___/|_|\\_\\___|\\__,_|\\___/_/\\_\\" RESET);

	printf(MARRON_BOLD
	       "\n\n\n\t\t\t\t\t\t\t\t                        -.                                        \n");
	printf("\t\t\t\t\t\t\t\t                      .#*:                                       \n");
	printf("\t\t\t\t\t\t\t\t                      -#%%*=                                      \n");
	printf("\t\t\t\t\t\t\t\t                      :####=                                     \n");
	printf("\t\t\t\t\t\t\t\t                       *%%##*:                                    \n");
	printf("\t\t\t\t\t\t\t\t                       -#%%%%@+ ... ..          .:--=+++-          \n");
	printf("\t\t\t\t\t\t\t\t                        -#@@*--=-==---:   :=*###%%%%##+:           \n");
	printf("\t\t\t\t\t\t\t\t                         .+#+===========-*%%@@%%%%###+:    :-       \n");
	printf("\t\t\t\t\t\t\t\t                           ==+==========+%%@@%%#*=:    .:::.      \n");
	printf("\t\t\t\t\t\t\t\t                          .=#**======++==+::...::----:-::::      \n");
	printf("\t\t\t\t\t\t\t\t                          :=%%@*=====#*@=+:  :++++++++++-:::      \n");
	printf("\t\t\t\t\t\t\t\t                        ..==+*==+===%%@%%++  -+++++++++++--:.      \n");
	printf("\t\t\t\t\t\t\t\t                       :..:=+==++++=++++=-:**++++++++++++=       \n");
	printf("\t\t\t\t\t\t\t\t                      ......:-=+++++++=-:::+***+++++++***.       \n");
	printf("\t\t\t\t\t\t\t\t                      .-..:.....::--:--:::-=+**********+.        \n");
	printf("\t\t\t\t\t\t\t\t                       .:::........:-:=-::++++*******+:          \n");
	printf("\t\t\t\t\t\t\t\t                          ::-:.....:--=-=+++++=::::.             \n");
	printf("\t\t\t\t\t\t\t\t                           :==-::::-=+*+++++++=                  \n");
	printf("\t\t\t\t\t\t\t\t                            =++==+++++***:===+-                  \n");
	printf("\t\t\t\t\t\t\t\t                             ++++==++***: ====.                  \n");
	printf("\t\t\t\t\t\t\t\t                             ===+===+*+. ====.                   \n");
	printf("\t\t\t\t\t\t\t\t                            .===+===:    ---.                    \n");
	printf("\t\t\t\t\t\t\t\t                                .::.                             \n");
}

void mostrar_mensaje_creando_pokedex()
{
	printf(AZUL
	       "\n\n\n\t\t\t\t\t\t\t\t      █▀▀ █▀█ █▀▀ ▄▀█ █▄░█ █▀▄ █▀█   █▀█ █▀█ █▄▀ █▀▀ █▀▄ █▀▀ ▀▄▀\n");
	printf("\t\t\t\t\t\t\t\t      █▄▄ █▀▄ ██▄ █▀█ █░▀█ █▄▀ █▄█   █▀▀ █▄█ █░█ ██▄ █▄▀ ██▄ █░█ ▄ ▄ ▄\n" RESET);
}

void mostrar_mensaje_exito_pokedex()
{
	limpiar_pantalla();

	printf(AZUL_BOLD
	       "\n\n\n\n\n\n\t\t\t\t\t\t\t\t     ____  _                           _     _   ____            _       \n");
	printf("\t\t\t\t\t\t\t\t    | __ )(_) ___ _ ____   _____ _ __ (_) __| | / __ \\    __ _  | | __ _ \n");
	printf("\t\t\t\t\t\t\t\t    |  _ \\| |/ _ \\ '_ \\ \\ / / _ \\ '_ \\| |/ _` |/ / _` |  / _` | | |/ _` |\n");
	printf("\t\t\t\t\t\t\t\t    | |_) | |  __/ | | \\ V /  __/ | | | | (_| | | (_| | | (_| | | | (_| |\n");
	printf("\t\t\t\t\t\t\t\t    |____/|_|\\___|_| |_|\\_/ \\___|_| |_|_|\\__,_|\\ \\__,_|  \\__,_| |_|\\__,_|\n");
	printf("\t\t\t\t\t\t\t\t                                                \\____/                   \n");

	printf("\n\n\t\t\t\t\t\t\t\t                     ____       _            _           \n");
	printf("\t\t\t\t\t\t\t\t                    |  _ \\ ___ | | _____  __| | _____  __\n");
	printf("\t\t\t\t\t\t\t\t                    | |_) / _ \\| |/ / _ \\/ _` |/ _ \\ \\/ /\n");
	printf("\t\t\t\t\t\t\t\t                    |  __/ (_) |   <  __/ (_| |  __/>  < \n");
	printf("\t\t\t\t\t\t\t\t                    |_|   \\___/|_|\\_\\___|\\__,_|\\___/_/\\_\\" RESET);

	printf(MARRON_BOLD
	       "\n\n\n\t\t\t\t\t\t\t\t                        -.                                        \n");
	printf("\t\t\t\t\t\t\t\t                      .#*:                                       \n");
	printf("\t\t\t\t\t\t\t\t                      -#%%*=                                      \n");
	printf("\t\t\t\t\t\t\t\t                      :####=                                     \n");
	printf("\t\t\t\t\t\t\t\t                       *%%##*:                                    \n");
	printf("\t\t\t\t\t\t\t\t                       -#%%%%@+ ... ..          .:--=+++-          \n");
	printf("\t\t\t\t\t\t\t\t                        -#@@*--=-==---:   :=*###%%%%##+:           \n");
	printf("\t\t\t\t\t\t\t\t                         .+#+===========-*%%@@%%%%###+:    :-       \n");
	printf("\t\t\t\t\t\t\t\t                           ==+==========+%%@@%%#*=:    .:::.      \n");
	printf("\t\t\t\t\t\t\t\t                          .=#**======++==+::...::----:-::::      \n");
	printf("\t\t\t\t\t\t\t\t                          :=%%@*=====#*@=+:  :++++++++++-:::      \n");
	printf("\t\t\t\t\t\t\t\t                        ..==+*==+===%%@%%++  -+++++++++++--:.      \n");
	printf("\t\t\t\t\t\t\t\t                       :..:=+==++++=++++=-:**++++++++++++=       \n");
	printf("\t\t\t\t\t\t\t\t                      ......:-=+++++++=-:::+***+++++++***.       \n");
	printf("\t\t\t\t\t\t\t\t                      .-..:.....::--:--:::-=+**********+.        \n");
	printf("\t\t\t\t\t\t\t\t                       .:::........:-:=-::++++*******+:          \n");
	printf("\t\t\t\t\t\t\t\t                          ::-:.....:--=-=+++++=::::.             \n");
	printf("\t\t\t\t\t\t\t\t                           :==-::::-=+*+++++++=                  \n");
	printf("\t\t\t\t\t\t\t\t                            =++==+++++***:===+-                  \n");
	printf("\t\t\t\t\t\t\t\t                             ++++==++***: ====.                  \n");
	printf("\t\t\t\t\t\t\t\t                             ===+===+*+. ====.                   \n");
	printf("\t\t\t\t\t\t\t\t                            .===+===:    ---.                    \n");
	printf("\t\t\t\t\t\t\t\t                                .::.                             \n");

	printf(VERDE_BOLD
	       "\n\n\n\t\t\t\t\t\t\t    █▀█ █▀█ █▄▀ █▀▀ █▀▄ █▀▀ ▀▄▀   █▀▀ █▀█ █▀▀ ▄▀█ █▀▄ ▄▀█   █▀▀ █▀█ █▄░█   █▀▀ ▀▄▀ █ ▀█▀ █▀█\n");
	printf("\t\t\t\t\t\t\t    █▀▀ █▄█ █░█ ██▄ █▄▀ ██▄ █░█   █▄▄ █▀▄ ██▄ █▀█ █▄▀ █▀█   █▄▄ █▄█ █░▀█   ██▄ █░█ █ ░█░ █▄█ ▄ ▄ ▄\n" RESET);
}

void mostrar_mensaje_fracaso_pokedex()
{
	printf(ROJO
	       "\n\n        █▄░█ █▀█   █▀▀ █░█ █▀▀   █▀█ █▀█ █▀ █ █▄▄ █░░ █▀▀   █▀▀ █▀█ █▀▀ ▄▀█ █▀█   █░░ ▄▀█   █▀█ █▀█ █▄▀ █▀▀ █▀▄ █▀▀ ▀▄▀\n");
	printf("        █░▀█ █▄█   █▀░ █▄█ ██▄   █▀▀ █▄█ ▄█ █ █▄█ █▄▄ ██▄   █▄▄ █▀▄ ██▄ █▀█ █▀▄   █▄▄ █▀█   █▀▀ █▄█ █░█ ██▄ █▄▀ ██▄ █░█\n" RESET);
}

void mostrar_mensaje_carga()
{
	limpiar_pantalla();

	printf(AZUL_BOLD
	       "\n\n\t\t\t\t\t\t\t\t\t          ____                                _                     \n");
	printf("\t\t\t\t\t\t\t\t\t         / ___|__ _ _ __ __ _  __ _ _ __   __| | ___                \n");
	printf("\t\t\t\t\t\t\t\t\t        | |   / _` | '__/ _` |/ _` | '_ \\ / _` |/ _ \\               \n");
	printf("\t\t\t\t\t\t\t\t\t        | |__| (_| | | | (_| | (_| | | | | (_| | (_) |              \n");
	printf("\t\t\t\t\t\t\t\t\t         \\____\\__,_|_|  \\__, |\\__,_|_| |_|\\__,_|\\___/               \n");
	printf("\t\t\t\t\t\t\t\t\t                        |___/                                       \n");
	printf("\t\t\t\t\t\t\t\t\t     _ __   ___ | | ____  _ __ ___   ___  _ __   ___  ___       \n");
	printf("\t\t\t\t\t\t\t\t\t    | '_ \\ / _ \\| |/ / _ \\ '_ ` _ \\ / _ \\| '_ \\ / _ \\/ __|      \n");
	printf("\t\t\t\t\t\t\t\t\t    | |_) | (_) |   <  __/ | | | | | (_) | | | |  __/\\__ \\_ _ _ \n");
	printf("\t\t\t\t\t\t\t\t\t    | .__/ \\___/|_|\\_\\___|_| |_| |_|\\___/|_| |_|\\___||___(_|_|_)\n");
	printf("\t\t\t\t\t\t\t\t\t    |_|                                                         \n\n\n" RESET);

	printf(MARRON_BOLD
	       "\t\t\t\t\t\t\t                            .::..                                                         \n");
	printf("\t\t\t\t\t\t\t                        :==+==++***=:                         .-=+****+==:                \n");
	printf("\t\t\t\t\t\t\t                      -*+-----:::-+**#=                      +****=------=+=.             \n");
	printf("\t\t\t\t\t\t\t                     =*=--:..      :###*                   .****-.....:::--=*=            \n");
	printf("\t\t\t\t\t\t\t                    -**-:.          .###*                  ####:         ..:-#*           \n");
	printf("\t\t\t\t\t\t\t                    **+:          ...=##%%.                +###=            .:##-          \n");
	printf("\t\t\t\t\t\t\t                    #**.  .          :%%##:                ####:             :%%#=          \n");
	printf("\t\t\t\t\t\t\t                    *##=             :##%%.                %%###:             *##-          \n");
	printf("\t\t\t\t\t\t\t                    .###+.       ....+%%%%#  ..:::::::....  %%%%##-           .+##*           \n");
	printf("\t\t\t\t\t\t\t                      +###+:.   ..:::%%%%%%*==-------------==#%%%%%%+          -###*.           \n");
	printf("\t\t\t\t\t\t\t                       .=##%%#+=-----#%%%%#------------------=%%%%%%%%=--::..-+#%%%%#-             \n");
	printf("\t\t\t\t\t\t\t                         :+#%%%%%%%%%%%%%%%%%%#=-----------------==+%%%%%%%%*+**#%%%%%%#+-               \n");
	printf("\t\t\t\t\t\t\t                   ::         =**####*=-----------------====+#%%%%%%%%%%%%*=-.      *.          \n");
	printf("\t\t\t\t\t\t\t            .     +*        .=============----==----==========++++===         -*= .:-     \n");
	printf("\t\t\t\t\t\t\t            .=*=-**   :    .+==========+=============================+.   :+.  ****-      \n");
	printf("\t\t\t\t\t\t\t               +**+--*:   :+========+*= :*==============*:.+*=========+.   +*+**+*=       \n");
	printf("\t\t\t\t\t\t\t              -*+.-***=.  +=========##+:+%%+============+%%-.+#*====+====+.-+****  -*:      \n");
	printf("\t\t\t\t\t\t\t             .*-  =*--*#**+=++++++==######+=====++======%%#####==*****+*###+- -*-  .=      \n");
	printf("\t\t\t\t\t\t\t             .    :     -####++++**=+****+======++======+****+=**+**####*      .          \n");
	printf("\t\t\t\t\t\t\t                         ++*###*++*+==++=+++++*-.:++++++==++==**+#%%#%%#*+-                 \n");
	printf("\t\t\t\t\t\t\t                       .:+##%%##*+++*=======+*+==+===+*========*+++*####%%#*+=-:            \n");
	printf("\t\t\t\t\t\t\t                  :-=*#*=-+++*++++*+=========+=====++=========**++++*==-.::-==++=-        \n");
	printf("\t\t\t\t\t\t\t                --::.    .+==+*****============================****+====                  \n");
	printf("\t\t\t\t\t\t\t                        .+==============================================+.                \n");
	printf("\t\t\t\t\t\t\t                        +=======================++=======================+                \n");
	printf("\t\t\t\t\t\t\t        .              -=================+++=--:..:-=++=*=----=============               \n");
	printf("\t\t\t\t\t\t\t       .**=:           +=============-----=-+*******+*+=------=============               \n");
	printf("\t\t\t\t\t\t\t       :****+==*=      +=============------=**+++++**##-----===+=========+*..::::.        \n");
	printf("\t\t\t\t\t\t\t       -**#****#-      ++=========**+====+=+-        .-:-===**##*+=====+++%%%%%%%%%%%%%%%%%%*=     \n");
	printf("\t\t\t\t\t\t\t    :=**##########-    =++++++==*****=-=+=    ............::.-+####**++++**=::::-+%%%%%%*    \n");
	printf("\t\t\t\t\t\t\t    .-=*#%%%%%%%%%%%%%%%%=      *+++++*****-.........................::-+*######*+.   ..-+###+    \n");
	printf("\t\t\t\t\t\t\t        .%%%%%%%%%%%%%%-        +**####*=---------------------------------=###############+:     \n");
	printf("\t\t\t\t\t\t\t        :---:=%%%%%%*:     .-#####=------------------------------------**+::--====-:.        \n");
	printf("\t\t\t\t\t\t\t              .=#%%#########+==*+----------------------------------=+=.                    \n");
	printf("\t\t\t\t\t\t\t                 .:==++=-:   -+**+==--------------------------=++**.                      \n");
	printf("\t\t\t\t\t\t\t                            -==-**+=**+-::-----::::::::-:-*++**++==+.                     \n");
	printf("\t\t\t\t\t\t\t                                 .    :                        :                          \n" RESET);
}

void mostrar_mensaje_carga_exito()
{
	limpiar_pantalla();

	printf(VERDE
	       "\n\n\n\n\t\t\t\t\t\t\t\t           ____                                  _ _                  _ \n");
	printf("\t\t\t\t\t\t\t\t          / ___|__ _ _ __ __ _  __ _    _____  _(_) |_ ___  ___  __ _| |\n");
	printf("\t\t\t\t\t\t\t\t         | |   / _` | '__/ _` |/ _` |  / _ \\ \\/ / | __/ _ \\/ __|/ _` | |\n");
	printf("\t\t\t\t\t\t\t\t         | |__| (_| | | | (_| | (_| | |  __/>  <| | || (_) \\__ \\ (_| |_|\n");
	printf("\t\t\t\t\t\t\t\t          \\____\\__,_|_|  \\__, |\\__,_|  \\___/_/\\_\\_|\\__\\___/|___/\\__,_(_)\n");
	printf("\t\t\t\t\t\t\t\t                         |___/                                          \n\n\n" RESET);

	printf(MARRON_BOLD
	       "\t\t\t\t\t\t\t                              .                                                           \n");
	printf("\t\t\t\t\t\t\t                         .- :*#:                                                          \n");
	printf("\t\t\t\t\t\t\t                        -##*###=-:.                                                       \n");
	printf("\t\t\t\t\t\t\t                       -############*:                                                    \n");
	printf("\t\t\t\t\t\t\t                     :=##########+=:                                                      \n");
	printf("\t\t\t\t\t\t\t                  :+##*+########*                                                         \n");
	printf("\t\t\t\t\t\t\t               .=#*=:   .-=*=:-==.                                 .::..                  \n");
	printf("\t\t\t\t\t\t\t             .+#+.                                              :+*+===+**-               \n");
	printf("\t\t\t\t\t\t\t            +#+.                       :=+*#*+-.               +*-:::::--=##-             \n");
	printf("\t\t\t\t\t\t\t          :##:                       :*+=---=*##=             **.........:*##:            \n");
	printf("\t\t\t\t\t\t\t         =##.                       =#--::....-##+           :#=..........*##=            \n");
	printf("\t\t\t\t\t\t\t        =##.                        #+-:.......-##:          :#=.........=###.            \n");
	printf("\t\t\t\t\t\t\t       -##-                         +#-.........+#+           #+.......:*###:             \n");
	printf("\t\t\t\t\t\t\t       ##*                           =#=........-#*           =#:...:=*###=               \n");
	printf("\t\t\t\t\t\t\t      =##-                            .+#*=:....-#*:-=++++++++=*+-=*##*=:                 \n");
	printf("\t\t\t\t\t\t\t      *##.                               :=+***+++++++++++++++++++*+:                     \n");
	printf("\t\t\t\t\t\t\t      ###                       ..  -+        =++=++++++++++++-*+++++=.      #:           \n");
	printf("\t\t\t\t\t\t\t      ###                        :+*#=-*    :+++%%+#+++++++++#%%#%%+++++++-  .*.*#++=.       \n");
	printf("\t\t\t\t\t\t\t      ###                         =*:+#*+-. ***+#%%#+++=++++++%%%%#+*****+++-+##++#          \n");
	printf("\t\t\t\t\t\t\t      *##:                        -  +. .-+*#***+++*#*=****+++++*****####*-.=: =-         \n");
	printf("\t\t\t\t\t\t\t      -##=                          .:-=+++*##**++++*+==+*++++++****###**+-               \n");
	printf("\t\t\t\t\t\t\t       ###.                        ....     ***+++++++++++++++++**********#*=:            \n");
	printf("\t\t\t\t\t\t\t       -##+                                 :+++++++++=+++++++++++***++++++..::.          \n");
	printf("\t\t\t\t\t\t\t        *##=                              .=+++++++=:...-=+++++++++++++++++:              \n");
	printf("\t\t\t\t\t\t\t        .###-                            :+++++++++:....-++++++++++++++++++.              \n");
	printf("\t\t\t\t\t\t\t         .###=                          :+++++--=+:.....:=+===+++++++++++++               \n");
	printf("\t\t\t\t\t\t\t          .*##+                         *++++=-...........:.::.+++++++++++=               \n");
	printf("\t\t\t\t\t\t\t            *##*:                       *++++++..........-++++=*+++++++++*.               \n");
	printf("\t\t\t\t\t\t\t             =###+.                     ++++++-..........=+++++*+++++++**:                \n");
	printf("\t\t\t\t\t\t\t              .+###+:                   :+++-............:=++++++++++***:                 \n");
	printf("\t\t\t\t\t\t\t                .=###*=.                 -**+-:...........:-++++++****=                   \n");
	printf("\t\t\t\t\t\t\t                   :+###*+-.              .+****++======+++++*******=.                    \n");
	printf("\t\t\t\t\t\t\t                      :=*####*+==-:::.......=*######*************=:                       \n");
	printf("\t\t\t\t\t\t\t                          :-=+*#####################******++=-:.                          \n");
	printf("\t\t\t\t\t\t\t                                 .:::--------:::..                                        \n" RESET);
}

void mostrar_dirigiendo_a_pokedex()
{
	printf(VERDE
	       "\n\n\t\t\t\t\t\t\t\t   █▀▄ █ █▀█ █ █▀▀ █ █▀▀ █▄░█ █▀▄ █▀█   ▄▀█   █▀█ █▀█ █▄▀ █▀▀ █▀▄ █▀▀ ▀▄▀ \n");
	printf("\t\t\t\t\t\t\t\t   █▄▀ █ █▀▄ █ █▄█ █ ██▄ █░▀█ █▄▀ █▄█   █▀█   █▀▀ █▄█ █░█ ██▄ █▄▀ ██▄ █░█ ▄ ▄ ▄\n" RESET);
}

void mostrar_mensaje_carga_fallida()
{
	limpiar_pantalla();

	printf("\n\t\t\t\t\t\t\t\t  ___  _                   _      _    _                         _ _                         _ \n");
	printf("\t\t\t\t\t\t\t\t / _ \\| |__    _ __   ___ | |    / \\  | | __ _  ___    ___  __ _| (_) ___    _ __ ___   __ _| |\n");
	printf("\t\t\t\t\t\t\t\t| | | | '_ \\  | '_ \\ / _ \\| |   / _ \\ | |/ _` |/ _ \\  / __|/ _` | | |/ _ \\  | '_ ` _ \\ / _` | |\n");
	printf("\t\t\t\t\t\t\t\t| |_| | | | | | | | | (_) |_|  / ___ \\| | (_| | (_) | \\__ \\ (_| | | | (_) | | | | | | | (_| | |\n");
	printf("\t\t\t\t\t\t\t\t \\___/|_| |_| |_| |_|\\___/(_) /_/   \\_\\_|\\__, |\\___/  |___/\\__,_|_|_|\\___/  |_| |_| |_|\\__,_|_|\n");
	printf("\t\t\t\t\t\t\t\t                                         |___/                                                 \n\n");

	printf("\t\t\t\t\t\t\t\t                                                :                                         \n");
	printf("\t\t\t\t\t\t\t\t                                             -*%%#                                         \n");
	printf("\t\t\t\t\t\t\t\t                                            *%%%%%%.                                         \n");
	printf("\t\t\t\t\t\t\t\t                                            *%%%%*                                          \n");
	printf("\t\t\t\t\t\t\t\t                                          .*%%%%%%%%+                                         \n");
	printf("\t\t\t\t\t\t\t\t                                         +%%%%%%%%%%%%-                                         \n");
	printf("\t\t\t\t\t\t\t\t                                        %%%%%%%%%%%%%%+                                          \n");
	printf("\t\t\t\t\t\t\t\t                                       -%%%%#++++=                                          \n");
	printf("\t\t\t\t\t\t\t\t                                       =++======                                          \n");
	printf("\t\t\t\t\t\t\t\t                                      -+========                                          \n");
	printf("\t\t\t\t\t\t\t\t                                     -=========-                                          \n");
	printf("\t\t\t\t\t\t\t\t                                    .+=========-                                          \n");
	printf("\t\t\t\t\t\t\t\t                                    +=========+                                           \n");
	printf("\t\t\t\t\t\t\t\t                                   -+=========+                                           \n");
	printf("\t\t\t\t\t\t\t\t                                :-=============+-.                                        \n");
	printf("\t\t\t\t\t\t\t\t                             .-====================.                                      \n");
	printf("\t\t\t\t\t\t\t\t                           :========***==============                                     \n");
	printf("\t\t\t\t\t\t\t\t                         .===+===*#@%%%%@+=============+:...:::--====###*:                  \n");
	printf("\t\t\t\t\t\t\t\t                         +=+****+%%%%%%%%@#================+===========*%%%%%%%%*.                \n");
	printf("\t\t\t\t\t\t\t\t                         ++****+=++**+==========*###*+============#%%%%%%%%%%%%#:               \n");
	printf("\t\t\t\t\t\t\t\t                         +=*+++@+==============#@@#@##=============-=*%%%%%%%%%%=              \n");
	printf("\t\t\t\t\t\t\t\t                         .+===+@*=-----------=*@#@%%@#*========-:.      -*%%%%%%#-            \n");
	printf("\t\t\t\t\t\t\t\t                          -=-::@#++++-::::::::-@%%%%@@*====+=:.             =#%%%%            \n");
	printf("\t\t\t\t\t\t\t\t                           --::-+==+*@=::::::::::=-:::-=+.                  -=            \n");
	printf("\t\t\t\t\t\t\t\t                            :-:::::::*@#*=::::=++++::::-:        :-++.                    \n");
	printf("\t\t\t\t\t\t\t\t                              --::::::::=@*=*#%%+*+=:::-:     .-+######                    \n");
	printf("\t\t\t\t\t\t\t\t                              ===-::::::::+##*+++=-::-.    -*#########-                   \n");
	printf("\t\t\t\t\t\t\t\t                             +=======--:::::--=-:::--    =############=                   \n");
	printf("\t\t\t\t\t\t\t\t                            ==============+=---:::.    -*#############:                   \n");
	printf("\t\t\t\t\t\t\t\t                           +===============*         :*##########**+-                     \n");
	printf("\t\t\t\t\t\t\t\t                          =====--:::::::---=+-      .########**+=:.                       \n");
	printf("\t\t\t\t\t\t\t\t                         :==-::::::::::::::::-=      -####*=-:                            \n");
	printf("\t\t\t\t\t\t\t\t                         =:::::::+=::::#=::::::=.   .+####*                               \n");
	printf("\t\t\t\t\t\t\t\t                        -::::::::*+::::**:::::::=  =++****+.                              \n");
	printf("\t\t\t\t\t\t\t\t                       .-::::::::--:::::-::::::::= .++++-                                 \n");
	printf("\t\t\t\t\t\t\t\t                       -:::::::::::::::::::::::::-. -*++:                                 \n");
	printf("\t\t\t\t\t\t\t\t                       =::::::::::::::::::::::::::=*+=:                                   \n");
	printf("\t\t\t\t\t\t\t\t                .-==---::::::::::::::::::::::::::::-=-::                                  \n");
	printf("\t\t\t\t\t\t\t\t                .-=*##*+-:::::::::::::::::::::::::---::::--                               \n");
	printf("\t\t\t\t\t\t\t\t               :==---=*+=---::=%%*-:-::-*#*=---:::+#%%%%%%:...                                \n");
	printf("\t\t\t\t\t\t\t\t                         .          ..  .:    ..::  ..                                    \n");
}

void mostrar_titulo_pokedex()
{
	limpiar_pantalla();

	printf("\n\t\t\t\t\t\t\t\t _ _____     _                      _           ____       _            _           _ \n");
	printf("\t\t\t\t\t\t\t\t(_) ____|___| |_ __ _    ___  ___  | |_ _   _  |  _ \\ ___ | | _____  __| | _____  _| |\n");
	printf("\t\t\t\t\t\t\t\t| |  _| / __| __/ _` |  / _ \\/ __| | __| | | | | |_) / _ \\| |/ / _ \\/ _` |/ _ \\ \\/ / |\n");
	printf("\t\t\t\t\t\t\t\t| | |___\\__ \\ || (_| | |  __/\\__ \\ | |_| |_| | |  __/ (_) |   <  __/ (_| |  __/>  <|_|\n");
	printf("\t\t\t\t\t\t\t\t|_|_____|___/\\__\\__,_|  \\___||___/  \\__|\\__,_| |_|   \\___/|_|\\_\\___|\\__,_|\\___/_/\\_(_)\n\n\n");
}