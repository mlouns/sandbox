#include "gtest/gtest.h"
#include "robot.h"

using std::cerr;
using std::endl;
using std::string;

using Mars::Plateau;
using Mars::Rover;


// Simple test for initializing a Plateau.
TEST(Plateau, Init)
{
    Plateau plateau(10, 5);

    EXPECT_EQ(10, plateau.MaxWidth());
    EXPECT_EQ(5, plateau.MaxHeight());
}

// Test legal positions on the plateau
TEST(Plateau, IsValidPosition)
{
    Plateau plateau(10, 5);

    for (int x = 0; x <= plateau.MaxWidth(); ++x)
    {
        for (int y = 0; y <= plateau.MaxHeight(); ++y)
        {
            EXPECT_TRUE(plateau.IsValidPosition(x, y));
        }
        EXPECT_FALSE(plateau.IsValidPosition(x, -1));
        EXPECT_FALSE(plateau.IsValidPosition(x, plateau.MaxHeight() + 1));
    }
    for (int y = 0; y <= plateau.MaxHeight(); ++y)
    {
        EXPECT_FALSE(plateau.IsValidPosition(-1, y));
        EXPECT_FALSE(plateau.IsValidPosition(plateau.MaxWidth() + 1, y));
    }
}


// Simple test for initializing a Rover.
TEST(Rover, Init_01)
{
    Plateau plateau(10, 5);

    EXPECT_EQ(0, plateau.RoverCount());

    Rover rover(1, 2, 'N', "LMLMLMLMM", plateau);

    EXPECT_EQ(1, plateau.RoverCount());

    int x, y;
    rover.GetCurrentPosition(x, y);

    EXPECT_EQ(1, x);
    EXPECT_EQ(2, y);

    EXPECT_EQ('N', rover.CurrentDirection());
    EXPECT_STREQ("LMLMLMLMM", rover.Instructions().c_str());

    EXPECT_EQ(0, rover.CurrentInstructionIndex());
    EXPECT_EQ('L', rover.CurrentInstruction());

    EXPECT_EQ(&plateau, &rover.GetPlateau());

    EXPECT_STREQ("1 2 N", rover.CurrentStatus().c_str());
    EXPECT_EQ('^', rover.Marker());
}

// Simple test for initializing two rovers.
TEST(Rover, Init_02)
{
    Plateau plateau(10, 5);

    EXPECT_EQ(0, plateau.RoverCount());

    Rover rover1(1, 2, 'N', "LMLMLMLMM", plateau);

    EXPECT_EQ(1, plateau.RoverCount());

    int x, y;
    rover1.GetCurrentPosition(x, y);

    EXPECT_EQ(1, x);
    EXPECT_EQ(2, y);

    EXPECT_EQ('N', rover1.CurrentDirection());
    EXPECT_STREQ("LMLMLMLMM", rover1.Instructions().c_str());

    EXPECT_EQ(0, rover1.CurrentInstructionIndex());
    EXPECT_EQ('L', rover1.CurrentInstruction());

    EXPECT_EQ(&plateau, &rover1.GetPlateau());

    EXPECT_STREQ("1 2 N", rover1.CurrentStatus().c_str());
    EXPECT_EQ('^', rover1.Marker());

    EXPECT_EQ(1, plateau.RoverCount());

    Rover rover2(3, 3, 'E', "MMRMMRMRRM", plateau);

    EXPECT_EQ(2, plateau.RoverCount());

    rover2.GetCurrentPosition(x, y);

    EXPECT_EQ(3, x);
    EXPECT_EQ(3, y);

    EXPECT_EQ('E', rover2.CurrentDirection());
    EXPECT_STREQ("MMRMMRMRRM", rover2.Instructions().c_str());

    EXPECT_EQ(0, rover2.CurrentInstructionIndex());
    EXPECT_EQ('M', rover2.CurrentInstruction());

    EXPECT_EQ(&plateau, &rover2.GetPlateau());

    EXPECT_STREQ("3 3 E", rover2.CurrentStatus().c_str());
    EXPECT_EQ('>', rover2.Marker());
}

