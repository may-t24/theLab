//Group 2 - Assignment 2
#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include "player.h"
#include "splash_art.h"
#include "level_template.h"
/*This is just a template of what a level*.c could look like.   Needs to be expanded more
This is where you would add the maze layout and the objects.  Basically think about how the level would look like and translate it into here
*/
int level_template(){
	int input;
 	//represents the object the player needs to collect.  change start_count in the header file depending on your key count
        int key_count = start_count;
	//Tracks the location of each key.  Second array is the coord as (x,y)
	int key_location[start_count][2] = { 
		{10,10},
		{10,20},
		{20,10} 
	};
	//NPC not a struct since its fairly similar to Player struct without much differences
	Player NPC,p1;
	NPC = createPlayer('?',10,15);
	//The npcs dialogue when you interact with him.  Replace example text with your own text
	char npc_dialogue[] ="Hello Player";
	int npc_timer= 0;
        p1 = createPlayer('@',10,25);
	//draws the objects and level structure for the level
        refresh_level(p1,NPC,key_location);
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
			refresh_level(p1,NPC,key_location);
                } else if (input == 'p'){
			clear();
			pause_art();
			refresh_level(p1,NPC,key_location);
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
			//REMINDER TO PUT YOUR DOOR COORDS HERE
			mvaddch(25,35,' ');
		        mvaddch(26,35,' ');
        		mvaddch(27,35,' ');
	                mvprintw(6,83,"DOOR IS OPEN GOGOGO!");
		}
        	mvprintw(5,83,"Keys Left: %d",key_count);
		mvprintw(4,83,"Total Keys: %d",start_count);
                refresh();
        }

}
void refresh_level(Player p1, Player NPC,int key_location[start_count][2]){
        // Draws Wall,Doors & Exit
	draw_level();
	//Draw UI
	mvprintw(2,83,"LEVEL TEST");
        mvprintw(6,83,"Door is Closed");
        mvprintw(32,0,"Dialogue:");
        mvprintw(8,83,"CONTROLS:");
        mvprintw(9,83,"Arrow Keys - Move");
        mvprintw(10,83,"I - Interact");
	mvprintw(11,83,"P - Pause");
        mvprintw(12,83,"Q - Quit");
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
//PUT YOUR LEVEL DESIGN WALLS HERE
//Game Objects should still be placed in the regular level function
void draw_level(){
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
	/*PUT YOUR LEVEL LAYOUT HERE. 
	REMINDER THAT POSITIVE Y GOES DOWN
        ALSO PUT THE DOOR LOCATIONS IN KEY_COUNT == 0 CHECK
	*/
	mvprintw(25,30,"%c",wall);
        mvprintw(26,30,"%c",wall);
        mvprintw(27,30,"%c",wall);
	mvprintw(25,35,"%c",door);
        mvprintw(26,35,"%c",door);
        mvprintw(27,35,"%c",door);
        mvprintw(26,40,"%c",exit);


}
