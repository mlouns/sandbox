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
Plateau::Plateau(int maxWidth, int maxHeight)
    : maxWidth_(maxWidth),
      maxHeight_(maxHeight)
{
    Initialize();
}


// Sets up the map for this plateau.
void Plateau::Initialize()
{
    for (int i = 0; i <= MaxHeight(); ++i)
    {
        string plateauLine = "";
        for (int j = 0; j <= MaxWidth(); ++j)
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
    for (int i = 0; i <= MaxHeight(); ++i)
    {
        os << map_[i] << endl;
    }    
}


// Adds newRover to this plateau.
void Plateau::AddRover(Rover * newRover)
{
    roverVector_.push_back(newRover);
}


// Moves each rover, returns combined success
bool Plateau::MoveRovers()
{
    for (auto rover : roverVector_)
    {
        cerr << "Move rover" << endl;
        if (!rover->Move())
        {
            return false;           // <== * return *
        }
    }
    return true;
}


// Returns true iff (x,y) is a valid position on this plateau.
// It is valid iff (x,y) is on the plateau.
// We don't currently check for collision with other rovers, although we could do that with a little more info.
bool Plateau::IsValidPosition(int x, int y) const
{
    return (x >= 0) && (x <= MaxWidth()) && (y >= 0) && (y <= MaxHeight());
}


// ctor for rover starting at position (x,y) on plateau, with the given instructions.
Rover::Rover(int x, int y, char direction, const std::string & instructions, Plateau & plateau)
    : x_(x),
      y_(y),
      instructions_(instructions),
      currentInstructionIndex_(0),
      plateau_(plateau)
{
    cerr << "New rover: (" << x << ", " << y << "), dir=" << direction << ", instr=" << instructions << endl;

    switch (direction)
    {
    case 'N': direction = kNorth;
        break;
    case 'E': direction = kEast;
        break;
    case 'S': direction = kSouth;
        break;
    case 'W': direction = kWest;
        break;
    default:
        cerr << "Read unknown direction: '" << direction << "'" << endl;
    }
    plateau.AddRover(this);
}


// Move this rover according to its instructions.
bool Rover::Move()
{
    bool success = true;
    while (success && !IsDoneMoving())
    {
        success = MoveOnce();
    }
    return success;
}


// Move this rover the single next instruction.
bool Rover::MoveOnce()
{
    bool success = true;
    switch (CurrentInstruction())
    {
    case 'L':
        TurnLeft();
        break;
        
    case 'R':
        TurnRight();
        break;
        
    case 'M':
        success = MoveForward();
        break;

    default:
        success = false;
    }
    ++currentInstructionIndex_;
    return success;
}


// Return true iff this rover has finished moving.
bool Rover::IsDoneMoving() const
{
    return CurrentInstructionIndex() < instructions_.size();
}


// Turns the rover 90 degrees to the left.
void Rover::TurnLeft()
{
    cerr << "turn left" << endl;
    switch (CurrentDirection())
    {
        case kNorth:
            direction_ = kWest;
            break;

        case kEast:
            direction_ = kNorth; 
            break;

        case kSouth:
            direction_ = kEast;
            break;

        case kWest:
            direction_ = kSouth;
            break;
    }
}


// Turns the rover 90 degrees to the right.
void Rover::TurnRight()
{
    cerr << "turn right" << endl;
    switch (CurrentDirection())
    {
        case kNorth:
            direction_ = kEast;
            break;

        case kEast:
            direction_ = kSouth;
            break;

        case kSouth:
            direction_ = kWest;
            break;

        case kWest:
            direction_ = kNorth;
            break;
    }
}


// Tries to move the rover 1 step forward on the plateau.
// Returns success if we can do this legally.
bool Rover::MoveForward()
{
    cerr << "move forward" << endl;
    int x, y;
    GetCurrentPosition(x, y);
    GetPlateau().SetMark(x, y, Marker());
    GetForwardPosition(x, y);
    bool success = GetPlateau().IsValidPosition(x, y);
    if (success)
    {
        GetPlateau().SetMark(x, y, '*');
        x_ = x;
        y_ = y;
    }
    return success;
}


// Sets x and y to the next position if we move forward
void Rover::GetCurrentPosition(int & x, int & y)
{
    x = x_;
    y = y_;
}


// Sets x and y to the next position if we move forward
void Rover::GetForwardPosition(int & x, int & y)
{
    GetCurrentPosition(x, y);
    switch (CurrentDirection())
    {
        case kNorth:
            y += 1;
            break;

        case kEast:
            x += 1;
            break;

        case kSouth:
            y -= 1;
            break;

        case kWest:
            x -= 1;
            break;
    }
}


// Returns marker corresponding to the current direction
char Rover::Marker() const
{
    char result = '\0';
    switch (CurrentDirection())
    {
        case kNorth:
            result = '^';
            break;

        case kEast:
            result = '>';
            break;

        case kSouth:
            result = 'V';
            break;

        case kWest:
            result = '<';
            break;
    }
    return result;
}
