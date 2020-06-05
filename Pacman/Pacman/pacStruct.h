#ifndef _pacStruct_h_
#define _pacStruct_h_

/*!	\file pacStruct.h
 *	\brief Contains declarations and constants for PacStructs
 */

#define NUMBER_OF_DIFFICULTIES 3

/*!
 *	\brief Enum containing difficulty speeds
 */
enum DifficultySpeed { EASY = 75, MEDIUM = 53, HARD = 32 , numberOfDifficulties};

/*!
 *	\brief Enum containing possible PacStruct directions
 */
enum Direction { DIRECTION_NONE = -1, DIRECTION_UP, DIRECTION_RIGHT, DIRECTION_DOWN, DIRECTION_LEFT, NUMBER_OF_DIRECTIONS };

/*!
 *	\brief Enum containing possible game modes in game
 */
enum GameMode { Normal, Reverse, EndReverse, GhostEaten };

/*!
 *	\brief Number of ghosts in game
 */
#define NUMBER_OF_GHOSTS 4

/*
 *	Direction:
 *	UP -> 0
 *	RIGHT -> 1
 *	DOWN -> 2
 *	LEFT -> 3
 *	NONE -> -1
 */

/*!
 *	\brief struct which contains everything needed for pacman and ghosts (coordinates, direction and game mode)
 */
typedef struct PacStructStruct {
	int iPosition;
	int jPosition;
	enum Direction direction;
	enum GameMode gameMode;
} PacStruct;

#endif
