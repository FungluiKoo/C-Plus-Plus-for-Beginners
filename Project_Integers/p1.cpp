//VE280 Project 1 Version 1.3 - Fenglei Gu 28 May 2019

#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
using namespace std;
const int BASE10=10;
const int BASE2=2;

int cntDig(int num){ //count the number of digits of input num
    int n=num, digit=0;
    while(n>0){
        digit++;
        n/=BASE10;
    }
    return digit;
}

void isTri(int num){ //judge input whether triangle
    auto key= (int) sqrt((float)2*num); //calculate the probable n
    if(num*2==key*(key+1)){cout<<1;} //yes
    else{cout<<0;} //no
}

void isPld(int num){ //judge input whether palindrome
    int n=num;
    int num2=0; //to be the inversed-digit number
    while(n>0){
        num2= num2*BASE10 + n%BASE10; //gradually, the least significant bit will become the most significant
        n/=BASE10;
    }
    if(num2==num){cout<<1;} //yes
    else{cout<<0;} //no
}

void isOdi(int num){ //judge whether odious
    int n=num;
    int cnt=0; //count the appearance of 1
    while(n>0){
        cnt+=n%BASE2;
        n/=BASE2;
    }
    if(cnt%2==1){cout<<1;}//yes
    else{cout<<0;}//no
}

void isExt(int num){ //judge whether extravagant
    //count the number of digits
    int digit=cntDig(num);

    //pseudo prime factorization
    int n=num;
    int base=0, expo=0; //total digits of base & exponential numbers
    for(int i=2; i<=num/2; i++){ 
        if(n%i==0){ //has factor base i
            base+=cntDig(i);
            n/=i;
            if(n%i==0){ //has exponent digit
                int tempExpo=1;
                while(n%i==0){n/=i;tempExpo++;}
                expo+=cntDig(tempExpo); //add the number of digits of the exponential
            }
        }
    }
    
    //judge extravagent
    if(digit<base+expo){cout<<1;} //yes
    else{cout<<0;} //no
}

struct IntPair{
    int num=-1;
    int choice=-1;
}intpair;

IntPair promptPair(){
    bool prompted=false;
    while (!prompted){
        cout<<"Please enter the integer and the test number: ";
        cin>>intpair.num>>intpair.choice; //if more integers are input, then this should be re-written
        if(intpair.num>0 && intpair.num<10000001 && intpair.choice>0 && intpair.choice<5){
            prompted=true;
            break;
            }
    }
    return intpair;
}

int main(){
    //ask for number pair
    IntPair p=promptPair();

    //to judge
    switch(p.choice){
        case 1:
            isTri(p.num);
            break;
        case 2:
            isPld(p.num);
            break;
        case 3:
            isOdi(p.num);
            break;
        default:
            isExt(p.num);
    }
    return 0;
}
