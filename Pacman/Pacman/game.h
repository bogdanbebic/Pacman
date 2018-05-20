#ifndef _game_h_
#define _game_h_

#include "ghosts.h"

#include "highscores.h"
#include "graphicsMenu.h"
#include "pacStruct.h"
#include "gameGraphics.h"

#define WIDTH_SCREEN 600
#define HEIGHT_SCREEN 400
#define NUMBER_OF_DIGITS 10
#define NUMBER_OF_LVL_DIGITS 3

enum GameType { NEW_GAME, CONTINUE_GAME, DEMO_GAME };

void updateScoreAndGameMode(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman, PacStruct ghosts[], int * pacDotCount, Highscore * currentScore);

int wallCheckAndMove(int [HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct *);

void changeDirectionForReverseGhost(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct *pacStruct);

void initTempMap(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], int tempMap[HEIGHT_OF_MAP][WIDTH_OF_MAP]);

enum Direction getPacmanDirectionFromUser(SDL_Event event);

void initNewGame(enum DifficultySpeed difficulty, int *delay, int *level, int *livesCount, int *numberOfLivesTiles, Highscore *currentScore, int *isStartOfNewGame);

Highscore playGame(enum GameType gameType, enum DifficultySpeed difficulty);

void initGhosts(PacStruct ghosts[NUMBER_OF_GHOSTS]);

void initPacmanPosition(PacStruct *pacman);

int pacmanGhostCheck(PacStruct pacman, PacStruct ghost);

int countPacDots(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP]);

typedef struct ScreenStruct {
	unsigned int width;
	unsigned int height;
	const char* name;
	SDL_Window* window;
	SDL_Renderer* renderer;
} Screen;

typedef struct GameTextureStruct {
	SDL_Texture * pacmanOpenMouthTextures[NUMBER_OF_DIRECTIONS];
	SDL_Texture * pacmanShutMouthTextures[NUMBER_OF_DIRECTIONS];
	SDL_Texture * wallTexture, *backgroundTexture, *pacDotTexture, *powerPelletTexture;
	SDL_Texture * ghostTextures[NUMBER_OF_GHOSTS];
	SDL_Texture * reverseGhostTexture;
	SDL_Texture * scoreBoxTexture, *livesBoxTexture, *levelBoxTexture;
	SDL_Texture * scoreDigitTextures[NUMBER_OF_DIGITS];
	SDL_Rect levelBoxRect, scoreBoxRect;
	SDL_Rect mapTileRects[HEIGHT_OF_MAP][WIDTH_OF_MAP];
	SDL_Rect scoreDigitRect[NUMBER_OF_DIGITS];
	SDL_Rect levelDigitRect[NUMBER_OF_LVL_DIGITS];
} GameTextures;

typedef struct GameStruct {
	SDL_bool isRunning;
	Screen screen;
	void(*init)();
	void(*quit)();
} Game;

Game game;

GameTextures gameTexturesManager;

#endif