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

BFS_solution BFS_next(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], int ghostX, int ghostY, int pacmanX, int pacmanY);

PacStruct BlinkyAI(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman, PacStruct ghosts[NUMBER_OF_GHOSTS], int currentGhostIndex);

BFS_solution PinkyAI_logic(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], int ghostX, int ghostY, int pacmanX, int pacmanY);

PacStruct PinkyAI(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman, PacStruct ghosts[NUMBER_OF_GHOSTS], int currentGhostIndex);

PacStruct InkyAI(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman, PacStruct ghosts[NUMBER_OF_GHOSTS], int currentGhostIndex);

PacStruct ClydeAI(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman, PacStruct ghosts[NUMBER_OF_GHOSTS], int currentGhostIndex);

int isDot(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], int pacmanX, int pacmanY);

int maximum(int a, int b, int c, int d);

int minimum(int a, int b, int c, int d);

PacStruct PacmanDemo(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman, PacStruct ghosts[NUMBER_OF_GHOSTS]);

#endif // !_ghosts_h_
