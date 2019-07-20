#include "square.h"

Square::Square(Vaxis v, Haxis h){
    this->v = v;
    this->h = h;
    this->p = nullptr; 
}

Vaxis Square::getV() const{
    return this->v;
}

void Square::setV(Vaxis v){
    this->v = v;
}

Haxis Square::getH() const{
    return this->h;
}

void Square::setH(Haxis h){
    this->h = h;
}

const Piece & Square::getPiece() const{
    if(this->p==nullptr){
        SquareException err_1(*this,"empty");
        throw err_1;
    }else{
        return *p;
    }
}

void Square::setPiece(const Piece *p){
    if(this->p!=nullptr){
        SquareException err_1(*this,"not empty");
        throw err_1;
    }else{
        this->p = p;
    }
}

bool Square::isEmpty() const{
    return (this->p == nullptr);
}

bool Square::isOnFirstDiagonal() const{
    return (int(v)==int(h));
}

bool Square::isOnSecondDiagonal() const{
    return ((int(v)+int(h)+1)==N);
}

std::string Square::toString() const{
    char V;
    switch(int(this->v)){
        case 0:
            V='A';
            break;
        case 1:
            V='B';
            break;
        case 2:
            V='C';
            break;
        default:
            V='D';
    }
    auto H=int(this->h);
    std::string result;
    std::ostringstream oStream;
    oStream << V << (H+1);
    result=oStream.str();
    return result;
}

