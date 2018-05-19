#ifndef _graphicsMenu_h_
#define _graphicsMenu_h_

#include <stdio.h>
#include <Windows.h>
#include <SDL.h>
#include <SDL_ttf.h>

#include "game.h"

#include "gameMap.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_SCALE 1
#define SCREEN_NAME "Pacman"
#define MAX_STRING_LINE 20


enum MenuOptions { demoGame, newGame, continueGame, highscore, settings, credits, quitGame, numberOfMenuOptions };

void gameInit();

void gameQuit();

void getScreenResolution(int *width, int *height);

void initTexturesForMenu(SDL_Texture * menuTextureWhite[], SDL_Texture * menuTextureYellow[], SDL_Texture ** PacmanTexture);

void createHeading();

void printMenu(enum menuOptions currentMenuOption, SDL_Texture * menuTextureWhite[], SDL_Texture * menuTextureYellow[], SDL_Texture * PacmanTexture);

SDL_Texture* Message[numberOfMenuOptions];

#endif