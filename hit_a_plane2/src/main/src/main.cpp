#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

// print some message when get fault
char _errMSG[256];
#define E_MSG(MSG, VAL) do{sprintf(_errMSG, "error:%s\n file:%s:%d", MSG, __FILE__, __LINE__);perror(_errMSG);return (VAL);}while(0)

#define WIN_WIDTH 80
#define WIN_HEIGHT 25

char disBuf[25][80]; // display buff
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
private:
	char* _disBuff;
	int _win_w;
	int _win_h;
};
void Display::sOutline(char ch){

	// draw outline
	for (int i=0; i<_win_w; i++){
		sBuff(0, i, ch);
		sBuff(_win_h-1, i, ch);
	}
	for (int i=0; i<_win_h; i++){
		sBuff(i, 0, ch);
		sBuff(i, _win_w-1, ch);
	}
}
void Display::cBuff(char ch){
	
	for (int i=0; i<_win_h; i++){

		for(int j=0; j <_win_w; j++){
			sBuff(i, j, ch);	
		}
	}
}
void Display::dis(){
	
	system("clear");
	for (int i=0; i<_win_h; i++){

		for(int j=0; j <_win_w; j++){
			printf("%c", disBuf[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

class Plane{
public:
	Plane(int vx, int vy, int win_w, int win_h);
	~Plane(){}
	
	void draw(Display* win, char ch); 
	void updateLoc(int t);
	int getX(){return mx;}
	int getY(){return my;}
private:
	int mvx;
	int mvy;
	int mx;
	int my;
	
	int mwin_w;
	int mwin_h;
};
Plane::Plane(int vx, int vy, int win_w, int win_h){
	mvx = vx;
	mvy = vy;

	mx = 1;
	my = 1;

	mwin_w = win_w;
	mwin_h = win_h;
}
void Plane::draw(Display* pwin, char ch){

	pwin->sBuff(my, mx, ch);
	pwin->sBuff(my, mx-1, ch);
	pwin->sBuff(my, mx-2, ch);
	pwin->sBuff(my, mx+1, ch);
	pwin->sBuff(my, mx+2, ch);
	pwin->sBuff(my-1, mx, ch);
	pwin->sBuff(my+1, mx-1, ch);
	pwin->sBuff(my+1, mx+1, ch);

}
void Plane::updateLoc(int t=1){
	mx = mx + mvx*t;
	my = my + mvy*t;
	
	if(mx >= mwin_w-1-1 || mx <= 1){
		mvx = -mvx;
	}
	if(my >= mwin_h-1-1 || my <= 1){
		mvy = -mvy;
	}
	

}


void updateWindow(Display* pwin, Plane* ap){

	// init window
	pwin->cBuff(' ');
	// draw outline
	pwin->sOutline('*');
	// draw plane
	ap->draw(pwin, '*');
}

int main(int argc, char** argv){
	
	Display win(WIN_WIDTH, WIN_HEIGHT);
	Plane ap(1, 1, WIN_WIDTH, WIN_HEIGHT);



	while(1){
		
		ap.updateLoc(1);
		updateWindow(&win, &ap);

		win.dis();
		usleep(100000);
	}
	return 0;
}
