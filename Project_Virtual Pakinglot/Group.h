#ifndef _GROUP_H_
#define _GROUP_H_
#include "Figure.h"
#include "Constpara.h"

class Group : public Figure {
protected:
	Vec ct; // indicating the center
	int sn; // indicating the number of the shape or group
	Figure* sh[19];
public:
	Group () {
		ct = {0, 0};
		sn = 0;
	}
	~Group () {
		FOR(i,0,sn-1) delete sh[i];
	}
	void draw() {
		FOR(i,0,sn-1) sh[i]->draw();
	}
	void move(Vec dir) {
		ct = ct + dir;
		anchor = anchor + dir;
		FOR(i,0,sn-1) sh[i]->move(dir);
	}
	void rotate(float angle) {
		Vec temp = ct - anchor;
		temp = temp << angle;
		ct = anchor + temp;
		FOR(i,0,sn-1) {
			sh[i]->setAnchor(anchor);
			sh[i]->rotate(angle);
		}
	}
	void zoom(float k) {
		Vec temp = ct - anchor;
		temp = temp * k;
		ct = ct + temp;
		FOR(i,0,sn-1) {
			sh[i]->setAnchor(anchor);
			sh[i]->zoom(k);
		}
	}
	virtual void script(int p) = 0;
};

class Car : public Group {
protected:
	float u;// the standard scale unit of the car;
public:
	Car (Vec center, float unit) {
		sn = 5;
		ct = center; u = unit; setAnchor(ct);
		Vec p1 = {ct.getx() - 6*u, ct.gety() + u};
		Vec p2 = {ct.getx() - 6*u, ct.gety() - u};
		Vec p3 = {ct.getx() + 6*u, ct.gety() - u};
		Vec p4 = {ct.getx() + 6*u, ct.gety() + u};
		Vec p5 = {ct.getx() - 4*u, ct.gety() + u};
		Vec p6 = {ct.getx() - 3*u, ct.gety() + 3*u};
		Vec p7 = {ct.getx() + 2*u, ct.gety() + 3*u};
		Vec p8 = {ct.getx() + 3*u, ct.gety() + u};
		Vec p9 = {ct.getx() - 4*u, ct.gety() - u};
		Vec p10= {ct.getx() + 3*u, ct.gety() - u};
		Vec p11= {ct.getx() - 5*u, ct.gety() + u};
		Vec p12= {ct.getx() - 5*u, ct.gety() + 2*u};
		sh[0] = new Quadrilateral(p1,p2,p3,p4,(float)99/255,(float)184/255,(float)255/255);
		sh[1] = new Quadrilateral(p5,p6,p7,p8,(float)65/255,(float)105/255,(float)225/255);
		sh[2] = new Circle(p9,u,(float)110/255,(float)123/255,(float)139/255);
		sh[3] = new Circle(p10,u,(float)110/255,(float)123/255,(float)139/255);
		sh[4] = new Flag(p12,p11);
	}
	//other function can be inherited from Group prefectly
	void script(int p) {
		int static runtime = 0;
		int static stage = 1;
		if (runtime < 100) runtime++;
		else {
			if (stage == 0) return;//stop moving
			if (stage == 1) {
				if (ct.gety() < -25*u) {
					Vec temp = {0,10*u/100};
					move(temp);
				} else stage = 2;
				return;
			}
			if (stage == 2) {
				if (ct.getx() < -15*u) {
					Vec temp = {-15*u,-25*u};
					setAnchor(temp);
					rotate(-10*u/12/100);
				} else 
					if (p <= 5) stage = 3;
					else stage = 5;
				return;
			}
			if (stage == 3) {
				Vec temp1 = {10*u,0}, temp2 = {9*u,0};
				Vec static place = ct + temp1 * ((double)(p-1)) + temp2;
				if (ct.getx()<place.getx()) {
					temp1 = {10*u/100,0};
					move(temp1);
				} else stage = 4;
				return;
			}
			if (stage == 4) {
				Vec temp = {0,-9*u};
				Vec static place = ct + temp;
				if (ct.gety()>place.gety()) {
					setAnchor(place);
					rotate(10*u/9/100);
				} else stage = 0;
				return;
			}
			if (stage == 5) {
				if (ct.getx()<25*u) {
					Vec temp = {10*u/100,0};
					move(temp);
				} else stage = 6;
				return;
			}
			if (stage == 6) {
				Vec static place = {25*u,-2.5*u};
				if (ct.getx()>place.getx() || ct.gety()<place.gety()) {
					setAnchor(place);
					rotate(10*u/10.5/100);
				} else stage = 7;
				return;
			}
			if (stage == 7) {
				Vec temp1 = {-10*u,0}, temp2 = {-9*u,0};
				Vec static place = ct + temp1 * ((double)(10-p)) + temp2;
				if (ct.getx()>place.getx()) {
					temp1 = {-10*u/100,0};
					move(temp1);
				} else stage = 8;
				return;
			} 
			if (stage == 8) {
				Vec temp = {0,9*u};
				Vec static place = ct + temp;
				if (ct.gety()<place.gety()) {
					setAnchor(place);
					rotate(10*u/9/100);
				} else stage = 0;
				return;
			}
		}
	}
};

