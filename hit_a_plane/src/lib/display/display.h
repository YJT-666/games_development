#ifndef DISPLAY_H__JT
#define DISPLAY_H__JT

class Display{
public:
	Display(int win_w, int win_h){
		_win_w = win_w;
		_win_h = win_h;
		_disBuff = new char[_win_w*_win_h];
	}
	~Display(){ delete [] _disBuff; }

	void sBuff(int row, int col, char ch){
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
};

#endif
