#ifndef DISPLAY_H__JT
#define DISPLAY_H__JT

#include <window.h>
#include <plane.h>

#define MAIN_WIN_COLOR 0
#define ANIMATION_WIN_COLOR 1
#define TIPS_WIN_COLOR 2
class Display{
public:
	Display();
	~Display(){
		delete main_win;
		delete ap;
	}

	void updateFrame();

	Window* main_win;
	Window* animation_win;
	Window* tips_win;
	Plane* ap;
private:

};

#endif
