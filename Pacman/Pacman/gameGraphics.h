#ifndef _gameGraphics_h_
#define _gameGraphics_h_

/*!	\file gameGraphics.h
 *	\brief Contains declarations and constants for gameplay graphics
 */

#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "gameMap.h"
#include "highscores.h"
#include "pacStruct.h"
#include "game.h"

/*!
 *	\brief Length of score box which is drawn on the screen
 */
#define LEN_OF_SCORE_BOX 50

/*!
 *	\brief Initializes all game textures
 */
void initGameTextures();

/*!
 *	\brief Destroys all game textures
 */
void destroyGameTextures();

/*!
 *	\brief Updates the score box in the game screen
 *	\param currentScore number which will be printed on screen as current score
 */
void updateScoreBox(Highscore currentScore);

/*!
 *	\brief Updates GUI level box in the game screen
 *	\param level number which will be printed on screen as level
 */
void updateLevelBox(int level);

/*!
 *	\brief Updates the Pacman lives box in the game screen according to the argument livesCount
 *	\param map map on which the game s played
 *	\param numberOfLivesTiles number of tiles which are on the game screen for lives
 *	\param livesCount number of lives pacman has left
 */
void updateLivesBox(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], int numberOfLivesTiles, int livesCount);

/*!
 *	\brief Prints argument map and pacman on the game screen
 *	\param map map on which the game s played
 *	\param pacman PacStruct containing info about pacman
 *	\param srbendaMod contains info about whether srbendaMod is active ( != 0 )
 *	\param newLevel contains info about wheter now a new level should be printed
 */
void printInitMap(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman, int srbendaMod, int newLevel);

/*!
 *	\brief Updates arguments map and pacman according to its values and values of arguments delay and timer_tick
 *	\param map map on which the game s played
 *	\param pacman PacStruct containing info about pacman
 *	\param timer_tick clock timer for game loop
 *	\param srbendaMod contains info about whether srbendaMod is active ( != 0 )
 */
void updatePacman(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman, int timer_tick, int srbendaMod);

/*!
 *	\brief Updates arguments map and ghosts according to their values and values of arguments delay and timer_tick
 *	\param map map on which the game s played
 *	\param ghosts PacStruct array containing info about ghosts
 *	\param timer_tick clock timer for game loop
 *	\param srbendaMod contains info about whether srbendaMod is active ( != 0 )
 *	\param pacman PacStruct which contains info about pacman
 *	\param lastPacmanDirection contains the last direction of Pacman, that wasn't none
 *	\param lastMovingTimerTick contains the last tick in which Pacman was moving
 */
void updateGhosts(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct ghosts[NUMBER_OF_GHOSTS], int timer_tick, int srbendaMod, PacStruct pacman, enum Direction lastPacmanDirection, int lastMovingTimerTick);

#endif
