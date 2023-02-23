#include "plane.h"


int main(){
	Dislpay win(80, 25);
	Plane ap(&win, 1, 1);

	ap.draw('x');

	win.dis();


}
