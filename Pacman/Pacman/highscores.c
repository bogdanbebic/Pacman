#include "highscores.h"

Highscore highscores[MAX_HIGHSCORES];

/*
*	Initializes highscores array
*	with generic highscores
*/
void makeGenericHighscores() {
	extern Highscore highscores[MAX_HIGHSCORES];
	const char genericName[] = "Anonymus";
	const int genericScore = 500;
	int i, j;
	for (i = MAX_HIGHSCORES - 1; i >= 0; i--) {
		for (j = 0; genericName[j] != '\0'; j++) {
			highscores[i].name[j] = genericName[j];
		}
		highscores[i].points = (MAX_HIGHSCORES - i + 1) * genericScore;
	}
	return;
}

/*
*	Updates highscores array
*	with newHighscore if neccesary
*/
void updateHighscores(Highscore newHighscore) {
	extern Highscore highscores[MAX_HIGHSCORES];
	int i;
	Highscore temp;

	i = MAX_HIGHSCORES - 1;
	
	if (newHighscore.points > highscores[i].points) {
		highscores[i] = newHighscore;
	}
	i--;

	// OVO NE RADI, IZDEBAGUJ
	while (i >= 0 && newHighscore.points > highscores[i].points) {
		temp = highscores[i];
		highscores[i] = newHighscore;
		highscores[i + 1] = temp;
		i--;
	}

	return;
}

/*
*	Reads highscores array from file
*/
void readHighscoresFromFile() {
	extern Highscore highscores[MAX_HIGHSCORES];

	// TODO: implement

	return;
}

/*
*	Writes highscores array to file
*/
void writeHighscoresToFile() {
	extern Highscore highscores[MAX_HIGHSCORES];
	
	// TODO: implement

	return;
}
