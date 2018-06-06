#pragma once
#ifndef _encryption_h_
#define _encryption_h_

#include "highscores.h"


void encrypt(Highscore highscores[MAX_HIGHSCORES], unsigned int seed_random_LCG);

#endif // !_encryption_h_
