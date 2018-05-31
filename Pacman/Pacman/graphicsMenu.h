#ifndef _graphicsMenu_h_
#define _graphicsMenu_h_

#include <stdio.h>
#include <Windows.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string.h>
#include <stdlib.h>

#include "game.h"
#include "pauseMenuGraphics.h"
#include "gameMap.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_SCALE 1
#define SCREEN_NAME ("Pacman")
#define MAX_STRING_LINE 20
#define NUMBER_OF_CHARACTERS ('Z')

enum MenuOptions { demoGame, newGame, continueGame, highscore, settings, credits, quitGame, numberOfMenuOptions };

enum SettingsOptions {gameDifficulty, diffOption, music, numberOfSettingsOptions}; //dodace se jos vrednosti

void gameInit();

void gameQuit();

void getScreenResolution(int *width, int *height);

void initTexturesForMenu(SDL_Texture * menuTextureWhite[], SDL_Texture * menuTextureYellow[], SDL_Texture ** PacmanTexture);

void createHeading();

void printMenu(enum menuOptions currentMenuOption, SDL_Texture * menuTextureWhite[], SDL_Texture * menuTextureYellow[], SDL_Texture * PacmanTexture);

void initSettingsTextures();

void createSettingsHeading();

void activateSettings(enum DifficultySpeed * currentDifficulty);

void printSettings(enum settingsOptions currentMenuOption, enum DifficultySpeed currentDifficulty, enum DifficultySpeed hoveringDiff);

void initEndGameTextures();

void endGameScreen();

void initFinalScoreTextures();

void finalScoreScreen(int currScore, char * name, int *nameSave);

typedef struct SettingsTexturesStruct {
	SDL_Texture * whiteTextures[numberOfSettingsOptions];
	SDL_Texture * yellowTextures[numberOfSettingsOptions];
	SDL_Texture * whiteDifficulty[NUMBER_OF_DIFFICULTIES];
	SDL_Texture * yellowDifficulty[NUMBER_OF_DIFFICULTIES];
	SDL_Texture * whiteFilledDiff[NUMBER_OF_DIFFICULTIES];
	SDL_Texture * yellowFilledDiff[NUMBER_OF_DIFFICULTIES];
	SDL_Texture * pacmanTexture;
}SettingsMenuTextures;

typedef struct EndGameTextureStruct {
	SDL_Texture * gameOverTexture;
	SDL_Texture * pressAnyButtonTexture;
}EndGameTextures;

typedef struct finalScoreTexturesStruct {
	SDL_Texture * typeInYourNameTexture;
	SDL_Texture * characterTextures[NUMBER_OF_CHARACTERS];
	SDL_Texture * blankTexture;
}FinalScoreTextures;

SettingsMenuTextures settingsTextureManager;

EndGameTextures endGameTextureManager;

FinalScoreTextures finalScoreTextureManager;

#endif