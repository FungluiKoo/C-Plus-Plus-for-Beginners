//
//Call Center, Version 2.4, Fenglei Gu, 30 July 2019
//

#include <iostream>
#include <string>

#include "dlist.h"

using namespace std;

const unsigned short int N=4; //the number of levels in total
enum status_t{REGULAR, SILVER, GOLD, PLATINUM};
const char* statusCODE[]={"regular","silver","gold","platinum"};
status_t str2status(string name);

class Customer{
private:
    unsigned int timestamp;
    string name;
    status_t status;
    unsigned int duration;
public:
    void setTimestamp(unsigned int timestamp){this->timestamp=timestamp;}
    void setName(string name){this->name=name;}
    string getName(){return this->name;}
    void setStatus(status_t status){this->status=status;}
    void setDuration(unsigned int duration){this->duration=duration;}
    unsigned int getDuration(){return this->duration;}
};

class Center{
private:
    unsigned short int custNum;
    unsigned int leftTime; //time left for the current call
public:
    Dlist<Customer> *regularCust;
    Dlist<Customer> *silverCust;
    Dlist<Customer> *goldCust;
    Dlist<Customer> *platinumCust;
    Center(unsigned short int num=1);
    ~Center();
    void clock(); // sycroneous clock
    void welcome(unsigned int ts); //get one line (customer)
    void check(); // get one customer in stack if not busy
    void answerCall(Dlist<Customer> *queue); //answer one call, used in check() function
    bool allReceived() const{return (this->custNum)<=0;} //file read to end
    bool completed() const; //all customers have finished the call
};


int main(){
    // initialization
    unsigned short int custNum=0; //number of customers today
    cin>>custNum;
    Center todayCenter(custNum);
    
    // operations
    unsigned int tick=0;
    unsigned int timestamp=0;
    cin >> timestamp;
    do{
        todayCenter.clock();
        cout << "Starting tick #" << tick << endl;
        while(timestamp==tick){
            if(!todayCenter.allReceived()){
                todayCenter.welcome(timestamp);
                cin >> timestamp;
            }else{timestamp=(unsigned int)(-1);break;}
        }
        todayCenter.check();
        tick++;
    }while(!todayCenter.completed());

    // episode
    return 0;
}

status_t str2status(string name){
    if(name==statusCODE[0]){return status_t(0);}
    else if(name==statusCODE[1]){return status_t(1);}
    else if(name==statusCODE[2]){return status_t(2);}
    else{return status_t(3);}
}

Center::Center(unsigned short int num){
    regularCust=new Dlist<Customer>;
    silverCust=new Dlist<Customer>;
    goldCust=new Dlist<Customer>;
    platinumCust=new Dlist<Customer>;
    this->custNum=num;
    this->leftTime=0;
}

Center::~Center(){
    delete regularCust;
    delete silverCust;
    delete goldCust;
    delete platinumCust;
}

void Center::clock(){
    if((this->leftTime)>0){this->leftTime--;}
}

void Center::welcome(unsigned int ts){
    string nm, st; //name and status;
    unsigned int dr; //duration
    cin >> nm >> st >> dr;
    Customer *newcomer=new Customer;
    newcomer->setTimestamp(ts);
    newcomer->setName(nm);
    newcomer->setStatus(str2status(st));
    newcomer->setDuration(dr);
    if(str2status(st)==REGULAR){
        this->regularCust->insertBack(newcomer);
    }else if(str2status(st)==SILVER){
        this->silverCust->insertBack(newcomer);
    }else if(str2status(st)==GOLD){
        this->goldCust->insertBack(newcomer);
    }else{
        this->platinumCust->insertBack(newcomer);
    }
    cout << "Call from " << nm << " a " << st << " member" << endl;
    if(this->custNum!=0){(this->custNum)--;}
}

void Center::check(){
    if(this->leftTime==0){// ready to answer call
        if(!this->platinumCust->isEmpty()){ // answer platinum queue
            this->answerCall(this->platinumCust);
            return;
        }else if(!this->goldCust->isEmpty()){ //answer gold queue
            this->answerCall(this->goldCust);
            return;
        }else if(!this->silverCust->isEmpty()){ //answer silver queue
            this->answerCall(this->silverCust);
            return;
        }else if(!this->regularCust->isEmpty()){ //answer regular queue
            this->answerCall(this->regularCust);
            return;
        }
    }
}

void Center::answerCall(Dlist<Customer> *queue){
    Customer *front=queue->removeFront();
    this->leftTime = front->getDuration();
    cout << "Answering call from " << front->getName() <<endl;
    delete front;
}

bool Center::completed() const{
    return (leftTime==0 && custNum==0 && regularCust->isEmpty() && silverCust->isEmpty() && goldCust->isEmpty() && platinumCust->isEmpty());
}

