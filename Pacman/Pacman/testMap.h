#ifndef _testMap_h_
#define _testMap_h_
#include "gameMap.h"
/*
*	Test map 1:
*	samo zidovi na krajevima mape
*	ostatak mape prazan
*/
int testMap1[HEIGHT_OF_MAP][WIDTH_OF_MAP] = { { WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL },
{ WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL,  WALL },
{ WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL,  WALL },
{ WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL,  WALL },
{ WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL,  WALL },
{ WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL,  WALL },
{ WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL,  WALL },
{ WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL,  WALL },
{ WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL,  WALL },
{ WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL } };
int pacDotCountTestMap1 = 0;

/*
*	Test map 2:
*	samo zidovi na krajevima mape
*	u prvoj nezid vrsti PAC_DOT-ovi
*	ostatak mape prazan
*/
int testMap2[HEIGHT_OF_MAP][WIDTH_OF_MAP] = { { WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL },
{ WALL, POWER_PELLET, PAC_DOT, PAC_DOT, PAC_DOT, PAC_DOT, PAC_DOT, PAC_DOT, POWER_PELLET,  WALL },
{ WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL,  WALL },
{ WALL, NO_WALL, NO_WALL, WALL, WALL, WALL, WALL, NO_WALL, NO_WALL,  WALL },
{ WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL,  WALL },
{ WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL,  WALL },
{ WALL, NO_WALL, NO_WALL, WALL, WALL, WALL, WALL, NO_WALL, NO_WALL,  WALL },
{ WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL,  WALL },
{ WALL, POWER_PELLET, PAC_DOT, PAC_DOT, PAC_DOT, PAC_DOT, PAC_DOT, PAC_DOT, POWER_PELLET,  WALL },
{ WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL } };
int pacDotCountTestMap2 = 8;

#endif // !_testMap_h_
