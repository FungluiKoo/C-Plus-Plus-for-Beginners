#include "pool.h"

Piece & Pool::getUnusedPiece(int index){
    if(this->pieces[index].isUsed()){
        UsedPieceException err_2(this->pieces[index]);
        throw err_2;
    }else{
        return this->pieces[index];
    }
}

Pool::Pool(){ //constructor is responsible for initialization
    int i=0;
    for(i=0;i<NP;i++){ //encode from 0000 to 1111
        Piece temp(Height(i/8),Color((i/4)%2),Shape((i/2)%2),Top(i%2));
        this->pieces[i]=temp;
    }
}

Piece & Pool::getUnusedPiece(Height h, Color c, Shape s, Top t){
    short int index=h*8+c*4+s*2+t;
    return this->getUnusedPiece(index);
}

Piece & Pool::getUnusedPiece(const std::string &in){
    if(in.length()!=4){
        InvalidInputException err_3(in);
        throw err_3;
    }else{
        short int h=-1, c=-1, s=-1, t=-1;
        std::istringstream iStream;
        char H, C, S, T;
        iStream.str(in);
        iStream >> H >> C >> S >> T;
        if(H==HCODE[0]){h=0;}
        else if(H==HCODE[1]){h=1;}
        if(C==CCODE[0]){c=0;}
        else if(C==CCODE[1]){c=1;}
        if(S==SCODE[0]){s=0;}
        else if(S==SCODE[1]){s=1;}
        if(T==TCODE[0]){t=0;}
        else if(T==TCODE[1]){t=1;}
        if((h+1)*(c+1)*(s+1)*(t+1)==0){ //either h, c, s, or t is still -1, indicating invalid input
            InvalidInputException err_3(in);
            throw err_3;
        }else{
            return this->getUnusedPiece(h*8+c*4+s*2+t);
        }
    }   
}

std::string Pool::toString() const{
    std::string l1, l2, result;
    std::ostringstream oStream_l1;
    std::ostringstream oStream_l2;
    int i=0;
    register bool first_piece=true;
    for(i=0;i<NP;i++){
        if(!this->pieces[i].isUsed()){
            if(!first_piece){oStream_l1 << " "; oStream_l2 << " ";}
            oStream_l1 << (this->pieces[i].toString()).substr(0,2);
            oStream_l2 << (this->pieces[i].toString()).substr(2);
            first_piece=false;
        }
    }
    l1=oStream_l1.str();
    l2=oStream_l2.str();
    if(!first_piece){result="Available:\n"+l1+"\n"+l2;}
    else{result="";} //return empty string if the list is empty
    return result;
}

