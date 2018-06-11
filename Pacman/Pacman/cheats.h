#pragma once
#ifndef _cheats_h_
#define _cheats_h_

/*!	\file cheats.h
*	\brief Contains declarations for cheats
*/

/*!
*	\brief max speed to which the cheat for increasing speed can go
*/
#define MAX_SPEED 4

/*!
*	\brief max length of cheat activation strings
*/
#define MAX_CHEAT 15

extern int immortalityCheat;

extern char immortality[];

extern int extraLifeCheat;

extern char extraLife[];

extern int drunkCheat;

extern char drunk[];

extern int invisibilityCheat;

extern char invisibility[];

extern int throughTheWallCheat;

extern char throughTheWall[];

extern int infinityReverseCheat;

extern char infinityReverse[];

void toggleIfCheat(char cheat[]);

#endif // !_cheats_h_
