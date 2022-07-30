#include "la_sombra_de_mac.h"
#include "utiles.h"
#include <stdio.h>
#include<stdlib.h>
#include<time.h>

#define IZQUIERDA 'A'
#define DERECHA 'D'
#define ARRIBA 'W'
#define ABAJO 'S'
#define IMAGEN_MAC "\U0001F9D2"
#define IMAGEN_VACIO "\U0001F7EB"
#define IMAGEN_BLOO "\U0001F47B"
#define IMAGEN_PARED "\U0001F7EA"
#define IMAGEN_ESCALERAS "\U0001FA9C"
#define IMAGEN_MONEDAS "\U0001F7E1"
#define IMAGEN_LLAVES "\U0001F5DD "
#define IMAGEN_PUERTA "\U0001F6AA"
#define IMAGEN_POZOS "\U0001F573 "
#define IMAGEN_INTERRUPTOR "\U0001F5B2"
#define IMAGEN_VELAS "\U0001F56F"
#define IMAGEN_PORTAL "\U0001F387"
#define IMAGEN_VIDAS "\U00002764"
#define MATRIZ_VELAS "\U0001F7E8"



const char VIDAS = 'V';
const char MAC = 'M';
const char BLOO = 'B';
const int VIDA = 3;
const int PUNTOS_AL_INICIO = 0;
const int REVIVIR = 50;
const int NO_ENCONTRADO = -1;
const int PUNTOS_VIDA = 200;
const int JUEGO_GANADO = 1;
const int JUGANDO = 0;
const int PERDIDO = -1;
const int MAX_PUNTOS = 11;
const int  MIN_PUNTOS = 10;
const char PUERTA = 'D';
const char VACIO = ' ';
const char ESCALERAS = 'E';
const char LLAVE = 'L';
const char MONEDAS = 'C';
const char POZOS = 'W';
const char INTERRUPTORES = 'O';
const char PORTALES = 'P';
const char VELAS = 'V';
const char PAREDES = 'X';
const int POS_NIVEL_1 = 0;
const int POS_NIVEL_2 = 1;
const int POS_NIVEL_3 = 2;
const int SIN_VIDA = 0;
const int PRIMER_NIVEL =1;
const int SEGUNDO_NIVEL =2;
const int TERCER_NIVEL =3;
const int ESCALERAS_NIVEL_UNO = 10;
const int MONEDAS_NIVEL_UNO = 10;
const int CANT_PUERTA = 1;
const int POZOS_NIVEL_UNO = 15;
const int VELAS_NIVEL_UNO = 5;
const int INTERRUPTOR_NIVEL_UNO = 1;
const int ESCALERAS_NIVEL_DOS = 15;
const int MONEDAS_NIVEL_DOS = 15;
const int CANT_LLAVE = 1;
const int VELAS_NIVEL_DOS = 10;
const int INTERRUPTOR_NIVEL_DOS = 2;
const int PORTALES_NIVEL_DOS = 2;
const int POZOS_NIVEL_DOS = 20;
const int ESCALERAS_NIVEL_TRES= 15;
const int MONEDAS_NIVEL_TRES = 15;
const int VELAS_NIVEL_TRES = 12;
const int INTERRUPTOR_NIVEL_TRES = 4;
const int PORTALES_NIVEL_TRES = 4;
const int POZOS_NIVEL_TRES = 30;
const int DISTANCIA_ADELANTE = 1;
const int DISTANCIA_ATRAS = -1;
const int IGUAL_DISTANCIA  = 0;

/*
* Función que recibe dos coordenadas, devuelve true si las
* coordenadas son iguales, sino false.
*/
bool coordenadas_iguales(coordenada_t a, coordenada_t b){
    return (a.fila == b.fila) && (a.col==b.col);
}


/*
* Función que dados una altura máxima y un ancho máximo
* devuelve una coordenada aleatoria. Una posición nunca podrá
* tener un valor negativo, ni ser mayor a sus máximos.
*/
coordenada_t coordenada_aleatoria(int max_alto, int max_ancho){
    coordenada_t coordenada;
    coordenada.col = rand() %max_ancho;
    coordenada.fila = rand()%max_alto;
    return coordenada;
}


/*
* Procedimiento que dejará la estructura personaje_t en un
* estado válido para iniciar el juego.
* 'arranque_personaje' es un parámetro que representa la posición 
* en la arrancará el personaje.
*/
void inicializar_personaje(personaje_t* ref_personaje, coordenada_t arranque_personaje){
    ref_personaje->posicion = arranque_personaje;
    ref_personaje->vida = VIDA;
    ref_personaje->puntos = PUNTOS_AL_INICIO;
    ref_personaje->tiene_llave = false;
    ref_personaje->interruptor_apretado = false;
}

/*
* Procedimiento que dejará una estructura elemento_t que
* represente a la sombra, en un estado válido para iniciar el juego. 
* 'arranque_sombra' es un parámetro que representa la posición 
* en la arrancará la sombra.
*/
void inicializar_sombra(sombra_t* ref_sombra, coordenada_t arranque_sombra){
    (*ref_sombra).posicion = arranque_sombra;
    ref_sombra->esta_viva = true;
}

/*
*   La función recibe un caracter y devuelve true
* si el movimiento recibido concuerda con la convención
* propuesta, sino false.
* -> W: Si el personaje debe moverse para la arriba. 
* -> A: Si el personaje debe moverse para la izquierda.
* -> S: Si el personaje debe moverse para la abajo.
* -> D: Si el personaje debe moverse para la derecha.
*/
bool es_movimiento_valido(char movimiento){
    return (movimiento == IZQUIERDA || movimiento == DERECHA || movimiento == ARRIBA || movimiento == ABAJO || movimiento == VIDAS);
}


/*
* La función recibe una coordenada, devuelve true
* si la posición esta dentro de las dimensiones dadas, sino false.
* Una posición nunca podrá tener un valor negativo y no tendrá un 
* valor más alto que los máximos.
*/
bool esta_dentro_rango(coordenada_t posicion, int max_alto, int max_ancho){
    return ((posicion.col >=0 && posicion.col < max_ancho) && (posicion.fila >=0 && posicion.fila < max_alto));
}


