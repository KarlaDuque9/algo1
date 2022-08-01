/* RESOLUCION

En la mansión foster para amigos imaginarios, tienen una lista con la cantidad de amigos imaginarios que fueron adoptados a lo largo de los días.

El señor Conejo tiene ganas de nombrar un día como el "Dia de la adopción", pero quiere que el día que sea elegido sea muy especial y tenga un significado. 
Por lo que no tuvo mejor idea que elegir el día con mayor adopciones para poder conmemorarlo.

Un día es considerado día record si la cantidad de adopciones en un día es estrictamente mayor a cualquiera de los dias anteriores.

Teniendo un vector que represente los días en números de una semana (0=domingo,1=lunes,2=martes…), 
y cada posición represente la cantidad total de adopciones concretadas en ese día:

    Implementar una función que devuelva cuál es el día record de adopciones.

Aclaraciones

-En caso de empate entre dos días, se considerará el día más cercano a la fecha como el día ganador.

Ejemplo

Si se recibe el vector [54,12,23,8,30,60,44], la mayor cantidad de adopciónes es 60, por lo que el día record sería el 5 (viernes)

*/ 
// RESOLUCION

#include <stdio.h>
#define MAXIMOS_DIAS 7

int dia_record(int adoptados[MAXIMOS_DIAS], int tope){
    int record =adoptados[0];
    int dia_record =0;
    for(int i =0; i<tope; i++){
        if( adoptados[i]>= record){
           record = adoptados[i];
           dia_record = i;
        }
    }
    return dia_record;
}