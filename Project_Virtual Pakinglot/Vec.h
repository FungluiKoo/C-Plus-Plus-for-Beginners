#ifndef _VEC_H_
#define _VEC_H_

#include <cmath>
#include "Constpara.h"

class Vec {
public:
	Vec() {
		x = 0; y = 0;
	}
	Vec(double _x, double _y) {
		x = _x; y = _y;
    }
	double getx() {
		return x;
	}
	double gety() {
		return y;
	}
	Vec operator+ (Vec v) {
		return Vec(x + v.getx(), y + v.gety());
	}
	Vec operator- (Vec v) {
		return Vec(x - v.getx(), y - v.gety());
	}
	Vec operator* (double k) {
		return Vec(x * k, y * k);
	}
	double operator* (Vec v) {
		return x * v.getx() + y * v.gety();
	}
	//Notice that the angle is expressed in radian
	Vec operator<< (double t) {
		return Vec(x * cos(t) - y * sin(t), x * sin(t) + y * cos(t));
	}
	Vec operator>> (double t) {
		return Vec(x * cos(t) + y * sin(t), - x * sin(t) + y * cos(t));
	}
	bool operator== (Vec v) {
		return (fabs(x - v.x)<ZERO && fabs(y - v.y)<ZERO);
	}
private:
	double x, y;
};
#endif