/*
* Procedimiento que se encargará de pedirle al usuario
* que ingrese un movimiento hasta que sea válido.
*/
void pedir_movimiento(char* ref_movimiento){
    printf(" Decime el movimiento: W =ARRIBA | S=ABAJO | D=DERECHA | A=IZQUIERDA \n");
    scanf(" %c", ref_movimiento);

    while(!es_movimiento_valido(*ref_movimiento)){
        printf(" El movimiento que colocaste no es valido decime el movimiento.\n");
        scanf(" %c", ref_movimiento);
    }
}

/*
 *   Función que recibe un vector de elementos, su tope, una cantidad de objetos y una posición
 *   y busca en un vector de elemento_t a un objeto y luego compara si la coordenada es igual a la que se
 *   pasa por parametro, si es igual devuelve true y sino devuelve false. 
 */
bool comparar_coordenadas_vectores(elemento_t objetos[MAX_ELEMENTOS], int tope, int objeto ,coordenada_t posicion){
    coordenada_t coord;
    bool encontrado = false;
    int i =0;

    while(i< tope && !encontrado){
        coord = objetos[i].coordenada;
        if(objetos[i].tipo == objeto && coordenadas_iguales(coord, posicion)){
            encontrado = true;      
        }
        i++;
    }
    return encontrado;
}


/*
* La función recibe un vector de elementos, su respectivo tope y una coordenada,
* devuelve la posición del elemento en el vector, que coincida con la coordenada pasada 'posicion',
* si no se encuentra ningún elemento, se devolverá -1. 
*/
int buscar_elemento(elemento_t elementos[MAX_ELEMENTOS], int tope, coordenada_t posicion){
    int posicion_encontrada =NO_ENCONTRADO;
    int i =0;

    while(i< tope && posicion_encontrada == NO_ENCONTRADO){
        if(coordenadas_iguales(elementos[i].coordenada, posicion)){
            posicion_encontrada = i;
        }
        i++;
    }
    return posicion_encontrada;
}


/*
 *  Función que recibe un vector de herramientas, su tope y un objeto y busca este último
 *  en el vector de herramientas, devolviendo su respectiva coordenada. 
 */
coordenada_t buscar_coord_objeto(elemento_t herramientas[MAX_ELEMENTOS], int tope, char objeto){   
    coordenada_t coord;
    bool encontrado= false;   
    int i =0;

    while(i< tope && !encontrado){
        if(herramientas[i].tipo == objeto){
            coord = herramientas[i].coordenada;
            encontrado = true;
        }
        i++;
    }
    return coord;
}

/*    Función que recibe un vector de cooordenadas y una coordenada y devuelve true si una de las coordenadas
 *    del vector  coincide con la coordenada que se pasa por parámetro.
 */
int buscar_pared(coordenada_t paredes[MAX_PAREDES], int tope, coordenada_t posicion){    
    int posicion_encontrada = NO_ENCONTRADO;
    int i =0;

    while(i< tope && posicion_encontrada == NO_ENCONTRADO){
        if(coordenadas_iguales(paredes[i], posicion)){
            posicion_encontrada = i;
        }
        i++;
    }
    return posicion_encontrada;
}

/*
 *   Procedimiento que recibe un vector de objetos, su tope por referencia y una posición y
 *   se encarga de eliminar el objeto en el vector.
 */
void eliminar_objetos(elemento_t objetos[MAX_ELEMENTOS], int* tope,coordenada_t posicion){
    int valor_posicion= buscar_elemento(objetos,*tope,posicion);
    objetos[valor_posicion] = objetos[(*tope)-1];
    (*tope)--;
}

/*
 *   Procedimiento que recibe un entero correspondiente a la posición de la escalera en el vector de
 *   objetos, el vector de objetos y su tope por referencia y se encarga de eliminar las escaleras una
 *   vez usadas por el personaje.  
 */
void eliminar_escaleras_usadas(int valor_posicion , elemento_t objetos[MAX_ELEMENTOS], int* tope){
    if(valor_posicion != NO_ENCONTRADO){
        objetos[valor_posicion] = objetos[(*tope)-1];
        (*tope)--;
    }
}
/* funcion que recibe la coordenada del personaje , una fila, una columna y si hay una escalera le suma a la coord de personaje y esta la devuelve.
*/
coordenada_t acciones_escaleras(coordenada_t personaje, int fila, int columna){
    personaje.fila += fila;
    personaje.col += columna;
    return personaje;
}

/* Procedimiento que recibe la coordenada del personaje por referencia, una fila, una columna y el juego
 * por referencia y si hay una escalera realiza la acción correspondiente.
*/
void avanzar_escalera(coordenada_t* personaje, int fila, int columna, juego_t* juego){
    coordenada_t aux;

    while(comparar_coordenadas_vectores(juego->niveles[juego->nivel_actual-1].herramientas,juego->niveles[juego->nivel_actual-1].tope_herramientas,ESCALERAS,*personaje)){
        aux= acciones_escaleras(*personaje, fila,columna);
        int pos = buscar_elemento(juego->niveles[juego->nivel_actual-1].herramientas,juego->niveles[juego->nivel_actual-1].tope_herramientas,*personaje);
        if(buscar_pared(juego->niveles[juego->nivel_actual-1].paredes,juego->niveles[juego->nivel_actual-1].tope_paredes, aux) != NO_ENCONTRADO && !comparar_coordenadas_vectores(juego->niveles[juego->nivel_actual-1].herramientas,juego->niveles[juego->nivel_actual-1].tope_herramientas,ESCALERAS,aux) ){
            personaje->fila -= fila;
            personaje->col-= columna; 
        }else if(esta_dentro_rango(aux,MAX_FILAS,MAX_COLUMNAS) && buscar_pared(juego->niveles[juego->nivel_actual-1].paredes,juego->niveles[juego->nivel_actual-1].tope_paredes, aux) == NO_ENCONTRADO){
            (*personaje)= aux;
            eliminar_escaleras_usadas(pos,juego->niveles[juego->nivel_actual-1].herramientas,&(juego->niveles[juego->nivel_actual-1].tope_herramientas));
        }else if(comparar_coordenadas_vectores(juego->niveles[juego->nivel_actual-1].herramientas,juego->niveles[juego->nivel_actual-1].tope_herramientas,ESCALERAS,*personaje) &&buscar_pared(juego->niveles[juego->nivel_actual-1].paredes,juego->niveles[juego->nivel_actual-1].tope_paredes, aux) != NO_ENCONTRADO){
            (*personaje)= aux; 
            eliminar_escaleras_usadas(pos,juego->niveles[juego->nivel_actual-1].herramientas,&(juego->niveles[juego->nivel_actual-1].tope_herramientas)); 
        }         
    }
}
        

