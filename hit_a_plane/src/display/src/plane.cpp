#include "../../include/display/plane.h"

void Plane::draw(){
	
	//_pwin->addChar(_y, _x,  _sCh, _attr);
	//_pwin->addChar(_y, _x-1, _sCh, _attr);
	//_pwin->addChar(_y, _x-2, _sCh, _attr);
	//_pwin->addChar(_y, _x+1, _sCh, _attr);
	//_pwin->addChar(_y, _x+2, _sCh, _attr);
	//_pwin->addChar(_y-1, _x, _sCh, _attr);
	//_pwin->addChar(_y+1, _x-1, _sCh, _attr);
	//_pwin->addChar(_y+1, _x+1, _sCh, _attr);

	init_pair(PLANE_COLOR_PAIR, COLOR_YELLOW, COLOR_BLACK);
	_pwin->setColorPart(PLANE_COLOR_PAIR);
	_pwin->addChar(_y, _x,  _sCh);
	_pwin->addChar(_y, _x-1, _sCh);
	_pwin->addChar(_y, _x-2, _sCh);
	_pwin->addChar(_y, _x+1, _sCh);
	_pwin->addChar(_y, _x+2, _sCh);
	_pwin->addChar(_y-1, _x, _sCh);
	_pwin->addChar(_y+1, _x-1, _sCh);
	_pwin->addChar(_y+1, _x+1, _sCh);
	_pwin->unSetColorPart(PLANE_COLOR_PAIR);
	
	if(bullet_y > 0){
		_pwin->addChar(bullet_y, bullet_x, '|');
	}

	if(isKilled){
		_pwin->addChar(target_y, target_x, ' ');
	}else{
		_pwin->addChar(target_y, target_x, '$');
	}

}
void Plane::updateLoc(char key){

	updateInput(key);

	if(bullet_y > 0) bullet_y--;
	
	if(target_spd < 10){
		target_spd++;
	}else{
		target_y++;
		target_spd=0;
	}

	limitBoundary();	
	draw();
}

void Plane::updateInput(char key){

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
			break;
		case ' ':
			isFire=true;
			bullet_x = _x;
			bullet_y = _y - 1;
			break;
		default:
			isFire=false;
			break;
	}
	if(_x == target_x && key == ' ') isKilled=true;
}

