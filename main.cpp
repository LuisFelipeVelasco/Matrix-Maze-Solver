#include <iostream>
#include <string>
#include "Board.h"
#include "Avatar.h"
#include <exception>
#include <cassert>
/*
Project: Matrix-Maze-Solver

Summary:
This program is an algorithm whose protagonist is an object of the Avatar class and traverses
the coordinates of a matrix that represents a maze. Empty spaces and dead ends are represented 
as 0 and Free Spaces as 1. Goal: Reach the exit located at cell [9,9]
*/

int main()
{
    // === BOARD ===
    Board Maze;
    Maze.DefinePosition();
    int PositionX = Maze.GetBoardX();
    int PositionY = Maze.GetBoardY();
    Avatar IntelligentAgent("Smart", PositionX, PositionY);
    IntelligentAgent.SolveTheMaze();
    return 0;
}