/*
 *  Procedimiento que recibe un juego y un personaje por referencia, una fila y una columna y se encarga de
 *  mover el personaje en caso de que la posición esté dentro del rango y no se encuentre una pared en esa
 *  posición.
 */
void realizar_movimiento_personaje(juego_t* juego, coordenada_t* personaje,int fila, int columna){
    personaje->fila += fila;
    personaje->col += columna;
    if(comparar_coordenadas_vectores(juego->niveles[juego->nivel_actual-1].herramientas,juego->niveles[juego->nivel_actual-1].tope_herramientas,ESCALERAS,(*personaje))){
        avanzar_escalera(personaje,fila,columna, juego);
    }

    if(!esta_dentro_rango(*personaje, MAX_FILAS, MAX_COLUMNAS) || (buscar_pared(juego->niveles[juego->nivel_actual-1].paredes,juego->niveles[juego->nivel_actual-1].tope_paredes, *personaje) !=NO_ENCONTRADO && !comparar_coordenadas_vectores(juego->niveles[juego->nivel_actual-1].herramientas,juego->niveles[juego->nivel_actual-1].tope_herramientas,ESCALERAS,(*personaje)))){
        personaje->fila -= fila;
        personaje->col -= columna; 
    }   
}

/*
 *  Procedimiento que recibe un jugo, una sombra por referencia, una fila y una columna y se encarga de mover
 *  la sombra en caso de que la posición esté dentro del rango y no se encuentre una pared en esa posición. 
 */
void realizar_movimiento_sombra(juego_t juego, sombra_t* sombra,int fila, int columna){
    sombra->posicion.fila += fila;
    sombra->posicion.col += columna;

    if(!sombra->esta_viva ||!esta_dentro_rango(sombra->posicion, MAX_FILAS, MAX_COLUMNAS) || buscar_pared(juego.niveles[juego.nivel_actual-1].paredes,juego.niveles[juego.nivel_actual-1].tope_paredes, sombra->posicion) !=NO_ENCONTRADO ||comparar_coordenadas_vectores(juego.niveles[juego.nivel_actual-1].herramientas,juego.niveles[juego.nivel_actual-1].tope_herramientas,ESCALERAS,sombra->posicion)){
        sombra->posicion.fila -= fila;
        sombra->posicion.col -= columna; 
    }   
}

/*
* El procedimiento recibe el personaje y la sombra por referencia y el movimiento,
* y según este último, los mueve acordemente.
* 
* El personaje se mueve de la forma:
* -> W: Si el personaje debe moverse para la arriba. 
* -> A: Si el personaje debe moverse para la izquierda.
* -> S: Si el personaje debe moverse para la abajo.
* -> D: Si el personaje debe moverse para la derecha.
*
*   La sombra se mueve de igual forma para el eje vertical, pero
* para el eje horizontal se moverá de forma inversa:
*
*   -> A: Si el personaje debe moverse para la derecha.
* -> D: Si el personaje debe moverse para la izquierda.
*/
void mover_personaje(personaje_t* ref_personaje, sombra_t* ref_sombra, char movimiento, juego_t* juego){
    

    switch(movimiento){
        case ARRIBA:
            realizar_movimiento_personaje(juego,&ref_personaje->posicion, DISTANCIA_ATRAS, IGUAL_DISTANCIA);
            realizar_movimiento_sombra(*juego,ref_sombra,DISTANCIA_ATRAS, IGUAL_DISTANCIA);
                
        break;
        case ABAJO:
            realizar_movimiento_personaje(juego,&ref_personaje->posicion, DISTANCIA_ADELANTE, IGUAL_DISTANCIA);  
            realizar_movimiento_sombra(*juego,ref_sombra,DISTANCIA_ADELANTE, IGUAL_DISTANCIA);
                      
        break;
        case DERECHA:
            realizar_movimiento_personaje(juego,&ref_personaje->posicion, IGUAL_DISTANCIA, DISTANCIA_ADELANTE);
            if(!ref_personaje->interruptor_apretado){
                realizar_movimiento_sombra(*juego,ref_sombra,IGUAL_DISTANCIA, DISTANCIA_ATRAS);
            }else{
                realizar_movimiento_sombra(*juego,ref_sombra,IGUAL_DISTANCIA, DISTANCIA_ADELANTE);
            }    
                
        break;
        case IZQUIERDA:
            realizar_movimiento_personaje(juego,&ref_personaje->posicion, IGUAL_DISTANCIA, DISTANCIA_ATRAS);
            
            if(!ref_personaje->interruptor_apretado){
                realizar_movimiento_sombra(*juego,ref_sombra,IGUAL_DISTANCIA, DISTANCIA_ADELANTE);
            }else{
                realizar_movimiento_sombra(*juego,ref_sombra,IGUAL_DISTANCIA, DISTANCIA_ATRAS);
            }

        break;       
    }
}

/*  Función que recibe una coordenada_t correspondiente a la sombra
 *  y devuelve la coordenada con la cual la sombra arrancará el juego.
 */
