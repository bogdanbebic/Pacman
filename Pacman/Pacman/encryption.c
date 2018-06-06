#include <string.h>
#include "encryption.h"
#include "highscores.h"



/*!
*   \brief Global variable used as seed for the randomLCG pseudo random number generator
*/
unsigned int seed_LCG;

/*!
*   \brief Seeds the randomLCG pseudo random number generator with argument seed
*	\param seed seed for LCG random generator
*/
void seedRandomLCG(unsigned int seed) {
	extern unsigned int seed_LCG;
	seed_LCG = seed;
	return;
}

/*!
*   \brief Finds a pseudo random number using a LCG algorithm
*   \return pseudo random unsigned int in range [0, UINT_MAX)
*/
unsigned int randomLCG() {
	extern unsigned int seed_LCG;
	unsigned int mul = 1664525U, inc = 1013904223U;
	seed_LCG = (mul * seed_LCG + inc);
	return seed_LCG;
}


/*!
*	\brief Encypts/decrypts using XOR operation and pseudo random LCG
*	\param highscores encryption is on this argument
*	\param seed_random_LCG seed for LCG random generators
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
