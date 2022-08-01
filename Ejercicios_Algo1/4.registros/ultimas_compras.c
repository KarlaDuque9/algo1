/*	 ENUNCIADO

Después de haber elegido el lugar y la fecha donde vacacionar, Tom, Jerry y Spike están haciendo las últimas compras necesarias para viajar. 
Su idea es gastar lo menos posible, para que les quede mucha plata para llevar y gastarla en el lugar.

    Implementar un procedimiento que calcule el precio total que tienen que gastar, y lo escriba en el campo precio_total del registro de lista de compras.

Lista de precios disponible:

    Chocolate: 50.
    Caramelos: 10.
    Gaseosa: 70.
    Pelota de playa: 120.

Ejemplo:

Si nos vienen las siguientes cantidades en nuestra lista:

    Chocolates: 5.
    Caramelos: 0.
    Gaseosa: 1.
    Pelota de playa: 1.

Al final de nuestra función el campo precio_total debería ser 440.

*/

//	RESOLUCON

#include <stdio.h>
#include "solucion.h"

const int precio_chocolate = 50;
const int precio_caramelo = 10;
const int precio_gasosa = 70;
const int precio_pelota_de_playa = 120;

typedef struct lista_compras{
	int cantidad_chocolates;
	int cantidad_caramelos;
	int cantidad_gaseosas;
	int cantidad_pelotas_playa;
	int precio_total;
}lista_compras_t;

void calcular_precio_total(lista_compras_t* lista_compras){	                            

lista_compras->precio_total = lista_compras->cantidad_chocolates *precio_chocolate + lista_compras->cantidad_caramelos *precio_caramelo + lista_compras->cantidad_gaseosas *precio_gasosa + lista_compras->cantidad_pelotas_playa* precio_pelota_de_playa;
}