coordenada_t coordenada_inicial_sombra(coordenada_t sombra){
    coordenada_t arranque_sombra;
    arranque_sombra.fila = sombra.fila;
    arranque_sombra.col = MAX_COLUMNAS - sombra.col - 1 ;
    return arranque_sombra;
}


/*
 *  Procedimiento que recibe un vector de elementos, su tope por referencia, un vector de paredes con su tope
 *  y una cantidad y se encarga de inicializar las esacaleras en el vector, coincidiendo su posición con algunas
 *  paredes pero no con otros elementos.
 */
void inicializar_escaleras(elemento_t elemento[MAX_ELEMENTOS],coordenada_t paredes[MAX_PAREDES], int tope_paredes, int cantidad, int *tope_elemento){
    for(int i =0; i< cantidad;i++){
        elemento[(*tope_elemento)].tipo= ESCALERAS;

        do{     
        
            elemento[(*tope_elemento)].coordenada= coordenada_aleatoria (MAX_FILAS, MAX_COLUMNAS);
        }while(buscar_pared(paredes, tope_paredes, elemento[(*tope_elemento)].coordenada) == NO_ENCONTRADO || buscar_elemento(elemento, *tope_elemento, elemento[*tope_elemento].coordenada) != NO_ENCONTRADO);
        (*tope_elemento)++; 
    }
}


/*
 *   Función que recibe un vector de elementos, uno de obstaculos, uno de paredes, sus topes y una coordenada
 *   y se encarga de verificar que las posiciones correspondientes a dichos vectores no coincidan entre sí. 
 */
bool posicion_valida(elemento_t elemento[MAX_ELEMENTOS], int tope, elemento_t obstaculos[MAX_ELEMENTOS], int tope_obstaculos, coordenada_t paredes[MAX_PAREDES],int tope_paredes, coordenada_t coord){
    return (buscar_elemento(elemento, tope -1,coord)!=NO_ENCONTRADO || buscar_elemento(obstaculos, tope_obstaculos,coord) !=NO_ENCONTRADO || buscar_pared(paredes, tope_paredes, coord) != NO_ENCONTRADO);
    
}



/*
 *   Procedimiento que se encarga de inicializar un vector de tipo elemento_t con sus coordenadas y su tipo,
 *   recibiendo dicho vector y su tope por referencia, un vector de obstáculos, uno de paredes y sus topes,
 *   un nombre (que corresponderá al tipo de elemento a inicializar) y la cantidad de veces que se quiera
 *   inicializar el objeto en el vector. 
 */
void inicializar_vector(elemento_t elemento[MAX_ELEMENTOS], int* tope, char nombre , int cantidad, elemento_t obstaculos[MAX_ELEMENTOS] , int tope_obstaculos, coordenada_t paredes[MAX_PAREDES], int tope_paredes){
    for(int i =0; i< cantidad; i++){
        elemento[(*tope)].tipo=nombre;
        
        do{    
            elemento[(*tope)].coordenada= coordenada_aleatoria (MAX_FILAS, MAX_COLUMNAS);       
        }while(posicion_valida(elemento, *tope, obstaculos, tope_obstaculos, paredes, tope_paredes, elemento[(*tope)].coordenada));      
        (*tope)++;
    }
}
      
/*
 *   Procedimiento que recibe un juego por referencia y un nivel por valor y se encarga de inicializar
 *   toda la informacion del nivel uno del juego.
 */
void cargar_nivel_uno(juego_t* juego, int nivel){
    juego->niveles[nivel].numero_nivel = PRIMER_NIVEL;
    juego->niveles[nivel].tope_obstaculos = 0;
    juego->niveles[nivel].tope_herramientas = 0;
    juego->niveles[nivel].tope_paredes =0;
    
    obtener_mapa(juego->niveles[nivel].paredes, &juego->niveles[nivel].tope_paredes);
    
    inicializar_escaleras(juego->niveles[nivel].herramientas,juego->niveles[nivel].paredes, juego->niveles[nivel].tope_paredes, ESCALERAS_NIVEL_UNO, &(juego->niveles[nivel].tope_herramientas));
 
    inicializar_vector(juego->niveles[nivel].herramientas,&(juego->niveles[nivel].tope_herramientas),MONEDAS ,MONEDAS_NIVEL_UNO,juego->niveles[nivel].obstaculos,juego->niveles[nivel].tope_obstaculos, juego->niveles[nivel].paredes, juego->niveles[nivel].tope_paredes);

    inicializar_vector(juego->niveles[nivel].herramientas,&(juego->niveles[nivel].tope_herramientas),PUERTA ,CANT_PUERTA,juego->niveles[nivel].obstaculos,juego->niveles[nivel].tope_obstaculos,juego->niveles[nivel].paredes, juego->niveles[nivel].tope_paredes);
    
    inicializar_vector(juego->niveles[nivel].obstaculos,&(juego->niveles[nivel].tope_obstaculos),VELAS ,VELAS_NIVEL_UNO,juego->niveles[nivel].herramientas,juego->niveles[nivel].tope_herramientas, juego->niveles[nivel].paredes, juego->niveles[nivel].tope_paredes);
    
    inicializar_vector(juego->niveles[nivel].obstaculos,&(juego->niveles[nivel].tope_obstaculos),POZOS ,POZOS_NIVEL_UNO,juego->niveles[nivel].herramientas,juego->niveles[nivel].tope_herramientas, juego->niveles[nivel].paredes, juego->niveles[nivel].tope_paredes);
 
    inicializar_vector(juego->niveles[nivel].obstaculos,&(juego->niveles[nivel].tope_obstaculos),INTERRUPTORES ,INTERRUPTOR_NIVEL_UNO,juego->niveles[nivel].herramientas,juego->niveles[nivel].tope_herramientas,juego->niveles[nivel].paredes, juego->niveles[nivel].tope_paredes);
    
}

/*
 *   Procedimiento que recibe un juego por referencia y un nivel por valor y se encarga de inicializar
 *   toda la informacion del nivel dos del juego.
 */
