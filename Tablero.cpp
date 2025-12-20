#include "Tablero.h"
#include <cstdlib>
#include <iostream>
/*
========================================================================================
                        IMPLEMENTACIÓN DE LA CLASE TABLERO
========================================================================================
La clase Tablero representa un tablero de 10x10 con valores 0 y 1, también almacena la
posición actual en coordenadas TableroX y TableroY, también define una posición valída
(donde la celda es diferente de cero) y también provee acceso a las coordenadas actuales
mediante getters

Se demuestra:
 - Uso de constructores mediante atributos y estructuras bidimensionales
 - Uso de metodos para la generación de coordenadas aleatorias
 - Impresión de matrices en consola con bucles anidados
========================================================================================
*/
Tablero::Tablero()
{

    this->TableroX = 0;
    this->TableroY = 0;

    // Se define los vacios del laberinto:

    matriz[0][0] = 0;
    matriz[0][1] = 0;
    matriz[0][2] = 1;
    matriz[0][3] = 0;
    matriz[0][4] = 1;
    matriz[0][5] = 1;
    matriz[0][6] = 0;
    matriz[0][7] = 0;
    matriz[0][8] = 0;
    matriz[0][9] = 1;

    matriz[1][0] = 1;
    matriz[1][1] = 1;
    matriz[1][2] = 1;
    matriz[1][3] = 0;
    matriz[1][4] = 1;
    matriz[1][5] = 0;
    matriz[1][6] = 0;
    matriz[1][7] = 1;
    matriz[1][8] = 0;
    matriz[1][9] = 1;

    matriz[2][0] = 0;
    matriz[2][1] = 0;
    matriz[2][2] = 1;
    matriz[2][3] = 0;
    matriz[2][4] = 1;
    matriz[2][5] = 1;
    matriz[2][6] = 1;
    matriz[2][7] = 1;
    matriz[2][8] = 1;
    matriz[2][9] = 1;

    matriz[3][0] = 0;
    matriz[3][1] = 1;
    matriz[3][2] = 1;
    matriz[3][3] = 0;
    matriz[3][4] = 0;
    matriz[3][5] = 0;
    matriz[3][6] = 0;
    matriz[3][7] = 0;
    matriz[3][8] = 0;
    matriz[3][9] = 1;

    matriz[4][0] = 0;
    matriz[4][1] = 1;
    matriz[4][2] = 0;
    matriz[4][3] = 1;
    matriz[4][4] = 1;
    matriz[4][5] = 1;
    matriz[4][6] = 0;
    matriz[4][7] = 1;
    matriz[4][8] = 1;
    matriz[4][9] = 1;

    matriz[5][0] = 1;
    matriz[5][1] = 1;
    matriz[5][2] = 0;
    matriz[5][3] = 1;
    matriz[5][4] = 0;
    matriz[5][5] = 1;
    matriz[5][6] = 0;
    matriz[5][7] = 1;
    matriz[5][8] = 0;
    matriz[5][9] = 1;

    matriz[6][0] = 1;
    matriz[6][1] = 0;
    matriz[6][2] = 0;
    matriz[6][3] = 1;
    matriz[6][4] = 0;
    matriz[6][5] = 1;
    matriz[6][6] = 0;
    matriz[6][7] = 1;
    matriz[6][8] = 1;
    matriz[6][9] = 0;

    matriz[7][0] = 1;
    matriz[7][1] = 1;
    matriz[7][2] = 1;
    matriz[7][3] = 0;
    matriz[7][4] = 1;
    matriz[7][5] = 1;
    matriz[7][6] = 0;
    matriz[7][7] = 1;
    matriz[7][8] = 0;
    matriz[7][9] = 0;

    matriz[8][0] = 0;
    matriz[8][1] = 0;
    matriz[8][2] = 1;
    matriz[8][3] = 0;
    matriz[8][4] = 0;
    matriz[8][5] = 1;
    matriz[8][6] = 1;
    matriz[8][7] = 1;
    matriz[8][8] = 1;
    matriz[8][9] = 1;

    matriz[9][0] = 0;
    matriz[9][1] = 1;
    matriz[9][2] = 1;
    matriz[9][3] = 1;
    matriz[9][4] = 1;
    matriz[9][5] = 1;
    matriz[9][6] = 0;
    matriz[9][7] = 1;
    matriz[9][8] = 0;
    matriz[9][9] = 1;
    srand(time(0));
}

void Tablero::Definirposicion()
{ // Se define la  inicial del jugador

    int aux = 0;
    while (aux == 0 || (TableroX == 9 && TableroY == 9))
    {
        DefinirposicionX();
        DefinirposicionY();
        aux = matriz[TableroX][TableroY];
    }
}

void Tablero::DefinirposicionX()
{
    // Inicializa la semilla (solo se hace una vez)
    TableroX = rand() % 10; // Genera número entre 0 y 9
}

void Tablero::DefinirposicionY()
{
    TableroY = rand() % 10;
}

int Tablero::GetTableroX()
{
    return TableroX;
}
int Tablero::GetTableroY()
{
    return TableroY;
}

int Tablero::matriz[10][10] = { // se crea una matriz estatica que pertenecera a la clase
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

int (&Tablero::GetMatrizStatic())[10][10]
{
    return matriz;
}
