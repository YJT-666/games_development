#ifndef WINDOW_H__JT
#define WINDOW_H__JT

#include <curses.h>
#include <unistd.h>
#include <string>
#include <map>

typedef chtype chtype;


class Window{
public:
	Window(std::string& win_name, int win_h, int win_w, int begin_y, int begin_x, short win_color, Window* parent=NULL);
	~Window();
	Window(Window& win, std::string win_name); // copy construct
			
	// set outline
	void sOutline(chtype ls=ACS_BLOCK, chtype rs=ACS_BLOCK, chtype ts=ACS_BLOCK, chtype bs=ACS_BLOCK, \
	              chtype tl=ACS_BLOCK, chtype tr=ACS_BLOCK, chtype bl=ACS_BLOCK, chtype br=ACS_BLOCK);
	void addChar(int y, int x, chtype ch, chtype attr); 
	void addChar(int y, int x, chtype ch) { addChar(y, x, ch, 0); }
	void reflashWin() {  sOutline(); wrefresh(_win); }
	void clearWin() { wclear(_win); }
	void printTips(const char* s);
	
	void setColor(short f, short b);
	void setColorF(short f) { setColor(f, _win_color_b); }
	void setColorB(short b) { setColor(_win_color_f, b); }
	void setColorPart(short color_pair);
	void unSetColorPart(short color_pair);
	void unSetColor();

	int gWinW(){return _win_w;}
	int gWinH(){return _win_h;}
	int gWinBY(){return _win_begin_y;}
	int gWinBX(){return _win_begin_x;}
	short gWinColor(){return _win_color;}
	short gWinColorF(){return _win_color_f;}
	short gWinColorB(){return _win_color_b;}
	std::string& gWinName(){return *_win_name;}
	Window* gWinParent(){return _parent;}

	bool hasColors() { return has_colors() && can_change_color(); } // check color support

	bool setParent(Window* win);
	void insertChildWin(Window* cWin);
	Window* findChildWin(std::string& win_name);
	void deleteChildWin(std::string& win_name);
	int numOfChildWin();
private:
	Window* _parent;     // parent window
	
	typedef std::map<std::string, Window* > WMAP;
	typedef WMAP::iterator MIT;
	WMAP * _childMap; // children window map name is the key
	
	std::string* _win_name; // win name
	WINDOW* _win;  // screen
	int _win_w; 
	int _win_h;
	int _win_begin_y;
	int _win_begin_x;

	short _win_color;  // win color pair number
	short _win_color_f;
	short _win_color_b;
	
	int _cursor_x;  // cursor location
	int _cursor_y;

	attr_t _win_attr; // window atributes
};

#endif