// Turn a rover right
TEST(Rover, TurnRight)
{
    Plateau plateau(10, 5);

    EXPECT_EQ(0, plateau.RoverCount());

    Rover rover(1, 2, 'N', "LMLMLMLMM", plateau);

    int x, y;
    rover.GetCurrentPosition(x, y);

    EXPECT_EQ(1, x);
    EXPECT_EQ(2, y);

    EXPECT_EQ('N', rover.CurrentDirection());
    EXPECT_EQ('^', rover.Marker());

    rover.TurnRight();
    rover.GetCurrentPosition(x, y);

    EXPECT_EQ(1, x);
    EXPECT_EQ(2, y);

    EXPECT_EQ('E', rover.CurrentDirection());
    EXPECT_EQ('>', rover.Marker());

    rover.TurnRight();
    rover.GetCurrentPosition(x, y);

    EXPECT_EQ(1, x);
    EXPECT_EQ(2, y);

    EXPECT_EQ('S', rover.CurrentDirection());
    EXPECT_EQ('V', rover.Marker());

    rover.TurnRight();
    rover.GetCurrentPosition(x, y);

    EXPECT_EQ(1, x);
    EXPECT_EQ(2, y);

    EXPECT_EQ('W', rover.CurrentDirection());
    EXPECT_EQ('<', rover.Marker());

    rover.TurnRight();
    rover.GetCurrentPosition(x, y);

    EXPECT_EQ(1, x);
    EXPECT_EQ(2, y);

    EXPECT_EQ('N', rover.CurrentDirection());
}

// Turn a rover left
TEST(Rover, TurnLeft)
{
    Plateau plateau(10, 5);

    EXPECT_EQ(0, plateau.RoverCount());

    Rover rover(1, 2, 'N', "LMLMLMLMM", plateau);

    int x, y;
    rover.GetCurrentPosition(x, y);

    EXPECT_EQ(1, x);
    EXPECT_EQ(2, y);

    EXPECT_EQ('N', rover.CurrentDirection());

    rover.TurnLeft();
    rover.GetCurrentPosition(x, y);

    EXPECT_EQ(1, x);
    EXPECT_EQ(2, y);

    EXPECT_EQ('W', rover.CurrentDirection());

    rover.TurnLeft();
    rover.GetCurrentPosition(x, y);

    EXPECT_EQ(1, x);
    EXPECT_EQ(2, y);

    EXPECT_EQ('S', rover.CurrentDirection());

    rover.TurnLeft();
    rover.GetCurrentPosition(x, y);

    EXPECT_EQ(1, x);
    EXPECT_EQ(2, y);

    EXPECT_EQ('E', rover.CurrentDirection());

    rover.TurnLeft();
    rover.GetCurrentPosition(x, y);

    EXPECT_EQ(1, x);
    EXPECT_EQ(2, y);

    EXPECT_EQ('N', rover.CurrentDirection());
}

// Move a north-facing rover forward
TEST(Rover, MoveForward_01)
{
    Plateau plateau(10, 5);

    EXPECT_EQ(0, plateau.RoverCount());

    Rover rover(1, 2, 'N', "LMLMLMLMM", plateau);

    int x, y;
    rover.GetCurrentPosition(x, y);

    EXPECT_EQ(1, x);
    EXPECT_EQ(2, y);

    rover.GetForwardPosition(x, y);

    EXPECT_EQ(1, x);
    EXPECT_EQ(3, y);

    EXPECT_EQ('N', rover.CurrentDirection());

    bool success = rover.MoveForward();

    EXPECT_TRUE(success);

    rover.GetCurrentPosition(x, y);

    EXPECT_EQ(1, x);
    EXPECT_EQ(3, y);

    EXPECT_EQ('N', rover.CurrentDirection());

    success = rover.MoveForward();

    EXPECT_TRUE(success);

    rover.GetCurrentPosition(x, y);

    EXPECT_EQ(1, x);
    EXPECT_EQ(4, y);

    EXPECT_EQ('N', rover.CurrentDirection());

    success = rover.MoveForward();

    EXPECT_TRUE(success);

    rover.GetCurrentPosition(x, y);

    EXPECT_EQ(1, x);
    EXPECT_EQ(5, y);

    EXPECT_EQ('N', rover.CurrentDirection());

    success = rover.MoveForward();

    EXPECT_FALSE(success);   // last move should have failed
}

// Move a west-facing rover forward
TEST(Rover, MoveForward_02)
{
    Plateau plateau(10, 5);

    EXPECT_EQ(0, plateau.RoverCount());

    Rover rover(1, 2, 'W', "LMLMLMLMM", plateau);

    int x, y;
    rover.GetCurrentPosition(x, y);

    EXPECT_EQ(1, x);
    EXPECT_EQ(2, y);

    rover.GetForwardPosition(x, y);

    EXPECT_EQ(0, x);
    EXPECT_EQ(2, y);

    EXPECT_EQ('W', rover.CurrentDirection());

    bool success = rover.MoveForward();

    EXPECT_TRUE(success);

    rover.GetCurrentPosition(x, y);

    EXPECT_EQ(0, x);
    EXPECT_EQ(2, y);

    EXPECT_EQ('W', rover.CurrentDirection());

    success = rover.MoveForward();

    EXPECT_FALSE(success);   // last move should have failed
}

