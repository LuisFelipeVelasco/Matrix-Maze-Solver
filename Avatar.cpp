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

int Avatar::GetPositionX(){return PositionX;}
int Avatar::GetPositionY(){return PositionY;}

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

int Avatar::countBlockedDirections(bool& right,bool& left,bool& up,bool& down){
    int numberOfBlockCells=0;
    if (right) numberOfBlockCells++;
    if (left) numberOfBlockCells++; 
    if (up) numberOfBlockCells++; 
    if (down) numberOfBlockCells++; 
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
    view.Delay(2000);            // 2 second pause at start

    while (PositionY != 9 || PositionX != 9)
    {   // execute until reaching exit
        // Variables right,left,up,down to detect path direction around avatar
        bool right = DetectEmptyRight(matrix);
        bool left = DetectEmptyLeft(matrix);
        bool up = DetectEmptyUp(matrix);
        bool down = DetectEmptyDown(matrix);

        int numberOfBlockCells=countBlockedDirections(right,left,up,down);
    if(numberOfBlockCells==3){
            matrix[PositionX][PositionY]=0;
            moveIfOnlyOneDirectionAvailable(right,left,up,down);
            if (!LastMovements.empty())LastMovements.pop_back(); // if movements have already been made, delete last movement            

        }

       // moveIfOnlyOneDirectionAvailable(right,left,up,down,matrix);
      else if (left && right)
        { // Blocked left and right
            if (!LastMovements.empty())
                { // if a movement has already been recorded:
                    if (LastMovements[LastMovements.size() - 1] == "Up")
                        {
                    PositionX--;
                    LastMovements.emplace_back("Up");
                        } // if last movement was up then continue up
                else if (LastMovements[LastMovements.size() - 1] == "Down")
                    {
                    PositionX++;
                    LastMovements.emplace_back("Down");
                    }
            }
            else
                { // if no movement has been recorded, make random decision and add to vector
                int option = rand() % 2;
                if (option == 1)
                    {
                    PositionX--;
                    LastMovements.emplace_back("Up");
                    }
                else
                    {
                    PositionX++;
                    LastMovements.emplace_back("Down");
                    }
            }
        }
    else if (right && up)
        { // Blocked right and up
            if (!LastMovements.empty())
            {
                if (LastMovements[LastMovements.size() - 1] == "Right")
                    {
                          PositionX++;
                        LastMovements.emplace_back("Down");
                    }
                else if (LastMovements[LastMovements.size() - 1] == "Up")
                {
                    PositionY--;
                    LastMovements.emplace_back("Left");
                }
            }
            else
            {
                int option = rand() % 2;
                if (option == 1)
                {
                    PositionY--;
                    LastMovements.emplace_back("Left");
                }
                else
                {
                    PositionX++;
                    LastMovements.emplace_back("Down");
                }
            }
        }
    else if (right && down)
        { // Blocked right and down
            if (!LastMovements.empty())
            {
                if (LastMovements[LastMovements.size() - 1] == "Right")
                {
                    PositionX--;
                    LastMovements.emplace_back("Up");
                }
                else if (LastMovements[LastMovements.size() - 1] == "Down")
                {
                    PositionY--;
                    LastMovements.emplace_back("Left");
                }
            }
            else
            {
                int option = rand() % 2;
                if (option == 1)
                {
                    PositionY--;
                    LastMovements.emplace_back("Left");
                }
                else
                {
                    PositionX--;
                    LastMovements.emplace_back("Up");
                }
            }
        }
    else if (left && up)
        { // Blocked left and up
            if (!LastMovements.empty())
            {
                if (LastMovements[LastMovements.size() - 1] == "Left")
                {
                    PositionX++;
                    LastMovements.emplace_back("Down");
                }
                else if (LastMovements[LastMovements.size() - 1] == "Up")
                {
                    PositionY++;
                    LastMovements.emplace_back("Right");
                }
            }

            else
            {
                int option = rand() % 2;
                if (option == 1)
                {
                    PositionY++;
                    LastMovements.emplace_back("Right");
                }
                else
                {
                    PositionX++;
                    LastMovements.emplace_back("Down");
                }
            }
        }
    else if (left && down)
        { // Blocked left and down
            if (!LastMovements.empty())
            {
                if (LastMovements[LastMovements.size() - 1] == "Left")
                {
                    PositionX--;
                    LastMovements.emplace_back("Up");
                }
                else if (LastMovements[LastMovements.size() - 1] == "Down")
                {
                    PositionY++;
                    LastMovements.emplace_back("Right");
                }
            }

            else
            {
                int option = rand() % 2;
                if (option == 1)
                {
                    PositionY++;
                    LastMovements.emplace_back("Right");
                }
                else
                {
                    PositionX--;
                    LastMovements.emplace_back("Up");
                }
            }
        }
    else if (up && down)
        { // Blocked up and down
            if (!LastMovements.empty())
            { // if vector of last movements is not empty then execute inside
                if (LastMovements[LastMovements.size() - 1] == "Left")
                {
                    PositionY--;
                    LastMovements.emplace_back("Left");
                } // if last movement comes from left then continue left
                else if (LastMovements[LastMovements.size() - 1] == "Right")
                {
                    PositionY++;
                    LastMovements.emplace_back("Right");
                } // if last movement comes from right then continue right
            }

            else
            {
                int option = rand() % 2;
                if (option == 1)
                {
                    PositionY++;
                    LastMovements.emplace_back("Right");
                }
                else
                {
                    PositionY--;
                    LastMovements.emplace_back("Left");
                }
            }
        }

    else if (up)
        { // Blocked up: decide between down, left or right
            if (!LastMovements.empty())
            {
                if (LastMovements[LastMovements.size() - 1] == "Up")
                {
                    int option = rand() % 2;
                    if (option == 1)
                    {
                        PositionY++;
                        LastMovements.emplace_back("Right");
                    }
                    else
                    {
                        PositionY--;
                        LastMovements.emplace_back("Left");
                    }
                }

                else if (LastMovements[LastMovements.size() - 1] == "Right")
                {
                    int option = rand() % 2;
                    if (option == 1)
                    {
                        PositionY++;
                        LastMovements.emplace_back("Right");
                    }
                    else
                    {
                        PositionX++;
                        LastMovements.emplace_back("Down");
                    }
                }

                else if (LastMovements[LastMovements.size() - 1] == "Left")
                {
                    int option = rand() % 2;
                    if (option == 1)
                    {
                        PositionY--;
                        LastMovements.emplace_back("Left");
                    }
                    else
                    {
                        PositionX++;
                        LastMovements.emplace_back("Down");
                    }
                }
            }
            else
            {
                int option = rand() % 3;
                if (option == 1)
                {
                    PositionX++;
                    LastMovements.emplace_back("Down");
                }
                else if (option == 2)
                {
                    PositionY++;
                    LastMovements.emplace_back("Right");
                }
                else
                {
                    PositionY--;
                    LastMovements.emplace_back("Left");
                }
            }
        }
    else if (down)
        { // Blocked down: decide between up, left or right
            if (!LastMovements.empty())
            {

                if (LastMovements[LastMovements.size() - 1] == "Down")
                {
                    int option = rand() % 2;
                    if (option == 1)
                    {
                        PositionY++;
                        LastMovements.emplace_back("Right");
                    }
                    else
                    {
                        PositionY--;
                        LastMovements.emplace_back("Left");
                    }
                }

                else if (LastMovements[LastMovements.size() - 1] == "Right")
                {
                    int option = rand() % 2;
                    if (option == 1)
                    {
                        PositionY++;
                        LastMovements.emplace_back("Right");
                    }
                    else
                    {
                        PositionX--;
                        LastMovements.emplace_back("Up");
                    }
                }

                else if (LastMovements[LastMovements.size() - 1] == "Left")
                {
                    int option = rand() % 2;
                    if (option == 1)
                    {
                        PositionY--;
                        LastMovements.emplace_back("Left");
                    }
                    else
                    {
                        PositionX--;
                        LastMovements.emplace_back("Up");
                    }
                }
            }

            else
            {
                int option = rand() % 3;
                if (option == 1)
                {
                    PositionX--;
                    LastMovements.emplace_back("Up");
                }
                else if (option == 2)
                {
                    PositionY--;
                    LastMovements.emplace_back("Left");
                }
                else
                {
                    PositionY++;
                    LastMovements.emplace_back("Right");
                }
            }
        }
    else if (right)
        { // Blocked right: decide between other three directions
            if (!LastMovements.empty())
            {
                if (LastMovements[LastMovements.size() - 1] == "Up")
                {
                    int option = rand() % 2;
                    if (option == 1)
                    {
                        PositionY--;
                        LastMovements.emplace_back("Left");
                    }
                    else
                    {
                        PositionX--;
                        LastMovements.emplace_back("Up");
                    }
                }
                else if (LastMovements[LastMovements.size() - 1] == "Down")
                {
                    int option = rand() % 2;
                    if (option == 1)
                    {
                        PositionY--;
                        LastMovements.emplace_back("Left");
                    }
                    else
                    {
                        PositionX++;
                        LastMovements.emplace_back("Down");
                    }
                }

                else if (LastMovements[LastMovements.size() - 1] == "Right")
                {
                    int option = rand() % 2;
                    if (option == 1)
                    {
                        PositionX--;
                        LastMovements.emplace_back("Up");
                    }
                    else
                    {
                        PositionX++;
                        LastMovements.emplace_back("Down");
                    }
                }
            }

            else
            {
                int option = rand() % 3;
                if (option == 1)
                {
                    PositionX++;
                    LastMovements.emplace_back("Down");
                }
                else if (option == 2)
                {
                    PositionX--;
                    LastMovements.emplace_back("Up");
                }
                else
                {
                    PositionY--;
                    LastMovements.emplace_back("Left");
                }
            }
        }

    else if (left)
        { // Blocked left: decide between other three directions
            if (!LastMovements.empty())
            {
                if (LastMovements[LastMovements.size() - 1] == "Down")
                {
                    int option = rand() % 2;
                    if (option == 1)
                    {
                        PositionY++;
                        LastMovements.emplace_back("Right");
                    }
                    else
                    {
                        PositionX++;
                        LastMovements.emplace_back("Down");
                    }
                }

                else if (LastMovements[LastMovements.size() - 1] == "Up")
                {
                    int option = rand() % 2;
                    if (option == 1)
                    {
                        PositionY++;
                        LastMovements.emplace_back("Right");
                    }
                    else
                    {
                        PositionX--;
                        LastMovements.emplace_back("Up");
                    }
                }

                else if (LastMovements[LastMovements.size() - 1] == "Left")
                {
                    int option = rand() % 2;
                    if (option == 1)
                    {
                        PositionX--;
                        LastMovements.emplace_back("Up");
                    }
                    else
                    {
                        PositionX++;
                        LastMovements.emplace_back("Down");
                    }
                }
            }

            else
            {
                int option = rand() % 3;
                if (option == 1)
                {
                    PositionX++;
                    LastMovements.emplace_back("Down");
                }
                else if (option == 2)
                {
                    PositionX--;
                    LastMovements.emplace_back("Up");
                }
                else
                {
                    PositionY++;
                    LastMovements.emplace_back("Right");
                }
            }
        }

    else
        { // avatar is not blocked around, so can make any decision
            if (!LastMovements.empty())
            {
                if (LastMovements[LastMovements.size() - 1] == "Down")
                {
                    int option = rand() % 3;
                    if (option == 1)
                    {
                        PositionY++;
                        LastMovements.emplace_back("Right");
                    }
                    else if (option == 2)
                    {
                        PositionX++;
                        LastMovements.emplace_back("Down");
                    }
                    else
                    {
                        PositionY--;
                        LastMovements.emplace_back("Left");
                    }
                }

                else if (LastMovements[LastMovements.size() - 1] == "Up")
                {
                    int option = rand() % 3;
                    if (option == 1)
                    {
                        PositionY++;
                        LastMovements.emplace_back("Right");
                    }
                    else if (option == 2)
                    {
                        PositionX--;
                        LastMovements.emplace_back("Up");
                    }
                    else
                    {
                        PositionY--;
                        LastMovements.emplace_back("Left");
                    }
                }

                else if (LastMovements[LastMovements.size() - 1] == "Right")
                {
                    int option = rand() % 3;
                    if (option == 1)
                    {
                        PositionY++;
                        LastMovements.emplace_back("Right");
                    }
                    else if (option == 2)
                    {
                        PositionX--;
                        LastMovements.emplace_back("Up");
                    }
                    else
                    {
                        PositionX++;
                        LastMovements.emplace_back("Down");
                    }
                }

                else if (LastMovements[LastMovements.size() - 1] == "Left")
                {
                    int option = rand() % 3;
                    if (option == 1)
                    {
                        PositionY--;
                        LastMovements.emplace_back("Left");
                    }
                    else if (option == 2)
                    {
                        PositionX--;
                        LastMovements.emplace_back("Up");
                    }
                    else
                    {
                        PositionX++;
                        LastMovements.emplace_back("Down");
                    }
                }
            }
            else
            {
                int option = rand() % 4;
                if (option == 1)
                {
                    PositionX++;
                    LastMovements.emplace_back("Down");
                }
                else if (option == 2)
                {
                    PositionX--;
                    LastMovements.emplace_back("Up");
                }
                else if (option == 3)
                {
                    PositionY++;
                    LastMovements.emplace_back("Right");
                }
                else
                {
                    PositionY--;
                    LastMovements.emplace_back("Left");
                }
            }
        }
        view.IncrementSteps();
        view.DrawBoard(matrix);
        view.Delay(500);
    }
    view.ShowVictory();
}

// ====== Individual Detection Functions ======




void Avatar::moveIfOnlyOneDirectionAvailable(bool& right,bool& left,bool& up,bool& down){
    if (right && left && up)
        {            
            PositionX++;// Blocked right, left and up: move down
        }
    else if (right && left && down)
        {
            PositionX--;// Blocked right, left and down: move up
        }
    else if (right && down && up)
        {
            PositionY--;// Blocked right, down and up: move left
        }
    else if (left && down && up)
        {
            PositionY++;// Blocked left, down and up: move right
        }

}



