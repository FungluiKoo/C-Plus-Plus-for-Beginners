#include "simulation.h"

void MyException::addINFO(string newINFO){
    *(errINFO+infoID)=newINFO;
    infoID++;
}

void MyException::setID(short int newID){
    errID=newID;
}

void MyException::printMSG(){
    switch(errID){
        case 3:
            cout<<errMSG[3]<<*errINFO<<"!"<<endl;
            break;
        case 4:
            cout<<errMSG[4]<<MAXSPECIES<<"."<<endl;
            break;
        case 5:
            cout<<errMSG[5]<<*errINFO<<"!\nMaximal number of instructions is "<<MAXPROGRAM<<"."<<endl;
            break;
        case 6:
            cout<<errMSG[6]<<*errINFO<<" is not recognized!"<<endl;
            break;
        case 7:
            cout<<errMSG[7]<<MAXCREATURES<<"."<<endl;
            break;
        case 8:
            cout<<errMSG[8]<<*errINFO<<" not found!"<<endl;
            break;
        case 9:
            cout<<errMSG[9]<<*errINFO<<" is not recognized!"<<endl;
            break;
        case 12:
            cout<<errMSG[12]<<*errINFO<<" "
                            <<*(errINFO+1)<<" "
                            <<*(errINFO+2)<<" "
                            <<*(errINFO+3)<<") is out of bound!\nThe grid size is "
                            <<*(errINFO+4)<<"-by-"
                            <<*(errINFO+5)<<"."<<endl;
            break;
        case 13:
            cout<<errMSG[13]<<*errINFO<<" "
                            <<*(errINFO+1)<<" "
                            <<*(errINFO+2)<<" "
                            <<*(errINFO+3)<<") overlaps with creature ("
                            <<*(errINFO+4)<<" "
                            <<*(errINFO+5)<<" "
                            <<*(errINFO+6)<<" "
                            <<*(errINFO+7)<<")!"<<endl;
            break;
        default:
            cout<<errMSG[errID]<<endl;
    }
}

void Summary::setDir(string newDir){
    directory=newDir;
}

void Summary::addName(string newName){
    if(speciesSize>=MAXSPECIES){
        MyException err_4;
        err_4.setID(4);
        throw err_4;
    }else{
        speciesNames[speciesSize]=newName;
        speciesSize++;
    }
}

bool Summary::queryName(string theName) const{
    bool flag=false;
    unsigned int i=0;
    for(i=0;i<speciesSize;i++){
        if(speciesNames[i]==theName){flag=true; break;}
    }
    return flag;
}

unsigned int Summary::querySize() const{
    return speciesSize;
}

string Summary::getName(unsigned int index) const{
    return speciesNames[index];
}

string Summary::getFileAdd(unsigned int index) const{
    ostringstream output;
    output<<directory;
    output<<"/"<<speciesNames[index];
    string result=output.str();
    return result;
}

void checkArgument(int argc){
    if(argc<4){
        MyException err_1;
        err_1.setID(1);
        throw err_1;
    }
}

Summary readSpeciesSummary(const char* fileName){
    Summary newSummary;
    ifstream iSpecies;
    string info=fileName;
    //try to open the species summary file
    iSpecies.open(info);
    if(!iSpecies){
        MyException err_3;
        err_3.setID(3);
        err_3.addINFO(info);
        throw err_3;
    }
    //read the first line (directory address)
    string str;
    getline(iSpecies,str);
    newSummary.setDir(str);
    //add the names of species into the summary
    while(getline(iSpecies,str)){
        if(!str.empty()){newSummary.addName(str);}
    }
    iSpecies.close();
    return newSummary;
}

