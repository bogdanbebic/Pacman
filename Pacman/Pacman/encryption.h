#pragma once
#ifndef _encryption_h_
#define _encryption_h_

/*!	\file encryption.h
*	\brief Contains function declarations for encryption
*/

#include "highscores.h"

void seedRandomLCG(unsigned int seed);

unsigned int randomLCG();

void encrypt(int *bufferInt, int sizeof_bufferInt);

#endif // !_encryption_h_
