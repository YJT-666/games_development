#ifndef DISPLAY_H__JT
#define DISPLAY_H__JT

#include <ncurses.h>

class Display{
public:
	Display(int win_w, int win_h, char line_ch='*'){
		_win_w = win_w;
		_win_h = win_h;
		_line_ch = line_ch;
		_disBuff = new char[_win_w*_win_h];
		cBuff(' ');
	}
	~Display(){ delete [] _disBuff; }

	void sBuff(int row, int col, char ch){
		if(row >= _win_h-2) row = _win_h-2;
		if(col >= _win_w-2) col = _win_w-2;
		if(row <=1 ) row = 1;
		if(col <=1 ) col = 1;
		_disBuff[row*_win_w + col] = ch;
	}
	
	void sOutline(char ch); // set outline
	void cBuff(char ch); // use ch to lean buff
	void dis();

	int gWinW(){return _win_w;}
	int gWinH(){return _win_h;}
private:
	char* _disBuff;
	int _win_w;
	int _win_h;
	char _line_ch;
	
	void sBuff_line(int row, int col, char ch){
		_disBuff[row*_win_w + col] = ch;
	}
};

#endif
