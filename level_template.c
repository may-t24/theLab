//Group 2 - Assignment 2
#include <stdio.h>
#include <curses.h>
#include <time.h>
/*This is just a template of what a level*.c could look like.   Needs to be expanded more
This is where you would add the maze layout and the objects.  Basically think about how the level would look like and translate it into here
*/
void level_template(){
        char h = '|';
	//represents the object the player needs to collect.  Replace 0 with the value for the level
        int key_count =0;
	//Tracks the location of each key.  Second array is the coord as (x,y)
	int key_location[key_count][2];
	//NPC not a struct since its fairly similar to Player struct without much differences
	Player NPC;
	NPC.createPlayer(10,15);
	drawPlayer(NPC);
	//The npcs dialogue when you interact with him.  Replace example text with your own text
	char npc_dialogue[] ="Hello Player";
	time_t npc_timer1 = time();
	time_t npc_timer2 = time();
        //Adds actual walls since border is visual only
	//Put your level layout here
        mvprintw(25,30,"%c",h);
        mvprintw(26,30,"%c",h);
        mvprintw(27,30,"%c",h);
        p1.createPlayer(0,10);
        drawPlayer(p1);
        //Handles input / gamestate
        while(1){
		//Keep track of where = is in the maze.  Replace 0,0 with the coords of =
		if key_count = 0{
			mvaddch('0','0',' ');
		}
		/* if timer1 is 3 seconds, NPC move right, 
		if timer2 is 6 seconds NPC move left reset time		*/
		if(time - npc_timer1 >=3){
			movePlayerRight(NPC);
			npc_timer1 = time();
		}
		if (time - npc_timer2 >=6){
			movePlayerLeft(NPC);
			npc_timer2 = time();
		}
		//Might see if switch case is possible here
                if (input == KEY_RIGHT){
                        if (mvinch(p1.y,p1.x+1) == ' '){
                        p = movePlayerRight(p1);
			sleep(5);
                        }
		} else if(input == KEY_LEFT){
                        if (mvinch(p1.y,p1.x-1) == ' '){
                        p = movePlayerLeft(p1);
			sleep(5);
                        } 
                } else if(input == KEY_UP){
                        if (mvinch(p1.y-1,p1.x) == ' '){
                        p = movePlayerUp(p1);
			sleep(5);
                        } 

                } else if(input == KEY_DOWN){
                        if (mvinch(p1.y+1,p1.x) == ' '){
                        p = movePlayerDown(p1);
			sleep(5);
                        } 
                } else if (input == 'q'){
			if(end_art() = 1){
				return 1;
			}
			refresh_level();
                } else if (input == 'p'){
			pause_art();
			refresh_level();
		//Checks player interaction
		} else if (input == 'i'){
			//NPC check can combine all the +1 checks into one statement since it does not need to modify the play field
			if(mvinch(p1.y,p1.x+1) == '?' || mvinch(p1.y,p1.x-1) == '?' || mvinch(p1.y-1,p1.) == '?' || mvinch(p1.y+1,p1.x) == '?'){
				//print npc_dialogue in ncurses
				mvprintw(15,40,npc_dialogue);
				//Pressing any button closes dialogue
				input = getch();
				clear();
				refresh();
			}
			//Exit Reached.  Going to next level
                        if(mvinch(p1.y,p1.x+1) == '#' || mvinch(p1.y,p1.x-1) == '#' || mvinch(p1.y-1,p1.) == '#' || mvinch(p1.y+1,p1.x) == '#'){
                                return 0;
                        }
                        if(mvinch(p1.y,p1.x+1) == '0'){
				mvaddch(p1.y,p1.x+1,' ');
				for(int i = 0; i < (sizeof(key_location)/sizeof(key_location[0]); i++){
					if(p1.y == key_location[i][1] && p1.x+1 == key_location[i][0]){
						key_location[i][0] == -1;
						key_location[i][1] == -1;
					}
				}
				key_count-=1;
			} else if (mvinch(p1.y,p1.x-1) == '0'){
                                mvaddch(p1.y,p1.x-1,' ');
                                for(int i = 0; i < (sizeof(key_location)/sizeof(key_location[0]); i++){
                                        if(p1.y == key_location[i][1] && p1.x-1 == key_location[i][0]){
                                                key_location[i][0] == -1;
                                                key_location[i][1] == -1;
                                        }
                                }
				key_count-=1;
			} else if (mvinch(p1.y-1,p1.) == '0'){
                                for(int i = 0; i < (sizeof(key_location)/sizeof(key_location[0]); i++){
                                        if(p1.y-1 == key_location[i][1] && p1.x == key_location[i][0]){
                                                key_location[i][0] == -1;
                                                key_location[i][1] == -1;
                                        }
                                }
                                mvaddch(p1.y-1,p1.,' ');
				key_count-=1;
			} else if (mvinch(p1.y+1,p1.x) == '0'){
                                for(int i = 0; i < (sizeof(key_location)/sizeof(key_location[0]); i++){
                                        if(p1.y+1 == key_location[i][1] && p1.x == key_location[i][0]){
                                                key_location[i][0] == -1;
                                                key_location[i][1] == -1;
                                        }
                                }
                                mvaddch(p1.y+1,p1.x,' ');
				key_count-=1;
			}

		}
                input=getch();
                refresh();
        }

}

void refresh_level(){
	// Copy the level layout here
	
	//Refresh the player and npc
	drawPlayer(p1);
	drawPlayer(NPC);
	// Draws the uncollected keys
	for(int i = 0; i < (sizeof(key_location)/sizeof(key_location[0]); i++){
		if(key_location[i][0] != -1 && key_location[i][1] != -1){
			mvaddch(key_location[i][0],key_location[1],'0');
		}
	}
	refresh();
}
