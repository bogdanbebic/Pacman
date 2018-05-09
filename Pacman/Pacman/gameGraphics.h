#ifndef _gameGraphics_h_
#define _gameGraphics_h_

#include <stdio.h>
#include <Windows.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "gameMap.h"

#include "pacStruct.h"
#include "game.h"

void printInitMap(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP]);

void updateMap(int map[HEIGHT_OF_MAP][HEIGHT_OF_MAP], PacStruct pacman, PacStruct ghosts[NUMBER_OF_GHOSTS]);

#endif