void cargar_nivel_dos(juego_t* juego, int nivel){
    juego->niveles[nivel].numero_nivel = SEGUNDO_NIVEL;
    juego->niveles[nivel].tope_obstaculos = 0;
    juego->niveles[nivel].tope_herramientas = 0;
    juego->niveles[nivel].tope_paredes =0;

    obtener_mapa(juego->niveles[nivel].paredes, &juego->niveles[nivel].tope_paredes);

    inicializar_escaleras(juego->niveles[nivel].herramientas,juego->niveles[nivel].paredes, juego->niveles[nivel].tope_paredes, ESCALERAS_NIVEL_DOS,&(juego->niveles[nivel].tope_herramientas)); 
 
    inicializar_vector(juego->niveles[nivel].herramientas,&(juego->niveles[nivel].tope_herramientas),MONEDAS ,MONEDAS_NIVEL_DOS, juego->niveles[nivel].obstaculos,juego->niveles[nivel].tope_obstaculos, juego->niveles[nivel].paredes, juego->niveles[nivel].tope_paredes);

    inicializar_vector(juego->niveles[nivel].herramientas,&(juego->niveles[nivel].tope_herramientas),LLAVE ,CANT_LLAVE, juego->niveles[nivel].obstaculos,juego->niveles[nivel].tope_obstaculos, juego->niveles[nivel].paredes, juego->niveles[nivel].tope_paredes);
 
    inicializar_vector(juego->niveles[nivel].herramientas,&(juego->niveles[nivel].tope_herramientas),PUERTA ,CANT_PUERTA, juego->niveles[nivel].obstaculos,juego->niveles[nivel].tope_obstaculos, juego->niveles[nivel].paredes, juego->niveles[nivel].tope_paredes);
    
    inicializar_vector(juego->niveles[nivel].obstaculos,&(juego->niveles[nivel].tope_obstaculos),INTERRUPTORES ,INTERRUPTOR_NIVEL_DOS,juego->niveles[nivel].herramientas,juego->niveles[nivel].tope_herramientas, juego->niveles[nivel].paredes, juego->niveles[nivel].tope_paredes);
    
    inicializar_vector(juego->niveles[nivel].obstaculos,&(juego->niveles[nivel].tope_obstaculos),VELAS ,VELAS_NIVEL_DOS,juego->niveles[nivel].herramientas,juego->niveles[nivel].tope_herramientas, juego->niveles[nivel].paredes, juego->niveles[nivel].tope_paredes);
  
    inicializar_vector(juego->niveles[nivel].obstaculos,&(juego->niveles[nivel].tope_obstaculos),PORTALES ,PORTALES_NIVEL_DOS,juego->niveles[nivel].herramientas,juego->niveles[nivel].tope_herramientas, juego->niveles[nivel].paredes, juego->niveles[nivel].tope_paredes);
   
    inicializar_vector(juego->niveles[nivel].obstaculos,&(juego->niveles[nivel].tope_obstaculos),POZOS ,POZOS_NIVEL_DOS,juego->niveles[nivel].herramientas,juego->niveles[nivel].tope_herramientas, juego->niveles[nivel].paredes, juego->niveles[nivel].tope_paredes);

}


/*
 *   Procedimiento que recibe un juego por referencia y un nivel por valor y se encarga de inicializar
 *   toda la informacion del nivel tres del juego.
 */
void cargar_nivel_tres(juego_t* juego, int nivel){

    juego->niveles[nivel].numero_nivel = TERCER_NIVEL;
    juego->niveles[nivel].tope_obstaculos = 0;
    juego->niveles[nivel].tope_herramientas = 0;
    juego->niveles[nivel].tope_paredes =0;

    obtener_mapa(juego->niveles[nivel].paredes, &juego->niveles[nivel].tope_paredes);
    
    inicializar_escaleras(juego->niveles[nivel].herramientas,juego->niveles[nivel].paredes, juego->niveles[nivel].tope_paredes, ESCALERAS_NIVEL_TRES,&(juego->niveles[nivel].tope_herramientas));
  
    inicializar_vector(juego->niveles[nivel].herramientas,&(juego->niveles[nivel].tope_herramientas),MONEDAS ,MONEDAS_NIVEL_TRES , juego->niveles[nivel].obstaculos,juego->niveles[nivel].tope_obstaculos, juego->niveles[nivel].paredes, juego->niveles[nivel].tope_paredes);
  
    inicializar_vector(juego->niveles[nivel].herramientas,&(juego->niveles[nivel].tope_herramientas),LLAVE ,CANT_LLAVE, juego->niveles[nivel].obstaculos,juego->niveles[nivel].tope_obstaculos, juego->niveles[nivel].paredes, juego->niveles[nivel].tope_paredes);
   
    inicializar_vector(juego->niveles[nivel].herramientas,&(juego->niveles[nivel].tope_herramientas),PUERTA ,CANT_PUERTA, juego->niveles[nivel].obstaculos,juego->niveles[nivel].tope_obstaculos, juego->niveles[nivel].paredes, juego->niveles[nivel].tope_paredes);

    inicializar_vector(juego->niveles[nivel].obstaculos,&(juego->niveles[nivel].tope_obstaculos),VELAS ,VELAS_NIVEL_TRES,juego->niveles[nivel].herramientas,juego->niveles[nivel].tope_herramientas, juego->niveles[nivel].paredes, juego->niveles[nivel].tope_paredes);
    
    inicializar_vector(juego->niveles[nivel].obstaculos,&(juego->niveles[nivel].tope_obstaculos),INTERRUPTORES ,INTERRUPTOR_NIVEL_TRES, juego->niveles[nivel].herramientas,juego->niveles[nivel].tope_herramientas, juego->niveles[nivel].paredes, juego->niveles[nivel].tope_paredes);
  
    inicializar_vector(juego->niveles[nivel].obstaculos,&(juego->niveles[nivel].tope_obstaculos),POZOS ,POZOS_NIVEL_TRES, juego->niveles[nivel].herramientas,juego->niveles[nivel].tope_herramientas, juego->niveles[nivel].paredes, juego->niveles[nivel].tope_paredes);

    inicializar_vector(juego->niveles[nivel].obstaculos,&(juego->niveles[nivel].tope_obstaculos),PORTALES ,PORTALES_NIVEL_TRES,juego->niveles[nivel].herramientas,juego->niveles[nivel].tope_herramientas, juego->niveles[nivel].paredes, juego->niveles[nivel].tope_paredes);
  
         
}


