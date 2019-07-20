//
//VE280 Project 4 - Version 2.6 - Fenglei Gu - 19 July 2019
//

#include <ctime>
#include <cstdlib>
#include <iostream>
#include "player.h"

void operation(const std::string &first, const std::string &second, unsigned int seed);
void turn(Board &nowBoard, Pool &nowPool, Player *player_1, Player *player_2, bool altern);

int main(int argc, char* argv[]){
    try{
        if(argc!=3 && argc!=4){ //invalid number of input entries
            std::string inputs;
            auto i=0;
            for(i=0;i<argc;i++){
                std::string temp=argv[i];
                inputs.append(temp);
                if(i!=argc-1){inputs.append(" ");}
            }
            InvalidInputException err_3(inputs);
            throw err_3;
        }else{ //valid number of input entries
            auto seed=(unsigned int)time(nullptr);
            std::string firstPlayer=argv[1], secondPlayer=argv[2];
            if(firstPlayer!="h" && firstPlayer!="m"){InvalidInputException err_3(firstPlayer); throw err_3;}
            if(secondPlayer!="h" && secondPlayer!="m"){InvalidInputException err_3(secondPlayer); throw err_3;}
            if(argc==4){seed=(unsigned int)atoi(argv[3]);}
            //start operation
            operation(firstPlayer,secondPlayer,seed);
        }
    }catch(std::exception &err){
        std::string errMSG=err.what();
        std::cout<<errMSG<<std::endl;
    }
    return 0;
}

void operation(const std::string &first, const std::string &second, unsigned int seed){
    //initialization
    Board boardToday;
    Pool poolToday;
    Player *player_1, *player_2;
    if(first=="h"){player_1=getHumanPlayer(&boardToday,&poolToday);}
    else{player_1=getMyopicPlayer(&boardToday,&poolToday,seed);}
    if(second=="h"){player_2=getHumanPlayer(&boardToday,&poolToday);}
    else{player_2=getMyopicPlayer(&boardToday,&poolToday,seed);}
    //turns start!
    turn(boardToday,poolToday,player_1,player_2,true);
}

void turn(Board &nowBoard, Pool &nowPool, Player *player_1, Player *player_2, bool altern){
    std::cout<< nowBoard.toString() <<std::endl;
    std::cout<< nowPool.toString() <<std::endl;
    std::cout<< "\nPlayer " << ((altern)?1:2) << "'s turn to select a piece:" <<std::endl;
    Piece & pc=player_1->selectPiece();
    std::cout<< pc.toString() << " selected." <<std::endl;
    std::cout<< "\nPlayer " << ((altern)?2:1) << "'s turn to select a square:" <<std::endl;
    Square & sq=player_2->selectSquare(pc);
    std::cout<< sq.toString() << " selected." <<std::endl;
    nowBoard.place(pc,sq);
    std::cout<<std::endl;

    if(nowBoard.isWinning(pc,sq)){ //someone has won
        std::cout<< nowBoard.toString() <<std::endl;
        std::cout<< nowPool.toString() <<std::endl;
        std::cout<< "\nPlayer " << ((altern)?2:1) << " has won!"<<std::endl;
        return;
    }else if((nowPool.toString()).empty()){ //all the pieces are used
        std::cout<< nowBoard.toString() <<std::endl;
        std::cout<< nowPool.toString() <<std::endl;
        std::cout<< "\nIt is a draw." <<std::endl;
        return;
    }else{ //continue a new turn
        turn(nowBoard,nowPool,player_2,player_1,!altern);
    }
}