// Move a south-facing rover forward
TEST(Rover, MoveForward_03)
{
    Plateau plateau(10, 5);

    EXPECT_EQ(0, plateau.RoverCount());

    Rover rover(1, 2, 'S', "LMLMLMLMM", plateau);

    int x, y;
    rover.GetCurrentPosition(x, y);

    EXPECT_EQ(1, x);
    EXPECT_EQ(2, y);

    rover.GetForwardPosition(x, y);

    EXPECT_EQ(1, x);
    EXPECT_EQ(1, y);

    EXPECT_EQ('S', rover.CurrentDirection());

    bool success = rover.MoveForward();

    EXPECT_TRUE(success);

    rover.GetCurrentPosition(x, y);

    EXPECT_EQ(1, x);
    EXPECT_EQ(1, y);

    EXPECT_EQ('S', rover.CurrentDirection());

    success = rover.MoveForward();

    EXPECT_TRUE(success);

    rover.GetCurrentPosition(x, y);

    EXPECT_EQ(1, x);
    EXPECT_EQ(0, y);

    EXPECT_EQ('S', rover.CurrentDirection());

    success = rover.MoveForward();

    EXPECT_FALSE(success);   // last move should have failed
}

// Move an east-facing rover forward
TEST(Rover, MoveForward_04)
{
    Plateau plateau(4, 5);

    EXPECT_EQ(0, plateau.RoverCount());

    Rover rover(1, 2, 'E', "LMLMLMLMM", plateau);

    int x, y;
    rover.GetCurrentPosition(x, y);

    EXPECT_EQ(1, x);
    EXPECT_EQ(2, y);

    rover.GetForwardPosition(x, y);

    EXPECT_EQ(2, x);
    EXPECT_EQ(2, y);

    EXPECT_EQ('E', rover.CurrentDirection());

    bool success = rover.MoveForward();

    EXPECT_TRUE(success);

    rover.GetCurrentPosition(x, y);

    EXPECT_EQ(2, x);
    EXPECT_EQ(2, y);

    EXPECT_EQ('E', rover.CurrentDirection());

    success = rover.MoveForward();

    EXPECT_TRUE(success);

    rover.GetCurrentPosition(x, y);

    EXPECT_EQ(3, x);
    EXPECT_EQ(2, y);

    EXPECT_EQ('E', rover.CurrentDirection());

    success = rover.MoveForward();

    EXPECT_TRUE(success);

    rover.GetCurrentPosition(x, y);

    EXPECT_EQ(4, x);
    EXPECT_EQ(2, y);

    EXPECT_EQ('E', rover.CurrentDirection());

    success = rover.MoveForward();

    EXPECT_FALSE(success);   // last move should have failed
}

// Move once from instructions
TEST(Rover, MoveOnce)
{
    Plateau plateau(5, 5);

    EXPECT_EQ(0, plateau.RoverCount());

    Rover rover(1, 2, 'N', "MLMLMLMM", plateau);

    int x, y;
    rover.GetCurrentPosition(x, y);

    EXPECT_EQ(1, x);
    EXPECT_EQ(2, y);

    EXPECT_EQ('N', rover.CurrentDirection());
    EXPECT_FALSE(rover.IsDoneMoving());

    bool success = rover.MoveOnce();

    EXPECT_TRUE(success);

    rover.GetCurrentPosition(x, y);

    EXPECT_EQ(1, x);
    EXPECT_EQ(3, y);

    EXPECT_EQ('N', rover.CurrentDirection());
    EXPECT_FALSE(rover.IsDoneMoving());
}

// Move through all instructions
TEST(Rover, Move)
{
    // Tests input case number 2 from the spec
    Plateau plateau(5, 5);

    EXPECT_EQ(0, plateau.RoverCount());

    Rover rover(3, 3, 'E', "MMRMMRMRRM", plateau);

    int x, y;
    rover.GetCurrentPosition(x, y);

    EXPECT_EQ(3, x);
    EXPECT_EQ(3, y);

    EXPECT_EQ('E', rover.CurrentDirection());
    EXPECT_FALSE(rover.IsDoneMoving());

    bool success = rover.Move();

    EXPECT_TRUE(success);

    rover.GetCurrentPosition(x, y);

    EXPECT_EQ(5, x);
    EXPECT_EQ(1, y);

    EXPECT_EQ('E', rover.CurrentDirection());
    EXPECT_TRUE(rover.IsDoneMoving());
    EXPECT_STREQ("5 1 E", rover.CurrentStatus().c_str());
}
