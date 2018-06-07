#ifndef _gameGraphics_h_
#define _gameGraphics_h_

/*!	\file gameGraphics.h
*	\brief Contains declarations and constants for gameplay graphics
*/

#include <stdio.h>
#include <Windows.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "gameMap.h"
#include "highscores.h"
#include "pacStruct.h"
#include "game.h"

/*!
*	\brief Length of score box which is drawn on the screen
*/
#define LEN_OF_SCORE_BOX 50

void initGameTextures();

void destroyGameTextures();

void updateScoreBox(Highscore currentScore);

void updateLevelBox(int level);

void updateLivesBox(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], int numberOfLivesTiles, int livesCount);

void printInitMap(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman, int srbendaMod, int newLevel);

void updatePacman(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman, int timer_tick, int srbendaMod);

void updateGhosts(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct ghosts[NUMBER_OF_GHOSTS], int timer_tick, int srbendaMod, PacStruct pacman, enum direction lastPacmanDirection, int lastMovingTimerTick);

#endif
