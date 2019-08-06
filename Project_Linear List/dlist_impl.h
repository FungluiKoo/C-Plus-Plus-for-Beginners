//
// Double-Linked List, Version 2.0, fenglei Gu, 28 July 2019
//

#include <cstdlib>

#ifndef DLIST_IMPL_H
#define DLIST_IMPL_H

//
// Utility methods
//

template <class T>
void Dlist<T>::removeAll(){
    while(!(this->isEmpty())){
        T *op=this->removeBack();
        delete op;
    }
}

template <class T>
void Dlist<T>::copyAll(const Dlist &l){
    if(this==&l){return;} //do not copy itself
    else{
        this->removeAll();
        node *current=l.first;
        while(current!=nullptr){
            T *newTptr= new T(*(current->op));
            this->insertBack(newTptr);
            current=current->next;
        }
    }
}

//
// Maintenance methods
//

template <class T>
Dlist<T>::Dlist(){
    this->first=nullptr;
    this->last=nullptr;
}

template <class T>
Dlist<T>::Dlist(const Dlist &l){
    this->first=nullptr;
    this->last=nullptr;
    this->copyAll(l);
}

template <class T>
Dlist<T> & Dlist<T>::operator=(const Dlist<T> &l){
    if(this!=&l){this->copyAll(l);}
    return *this;
}

template <class T>
Dlist<T>::~Dlist(){
    this->removeAll();
}

//
// Operational methods
//

template <class T>
bool Dlist<T>::isEmpty() const{
    return (this->first)==nullptr;
}

template <class T>
void Dlist<T>::insertFront(T *op){
    node *np= new node;
    if(this->isEmpty()){np->next=nullptr;}
    else{np->next=this->first;}
    np->prev=nullptr;
    np->op=op;
    if(this->isEmpty()){this->last=np;}
    else{this->first->prev=np;}
    this->first=np;
}

template <class T>
void Dlist<T>::insertBack(T *op){
    node *np= new node;
    np->next=nullptr;
    if(this->isEmpty()){np->prev=nullptr;}
    else{np->prev=this->last;}
    np->op=op;
    if(this->isEmpty()){this->first=np;}
    else{this->last->next=np;}
    this->last=np;
}

template <class T>
T* Dlist<T>::removeFront(){
    if(this->isEmpty()){
        emptyList err;
        throw err;
    }else{
        node *victim=this->first;
        T *result=victim->op;
        if(this->first->next==nullptr){ //only one node left at this time
            this->first=nullptr;
            this->last=nullptr;
        }else{ //there is still other nodes left
            victim->next->prev=nullptr;
            this->first=victim->next;
        }
        delete victim;
        return result;
    }
}

template <class T>
T * Dlist<T>::removeBack(){
    if(this->isEmpty()){
        emptyList err;
        throw err;
    }else{
        node *victim=this->last;
        T *result=victim->op;
        if(this->last->prev==nullptr){ //only one node in the list
            this->first=nullptr;
            this->last=nullptr;
        }else{
            victim->prev->next=nullptr;
            this->last=victim->prev;
        }
        delete victim;
        return result;
    }
}

#endif /** DLIST_IMPL_H */