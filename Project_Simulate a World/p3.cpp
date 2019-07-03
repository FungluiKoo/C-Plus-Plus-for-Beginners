//
//VE280 Project 3 - Version 2.1 - Fenglei Gu - 2 July 2019
//

#include "world_type.h"
#include "simulation.h"

int main(int argc, char* argv[]){
    //check the validity of the quantity of arguments
    try{checkArgument(argc);}
    catch(MyException &err){err.printMSG();exit(0);}
    //read the species summary file
    Summary todaySummary;
    try{todaySummary=readSpeciesSummary(argv[1]);}
    catch(MyException &err){err.printMSG();exit(0);}
    //construct species
    world_t todayWorld={};
    try{readSpeciesProgram(todaySummary,todayWorld);}
    catch(MyException &err){err.printMSG();exit(0);}
    //construct the rest of the world
    try{readWorldFile(argv[2],todayWorld);}
    catch(MyException &err){err.printMSG();exit(0);}
    //run the world
    bool isVerbose=false;
    if(argc>4){string temp=argv[4]; isVerbose=(temp=="v")||(temp=="verbose");}
    try{runWorld(argv[3],isVerbose,todayWorld);}
    catch(MyException &err){err.printMSG();exit(0);}
    
    return 0;
}

