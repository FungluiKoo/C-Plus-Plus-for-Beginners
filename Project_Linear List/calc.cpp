//
//Reversed-Polish Calculator, Version 1.5, Fenglei Gu, 30 July 2019
//

#include <iostream>
#include <string>

#include "dlist.h"

using namespace std;

static void processing(string str, Dlist<int> *const stack); //background calculation/manipulation
static void binaryOperation(string op, Dlist<int> *const stack); //for binary operators (+-*/r)
static void unaryOperation(string op, Dlist<int> *const stack); //for unary operators (ndp)
static void clear(Dlist<int> *const stack); //do the clear operation
static void printAll(Dlist<int> *const stack); //do the printAll operation
static bool isInteger(string str); //judge whether is a valid input
static void common(string str, Dlist<int> *const stack); //either number or wrong input

int main(){
    string str; //used to store number or operator
    Dlist<int> *stack= new Dlist<int>; //dynamic stack
    while(cin>>str){ //get number or operator
        if(str.empty()){
            continue;
        }else if(str=="q"){ //we need to quit the calculator
            break;
        }else{ //we need to execute
            processing(str,stack);
        }
    }
    delete stack;
    return 0;
}

static void processing(string str, Dlist<int> *const stack){
    string binaryOps="+-*/r";
    string unaryOps="ndp";
    if(str.length()==0){ //blank, no need to process
        return;
    }else if(str.length()==1){
        if(binaryOps.find(str)!=binaryOps.npos){ // a binary operator found
            binaryOperation(str,stack);
        }else if(unaryOps.find(str)!=unaryOps.npos){ // a unary operator found
            unaryOperation(str,stack);
        }else if(str=="c"){ // clear stack
            clear(stack);
        }else if(str=="a"){ // list all
            printAll(stack);
        }else{common(str,stack);} // other circumstances
    }else{common(str,stack);} // other circumstances
}

static void binaryOperation(string op, Dlist<int> *const stack){
    int *first, *second;
    //get the two operends
    try{ //get first operend
        first=stack->removeBack();
    }catch(...){ //even no one operends!
        cout<< "Not enough operands" << endl;
        return;
    }
    try{ //get second operend
        second=stack->removeBack();
    }catch(...){ //only one operends -- no second operend!
        stack->insertBack(first);
        cout << "Not enough operands" << endl;
        return;
    }
    //calculations
    if(op=="+"){*second = *second + *first; delete first;}
    else if(op=="-"){*second = *second - *first; delete first;}
    else if(op=="*"){*second = (*second) * (*first); delete first;}
    else if(op=="/"){
        if((*first)==0){ //divide by zero, error!
            cout << "Divide by zero" << endl;
            stack->insertBack(second);
            stack->insertBack(first);
            return;
        }else{
            *second = (*second) / (*first);
            delete first;
        }
    }else{stack->insertBack(first);} //reverse
    //give back the result
    stack->insertBack(second);
}

static void unaryOperation(string op, Dlist<int> *const stack){
    int *pop;
    //get one operend
    try{
        pop=stack->removeBack();
    }catch(...){ //no operend available
        cout<< "Not enough operands" << endl;
        return;
    }
    int *result=new int;
    //calculation
    if(op=="n"){*result=-(*pop);} //negate
    else if(op=="d"){ //duplicate
        int *dup=new int;
        *dup=*pop;
        stack->insertBack(dup);
        *result=*pop;
    }else{cout<<*pop<<endl;*result=*pop;} //print (one item)
    //give back the result
    stack->insertBack(result);
    delete pop;
}

static void clear(Dlist<int> *const stack){
    while(!(stack->isEmpty())){
        int *temp=stack->removeBack();
        delete temp;
    }
}

static void printAll(Dlist<int> *const stack){
    Dlist<int> *tempList=new Dlist<int>(*stack);
    while(!(tempList->isEmpty())){
        int *item=tempList->removeBack();
        cout<<*item<<" ";
        delete item;
    }
    cout<<endl;
    delete tempList;
}

static bool isInteger(string str){
    //REQUIRES: len(str)>1., whixh is ensured in the processing function block
    short unsigned int i=1;
    for(i=1;i<str.length();i++){
        if(str.at(i)<'0' || str.at(i)>'9'){
            return false;
        }else{continue;}
    }
    if((str.at(0)<'0' || str.at(0)>'9') && str.at(0)!='-'){return false;}
    else{return true;}
}

static void common(string str, Dlist<int> *const stack){
    int *newNum=new int;
    if(!isInteger(str)){
        cout << "Bad input" << endl;
        delete newNum;
        return;
    }else{
        *newNum=stoi(str);
        stack->insertBack(newNum);
    }    
}
