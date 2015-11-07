// robot.cpp
//
// Author: Michael Lounsbery
// Date: Nov 6, 2015

#include "robot.h"

using std::ceil;
using std::cerr;
using std::endl;
using std::ostream;
using std::string;
using std::stringstream;
using std::vector;

using Mars::Plateau;
using Mars::Rover;


// ctor for a plateau from [0..maxWidth] to [0..maxHeight]
Plateau::Plateau(size_t maxWidth, size_t maxHeight)
    : maxWidth_(maxWidth),
      maxHeight_(maxHeight)
{
    Initialize();
}


// Sets up the map for this plateau.
void Plateau::Initialize()
{
    for (size_t i = 0; i <= MaxHeight(); ++i)
    {
        string plateauLine = "";
        for (size_t j = 0; j <= MaxWidth(); ++j)
        {
            plateauLine += ".";
        }
        map_.push_back(plateauLine);
    }
}


// Returns the mark at position (x,y) on the plateau
char Plateau::GetMark(size_t x, size_t y)
{
    return map_[y][x];
}


// Sets position (x,y) on the plateau to mark
void Plateau::SetMark(size_t x, size_t y, char mark)
{
    map_[y][x] = mark;
}


// Outputs the plateau to os
void Plateau::Output(ostream & os)
{
    for (size_t i = 0; i <= MaxHeight(); ++i)
    {
        os << map_[i] << endl;
    }    
}


