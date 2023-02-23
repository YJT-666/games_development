#include "../../include/display/window.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

Window::Window(std::string& win_name, int win_h, int win_w, int begin_y, int begin_x, short win_color, Window* parent){

    _childMap = new WMAP;
	_win_name = new std::string(win_name);

	_win_w = win_w;
	_win_h = win_h;
	_win_begin_y = begin_y;
	_win_begin_x = begin_x;

	_win_color = win_color;
	_win_color_f = COLOR_WHITE;
	_win_color_b = COLOR_BLACK;

	if(parent == NULL){
		initscr();	
    	cbreak(); // To disable the buffering of typed characters by the TTY driver and get a character-at-a-time input
		noecho(); // To suppress the automatic echoing of typed characters
		keypad(stdscr, TRUE); // In order to capture special keystrokes like Backspace, Delete and the four arrow keys by getch()
		curs_set(0); //sets the appearance of the cursor Invisible
		nodelay(stdscr, TRUE);
		if(hasColors()){
			start_color(); // color support on
		}
		getmaxyx(stdscr, _win_h, _win_w);
		_win = stdscr;
	}else{
		_parent = parent;
		_parent->insertChildWin(this);
		_win = newwin(_win_h, _win_w, _win_begin_y, _win_begin_x);
	}
	
	// color support
	if(hasColors()){
		setColor(COLOR_BLUE, COLOR_BLACK);
	}

	sOutline();
	reflashWin();
}
Window::~Window(){
	delete _win_name;  // release name memory
	if (_childMap->size()){
		for(MIT it = _childMap->begin(); it != _childMap->end(); it++){
			delete it->second;  // delete children win
		}	
		_childMap->clear();
	}
	delete _childMap;
	if(_parent==NULL){
		endwin(); // Before the program is terminated, endwin() must be called to restore the terminal settings
	}else{
		delwin(_win); // release screen win memory
	}
}
Window::Window(Window& win, std::string win_name){
	Window(win_name, win._win_h, win._win_w, win._win_begin_y, win._win_begin_x, win._win_color, win._parent);
}


void Window::addChar(int y, int x, chtype ch, chtype attr){
	mvwaddch(_win, y, x, ch | attr);
}
void Window::sOutline(chtype ls, chtype rs, chtype ts, chtype bs, chtype tl, chtype tr, chtype bl, chtype br){
	// draw outline
	// wborder(_win, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK);
	wborder(_win, ls, rs, ts, bs, tl, tr, bl, br);
}



void Window::printTips(const char* tips){	
	int y,x;
	waddstr(_win, tips);
	getyx(_win,  y, x);
	y++;
	if(y > _win_h - 1) y = 0;
	x = 0;
	wmove(_win, y, x);
}

void Window::setColor(short f, short b){
	if(hasColors()){
		wattroff(_win, COLOR_PAIR(_win_color));
		init_pair(_win_color, f, b);
		wattron(_win, COLOR_PAIR(_win_color)); // set color
	}
}
void Window::unSetColor(){
	if(hasColors()){
		wattroff(_win, COLOR_PAIR(_win_color));
		init_pair(_win_color, _win_color_f, _win_color_b); // set default color
		wattron(_win, COLOR_PAIR(_win_color)); // set color
	}	
}
void Window::setColorPart(short color_pair){
	if(hasColors()){
		wattron(_win, COLOR_PAIR(color_pair)); // set color
	}
}
void Window::unSetColorPart(short color_pair){
	if(hasColors()){
		wattroff(_win, COLOR_PAIR(_win_color));
	}
}

void Window::insertChildWin(Window* cWin){
	if(cWin == NULL) return;
	_childMap->insert(std::make_pair(*(cWin->_win_name), cWin));
}
Window* Window::findChildWin(std::string& win_name){
	MIT it = _childMap->find(win_name);
	if(it != _childMap->end()){
		return it->second;
	}else{
		return NULL;
	}
}
void Window::deleteChildWin(std::string& win_name){
	MIT it = _childMap->find(win_name);
	if(it != _childMap->end()){
		delete it->second;  // release win
		_childMap->erase(it);
	}
}
int Window::numOfChildWin(){
	return _childMap->size();
}
bool Window::setParent(Window* win){
	if( win == NULL) return false;
	if( _parent != NULL ){
		_parent->deleteChildWin(*_win_name);
	}
	_parent = win;
	return true;
}

