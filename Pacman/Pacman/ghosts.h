#pragma once
#ifndef _ghosts_h_
#define _ghosts_h_

/*!	\file ghosts.h
 *	\brief Contains declarations for ghosts logics and AI
 */

#include "pacStruct.h"
#include "gameMap.h"
#include <stdlib.h>

/*!
 *	\brief Struct containing count of steps and direction of BFS solution
 */
typedef struct {
	int direction;
	int count;
} BFS_solution;

/*!
 *	\brief Finds next position using BFS
 *	\param Map map on which the game is played
 *	\param ghostX x coordinate of ghost
 *	\param ghostY y coordinate of ghost
 *	\param pacmanX x coordinate of pacman
 *	\param pacmanY y coordinate of pacman
 *	\return BFS_solution (direction and number of steps from ghost to pacman)
 */
BFS_solution BFS_next(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], int ghostX, int ghostY, int pacmanX, int pacmanY);

/*!
 *	\brief Finds next AI move for Blinky, Blinky's target tile is always Pac-Man�s current tile
 *	\param Map map on which the game is played
 *	\param pacman PacStruct containing info about pacman
 *	\param ghosts PacStruct array containing info about ghosts
 *	\param currentGhostIndex index in ghosts array which defines current ghost
 *	\return PacStruct containing next position of Blinky
 */
PacStruct BlinkyAI(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman, PacStruct ghosts[NUMBER_OF_GHOSTS], int currentGhostIndex);

/*!
 *	\brief Finds next AI move for Pinky. Pinky's target tile is always a tile that is next to Pac-Man's current tile
 *	\param Map map on which the game is played
 *	\param ghostX x coordinate of ghost
 *	\param ghostY y coordinate of ghost
 *	\param pacmanX x coordinate of pacman
 *	\param pacmanY y coordinate of pacma
 *	\return PacStruct containing next position of Pinky
 */
BFS_solution PinkyAI_logic(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], int ghostX, int ghostY, int pacmanX, int pacmanY);

/*!
 *	\brief Finds next AI move for Pinky. This function uses PinkyAI_logic function
 *	\param Map map on which the game is played
 *	\param pacman PacStruct containing info about pacman
 *	\param ghosts PacStruct array containing info about ghosts
 *	\param currentGhostIndex index in ghosts array which defines current ghost
 *	\return PacStruct containing next position of Pinky
 */
PacStruct PinkyAI(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman, PacStruct ghosts[NUMBER_OF_GHOSTS], int currentGhostIndex);

/*!
 *	\brief Finds next AI move for Inky. Inky's target tile is always a tile that is two tiles from the Pac-Man's current tile
 *	\param Map map on which the game is played
 *	\param pacman PacStruct containing info about pacman
 *	\param ghosts PacStruct array containing info about ghosts
 *	\param currentGhostIndex index in ghosts array which defines current ghost
 *	\return	PacStruct containing next position of Inky
 */
PacStruct InkyAI(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman, PacStruct ghosts[NUMBER_OF_GHOSTS], int currentGhostIndex);

/*!
 *	\brief Finds next AI move for Clyde. Clyde�s target tile is Pac-Man�s current tile if Clyde is ten tiles from the Pac-Man
 *	Otherwise, target tile is bottom left tile on the map.
 *	\param Map map on which the game is played
 *	\param pacman PacStruct containing info about pacman
 *	\param ghosts PacStruct array containing info about ghosts
 *	\param currentGhostIndex index in ghosts array which defines current ghost
 *	\return	PacStruct containing next position of Clyde
 */
PacStruct ClydeAI(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman, PacStruct ghosts[NUMBER_OF_GHOSTS], int currentGhostIndex);

/*!
 *	\brief Function finds the number of PAC_DOT/POWER_PELLET that surround current tile
 *	\param Map map on which the game is played
 *	\param pacmanX x coordinate of pacman
 *	\param pacmanY y coordinate of pacma
 *	\return	Number of neighbourhood tiles that contain PAC_DOT or POWER_PELLET
 */
int isDot(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], int pacmanX, int pacmanY);

/*!
 *	\brief Function finds the maximum of four numbers
 *	\param a one of the numbers of which to find max
 *	\param b one of the numbers of which to find max
 *	\param c one of the numbers of which to find max
 *	\param d one of the numbers of which to find max
 *	\return	Maximum of numbers
 */
int maximum(int a, int b, int c, int d);

/*!
 *	\brief Function finds the minimum of four numbers
 *	\param a one of the numbers of which to find min
 *	\param b one of the numbers of which to find min
 *	\param c one of the numbers of which to find min
 *	\param d one of the numbers of which to find min
 *	\return	Minimum of numbers
 */
int minimum(int a, int b, int c, int d);

/*!
 *	\brief Finds next AI move for Pac-Man. Pac-Man�s target tile is a tile that contains PAC_DOT or POWER_PELLET and that is opposite of ghosts.
 *	\param Map map on which the game is played
 *	\param pacman PacStruct containing info about pacman
 *	\param ghosts PacStruct array containing info about ghosts
 *	\return	PacStruct containing next position of Pac-Man
 */
PacStruct PacmanDemo(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman, PacStruct ghosts[NUMBER_OF_GHOSTS]);

#endif // !_ghosts_h_
