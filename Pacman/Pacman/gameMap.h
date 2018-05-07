#ifndef _gameMap_h_
#define _gameMap_h_

#define HEIGHT_OF_MAP 10 // nesto popuni kako treba
#define WIDTH_OF_MAP 10 // nesto popuni kako treba

#define WALL -1
#define NO_WALL 0
#define PAC_DOT 1
#define POWER_PELLET 2

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
										{ WALL, PAC_DOT, PAC_DOT, PAC_DOT, PAC_DOT, PAC_DOT, PAC_DOT, PAC_DOT, PAC_DOT,  WALL },
										{ WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL,  WALL },
										{ WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL,  WALL },
										{ WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL,  WALL },
										{ WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL,  WALL },
										{ WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL,  WALL },
										{ WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL,  WALL },
										{ WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL, NO_WALL,  WALL },
										{ WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL } };
int pacDotCountTestMap2 = 8;

#endif
