#pragma once
#ifndef _encryption_h_
#define _encryption_h_

/*!	\file encryption.h
*	\brief Contains function declarations for encryption
*/

#include "highscores.h"

/*!
*   \brief Seeds the randomLCG pseudo random number generator with argument seed
*	\param seed seed for LCG random generator
*/
void seedRandomLCG(unsigned int seed);

/*!
*   \brief Finds a pseudo random number using a LCG algorithm
*   \return pseudo random unsigned int in range [0, UINT_MAX >> 1]
*/
unsigned int randomLCG();

/*!
*	\brief Shuffles array
*	\param a array to be shuffled
*	\param size_of_a number of elements in array a
*/
void shuffleArray(int *a, int size_of_a);

/*!
*	\brief Encypts/decrypts using XOR operation and pseudo random LCG
*	\param highscores encryption is on this argument
*	\param seed_random_LCG seed for LCG random generators
*/
void encrypt(int *bufferInt, int sizeof_bufferInt);

#endif // !_encryption_h_
