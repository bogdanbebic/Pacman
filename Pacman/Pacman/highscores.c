#include "highscores.h"
#include <stdio.h>
#include <Windows.h>
#include "encryption.h"

/*!	\file highscores.c
*	\brief Contains variable and function definitions for keeping highscores
*/

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

/*!
*	\brief Global variable containing seeds for encryption for data for each file
*/
unsigned int seed_for_LCG_random[] = { 1000U, 1500U, 2000U, 2500U, 3000U };

/*!
*	\brief Global variable containing seeds for encryption for prefix sums for each file
*/
unsigned int seed_for_random_prefix_sums[] = { 123555U, 212345U, 654321U, 987456U, 154826U };

/*!
*	\brief global variable in which highscores are kept
*/
Highscore highscores[MAX_HIGHSCORES];

/*!
*	\brief Makes decoy highscore files with the purpose of fooling Marko Misic
*/
void makeDecoyHighscoreFiles() {
	FILE *notAhighscoreFile;

	char s[] = "Nije highscore ovde, sacuvan je na boljem mestu";
	char s0[] = "Pa nije ovde highscore, bukvalno pise u imenu fajla";
	char s1[] = "Nije ni ovde highscore, ali sigurno ste mislili da ste nasli :P";

	fopen_s(&notAhighscoreFile, DECOY_1, "wb");
	if (notAhighscoreFile != NULL) {
		fwrite(s, sizeof(char), sizeof(s) / sizeof(char) - 1, notAhighscoreFile);
		fclose(notAhighscoreFile);
	}

	fopen_s(&notAhighscoreFile, DECOY_2, "wb");
	if (notAhighscoreFile != NULL) {
		fwrite(s, sizeof(char), sizeof(s) / sizeof(char) - 1, notAhighscoreFile);
		fclose(notAhighscoreFile);
	}

	fopen_s(&notAhighscoreFile, DECOY_3, "wb");
	if (notAhighscoreFile != NULL) {
		fwrite(s, sizeof(char), sizeof(s) / sizeof(char) - 1, notAhighscoreFile);
		fclose(notAhighscoreFile);
	}

	fopen_s(&notAhighscoreFile, DECOY_4, "wb");
	if (notAhighscoreFile != NULL) {
		fwrite(s0, sizeof(char), sizeof(s0) / sizeof(char) - 1, notAhighscoreFile);
		fclose(notAhighscoreFile);
	}

	fopen_s(&notAhighscoreFile, DECOY_5, "wb");
	if (notAhighscoreFile != NULL) {
		fwrite(s1, sizeof(char), sizeof(s1) / sizeof(char) - 1, notAhighscoreFile);
		fclose(notAhighscoreFile);
	}
	return;
}

/*!
*	\brief Initializes highscores array with generic highscores
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

/*!
*	\brief Updates highscores array if neccesary
*	\param newHighscore highscore which is added to highscores if points are greater
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

/*!
*	\brief Number of files in which highscores are kept
*/
#define NUMBER_OF_FILES 5

#define BITS_IN_BYTE 8

/*!
*	\brief Size of unsigned int buffer for reading/writing from/to highscores file
*/
#define SIZE_OF_BUFFER ((MAX_HIGHSCORES * sizeof(Highscore) + sizeof(unsigned int) - 1) / sizeof(unsigned int))

/*!
*	\brief Buffer for reading/writing data from/to highscores file
*/
unsigned int bufferInt[NUMBER_OF_FILES][SIZE_OF_BUFFER];

/*!
*	\brief Buffer for reading/writing prefix sums from/to highscores file
*/
unsigned int prefixSumsBuffer[SIZE_OF_BUFFER];

