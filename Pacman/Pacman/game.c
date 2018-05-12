#include "game.h"
#include "testMap.h"

void wallCheckAndMove(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct *pacStruct) {
	switch (pacStruct->direction) {
	case DIRECTION_UP:
		if (map[pacStruct->iPosition - 1][pacStruct->jPosition] == WALL) {
			pacStruct->direction = DIRECTION_NONE;
		}
		else {
			pacStruct->iPosition--;
		}
		break;
	case DIRECTION_RIGHT:
		if (map[pacStruct->iPosition][pacStruct->jPosition + 1] == WALL) {
			pacStruct->direction = DIRECTION_NONE;
		}
		else {
			pacStruct->jPosition++;
		}
		break;
	case DIRECTION_DOWN:
		if (map[pacStruct->iPosition + 1][pacStruct->jPosition] == WALL) {
			pacStruct->direction = DIRECTION_NONE;
		}
		else {
			pacStruct->iPosition++;
		}
		break;
	case DIRECTION_LEFT:
		if (map[pacStruct->iPosition][pacStruct->jPosition - 1] == WALL) {
			pacStruct->direction = DIRECTION_NONE;
		}
		else {
			pacStruct->jPosition--;
		}
		break;
	default:
		break;
	}
	return;
}

void initTempMap(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], int tempMap[HEIGHT_OF_MAP][WIDTH_OF_MAP]) {
	for (int i = 0; i < HEIGHT_OF_MAP; i++) {
		for (int j = 0; j < WIDTH_OF_MAP; j++) {
			tempMap[i][j] = map[i][j];
		}
	}
}

void initGhostsPostitions(PacStruct ghosts[NUMBER_OF_GHOSTS]) {
	
	ghosts[0].direction = DIRECTION_NONE;
	ghosts[0].iPosition = HEIGHT_OF_MAP / 2 - 2;
	ghosts[0].jPosition = WIDTH_OF_MAP / 2 - 2;

	ghosts[1].direction = DIRECTION_NONE;
	ghosts[1].iPosition = HEIGHT_OF_MAP / 2 - 2;
	ghosts[1].jPosition = WIDTH_OF_MAP / 2 - 1;

	ghosts[2].direction = DIRECTION_NONE;
	ghosts[2].iPosition = HEIGHT_OF_MAP / 2 - 2;
	ghosts[2].jPosition = WIDTH_OF_MAP / 2;

	ghosts[3].direction = DIRECTION_NONE;
	ghosts[3].iPosition = HEIGHT_OF_MAP / 2 - 2;
	ghosts[3].jPosition = WIDTH_OF_MAP / 2 + 1;
		
	return;
}

void initPacmanPosition(PacStruct *pacman) {
	pacman->direction = DIRECTION_NONE;
	pacman->iPosition = HEIGHT_OF_MAP / 2 + 7;
	pacman->jPosition = WIDTH_OF_MAP / 2;
	return;
}

int pacmanGhostCheck(PacStruct pacman, PacStruct ghost) {
	if (pacman.iPosition == ghost.iPosition && pacman.jPosition == ghost.jPosition)
		return 1;
	else
		return 0;
}

int countPacDots(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP]) {
	int i, j;
	int pacDotCount = 0;
	for (i = 0; i < HEIGHT_OF_MAP; i++) {
		for (j = 0; j < WIDTH_OF_MAP; j++) {
			if (map[i][j] == PAC_DOT) {
				pacDotCount++;
			}
		}
	}
	return pacDotCount;
}

extern SDL_Event event;

