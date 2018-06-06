#include <string.h>
#include <limits.h>
#include "encryption.h"
#include "highscores.h"


#pragma region RANDOM_FUNCTIONS

/*!
*   Global variable used as seed for the
*   randomLCG pseudo random number generator
*/
unsigned int seed_LCG;

/*!
*   Seeds the randomLCG
*   pseudo random number generator
*   with argument seed
*/
void seedRandomLCG(unsigned int seed) {
	extern unsigned int seed_LCG;
	seed_LCG = seed;
	return;
}

/*!
*   Finds a pseudo random number
*   using a LCG algorithm
*   Return value:
*   pseudo random unsigned int in range [0, UINT_MAX)
*/
unsigned int randomLCG() {
	extern unsigned int seed_LCG;
	unsigned int mul = 48271U, inc = 1U, mod = UINT_MAX;
	seed_LCG = (mul * seed_LCG + inc) % mod;
	return seed_LCG;
}
#pragma endregion


/*!
*	Encypts/decrypts the the contents of
*	argument highscores using XOR operation
*	and pseudo random number generator
*	with seed seed_random_LCG
*/
void encrypt(Highscore highscores[MAX_HIGHSCORES], unsigned int seed_random_LCG) {
	int *ptr = (int*)highscores, *start = (int*)highscores;
	seedRandomLCG(seed_random_LCG);
	while (ptr < start + MAX_HIGHSCORES * 4) {	// Constant depends on sizeof(highscores) -> not std defined
		*ptr ^= randomLCG();
		ptr++;
	}
	return;
}

/*
*	POPRAVI OVO
*/
//void generateMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
//	int indices[MATRIX_ELEMENTS];
//	int i, index, t;
//	double randomNumber;
//	for (i = 0; i < MATRIX_ELEMENTS; i++) {
//		indices[i] = i;
//	}
//	for (i = 0; i < MATRIX_ELEMENTS; i++) {
//		randomNumber = (double)rand() / (RAND_MAX + 1);
//		index = (int)(randomNumber * (MATRIX_ELEMENTS - i) + i);
//		t = indices[i];
//		indices[i] = indices[index];
//		indices[index] = t;
//	}
//	for (i = 0; i < MATRIX_ELEMENTS; i++) {
//		matrix[indices[i] / MATRIX_SIZE][indices[i] % MATRIX_SIZE] = i;
//	}
//	return;
//}




/*
*	Encrypts extern Highscores buffer
*/
//void encrypt() {
//	extern Highscore highscores[MAX_HIGHSCORES];
//	int *ptr = (int*)highscores;
//
//	while (ptr < (int*)(&highscores + 1)) {
//		*ptr ^= XOR_KEY_INT + XOR_KEY; // TODO: LCG generator for XOR
//		ptr++;
//	}
//
//	return;
//}
