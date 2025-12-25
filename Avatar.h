#ifndef MATRIX_MAZE_SOLVER_AVATAR_H
#define MATRIX_MAZE_SOLVER_AVATAR_H

#include <string>
#include <vector>

/*
===============================================================================
                                MOVEMENT CRC
===============================================================================
Class Name: Avatar
Responsibilities:
    - Movement of the agent (up, down, left, right)
Collaborators:
    - Avatar
    - Board
===============================================================================
*/
class Avatar {
private:
    std::string Name{};
    int& PositionX;
    int& PositionY;
    std::vector<std::string> LastMovements{}; // vector that allows recording the last movements performed by the Avatar

public:
    Avatar( std::string name, int& positionX ,  int& positionY); // Message passing by reference

    int GetPositionX();
    int GetPositionY();
    // Methods for detecting empty spaces to make a decision
    bool DetectEmptyRight(int (&matrix)[10][10]);
    bool DetectEmptyLeft(int (&matrix)[10][10]);
    bool DetectEmptyUp(int (&matrix)[10][10]);
    bool DetectEmptyDown(int (&matrix)[10][10]);
    // Movement method
    void SolveTheMaze();
    void moveIfOnlyOneDirectionAvailable(bool& right,bool& left,bool& up,bool& down,int (&matrix)[10][10] );
  
};
#endif //MATRIX_MAZE_SOLVER_AVATAR_H
