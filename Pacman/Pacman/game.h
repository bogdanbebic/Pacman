#ifndef _game_h_
#define _game_h_

#include "graphicsMenu.h"
#include "pacStruct.h"
#include "gameGraphics.h"

#define WIDTH_SCREEN 600
#define HEIGHT_SCREEN 400

void wallCheckAndMove(int [HEIGHT_OF_MAP][HEIGHT_OF_MAP], PacStruct *);

void playNewGame(enum DifficultySpeed difficulty);

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