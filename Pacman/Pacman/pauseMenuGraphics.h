#ifndef _pauseMenuGraphics_h_
#define _pauseMenuGraphics_h_

/*!	\file pauseMenuGraphics.h
*	\brief Contains declarations and constants for pause menu graphics
*/

#include <stdio.h>
#include <Windows.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "game.h"
#include "gameMap.h"

/*!
*	\brief Maps SDLK number constants to ASCII number constants
*/
#define MAP_SDL_NUMBERS(x) ((x) - SDLK_0 + '0')

/*!
*	\brief Maps SDLK letter constants to ASCII letter constants
*/
#define MAP_SDL_LETTERS(x) ((x) - SDLK_a + 'a')

/*!
*	\brief Enum containing all pause manu options
*/
enum PauseMenuOptions { continueWithGame, mainMenu, finishGame, numberOfPauseMenuOptions, quitInGame };

enum PauseMenuOptions ActivatePauseMenu(int difficulty);

void initPauseMenuTextures();

void destroyPauseMenuTextures();

/*!
*	\brief Struct containing variables needed for pause menu textures
*/
typedef struct PauseMenuTexturesStruct {
	SDL_Texture * whiteTextures[numberOfPauseMenuOptions];
	SDL_Texture * yellowTextures[numberOfPauseMenuOptions];
	SDL_Texture * pacmanTexture;
}PauseMenuTextures;

/*!
*	\brief Global variable which contains pause menu textures information
*/
PauseMenuTextures pauseMenuTextureManager;

#endif