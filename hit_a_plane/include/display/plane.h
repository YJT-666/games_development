#ifndef PLANE_H__JT
#define PLANE_H__JT
#include "window.h"


#define PLANE_COLOR_PAIR (COLORS-1)

class BasicObj{
public:
	int y;
	int x;
	int min_y;
	int min_x;
	int max_y;
	int max_x;
	int spd;
	char ch;
	Window* pwin;


	virtual void updateLoc()=0;
	virtual void draw()=0;
}
class Enemy : public BasicObj{
	Enemy(int my, int mx, int mspd, int maxY, int maxX, int minY, int minX, char mch, Window mpwin){
		y = my;
		x = mx;
		spd = mspd;
		max_y = maxY;
		max_x = maxX;
		min_y = minY;
		min_x = minX;
		ch = mch;
		pwin = mpwin;

		isKilled = false;
	}	
	void updateLoc(){
		if( spd < 10){
			spd++;
		}else{
			y++;
			spd=0;
		}
	}
	void draw(){
		if(isKilled){
			pwin->addChar(y, x, ' ');
		}else{
			pwin->addChar(y, x, ch);
		}
	}

	bool isKilled;
}


class Plane{
public:

	Plane(Window* pwin, int vx, int vy ):_pwin(pwin), _vx(vx), _vy(vy), _x(1), _y(1){
		_sCh = '*';
		_attr = A_BOLD;
		isFire = false;
		isKilled = false;

		bullet_x = 0;
		bullet_y = 0;

		target_spd = 0;
		target_x = _pwin->gWinW() / 2;
		target_y = 10;
	}
	
	~Plane(){}
	
	void draw(); 
	void updateLoc(char key);
	void updateInput(char key);
	int getX(){return _x;}
	int getY(){return _y;}
private:
	int _vx;
	int _vy;
	int _x;
	int _y;

	char _sCh;
	chtype _attr;


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
		if(_y <= 2){
			_y = 2;
		}
	}

	Window* _pwin;

	bool isFire;
	int bullet_x;
	int bullet_y;

	int target_x;
	int target_y;
	int target_spd;
	bool isKilled;
};

#endif
