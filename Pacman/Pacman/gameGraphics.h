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

void updateLivesBox(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], int numberOfLivesTiles, int livesCount);

void printInitMap(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman);

void updateMap(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman, PacStruct ghosts[NUMBER_OF_GHOSTS], int delay, int timer_tick);

void deletePacmanGhost(PacStruct pacStruct);

void drawInitPacman(PacStruct pacman);

#endif
