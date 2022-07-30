/* ENUNCIADO

Ed se volvió fanático de la astrología, por lo que empezó a leer libros y buscar información de cada signo. 
Para probar sus conocimientos, quiso hacerles unas preguntas a Edd y Eddy y tratar de adivinar de qué signo son. 
Para facilitarse el trabajo, les hizo las preguntas a los dos al mismo tiempo y en cada posición de un vector fue marcando S si ambos respondieron que sí, 
N si ambos respondieron que no, E si sólo Edd respondió que sí, y D Si sólo Eddy respondió que sí.
Tiene como información adicional que los signos de ambos solamente pueden ser piscis, libra, acuario o cáncer.

    Implementar una función que calcule cuántas respuestas positivas tuvieron tanto Edd como Eddy, y a partir de este resultado, 
    retorne true si son del mismo signo, o false en caso contrario.

-Entre 0 y 2: Libra (L).
-Entre 3 y 5: Piscis(P).
-Entre 6 y 8: Acuario(A).
-Más de 8: Cáncer(C).
*/

// RESOLUCION

#include <stdio.h>
#include <stdbool.h>
#define MAX_RESPUESTAS 300
const char RESPONDEN = 'S';
const char NO_RESPONDEN = 'N';
const char RESPONDE_EDD = 'E';
const char RESPONDE_EDDY = 'D';

bool tienen_mismo_signo(char respuestas[MAX_RESPUESTAS], int tope_respuestas) {
	int contador_edd = 0;
	int contador_eddy = 0;
	for (int i = 0; i< tope_respuestas; i++){
        if(respuestas[i]== RESPONDEN){
			contador_edd ++;
			contador_eddy ++;
		}else if(respuestas[i] == RESPONDE_EDD){
            contador_edd ++;
		}else if(respuestas[i] == RESPONDE_EDDY){
			contador_eddy ++;
		}	
	}
	return contador_edd == contador_eddy;
}