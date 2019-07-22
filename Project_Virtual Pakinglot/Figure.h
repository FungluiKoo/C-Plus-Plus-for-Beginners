#ifndef _FIGURE_H_
#define _FIGURE_H_

#include "Vec.h"
#include "Constpara.h"
#include <windows.h>
#include <freeglut.h>
#include <ctime>
#include <iostream>

class Figure {
protected:
	Vec anchor;
public:
	Figure() : anchor(0,0) {}
	Vec getAnchor() {return anchor;}
	void setAnchor(Vec a) {anchor = a;}
	virtual void draw() = 0;
	virtual void move(Vec dir) = 0;
	virtual void rotate(float angle) = 0;
	virtual void zoom(float k) = 0;
	virtual ~Figure() {} 
};

class ColoredFig : public Figure {
protected:
	float r, g, b;// indicating the color;
public:
	void paint(float* r, float* g, float* b) {
		*r = (float)rand()/RAND_MAX;
		*g = (float)rand()/RAND_MAX;
		*b = (float)rand()/RAND_MAX;
	}
};

class Line : public ColoredFig {
protected:
	Vec p[2];
public:
	Line (Vec p1, Vec p2, 
		float red, float green, float blue) {
		p[0] = p1; p[1] = p2;
		r = red; g = green; b = blue;
	}
	void draw() {
		glColor3f(r, g, b);
		glBegin(GL_LINES);
		FOR(i,0,1)
			glVertex2f(p[i].getx()/MS, p[i].gety()/MS);
		glEnd();
	}
	void move(Vec dir) {
		FOR(i,0,1)
			p[i] = p[i] + dir;
		anchor = anchor + dir;
	}
	void rotate(float angle) {
		FOR(i,0,1) {
			Vec temp = p[i] - anchor;
			temp = temp << angle;
			p[i] = anchor + temp;
		}
	}
	void zoom(float k) {
		FOR(i,0,1) {
			Vec temp = p[i] - anchor;
			temp = temp * k;
			p[i] = anchor + temp;
		}
	}
};

class Triangle : public ColoredFig {
protected:
	Vec p[3];
public:
	Triangle (Vec p1, Vec p2, Vec p3, 
		float red, float green, float blue) {
		p[0] = p1; p[1] = p2; p[2] = p3;
		r = red; g = green; b = blue;
	}
	void draw() {
		glColor3f(r, g ,b);
		glBegin(GL_TRIANGLES);
		FOR(i,0,2)
			glVertex2f(p[i].getx()/MS, p[i].gety()/MS);
		glEnd();
	}
	void move(Vec dir) {
		FOR(i,0,2)
			p[i] = p[i] + dir;
		anchor = anchor + dir;
	}
	void rotate(float angle) {
		FOR(i,0,2) {
			Vec temp = p[i] - anchor;
			temp = temp << angle;
			p[i] = anchor + temp;
		}
	}
	void zoom(float k) {
		FOR(i,0,2) {
			Vec temp = p[i] - anchor;
			temp = temp * k;
			p[i] = anchor + temp;
		}
	}
};

class Quadrilateral : public ColoredFig {
protected:
	Vec p[4];
public:
	Quadrilateral (Vec p1, Vec p2, Vec p3, Vec p4, 
		float red, float green, float blue) {
		p[0] = p1; p[1] = p2; p[2] = p3; p[3] = p4;
		r = red; g = green; b = blue;
	}
	void draw() {
		glColor3f(r, g ,b);
		glBegin(GL_QUADS);
		FOR(i,0,3)
			glVertex2f(p[i].getx()/MS, p[i].gety()/MS);
		glEnd();
	}
	void move(Vec dir) {
		FOR(i,0,3)
			p[i] = p[i] + dir;
		anchor = anchor + dir;
	}
	void rotate(float angle) {
		FOR(i,0,3) {
			Vec temp = p[i] - anchor;
			temp = temp << angle;
			p[i] = anchor + temp;
		}
	}
	void zoom(float k) {
		FOR(i,0,3) {
			Vec temp = p[i] - anchor;
			temp = temp * k;
			p[i] = anchor + temp;
		}
	}
};

