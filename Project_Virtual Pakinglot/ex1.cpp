#include "GPL.h"
#include <mem.h>

void Initialize(Vehicle* a, int* usernumber) {
	*usernumber = rand() % MaxUN + 1;
	FOR(i,0,*usernumber-1) {
		int type = rand() % 4 + 1;
		int leavingtime = rand() % MaxTime + 1;
		int enteringtime = rand() % leavingtime;
		a[i].ini(type, i, enteringtime, leavingtime);
	}
}

void parkingLotManage(Vehicle* a, int n) {
	priority_queue<PLinfo> pl;
	bool slot[5][MaxBN];
	bool user[MaxUN];
	int Maxl[4] = {MaxVN, MaxCN, MaxMN, MaxBN};
	memset(slot, 0, sizeof(slot));
	memset(user, 0, sizeof(user));
	FOR(i,0,n-1) {
		pl.push(a[i].genin());
		pl.push(a[i].genout());
		user[i] = 1;
	}

	while (!pl.empty()) {
		PLinfo temp = pl.top();
		if (temp.io == 1) {
			FOR(i,0,Maxl[temp.tp])
				if (!slot[temp.tp][i]) {
					user[temp.id] = 1; // register the user
					a[temp.id].setslot(temp.tp, i+1); // notice that there's no slot 0
					slot[temp.tp][i] = 1;// register the slot
					a[temp.id].printin();//print the entering info
					break;
				}
			if (!user[temp.id]) {
				cout << "Sorry!" << endl;
				cout << "You failed to enter the parking lot since every slot of your type has been occupied!" << endl;
				cout << endl;
			}
			getchar();
		}
		else 
			if (user[temp.id]) {
				user[temp.id] = 0;// cancel the user
				slot[temp.tp][a[temp.id].showslot()] = 0;// cancel the slot
				a[temp.id].printout();//print the leaving info
				getchar();
			}
		pl.pop();
	}
}

void ex1() {
	srand((unsigned)time(NULL));
	Vehicle userlist[MaxUN]; int usernumber;
	Initialize(userlist, &usernumber);
	parkingLotManage(userlist, usernumber);
}