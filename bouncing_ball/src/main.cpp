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

class BouncingBall{
public:
	BouncingBall(int vx, int vy, int win_w, int win_h);
	~BouncingBall(){}

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
BouncingBall::BouncingBall(int vx, int vy, int win_w, int win_h){
	mvx = vx;
	mvy = vy;

	mx = 1;
	my = 1;

	mwin_w = win_w;
	mwin_h = win_h;
}
void BouncingBall::updateLoc(int t=1){
	mx = mx + mvx*t;
	my = my + mvy*t;
	
	if(mx >= mwin_w-1-1 || mx <= 1){
		mvx = -mvx;
	}
	if(my >= mwin_h-1-1 || my <= 1){
		mvy = -mvy;
	}
	

}


void updateWindow(BouncingBall* bb){

	// init window
	for (int i=0; i<WIN_HEIGHT; i++){

		for(int j=0; j <WIN_WIDTH; j++){
			disBuf[i][j]=' ';	
		}
	}

	// draw outline
	for (int i=0; i<WIN_WIDTH; i++){
		disBuf[0][i]='*';
		disBuf[WIN_HEIGHT-1][i]='*';
	}
	for (int i=0; i<WIN_HEIGHT; i++){
		disBuf[i][0]='*';
		disBuf[i][WIN_WIDTH-1]='*';
	}

	// draw bouncing ball
	disBuf[bb->getY()][(*bb).getX()] = 'o';
}
void drawWindow(){
	system("clear");
	for (int i=0; i<WIN_HEIGHT; i++){

		for(int j=0; j <WIN_WIDTH; j++){
			printf("%c", disBuf[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	usleep(100000);
}

int main(int argc, char** argv){
	
	BouncingBall bb(1, 1, WIN_WIDTH, WIN_HEIGHT);



	while(1){
		drawWindow();	
		
		bb.updateLoc(1);
		updateWindow(&bb);
	}
	return 0;
}
