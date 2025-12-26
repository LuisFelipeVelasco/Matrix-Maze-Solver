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

    // Getter Methods

    int GetPositionX();
    int GetPositionY();
    std::string GetLastMoveDirection();
    int GetAleatoryNumber(int MaximumValue);

    // Methods for detecting block spaces to make a decision
    bool IsRightBlocked(int (&matrix)[10][10]);
    bool IsLeftBlocked(int (&matrix)[10][10]);
    bool IsUpBlocked(int (&matrix)[10][10]);
    bool IsDownBlocked(int (&matrix)[10][10]);
    int CountBlockedDirections();

    // Movement methods
    void SolveTheMaze();
    void MoveIfOnlyOneDirectionAvailable(bool& right,bool& left,bool& up,bool& down);
    void MoveIfTwoDirectionsAvailable(bool& right,bool& left,bool& up,bool& down);
    void MoveIfThreeDirectionsAvailable(bool& right,bool& left,bool& up,bool& down);
    void MoveIfFourDirectionsAvailable();
    void Move(std::string Direction);
    bool HasRecordedMovements();
};
#endif //MATRIX_MAZE_SOLVER_AVATAR_H
