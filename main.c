//Group 2 - Assignment2
#include <stdio.h>
#include <curses.h>
#include <unistd.h>
int main(){
	WINDOW *w;
	Player p1;
	int input;
	//Ncurse initializing
	initscr();
	noecho();
	w = newwin(30,80,1,1);
	refresh();
        wborder(w,'|','|','-','-','+','+','+','+');
	wfresh(w);
	start_art();
	level1();
	level2();
	end_art();
	// Game is ended
	getch();
	endwin();
	return 0;
}