opcode_t str2Op(string str){
    if(str==opName[HOP]){return HOP;}
    else if(str==opName[LEFT]){return LEFT;}
    else if(str==opName[RIGHT]){return RIGHT;}
    else if(str==opName[INFECT]){return INFECT;}
    else if(str==opName[IFEMPTY]){return IFEMPTY;}
    else if(str==opName[IFWALL]){return IFWALL;}
    else if(str==opName[IFSAME]){return IFSAME;}
    else if(str==opName[IFENEMY]){return IFENEMY;}
    else if(str==opName[GO]){return GO;}
    else{ //check the validity of the string name
        MyException err_6;
        err_6.setID(6);
        err_6.addINFO(str);
        throw err_6;
    }
}

void readSpeciesProgram(const Summary newSummary, world_t &newWorld){
    unsigned int i=0;
    for(i=0;i<newSummary.querySize();i++){
        ifstream iFile;
        //try to open the species program file
        string fileAddress=newSummary.getFileAdd(i);
        iFile.open(fileAddress);
        if(!iFile){
            MyException err_3;
            err_3.setID(3);
            err_3.addINFO(fileAddress);
            throw err_3;
        }
        //initialize the species
        newWorld.numSpecies++; //set the number of species in total
        newWorld.species[i].name=newSummary.getName(i); //set the name
        unsigned int size=0; //set the number (progarmID) of instructions
        //read the instructions
        string line;
        while(getline(iFile,line)){
            if(!line.empty()){
                if(size>=MAXPROGRAM){ //check the number of instructions
                    MyException err_5;
                    err_5.setID(5);
                    err_5.addINFO(newSummary.getName(i));
                    throw err_5;
                }
                istringstream iSStream;
                iSStream.str(line);
                string instructionName;
                iSStream>>instructionName;
                opcode_t opCode=str2Op(instructionName);
                newWorld.species[i].program[size].op=opCode;
                if(opCode>3){
                    unsigned int addr;
                    iSStream>>addr;
                    newWorld.species[i].program[size].address=addr-1;
                }
                size++;
            }else{break;} //empty line indicated the descend of addtional (useless) comment
        }
        //finalize the size of species program (instruction)
        newWorld.species[i].programSize=size;
        iFile.close();
    }
}

int locateSpecies(string name, world_t thisWorld){
    int index=-1, i;
    for(i=0;i<(int)thisWorld.numSpecies;i++){
        if((name.compare(thisWorld.species[i].name))==0){index=i;break;}
    }
    return index;
}

direction_t str2Dir(string str){
    if(str==directName[EAST]){return EAST;}
    else if(str==directName[SOUTH]){return SOUTH;}
    else if(str==directName[WEST]){return WEST;}
    else if(str==directName[NORTH]){return NORTH;}
    else{ //check the validity of the string direction
        MyException err_9;
        err_9.setID(9);
        err_9.addINFO(str);
        throw err_9;
    }
}