void playNewGame(enum DifficultySpeed difficulty) {
	extern int map[HEIGHT_OF_MAP][WIDTH_OF_MAP];
	int testMapTemp[HEIGHT_OF_MAP][WIDTH_OF_MAP];
	enum GameMode gameMode = Normal;
	SDL_bool isLevelRunning = SDL_TRUE;

	PacStruct pacman;
	PacStruct ghosts[4];

	int i;

	int level = -1;
	int delay;
	delay = (int)difficulty;
	int isStartOfNewGame = 1;	// NE DIRAJ OVO !!!!!

	int isPacmanEaten = 0;

	int livesCount;	// TODO: ovo promeni da bude promenljivo
	int numberOfLivesTiles;
	int pacDotCount = 0;

	// broj rezervisanih pozicija za zivote na mapi
	// i broj samih zivota odredjen tezinom igre
	switch (difficulty) {
	case EASY:
		numberOfLivesTiles= livesCount = 5;
		break;
	case MEDIUM:
		numberOfLivesTiles = livesCount = 3;
		break;
	case HARD:
		numberOfLivesTiles = livesCount = 1;
		break;
	default:
		break;
	}

	int currentScore = 0;

	while (isLevelRunning && livesCount && delay - 2 * level > 0 && game.isRunning) {
		
		// Inicijalizuje poziciju Pacman-a
		initPacmanPosition(&pacman);

		// Inicijalizuje pozicije duhova
		initGhostsPostitions(ghosts);
		
		if (pacDotCount == 0 || isStartOfNewGame) { // OVO JE ZA NOVI NIVO
			if (isStartOfNewGame) {
				isStartOfNewGame = 0;
			}
			pacDotCount = countPacDots(map); //Power Pellet-i nisu u broju dotova!!!
			level++;
			printInitMap(map, pacman, pacDotCount);
			initTempMap(map, testMapTemp);
			updateScoreBox(currentScore);
			updateLivesBox(testMapTemp, numberOfLivesTiles, livesCount);
		}
		
		while (isLevelRunning && pacDotCount && livesCount && game.isRunning && !isPacmanEaten) {
			while (SDL_PollEvent(&event) && isLevelRunning) {
				switch (event.type) {
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {

					case SDLK_ESCAPE:
						isLevelRunning = SDL_FALSE;
						break;

					case SDLK_UP:
						pacman.direction = DIRECTION_UP;
						break;

					case SDLK_DOWN:
						pacman.direction = DIRECTION_DOWN;
						break;

					case SDLK_RIGHT:
						pacman.direction = DIRECTION_RIGHT;
						break;

					case SDLK_LEFT:
						pacman.direction = DIRECTION_LEFT;
						break;

					default:
						break;
					}
					break;
				case SDL_QUIT:
					isLevelRunning = SDL_FALSE;
					game.isRunning = SDL_FALSE;
					break;
				}
			}
			
			wallCheckAndMove(testMapTemp, &pacman);

			//TODO: updateovanje gamemode-a igre, ko koga juri!!!!

			//azuriranje Score-a, da li je Pacman pojeo nesto
			gameMode = updateScoreAndGameMode(testMapTemp, pacman, &pacDotCount, &currentScore);

			// TODO: odredjivanje novih pozicija duhova
			

			// TODO: wallCheckAndMove za duhove

			// provera -> pacman i duh na istom polju pre pomeranja duhova
			for (i = 0; i < NUMBER_OF_GHOSTS; i++) {
				isPacmanEaten |= pacmanGhostCheck(pacman, ghosts[i]);
			}
			if (isPacmanEaten) {
				livesCount--;
			}

			// Azurira livesBox sa trenutnim brojem zivota
			// Moze efikasnije ako se stavi da azurira samo kada se promeni broj zivota 
			updateLivesBox(testMapTemp, numberOfLivesTiles, livesCount);

			// Poziv funkcije za grafiku -> iscrtavanje nove mape
			updateMap(testMapTemp, pacman, ghosts, delay - 2 * level);

			// NOVI DIRECTION-I DUHOVA
			ghosts[0] = BlinkyAI(map, pacman, ghosts, 0);
			ghosts[1] = InkyAI(map, pacman, ghosts, 1);
			ghosts[2] = PinkyAI(map, pacman, ghosts, 2);
			ghosts[3] = ClydeAI(map, pacman, ghosts, 3);
			for (i = 0; i < NUMBER_OF_GHOSTS; i++) {
				wallCheckAndMove(map, &ghosts[i]);
			}

			// provera -> pacman i duh na istom polju kad se pomere duhovi
			for (i = 0; i < NUMBER_OF_GHOSTS; i++) {
				isPacmanEaten |= pacmanGhostCheck(pacman, ghosts[i]);
			}
		}
		
		isPacmanEaten = 0;	// KADA SE POJEDE PACMAN, MORA DA SE RESETUJE

		// TODO: POPRAVITI OVO OBAVEZNO, MORA DA BRISE STARE POZICIJE
		if (pacman.iPosition != HEIGHT_OF_MAP / 2 + 7 || pacman.jPosition != WIDTH_OF_MAP / 2) {
			deletePacmanGhost(pacman.iPosition, pacman.jPosition);
		}
		for (i = 0; i < NUMBER_OF_GHOSTS; i++) {
			deletePacmanGhost(ghosts[i].iPosition, ghosts[i].jPosition);
		}
	}

	// TODO: ispis endgame ekrana -> pobeda ili poraz

	return;
}
