#ifndef MATRIX_MAZE_SOLVER_VISUAL_H
#define MATRIX_MAZE_SOLVER_VISUAL_H
/*
===============================================================================
                                CRC CARD
===============================================================================
Class Name: Visual
Responsibilities:
    - Display the algorithm execution in console
Collaborators:
    - Board
    - Movement
===============================================================================
*/
class Visual {
private:
    int* PositionX;
    int* PositionY;
    int StepCounter;
    bool UseAsciiFallback; // fallback if console does not support UTF-8/ANSI

    void ClearScreen();
    void ShowCell(int value, bool isCurrentPosition, bool isExit);
    void ShowHeader();
    void ShowLegend();
    void EnableUtf8AndAnsi(); // enable UTF-8 and ANSI on Windows

public:
    Visual(int* posX, int* posY);
    void DrawBoard(int (&matrix)[10][10]);
    void Delay(int milliseconds);
    void IncrementSteps();
    void ShowVictory();
};

#endif //MATRIX_MAZE_SOLVER_VISUAL_H
