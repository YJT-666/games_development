#include "display.h"


int main(){
	Display win(80, 25);
	win.cBuff('o');
	win.sOutline('*');
	win.dis();
}
