#include "highscores.h"
#include <stdio.h>
#include <Windows.h>
#include "encryption.h"

/*
*	Ne dirati ove fajlove, ovo su highscore fajlovi
*/
#define FILE_1 "SDL2/SDL_Event.dll"
#define FILE_2 "SDL2/SDL2_init_test.lib"
#define FILE_3 "SDL2_ttf/zlib2.dll"
#define FILE_4 "SDL2_ttf/TTF_Texture.lib"
#define FILE_5 "SDL2_ttf/libfreetype_x.dll"

#define L_FILE_1 L"SDL2/SDL_Event.dll"
#define L_FILE_2 L"SDL2/SDL2_init_test.lib"
#define L_FILE_3 L"SDL2_ttf/zlib2.dll"
#define L_FILE_4 L"SDL2_ttf/TTF_Texture.lib"
#define L_FILE_5 L"SDL2_ttf/libfreetype_x.dll"

#define DECOY_1 "highscores1.hsc"
#define DECOY_2 "highscores2.hsc"
#define DECOY_3 "highscores3.hsc"
#define DECOY_4 "not_a_highscore_file.hsc"
#define DECOY_5 "Music/highscores.hsc"

Highscore highscores[MAX_HIGHSCORES];

/*
*	Makes decoy highscore files
*	with the purpose of fooling Marko Misic
*/
void makeDecoyHighscoreFiles() {
	FILE *notAhighscoreFile;

	char s[] = "Nije highscore ovde, sacuvan je na boljem mestu";
	char s0[] = "Pa nije ovde highscore, bukvalno pise u imenu fajla";
	char s1[] = "Nije ni ovde highscore, ali sigurno ste mislili da ste nasli :P";

	fopen_s(&notAhighscoreFile, DECOY_1, "wb");
	fwrite(s, sizeof(char), sizeof(s)/sizeof(char) - 1, notAhighscoreFile);
	fclose(notAhighscoreFile);

	fopen_s(&notAhighscoreFile, DECOY_2, "wb");
	fwrite(s, sizeof(char), sizeof(s) / sizeof(char) - 1, notAhighscoreFile);
	fclose(notAhighscoreFile);

	fopen_s(&notAhighscoreFile, DECOY_3, "wb");
	fwrite(s, sizeof(char), sizeof(s) / sizeof(char) - 1, notAhighscoreFile);
	fclose(notAhighscoreFile);

	fopen_s(&notAhighscoreFile, DECOY_4, "wb");
	fwrite(s0, sizeof(char), sizeof(s0) / sizeof(char) - 1, notAhighscoreFile);
	fclose(notAhighscoreFile);

	fopen_s(&notAhighscoreFile, DECOY_5, "wb");
	fwrite(s1, sizeof(char), sizeof(s1) / sizeof(char) - 1, notAhighscoreFile);
	fclose(notAhighscoreFile);

	return;
}

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
	FILE *highscoresFile;
	SetFileAttributes(L_FILE_1, FILE_ATTRIBUTE_NORMAL);
	fopen_s(&highscoresFile, FILE_1, "rb");

	if (highscoresFile != NULL) {
		fread(&highscores, sizeof(highscores), 1, highscoresFile);
		fclose(highscoresFile);
		encrypt();
	}
	else {
		makeGenericHighscores();
	}
	return;
}

/*
*	Writes highscores array to file
*/
void writeHighscoresToFile() {
	extern Highscore highscores[MAX_HIGHSCORES];
	FILE *highscoresFile;

	fopen_s(&highscoresFile, FILE_1, "wb");

	encrypt();

	fwrite(&highscores, sizeof(highscores), 1, highscoresFile);
	
	fclose(highscoresFile);

	SetFileAttributes(L_FILE_1, FILE_ATTRIBUTE_HIDDEN);

	return;
}
