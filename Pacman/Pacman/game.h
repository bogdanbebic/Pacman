#ifndef _game_h_
#define _game_h_

#include "ghosts.h"


#include "graphicsMenu.h"
#include "pacStruct.h"
#include "gameGraphics.h"

#define WIDTH_SCREEN 600
#define HEIGHT_SCREEN 400

void wallCheckAndMove(int [HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct *);

void initTempMap(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], int tempMap[HEIGHT_OF_MAP][WIDTH_OF_MAP]);

void playNewGame(enum DifficultySpeed difficulty);

void initGhostsPostitions(PacStruct ghosts[NUMBER_OF_GHOSTS]);

void initPacmanPosition(PacStruct *pacman);

int pacmanGhostCheck(PacStruct pacman, PacStruct ghost);

int countPacDots(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP]);

typedef struct ScreenStruct {
	unsigned int width;
	unsigned int height;
	const char* name;
	SDL_Window* window;
	SDL_Renderer* renderer;
} Screen;

typedef struct GameStruct {
	SDL_bool isRunning;
	Screen screen;
	void(*init)();
	void(*quit)();
} Game;

Game game;

#endif