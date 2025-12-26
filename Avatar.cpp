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
int Avatar::GetAleatoryNumber(int MaximumValue){return rand() % MaximumValue ;}


// ====== Individual Detection Functions ======

bool Avatar::IsRightBlocked(int (&matrix)[10][10])
{
    if (PositionY + 1 > 9) return true;
    else if (matrix[PositionX][PositionY + 1] == 0) return true;
    else return false;
}

bool Avatar::IsLeftBlocked(int (&matrix)[10][10])
{
    if (PositionY - 1 < 0) return true;
    else if (matrix[PositionX][PositionY - 1] == 0) return true;
    else return false;
}

bool Avatar::IsUpBlocked(int (&matrix)[10][10])
{
    if (PositionX - 1 < 0)return true;
    else if (matrix[PositionX - 1][PositionY] == 0) return true;
    else return false;
}

bool Avatar::IsDownBlocked(int (&matrix)[10][10])
{
    if (PositionX + 1 > 9) return true;
    else if (matrix[PositionX + 1][PositionY] == 0) return true;
    else return false;
}


int Avatar::CountBlockedDirections(){
    int (&matrix)[10][10] = Board::GetMatrixStatic();
    int numberOfBlockCells=0;
    if (IsRightBlocked(matrix))  numberOfBlockCells++;
    if (IsLeftBlocked(matrix))   numberOfBlockCells++; 
    if (IsUpBlocked(matrix))     numberOfBlockCells++; 
    if (IsDownBlocked(matrix))   numberOfBlockCells++; 
    return numberOfBlockCells;     
}

bool Avatar::HasRecordedMovements(){return !LastMovements.empty();}

//===================Movement Methods===================

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
        bool right = IsRightBlocked(matrix);
        bool left = IsLeftBlocked(matrix);
        bool up = IsUpBlocked(matrix);
        bool down = IsDownBlocked(matrix);

        int numberOfBlockCells=CountBlockedDirections();

        //if the avatar is in a DeadEnd
        if(numberOfBlockCells==3)
        {
            //Block the cell like a DeadEnd
            matrix[PositionX][PositionY]=0; 
            MoveIfOnlyOneDirectionAvailable(right,left,up,down);
            // if movements have already been made, delete last movement  
            if (HasRecordedMovements())LastMovements.pop_back();           
        }
        else if(numberOfBlockCells==2) MoveIfTwoDirectionsAvailable(right,left,up,down);
        else if(numberOfBlockCells==1) MoveIfThreeDirectionsAvailable(right,left,up,down);
        // avatar is not blocked around, so can make any decision
        else MoveIfFourDirectionsAvailable();            
        view.IncrementSteps();
        view.DrawBoard(matrix);
        view.Delay(500);
    }
    view.ShowVictory();
}

void Avatar::MoveIfOnlyOneDirectionAvailable(bool& right,bool& left,bool& up,bool& down)
{
    if (right && left && up)        Move("Down");          // Blocked right, left and up: move down       
    else if (right && left && down) Move("Up");      // Blocked right, left and down: move up
    else if (right && down && up)   Move("Left");     // Blocked right, down and up: move left
    else if (left && down && up)    Move("Right");    // Blocked left, down and up: move right
}

void Avatar::MoveIfTwoDirectionsAvailable(bool& right,bool& left,bool& up,bool& down)
{
    int option=GetAleatoryNumber(2); // Chose 1 or 2
    
    if (left && right) // Blocked left and right
    { 
        // if a movement has already been recorded:
        if (HasRecordedMovements()) Move(GetLastMoveDirection()=="Up" ? "Up": "Down");  //if last movement was up then continue up , else down
        else Move(option==1 ? "Up" : "Down");    // if no movement has been recorded, make random decision

    }
    else if (right && up) // Blocked right and up
    { 
        if (HasRecordedMovements()) Move(GetLastMoveDirection()=="Right" ? "Down" : "Left");        
        else Move(option==1 ? "Down" : "Left");
    }
    else if (right && down) // Blocked right and down
    { 
        if (HasRecordedMovements()) Move(GetLastMoveDirection()=="Right"? "Up": "Left");
        else Move(option==1 ? "Up" : "Left" );
    }
    else if (left && up) // Blocked left and up
    { 
        if (HasRecordedMovements()) Move(GetLastMoveDirection()=="Left" ? "Down" : "Right");
        else Move(option==1 ? "Down" : "Right");

    }
    else if (left && down) // Blocked left and down
    { 
        if (HasRecordedMovements()) Move(GetLastMoveDirection()=="Left" ? "Up" : "Right");
        else Move(option==1 ? "Up" : "Right");
    }
    else if (up && down) // Blocked up and down
    { 
        if (HasRecordedMovements()) Move(GetLastMoveDirection()=="Left" ? "Left" : "Right");
        else Move(option==1 ? "Left" : "Right");
    }
}

