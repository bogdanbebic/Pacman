#ifndef _game_h_
#define _game_h_

/*!	\file game.h
*	\brief Contains declarations and constants for gameplay
*/

#include "ghosts.h"

#include "highscores.h"
#include "graphicsMenu.h"
#include "pacStruct.h"
#include "gameGraphics.h"

#define WIDTH_SCREEN 600
#define HEIGHT_SCREEN 400
#define NUMBER_OF_DIGITS 10
#define NUMBER_OF_LVL_DIGITS 3

/*!
*	\brief Max number of lives which pacman can have
*/
#define MAX_LIVES 10

/*!
*	\brief Enum containing all types of possible game modes
*/
enum GameType { NEW_GAME, CONTINUE_GAME, DEMO_GAME };

/*!
*	\brief Updates the currentScore and gameMode if pacman has eaten a power pellet
*	\param map map which contains everything needed for start of level
*	\param pacman PacStruct containing pacmans coordinates
*	\param ghosts PacStruct array containing ghosts coordinates
*	\param pacDotCount number of pac dots left
*	\param currentScore current score which is accumulated
*	\param timer_tick clock timer for game loop
*	\param isPowerPelletEaten indicates if a power pellet has been eaten
*	\param difficulty diffilculty of the game
*/
void updateScoreAndGameMode(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman, PacStruct ghosts[], int * pacDotCount, Highscore * currentScore, int *timer_tick, int *isPowerPelletEaten, enum DifficultySpeed difficulty);

/*!
*	\brief Moves pacStruct on map, prevents pacStruct to be in wall
*	\param map current map on which the game is played
*	\param pacStruct PacStruct which is to be moved
*	\return returns 1 if pacStruct moved, 0 otherwise
*/
int wallCheckAndMove(int [HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct *);

/*!
*	\brief Changes direction for ghost in reverse mode
*	\param map current map on which the game is played
*	\param pacStruct PacStruct which is to be moved
*/
void changeDirectionForReverseGhost(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct *pacStruct);

/*!
*	\brief Initializes temporary map which is used in a single level
*	\param map map which contains everything needed for start of level
*	\param tempMap map which will be used in gamepla
*/
void initTempMap(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], int tempMap[HEIGHT_OF_MAP][WIDTH_OF_MAP]);

/*!
*	\brief Gets pacman direction from user
*	\param event SDL event used to get keyboard input
*	\return enum Direction which marks direction that the user has given as input or DIRECTION_NONE if user has given input whhich is not correct
*/
enum Direction getPacmanDirectionFromUser(SDL_Event event);

/*!
*	\brief Initializes a new game with new game parameters and sets values for all arguments except difficulty
*	\param difficulty diffilculty of the game
*	\param delay delay of function calling in game
*	\param level level on which the game is
*	\param livesCount number of lives left
*	\param currentScore current score which is accumulated
*	\param isStartOfNewGame indicates wheter the game has not yet been initialized
*	\param home PacStruct containing info about where ghosts go to ressurect
*/
void initNewGame(enum DifficultySpeed difficulty, int *delay, int *level, int *livesCount, Highscore *currentScore, int *isStartOfNewGame, PacStruct *home);

/*!
*	\brief Sets up and plays new Pacman game according to the argument difficulty
*	\param gameType type of game which is played
*	\param difficulty difficulty at which the game is played
*	\param isMusicOn 1 if true, otherwise 0
*	\return currentScore is the score that the player has accumulated in the game
*/
Highscore playGame(enum GameType gameType, enum DifficultySpeed difficulty, int isMusicOn);

/*!
*	\brief Initializes starting ghosts positions on map
*	\param ghosts array of PacStructs which will be initialized
*/
void initGhosts(PacStruct ghosts[NUMBER_OF_GHOSTS]);

/*!
*	\brief Initializes starting pacman position on map
*	\param pacman PacStruct which will be initialized
*/
void initPacmanPosition(PacStruct *pacman);

/*!
*	\brief Checks if pacman and and ghost have the same coordinates
*	\param pacman PacStruct containing pacmans coordinates
*	\param ghost PacStruct containing ghosts coordinates
*	\return	1 for same coordinates 0 for different coordinates
*/
int pacmanGhostCheck(PacStruct pacman, PacStruct ghost);

/*!
*	\brief Counts pacDot-s on given map
*	\param map map on which the function counts pacDot-s
*	\return count of pacDot-s
*/
int countPacDots(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP]);

