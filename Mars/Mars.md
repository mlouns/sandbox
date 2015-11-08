# Mars Rovers

## Introduction

The code simulates one or more Mars rovers on a rectangular plateau.

## Classes

All classes and their interfaces are described in the `robot.h` file.

`Plateau`: models the plateau that rovers run around on.

`Rover`: models a rover.

## Unit tests

Test files are in the Mars/utest directory.

## How to use

### Input file

A single input file contains the description of the plateau and each rover.
The first line of the file gives the size of the plateau.
Following lines give descriptions of each rover: a line giving the initial (x,y) position on the plateau, and an intitial direction, and a line of instructions for the rover to follow.

**Interpretation of Instructions**:

`M` : Move forward one space on the plateau, in the direction the rover is currently facing.

`R` : Rotate the rover 90 degrees clockwise.

`L` : Rotate 90 degrees counter-clockwise.

#### Example input:

    5 5 
    1 2 N 
    LMLMLMLMM 
    3 3 E 
    MMRMMRMRRM 

This sets up a single plateau of size 5 by 5, and two rovers. The first rover begins at (1,2), facing North, and has the instruction sequence `LMLMLMLMM`. The second begins at (3,3) facing East, with instructions `MMRMMRMRRM`.

### Running from the input

The program reads directly from standard input.

#### Example run:

`% ./mars < input.txt`


### Output

After running, the program prints out the current status of all rovers, and a simple ASCII map that shows the tracks taken by each rover.

#### Example output:

For the above example input, the output is as follows:

    Status of all rovers:
    1 3 N
    5 1 E

    Map of the plateau:
    ......
    ......
    .1.>>V
    V^...V
    >^..>2
    ......
    
     
