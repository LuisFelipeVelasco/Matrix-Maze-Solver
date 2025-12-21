#ifndef MATRIX_MAZE_SOLVER_BOARD_H
#define MATRIX_MAZE_SOLVER_BOARD_H
/*
===============================================================================
                                CRC CARD
===============================================================================
Class Name: Board
Responsibilities:
    - Create a 10x10 matrix with values 0 and 1 in cells
    - Define the random position of the agent
Collaborators:
    - Avatar
===============================================================================
*/

class Board {
private:
    int BoardX{};
    int BoardY{};
    static int matrix[10][10];
public:
    Board();
    void DefinePosition();
    void DefinePositionX(); // when the game starts
    void DefinePositionY(); // when the game starts
    int GetBoardX();
    int GetBoardY();
    static int (&GetMatrixStatic())[10][10]; // getter for matrix to read it in movement.cpp


};

#endif //MATRIX_MAZE_SOLVER_BOARD_H
