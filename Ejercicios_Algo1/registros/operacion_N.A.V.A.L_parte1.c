/*	 ENUNCIADO

Los chicos del barrio se enfrentarán a Barba pegajosa, el némesis de Número 5, que se encuentra zarpando en altamar. 
Están en medio de la difícil tarea de determinar los puntos débiles de un barco de artillería que están construyendo. 
Por ahora, lograron encontrar que el barco tiene como debilidad que lo ataquen al mismo tiempo en dos puntos que estén a una cierta distancia.

    Implementar una función que con la ayuda del registro punto_t, determine la distancia entre dos puntos del barco dados y la devuelva.

Aclaración:

La distancia se calcula como distancia manhattan, que es la suma de las distancias en ambos sentidos: |x1 - x2| + |y1 - y2|

Ejemplo:

Dado como primer punto (x,y) = (1,3) y como segundo punto (x,y) = (2,6), la distancia entre estos dos puntos nos da 4.
*/

//	RESOLUCION

#include <stdio.h>
#include "solucion.h"

typedef struct punto {
	int x;
	int y;
} punto_t;

int distancia_entre_puntos(punto_t primer_punto, punto_t segundo_punto) {
	int distancia_x =primer_punto.x- segundo_punto.x;
    
	if(distancia_x < 0)
		distancia_x *= -1;
	
    int distancia_y = primer_punto.y -segundo_punto.y; 
	
	if(distancia_y < 0)
		distancia_y *=-1;
	
	return distancia_x + distancia_y;
}