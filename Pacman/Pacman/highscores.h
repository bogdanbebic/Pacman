#pragma once
#ifndef _highscores_h_
#define _highscores_h_

#define MAX_NAME 12

#define MAX_HIGHSCORES 7

/*!
*	\brief struct which contains info needed for highscore (name and points)
*/
typedef struct HighscoreStruct {
	int points;
	char name[MAX_NAME];
} Highscore;

void makeDecoyHighscoreFiles();

void makeGenericHighscores();

void updateHighscores(Highscore newHighscore);

void readHighscoresFromFiles();

void writeHighscoresToFiles();

#endif // !_highscores_h_
