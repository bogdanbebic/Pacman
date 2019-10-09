#pragma once
#ifndef _highscores_h_
#define _highscores_h_

/*!	\file highscores.h
 *	\brief Contains declarations and constants for highscore keeping
 */

/*!
 *	\brief Maximum name for player
 */
#define MAX_NAME 12

/*!
 *	\brief Number of highscores saved
 */
#define MAX_HIGHSCORES 7

/*!
 *	\brief struct which contains info needed for highscore (name and points)
 */
typedef struct HighscoreStruct {
	int points;
	char name[MAX_NAME];
} Highscore;

/*!
 *	\brief Makes decoy highscore files with the purpose of fooling Marko Misic
 */
void makeDecoyHighscoreFiles();

/*!
 *	\brief Initializes highscores array with generic highscores
 */
void makeGenericHighscores();

/*!
 *	\brief Updates highscores array if neccesary
 *	\param newHighscore highscore which is added to highscores if points are greater
 */
void updateHighscores(Highscore newHighscore);

/*!
 *	\brief Reads highscores array from files
 */
void readHighscoresFromFiles();

/*!
 *	\brief Writes highscores to 5 files using the function writeHighscoresToFile
 */
void writeHighscoresToFiles();

#endif // !_highscores_h_
