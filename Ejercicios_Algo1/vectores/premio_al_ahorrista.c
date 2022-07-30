/*	ENUNCIADO

Después de varios días de ahorros, Ed, Edd y Eddy por fin pudieron comprar su tan deseado rompemuelas. El tema es que solo lograron comprar uno 
y no se dignan a compartirlo. Por lo que llegaron a un acuerdo: el que haya ahorrado más plata en un día, se puede quedar con el rompemuelas, 
y le describe al resto el sabor así no se sienten tan dejados de lado.
Recordemos que tenían sus ahorros en un vector donde cada posición corresponde a un día diferente. Esto quiere decir que en la posición 0 (cero) 
del vector vamos a tener el día 1 (uno), luego la 2 (dos) y así.

    Implementar una función que dado el vector con los ahorros devuelva quién es el ganador.
    Se sabe que en los días pares ahorró solo Edd, en los impares múltiplos de 5 ahorró Ed y en el resto ahorró Eddy.

Tener en cuenta:

    El ganador es el que más ahorró en un día, no en total.
    Cada ganador se representa con un char:
        Ed (E)
        Edd (D).
        Eddy (Y).
    En el caso de que no haya ahorros, es decir, que el vector de ahorros esté vacío, se debe devolver N de nadie.

Ejemplo:

    Si se recibe el vector [1, 4, 2, 8] los números de días que corresponden son [1, 2, 3, 4]. Como el 8 es el mayor y cae el día 4 el ganador es Edd 
    y se debe devolver D.
*/

// RESOLUCION

#include <stdio.h>
#define MAX_AHORROS 256
const char ED = 'E';
const char  EDD = 'D';
const char EDDY = 'Y';
const char NINGUNO = 'N';


char ganador_ahorrista(int ahorros[MAX_AHORROS], int tope_ahorros) {
    int mayor=0;
    int dia;
    char ganador; 
    for (int i=0; i< tope_ahorros;i++){
        if(ahorros[i] > mayor){
            mayor = ahorros[i];
            dia = i+ 1;
        }
    }
    if(ahorros[0] == '\0'){
         ganador = NINGUNO;
    }else if(dia%2 == 0){
        ganador = EDD;
    }else if(dia%5 == 0 && dia%2!= 0){
       ganador= ED; 
    }else{
          ganador = EDDY;
      }
    
  
  return ganador;
}
