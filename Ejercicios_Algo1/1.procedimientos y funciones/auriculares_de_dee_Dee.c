 /* ENUNCIADO
 En su laboratorio Dexter está trabajando en un nuevo invento, algo que revolucionará su vida: unos auriculares que tapen por completo sólo 
 la voz de su hermana, para que él pueda trabajar en paz. Pese a que no logró tapar por completo su voz, la pudo amortiguar bastante, 
 por lo que quiere probar la calidad de sus nuevos auriculares. Para esto generó un rango de calidad según el volumen que le llega por los auriculares:

-Excelente (A): si el volumen amortiguado es menor o igual a 10.
-Bueno (B): si el volumen amortiguado es mayor a 10 y menor o igual a 40.
-Malo (C): si el volumen amortiguado es mayor a 40 y menor o igual a 70.
-Pésimo (D): si el volumen amortiguado es mayor a 70.

Hay que ayudar a Dexter a calcular el nivel de calidad de sus auriculares dado el volumen exterior, que en este caso ese sería el de la voz de Dee Dee.
Dado que el cálculo del volumen amortiguado es demasiado avanzado, él ya nos dejó una función que lo calcula por nosotros.

Implementar la función calcular_calidad_auriculares el cual dado el volumen de la voz de Dee Dee, devuelve el nivel de calidad.

*/ 
// RESOLUCION

#include "solucion.h"
#define EXCELENTE 'A'
#define BUENO 'B'
#define MALO 'C'
#define PESIMO 'D'
#define AMORTIGUAMIENTO 3

int volumen_amortiguado(int volumen) {
    return (volumen / AMORTIGUAMIENTO);
}

char  calcular_calidad_auriculares(int volumen){
      int calidad = volumen_amortiguado(volumen);
    if(calidad <= 10){
        return EXCELENTE;
    }else if (calidad <= 40 && calidad > 10){
        return BUENO;
    }else if (calidad <= 70 && calidad > 40){
        return MALO;
    }else{

        return PESIMO;
        }
}