#include "Board.h"
#include "Avatar.h"
#include "Visual.h"
#include <string>
#include <iostream>
#include <vector>
/*
===============================================================================
                        IMPLEMENTATION OF THE AVATAR CLASS
===============================================================================
The Avatar class represents the actions that the avatar can perform,
modifying its coordinates to simulate its displacement

Demonstrates:
 - Passing objects by reference
 - Associating an existing board position (by reference)
 - Changing current position moving in different directions
 - Integration with the Visual class to show progress
===============================================================================
*/

Avatar::Avatar(std::string name , int &x, int &y) : Name (name ) ,PositionX(x), PositionY(y) {}

// ========== Getter Methods =============

int Avatar::GetPositionX(){return PositionX;}
int Avatar::GetPositionY(){return PositionY;}
std::string Avatar::GetLastMoveDirection(){return LastMovements[LastMovements.size()-1] ;}


// ====== Individual Detection Functions ======

bool Avatar::DetectEmptyRight(int (&matrix)[10][10])
{
    if (PositionY + 1 > 9) return true;
    else if (matrix[PositionX][PositionY + 1] == 0) return true;
    else return false;
}

bool Avatar::DetectEmptyLeft(int (&matrix)[10][10])
{
    if (PositionY - 1 < 0) return true;
    else if (matrix[PositionX][PositionY - 1] == 0) return true;
    else return false;
}

bool Avatar::DetectEmptyUp(int (&matrix)[10][10])
{
    if (PositionX - 1 < 0)return true;
    else if (matrix[PositionX - 1][PositionY] == 0) return true;
    else return false;
}

bool Avatar::DetectEmptyDown(int (&matrix)[10][10])
{
    if (PositionX + 1 > 9) return true;
    else if (matrix[PositionX + 1][PositionY] == 0) return true;
    else return false;
}

//==============================================================

int Avatar::CountBlockedDirections(){
    int (&matrix)[10][10] = Board::GetMatrixStatic();
    int numberOfBlockCells=0;
    if (DetectEmptyRight(matrix)) numberOfBlockCells++;
    if (DetectEmptyLeft(matrix)) numberOfBlockCells++; 
    if (DetectEmptyUp(matrix)) numberOfBlockCells++; 
    if (DetectEmptyDown(matrix)) numberOfBlockCells++; 
    return numberOfBlockCells;     
}

