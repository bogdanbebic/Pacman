#pragma once
#ifndef _saveGame_h_
#define _saveGame_h_

#include "pacStruct.h"
#include "highscores.h"
#include "gameMap.h"

typedef struct SaveGameStruct {
	enum DifficultySpeed difficulty;
	int delay;
	int level;
	int livesCount;
	int numberOfLivesTiles;
	Highscore currentScore;
	int isStartOfNewGame;
	PacStruct home;
	int map[HEIGHT_OF_MAP][WIDTH_OF_MAP];
	PacStruct pacman;
	PacStruct ghosts[NUMBER_OF_GHOSTS];
	int pacDotCount;
} SaveGame;

#endif // !_saveGame_h_
