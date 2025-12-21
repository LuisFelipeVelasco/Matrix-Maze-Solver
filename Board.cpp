#include "Board.h"
#include <cstdlib>
#include <iostream>
/*
========================================================================================
                        IMPLEMENTATION OF THE BOARD CLASS
========================================================================================
The Board class represents a 10x10 board with values 0 and 1. It also stores
the current position in BoardX and BoardY coordinates. It also defines a valid position
(where the cell is different from zero) and also provides access to current coordinates
via getters

Demonstrates:
 - Use of constructors with attributes and bidimensional structures
 - Use of methods for generating random coordinates
 - Printing matrices in console with nested loops
========================================================================================
*/
Board::Board()
{

    this->BoardX = 0;
    this->BoardY = 0;

    // Define the empty spaces of the maze:

    matrix[0][0] = 0;
    matrix[0][1] = 0;
    matrix[0][2] = 1;
    matrix[0][3] = 0;
    matrix[0][4] = 1;
    matrix[0][5] = 1;
    matrix[0][6] = 0;
    matrix[0][7] = 0;
    matrix[0][8] = 0;
    matrix[0][9] = 1;

    matrix[1][0] = 1;
    matrix[1][1] = 1;
    matrix[1][2] = 1;
    matrix[1][3] = 0;
    matrix[1][4] = 1;
    matrix[1][5] = 0;
    matrix[1][6] = 0;
    matrix[1][7] = 1;
    matrix[1][8] = 0;
    matrix[1][9] = 1;

    matrix[2][0] = 0;
    matrix[2][1] = 0;
    matrix[2][2] = 1;
    matrix[2][3] = 0;
    matrix[2][4] = 1;
    matrix[2][5] = 1;
    matrix[2][6] = 1;
    matrix[2][7] = 1;
    matrix[2][8] = 1;
    matrix[2][9] = 1;

    matrix[3][0] = 0;
    matrix[3][1] = 1;
    matrix[3][2] = 1;
    matrix[3][3] = 0;
    matrix[3][4] = 0;
    matrix[3][5] = 0;
    matrix[3][6] = 0;
    matrix[3][7] = 0;
    matrix[3][8] = 0;
    matrix[3][9] = 1;

    matrix[4][0] = 0;
    matrix[4][1] = 1;
    matrix[4][2] = 0;
    matrix[4][3] = 1;
    matrix[4][4] = 1;
    matrix[4][5] = 1;
    matrix[4][6] = 0;
    matrix[4][7] = 1;
    matrix[4][8] = 1;
    matrix[4][9] = 1;

    matrix[5][0] = 1;
    matrix[5][1] = 1;
    matrix[5][2] = 0;
    matrix[5][3] = 1;
    matrix[5][4] = 0;
    matrix[5][5] = 1;
    matrix[5][6] = 0;
    matrix[5][7] = 1;
    matrix[5][8] = 0;
    matrix[5][9] = 1;

    matrix[6][0] = 1;
    matrix[6][1] = 0;
    matrix[6][2] = 0;
    matrix[6][3] = 1;
    matrix[6][4] = 0;
    matrix[6][5] = 1;
    matrix[6][6] = 0;
    matrix[6][7] = 1;
    matrix[6][8] = 1;
    matrix[6][9] = 0;

    matrix[7][0] = 1;
    matrix[7][1] = 1;
    matrix[7][2] = 1;
    matrix[7][3] = 0;
    matrix[7][4] = 1;
    matrix[7][5] = 1;
    matrix[7][6] = 0;
    matrix[7][7] = 1;
    matrix[7][8] = 0;
    matrix[7][9] = 0;

    matrix[8][0] = 0;
    matrix[8][1] = 0;
    matrix[8][2] = 1;
    matrix[8][3] = 0;
    matrix[8][4] = 0;
    matrix[8][5] = 1;
    matrix[8][6] = 1;
    matrix[8][7] = 1;
    matrix[8][8] = 1;
    matrix[8][9] = 1;

    matrix[9][0] = 0;
    matrix[9][1] = 1;
    matrix[9][2] = 1;
    matrix[9][3] = 1;
    matrix[9][4] = 1;
    matrix[9][5] = 1;
    matrix[9][6] = 0;
    matrix[9][7] = 1;
    matrix[9][8] = 0;
    matrix[9][9] = 1;
    srand(time(0));
}

void Board::DefinePosition()
{ // Define the initial position of the player

    int aux = 0;
    while (aux == 0 || (BoardX == 9 && BoardY == 9))
    {
        DefinePositionX();
        DefinePositionY();
        aux = matrix[BoardX][BoardY];
    }
}

void Board::DefinePositionX()
{
    // Initialize the seed (only done once)
    BoardX = rand() % 10; // Generate number between 0 and 9
}

void Board::DefinePositionY()
{
    BoardY = rand() % 10;
}

int Board::GetBoardX()
{
    return BoardX;
}
int Board::GetBoardY()
{
    return BoardY;
}

int Board::matrix[10][10] = { // static matrix belonging to the class
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

int (&Board::GetMatrixStatic())[10][10]
{
    return matrix;
}
