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

    Rover rover(1, 2, 'N', "LMLMLMLMM", plateau);

    int x, y;
    rover.GetCurrentPosition(x, y);

    EXPECT_EQ(1, x);
    EXPECT_EQ(2, y);
}
