#ifndef _pauseMenuGraphics_h_
#define _pauseMenuGraphics_h_

#include <stdio.h>
#include <Windows.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "game.h"
#include "gameMap.h"

#define MAP_SDL_NUMBERS(x) ((x) - SDLK_0 + '0')
#define MAP_SDL_LETTERS(x) ((x) - SDLK_a + 'a')

enum PauseMenuOptions { continueWithGame, mainMenu, finishGame, numberOfPauseMenuOptions, quitInGame };

enum PauseMenuOptions ActivatePauseMenu(int difficulty);

void initPauseMenuTextures();

void destroyPauseMenuTextures();

typedef struct PauseMenuTexturesStruct {
	SDL_Texture * whiteTextures[numberOfPauseMenuOptions];
	SDL_Texture * yellowTextures[numberOfPauseMenuOptions];
	SDL_Texture * pacmanTexture;
}PauseMenuTextures;

PauseMenuTextures pauseMenuTextureManager;

#endif