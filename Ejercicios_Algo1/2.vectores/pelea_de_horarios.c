/*  ENUNCIADO


En Cartoon Network hay una fuerte discusión sobre qué programa debería pasarse a la mañana, cuando los chicos despiertan para ir al colegio. 
Para hacerlo de una manera justa, se le dio a cada personaje un número aleatorio entre el 0 y el 100 (ambos inclusive) y los fueron anotando en un vector. 
Y decidieron que, el que tenga el número más chico, tendrá la suerte de salir al aire en ese horario.

    Implementar una función que dado un vector con los números aleatorios, devuelva el índice del más chico.

    Además, implementar una función que dado un vector donde cada posición representa un programa y el vector de números aleatorios, 
    devuelva el programa al cual le corresponde el número más chico.

Tener en cuenta:

    Los programas son representados con la inicial de su nombre, o “-” en caso de que no haya uno.
    Ambos vectores pueden tener topes diferentes. En el caso de que el índice del número más chico caiga por fuera del vector de programas 
    se debe devolver '-'.
    Si el vector de programas o el de aleatorios está vació se debe devolver '-'.

Ejemplo:

    Teniendo el vector de programas ['T', 'S', '-'] y el vector de números aleatorios [2, 0, 5]. El número más chico de los aleatorios es el 0 (cero) 
    en el indice 1, por lo que la función programa_ganador debería devolver 'S'.

*/
// RESOLUCION 



#include <stdio.h>
#include <stdbool.h>
#define MAX_NUMEROS 100


int numero_mas_chico(int numeros[MAX_NUMEROS], int tope_numeros) {
    int posicion_mas_chica = numeros[0];
    int numero_chico = 0;
        for(int j = 1; j< tope_numeros; j++){
            if(numeros[j]< posicion_mas_chica){
                posicion_mas_chica = numeros[j];
                numero_chico = j;
            }
        }

    return numero_chico;
}

char programa_ganador(char programas[MAX_NUMEROS], int tope_programas, int numeros[MAX_NUMEROS], int tope_numeros) {
    char programa_inicial ='-';
    int i =0;
    bool encontrado = false;
    while(i<tope_programas && !encontrado){
      if( i == numero_mas_chico(numeros, tope_numeros)){
          programa_inicial = programas[i];
          encontrado = true;
      }
      i++;
    }
    return programa_inicial;
}