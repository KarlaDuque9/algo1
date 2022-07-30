/*	ENUNCIADO

El director Buenavibra ha notado un ascenso inusual en las notas de la mayoría de los estudiantes y cree que se debe a que se están copiando. 
Gracias a su contacto en Whatsapp inc, ha interceptado los mensajes que se envían por un grupo de estudiantes.
Estos mensajes tienen la siguiente información:
-Si tiene palabras relacionadas con el colegio (bool).
-Cantidad de palabras que contiene (int).
-Cantidad de respuestas al mensaje (int).
-Si el autor es sospechoso (bool).

    Dado un mensaje del tipo mensaje_t, calcular y devolver el índice de probabilidad de que sea un mensaje con la intención de copiarse.

Aclaración:

Sabemos la probabilidad de copiarse según las siguientes reglas:

    Todo mensaje empieza con una probabilidad de copia de 5 puntos.
    Si el mensaje tiene palabras relacionadas al colegio, la probabilidad aumenta 2 puntos, sino disminuye 2 puntos.
    Si el mensaje es muy largo (tiene más de 50 palabras, estricto) la probabilidad aumenta 2 puntos, sino disminuye 1 punto.
    Si el mensaje tiene una alta cantidad de respuestas (más que 3, estricto) la probabilidad aumenta 2 puntos, sino se mantiene igual.
    Si el mensaje fue escrito por un alumno cuyas calificaciones aumentaron (aka: autor sospechoso), la probabilidad aumenta 3 puntos, sino disminuye 1 punto.

Ejemplo:

Si tenemos la siguiente información del mensaje:

    tiene_palabras_de_colegio = true. (aumenta 2).
    cantidad_de_palabras = 50. (disminuye 1).
    cantidad_de_respuestas = 2. (mantiene).
    autor_sospechoso = true. (aumenta 3).

La probabilidad nos quedaría:
5 + 2 - 1 + 0 + 3 = 9

Recuerden los 5 puntos iniciales. 
*/

//	RESOLUCION

#include <stdio.h>
#include "solucion.h"
const int numero_1 = 1;
const int numero_2 = 2;
const int numero_3 = 3;
const int numero_5 = 5;
const int numero_50 = 50;

typedef struct mensaje {
    bool tiene_palabras_de_colegio;
    int cantidad_de_palabras;
    int cantidad_de_respuestas;
    bool autor_sospechoso;
} mensaje_t;

int indice_de_probabilidad_de_copia(mensaje_t mensaje){
    
    int probabilidad = numero_5;
    if(mensaje.tiene_palabras_de_colegio){
     probabilidad += numero_2;
    }else{
     probabilidad -=numero_2;
    }
    
    if(mensaje.cantidad_de_palabras > numero_50){
        probabilidad += numero_2;
    }else{
        probabilidad -= numero_1;
    }
    
    if(mensaje.cantidad_de_respuestas > numero_3){
        probabilidad += numero_2;
    }
    
    if(mensaje.autor_sospechoso){
    probabilidad += numero_3;
    }else{
        probabilidad -= numero_1;
    }
 return probabilidad;
}