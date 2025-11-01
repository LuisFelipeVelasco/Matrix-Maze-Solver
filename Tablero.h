#ifndef PROYECTO_AGENTE_INTELIGENTE_TABLERO_H
#define PROYECTO_AGENTE_INTELIGENTE_TABLERO_H
/*
===============================================================================
                                TARJETA CRC
===============================================================================
Nombre de la clase:Tablero
Responsabilidades:
    - Crear una matriz 10x10 con valores en las cerdas de 0 y 1
    - Definir la posición aleatoria del soldado
Colaboradores:
    - Avatar
===============================================================================
*/

class Tablero {
private:
    int TableroX{};
    int TableroY{};
    static int matriz[10][10];
public:
    Tablero();
    void Definirposicion();
    void DefinirposicionX(); //cuando empieza el juego
    void DefinirposicionY(); //cuando empieza el juego
    int GetTableroX();
    int GetTableroY();
    static int (&GetMatrizStatic())[10][10] ;//se declara un getter de la matriz para poder leerla en movimiento.cpp



};

#endif //PASO_MENSAJES_TABLERO_H