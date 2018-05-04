#ifndef _graphicsMenu_h_
#define _graphicsMenu_h_

#include <stdio.h>
#include <Windows.h>
#include <SDL.h>


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_SCALE 1
#define SCREEN_NAME "Pacman"

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

void gameInit();

void gameQuit();

void getScreenResolution(int *width, int *height);

Game game;

#endif