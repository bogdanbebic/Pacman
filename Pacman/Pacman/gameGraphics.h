#ifndef _gameGraphics_h_
#define _gameGraphics_h_

#include <stdio.h>
#include <Windows.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "gameMap.h"
#include "highscores.h"
#include "pacStruct.h"
#include "game.h"

#define LEN_OF_SCORE_BOX 50

void initGameTextures();

void destroyGameTextures();

void updateScoreBox(Highscore currentScore);

void updateLevelBox(int level);

void updateLivesBox(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], int numberOfLivesTiles, int livesCount);

void printInitMap(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman, int srbendaMod, int newLevel);

void updatePacman(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman, int timer_tick, int srbendaMod);

void updateGhosts(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct ghosts[NUMBER_OF_GHOSTS], int timer_tick, int srbendaMod);

#endif
