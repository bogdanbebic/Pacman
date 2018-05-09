#ifndef _pacStruct_h_
#define _pacStruct_h_



enum Direction { DIRECTION_NONE = -1, DIRECTION_UP, DIRECTION_RIGHT, DIRECTION_DOWN, DIRECTION_LEFT, NUMBER_OF_DIRECTIONS };

#define NUMBER_OF_GHOSTS 4

/*
*	Direction:
*	UP -> 0
*	RIGHT -> 1
*	DOWN -> 2
*	LEFT -> 3
*	NONE -> -1
*/
typedef struct PacStructStruct {
	int iPosition;
	int jPosition;
	enum Direction direction;
} PacStruct;

#endif
