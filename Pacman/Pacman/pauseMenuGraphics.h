#ifndef _pauseMenuGraphics_h_
#define _pauseMenuGraphics_h_

#include <stdio.h>
#include <Windows.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "game.h"
#include "gameMap.h"

enum PauseMenuOptions { continueWithGame, mainMenu, finishGame, numberOfPauseMenuOptions, quitInGame};

enum PauseMenuOptions ActivatePauseMenu(int difficulty);

void initPauseMenuTextures();

typedef struct PauseMenuTexturesStruct {
	SDL_Texture * whiteTextures[numberOfPauseMenuOptions];
	SDL_Texture * yellowTextures[numberOfPauseMenuOptions];
	SDL_Texture * pacmanTexture;
}PauseMenuTextures;

PauseMenuTextures pauseMenuTextureManager;

#endif