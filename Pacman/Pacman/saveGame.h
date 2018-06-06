#pragma once
#ifndef _saveGame_h_
#define _saveGame_h_

#include "pacStruct.h"
#include "highscores.h"
#include "gameMap.h"

/*!
*	\brief struct which contains info about in game data
*/
typedef struct SaveGameStruct {
	enum DifficultySpeed difficulty;
	int delay;
	int level;
	int livesCount;
	Highscore currentScore;
	int isStartOfNewGame;
	PacStruct home;
	int map[HEIGHT_OF_MAP][WIDTH_OF_MAP];
	PacStruct pacman;
	PacStruct ghosts[NUMBER_OF_GHOSTS];
	int pacDotCount;
	int srbendaMod;
	int isPowerPelletEaten;
	int timer_tick;
	int timer_tick_POWER_PELLET;
} SaveGame;

#endif // !_saveGame_h_
