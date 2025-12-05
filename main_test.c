/********************************************************
 * @file main.c                                         *
 * @Brief Main driver of the game                       *
 * @author CMPT201 Group 2                              *
 * @date Nov. 27, 2025                                  *
 ********************************************************/


#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include "player.h"
#include "splash_art.h"
#include "level_template.h"
int main(){
	//Ncurse initializing
	initscr();
	noecho();
	/*
	w = newwin(30,80,1,1);
	refresh();
        wborder(w,'|','|','-','-','+','+','+','+');
	wfresh(w);
	*/
	//In each function, a return of one signifies that the user quits
	if (start_art() == 1){
		getch();
		endwin();
		return 1;
	}
	if (level_template() == 1){
		getch();
		endwin();
		return 1;
	} 
	end_art();
	// Game is ended
	getch();
	endwin();
	return 0;
}
