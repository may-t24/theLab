//Group 2 - Assignment 2
#include <stdio.h>
#include <curses.h>
#include <unistd.h>

/*This is just a template of what a level*.c could look like.   Needs to be expanded more
This is where you would add the maze layout and the objects.  Basically think about how the level would look like and translate it into here
*/
void level_template(){
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
			end_art();
                } else if (input 'p'){
			pause_art();
		}
                input=getch();
                refresh();
        }

}
