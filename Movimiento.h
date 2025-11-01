#ifndef PROYECTO_AGENTE_INTELIGENTE_MOVIMIENTO_H
#define PROYECTO_AGENTE_INTELIGENTE_MOVIMIENTO_H

#include <string>
#include <vector>

/*
===============================================================================
                                MOVIMIENTO CRC
===============================================================================
Nombre de la clase:Movimiento
Responsabilidades:
    - Movimiento del soldado (arriba, abajo, izquierda, derecha)
Colaboradores:
    - Avatar
    - Tablero
===============================================================================
*/
class Movimiento {
private:
    int& PosicionX ;
    int& PosicionY ;
    std::vector<std::string> UltimosMovimientos{}; // vector que permite registrar los últimos movimientos realizados por el Avatar

public:
    Movimiento( int& posicionX ,  int& posicionY); // Paso de mensaje por referencia
    // Metodos de deteccion de vacios para tomar una decision
    bool DetectarVacioDerecha(int (&matriz)[10][10]);
    bool DetectarVacioIzquierda(int (&matriz)[10][10]);
    bool DetectarVacioArriba(int (&matriz)[10][10]);
    bool DetectarVacioAbajo(int (&matriz)[10][10]);
    //Metodo de movimiento
    std::string Moverse();
};
#endif //PASO_MENSAJES_MOVIMIENTO_H