
/* ENUNCIADO

Los chicos del barrio están por ir a una misión, y necesitan averiguar quién es el más hábil para que en caso de pelea, éste luche primero. 
Los que están disponibles para la misión son número 1 (1), número 3 (3) y número 5 (5).
Para cada uno de los chicos, se dispone de un vector donde se encuentra el puntaje de inteligencia (posición 0), resistencia física (posición 1), 
agilidad (posición 2) y fuerza (posición 3).
Para calcular quién es el más habil, se suma la inteligencia, el triple de resistencia física, el doble de agilidad, y la fuerza.

    Implementar una función que calcule dicho valor, y devuelva quién es el que deberá luchar primero.

Ejemplo:

    Si se reciben los vectores 1: [4,3,8,2], 3: [5,1,9,3] y 5: [4,8,7,1], siendo el resultado de cada uno 31, 29 y 43 respectivamente, se debe devolver 5.
*/

	// RESOLUCION


#include <stdio.h>
#define MAX_HABILIDADES 4
const int numero_1 = 1;
const int numero_5 = 5;
const int numero_3 = 3;
const int numero_2 = 2;
int agente_mas_habil(int habilidades_1[MAX_HABILIDADES], int habilidades_3[MAX_HABILIDADES], int habilidades_5[MAX_HABILIDADES]){
	int contador_1 = 0;
	int contador_3 = 0;
	int contador_5 = 0;
	int debera_luchar;
     contador_1= habilidades_1[0] + numero_3*habilidades_1[1]+ numero_2*habilidades_1[2] + habilidades_1[3];
	 
	 contador_3= habilidades_3[0] + numero_3*habilidades_3[1]+ numero_2*habilidades_3[2] + habilidades_3[3];
	
	 contador_5= habilidades_5[0] + numero_3*habilidades_5[1]+ numero_2*habilidades_5[2] + habilidades_5[3];
	
	if(contador_1 > contador_3 && contador_1 > contador_3){
		debera_luchar = numero_1;
	}else if (contador_3 > contador_1 && contador_3 > contador_5){
		debera_luchar = numero_3;
	}else if(contador_5 > contador_1 && contador_5 > contador_3){
		debera_luchar = numero_5;
	}
	return debera_luchar;
}