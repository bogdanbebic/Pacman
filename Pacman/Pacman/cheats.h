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

/*!
*	\brief if != 0 then pacman can be at the same spot as a ghost
*/
extern int immortalityCheat;

/*!
*	\brief immortality activation string
*/
extern char immortality[];

/*!
*	\brief if != 0 then pacman gets an extra life
*/
extern int extraLifeCheat;

/*!
*	\brief extra life activation string
*/
extern char extraLife[];

/*!
*	\brief if != 0 then controls are inverted
*/
extern int drunkCheat;

/*!
*	\brief drunk activation string
*/
extern char drunk[];

/*!
*	\brief if != 0 then pacman is not shown on map
*/
extern int invisibilityCheat;

/*!
*	\brief invisibility activation string
*/
extern char invisibility[];

/*!
*	\brief if != 0 then pacman can go through walls
*/
extern int throughTheWallCheat;

/*!
*	\brief through the wall activation string
*/
extern char throughTheWall[];

/*!
*	\brief if != 0 then power pellet effect lasts until ghost is eaten
*/
extern int infinityReverseCheat;

/*!
*	\brief infinity reverse activation string
*/
extern char infinityReverse[];

/*!
*	\brief Toggles cheat if argument is a cheat
*	\param cheat string which was typed in
*/
void toggleIfCheat(char cheat[]);

#endif // !_cheats_h_