void Avatar::SolveTheMaze()
{
    // Create Visual object passing pointers to positions
    Visual view(&PositionX, &PositionY);
    // Get reference to board matrix
    int (&matrix)[10][10] = Board::GetMatrixStatic();
    // Show initial state of maze
    view.DrawBoard(matrix);
    // 2 second pause at start
    view.Delay(2000);            
    // execute until reaching exit
    while (PositionY != 9 || PositionX != 9)  
    {  
        // Variables right,left,up,down to detect path direction around avatar
        bool right = DetectEmptyRight(matrix);
        bool left = DetectEmptyLeft(matrix);
        bool up = DetectEmptyUp(matrix);
        bool down = DetectEmptyDown(matrix);

        int numberOfBlockCells=CountBlockedDirections();

        //if the avatar is in a DeadEnd
        if(numberOfBlockCells==3)
        {
            //Block the cell like a DeadEnd
            matrix[PositionX][PositionY]=0; 
            MoveIfOnlyOneDirectionAvailable(right,left,up,down);
            // if movements have already been made, delete last movement  
            if (!LastMovements.empty())LastMovements.pop_back();           
        }

        else if (left && right) // Blocked left and right
        { 
            if (!LastMovements.empty())
            {   
                // if a movement has already been recorded:
                if (GetLastMoveDirection() == "Up") Move("Up");      // if last movement was up then continue up
                else Move("Down");                                  // if last movement wasn´t up then continue down
            }
            else
            { // if no movement has been recorded, make random decision and add to vector
                int option = rand() % 2;
                if (option == 1) Move("Up");
                else Move("Down");
            }
        }
        else if (right && up) // Blocked right and up
        { 
            if (!LastMovements.empty())
            {
                if (GetLastMoveDirection() == "Right") Move("Down");
                else Move("Left");
            }
            else
            {
                int option = rand() % 2;
                if (option == 1) Move("Down");
                else Move("Left");
            }
        }
        else if (right && down) // Blocked right and down
        { 
            if (!LastMovements.empty())
            {
                if (GetLastMoveDirection() == "Right") Move("Up");
                else Move("Left");
            }
            else
            {
                int option = rand() % 2;
                if (option == 1) Move("Up");
                else Move("Left");
            }
        }
        else if (left && up) // Blocked left and up
        { 
            if (!LastMovements.empty())
            {
                if (GetLastMoveDirection() == "Left") Move("Down");
                else Move("Right");
            }
            else
            {
                int option = rand() % 2;
                if (option == 1) Move("Right");
                else Move("Down");
            }
        }
        else if (left && down) // Blocked left and down
        { 
            if (!LastMovements.empty())
            {
                if (GetLastMoveDirection() == "Left") Move("Up");
                else Move("Right");
            }
            else
            {
                int option = rand() % 2;
                if (option == 1) Move("Up");
                else Move("Right");

            }
        }
        else if (up && down) // Blocked up and down
        { 
            if (!LastMovements.empty())
            { 
                if (GetLastMoveDirection() == "Left") Move("Left");
                else Move("Right");
            }
            else
            {
                int option = rand() % 2;
                if (option == 1) Move("Left");
                else Move("Right");
            }
        }

        else if (up) // Blocked up: decide between down, left or right
        { 
            if (!LastMovements.empty())
            {
                if (GetLastMoveDirection() == "Up")
                {
                    int option = rand() % 2;
                    if (option == 1) Move("Right");
                    else Move("Left");
                }

                else if (GetLastMoveDirection() == "Right")
                {
                    int option = rand() % 2;
                    if (option == 1) Move("Right");
                    else Move("Down");
                }

                else if (GetLastMoveDirection() == "Left")
                {
                    int option = rand() % 2;
                    if (option == 1) Move("Left");
                    else Move("Down");
                }
            }
            else
            {
                int option = rand() % 3;
                if (option == 1) Move("Down");
                else if (option == 2) Move("Right");
                else Move("Left");
            }
        }
        else if (down) // Blocked down: decide between up, left or right
        { 
            if (!LastMovements.empty())
            {

                if (GetLastMoveDirection() == "Down")
                {
                    int option = rand() % 2;
                    if (option == 1) Move("Right");
                    else Move("Left");
                }

                else if (GetLastMoveDirection() == "Right")
                {
                    int option = rand() % 2;
                    if (option == 1) Move("Right");
                    else Move("Up");
                }

                else if (GetLastMoveDirection() == "Left")
                {
                    int option = rand() % 2;
                    if (option == 1) Move("Left");
                    else Move("Up");
                }
            }
            else
            {
                int option = rand() % 3;
                if (option == 1) Move("Up");
                else if (option == 2) Move("Left");
                else Move("Right");
            }
        }
        else if (right) // Blocked right: decide between other three directions
        { 
            if (!LastMovements.empty())
            {
                if (GetLastMoveDirection() == "Up")
                {
                    int option = rand() % 2;
                    if (option == 1) Move("Left");
                    else Move("Up");
                }
                else if (GetLastMoveDirection() == "Down")
                {
                    int option = rand() % 2;
                    if (option == 1) Move("Left");
                    else Move("Down");
                }

                else if (GetLastMoveDirection() == "Right")
                {
                    int option = rand() % 2;
                    if (option == 1) Move("Up");
                    else Move("Down");
                }
            }
            else
            {
                int option = rand() % 3;
                if (option == 1) Move("Down");
                else if (option == 2) Move("Up");
                else Move("Left");
            }
        }

        else if (left) // Blocked left: decide between other three directions
        { 
            if (!LastMovements.empty())
            {
                if (GetLastMoveDirection() == "Down") 
                {
                    int option = rand() % 2;
                    if (option == 1) Move("Right");
                    else Move("Down");

                }

                else if (GetLastMoveDirection() == "Up")
                {
                    int option = rand() % 2;
                    if (option == 1) Move("Right");
                    else Move("Up");
                }

                else if (GetLastMoveDirection() == "Left")
                {
                    int option = rand() % 2;
                    if (option == 1) Move("Up");
                    else Move("Down");
                }
            }

            else
            {
                int option = rand() % 3;
                if (option == 1) Move("Down");
                else if (option == 2) Move("Up");
                else Move("Right");
            }
        }

        else // avatar is not blocked around, so can make any decision
        { 
            if (!LastMovements.empty())
            {
                if (GetLastMoveDirection() == "Down")
                {
                    int option = rand() % 3;
                    if (option == 1) Move("Right");
                    else if (option == 2) Move("Down");
                    else Move("Left");

                }

                else if (GetLastMoveDirection() == "Up")
                {
                    int option = rand() % 3;
                    if (option == 1) Move("Right");
                    else if (option == 2) Move("Up");
                    else Move("Left");
                }

                else if (GetLastMoveDirection() == "Right")
                {
                    int option = rand() % 3;
                    if (option == 1) Move("Right");
                    else if (option == 2) Move("Up");
                    else Move("Down");
                }

                else if (GetLastMoveDirection() == "Left")
                {
                    int option = rand() % 3;
                    if (option == 1) Move("Left");
                    else if (option == 2) Move("Up");
                    else Move("Down");
                }
            }
            else
            {
                int option = rand() % 4;
                if (option == 1) Move("Down");
                else if (option == 2) Move("Up");
                else if (option == 3) Move("Right");
                else Move("Left");
            }
        }
        view.IncrementSteps();
        view.DrawBoard(matrix);
        view.Delay(500);
    }
    view.ShowVictory();
}

void Avatar::MoveIfOnlyOneDirectionAvailable(bool& right,bool& left,bool& up,bool& down)
{
    if (right && left && up) Move("Down");          // Blocked right, left and up: move down       
    else if (right && left && down)Move("Up");      // Blocked right, left and down: move up
    else if (right && down && up) Move("Left");     // Blocked right, down and up: move left
    else if (left && down && up)  Move("Right");    // Blocked left, down and up: move right
}

void Avatar::Move(std::string Direction)
{
    // If the avatar is not in a dead end, save the next move direction.
    if (CountBlockedDirections()!=3) LastMovements.emplace_back(Direction); 
    if (Direction=="Right") PositionY++;      
    else if (Direction=="Left") PositionY--;
    else if (Direction=="Up")  PositionX--;
    else if (Direction=="Down") PositionX++;
}