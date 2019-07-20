#include "board.h"

Board::Board(){
    int row=0,column=0;
    for(row=0;row<N;row++){
        for(column=0;column<N;column++){
            this->grid[row][column].setV(Vaxis(row));
            this->grid[row][column].setH(Haxis(column));
        }
    }
}

Square & Board::getSquare(Vaxis v, Haxis h){
    return this->grid[int(v)][int(h)];
}

Square & Board::getEmptySquare(Vaxis v, Haxis h){
    if(this->grid[int(v)][int(h)].isEmpty()){
        return this->grid[int(v)][int(h)];
    }else{
        SquareException err_1(this->grid[int(v)][int(h)],"not empty");
        throw err_1;
    }
}

Square & Board::getEmptySquare(const std::string &s){
    char row;
    int column;
    std::istringstream iStream;
    iStream.str(s);
    iStream >> row >> column;
    Vaxis v=D;
    bool valid_row=true;
    if(row=='A'){v=A;}
    else if(row=='B'){v=B;}
    else if(row=='C'){v=C;}
    else if(row=='D'){v=D;}
    else{valid_row=false;}
    if(valid_row && (column<=N) && (column>0)){
        return this->getEmptySquare(v,Haxis(column-1));
    }else{
        InvalidInputException err_3(s);
        throw err_3;
    }
}

void Board::place(Piece &p, Square &sq){
    this->grid[int(sq.getV())][int(sq.getH())].setPiece(&p);
}

static const Vaxis indexV(const short int ref,const Square &sq, const short int mode){ //get row index
    //REQUIRES: ref=1,2,3,4
    if(mode==3){ //check winning in row(3)
        return (sq.getV());
    }else{ //check winning in first diag(1), second diag(2), or column(4)
        return Vaxis(ref);
    }
}

static const Haxis indexH(const short int ref, const Square &sq, const short int mode){ //get column index
    //REQUIRES: ref=1,2,3,4
    if(mode==2){ //check winning in second diag(2)
        return Haxis(N-ref);
    }else if(mode==4){ //check winning in column(4)
        return (sq.getH());
    }else{ //check winning in first diag(1) or row(3)
        return Haxis(ref);
    }
}

static bool isWinning_helper(Board *const board, const Piece &p, const Square &sq, const short int mode){
    bool full=true; //every square except sq is occupied
    short int i=0; //reference number
    bool sameHeight=true, sameColor=true, sameShape=true, sameTop=true;
    for(i=0;i<N;i++){
        register Haxis h=indexH(i,sq,mode);
        register Vaxis v=indexV(i,sq,mode);
        if(h==(sq.getH()) && v==(sq.getV())){continue;} //ignore the same square
        else{
            if(board->getSquare(v,h).isEmpty()){full=false;break;}
            else{
                sameHeight=(sameHeight && (board->getSquare(v,h).getPiece().compareHeight(p)));
                sameColor=(sameColor && (board->getSquare(v,h).getPiece().compareColor(p)));
                sameShape=(sameShape && (board->getSquare(v,h).getPiece().compareShape(p)));
                sameTop=(sameTop && (board->getSquare(v,h).getPiece().compareTop(p)));
            }
        }
    }
    return (full && (sameHeight || sameColor || sameShape || sameTop));
}

bool Board::isWinning(const Piece &p, const Square &sq){
    //check the first diagonal (mode 1)
    bool win_1;
    if(sq.isOnFirstDiagonal()){
        win_1=isWinning_helper(this,p,sq,1);
    }else{win_1=false;}
    //check the second diagonal (mode 2)
    bool win_2;
    if(sq.isOnSecondDiagonal()){
        win_2=isWinning_helper(this,p,sq,2);
    }else{win_2=false;}
    //check the row (mode 3)
    bool win_3=isWinning_helper(this,p,sq,3);
    //check the column (mode 4)
    bool win_4=isWinning_helper(this,p,sq,4);
    //combine the result
    return (win_1 || win_2 || win_3 || win_4);
}

std::string Board::toString() const{
    std::string hd="    1    2    3    4\n"; // header line
    std::string sp="  +----+----+----+----+\n"; // seperator line
    std::string ln[2*N]; //body lines
    char rowMark[N]={'a','b','c','d'};
    int row,column;
    for(row=0;row<N;row++){
        std::ostringstream oStream_l1;
        std::ostringstream oStream_l2;
        oStream_l1 << rowMark[row] << " |";
        oStream_l2 << "  |";
        for(column=0;column<N;column++){
            if(this->grid[row][column].isEmpty()){ //for an empty square
                oStream_l1 << "    |";
                oStream_l2 << "    |";
            }else{ //for an occupied square
                oStream_l1 << " " << (this->grid[row][column].getPiece().toString()).substr(0,2) << " |";
                oStream_l2 << " " << (this->grid[row][column].getPiece().toString()).substr(2) << " |";
            }
        }
        ln[2*row]=(oStream_l1.str())+"\n";
        ln[2*row+1]=(oStream_l2.str())+"\n";
    }
    return (hd+sp+ln[0]+ln[1]+sp+ln[2]+ln[3]+sp+ln[4]+ln[5]+sp+ln[6]+ln[7]+sp);
}

