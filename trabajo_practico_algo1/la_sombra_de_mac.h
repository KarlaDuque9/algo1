#ifndef __LA_SOMBRA_DE_MAC__
#define __LA_SOMBRA_DE_MAC__
#include <stdbool.h>
#include <stdio.h>

#define MAX_FILAS 20
#define MAX_COLUMNAS 25
#define MAX_ELEMENTOS 500
#define MAX_NIVELES 3
#define MAX_PAREDES 200
#define MAX_PARTIDAS 60
#define MAX_NOMBRE 100
#define MAX_GANO 10

typedef struct coordenada {
    int fila;
    int col;
}coordenada_t;

typedef struct personaje {
    coordenada_t posicion;
    int vida;
    int puntos;
    bool tiene_llave;
    bool interruptor_apretado;
}personaje_t;

typedef struct sombra {
    coordenada_t posicion;
    bool esta_viva;
}sombra_t;

typedef struct elemento {
    char tipo;
    coordenada_t coordenada;
}elemento_t;

typedef struct nivel {
    int numero_nivel;
    coordenada_t paredes[MAX_PAREDES];
    int tope_paredes;
    elemento_t obstaculos[MAX_ELEMENTOS];
    int tope_obstaculos;
    elemento_t herramientas[MAX_ELEMENTOS];
    int tope_herramientas;
}nivel_t;

typedef struct juego {
    personaje_t personaje;
    sombra_t sombra;
    nivel_t niveles[MAX_NIVELES];
    int nivel_actual;
}juego_t;

typedef struct partida{
    char jugador[MAX_NOMBRE];
    int nivel_llegado;
    int puntos;
    int vidas_restantes;
    bool gano;
}partida_t;


/*
 * Procedimiento que recibe el juego e imprime toda su información por pantalla.
 */
void imprimir_terreno(juego_t juego);

/* 
 *Inicializará el juego, cargando toda la información inicial, los datos del personaje, y los 3 niveles.
 */
void inicializar_juego(juego_t* juego);

/*
 * Recibe un juego con todas sus estructuras válidas.
 *
 * El juego se dará por ganado, si terminó todos los niveles. O perdido, si el personaje queda
 * sin vida. 
 * Devolverá:
 * -> 0 si el estado es jugando. 
 * -> -1 si el estado es perdido.
 * -> 1 si el estado es ganado.
 */
int estado_juego(juego_t juego);

/*
 * El nivel se dará por terminado, si ambos personajes pasaron por la puerta teniendo la 
 * llave correspondiente.
 * Devolverá:
 * -> 0 si el estado es jugando.
 * -> 1 si el estado es ganado.
 */
//int estado_nivel(juego_t juego);

/*
 * Moverá el personaje, y realizará la acción necesaria en caso de chocar con un elemento
 */
void realizar_jugada(juego_t* juego);

/* procedimiento que recibe una partida_t por referencia y un string y se encarga de pedirle al usuario 
 * los datos de la partida que quiere agregar y debe escriirlo en orden  como se pide el nivel entre 1 y 3 y  las vidas tambien entre 1 y 3 y lo guarda en la partida_t y en el string guarda si gano o no el juego
 * 
 */
void preguntar_al_usuario(partida_t* partida, char gano[MAX_GANO]);

/* procedimiento que recibe el archivo original y un archivo auxiliar y se encarga de agregar la partida que el usuario 
 * quiere agregar al archivo auxiliar y escribe todas las partidas del archivo originak en el auxiliar incluyendo la partida q se quiere agregar
 */
void agregar_partida(FILE* partida,FILE* partidas_aux  , partida_t partida_agregar);

/* procedimiento que recibe el archivo original y un archivo auxiliar encarga de escribir lo que tiene el archivo origimal menos  la partida que el usuario quiere eliminar
 * 
 */
void eliminar_partida(FILE* partida , FILE* partidas_aux , char jugador_eliminar[MAX_NOMBRE]);

/* procedimiento que recibe un archivo , un tope por referencia, un vector de partidas y se encarga de  
 * de llenar a un vector con los datos que tiene un archivo
 */
void llenar_vector(FILE* partida ,int* tope_partidas,partida_t partidas[MAX_PARTIDAS] , char gano[MAX_GANO]);

/* procedimiento que recibe un vector de partidas y su tope y se encarga 
 * de ordenar el vector de partidas 
 */
void ordenar_vector( partida_t partidas[MAX_PARTIDAS], int tope_partidas);  


/* procedimiento que recibe el archivo original y un archvo auxiliar  y se encarga de 
 * ordenar las partidas y escrbirlas en orden en el archivo auxiliar 
 */
void ordenar_partidas(FILE* partida , FILE* partidas_aux);


#endif