void readWorldFile(const char* fileName, world_t &newWorld){
    ifstream iWorld;
    string info=fileName;
    //try to open the world file
    iWorld.open(info);
    if(!iWorld){
        MyException err_3;
        err_3.setID(3);
        err_3.addINFO(info);
        throw err_3;
    }
    //set the gird
    string line;
    getline(iWorld,line);
    int size=stoi(line);
    if(size<1 || (unsigned int)size>MAXHEIGHT){ //check whether height is valid
        MyException err_10;
        err_10.setID(10);
        throw err_10;
    }else{newWorld.grid.height=(unsigned int)size;}
    getline(iWorld,line);
    size=stoi(line);
    if(size<1 || (unsigned int)size>MAXWIDTH){ //check whether width is valid
        MyException err_11;
        err_11.setID(11);
        throw err_11;
    }else{newWorld.grid.width=(unsigned int)size;}
    //set the creatures
    unsigned int order=0;
    while(getline(iWorld,line)){
        if(!line.empty()){
            if(order>=MAXCREATURES){//check whether too many creatures
                MyException err_7;
                err_7.setID(7);
                throw err_7;
            }
            string name, dir;
            int row, column;
            istringstream iSStream;
            iSStream.str(line);
            iSStream>>name>>dir>>row>>column;
            int arrayIndex=locateSpecies(name,newWorld);
            if(arrayIndex<0){ //check whether is unkown species
                MyException err_8;
                err_8.setID(8);
                err_8.addINFO(name);
                throw err_8;
            }else{ //set the type of species of the creature
                newWorld.creatures[order].species=&(newWorld.species[arrayIndex]);
            }
            //set the direction of the creature
            newWorld.creatures[order].direction=str2Dir(dir);
            //check whether out of bound
            if(row <0 || row>=(int)newWorld.grid.height || column<0 || column>=(int)newWorld.grid.width){
                MyException err_12;
                err_12.setID(12);
                err_12.addINFO(name);
                err_12.addINFO(dir);
                err_12.addINFO(to_string(row));
                err_12.addINFO(to_string(column));
                err_12.addINFO(to_string(newWorld.grid.height));
                err_12.addINFO(to_string(newWorld.grid.width));
                throw err_12;
            }else{//set the location on gird of the creature
                newWorld.creatures[order].location.r=row;
                newWorld.creatures[order].location.c=column;
                if(newWorld.grid.squares[row][column]!=nullptr){ //check overlap
                    MyException err_13;
                    err_13.setID(13);
                    err_13.addINFO(name);
                    err_13.addINFO(dir);
                    err_13.addINFO(to_string(row));
                    err_13.addINFO(to_string(column));
                    err_13.addINFO(newWorld.grid.squares[row][column]->species->name);
                    err_13.addINFO(directName[newWorld.grid.squares[row][column]->direction]);
                    err_13.addINFO(to_string(newWorld.grid.squares[row][column]->location.r));
                    err_13.addINFO(to_string(newWorld.grid.squares[row][column]->location.c));
                    throw err_13;
                }else{newWorld.grid.squares[row][column]=&(newWorld.creatures[order]);}
            }
            //initialize the programID (instruction to be executed)
            newWorld.creatures[order].programID=0;
            order++;
        }
    }
    newWorld.numCreatures=order;
    iWorld.close();
}

void runWorld(const char* roundArgument, bool isVerbose, world_t &thisWorld){
    //check the validity of rounds
    int round=atoi(roundArgument);
    if(round<0){
        MyException err_2;
        err_2.setID(2);
        throw err_2;
    }
    //print initial state
    cout<<"Initial state"<<endl;
    printGird(thisWorld);
    //run
    int i=0;
    for(i=1;i<=round;i++){
        cout<<"Round "<<i<<endl;
        unsigned int order=0; //the order of creatures taking turns
        for(order=0;order<thisWorld.numCreatures;order++){
            //announcement
            cout<<"Creature ("<<thisWorld.creatures[order].species->name<<" "<<directName[thisWorld.creatures[order].direction]<<" "<<(thisWorld.creatures[order].location.r)<<" "<<(thisWorld.creatures[order].location.c)<<") takes action:";
            //Processing
            if(isVerbose){ //run in verbose mode
                runVerboseWorld(order,thisWorld);
                printGird(thisWorld);
            }else{ //run in concise mode
                runConciseWorld(order,thisWorld);
            }
        }
        if(!isVerbose){printGird(thisWorld);}
    }
}

bool isWall(const unsigned int order, const world_t &nowWorld){
    direction_t dir=nowWorld.creatures[order].direction;
    unsigned int row=nowWorld.creatures[order].location.r;
    unsigned int column=nowWorld.creatures[order].location.c;    
    if(dir==EAST){return ((column+1)==nowWorld.grid.width);}
    else if(dir==SOUTH){return ((row+1)==nowWorld.grid.height);}
    else if(dir==WEST){return (column==0);}
    else{return (row==0);}
}

bool isEmpty(const unsigned int order, const world_t &nowWorld){
    //REQUIRES: isWall==false

    direction_t dir=nowWorld.creatures[order].direction;
    unsigned int row=nowWorld.creatures[order].location.r;
    unsigned int column=nowWorld.creatures[order].location.c;    
    if(dir==EAST){return (nowWorld.grid.squares[row][column+1]==nullptr);}
    else if(dir==SOUTH){return (nowWorld.grid.squares[row+1][column]==nullptr);}
    else if(dir==WEST){return (nowWorld.grid.squares[row][column-1]==nullptr);}
    else{return (nowWorld.grid.squares[row-1][column]==nullptr);}
}

