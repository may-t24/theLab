/********************************************************
 * @file player.c                                       *
 * @Brief Definition of the functions in player.h       *
 * @author CMPT201 Group 2                              *
 * @date Nov. 27, 2025                                  *
 ********************************************************/
#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include "player.h"

Player createPlayer(int x, int y){
	Player p1;
	p1.x = x;
	p1.y = y;
	p1.symbol = '@';
	return p1;
}

/* might need this for other functions
void drawPlayer(){
	mvaddch(p1.y,p1.s,p1.symbol);
	refresh();
}
*/

Player moveRight(Player p1){
	mvaddch(p1.y,p1.x,' ');
	mvaddch(p1.y,p1.x +1,p1.symbol);
	p1.x+=1;
	refresh();
	return p1;
}

Player moveLeft(Player p1){
        mvaddch(p1.y,p1.x,' ');
        mvaddch(p1.y,p1.x -1,p1.symbol);
        p1.x-=1;
        refresh();
        return p1;
}
//Going up is NEGATIVE in ncurse
Player moveUp(Player p1){
        mvaddch(p1.y,p1.x,' ');
        mvaddch(p1.y-1,p1.x,p1.symbol);
        p1.y-=1;
        refresh();
        return p1;
}

Player moveDown(Player p1){
        mvaddch(p1.y,p1.x,' ');
        mvaddch(p1.y+1,p1.x,p1.symbol);
        p1.y+=1;
        refresh();
        return p1;
}


