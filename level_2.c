//Group 2 - Assignment 2
#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include "player.h"
#include "splash_art.h"
#include "level_2.h"

int level_2(){
	int input;
 	//represents the object the player needs to collect.  change start_count in the header file depending on your key count
        int key_count = start_count;
	//Tracks the location of each key.  Second array is the coord as (x,y)
	int key_location[start_count][2] = { 
		{6,18},
		{22,24},
		{26,20},
		{48,11},
		{73,18},
		{77,10} 
	};
	//NPC not a struct since its fairly similar to Player struct without much differences
	Player NPC,p1;
	NPC = createPlayer('?',68,1);
	//The npcs dialogue when you interact with him.  Replace example text with your own text
	char npc_dialogue[] ="I'm so close to the exit...";
	int npc_timer= 0;
        p1 = createPlayer('@',2,27);
	//draws the objects and level structure for the level
        refresh_level2(p1,NPC,key_location);
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
			refresh_level2(p1,NPC,key_location);
                } else if (input == 'p'){
			clear();
			pause_art();
			refresh_level2(p1,NPC,key_location);
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
			//Door coords to get removed once keys are collected
			mvaddch(1,70,' ');
		        mvaddch(1,75,' ');
        		mvaddch(2,75,' ');
                        mvaddch(3,75,' ');
                        mvaddch(4,75,' ');
                        mvaddch(5,75,' ');

	                mvprintw(6,83,"DOOR IS OPEN GOGOGO!");
		}
        	mvprintw(5,83,"Keys Left: %d",key_count);
		mvprintw(4,83,"Total Keys: %d",start_count);
                refresh();
        }

}
void refresh_level2(Player p1, Player NPC,int key_location[start_count][2]){
        //Draws Wall,Doors & Exit
	draw_level2();
	//Draw UI
	mvprintw(2,83,"LEVEL 2");
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
//Level design walls
void draw_level2(){
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
	//Layout is row by row
	mvprintw(1,70,"%c",door);
	mvprintw(1,75,"%c",door);
	for(int i = 2; i <= 71; i++){
		mvprintw(2,i,"%c",wall);

	}
	mvprintw(2,75,"%c",door);
	mvprintw(2,78,"%c",exit);
	mvprintw(3,2,"%c",wall);
        mvprintw(3,11,"%c",wall);
        mvprintw(3,14,"%c",wall);
        mvprintw(3,38,"%c",wall);
	for(int i =50; i <=55;i++){
        	mvprintw(3,i,"%c",wall);
	}
        mvprintw(3,59,"%c",wall);
	mvprintw(3,71,"%c",wall);
        mvprintw(3,75,"%c",door);
        mvprintw(4,2,"%c",wall);
        for(int i = 4; i <=11; i++){
		mvprintw(4,i,"%c",wall);
	}
        mvprintw(4,14,"%c",wall);
	for(int i = 16; i<=21; i++){
	        mvprintw(4,i,"%c",wall);
	}
	for (int i =26; i<=38;i++){
	        mvprintw(4,i,"%c",wall);
	}
	for(int i = 40;i<=42;i++){
	        mvprintw(4,i,"%c",wall);
	}
        mvprintw(4,44,"%c",wall);
        mvprintw(4,46,"%c",wall);
        mvprintw(4,55,"%c",wall);
	for(int i=59;i<=67;i++){
	        mvprintw(4,i,"%c",wall);
	}
        mvprintw(4,71,"%c",wall);
        mvprintw(4,75,"%c",door);
        mvprintw(5,2,"%c",wall);
        mvprintw(5,14,"%c",wall);
        mvprintw(5,16,"%c",wall);
        for(int i=21;i<=23;i++){
	        mvprintw(5,i,"%c",wall);
	}
	mvprintw(5,26,"%c",wall);
        mvprintw(5,38,"%c",wall);
        mvprintw(5,40,"%c",wall);
        mvprintw(5,42,"%c",wall);
        mvprintw(5,44,"%c",wall);
	for(int i=46;i<=50;i++){
	        mvprintw(5,i,"%c",wall);
	}
        mvprintw(5,52,"%c",wall);
        mvprintw(5,53,"%c",wall);
        mvprintw(5,55,"%c",wall);
        mvprintw(5,59,"%c",wall);
        mvprintw(5,67,"%c",wall);
        mvprintw(5,71,"%c",wall);
        mvprintw(5,75,"%c",door);
        mvprintw(6,2,"%c",wall);
        for(int i=4;i<=9;i++){
	        mvprintw(6,i,"%c",wall);
	}
	for(int i=11;i<=14;i++){
	        mvprintw(6,i,"%c",wall);
	}
	mvprintw(6,16,"%c",wall);
        mvprintw(6,18,"%c",wall);
        mvprintw(6,19,"%c",wall);
        mvprintw(6,23,"%c",wall);
        mvprintw(6,26,"%c",wall);
	for(int i=28;i<=36;i++){
	        mvprintw(6,i,"%c",wall);
	}
        mvprintw(6,38,"%c",wall);
        mvprintw(6,40,"%c",wall);
        mvprintw(6,42,"%c",wall);
        mvprintw(6,44,"%c",wall);
        mvprintw(6,46,"%c",wall);
        mvprintw(6,50,"%c",wall);
        mvprintw(6,52,"%c",wall);
        mvprintw(6,53,"%c",wall);
	for(int i=55;i<=59;i++){
	        mvprintw(6,i,"%c",wall);
	}
	for(int i=61;i<=65;i++){
	        mvprintw(6,i,"%c",wall);
	}
        mvprintw(6,67,"%c",wall);
        mvprintw(6,71,"%c",wall);
	for(int i=75;i<=79;i++){
		mvprintw(6,i,"%c",wall);
        }
	//Changed my approach to loading level since above method was taking too much time to add
	for(int y=7;y<=22;y++){
	        mvprintw(y,2,"%c",wall);
	}
	for(int x=3;x<=8;x++){
	        mvprintw(22,x,"%c",wall);
	}
	for(int y=23;y<=26;y++){
	        mvprintw(y,8,"%c",wall);
	}
	for(int x=1;x<=6;x++){
	        mvprintw(24,x,"%c",wall);
	}
	mvprintw(25,6,"%c",wall);
        mvprintw(26,6,"%c",wall);
	for(int x=4;x<=9;x++){
		mvprintw(7,x,"%c",wall);
	}
        mvprintw(8,9,"%c",wall);
        mvprintw(9,9,"%c",wall);
	for(int x=4;x<=8;x++){
	        mvprintw(9,x,"%c",wall);
	}
	for(int y=10;y<=20;y++){
	        mvprintw(y,4,"%c",wall);
	}
	for(int x=5;x<=8;x++){
	        mvprintw(20,x,"%c",wall);
	}
	for(int y=13;y<=19;y++){
	        mvprintw(y,8,"%c",wall);
	}
	for(int x=9;x<=16;x++){
	        mvprintw(13,x,"%c",wall);
	}
	for(int y=7;y<=12;y++){
	        mvprintw(y,16,"%c",wall);
	}
        mvprintw(7,11,"%c",wall);
        mvprintw(8,11,"%c",wall);
	for(int x=12;x<=14;x++){
	        mvprintw(8,x,"%c",wall);
	}
	for(int y=10;y<=12;y++){
	        mvprintw(y,11,"%c",wall);
	}
        mvprintw(13,10,"%c",wall);
        mvprintw(6,52,"%c",wall);
	for(int y=10;y<=12;y++){
	        mvprintw(y,14,"%c",wall);
	}
	for(int y=18;y<=29;y++){
	        mvprintw(y,10,"%c",wall);
	}
        mvprintw(18,11,"%c",wall);
	for(int x=10;x<=13;x++){
	        mvprintw(x,16,"%c",wall);
	}
	for(int y=17;y<=22;y++){
	        mvprintw(y,13,"%c",wall);
	}
        mvprintw(22,14,"%c",wall);
	for(int x=14;x<=19;x++){
	        mvprintw(17,x,"%c",wall);
	}
	for(int y=18;y<=24;y++){
	        mvprintw(y,16,"%c",wall);
	}
	for(int x=13;x<=15;x++){
	        mvprintw(24,x,"%c",wall);
	}
	for(int y=25;y<=27;y++){
	        mvprintw(y,13,"%c",wall);
	}
	for(int y=24;y<=27;y++){
	        mvprintw(y,17,"%c",wall);
	}
        mvprintw(27,16,"%c",wall);
        mvprintw(27,15,"%c",wall);
        mvprintw(26,15,"%c",wall);
	for(int y=18;y<=29;y++){
	        mvprintw(y,19,"%c",wall);
	}
	for(int x=20;x<=24;x++){
	        mvprintw(27,x,"%c",wall);
	}
	for(int x=10;x<=19;x++){
	        mvprintw(15,x,"%c",wall);
	}
	for(int y=7;y<=14;y++){
	        mvprintw(y,18,"%c",wall);
	        mvprintw(y,19,"%c",wall);
	}
	for(int y=6;y<=10;y++){
		mvprintw(y,21,"%c",wall);
		mvprintw(y,2,"%c",wall);

	}
	for(int x=21;x<=24;x++){
		mvprintw(11,x,"%c",wall);
	}
	mvprintw(12,24,"%c",wall);
	mvprintw(13,24,"%c",wall);
	for(int x=21;x<=23;x++){
		mvprintw(13,x,"%c",wall);
	}
	for(int y=13;y<25;y++){
		mvprintw(y,21,"%c",wall);
	}
	for(int x=21;x<=28;x++){
		mvprintw(25,x,"%c",wall);
	}
	for(int x=23;x<=28;x++){
		mvprintw(24,x,"%c",wall);
	}
	for(int y=15;y<=23;y++){
		mvprintw(y,23,"%c",wall);
	}
	for(int x=24;x<=33;x++){
		mvprintw(15,x,"%c",wall);
	}
	for(int y=9;y<=14;y++){
		mvprintw(y,33,"%c",wall);
	}
	for(int y=9;y<=12;y++){
		mvprintw(y,32,"%c",wall);
	}
	for(int x=26;x<=31;x++){
		mvprintw(12,x,"%c",wall);
	}
	for(int x=30;x<=36;x++){
		mvprintw(7,x,"%c",wall);
	}
	for(int y=7;y<=11;y++){
		mvprintw(y,26,"%c",wall);
	}
	for(int y=7;y<=9;y++){
		mvprintw(y,28,"%c",wall);
		mvprintw(y,30,"%c",wall);
	}
	for(int x=28;x<=30;x++){
		mvprintw(10,x,"%c",wall);
	}
	for(int y=8;y<=18;y++){
		mvprintw(y,35,"%c",wall);
		mvprintw(y,36,"%c",wall);
	}
	mvprintw(18,34,"%c",wall);
	mvprintw(17,34,"%c",wall);
	for(int y=19;y<=27;y++){
		mvprintw(y,36,"%c",wall);
	}
	mvprintw(27,35,"%c",wall);
	mvprintw(27,34,"%c",wall);
	mvprintw(27,32,"%c",wall);
	mvprintw(28,32,"%c",wall);
	mvprintw(29,32,"%c",wall);
	for(int x=26;x<=30;x++){
		mvprintw(27,x,"%c",wall);
	}
	for(int y=22;y<=26;y++){
		mvprintw(y,30,"%c",wall);
	}
	for(int x=31;x<=34;x++){
		mvprintw(23,x,"%c",wall);
	}
	for(int x=31;x<=35;x++){
		mvprintw(25,x,"%c",wall);
	}
	for(int x=25;x<=29;x++){
		mvprintw(22,x,"%c",wall);
	}
	for(int y=17;y<=21;y++){
		mvprintw(y,25,"%c",wall);
	}
	for(int x=26;x<=32;x++){
		mvprintw(17,x,"%c",wall);
		mvprintw(19,x,"%c",wall);
	}
	mvprintw(20,32,"%c",wall);
	mvprintw(21,32,"%c",wall);
	mvprintw(21,33,"%c",wall);
	mvprintw(21,34,"%c",wall);
	mvprintw(20,34,"%c",wall);
	for(int x=37;x<=43;x++){
		mvprintw(25,x,"%c",wall);
	}
	for(int y=26;y<=29;y++){
		mvprintw(y,43,"%c",wall);
	}
	mvprintw(28,42,"%c",wall);
	mvprintw(26,40,"%c",wall);
	mvprintw(27,40,"%c",wall);

	mvprintw(29,38,"%c",wall);
	mvprintw(28,38,"%c",wall);
	mvprintw(27,38,"%c",wall);
	for(int y=7;y<=23;y++){
		mvprintw(y,38,"%c",wall);
	}
	for(int x=39;x<=44;x++){
		mvprintw(16,x,"%c",wall);
	}
	for(int y=17;y<=19;y++){
		mvprintw(y,44,"%c",wall);
	}
	for(int x=40;x<=48;x++){
		mvprintw(20,x,"%c",wall);
	}
	mvprintw(19,40,"%c",wall);
	mvprintw(18,40,"%c",wall);
	mvprintw(18,42,"%c",wall);
	mvprintw(17,42,"%c",wall);
	mvprintw(7,39,"%c",wall);
	for(int x=39;x<=53;x++){
		mvprintw(23,x,"%c",wall);
	}
	for(int y=16;y<=20;y++){
		mvprintw(y,52,"%c",wall);
		mvprintw(y,53,"%c",wall);
	}
	mvprintw(20,51,"%c",wall);
	mvprintw(20,50,"%c",wall);
	mvprintw(21,53,"%c",wall);
	mvprintw(22,53,"%c",wall);
	for(int y=10;y<=14;y++){
	        mvprintw(y,42,"%c",wall);
	        mvprintw(y,40,"%c",wall);
	}
        mvprintw(10,41,"%c",wall);
	for(int x=43;x<=45;x++){
	        mvprintw(14,x,"%c",wall);
	}
	for(int y=14;y<=16;y++){
	        mvprintw(y,46,"%c",wall);
	        mvprintw(y,48,"%c",wall);
	}
        mvprintw(16,47,"%c",wall);
	for(int x=42;x<=44;x++){
	        mvprintw(7,x,"%c",wall);
	}
	for(int x=44;x<=50;x++){
	        mvprintw(8,x,"%c",wall);
	}
        mvprintw(7,50,"%c",wall);
	for(int y=9;y<=12;y++){
	        mvprintw(y,46,"%c",wall);
	}
	for(int x=47;x<=53;x++){
	        mvprintw(12,x,"%c",wall);
	}
        mvprintw(11,50,"%c",wall);
        mvprintw(10,50,"%c",wall);
        mvprintw(11,53,"%c",wall);
        mvprintw(10,53,"%c",wall);
	for(int y=7;y<=9;y++){
	        mvprintw(y,52,"%c",wall);
	        mvprintw(y,53,"%c",wall);
	}
	for(int x=54;x<=57;x++){
	        mvprintw(8,x,"%c",wall);
	}
	for(int y=9; y<=15;y++){
	        mvprintw(y,57,"%c",wall);
	}
	for(int x=46;x<=50;x++){
	        mvprintw(18,x,"%c",wall);
	}
	for(int y=14;y<=17;y++){
	        mvprintw(y,50,"%c",wall);
	}
	for(int x=50;x<=54;x++){
	        mvprintw(14,x,"%c",wall);
	}
	for(int y=10;y<=23;y++){
	        mvprintw(y,55,"%c",wall);
	}
        mvprintw(17,56,"%c",wall);
        mvprintw(23,56,"%c",wall);
        mvprintw(23,57,"%c",wall);
	for(int y=23;y<=26;y++){
	        mvprintw(y,58,"%c",wall);
	        mvprintw(y,59,"%c",wall);
	}
	for(int y=7;y<=22;y++){
	        mvprintw(y,59,"%c",wall);
	}
        mvprintw(20,58,"%c",wall);
        mvprintw(20,57,"%c",wall);
        mvprintw(17,58,"%c",wall);
	for(int x=45;x<=56;x++){
	        mvprintw(25,x,"%c",wall);
	}
        mvprintw(26,46,"%c",wall);
        mvprintw(28,46,"%c",wall);
        mvprintw(28,47,"%c",wall);
        mvprintw(29,47,"%c",wall);
        mvprintw(26,49,"%c",wall);
        mvprintw(27,49,"%c",wall);
	for(int y=27;y<=29;y++){
        	mvprintw(27,51,"%c",wall);
	}
	for(int x=52;x<=54;x++){
	        mvprintw(27,x,"%c",wall);
	}
	for(int y=26;y<=28;y++){
	        mvprintw(y,56,"%c",wall);
	}
	for(int x=57;x<=73;x++){
	        mvprintw(28,x,"%c",wall);
	}
        mvprintw(29,65,"%c",wall);
	for(int y=7;y<=27;y++){
	        mvprintw(y,61,"%c",wall);
	}
	for(int y=7;y<=10;y++){
	        mvprintw(y,65,"%c",wall);
	}
	for(int y=8;y<=10;y++){
	        mvprintw(y,63,"%c",wall);
	}
        mvprintw(10,64,"%c",wall);
	for(int y=7; y<=12;y++){
	        mvprintw(y,67,"%c",wall);
	}
	mvprintw(12,63,"%c",wall);
        mvprintw(12,64,"%c",wall);
        mvprintw(14,63,"%c",wall);
        mvprintw(14,64,"%c",wall);
	for(int y=12;y<=17;y++){
	        mvprintw(y,64,"%c",wall);
	}
        mvprintw(17,62,"%c",wall);
        mvprintw(17,63,"%c",wall);
        mvprintw(17,64,"%c",wall);
	for(int y=14;y<=19;y++){
	        mvprintw(y,67,"%c",wall);
	}
        for(int x=63;x<=66;x++){
	        mvprintw(19,x,"%c",wall);
	}
	for(int y=20;y<=26;y++){
	        mvprintw(y,63,"%c",wall);
	}
	for(int x=64;x<=74;x++){
	        mvprintw(26,x,"%c",wall);
	}
	for(int y=17;y<=26;y++){
	        mvprintw(y,75,"%c",wall);
	}
        mvprintw(17,72,"%c",wall);
        mvprintw(17,73,"%c",wall);
        mvprintw(17,74,"%c",wall);
        mvprintw(21,73,"%c",wall);
        mvprintw(21,74,"%c",wall);
	for(int y=7;y<=24;y++){
	        mvprintw(y,71,"%c",wall);
	}
        mvprintw(23,72,"%c",wall);
        mvprintw(23,73,"%c",wall);
	for(int y=21;y<=24;y++){
        	mvprintw(y,69,"%c",wall);
	        mvprintw(y,67,"%c",wall);
	        mvprintw(y,65,"%c",wall);
	}
        mvprintw(21,70,"%c",wall);
        mvprintw(21,66,"%c",wall);
        mvprintw(24,68,"%c",wall);
        mvprintw(28,75,"%c",wall);
        mvprintw(28,76,"%c",wall);
	for(int y=15;y<=28;y++){
	        mvprintw(y,77,"%c",wall);
	}
	for(int x=73;x<=76;x++){
	        mvprintw(15,x,"%c",wall);
	}
	for(int y=7;y<=14;y++){
	        mvprintw(y,73,"%c",wall);
	}
        mvprintw(7,74,"%c",wall);
        mvprintw(7,25,"%c",wall);
	for(int y=9;y<=12;y++){
	        mvprintw(y,75,"%c",wall);
	}
	for(int x=76;x<=79;x++){
	        mvprintw(12,x,"%c",wall);
	}
}