class Rocket : public Group {
protected:
	float u;// the standard scale unit of the rocket;
	int direct;
	double size;
public:
	Rocket (Vec center, float unit) {
		sn = 8;
		ct = center; u = unit; setAnchor(ct); direct = 0; size = 1;
		Vec p1 = {ct.getx() - 2*u, ct.gety() + 4*u};
		Vec p2 = {ct.getx() + 2*u, ct.gety() + 4*u};
		Vec p3 = {ct.getx() + 2*u, ct.gety() - 2*u};
		Vec p4 = {ct.getx() - 2*u, ct.gety() - 2*u};
		Vec p5 = {ct.getx() - u, ct.gety() - 2*u};
		Vec p6 = {ct.getx() + u, ct.gety() - 2*u};
		Vec p7 = {ct.getx() + 2*u, ct.gety() - 3*u};
		Vec p8 = {ct.getx() - 2*u, ct.gety() - 3*u};
		Vec p9 = {ct.getx() + 2*u, ct.gety() + 2*u};
		Vec p10= {ct.getx() + 3*u, ct.gety() - 2*u};
		Vec p11= {ct.getx() - 2*u, ct.gety() + 2*u};
		Vec p12= {ct.getx() - 3*u, ct.gety() - 2*u};
		Vec p13= {ct.getx() + 0.5*u, ct.gety() + 3*u};
		Vec p14= {ct.getx() + 1.5*u, ct.gety() + 3*u};
		Vec p15= {ct.getx() + 1.5*u, ct.gety() + 2*u};
		Vec p16= {ct.getx() + 0.5*u, ct.gety() + 2*u};
		Vec p17= {ct.getx() - 1.5*u, ct.gety() + 3*u};
		Vec p18= {ct.getx() - 0.5*u, ct.gety() + 3*u};
		Vec p19= {ct.getx() - 0.5*u, ct.gety() + 2*u};
		Vec p20= {ct.getx() - 1.5*u, ct.gety() + 2*u};
		Vec p21= {ct.getx() - 0.5*u, ct.gety() + u};
		Vec p22= {ct.getx() + 0.5*u, ct.gety() + u};
		Vec p23= {ct.getx() + 0.5*u, ct.gety() - u};
		Vec p24= {ct.getx() - 0.5*u, ct.gety() - u};
		Vec p25= {ct.getx(), ct.gety() + 6*u};
		sh[0] = new Quadrilateral(p1,p2,p3,p4,(float)238/255,(float)238/255,(float)0);
		sh[1] = new Quadrilateral(p5,p6,p7,p8,(float)218/255,(float)112/255,(float)214/255);
		sh[2] = new Triangle(p3,p9,p10,(float)205/255,(float)38/255,(float)38/255);
		sh[3] = new Triangle(p11,p4,p12,(float)205/255,(float)38/255,(float)38/255);
		sh[4] = new Quadrilateral(p13,p14,p15,p16,(float)238/255,(float)121/255,(float)66/255);
		sh[5] = new Quadrilateral(p17,p18,p19,p20,(float)238/255,(float)121/255,(float)66/255);
		sh[6] = new Quadrilateral(p21,p22,p23,p24,(float)238/255,(float)121/255,(float)66/255);
		sh[7] = new Triangle(p1,p2,p25,(float)205/255,(float)38/255,(float)38/255);
	}
	void script(int p) {
		if (direct == 0) {size *= 1.01; zoom(1.01);}
		if (direct == 1) {size *= 1/1.01; zoom(1/1.01);}
		if (size > 1.7) direct = 1;
		if (size < 1) direct = 0;
	}
};

