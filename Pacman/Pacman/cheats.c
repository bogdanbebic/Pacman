#include <string.h>
#include "cheats.h"

/*!	\file cheats.c
*	\brief Contains global variables for cheats and cheat toggling function definitions
*/

/* !!!!!!!!!! CHEAT CODES MUST BE LESS THAN 15 STRLEN !!!!!!!!!! */

/*!
*	\brief if != 0 then pacman can be at the same spot as a ghost
*/
int immortalityCheat;

/*!
*	\brief immortality activation string
*/
char immortality[] = "baguvix";


/*!
*	\brief if != 0 then pacman gets an extra life
*/
int extraLifeCheat;

/*!
*	\brief extra life activation string
*/
char extraLife[] = "hesoyam";


/*!
*	\brief if != 0 then controls are inverted
*/
int drunkCheat;

/*!
*	\brief drunk activation string
*/
char drunk[] = "elektrijada";


/*!
*	\brief if != 0 then pacman is not shown on map
*/
int invisibilityCheat;

/*!
*	\brief invisibility activation string
*/
char invisibility[] = "mcstojan";


/*!
*	\brief variable which affects the speed of pacman
*/
int speed;

/*!
*	\brief if != 0 then pacmans speed will increase
*/
int increaseSpeedCheat;

/*!
*	\brief increase speed activation string
*/
char increaseSpeed[] = "acalukas";


/*!
*	\brief if != 0 then pacman can go through walls
*/
int throughTheWallCheat;

/*!
*	\brief through the wall activation string
*/
char throughTheWall[] = "ekvzid";


/*!
*	\brief if != 0 then power pellet effect lasts until ghost is eaten
*/
int infinityReverseCheat;

/*!
*	\brief infinity reverse activation string
*/
char infinityReverse[] = "rasta";

/*!
*	\brief Toggles argument
*/
#define TOGGLE_CHEAT(x) ((x) = (x) == 1 ? 0 : 1)

/*!
*	\brief Toggles cheat if argument is a cheat
*	\param cheat string which was typed in
*/
void toggleIfCheat(char cheat[]) {
	if (strcmp(cheat, immortality) == 0) {
		TOGGLE_CHEAT(immortalityCheat);
	}
	if (strcmp(cheat, extraLife) == 0) {
		TOGGLE_CHEAT(extraLifeCheat);
	}
	if (strcmp(cheat, drunk) == 0) {
		TOGGLE_CHEAT(drunkCheat);
	}
	if (strcmp(cheat, invisibility) == 0) {
		TOGGLE_CHEAT(invisibilityCheat);
	}
	if (strcmp(cheat, throughTheWall) == 0) {
		TOGGLE_CHEAT(throughTheWallCheat);
	}
	if (strcmp(cheat, infinityReverse) == 0) {
		TOGGLE_CHEAT(infinityReverseCheat);
	}
	/*if (strcmp(cheat, increaseSpeed) == 0) {
		if (speed + 2 < MAX_SPEED) {
			speed += 2;
		}
		increaseSpeedCheat = 0;
	}*/
	return;
}
