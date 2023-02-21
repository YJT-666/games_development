#ifndef PLANE_H__JT
#define PLANE_H__JT
#include "../display/display.h"

class Plane{
public:
	Plane(Display* pwin, int vx, int vy):_pwin(pwin), _vx(vx), _vy(vy), _x(1), _y(1) {}
	
	~Plane(){}
	
	void draw(char ch); 
	void updateLoc(int t);
	int getX(){return _x;}
	int getY(){return _y;}
private:
	int _vx;
	int _vy;
	int _x;
	int _y;

	Display* _pwin;
};
