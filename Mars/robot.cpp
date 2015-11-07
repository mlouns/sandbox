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
char Plateau::GetMark(size_t x, size_t y) const
{
    return map_[y][x];
}


// Sets position (x,y) on the plateau to mark
void Plateau::SetMark(size_t x, size_t y, char mark)
{
    map_[y][x] = mark;
}


// Outputs status of all rovers to os
void Plateau::OutputRoverStatus(ostream & os) const
{
    os << endl << "Status of all rovers:" << endl;
    for (auto rover : roverVector_)
    {
        os << rover->CurrentStatus() << endl;
    }    
}


// Outputs a map of the plateau to os
void Plateau::OutputMap(ostream & os) const
{
    os << endl << "Map of the plateau:" << endl;
    for (int i = MaxHeight(); i >= 0; --i)
    {
        os << map_[i] << endl;
    }    
}


// Adds newRover to this plateau.
void Plateau::AddRover(Rover * newRover)
{
    roverVector_.push_back(newRover);
    newRover->SetId('0' + char(RoverCount()));
}


// Moves each rover, returns combined success
void Plateau::MoveRovers()
{
    for (auto rover : roverVector_)
    {
        rover->Move();
    }
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
      direction_(direction),
      instructions_(instructions),
      currentInstructionIndex_(0),
      plateau_(plateau)
{
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
    return CurrentInstructionIndex() >= instructions_.size();
}


// Turns the rover 90 degrees to the left.
void Rover::TurnLeft()
{
    switch (CurrentDirection())
    {
        case 'N':
            direction_ = 'W';
            break;

        case 'E':
            direction_ = 'N'; 
            break;

        case 'S':
            direction_ = 'E';
            break;

        case 'W':
            direction_ = 'S';
            break;
    }
}


// Turns the rover 90 degrees to the right.
void Rover::TurnRight()
{
    switch (CurrentDirection())
    {
        case 'N':
            direction_ = 'E';
            break;

        case 'E':
            direction_ = 'S';
            break;

        case 'S':
            direction_ = 'W';
            break;

        case 'W':
            direction_ = 'N';
            break;
    }
}


// Tries to move the rover 1 step forward on the plateau.
// Returns success if we can do this legally.
bool Rover::MoveForward()
{
    int x, y;
    GetCurrentPosition(x, y);
    GetPlateau().SetMark(x, y, Marker());
    GetForwardPosition(x, y);
    bool success = GetPlateau().IsValidPosition(x, y);
    if (success)
    {
        GetPlateau().SetMark(x, y, Id());
        x_ = x;
        y_ = y;
    }
    return success;
}


// Sets x and y to the next position if we move forward
void Rover::GetCurrentPosition(int & x, int & y) const
{
    x = x_;
    y = y_;
}


// Sets x and y to the next position if we move forward
void Rover::GetForwardPosition(int & x, int & y) const
{
    GetCurrentPosition(x, y);
    switch (CurrentDirection())
    {
        case 'N':
            y += 1;
            break;

        case 'E':
            x += 1;
            break;

        case 'S':
            y -= 1;
            break;

        case 'W':
            x -= 1;
            break;
    }
}


// Returns a succinct string indicating current rover status
string Rover::CurrentStatus() const
{
    stringstream result;
    result << x_ << " " << y_ << " " << CurrentDirection();
    return result.str();
}


// Returns marker corresponding to the current direction
char Rover::Marker() const
{
    char result = '\0';
    switch (CurrentDirection())
    {
        case 'N':
            result = '^';
            break;

        case 'E':
            result = '>';
            break;

        case 'S':
            result = 'V';
            break;

        case 'W':
            result = '<';
            break;
    }
    return result;
}