class _Polygon : public ColoredFig {
protected:
	Vec p;//indicating the first point
	Vec c;//indicating the center point;
	int e;//indicating the number of edges
public:
	_Polygon (Vec center, Vec point, int edge,
		float red, float green, float blue) {
		c = center; p = point;
		e = edge;
		r = red; g = green; b = blue;
	}
	void draw() {
		paint(&r, &g, &b);
		glColor3f(r, g, b);
		glBegin(GL_POLYGON);
		FOR(i,0,e-1) {
			Vec temp = (p - c) >> (2*pi/e*i);
			temp = temp + c;
			glVertex2f(temp.getx()/MS, temp.gety()/MS);
		}
		glEnd();
	}
	void move(Vec dir) {
		p = p + dir;
		c = c + dir;
		anchor = anchor + dir;
	}
	void rotate(float angle) {
		Vec temp = p - anchor;
		temp = temp << angle;
		p = p + temp;
	}
	void zoom(float k) {
		Vec temp = p - anchor;
		temp = temp * k;
		p = anchor + temp;
	}
};

class Circle : public ColoredFig {
protected:
	Vec c;//indicating the center point;
	float rd;//indicating the radius;
public:
	Circle () {}
	Circle (Vec center, float radius,
		float red, float green, float blue) {
		c = center;
		rd = radius;
		r = red; g = green; b = blue;
	}
	void draw() {
		glColor3f(r, g, b);
		glBegin(GL_POLYGON);
		FOR(i,0,MD) {
			Vec temp = {rd * cos(-2*pi/MD*i), rd * sin(-2*pi/MD*i)};
			temp = temp + c;
			glVertex2f(temp.getx()/MS, temp.gety()/MS);
		}
		glEnd();
	}
	void move(Vec dir) {
		c = c + dir;
		anchor = anchor + dir;
	}
	void rotate(float angle) {
		Vec temp = c - anchor;
		temp = temp << angle;
		c = anchor + temp;
	}
	void zoom(float k) {
		rd *= k;
	}
};

class PartialCircle : public Circle {
protected:
	float al;//indicating the starting angle alpha
	float th;//indicating the drawing angle theta
public:
	PartialCircle (Vec center, float radius, float alpha, float theta,
		float red, float green, float blue) {
		c = center;
		rd = radius; al = alpha, th = theta;
		r = red; g = green; b = blue;
	}
	void draw() {
		glColor3f(r, g, b);
		glBegin(GL_POLYGON);
		FOR(i,0,MD) {
			Vec temp = {rd * cos(al-th/MD*i), rd * sin(al-th/MD*i)};
			temp = temp + c;
			glVertex2f(temp.getx()/MS, temp.gety()/MS);
		}
		glVertex2f(c.getx()/MS, c.gety()/MS);
		glEnd();
	}
	void move(Vec dir) {
		c = c + dir;
		anchor = anchor + dir;
	}
	void rotate(float angle) {
		al += angle;
	}
	void zoom(float k) {
		rd *= k;
	}
};

class Flag : public Figure {
protected:
	Vec bot;//the bottom of the pole
	//also indicating the size of the flag
	Vec ct;
	Vec top;
	Figure* sh[2];
public:
	Flag(Vec center, Vec bottom) {
		ct = center; bot = bottom;
		top = ct * 2 - bot;
		sh[0] = new Line(bot, top, 0, 0, 0);
		Vec temp = top - ct;
		Vec mid = (top + ct) * 0.5;
		temp = (temp << (pi/2)) + mid;
		sh[1] = new Triangle(top, ct, temp, 1, 0, 0);
	}
	void moveFlag() {
		int static direct = 0;
		int static runtime = 0;
		if (direct == 0) sh[1]->move((ct - top) * 0.02);
		if (direct == 1) sh[1]->move((top - ct) * 0.02);
		runtime ++;
		if (runtime >= 50) {
			direct ^= 1;
			runtime = 0;
		}
	}
	void move(Vec dir) {
		ct = ct + dir;
		bot = bot + dir;
		top = top + dir;
		anchor = anchor + dir;
		FOR(i,0,1)
			sh[i]->move(dir);
		moveFlag();
	}
	void rotate(float angle) {
		Vec temp = top - anchor; temp = temp << angle; top = anchor + temp;
		temp = bot - anchor; temp = temp << angle; bot = anchor + temp;
		temp = ct - anchor; temp = temp << angle; ct = anchor + temp;
		FOR(i,0,1) {
			sh[i]->setAnchor(anchor);
			sh[i]->rotate(angle);
		}
		moveFlag();
	}
	void draw() {
		FOR(i,0,1)
			sh[i]->draw();
	}
	void zoom(float k) {}
};

#endif