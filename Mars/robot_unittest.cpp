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


// Simple test for initializing a Rover.
TEST(Rover, Init)
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
