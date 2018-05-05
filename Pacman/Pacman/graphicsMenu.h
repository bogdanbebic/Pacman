#ifndef _graphicsMenu_h_
#define _graphicsMenu_h_

#include <stdio.h>
#include <Windows.h>
#include <SDL.h>
#include <SDL_ttf.h>


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_SCALE 1
#define SCREEN_NAME "Pacman"
#define MAX_STRING_LINE 20

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

enum MenuOptions { newGame, continueGame, highscore, settings, credits, quitGame, numberOfMenuOptions };

void gameInit();

void gameQuit();

void getScreenResolution(int *width, int *height);

void printMenu(enum menuOptions currentMenuOption);

Game game;

TTF_Font* font;

SDL_Texture* Message[numberOfMenuOptions];

#endif