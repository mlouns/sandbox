// main.cpp
//
// Author: Michael Lounsbery
// Date: Nov 4, 2015

#include "robot.h"

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::stringstream;

using Mars::Plateau;
using Mars::Rover;


namespace
{
// Splits s into tokens, where space is the delimiter.
void SplitIntoTokens(const string & s, StringVector & tokens)
{
    tokens.clear();
    string tempBuffer;
    stringstream stream(s);

    while (stream >> tempBuffer)
    {
        tokens.push_back(tempBuffer);
    }
}

// Reads from the file in fileName, sets up rovers on plateau.
bool ParseInput(const string & fileName, Plateau * & plateau)
{
    ifstream infile(fileName);

    string line;

    // Read in size of the plateau.
    std::getline(infile, line);

    StringVector roverTokens;
    SplitIntoTokens(line, roverTokens);

    bool success = roverTokens.size() == 2;

    if (!success)
    {
        return false;              // <== * return *
    }
    int x = std::stoi(roverTokens[0]);
    int y = std::stoi(roverTokens[1]);

    plateau = new Plateau(x, y);

    while (success && std::getline(infile, line))
    {
        SplitIntoTokens(line, roverTokens);

        success = roverTokens.size() == 3;
        if (success)
        {
            char direction = '\0';
            try
            {
                x = std::stoi(roverTokens[0]);
                y = std::stoi(roverTokens[1]);
                success = roverTokens[2].size() == 1;
                if (success)
                {
                    direction = roverTokens[2][0];
                }
            }
            catch (...)
            {
                cerr << "Failure 1" << endl;
                success = false;
            }
            if (success)
            {
                string instructions;
                std::getline(infile, instructions);

                plateau->AddRover(new Rover(x, y, direction, instructions, *plateau));
            }
        }
    }
    if (!success)
    {
        cerr << "Failure reading rovers" << endl;
    }
    return success;
}

} // anonymous namespace

int main()
{
    Plateau * plateau;

    bool success = ParseInput("input.txt", plateau);
    if (success)
    {
        plateau->MoveRovers();
        plateau->OutputRoverStatus(cout);
        plateau->OutputMap(cout);
    }
    return 0;
}
