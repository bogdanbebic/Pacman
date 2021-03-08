#ifndef _pauseMenuGraphics_h_
#define _pauseMenuGraphics_h_

/*!	\file pauseMenuGraphics.h
 *	\brief Contains declarations and constants for pause menu graphics
 */

#include <stdio.h>
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

/*!	\brief Activates pause menu
 *
 *	Activates pause menu on the game screen by
 *	handling all the user related input in the
 *	menu itself and prints the newly activated menu
 *   on the game screen
 *	\param difficulty difficulty of the game
 */
enum PauseMenuOptions ActivatePauseMenu(int difficulty);

/*!
 *	\brief Initializes the textures for pause menu
 */
void initPauseMenuTextures();

/*
 *	\brief Destroys all the textures used in the pause menu
 */
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