/*!
*	\brief Reads highscores array from one file
*	\param filePath defines name of file
*	\param L_filePath defines name of file for hiding
*	\param encryptionSeed seed used for random generator used in encryption
*	\param indexOfFile Represents index of file to be read
*	\param seedForPrefixSums seed used for random generator used in encryption of prefix sums
*	\return Returns 1 if opened file != NULL, 0 if file was not opened
*/
int readHighscoresFromFile(char *filePath, LPCWSTR L_filePath, unsigned int encryptionSeed, int indexOfFile, int seedForPrefixSums) {
	extern unsigned int bufferInt[NUMBER_OF_FILES][SIZE_OF_BUFFER];
	extern unsigned int prefixSumsBuffer[SIZE_OF_BUFFER];
	FILE *highscoresFile;
	int i;

	SetFileAttributes(L_filePath, FILE_ATTRIBUTE_NORMAL);
	fopen_s(&highscoresFile, filePath, "rb");
	if (highscoresFile != NULL) {
		seedRandomLCG(seedForPrefixSums);
		for (i = 0; i < 2 * SIZE_OF_BUFFER; ) {
			fread(&prefixSumsBuffer[i / 2], sizeof(prefixSumsBuffer[i / 2]), 1, highscoresFile);
			i++;

			encrypt(&prefixSumsBuffer[i / 2], sizeof(prefixSumsBuffer[i / 2]) / sizeof(int));
			prefixSumsBuffer[i / 2] &= ~(1U << (sizeof(int) * BITS_IN_BYTE - 1));
			
			if ((prefixSumsBuffer[i / 2] ^ 1U << (sizeof(int) * BITS_IN_BYTE - 1)) && prefixSumsBuffer[i / 2] >= 0 && prefixSumsBuffer[i / 2] < SIZE_OF_BUFFER) {
				fread(&bufferInt[indexOfFile][prefixSumsBuffer[i / 2]], sizeof(bufferInt[indexOfFile][prefixSumsBuffer[i / 2]]), 1, highscoresFile);
				i++;
			}
		}
		fclose(highscoresFile);


		seedRandomLCG(encryptionSeed);
		encrypt(bufferInt[indexOfFile], sizeof(bufferInt[indexOfFile]) / sizeof(int));
		
		return 1;
	}
	else {
		return 0;
	}
}

/*!
*	\brief Reads highscores array from files
*/
void readHighscoresFromFiles() {	// OVO POPRAVITI DA RADI SA 5 FAJLOVA
	extern Highscore highscores[MAX_HIGHSCORES];
	extern unsigned int bufferInt[NUMBER_OF_FILES][SIZE_OF_BUFFER];
	int flag;
	
	flag = readHighscoresFromFile(FILE_1, L_FILE_1, seed_for_LCG_random[0], 0, seed_for_random_prefix_sums[0]);
	if (flag) {
		memcpy(highscores, bufferInt[0], sizeof(highscores));
	}
	else {
		makeGenericHighscores();
	}
	return;
}

/*!
*	\brief Encrypts highscores array and writes it to file
*	\param filePath defines name of file
*	\param L_filePath defines name of file for hiding
*	\param encryptionSeed seed used for random generator used in encryption of data
*	\param seedForPrefixSums seed used for random generator used in encryption of prefix sums
*/
static void writeHighscoresToFile(char *filePath, LPCWSTR L_filePath, unsigned int encryptionSeed, int seedForPrefixSums) {
	extern Highscore highscores[MAX_HIGHSCORES];
	FILE *highscoresFile;
	int i;
	extern unsigned int prefixSumsBuffer[SIZE_OF_BUFFER];
	extern unsigned int bufferInt[NUMBER_OF_FILES][SIZE_OF_BUFFER];

	for (i = 0; i < SIZE_OF_BUFFER; i++) {
		prefixSumsBuffer[i] = i;
	}
	seedRandomLCG(seedForPrefixSums);
	encrypt(prefixSumsBuffer, sizeof(prefixSumsBuffer) / sizeof(int));
	for (i = 0; i < SIZE_OF_BUFFER; i++) {
		prefixSumsBuffer[i] |= 1U << (sizeof(int) * BITS_IN_BYTE - 1);
	}
	
	memcpy(bufferInt[0], highscores, sizeof(highscores));
	seedRandomLCG(encryptionSeed);
	encrypt(bufferInt[0], sizeof(bufferInt[0]) / sizeof(int));

	fopen_s(&highscoresFile, filePath, "wb");
	if (highscoresFile != NULL) {
		for (i = 0; i < SIZE_OF_BUFFER; i++) {
			fwrite(&prefixSumsBuffer[i], sizeof(prefixSumsBuffer[i]), 1, highscoresFile);
			fwrite(&bufferInt[0][i], sizeof(bufferInt[0][i]), 1, highscoresFile);
		}
		
		fclose(highscoresFile);

		SetFileAttributes(L_filePath, FILE_ATTRIBUTE_HIDDEN);
	}
	return;
}

/*!
*	\brief Writes highscores to 5 files using the function writeHighscoresToFile
*/
void writeHighscoresToFiles() {
	writeHighscoresToFile(FILE_1, L_FILE_1, seed_for_LCG_random[0], seed_for_random_prefix_sums[0]);
	//writeHighscoresToFile(FILE_2, L_FILE_2, seed_for_LCG_random[1], seed_for_random_prefix_sums[1]);
	//writeHighscoresToFile(FILE_3, L_FILE_3, seed_for_LCG_random[2], seed_for_random_prefix_sums[2]);
	//writeHighscoresToFile(FILE_4, L_FILE_4, seed_for_LCG_random[3], seed_for_random_prefix_sums[3]);
	//writeHighscoresToFile(FILE_5, L_FILE_5, seed_for_LCG_random[4], seed_for_random_prefix_sums[4]);
	return;
}
