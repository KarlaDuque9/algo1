/*	ENUNCIADO

En el camino al taller, las pancitas de los amigos imaginarios empezaron a gruñir. (https://youtu.be/Ay1BbFMVMsg?t=45). 
Ahora deberán decidir a dónde comprar comida para llevar, pero considerando que restaurante es lo suficientemente rápido.

    Dado el registro restaurante_t que contiene al registro empleados_t, calcular la velocidad de preparación, y devolver L si el restaurante es lento, 
    M si el restaurante es muy lento, o R si el restaurante es rápido.
    Se debe tener en cuenta:

-Si los empleados tienen un delay mayor(estricto) a 5 minutos, se considerará Lento.
-Si los empleados están de franco, se considerará Muy lento.
-Si el restaurante está cerrado, se considerará Muy lento.
-Si el restaurante no es de comida rápida, se considerará Lento.
-En otro caso, se considerará Rápido.

Aclaración:
Si un restaurante cumple las condiciones de lento y muy lento a la vez, se considerará Muy lento.

*/

//	RESOLUCION

#include "solucion.h"
const char MUY_LENTO ='M';
const char LENTO ='L';
const char RAPIDO = 'R';
typedef struct empleados {
	int delay_en_entregar; //en minutos
	bool estan_de_franco;
} empleados_t;

typedef struct restaurante{
	empleados_t empleados;
	bool cerrado;
	bool es_de_comida_rapida;
} restaurante_t;

char velocidad_del_restaurante(restaurante_t restaurante) {
	
    if(restaurante.cerrado)
        return MUY_LENTO;
    if(restaurante.empleados.estan_de_franco)
        return MUY_LENTO;
    if(restaurante.empleados.delay_en_entregar > 5)
        return LENTO;
    if(!restaurante.es_de_comida_rapida)
        return LENTO;
    return RAPIDO;
}