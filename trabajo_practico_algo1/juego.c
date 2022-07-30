#include<stdio.h>
#include <stdbool.h>
#include<stdlib.h>
#include<time.h>
#include "la_sombra_de_mac.h"

const int ESTADO_JUGANDO = 0;

int main(){
	
    srand ((unsigned)time(NULL));
	
    juego_t juego;
   
    inicializar_juego(&juego);

    imprimir_terreno(juego);

    while(estado_juego(juego)== ESTADO_JUGANDO){
      realizar_jugada(&juego);
      imprimir_terreno(juego);   
      estado_juego(juego);
    }

      
    return 0;
  
}
