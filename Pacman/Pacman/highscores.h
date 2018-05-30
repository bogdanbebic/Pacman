#pragma once
#ifndef _highscores_h_
#define _highscores_h_

// TODO: ovo treba da bude nesto smisleno
#define MAX_NAME 100

// TODO: ovo treba da bude nesto smisleno
#define MAX_HIGHSCORES 8

typedef struct HighscoreStruct {
	int points;
	int pacDots;
	int powerPellets;
	int ghosts;
	char name[MAX_NAME];
} Highscore;

void makeGenericHighscores(Highscore highscores[MAX_HIGHSCORES]);

void updateHighscores(Highscore highscores[MAX_HIGHSCORES], Highscore newHighscore);

void readHighscoresFromFile(Highscore highscores[MAX_HIGHSCORES]);

void writeHighscoresToFile(Highscore highscores[MAX_HIGHSCORES]);

#endif // !_highscores_h_
