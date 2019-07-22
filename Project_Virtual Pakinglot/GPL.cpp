#include "GPL.h"

void printTime(int x) {
	int h = x / 60 / 60;
	int m = (x % 3600) / 60;
	int s = x % 60;
	if (h<10) 
		cout << "0" << h;
	else
		cout << h;
	cout << ":";
	if (m<10)
		cout << "0" << m;
	else
		cout << m;
	cout << ":";
	if (s<10)
		cout << "0" << s;
	else 
		cout << s;
}

void printPrice(int tp, int x) {
	int h = x / 60 / 60;
	h = h % 4 + 1;
	int p = h * (5 - tp) * 5;
	if (p<10)
		cout << "¥ " << p << "  ";
	else
		if (p<100)
			cout << "¥ " << p << " ";
		else
			cout << "¥ " << p;
}

bool PLinfo::operator<(const PLinfo& t) const{
	if (time != t.time) 
		return (time>t.time);
	return (io>t.io);
}

Vehicle::Vehicle() {}
Vehicle::Vehicle(int tp, int id, int et, int lt) {
	this->tp = tp;
	this->id = id;
	this->et = et;
	this->lt = lt;
}
Vehicle::~Vehicle() {}
void Vehicle::ini(int tp, int id, int et, int lt) {
	this->tp = tp;
	this->id = id;
	this->et = et;
	this->lt = lt;
}
void Vehicle::setslot(int floor, int slot) {
	fl = floor;
	s = slot;
}
int Vehicle::showslot() {
	return s;
}
void Vehicle::printin() {
	cout << "╔═════Welcome!═════╗" << endl;
	cout << "║TIME:";
	printTime(et);
	cout << "     ║" << endl;
	cout << "╟──────────────────╢" << endl;
	cout << "║TYPE:";
	if (tp == 1)
		cout << " Van         ║" << endl;
	if (tp == 2)
		cout << " Car         ║" << endl;
	if (tp == 3)
		cout << " Motorbike   ║" << endl;
	if (tp == 4)
		cout << " Bicycle     ║" << endl;
	cout << "╟──────────────────╢" << endl;
	cout << "║PARKING PLACE:    ║" << endl;
	cout << "║ floor " << fl << " slot ";
	if (s<10) 
		cout << "0" << s;
	else 
		cout << s;
	cout << "  ║" << endl;
	cout << "╚══════════════════╝" << endl;
	cout << endl;
}	
void Vehicle::printout() {
	cout << "╔═════GoodBye!═════╗" << endl;
	cout << "║DURATION:";
	printTime(et);
	cout << " ║" << endl;
	cout << "╟──────────────────╢" << endl;
	cout << "║TYPE:";
	if (tp == 1)
		cout << " Van         ║" << endl;
	if (tp == 2)
		cout << " Car         ║" << endl;
	if (tp == 3)
		cout << " Motorbike   ║" << endl;
	if (tp == 4)
		cout << " Bicycle     ║" << endl;
	cout << "╟──────────────────╢" << endl;
	cout << "║PRICE: ";
	printPrice(tp, lt - et);
	cout << "      ║" << endl;
	cout << "╚══════════════════╝" << endl;
	cout << endl;
}
PLinfo Vehicle::genin() {
	PLinfo temp = {et,id,1,tp};
	return temp;
}
PLinfo Vehicle::genout() {
	PLinfo temp = {lt,id,0,tp};
	return temp;
}