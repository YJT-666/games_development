#include "../../include/display/plane.h"

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
void Plane::updateLoc(char key){

	switch(key){
		case 'a':
			_x--;
			break;
		case 'd':
			_x++;
			break;
		case 'w':
			_y--;
			break;
		case 's':
			_y++;
	}
	limitBoundary();	
	draw(_draw_ch);
}

