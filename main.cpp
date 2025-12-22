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
    std::cout << "===== DEBUGGER STARTED =====" << std::endl;

    // === BOARD ===
    std::cout << "[DEBUG] Creating Board object (Maze)..." << std::endl;
    Board Maze;
    std::cout << "[DEBUG] Defining initial position..." << std::endl;
    Maze.DefinePosition();
    int PositionX = Maze.GetBoardX();
    int PositionY = Maze.GetBoardY();
    std::cout << "[INFO] Initial position obtained: X=" << PositionX << " , Y=" << PositionY << std::endl;
    // Validation with assert
    assert(PositionX >= 0 && "ERROR: PositionX cannot be negative");
    assert(PositionY >= 0 && "ERROR: PositionY cannot be negative");
    // === AVATAR ===
    std::cout << "\n[DEBUG] Creating Avatar 'Smart'..." << std::endl;
    Avatar IntelligentAgent("Smart", PositionX, PositionY);
    std::cout << "[DEBUG] Showing initial position of Avatar..." << std::endl;
    
    // Verify consistency
    assert(IntelligentAgent.GetPositionX() == PositionX && "ERROR: Avatar X Position does not match Board position");
    assert(IntelligentAgent.GetPositionY() == PositionY && "ERROR: Avatar Y Position does not match Board position");

    // === MOVEMENT ===
    std::cout << "\n[DEBUG] Initializing Movement module..." << std::endl;
    std::cout << "[DEBUG] Executing Move() method..." << std::endl;
    try
    {
        IntelligentAgent.Move();
        std::cout << "[OK] Movement executed without errors." << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "[EXCEPTION] Error during movement: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "[EXCEPTION] Unknown error during movement." << std::endl;
    }

    return 0;
}