/*!
 *	\brief Initializes continue game with saved game parameters and sets values for all arguments except difficulty
 *	\param difficulty diffilculty of the game
 *	\param delay delay of function calling in game
 *	\param level level on which the game is
 *	\param livesCount number of lives left
 *	\param currentScore current score which is accumulated
 *	\param isStartOfNewGame indicates wheter the game has not yet been initialized
 *	\param home PacStruct containing info about where ghosts go to ressurect
 *	\param pacDotCount number of pac dots left
 *	\param timer_tick clock timer for game loop
 *	\param timer_tick_POWER_PELLET clock timer for power pellet effects
 *	\param isPowerPelletEaten indicates if a power pellet has been eaten
 */
void initContinueGame(enum DifficultySpeed *difficulty, int *delay, int *level, int *livesCount, Highscore *currentScore, int *isStartOfNewGame, PacStruct *home, int *pacDotCount, int *timer_tick, int *timer_tick_POWER_PELLET, int *isPowerPelletEaten);

/*!
*	\brief Saves current game and makes it possible to continue game
*	\param difficulty diffilculty of the game
*	\param delay delay of function calling in game
*	\param level level on which the game is
*	\param livesCount number of lives left
*	\param currentScore current score which is accumulated
*	\param isStartOfNewGame indicates wheter the game has not yet been initialized
*	\param home PacStruct containing info about where ghosts go to ressurect
*	\param pacman PacStruct containing info about pacman
*	\param ghosts PacStruct array containing info about ghosts
*	\param map map on which the game is played
*	\param pacDotCount number of pac dots left
*	\param srbendaMod indicates if srbenda mode is on
*	\param timer_tick clock timer for game loop
*	\param timer_tick_POWER_PELLET clock timer for power pellet effects
*	\param isPowerPelletEaten indicates if a power pellet has been eaten
*/
void saveGameForContinue(enum DifficultySpeed difficulty, int delay, int level, int livesCount, Highscore currentScore, int isStartOfNewGame, PacStruct home, PacStruct pacman, PacStruct ghosts[], int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], int pacDotCount, int srbendaMod, int timer_tick, int timer_tick_POWER_PELLET, int isPowerPelletEaten);

/*!
*	\brief Struct which contains needed variables for SDL screen
*/
typedef struct ScreenStruct {
	unsigned int width;
	unsigned int height;
	const char* name;
	SDL_Window* window;
	SDL_Renderer* renderer;
} Screen;

/*!
*	\brief Struct containing needed variables for game textures
*/
typedef struct GameTextureStruct {
	SDL_Texture * pacmanOpenMouthTextures[NUMBER_OF_DIRECTIONS];
	SDL_Texture * pacmanShutMouthTextures[NUMBER_OF_DIRECTIONS];
	SDL_Texture * wallTexture, *backgroundTexture, *pacDotTexture, *powerPelletTexture;
	SDL_Texture * wallSrbendaTexture, *powerPelletSrbendaTexture;
	SDL_Texture * ghostTextures[NUMBER_OF_GHOSTS];
	SDL_Texture * reverseGhostTexture, * eatenGhostTexture;
	SDL_Texture * scoreBoxTexture, *livesBoxTexture, *levelBoxTexture;
	SDL_Texture * scoreDigitTextures[NUMBER_OF_DIGITS];
	SDL_Texture * pacmanSrbendaOpenMouth[NUMBER_OF_DIRECTIONS];
	SDL_Texture * pacmanSrbendaShutMouth[NUMBER_OF_DIRECTIONS];
	SDL_Rect levelBoxRect, scoreBoxRect;
	SDL_Rect mapTileRects[HEIGHT_OF_MAP][WIDTH_OF_MAP];
	SDL_Rect scoreDigitRect[NUMBER_OF_DIGITS];
	SDL_Rect levelDigitRect[NUMBER_OF_LVL_DIGITS];
} GameTextures;

/*!
*	\brief Struct containing needed variables for game start and end
*/
typedef struct GameStruct {
	SDL_bool isRunning;
	Screen screen;
	void(*init)();
	void(*quit)();
} Game;

/*!
*	\brief Global variable which contains game information
*/
Game game;

/*!
*	\brief Global variable which contains game textures information
*/
GameTextures gameTexturesManager;

#endif