bool isSame(const unsigned int order, const world_t &nowWorld){
    //REQUIRES: isWall==false && isEmpty==false

    direction_t dir=nowWorld.creatures[order].direction;
    unsigned int row=nowWorld.creatures[order].location.r;
    unsigned int column=nowWorld.creatures[order].location.c;
    species_t* homo=nowWorld.creatures[order].species;
    if(dir==EAST){return (homo==(nowWorld.grid.squares[row][column+1]->species));}
    else if(dir==SOUTH){return (homo==(nowWorld.grid.squares[row+1][column]->species));}
    else if(dir==WEST){return (homo==(nowWorld.grid.squares[row][column-1]->species));}
    else{return (homo==(nowWorld.grid.squares[row-1][column]->species));}
}

bool isEnemy(const unsigned int order, const world_t &nowWorld){
    //REQUIRES: isWall==false && isEmpty==false

    return (!isSame(order,nowWorld));
}

void moveForward(const unsigned int order, world_t &nowWorld){
    //REQUIRES: isWall==false && isEmpty==true

    direction_t dir=nowWorld.creatures[order].direction;
    unsigned int row=nowWorld.creatures[order].location.r;
    unsigned int column=nowWorld.creatures[order].location.c;
    if(dir==EAST){
        (nowWorld.creatures[order].location.c)++;
        nowWorld.grid.squares[row][column+1]=&(nowWorld.creatures[order]);
    }else if(dir==SOUTH){
        (nowWorld.creatures[order].location.r)++;
        nowWorld.grid.squares[row+1][column]=&(nowWorld.creatures[order]);
    }else if(dir==WEST){
        (nowWorld.creatures[order].location.c)--;
        nowWorld.grid.squares[row][column-1]=&(nowWorld.creatures[order]);
    }else{
        (nowWorld.creatures[order].location.r)--;
        nowWorld.grid.squares[row-1][column]=&(nowWorld.creatures[order]);
    }
    nowWorld.grid.squares[row][column]=nullptr;
}

void turnLeft(const unsigned int order, world_t &nowWorld){
    direction_t dir=nowWorld.creatures[order].direction;
    if(dir==EAST){nowWorld.creatures[order].direction=NORTH;}
    else if(dir==SOUTH){nowWorld.creatures[order].direction=EAST;}
    else if(dir==WEST){nowWorld.creatures[order].direction=SOUTH;}
    else{nowWorld.creatures[order].direction=WEST;}
}

void turnRight(const unsigned int order, world_t &nowWorld){
    direction_t dir=nowWorld.creatures[order].direction;
    if(dir==EAST){nowWorld.creatures[order].direction=SOUTH;}
    else if(dir==SOUTH){nowWorld.creatures[order].direction=WEST;}
    else if(dir==WEST){nowWorld.creatures[order].direction=NORTH;}
    else{nowWorld.creatures[order].direction=EAST;}
}

void infectObject(const unsigned int order, world_t &nowWorld){
    //REQUIRES: isWall==false && isEmpty==false && isEnemy==true

    direction_t dir=nowWorld.creatures[order].direction;
    unsigned int row=nowWorld.creatures[order].location.r;
    unsigned int column=nowWorld.creatures[order].location.c;
    species_t* virus=nowWorld.creatures[order].species;
    if(dir==EAST){
        (nowWorld.grid.squares[row][column+1]->programID)=0;
        (nowWorld.grid.squares[row][column+1]->species)=virus;
    }else if(dir==SOUTH){
        (nowWorld.grid.squares[row+1][column]->programID)=0;
        (nowWorld.grid.squares[row+1][column]->species)=virus;
    }else if(dir==WEST){
        (nowWorld.grid.squares[row][column-1]->programID)=0;
        (nowWorld.grid.squares[row][column-1]->species)=virus;
    }else{
        (nowWorld.grid.squares[row-1][column]->programID)=0;
        (nowWorld.grid.squares[row-1][column]->species)=virus;
    }
}

