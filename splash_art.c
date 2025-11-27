//Group 2 - Assignment2
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>

//The splash screen that will display when opening the game
int start_art(){

initscr();

addstr("\t---------   |    |   -------        |             /\       |------  \n");
addstr("\t    |       |    |   |              |            /  \      |      | \n");
addstr("\t    |       |----|   |-----         |           /    \     |------  \n");
addstr("\t    |       |    |   |              |          /------\    |      | \n");
addstr("\t    |       |    |   |------        |------   /        \   |------  \n\n\n");

addstr("\t\tPress any key to start game.\n");
addstr("\t\tPress q to quit.");

refresh();

//If user input is "q", return 1 so that the quit screen can be called
if (getch() == "q") {
	return 1;
}

return 0;

}

//Splash screen for reaching the end of level 2
int end_art(){

initscr();

addstr("\t\     /   /------\   |      |        |      |   -------   |\    |\n");
addstr("\t \   /    |      |   |      |        |      |      |      | \   |\n");
addstr("\t  \ /     |      |   |      |        |  /\  |      |      |  \  |\n");
addstr("\t   |      |      |   |      |        | /  \ |      |      |   \ |\n");
addstr("\t   |      \------/   \------/        |/    \|   -------   |    \|\n\n\n");

addstr("\t\tPress any key to quit.");

refresh();

//Waits for user input before closing screen
getch();
return 0;
}

//Splash screen for when the player pauses the game
int pause_art(){

initscr();

addstr("\t|-----        /\       |     |   -------   |------   |-----\\n");
addstr("\t|     |      /  \      |     |   |         |         |     |\n");
addstr("\t|-----      /    \     |     |   -------   |-----    |     |\n");
addstr("\t|          /------\    |     |         |   |         |     |\n");
addstr("\t|         /        \   \-----/   -------   |------   |-----/\n\n\n");

addstr("\t\tPress any key to continue.");

refresh():

if (getch() == "q") {
	return 1;
}

return 0;

}

int quit_art(){

intiscr();

addstr("\t\t\t|--------------------------------|\n");
addstr("\t\t\t| Are you sure you want to quit? |\n");
addstr("\t\t\t|                                |\n");
addstr("\t\t\t|             y/n                |\n");
addstr("\t\t\t|--------------------------------|\n");

refresh();

if (getch() == "q") {
	return 1;
}

return 0;

}