void Avatar:: MoveIfThreeDirectionsAvailable(bool& right,bool& left,bool& up,bool& down)
{
    int option1= GetAleatoryNumber(2);
    int option2= GetAleatoryNumber(3);
    if (up) // Blocked up: decide between down, left or right
    { 
        if (HasRecordedMovements())
        {
            if (GetLastMoveDirection() == "Up")         Move(option1==1 ? "Right" : "Left");
            else if (GetLastMoveDirection() == "Right") Move(option1==1 ? "Right" : "Down");
            else if (GetLastMoveDirection() == "Left")  Move(option1==1 ? "Down" : "Left");
        }
        else
        {
            if (option2 == 1)       Move("Down");
            else if (option2 == 2)  Move("Right");
            else                    Move("Left");
        }
    }
    else if (down) // Blocked down: decide between up, left or right
    { 
        if (HasRecordedMovements())
        {
            if (GetLastMoveDirection() == "Down")       Move(option1==1 ? "Right" : "Left");
            else if (GetLastMoveDirection() == "Right") Move(option1==1 ? "Right" : "Up");
            else if (GetLastMoveDirection() == "Left")  Move(option1==1 ? "Left" : "Up");
        }
        else
        {
            if (option2 == 1)       Move("Up");
            else if (option2 == 2)  Move("Left");
            else                    Move("Right");
        }
    }
    else if (right) // Blocked right: decide between other three directions
    { 
        if (HasRecordedMovements())
        {
            if (GetLastMoveDirection() == "Up")         Move(option1==1 ? "Left" : "Up");
            else if (GetLastMoveDirection() == "Down")  Move(option1==1 ? "Down" : "Left");
            else if (GetLastMoveDirection() == "Right") Move(option1==1 ? "Up" : "Down");
        }
        else
        {
            if (option2 == 1)       Move("Down");
            else if (option2 == 2)  Move("Up");
            else                    Move("Left");
        }
    }
    else if (left) // Blocked left: decide between other three directions
    { 
        if (HasRecordedMovements())
        {
            if (GetLastMoveDirection() == "Down")       Move(option1==1 ? "Right" : "Down");
            else if (GetLastMoveDirection() == "Up")    Move(option1==1 ? "Right" : "Up");
            else if (GetLastMoveDirection() == "Left")  Move(option1==1 ? "Up" : "Down");
        }
        else
        {
            if (option2 == 1)       Move("Down");
            else if (option2 == 2)  Move("Up");
            else                    Move("Right");
        }
    }    
}

void Avatar::MoveIfFourDirectionsAvailable()
{
    if (HasRecordedMovements())
    {
        int option= GetAleatoryNumber(3);
        if (GetLastMoveDirection() == "Down")
        {
            if (option == 1)      Move("Right");
            else if (option == 2) Move("Down");
            else                  Move("Left");
        }
        else if (GetLastMoveDirection() == "Up")
        {
            if (option == 1)      Move("Right");
            else if (option == 2) Move("Up");
            else                  Move("Left");
        }

        else if (GetLastMoveDirection() == "Right")
        {
            if (option == 1)      Move("Right");
            else if (option == 2) Move("Up");
            else                  Move("Down");
        }

        else if (GetLastMoveDirection() == "Left")
        {
            if (option == 1)      Move("Left");
            else if (option == 2) Move("Up");
            else                  Move("Down");
        }
    }
    else
    {
        int  option = GetAleatoryNumber(4);
        if (option == 1)       Move("Down");
        else if (option == 2)  Move("Up");
        else if (option == 3)  Move("Right");
        else                   Move("Left");
    }
}
void Avatar::Move(std::string Direction)
{
    // If the avatar is not in a dead end, save the next move direction.
    if (CountBlockedDirections()!=3) LastMovements.emplace_back(Direction); 
    if (Direction=="Right")     PositionY++;      
    else if (Direction=="Left") PositionY--;
    else if (Direction=="Up")   PositionX--;
    else if (Direction=="Down") PositionX++;
}
