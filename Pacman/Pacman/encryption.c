#include <string.h>
#include "encryption.h"
#include "highscores.h"


/*
*	Encrypts extern Highscores buffer
*/
void encrypt() {
	extern Highscore highscores[MAX_HIGHSCORES];
	int *ptr = (int*)highscores;

	while (ptr < (int*)(&highscores + 1)) {
		*ptr ^= XOR_KEY_INT + XOR_KEY; // TODO: LCG generator for XOR
		ptr++;
	}

	return;
}
