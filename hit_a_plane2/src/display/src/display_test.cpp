
#include <iostream>
#include <string>
#include <map>
#include <curses.h>

// test func class
typedef  int (*PTFunc)();
#define MKSTR(X) #X
#define ADD_TEST_FUN(FT, FNAME) FT.addTestFun(MKSTR(FNAME), FNAME) 
class FuncTest{
public:
	FuncTest():_num(0){ _mf = new std::map<std::string, PTFunc>; }
	~FuncTest(){ delete _mf; }
	void addTestFun(std::string mark, PTFunc pF){ _num++; _mf->insert(std::make_pair(mark, pF)); }
	void deleteTestFun(PTFunc pF){ if (_num==0) return; SIT sit=_mf->find(MKSTR(pF)); if(sit != _mf->end()) {_mf->erase(sit); _num--;} }
	void clearTestFun(){ while(_num) {_mf->clear(); _num=0;} }
	int numOfTestFun(){return _num;}
	
	int selectTestFunRun(std::string fn); // return 0 is pass, -1 present no this test function
	int testRun(); // run func test, return number of success
private:
	using SIT = std::map<std::string, PTFunc>::iterator;
	int _num; // Number of functions to test
	std::map<std::string, PTFunc>* _mf; // a map to save test function

};

int FuncTest::testRun(){
	if ( _num <= 0 ) return -1;  // no test function
	
	int pass_count=0, fail_count=0, r=-1;
	for ( SIT it = _mf->begin(); it != _mf->end(); it++){
		try {
			r = (*((*it).second))();
		} catch (...) {
		   r = -1;
		   std::cout << "error................" << std::endl;
		}
		if ( r==0 ){
		 	pass_count++;
			std::cout << "Function: " << (*it).first << " pass !" << std::endl;
		}else{
			fail_count++;
		}
		r = -1;
	}
	return pass_count;
}
int FuncTest::selectTestFunRun(std::string fn){
	int r=-1;
	SIT it = _mf->find(fn);
	if (it != _mf->end()){
		try {
			r = (*((*it).second))();
		} catch (...) {
		   r = 1;
		}
	}
	if (r==0) std::cout << "Function: " << (*it).first << " pass !" << std::endl;
	return r;
}
	

#include "../../include/display/display.h"
#include "../../include/display/plane.h"



int t_display(){
	Display win(80, 25);
	win.cBuff('o');
	win.sOutline('*');
	win.dis();
	return 0;
}

int t_plane(){
	Display win(80, 25);
	win.sOutline('o');
	Plane ap(&win, 1, 1);

	while(1){
		
		initscr();	
		cbreak();
		char ch = getch();
		endwin();
		ap.updateLoc(ch);
		win.dis();
		std::cout << "ch" << ch << std::endl;
	}
	return 0;
}
int t_1(){
	return 0;
}
int t_2(){
	return 1;
}
int t_0(){
	
	int a = 100;
	int b = 0;
	return 0;
}

int main(int argc, char* argv[]){
	FuncTest ft;
	
	// add function
	ADD_TEST_FUN(ft, t_display);
	ADD_TEST_FUN(ft, t_plane);
	ADD_TEST_FUN(ft, t_0);
	ADD_TEST_FUN(ft, t_1);
	ADD_TEST_FUN(ft, t_2);


	int pass_count=0;
	if (argc == 1){
		// test all module
		pass_count =  ft.testRun();
	}else{
		for (int i=1; i < argc; i++){
			std::cout << "running function: " << argv[i] << " ..." << std::endl;
			int r = ft.selectTestFunRun(argv[i]);
			if (r==0) pass_count++;
		}
	}
	std::cout << "total:" << ft.numOfTestFun() <<" " << "pass:" << pass_count << std::endl;

	return 0;
}
