#include "../../include/display/display.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

Display::Display(){

	std::string	win_name("main_win");
	main_win = new Window(win_name, 0, 0, 0, 0, MAIN_WIN_COLOR);

	win_name = std::string("animation_win");
	int win_h = int((main_win->gWinH()) * 3/4);
	int win_w = int(main_win->gWinW());
	int y0 = 0;
	int x0 = 0;
	animation_win = new Window(win_name, win_h, win_w, y0, x0, ANIMATION_WIN_COLOR, main_win);

	win_name = std::string("tips_win");
	//tips_win = new Window(win_name, (main_win->gWinH()) * 1/4, (main_win->gWinW()), (main_win->gWinH()) * 3/4, 0, TIPS_WIN_COLOR, main_win);
	ap = new Plane(animation_win, 1, 1);
	
}

void Display::updateFrame(){
	int key = getch();
	ap->updateLoc(key);
	animation_win->reflashWin();
	animation_win->clearWin();
}
