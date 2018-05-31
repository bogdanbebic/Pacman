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

	i = MAX_HIGHSCORES - 1;
	
	if (newHighscore.points > highscores[i].points) {
		highscores[i] = newHighscore;
	}
	else {
		return;
	}

	i--;

	while (i >= 0 && newHighscore.points > highscores[i].points) {
		highscores[i + 1] = highscores[i];
		i--;
	}
	i = (i == -1 ? 0 : i + 1);
	highscores[i] = newHighscore;

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
