#include <iostream>
#include <string>
#include "Tablero.h"
#include "Avatar.h"
#include "Movimiento.h"

/*
Proyecto: Paso-de-Mensajes-Main

Curso: Fundamentos de Programación Orientada a Objetos (FPOO)

Autores:
Felipe velasco - 2517245
Jerónimo imbachi - 2517760
Leonardo rosero - 2518313-3743
Alejandro velez - 2521169-3743
Julio Cesar Urbano Noguera- 2517931

Resumen:
Este programa es un algoritmo cuyo protagonista es un objeto de la clase avatar y que recorre las coordenadas de una matriz que representa un laberinto.
Los Vacios y Espacios sin salida se representan como 0 y los Espacios Libres como 1
Meta: Llegar a la salida ubicada en la celda [9,9]
*/

int main() {
    Tablero Laberinto;
    Laberinto.Definirposicion();
    int PosicionX=Laberinto.GetTableroX();
    int PosicionY=Laberinto.GetTableroY();
    Avatar AgenteI("Smart" , PosicionX, PosicionY);
    AgenteI.Posicion();
    Movimiento MovimientoAgente(AgenteI.GetPosicionX(),AgenteI.GetPosicionY());
    MovimientoAgente.Moverse();
    return 0;
}