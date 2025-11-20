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
	char h = '|';
	//Adds actual walls since border is visual only
       	mvprintw(25,30,"%c",h);
        mvprintw(26,30,"%c",h);
        mvprintw(27,30,"%c",h);
	p1.createPlayer();
	drawPlayer(p1);
	//Handles input / gamestate
	while(1){
		if (input == KEY_RIGHT){
			if (mvinch(p1.y,p1.x+1) == ' '){
			p = movePlayerRight(p1);
			}
		} else if (input 'q'){
			break;
		}
		input=getch();
		refresh();
	}
	// Game is ended
	getch();
	endwin();
	return 0;
}
