#include <iostream>
#include <cstdlib>
#include "player.h"

//
//Human Player
//

class HumanPlayer final : public Player{
public:
    HumanPlayer(Board *board, Pool *pool);
    Piece & selectPiece() override;
    Square & selectSquare(const Piece &p) override;
};

HumanPlayer::HumanPlayer(Board *board, Pool *pool):Player(board,pool){}

Piece & HumanPlayer::selectPiece(){
    bool finished=false;
    Piece *temp;
    while(!finished){
        std::cout<<"Enter a piece:";
        std::string pieceName;
        std::cin>>pieceName;
        finished=true;
        try{
            temp=&(pool->getUnusedPiece(pieceName));
            break;
        }catch(std::exception &err){
            std::string errMSG=err.what();
            std::cout<<errMSG<<std::endl;
            finished=false;
            continue;
        }
    }
    temp->setUsed(true);
    return *temp;
}

Square & HumanPlayer::selectSquare(const Piece &p){
    bool finished=false;
    Square *temp;
    while(!finished){
        std::cout<<"Enter a position:";
        std::string squareName;
        std::cin>>squareName;
        finished=true;
        try{temp=&(board->getEmptySquare(squareName));}
        catch(std::exception &err){
            std::string errMSG=err.what();
            std::cout<<errMSG<<std::endl;
            finished=false;
            continue;
        }
    }
    return *temp;
}

//
//Computer Player
//

class MyopicPlayer final : public Player{
public:
    MyopicPlayer(Board *board, Pool *pool);
    Piece & selectPiece() override;
    Square & selectSquare(const Piece &p) override;
};

MyopicPlayer::MyopicPlayer(Board *board, Pool *pool):Player(board,pool){}

Piece & MyopicPlayer::selectPiece(){
    //REQUIRES: pool not empty
    //trasverse to get all unused (and potentially not-bad) pieces
    int i=0;
    int unusedNum=NP;
    int notbadNum=NP;
    Piece *pcs_unused[NP];
    Piece *pcs_notbad[NP];
    for(i=0;i<NP;i++){ //pieces encoded from 0000 to 1111
        bool notbad=true;
        try{
            pcs_unused[i+unusedNum-NP]=&(pool->getUnusedPiece(Height(i/8),Color((i/4)%2),Shape((i/2)%2),Top(i%2)));
            //judge goodness of a piece
            int j=0;
            for(j=0;j<NP;j++){
                try{
                    if(board->isWinning(*(pcs_unused[i+unusedNum-NP]),board->getEmptySquare(Vaxis(j/4),Haxis(j%4)))){ //the opponent is going to win, bad
                        notbad=false;
                        notbadNum--;
                        break;
                    }
                }catch(...){continue;}
            }
        }catch(...){unusedNum--;notbadNum--;continue;}
        if(notbad){pcs_notbad[i+notbadNum-NP]=pcs_unused[i+unusedNum-NP];}
    }
    if(notbadNum==0){//all are bad choice, random select one
        int index=rand()%unusedNum;
        pcs_unused[index]->setUsed(true);
        return *(pcs_unused[index]);
    }else{//still some not bad
        int index=rand()%notbadNum;
        pcs_notbad[index]->setUsed(true);
        return *(pcs_notbad[index]);
    }
}

Square & MyopicPlayer::selectSquare(const Piece &p){
    int row=0, column=0;
    bool foundGoodSquare=false;
    Square *emptySquares[NP];
    int emptyNum=NP;
    Square *result;
    for(row=0;row<N;row++){
        for(column=0;column<N;column++){
            try{ //assume the square to be empty
                if(board->isWinning(p,board->getEmptySquare(Vaxis(row),Haxis(column)))){ //hiself/herself is going to win, good
                    foundGoodSquare=true;
                    result=&(board->getEmptySquare(Vaxis(row),Haxis(column)));
                }
                emptySquares[N*row+column+emptyNum-NP]=&(board->getEmptySquare(Vaxis(row),Haxis(column)));
            }catch(...){emptyNum--;continue;}
            if(foundGoodSquare){break;}
        }
        if(foundGoodSquare){break;}
    }
    if(!foundGoodSquare){ //in this case, we have to randomly select one
        result=emptySquares[rand()%emptyNum];
    }
    return *result;
}

//
//get Player
//

Player *getHumanPlayer(Board *b, Pool *p){
    static HumanPlayer player(b,p);
    return &player;
}

Player *getMyopicPlayer(Board *b, Pool *p, unsigned int s){
    srand(s);
    static MyopicPlayer player(b,p);
    return &player;
}
