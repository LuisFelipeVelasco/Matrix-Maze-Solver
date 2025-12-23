#include <gtest/gtest.h>
#include <thread>
#include "../Avatar.h"
#include "../Board.h"



TEST(TEST_MATRIX_MAZE_SOLVER,FINALPOSITION){
    Board Maze;
    Maze.DefinePosition();
    int PositionX=Maze.GetBoardX();
    int PositionY=Maze.GetBoardY();
    Avatar Avatar1("Smart",PositionX,PositionY);
    Avatar1.Move();
    EXPECT_EQ(Avatar1.GetPositionX(),9);
    EXPECT_EQ(Avatar1.GetPositionY(),9);
}

TEST(TEST_MATRIX_MAZE_SOLVER,POSTION){
    Board Maze;
    int Position= Maze.ChoseNumberPosition(Position);
    EXPECT_GE(Position, 0);   // PositionX >= 0
    EXPECT_LT(Position, 10);  // PositionX < 10

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}