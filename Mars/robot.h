// robot.h
//
// Author: Michael Lounsbery
// Date: Nov 6, 2015

#include "basics.h"

namespace Mars
{

class Rover;

class Plateau
{
public:
    Plateau(size_t width, size_t height);

    void Initialize();                              // Initialize the plateau and its map

    char GetMark(size_t x, size_t y);               // returns the mark at position (x, y)
    void SetMark(size_t x, size_t y, char mark);    // mark the plateau map at (x, y) with the given mark
    void Output(std::ostream & os);                 // Output the plateau map to os

    size_t MaxWidth() const { return maxWidth_; }
    size_t MaxHeight() const { return maxHeight_; }

    bool AddRover(Rover * newRover);                // Add a new rover to the list of rovers, return success
    bool MoveRovers();                              // moves the rovers and returns success
    size_t RoverCount() const { return roverVector_.size(); }

    // Returns true iff (x,y) is a legal position on this plateau for rover
    bool IsValidPosition(Rover * rover, size_t x, size_t y) const;

protected:
    size_t maxWidth_;                               // max plateau width
    size_t maxHeight_;                              // max plateau height

    std::vector<Rover *> roverVector_;              // list of rovers
    std::vector<std::string> map_;                  // map of where rovers are and have been. For fun and debugging.
};


class Rover
{
public:
    Rover(size_t x, size_t y, const std::string & instructions);

    enum Direction { kNorth, kEast, kSouth, kWest };// Possible movement directions

    bool MoveOnce();                                // Take one movement step, return success
    bool IsDoneMoving() const;                      // Returns true iff this rover is done moving
    bool Move();                                    // Move through all the remaining instructions, return success

    size_t CurrentInstructionIndex() const { return currentInstructionIndex_; }
    char InstructionAt(size_t index) const { return instructions_[index]; }
    size_t InstructionCount() const { return instructions_.size(); }

    void CurrentPosition(size_t & x, size_t & y);   // Returns (x,y) position of this rover
    void NextPosition(size_t & x, size_t & y);      // Returns position of this rover if it should move one step

    Direction CurrentDirection() const { return direction_; }
    void TurnLeft();                                // Turns the rover 90 degrees counter-clockwise
    void TurnRight();                               // Turns the rover 90 degrees clockwise

protected:
    Direction direction_;                           // current direction this rover is facing
            
    size_t x_;                                      // current x position
    size_t y_;                                      // current y position

    std::string instructions_;                      // list of instructions for this rover to execute
    size_t currentInstructionIndex_;                // which instruction we're on right now
};

}
