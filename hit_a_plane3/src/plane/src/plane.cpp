#include "plane.h"

void Plane::draw(char ch){

	_pwin->sBuff(_y, _x, ch);
	_pwin->sBuff(_y, _x-1, ch);
	_pwin->sBuff(_y, _x-2, ch);
	_pwin->sBuff(_y, _x+1, ch);
	_pwin->sBuff(_y, _x+2, ch);
	_pwin->sBuff(_y-1, _x, ch);
	_pwin->sBuff(_y+1, _x-1, ch);
	_pwin->sBuff(_y+1, _x+1, ch);

}
void Plane::updateLoc(int t=1){
	_x = _x + _vx*t;
	_y = _y + _vy*t;
	
	if(_x >= (_pwin->gWinW())-1-1 || _x <= 1){
		_vx = -_vx;
	}
	if(_y >= (_pwin->gWinH())-1-1 || _y <= 1){
		_vy = -_vy;
	}
	

}