void backgroundProcess(const unsigned int order, opcode_t op, const unsigned int programID, const unsigned int newID, world_t &thisWorld){
    if(op==HOP){
        if((!isWall(order,thisWorld))&&isEmpty(order,thisWorld)){moveForward(order,thisWorld);}
        (thisWorld.creatures[order].programID)++;
    }else if(op==LEFT){turnLeft(order,thisWorld); (thisWorld.creatures[order].programID)++;}
    else if(op==RIGHT){turnRight(order,thisWorld); (thisWorld.creatures[order].programID)++;}
    else if(op==INFECT){
        if((!isWall(order,thisWorld))&&(!isEmpty(order,thisWorld))&&(isEnemy(order,thisWorld))){infectObject(order,thisWorld);}
        (thisWorld.creatures[order].programID)++;
    }else if(op==IFEMPTY){
        (thisWorld.creatures[order].programID)=((!isWall(order,thisWorld))&&isEmpty(order,thisWorld))?newID:(programID+1);
    }else if(op==IFWALL){
        (thisWorld.creatures[order].programID)=(isWall(order,thisWorld))?newID:(programID+1);
    }else if(op==IFSAME){
        (thisWorld.creatures[order].programID)=((!isWall(order,thisWorld))&&(!isEmpty(order,thisWorld))&&isSame(order,thisWorld))?newID:(programID+1);
    }else if(op==IFENEMY){
        (thisWorld.creatures[order].programID)=((!isWall(order,thisWorld))&&(!isEmpty(order,thisWorld))&&isEnemy(order,thisWorld))?newID:(programID+1);
    }else if(op==GO){
        (thisWorld.creatures[order].programID)=newID;
    }
}

void runVerboseWorld(const unsigned int order, world_t &thisWorld){
    cout<<endl;
    bool flag=true;
    while(flag){ //turn ("Hui He") not ended
        unsigned int programID=thisWorld.creatures[order].programID;
        unsigned int newID=0;
        opcode_t op=thisWorld.creatures[order].species->program[programID].op;
        cout<<"Instruction "<<(programID+1)<<": "<<opName[op];
        flag=(op>3);
        if(flag){
            newID=thisWorld.creatures[order].species->program[programID].address;
            cout<<" "<<(newID+1);
        }
        cout<<endl;
        //backgroung operations
        backgroundProcess(order,op,programID,newID,thisWorld);
        if(flag==false){break;}
    }
}

void runConciseWorld(const unsigned int order, world_t &thisWorld){
    bool flag=true;
    while(flag){ //turn ("Hui He") not ended
        unsigned int programID=thisWorld.creatures[order].programID;
        unsigned int newID=0;
        opcode_t op=thisWorld.creatures[order].species->program[programID].op;
        flag=(op>3);
        if(flag){
            newID=thisWorld.creatures[order].species->program[programID].address;
        }else{
            cout<<" "<<opName[op]<<endl;
        }
        //backgroung operations
        backgroundProcess(order,op,programID,newID,thisWorld);
        if(flag==false){break;}
    }
}

void printGird(const world_t &nowWorld){
    unsigned int row=0, column=0;
    for(row=0;row<nowWorld.grid.height;row++){
        for(column=0;column<nowWorld.grid.width;column++){
            if(nowWorld.grid.squares[row][column]==nullptr){ //no creature living
                cout<<"____ ";
            }else{ //occupied by a creature
                string speciesName=nowWorld.grid.squares[row][column]->species->name;
                cout<<(speciesName.substr(0,2))<<"_";
                cout<<directShortName[nowWorld.grid.squares[row][column]->direction]<<" ";
            }
        }
        cout<<endl;
    }
}