void inicializar_juego(juego_t* juego){

    juego->nivel_actual = PRIMER_NIVEL;
    cargar_mapas();

    coordenada_t arranque_personaje = coordenada_aleatoria (MAX_FILAS, MAX_COLUMNAS);
    inicializar_personaje(&(juego->personaje), arranque_personaje);

    coordenada_t arranque_sombra = coordenada_inicial_sombra(arranque_personaje);

    inicializar_sombra(&(juego->sombra), arranque_sombra);
    
    cargar_nivel_uno(juego, POS_NIVEL_1);

    cargar_nivel_dos(juego, POS_NIVEL_2);

    cargar_nivel_tres(juego, POS_NIVEL_3);   
}

/*
 *  Función que recibe una coordenada y la coordenada de la puerta
 *  y devuelve la distancia que hay entre ellas. 
 */
int distancia_manhatan(coordenada_t coordenada, coordenada_t puerta){
    return (abs(coordenada.fila - puerta.fila) + abs(coordenada.col -puerta.col));
}

int estado_nivel(juego_t juego){
   

    coordenada_t coord_puerta_1 = buscar_coord_objeto(juego.niveles[POS_NIVEL_1].herramientas, juego.niveles[POS_NIVEL_1].tope_herramientas, PUERTA);
    coordenada_t coord_puerta_2 = buscar_coord_objeto(juego.niveles[POS_NIVEL_2].herramientas, juego.niveles[POS_NIVEL_2].tope_herramientas, PUERTA);
    coordenada_t coord_puerta_3 = buscar_coord_objeto(juego.niveles[POS_NIVEL_3].herramientas, juego.niveles[POS_NIVEL_3].tope_herramientas, PUERTA);
    int estado_del_nivel= JUGANDO;
    
    if (juego.nivel_actual == PRIMER_NIVEL && distancia_manhatan(juego.personaje.posicion, coord_puerta_1) <= 1 && distancia_manhatan(juego.sombra.posicion, coord_puerta_1) <= 1 && juego.sombra.esta_viva){
        estado_del_nivel = JUEGO_GANADO;
    
    }else if(juego.nivel_actual==SEGUNDO_NIVEL && distancia_manhatan(juego.personaje.posicion, coord_puerta_2) <= 1 && distancia_manhatan(juego.sombra.posicion, coord_puerta_2) <= 1  && juego.personaje.tiene_llave && juego.sombra.esta_viva){
        estado_del_nivel = JUEGO_GANADO;
    }else if(juego.nivel_actual==TERCER_NIVEL && distancia_manhatan(juego.personaje.posicion, coord_puerta_3) <= 1 && distancia_manhatan(juego.sombra.posicion, coord_puerta_3) <= 1  && juego.personaje.tiene_llave && juego.sombra.esta_viva){
        estado_del_nivel = JUEGO_GANADO;
    }
    return estado_del_nivel;
}


int estado_juego(juego_t juego){
    int jueguito = JUGANDO; 
    if(juego.personaje.vida == SIN_VIDA){
        jueguito = PERDIDO;
    }else if(juego.nivel_actual == TERCER_NIVEL && estado_nivel(juego)== JUEGO_GANADO){
        jueguito =  JUEGO_GANADO;
    }
    return jueguito;
    
}


/*
 *  Procedimiento que recibe el terreno del juego y elimina la basura que pueda haber en la matriz.
 */
void limpiar_terreno(char terreno[MAX_FILAS][MAX_COLUMNAS]){

    for (int i = 0; i < MAX_FILAS; i++){
        for (int j = 0; j < MAX_COLUMNAS; j++){
            terreno[i][j] = VACIO;
        }
    }
}

/*
 *  Procedimiento que recibe un terrreno, una coordenada y el nombre de un objeto por referencia
 *  y se encarga de llenar el terreno con dicho nombre.
 */
void llenar_terreno(char terreno[MAX_FILAS][MAX_COLUMNAS],coordenada_t coordenada, char nombre){
    terreno[coordenada.fila][coordenada.col] = nombre;
}


/*
 *  Procedimiento que recibe un terreno, un vector de objetos, su tope, un nombre por referencia y un objeto
 *  y se encarga de llenar el terreno con los vectores de  obstaculos y  herramientas.  
 */
void llenar_terreno_con_vectores(char terreno[MAX_FILAS][MAX_COLUMNAS], elemento_t objetos[MAX_ELEMENTOS], int tope){
 
    for(int i =0; i< tope;i++){

        llenar_terreno(terreno,objetos[i].coordenada, objetos[i].tipo);
    
    } 


}

/*
 *  Procedimiento que recibe un terreno, un vector de paredes, su tope y un nombre por referencia
 *  y se encarga de llenar el terreno con las paredes.
 */
void llenar_terreno_con_paredes(char terreno[MAX_FILAS][MAX_COLUMNAS], coordenada_t paredes[MAX_PAREDES], int tope){
      
    for(int i =0; i< tope;i++){
        
        llenar_terreno(terreno,paredes[i], PAREDES);
        
    }   
}
/*
 *  Procedimiento que recibe una matriz y se encarga de imprimirla por pantalla.
 */
