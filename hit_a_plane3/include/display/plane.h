#ifndef PLANE_H__JT
#define PLANE_H__JT
#include "../display/display.h"

class Plane{
public:
	Plane(Display* pwin, int vx, int vy, char draw_ch='*'):_pwin(pwin), _vx(vx), _vy(vy), _x(1), _y(1), _draw_ch(draw_ch){}
	
	~Plane(){}
	
	void draw(char ch); 
	void updateLoc(char key);
	int getX(){return _x;}
	int getY(){return _y;}
private:
	int _vx;
	int _vy;
	int _x;
	int _y;

	int _draw_ch;

	void limitBoundary(){
		if(_x >= (_pwin->gWinW())-2){
			_x = (_pwin->gWinW())-2;
		}
		if(_x <= 1){
			_x = 1;
		}
		if(_y >= (_pwin->gWinH())-2){
			_y = (_pwin->gWinH())-2;
		}
		if(_y <= 1){
			_y = 1;
		}
	}

	Display* _pwin;
};

#endif
