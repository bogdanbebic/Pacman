#include <string.h>
#include "cheats.h"

/* !!!!!!!!!! CHEAT CODES MUST BE LESS THAN 15 STRLEN !!!!!!!!!! */

int immortalityCheat;

char immortality[] = "baguvix";

int extraLifeCheat;

char extraLife[] = "hesoyam";

int drunkCheat;

char drunk[] = "elektrijada";

int invisibilityCheat;

char invisibility[] = "mcstojan";

int speed;

int increaseSpeedCheat;

char increaseSpeed[] = "acalukas";

int throughTheWallCheat;

char throughTheWall[] = "ekvzid";

int infinityReverseCheat;

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
