#include "piece.h"

Piece::Piece(Height h, Color c, Shape s, Top t){
    this->h=h;
    this->c=c;
    this->s=s;
    this->t=t;
    this->setUsed(false); //when a piece is generated, it is initially not used.
}

bool Piece::compareHeight(const Piece &p) const{
    return (this->h == p.h);
}

bool Piece::compareColor(const Piece &p) const{
    return (this->c == p.c);
}

bool Piece::compareShape(const Piece &p) const{
    return (this->s == p.s);
}

bool Piece::compareTop(const Piece &p) const{
    return (this->t == p.t);
}

bool Piece::isUsed() const{
    return this->used;
}

void Piece::setUsed(bool u){
    this->used = u;
}

std::string Piece::toString() const{
    std::string result;
    std::ostringstream oStream;
    oStream << HCODE[h] << CCODE[c] << SCODE[s] << TCODE[t];
    result = oStream.str();
    return result;
}

