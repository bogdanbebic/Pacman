#include <string.h>
#include <limits.h>
#include "encryption.h"
#include "highscores.h"

/*!	\file encryption.c
*	\brief Contains random, encryption and recovery function definitions
*/

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
*	\brief Max number which can be produced by randomLCG()
*/
#define RANDOM_LCG_MAX (UINT_MAX >> 1)

/*!
*   \brief Finds a pseudo random number using a LCG algorithm
*   \return pseudo random unsigned int in range [0, UINT_MAX >> 1]
*/
unsigned int randomLCG() {
	extern unsigned int seed_LCG;
	unsigned int mul = 1664525U, inc = 1013904223U;
	seed_LCG = (unsigned int)(((unsigned long long)mul * (unsigned long long)seed_LCG + inc)) >> 1;
	return seed_LCG;
}

/*!
*	\brief Shuffles array
*	\param a array to be shuffled
*	\param size_of_a number of elements in array a
*/
void shuffleArray(int *a, int size_of_a) {
	int i;
	int index, t;
	double randomNumber;
	for (i = 0; i < size_of_a; i++) {
		randomNumber = ((double)randomLCG() / (RANDOM_LCG_MAX + 1));
		index = (int)(randomNumber * (size_of_a - i) + i);
		t = a[i];
		a[i] = a[index];
		a[index] = t;
	}
	return;
}

/*!
*	\brief Encypts/decrypts using XOR operation and pseudo random LCG
*	\param highscores encryption is on this argument
*	\param seed_random_LCG seed for LCG random generators
*/
void encrypt(int *bufferInt, int sizeof_bufferInt) {
	int *ptr = bufferInt, *start = bufferInt;
	while (ptr < start + sizeof_bufferInt) {	// Constant depends on sizeof(highscores) -> not std defined
		*ptr ^= randomLCG();
		ptr++;
	}
	return;
}
