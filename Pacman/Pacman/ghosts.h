#pragma once

#ifndef _ghosts_h_
#define _ghosts_h_

#include "pacStruct.h"
#include "gameMap.h"

/*
*	OVAKO  TREBA DA IZGLEDA
*	DEKLARACIJA ZA FUNKCIJE DUHOVA
*/
// PacStruct ghostDirectionFunction(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman, PacStruct ghosts[NUMBER_OF_GHOSTS], int currentGhostIndex);

/* OVDE NAPISATI MININE DUHOVE, SAMO SA OVOM DEKLARACIJOM */


PacStruct BlinkyAI(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman, PacStruct ghosts[NUMBER_OF_GHOSTS], int currentGhostIndex);

PacStruct PinkyAI(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman, PacStruct ghosts[NUMBER_OF_GHOSTS], int currentGhostIndex);

PacStruct InkyAI(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman, PacStruct ghosts[NUMBER_OF_GHOSTS], int currentGhostIndex);

PacStruct ClydeAI(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman, PacStruct ghosts[NUMBER_OF_GHOSTS], int currentGhostIndex);

#endif // !_ghosts_h_
