#include "display.h"
#include <stdio.h>
#include <stdlib.h>


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
	for (int i=0; i<_win_h*_win_w;){
		printf("%c", _disBuff[i]);
		i++;
		if(i%_win_w==0) printf("\n");
	}
	printf("\n");
}