void imprimir_matriz(char terreno[MAX_FILAS][MAX_COLUMNAS]){
    for(int i = 0 ; i < MAX_FILAS; i++){
        for(int j = 0; j < MAX_COLUMNAS; j++){
            if(terreno[i][j] == MAC){
                printf("%s", IMAGEN_MAC);
            }
            else if(terreno[i][j] == BLOO){
                printf("%s", IMAGEN_BLOO);
            }
            else if(terreno[i][j] == VELAS){
                printf("%s ", IMAGEN_VELAS);
            }
            else if(terreno[i][j] == POZOS){
                printf("%s", IMAGEN_POZOS);
            }
            else if(terreno[i][j] == MONEDAS){
                printf("%s", IMAGEN_MONEDAS);
            }
            else if(terreno[i][j] == PORTALES){
                printf("%s", IMAGEN_PORTAL);
            }
            else if(terreno[i][j] == INTERRUPTORES){
                printf("%s ", IMAGEN_INTERRUPTOR);
            }
            else if(terreno[i][j] == PUERTA){
                printf("%s", IMAGEN_PUERTA);
            }
            else if(terreno[i][j] == PAREDES){
                printf("%s", IMAGEN_PARED);
            }
            else if(terreno[i][j] == LLAVE){
                printf("%s", IMAGEN_LLAVES);
            }
            else if(terreno[i][j] == ESCALERAS){
                printf("%s ", IMAGEN_ESCALERAS);
            }else{
                printf("%s", IMAGEN_VACIO);
            }
        }
        printf("\n");
    }
    printf("\n");
}


/*
 * Procedimiento que recibe la cantidad de vidas del personaje y las imprme por pantalla. 
 */
void imprimir_vidas (int vidas){
    printf(" Vidas:");
    for (int i =0; i< vidas; i++){
        printf(" %s", IMAGEN_VIDAS);
    }
    printf("\n");
}

/*
 * Procedimiento se encarga de imprimir por pantalla si el interruptor esta apretado o no 
 */
void imprimir_valor_interruptor(bool interruptor_apretado){
    if(interruptor_apretado){
        printf(" el interruptor esta apretado \n");
    }else{
        printf(" el interruptor no esta apretado\n");
    }
}


/*
 * Procedimiento se encarga de imprimir por pantalla si el personaje tiene la llave o no 
 */
void imprimir_valor_llave(bool tiene_llave){
    if(tiene_llave){
        printf(" tienes la llave\n");
    }else{
        printf(" no tienes la llave aun \n");
    }
}


void imprimir_terreno(juego_t juego){
    char terreno[MAX_FILAS][MAX_COLUMNAS];
    limpiar_terreno(terreno);
    llenar_terreno_con_paredes(terreno,juego.niveles[juego.nivel_actual-1].paredes , juego.niveles[juego.nivel_actual-1].tope_paredes);
    llenar_terreno_con_vectores(terreno,juego.niveles[juego.nivel_actual-1].herramientas, juego.niveles[juego.nivel_actual-1].tope_herramientas);
    llenar_terreno_con_vectores(terreno,juego.niveles[juego.nivel_actual-1].obstaculos, juego.niveles[juego.nivel_actual-1].tope_obstaculos );
    llenar_terreno(terreno, juego.sombra.posicion, BLOO);
    llenar_terreno(terreno, juego.personaje.posicion, MAC);
    
    system("clear");
    imprimir_matriz(terreno);
    printf(" Puntos: %i\n", juego.personaje.puntos);
    printf(" Nivel %i\n", juego.nivel_actual);
    imprimir_valor_interruptor(juego.personaje.interruptor_apretado);
    imprimir_valor_llave(juego.personaje.tiene_llave);
    imprimir_vidas (juego.personaje.vida);
}


/*
 *   Procedimiento que recibe un vector de obstáculos, su tope y un personaje por referencia y se encarga de
 *   verificar si la posicion del personaje es la misma que la de un interruptor para apagar el interruptor
 *   si estaba prendido o prenderlo si estaba apagado. 
 */
void cambios_interruptor(elemento_t obstaculos[MAX_ELEMENTOS], int tope, personaje_t* personaje){
    if(comparar_coordenadas_vectores(obstaculos, tope, INTERRUPTORES,personaje->posicion)){
        if(personaje->interruptor_apretado){
            personaje->interruptor_apretado = false;
        }else{
            personaje->interruptor_apretado = true;
        }
    }
}

/*
 *   Procedimiento que recibe un vector de herrameintas, su tope por referencia y un personaje por
 *   referencia y se encarga de verificar si las coordenadas del personaje y la llave son iguales.
 *   De ser así, el personaje se queda con la llave y la misma desaparece del terreno. 
 */
void cambios_llave(elemento_t herramientas[MAX_ELEMENTOS], int *tope, personaje_t* personaje){
    if(comparar_coordenadas_vectores(herramientas, *tope, LLAVE,personaje->posicion)){
        eliminar_objetos(herramientas, tope,personaje->posicion);
        personaje->tiene_llave = true; 
    }

}

/*
 *  Procedimiento que recibe un vector de obstáculos, su tope por referencia, un personaje por referencia
 *  y la coordenada de la sombra y se encarga de verificar si las coordenadas del personaje o la sombra
 *  coinciden con las de las monedas. Si son iguales, el personaje adquiere una cierta cantidad de puntos
 *  aleatoriamente entre cierto rango.
 */
void cambio_puntos(elemento_t obstaculos[MAX_ELEMENTOS], int *tope, personaje_t* personaje, coordenada_t sombra){
    if(comparar_coordenadas_vectores(obstaculos, *tope, MONEDAS,personaje->posicion)){      
        personaje->puntos += rand() %MAX_PUNTOS +MIN_PUNTOS;
        eliminar_objetos(obstaculos, tope,personaje->posicion);
    }else if(comparar_coordenadas_vectores(obstaculos, *tope, MONEDAS, sombra)){
        personaje->puntos += rand() %MAX_PUNTOS +MIN_PUNTOS;
        eliminar_objetos(obstaculos, tope,sombra);
    }
}
/*   Procedimiento que recibe un personaje por referencia y un movimiento.
 *   Si el movimiento corresponde a la compra de una vida, el personaje tiene menos de 3 vidas y
 *   posee por lo menos 200 puntos, se le suma una vida y se le restan 200 puntos.
 */