class UFO : public Group {
protected:
	float u;
public:
	UFO (Vec center, float unit) {
		sn = 5;
		ct = center; u = unit; setAnchor(ct);
		Vec p1 = {ct.getx() + 2*u, ct.gety()};
		Vec p2 = {ct.getx() + 4*u, ct.gety()};
		Vec p3 = {ct.getx() + 5*u, ct.gety() - 2*u};
		Vec p4 = {ct.getx() + u, ct.gety() - 2*u};
		Vec p5 = {ct.getx() - 2*u, ct.gety()};
		Vec p6 = {ct.getx() - u, ct.gety() - 2*u};
		Vec p7 = {ct.getx() - 5*u, ct.gety() - 2*u};
		Vec p8 = {ct.getx() - 4*u, ct.gety()};
		Vec p9 = {ct.getx() - 3*u, ct.gety() + 4*u};
		Vec p10= {ct.getx() - 6*u, ct.gety() + 6*u};
		Vec p11= {ct.getx() + 3*u, ct.gety() + 4*u};
		Vec p12= {ct.getx() + 6*u, ct.gety() + 6*u};
		sh[0] = new PartialCircle(ct,5*u,pi,pi,(float)60/255,(float)179/255,(float)113/255);
		sh[1] = new Quadrilateral(p1,p2,p3,p4,(float)72/255,(float)209/255,(float)204/255);
		sh[2] = new Quadrilateral(p5,p6,p7,p8,(float)72/255,(float)209/255,(float)204/255);
		sh[3] = new Line(p9,p10,0,0,0);
		sh[4] = new Line(p11,p12,0,0,0);
	}
	void script(int p) {
		rotate(2*pi/MD); 
	}
};

class Teleporter : public Group {
protected:
	double runtime;
	double direct;
public:
	Teleporter(Vec center, Vec point) {
		sn = 8; runtime = 1; direct = -1;
		ct = center;
		FOR(i,0,7)
			sh[i] = new _Polygon(center,point,4+i,0,0,0);
	} 
	void draw() {
		sh[(int)runtime]->draw();
	}
	void script(int p) {
		runtime += 0.02 * direct;
		if (runtime>=7.5 || runtime<=0.5) direct *= -1; 
	}
};

