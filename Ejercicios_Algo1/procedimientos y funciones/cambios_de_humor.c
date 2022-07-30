
/* ENUNCIADO

Los tres queridos osos atraviesan varios cambios de humor a lo largo de un año según la estación.
 Por lo que los expertos en osos nos dijeron (osea, lo que nos dijo Chloe) que por cada estación del año, cada oso pasa por un humor diferente.
Los humores por lo que pueden pasar son los siguientes:

    Contento (C)
    Meh (M)
    Triste (T)

Y estos son lo cambios que logramos anotar:

-Primavera (P): Panda y Pardo están contentos, mientras que Polar está meh.
-Verano (V): Polar está triste, Panda está meh y Pardo está contento.
-Otoño (O): los tres osos están contentos (obvio, si es la mejor estación).
-Invierno (I): Polar está contento, Panda está meh y Pardo está triste.

    Implementar una función que dada la estación del año, modifique el humor de cada oso al correspondiente, 
    y devuelva la cantidad de osos que están contentos.

*/ 

// RESOLUCION

#include <stdio.h>
const char CONTENTO = 'C';
const char MEH = 'M';
const char TRISTE = 'T';
const char PRIMAVERA = 'P';
const char VERANO = 'V';
const char OTONIO = 'O';
const char INVIERNO = 'I';

int definir_humor_osos(char* humor_panda, char* humor_pardo, char* humor_polar, char estacion){
    if (estacion == PRIMAVERA){
        *humor_panda = CONTENTO;
        *humor_pardo = CONTENTO;
        *humor_polar = MEH;
        return 2;
    }else if (estacion == VERANO){
        *humor_panda = MEH;
        *humor_pardo = CONTENTO;
        *humor_polar = TRISTE;
        return 1;
    }else if (estacion == OTONIO){
        *humor_panda = CONTENTO;
        *humor_pardo = CONTENTO;
        *humor_polar = CONTENTO;
        return 3;
    }else{
        *humor_panda = MEH;
        *humor_pardo = TRISTE;
        *humor_polar = CONTENTO;
        return 1;
    }
}