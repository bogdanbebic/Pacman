#ifndef _gameGraphics_h_
#define _gameGraphics_h_

#include <stdio.h>
#include <Windows.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "gameMap.h"

#include "pacStruct.h"
#include "game.h"

#define LEN_OF_SCORE_BOX 15

void updateScoreBox(int currentScore);

void updateLivesBox(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], int numberOfLivesTiles, int livesCount);

void printInitMap(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman, int pacDotCount);

enum GameMode updateScoreAndGameMode(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman, int * pacDotCount, int * currentScore);

void updateMap(int Map[HEIGHT_OF_MAP][HEIGHT_OF_MAP], PacStruct pacman, PacStruct ghosts[NUMBER_OF_GHOSTS], int delay);

void deletePacmanGhost(int iPosition, int jPosition);

#endif
