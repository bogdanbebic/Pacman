#include "highscores.h"
#include <stdio.h>
#include <Windows.h>
#include <time.h>
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
*	\brief Global variable containing seeds for encryption for each file
*/
unsigned int seed_for_random[] = { 123555U, 212345U, 654321U, 987456U, 154826U };

/*!
*	\brief global variable in which highscores are kept
*/
Highscore highscores[MAX_HIGHSCORES];

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

void makeGenericHighscores() {
	extern Highscore highscores[MAX_HIGHSCORES];
	const char genericName[] = "Anonymous";
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
 *	\return Returns 1 if opened file != NULL, 0 if file was not opened
 */
static int readHighscoresFromFile(char *filePath, LPCWSTR L_filePath, unsigned int encryptionSeed, int indexOfFile) {
	extern unsigned int bufferInt[NUMBER_OF_FILES][SIZE_OF_BUFFER];
	extern unsigned int prefixSumsBuffer[SIZE_OF_BUFFER];
	FILE *highscoresFile;
	unsigned int i;
	unsigned int deletions = 0;

	SetFileAttributes(L_filePath, FILE_ATTRIBUTE_NORMAL);
	fopen_s(&highscoresFile, filePath, "rb");
	if (highscoresFile != NULL) {
		seedRandomLCG(encryptionSeed);
		for (i = 0; i < 2 * SIZE_OF_BUFFER - deletions; ) {
			fread(&prefixSumsBuffer[i / 2], sizeof(prefixSumsBuffer[i / 2]), 1, highscoresFile);
			i++;

			encrypt(&prefixSumsBuffer[i / 2], sizeof(prefixSumsBuffer[i / 2]) / sizeof(int));
			prefixSumsBuffer[i / 2] &= ~(1U << (sizeof(int) * BITS_IN_BYTE - 1));
			
			if ((prefixSumsBuffer[i / 2] ^ 1U << (sizeof(int) * BITS_IN_BYTE - 1)) && prefixSumsBuffer[i / 2] >= 0 && prefixSumsBuffer[i / 2] < SIZE_OF_BUFFER) {
				fread(&bufferInt[indexOfFile][prefixSumsBuffer[i / 2]], sizeof(bufferInt[indexOfFile][prefixSumsBuffer[i / 2]]), 1, highscoresFile);
				i++;
			}
			else {
				i--;
				deletions += 2;
			}
		}
		fclose(highscoresFile);

		encrypt(bufferInt[indexOfFile], sizeof(bufferInt[indexOfFile]) / sizeof(int));
		
		return 1;
	}
	else {
		return 0;
	}
}

void readHighscoresFromFiles() {
	extern Highscore highscores[MAX_HIGHSCORES];
	extern unsigned int bufferInt[NUMBER_OF_FILES][SIZE_OF_BUFFER];
	extern unsigned int seed_for_random[NUMBER_OF_FILES];
	int flag[NUMBER_OF_FILES], i;
	int numberOfOpenedFiles = 0;
	int isHighscoresUnrecoverable = 0;
	int currentElem, numberOfSameElems;
	
	flag[0] = readHighscoresFromFile(FILE_1, L_FILE_1, seed_for_random[0], 0);
	flag[1] = readHighscoresFromFile(FILE_2, L_FILE_2, seed_for_random[1], 1);
	flag[2] = readHighscoresFromFile(FILE_3, L_FILE_3, seed_for_random[2], 2);
	flag[3] = readHighscoresFromFile(FILE_4, L_FILE_4, seed_for_random[3], 3);
	flag[4] = readHighscoresFromFile(FILE_5, L_FILE_5, seed_for_random[4], 4);

	for (i = 0; i < NUMBER_OF_FILES; numberOfOpenedFiles += flag[i++]);

	if (numberOfOpenedFiles >= 3) {
		int j;
		for (j = 0; j < SIZE_OF_BUFFER; j++) {
			int start;
			for (start = 0; start < 1 + NUMBER_OF_FILES / 2; start++) {
				numberOfSameElems = 1;
				currentElem = bufferInt[start][j];
				for (i = start + 1; i < NUMBER_OF_FILES; i++) {
					if (bufferInt[i][j] == currentElem) {
						numberOfSameElems++;
					}
				}
				if (numberOfSameElems >= 3) {
					memcpy((int*)highscores + j, &currentElem, sizeof(currentElem));
					break;
				}
			}
			if (numberOfSameElems >= 3) {
				continue;
			}
			
			isHighscoresUnrecoverable = 1;
			break;
		}

		for (i = 0; i < MAX_HIGHSCORES; i++) {
			highscores[i].name[MAX_NAME - 1] = '\0';
		}
	}
	else {
		isHighscoresUnrecoverable = 1;
	}

	if (isHighscoresUnrecoverable) {
		makeGenericHighscores();
	}

	return;
}

/*!
 *	\brief Encrypts highscores array and writes it to file
 *	\param filePath defines name of file
 *	\param L_filePath defines name of file for hiding
 *	\param encryptionSeed seed used for random generator used in encryption of data
 */
static void writeHighscoresToFile(char *filePath, LPCWSTR L_filePath, unsigned int encryptionSeed) {
	extern Highscore highscores[MAX_HIGHSCORES];
	FILE *highscoresFile;
	int i;
	extern unsigned int prefixSumsBuffer[SIZE_OF_BUFFER];
	extern unsigned int bufferInt[NUMBER_OF_FILES][SIZE_OF_BUFFER];
	unsigned int prefixSumsShuffled[SIZE_OF_BUFFER];
	static int wasThisFunctionCalledBefore = 0;
	for (i = 0; i < SIZE_OF_BUFFER; i++) {
		prefixSumsBuffer[i] = i;
	}

	if (!wasThisFunctionCalledBefore) {
		seedRandomLCG((unsigned int)time(NULL));
		wasThisFunctionCalledBefore = 1;
	}
	shuffleArray(prefixSumsBuffer, SIZE_OF_BUFFER);

	memcpy(prefixSumsShuffled, prefixSumsBuffer, sizeof(prefixSumsShuffled));

	seedRandomLCG(encryptionSeed);
	encrypt(prefixSumsBuffer, sizeof(prefixSumsBuffer) / sizeof(int));
	for (i = 0; i < SIZE_OF_BUFFER; i++) {
		prefixSumsBuffer[i] |= 1U << (sizeof(int) * BITS_IN_BYTE - 1);
	}
	
	memcpy(bufferInt[0], highscores, sizeof(highscores));
	
	encrypt(bufferInt[0], sizeof(bufferInt[0]) / sizeof(int));

	fopen_s(&highscoresFile, filePath, "wb");
	if (highscoresFile != NULL) {
		for (i = 0; i < SIZE_OF_BUFFER; i++) {
			fwrite(&prefixSumsBuffer[i], sizeof(prefixSumsBuffer[i]), 1, highscoresFile);
			fwrite(&bufferInt[0][prefixSumsShuffled[i]], sizeof(bufferInt[0][i]), 1, highscoresFile);
		}
		
		fclose(highscoresFile);

		SetFileAttributes(L_filePath, FILE_ATTRIBUTE_HIDDEN);
	}
	return;
}

void writeHighscoresToFiles() {
	writeHighscoresToFile(FILE_1, L_FILE_1, seed_for_random[0]);
	writeHighscoresToFile(FILE_2, L_FILE_2, seed_for_random[1]);
	writeHighscoresToFile(FILE_3, L_FILE_3, seed_for_random[2]);
	writeHighscoresToFile(FILE_4, L_FILE_4, seed_for_random[3]);
	writeHighscoresToFile(FILE_5, L_FILE_5, seed_for_random[4]);
	return;
}
