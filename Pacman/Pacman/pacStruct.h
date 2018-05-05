#ifndef _pacStruct_h_
#define _pacStruct_h_

#define DIRECTION_UP 0
#define DIRECTION_RIGHT 1
#define DIRECTION_DOWN 2
#define DIRECTION_LEFT 3

/*
*	Direction:
*	UP -> 0
*	RIGHT -> 1
*	DOWN -> 2
*	LEFT -> 3
*/
typedef struct PacStructStruct {
	int iPosition;
	int jPosition;
	int direction;
} PacStruct;

#endif