void comprar_vida(personaje_t* personaje, char movimiento){
    if(personaje->vida < VIDA && movimiento == VIDAS &&personaje->puntos >= 200){
        personaje->vida++;
        personaje->puntos -= PUNTOS_VIDA;

    }
}

/*
 *   Procedimiento que recibe un juego por referencia y un nivel. Si las coordenadas del personaje
 *   coinciden cn la de algún pozo, se reinician las posiciones de personaje y de la sombra
 *   y personaje pierde una vida.
 */
void pierde_vida(juego_t* juego, int nivel){
    if(comparar_coordenadas_vectores(juego->niveles[nivel].obstaculos, juego->niveles[nivel].tope_obstaculos, POZOS,juego->personaje.posicion)){
        juego->personaje.vida --;

        do{

            juego->personaje.posicion  = coordenada_aleatoria (MAX_FILAS, MAX_COLUMNAS);
            juego->sombra.posicion = coordenada_inicial_sombra(juego->personaje.posicion);
        }while(posicion_valida(juego->niveles[nivel].obstaculos, juego->niveles[nivel].tope_obstaculos, juego->niveles[nivel].herramientas , juego->niveles[nivel].tope_herramientas,  juego->niveles[nivel].paredes, juego->niveles[nivel].tope_paredes, juego->personaje.posicion) && posicion_valida(juego->niveles[nivel].obstaculos, juego->niveles[nivel].tope_obstaculos, juego->niveles[nivel].herramientas , juego->niveles[nivel].tope_herramientas,  juego->niveles[nivel].paredes, juego->niveles[nivel].tope_paredes, juego->sombra.posicion));
    }

}

/*
 * Procedimiento que recibe un juego por referencia, un nombre y un nivel y se encarga de verificar las
 * coordenadas de sombra y portales, y en caso de ser iguales intercambia posiciones con personaje.
 */
void cambio_posiciones( juego_t* juego ,char nombre, int nivel){
    if(comparar_coordenadas_vectores(juego->niveles[nivel].obstaculos, juego->niveles[nivel].tope_obstaculos, nombre,juego->sombra.posicion)){
        coordenada_t aux = juego->sombra.posicion;
        juego->sombra.posicion = juego->personaje.posicion;
        juego->personaje.posicion = aux;    
    }


}

/*
 *  Procedimiento que recibe un vector de obstáculos, su tope, una cantidad de objetos y la coordenada de
 *  la sombra y se encarga de verificar si sombra esta dentro del rango de 3*3 de la vela. Si esta en ese
 *  rango devuelve true y sino false
 */
bool distancia_vela(elemento_t obstaculos[MAX_ELEMENTOS], int tope, int objeto, coordenada_t sombra){
    coordenada_t coord;
    bool encontrado = false;
    int i =0;

    while(i< tope && !encontrado){
        coord = obstaculos[i].coordenada;
        if(obstaculos[i].tipo == objeto){
            if((distancia_manhatan(sombra,coord)==2 && sombra.fila != coord.fila && sombra.col != coord.col)||(distancia_manhatan(sombra,coord) <=1)){
                encontrado = true;
            }      
        }
        i++;
    }
    return encontrado;
}

/*
 *  Procedimiento que recibe un vector de obstáculos, su tope por referencia, y un personaje y una sombra
 *  por referencia y se encarga de realizar las acciones que se piden cuando el personaje o la sombra estan
 *  cerca de la vela. 
 */
void acciones_vela (elemento_t obstaculos[MAX_ELEMENTOS], int* tope, personaje_t* personaje, sombra_t* sombra){
    bool encendida = false;
    if(distancia_vela(obstaculos,*tope,VELAS,sombra->posicion)){
        encendida = true;
        sombra->esta_viva = false;
    }
    if(comparar_coordenadas_vectores(obstaculos, *tope, VELAS,personaje->posicion)){
        eliminar_objetos(obstaculos,tope, personaje->posicion);
        encendida = false;
    }
    if(coordenadas_iguales(personaje->posicion, sombra->posicion) && !encendida){
        sombra->esta_viva = true;
        personaje->puntos -= REVIVIR;
    }else if(coordenadas_iguales(personaje->posicion, sombra->posicion) && encendida){
        personaje->puntos -= REVIVIR;
    }
}

/*
 *  Procedimiento que recibe un juego por referencia y se encarga de realizar el cambio de nivel.
 */
void cambio_nivel(juego_t* juego){
    if (estado_nivel(*juego) == JUEGO_GANADO && juego->nivel_actual< TERCER_NIVEL){
        juego->nivel_actual++;
        juego->personaje.tiene_llave = false;
        juego->personaje.interruptor_apretado = false;
    } 
}


/*
 *   Procedimiento que recibe un juego por referencia, un nivel y un movimiento y se encarga de realizar
 *   la accion necesaria en caso de chocar con algún elemento del nivel.
 */
void jugada_nivel(juego_t* juego, int nivel , char movimiento){

    cambios_interruptor(juego->niveles[nivel].obstaculos, juego->niveles[nivel].tope_obstaculos, &(juego->personaje));

    cambio_puntos(juego->niveles[nivel].herramientas, &(juego->niveles[nivel].tope_herramientas), &(juego->personaje), juego->sombra.posicion);
  
    comprar_vida(&juego->personaje, movimiento);

    pierde_vida(juego, nivel);

    cambio_posiciones(juego ,PORTALES, nivel);

    acciones_vela (juego->niveles[nivel].obstaculos, &(juego->niveles[nivel].tope_obstaculos),&(juego->personaje), &(juego->sombra)); 

    cambios_llave(juego->niveles[nivel].herramientas, &(juego->niveles[nivel].tope_herramientas), &(juego->personaje));  

    cambio_nivel(juego);
}




void realizar_jugada(juego_t* juego){   
    char movimiento;
    pedir_movimiento(&movimiento);
    mover_personaje(&(juego->personaje), &(juego->sombra), movimiento, juego);
    jugada_nivel(juego,juego->nivel_actual-1, movimiento);
}
