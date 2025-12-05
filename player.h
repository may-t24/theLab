/********************************************************
 * @file player.h                                       *
 * @Public Interface of the player                      *
 * @author CMPT201 Group 2                              *
 * @date Nov. 27, 2025                                  *
 ********************************************************/


#ifndef PLAYER_H
#define PLAYER_H

/**
* @brief This Struct defines the player
*/
typedef struct{
        int x; /**< initial x of the player */
	int y; /**< initial y of the player */
	char symbol; /**< character symbol representing the character*/
}Player;

/**
* This function creates a new player at the provided coordinate
* @param x is an integer representing the initial x of the player
* @param y is an integer representing the initial y of the player
* @return the created player as type Player
*/
Player createPlayer(char symbol,int x, int y);


/**
* This function simply draws the Player
* @param p1 is the Player
* @return Player updated and drawn
*/
void drawPlayer(Player p1);

/**
* This function moves the player to the right by 1
* @param p1 is the Player
* @return Player with an updated position
*/
Player moveRight(Player p1);

/**
* This function moves the player to the left by 1 
* @param p1 is the Player
* @return Player with an updated position
*/
Player moveLeft(Player p1);

/**
* This function moves the player to the up by 1 
* @param p1 is the Player
* @return Player with an updated position
*/
Player moveUp(Player p1);

/**
* This function moves the player to the down by 1 
* @param p1 is the Player
* @return Player with an updated position
*/
Player moveDown(Player p1);
#endif
