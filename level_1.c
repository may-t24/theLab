//Group 2 - Assignment 2
#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include "player.h"
#include "splash_art.h"
#include "level_1.h"

int level_1(){
	int input;
 	//represents the object the player needs to collect.  change start_count in the header file depending on your key count
        int key_count = start_count;
	//Tracks the location of each key.  Second array is the coord as (x,y)
	int key_location[start_count][2] = {
		{2, 24},
		{1, 6}
	};
	//NPC not a struct since its fairly similar to Player struct without much differences
	Player NPC,p1;
	NPC = createPlayer('?',10,27);
	//The npcs dialogue when you interact with him
	char npc_dialogue[] ="You have to escape the lab! The exit is over there!";
	int npc_timer= 0;
        p1 = createPlayer('@',2,27);
	//draws the objects and level structure for the level
        refresh_level1(p1,NPC,key_location);
	//prearing to enter while loop
	keypad(stdscr,TRUE);
	input=getch();
	refresh();
        //Handles input / gamestate
        while(1){
		//Keep track of where = is in the maze.  Replace 0,0 with the coords of =

		/* if timer1 is 3 seconds, NPC move right, 
		if timer2 is 6 seconds NPC move left reset time		*/
		//Might see if switch case is possible here
                if (input == KEY_RIGHT){
                        if (mvinch(p1.y,p1.x+1) == ' '){
                        p1 = moveRight(p1);
                        }
		} else if(input == KEY_LEFT){
                        if (mvinch(p1.y,p1.x-1) == ' '){
                        p1 = moveLeft(p1);
                        } 
                } else if(input == KEY_UP){
                        if (mvinch(p1.y-1,p1.x) == ' '){
                        p1 = moveUp(p1);
                        } 

                } else if(input == KEY_DOWN){
                        if (mvinch(p1.y+1,p1.x) == ' '){
                        p1 = moveDown(p1);
                        } 
                } else if (input == 'q'){
			clear();
			if(quit_art() == 1){
				return 1;
			}
			refresh_level1(p1,NPC,key_location);
                } else if (input == 'p'){
			clear();
			pause_art();
			refresh_level1(p1,NPC,key_location);
		//Checks player interaction
		} else if (input == 'i'){
			//NPC check can combine all the +1 checks into one statement since it does not need to modify the play field
			if(mvinch(p1.y,p1.x+1) == '?' || mvinch(p1.y,p1.x-1) == '?' || mvinch(p1.y-1,p1.x) == '?' || mvinch(p1.y+1,p1.x) == '?'){
				//print npc_dialogue in ncurses
				mvprintw(33,0,npc_dialogue);
				//Pressing any button closes dialogue
			}
			//Exit Reached.  Going to next level
                        if(mvinch(p1.y,p1.x+1) == '#' || mvinch(p1.y,p1.x-1) == '#' || mvinch(p1.y-1,p1.x) == '#' || mvinch(p1.y+1,p1.x) == '#'){
				clear();
                                return 0;
                        }
                        if(mvinch(p1.y,p1.x+1) == '0'){
				mvaddch(p1.y,p1.x+1,' ');
				for(int i = 0; i < start_count; i++){
					if(p1.y == key_location[i][1] && p1.x+1 == key_location[i][0]){
						key_location[i][0] = -1;
						key_location[i][1] = -1;
					}
				}
				key_count-=1;
			} else if (mvinch(p1.y,p1.x-1) == '0'){
                                mvaddch(p1.y,p1.x-1,' ');
                                for(int i = 0; i < start_count; i++){
                                        if(p1.y == key_location[i][1] && p1.x-1 == key_location[i][0]){
                                                key_location[i][0] = -1;
                                                key_location[i][1] = -1;
                                        }
                                }
				key_count-=1;
			} else if (mvinch(p1.y-1,p1.x) == '0'){
                                for(int i = 0; i < start_count; i++){
                                        if(p1.y-1 == key_location[i][1] && p1.x == key_location[i][0]){
                                                key_location[i][0] = -1;
                                                key_location[i][1] = -1;
                                        }
                                }
                                mvaddch(p1.y-1,p1.x,' ');
				key_count-=1;
			} else if (mvinch(p1.y+1,p1.x) == '0'){
                                for(int i = 0; i < start_count; i++){
                                        if(p1.y+1 == key_location[i][1] && p1.x == key_location[i][0]){
                                                key_location[i][0] = -1;
                                                key_location[i][1] = -1;
                                        }
                                }
                                mvaddch(p1.y+1,p1.x,' ');
				key_count-=1;
			}

		}
		input=getch();
		/* if timer1 is 3 seconds, NPC move right, 
                if timer2 is 6 seconds NPC move left reset time         */

		if(npc_timer == 3){
                        NPC = moveRight(NPC);
                }
                if (npc_timer == 6){
                        NPC = moveLeft(NPC);
                        npc_timer = 0;
                }
		npc_timer+=1;
		if (key_count == 0){
			//Doors get replaced by spaces when keys are found
			for(int y=1; y<=5; y++){
				mvaddch(y,74,' ');
			}
			for(int x=75; x<=79; x++){
				mvaddch(5,x,' ');
			}

	                mvprintw(6,83,"DOOR IS OPEN GOGOGO!");
		}
        	mvprintw(5,83,"Keys Left: %d",key_count);
		mvprintw(4,83,"Total Keys: %d",start_count);
                refresh();
        }

}
void refresh_level1(Player p1, Player NPC,int key_location[start_count][2]){
        // Draws Wall,Doors & Exit
	draw_level1();
	//Draw UI
	mvprintw(2,83,"LEVEL 1");
        mvprintw(6,83,"Door is Closed");
        mvprintw(32,0,"Dialogue:");
        mvprintw(8,83,"CONTROLS:");
        mvprintw(9,83,"Arrow Keys - Move");
        mvprintw(10,83,"I - Interact");
	mvprintw(11,83,"P - Pause");
        mvprintw(12,83,"Q - Quit");
	mvprintw(14,83,"Press I to pick up keys (0)!");
        //Refresh the player and npc
        drawPlayer(p1);
        drawPlayer(NPC);
        // Draws the uncollected keys
        for(int i = 0; i < start_count; i++){
                if(key_location[i][0] != 0 && key_location[i][1] != 0){
                        mvaddch(key_location[i][1],key_location[i][0],'0');
                } 
        }
        refresh();
}
//Level walls below
//Game Objects should still be placed in the regular level function
void draw_level1(){
	char wall = '|';
	char door = '=';
	char exit = '#';
	//border draw y
	for(int i =0; i <=30; i++)
	{
		mvprintw(i,0,"%c",wall);
		mvprintw(i,80,"%c",wall);
	}
	//border draw x
        for(int i =0; i <=80; i++)
        {
                mvprintw(0,i,"%c",wall);
		mvprintw(30,i,"%c",wall);
        }

	//Level layout
	//Main path
	for(int y=24;y<=29;y++){
	        mvprintw(y,17,"%c",wall);
	}

	for(int x=1;x<=15;x++){
		mvprintw(25,x,"%c",wall);
	}

	for(int x=3;x<17;x++){
		mvprintw(23,x,"%c",wall);
	}

	for(int y=21;y<24;y++){
		mvprintw(y,3,"%c",wall);
	}

	for(int x=3;x<20;x++){
		mvprintw(21,x,"%c",wall);
	}

	for(int x=1;x<21;x++){
		mvprintw(18,x,"%c",wall);
	}

	for(int y=10;y<=17;y++){
		mvprintw(y,20,"%c",wall);
	}

	for(int x=20;x<=32;x++){
		mvprintw(10,x,"%c",wall);
	}

	for(int x=22;x<=32;x++){
		mvprintw(12,x,"%c",wall);
	}

	for(int y=7;y<=25;y++){
		mvprintw(y,34,"%c",wall);
	}

	for(int y=7;y<=10;y++){
		mvprintw(y,32,"%c",wall);
	}

	for(int y=12;y<=29;y++){
		mvprintw(y,32,"%c",wall);
	}

	for(int x=1;x<=56;x++){
		mvprintw(5,x,"%c",wall);
	}

	for(int x=1;x<=32;x++){
		mvprintw(7,x,"%c",wall);
	}

	for(int x=34;x<=56;x++){
		mvprintw(25,x,"%c",wall);
	}

	for(int x=36;x<=56;x++){
		mvprintw(25,x,"%c",wall);
	}

	for(int y=6;y<=25;y++){
		mvprintw(y,73,"%c",wall);
	}

	for(int x=73;x<=79;x++){
		mvprintw(6,x,"%c",wall);
	}

	//Dead end 1
	for(int y=21;y<=26;y++){
		mvprintw(y,20,"%c",wall);
	}
	for(int y=12;y<=29;y++){
		mvprintw(y,22,"%c",wall);
	}

	//Dead end 2
	for(int x=34;x<=56;x++){
		mvprintw(7,x,"%c",wall);
	}
	for(int y=1;y<=25;y++){
		mvprintw(y,56,"%c",wall);
	}

	//Final obstacle
	for(int x=56;x<=72;x++){
		mvprintw(21,x,"%c",wall);
	}
	for(int x=56;x<=72;x++){
		mvprintw(17,x,"%c",wall);
	}
	for(int x=56;x<=72;x++){
		mvprintw(13,x,"%c",wall);
	}
	for(int x=56;x<=72;x++){
		mvprintw(9,x,"%c",wall);
	}

	//Spaces to move through during final obstacle
	mvaddch(21,65,' ');
	mvaddch(17,58,' ');
	mvaddch(14,56,' ');
	mvaddch(12,56,' ');
	mvaddch(9,69,' ');

	//Level exit
	mvprintw(3,77,"%c",exit);
	for(int y=1; y<=5; y++){
		mvprintw(y,74,"%c",door);
	}

	for(int x=74; x<=79; x++){
		mvprintw(5,x,"%c",door);
	}
}
