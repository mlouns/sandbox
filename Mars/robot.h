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
    Plateau(int width, int height);

    void Initialize();                                // Initialize the plateau and its map

    char GetMark(size_t x, size_t y) const;           // returns the mark at position (x, y)
    void SetMark(size_t x, size_t y, char mark);      // mark the plateau map at (x, y) with the given mark
    void OutputRoverStatus(std::ostream & os) const;  // Output the status of all rovers to os
    void OutputMap(std::ostream & os) const;          // Output the plateau map to os

    int MaxWidth() const { return maxWidth_; }
    int MaxHeight() const { return maxHeight_; }

    void AddRover(Rover * newRover);                  // Add a new rover to the list of rovers, return success
    void MoveRovers();                                // moves all rovers
    size_t RoverCount() const { return roverVector_.size(); }

    // Returns true iff (x,y) is a legal position on this plateau for rover
    bool IsValidPosition(int x, int y) const;

protected:
    int maxWidth_;                                    // max plateau width
    int maxHeight_;                                   // max plateau height

    std::vector<Rover *> roverVector_;                // list of rovers
    std::vector<std::string> map_;                    // map of where rovers are and have been. For fun and debugging.
};


class Rover
{
public:
    Rover(int x, int y, char direction, const std::string & instructions, Plateau & plateau);

    bool Move();                                      // Move through all the remaining instructions, return success
    bool MoveOnce();                                  // Take one movement step, return success
    bool IsDoneMoving() const;                        // Returns true iff this rover is done moving

    char CurrentDirection() const { return direction_; }

    void TurnLeft();                                  // Turns the rover 90 degrees counter-clockwise
    void TurnRight();                                 // Turns the rover 90 degrees clockwise
    bool MoveForward();                               // Tries to move one step forward. Returns success.

    const std::string & Instructions() const { return instructions_; }
    size_t CurrentInstructionIndex() const { return currentInstructionIndex_; }
    char CurrentInstruction() const { return InstructionAt(CurrentInstructionIndex()); }
    char InstructionAt(size_t index) const { return instructions_[index]; }
    size_t InstructionCount() const { return instructions_.size(); }

    void GetCurrentPosition(int & x, int & y) const;  // Returns (x,y) position of this rover
    void GetForwardPosition(int & x, int & y) const;  // Returns position of this rover if it should move one step
    std::string CurrentStatus() const;                // Returns a string giving current position and direction
    char Marker() const;                              // ASCII marker for this rover's direction (debug only)

    char Id() const { return id_; }                   // id for this rover
    void SetId(char id) { id_ = id; }                 // sets rover id

    Plateau & GetPlateau() { return plateau_; }       // where this rover lives

protected:
    int x_;                                           // current x position
    int y_;                                           // current y position

    char direction_;                                  // current direction this rover is facing
            
    std::string instructions_;                        // list of instruction chars for this rover to execute
    size_t currentInstructionIndex_;                  // which instruction we're on right now

    int id_;                                          // id for this rover (debugging only)

    Plateau & plateau_;                               // The plateau this rover is moving on
};

}
