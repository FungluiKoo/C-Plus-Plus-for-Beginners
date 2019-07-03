#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "world_type.h"

class MyException{
    //OVERVIEW: A class used to throw error message
private:
    string errMSG[14]={"",
        "Error: Missing arguments!\nUsage: ./p3 <species-summary> <world-file> <rounds> [v|verbose]",
        "Error: Number of simulation rounds is negative!",
        "Error: Cannot open file ",
        "Error: Too many species!\nMaximal number of species is ",
        "Error: Too many instructions for species ",
        "Error: Instruction ",
        "Error: Too many creatures! Maximal number of creatures is ",
        "Error: Species ",
        "Error: Direction ",
        "Error: The grid height is illegal!",
        "Error: The grid width is illegal!",
        "Error: Creature (",
        "Error: Creature ("};
    string errINFO[8]; //(optional) stores additional info that should be replaced specifically
    short int infoID=0;
    short int errID=0; //the ID# is just the # on the project description
public:
    void addINFO(string newINFO); //set errINFO
    void setID(short int newID); //set errID
    void printMSG(); //print the error message
};

class Summary{
    //OVERVIEW: A class used to convey the species summary.
private:
    string directory; //stores the directory address (the first line of the species summary file)
    unsigned int speciesSize=0; //the number of species
    string speciesNames[MAXSPECIES]; //stores the names of species
public:
    void setDir(string newDir); //read-in the directory
    void addName(string newName); //read-in a new species' name
    bool queryName(string theName) const; //search whether a given species' name is in the Summary
    unsigned int querySize() const; //return the number of species in this summary
    string getName(unsigned int index) const; //get the #index of the species
    string getFileAdd(unsigned int index) const; //get the address of the species
};

void checkArgument(int argc); //check if the quantity of argument is enough

Summary readSpeciesSummary(const char* fileName); //read the species summary file

opcode_t str2Op(string str); //convert string to opcode

void readSpeciesProgram(const Summary newSummary, world_t &newWorld); //read the species program file

int locateSpecies(string name, world_t thisWorld); //locate the place of a species in the species array of thisWorld

direction_t str2Dir(string str); //convert string to direction

void readWorldFile(const char* fileName, world_t &newWorld); //read the world file

void runWorld(const char* roundArgument, bool isVerbose, world_t &thisWorld); //run the world

bool isWall(const unsigned int order, const world_t &nowWorld); //judge whether a creature is facing to a wall

bool isEmpty(const unsigned int order, const world_t &nowWorld); //judge whether a creature is facing to an empty grid

bool isSame(const unsigned int order, const world_t &nowWorld); //judge whether the creature in front is in same species

bool isEnemy(const unsigned int order, const world_t &nowWorld); //judge whether the creature in front is enemy species

void moveForward(const unsigned int order, world_t &nowWorld); //move the current creature forward

void turnLeft(const unsigned int order, world_t &nowWorld); //turn the creature left

void turnRight(const unsigned int order, world_t &nowWorld); //turn the creature right

void infectObject(const unsigned int order, world_t &nowWorld); //infect the in-front creature

void backgroundProcess(const unsigned int order, const opcode_t op, const unsigned int programID, const unsigned int newID, world_t &thisWorld); //adjust the world accordingly

void runVerboseWorld(const unsigned int order, world_t &thisWorld); //run in verbose mode

void runConciseWorld(const unsigned int order, world_t &thisWorld); //run in concise mode

void printGird(const world_t &nowWorld); //print the grids in the current round


#endif //SIMULATION_H