#pragma once
#ifndef _highscores_h_
#define _highscores_h_

// TODO: ovo treba da bude nesto smisleno
#define MAX_NAME 12

// TODO: ovo treba da bude nesto smisleno
#define MAX_HIGHSCORES 7

typedef struct HighscoreStruct {
	int points;
	char name[MAX_NAME];
} Highscore;

void makeDecoyHighscoreFiles();

void makeGenericHighscores();

void updateHighscores(Highscore newHighscore);

void readHighscoresFromFile();

void writeHighscoresToFiles();

#endif // !_highscores_h_
