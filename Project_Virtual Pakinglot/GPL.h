#ifndef _GPL_H_
#define _GPL_H_
#include <iostream>
#include <cstdio>
#include <queue>
#include <ctime>
#define FOR(i,l,r) for(int i=l;i<=r;++i)
#define FOD(i,r,l) for(int i=r;i>=l;--i)
#define MaxUN 500
#define MaxVN 30
#define MaxCN 50
#define MaxMN 90
#define MaxBN 150
#define MaxTime 86400
using namespace std;

void printTime(int x); //to transform the time in s to the form of h:m:s
void printPrice(int tp, int x); //to print the price according to the type of vehicle and the duration

class PLinfo {
public:
	bool operator<(const PLinfo& t) const;//in order to use the
	//priority_queue, we need to define the order of PLinfo
	int time;//indicating the time when the event happens
	int id;//indicating the indentity of user
	int io;//indicating which kind of event, 
	int tp;//indicating the type of the vehicle
	//0 indicating leaving and 1 indicating entering
};

class Vehicle {
public:
	Vehicle();//empty constructor
	Vehicle(int tp, int id, int et, int lt);// initialize the info of an vehicle
	void ini(int tp, int id, int et, int lt);// another initialization
	~Vehicle();
	void setslot(int floor, int slot);//setting the info of an vehicle
	int showslot();//return the slot to cancel the vehicle
	void printin();//print the info when entering
	void printout();//print the info when leaving
	PLinfo genin();//To generate the entering info;
	PLinfo genout();//To generate the leaving info;
private:
	int tp;//indicating the type of vehicle
	int id;//indicating the identity of user
	int et;//indicating the entering time
	int lt;//indicating the leaving time
	int fl;//indicating the parking floor
	int s;//indicating the parking slot
};

#endif