class Parkinglot : public Group {
protected:
	float u;
public:
	Parkinglot(Vec center, float unit) {
		sn = 18;
		ct = center; u = unit;
		float grey = (float) 143/255;
		Vec p1 = {ct.getx() - 7*u, ct.gety() + 5*u};
		Vec p2 = {ct.getx() + 9*u, ct.gety() + 5*u};
		sh[0] = new Line(p1,p2,grey,grey,grey);
		p2 = {ct.getx() - 7*u, ct.gety() - 7*u};
		sh[1] = new Line(p1,p2,grey,grey,grey);
		p1 = {ct.getx() + 9*u, ct.gety() - 6*u};
		p2 = {ct.getx() + 9*u, ct.gety() + 5*u};
		sh[2] = new Line(p1,p2,grey,grey,grey);
		p2 = {ct.getx() - 4*u, ct.gety() - 6*u};
		sh[3] = new Line(p1,p2,grey,grey,grey);
		FOR(i,0,5) {
			p1 = {ct.getx() + (2*i-4)*u, ct.gety() + 5*u};
			p2 = {ct.getx() + (2*i-4)*u, ct.gety() + 3*u};
			sh[4+i] = new Line(p1,p2,grey,grey,grey);
		}
		p1 = {ct.getx() - 4*u, ct.gety() - 4*u};
		p2 = {ct.getx() - 4*u, ct.gety() - 7*u};
		sh[10] = new Line(p1,p2,grey,grey,grey);
		FOR(i,1,5) {
			p1 = {ct.getx() + (2*i-4)*u, ct.gety() - 4*u};
			p2 = {ct.getx() + (2*i-4)*u, ct.gety() - 6*u};
			sh[10+i] = new Line(p1,p2,grey,grey,grey);
		}
		p1 = {ct.getx() - 6.5*u, ct.gety() - 7*u};
		p2 = {ct.getx() - 4*u, ct.gety() - 7*u};
		sh[16] = new Line(p1,p2,1,0,0);
		p1 = {ct.getx() - 3*u, ct.gety()};
		p2 = {ct.getx() - 3*u, ct.gety() - u};
		Vec p3 = {ct.getx() + 5*u, ct.gety() - u};
		Vec p4 = {ct.getx() + 5*u, ct.gety()};
		sh[17] = new Quadrilateral(p1,p2,p3,p4,grey,grey,grey);
	}
	void script(int p) {
		int static runtime = 0;
		if (runtime <= 100) {
			runtime ++;
			Vec temp = {2.5*u/100, 0};
			sh[16]->move(temp);// Open the door;
		} else
		if (runtime <= 600) runtime ++;
		else 
			if (runtime <= 700) {
				runtime ++;
				Vec temp = {-2.5*u/100, 0};
				sh[16]->move(temp);
			}
	}
};

class Total {
protected:
	float u;
	int p;//indicating the place the car should park
	int sn;
	Group* sh[19];
public:
	Total(float unit) {
		int plot[20];
		memset(plot,0,sizeof(plot));
		plot[0] = rand() % 10 + 1;
		plot[plot[0]] = -1;
		FOR(i,1,10) 
		if (plot[i] != -1) 
			plot[i] = rand() % 4;
		sn = 1; u = unit; p = plot[0];
		Vec place[11];
		FOR(i,1,5)
			place[i] = {(-25+i*10)*u,-25*u};
		FOR(i,1,5)
			place[i+5] = {(-25+i*10)*u,20*u};
		FOR(i,1,10) {
			if (plot[i] == 0) continue;
			if (plot[i] == 1) {// _Polygon
				Vec temp = {0,3*u};
				sh[sn++] = new Teleporter(place[i], place[i] + temp);
				continue;
			}
			if (plot[i] == 2) {//UFO
				sh[sn++] = new UFO(place[i],u/2);
				continue;
			}
			if (plot[i] == 3) {//Rocket
				sh[sn++] = new Rocket(place[i],u/2);
				continue;
			}
		}
		Vec temp = {-27*u,-50*u};
		sh[0] = new Car(temp,u);
		sh[0]->setAnchor(temp);
		sh[0]->rotate(pi/2);
		temp = {0,0};
		sh[sn++] = new Parkinglot(temp, 5*u);
	}
	void script() {
		FOR(i,0,sn-1)
			sh[i]->script(p);
	}
	void draw() {
		FOR(i,0,sn-1)
			sh[i]->draw();
	}
};
#endif
