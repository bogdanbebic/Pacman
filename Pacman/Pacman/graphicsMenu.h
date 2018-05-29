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

SDL_Texture* Message[numberOfMenuOptions];

void initEndGameTextures();

void endGameScreen();

typedef struct SettingsTexturesStruct {
	SDL_Texture * whiteTextures[numberOfSettingsOptions];
	SDL_Texture * yellowTextures[numberOfSettingsOptions];
	SDL_Texture * whiteDifficulty[3];
	SDL_Texture * yellowDifficulty[3];
	SDL_Texture * whiteFilledDiff[3];
	SDL_Texture * yellowFilledDiff[3];
	SDL_Texture * pacmanTexture;
}SettingsMenuTextures;

typedef struct EndGameTextureStruct {
	SDL_Texture * gameOverTexture;
	SDL_Texture * pressAnyButtonTexture;
}EndGameTextures;

SettingsMenuTextures settingsTextureManager;

EndGameTextures endGameTextureManager;

#endif