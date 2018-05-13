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

enum GameMode updateScoreAndGameMode(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman, PacStruct ghosts[], int * pacDotCount, int * currentScore, enum GameMode *gameMode) {
	int i;
	if (map[pacman.iPosition][pacman.jPosition] == PAC_DOT) {
		*currentScore += 10;
		map[pacman.iPosition][pacman.jPosition] = NO_WALL;
		(*pacDotCount)--;
	}
	else if (map[pacman.iPosition][pacman.jPosition] == POWER_PELLET) {
		map[pacman.iPosition][pacman.jPosition] = NO_WALL;
		*currentScore += 50;
		*gameMode = Reverse;
	}
	if (*gameMode == Reverse) {
		for (i = 0; i < NUMBER_OF_GHOSTS; i++) {
			if (pacmanGhostCheck(pacman, ghosts[i])) {
				*currentScore += 200;
				// TODO: VRATI DUHA NA POCETNO MESTO !!!!!!!!!
			}
		}
	}

	//TODO:update-ovanje scora kada pacman pojede vockice

	updateScoreBox(*currentScore);
	return *gameMode;
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

void initNewGame(enum DifficultySpeed difficulty, int *delay, int *level, int *livesCount, int *numberOfLivesTiles, int *currentScore, enum GameMode *gameMode, int *isStartOfNewGame) {
	*isStartOfNewGame = 1;
	*gameMode = Normal;
	*level = -1;
	*delay = (int)difficulty;

	// broj rezervisanih pozicija za zivote na mapi
	// i broj samih zivota odredjen tezinom igre
	switch (difficulty) {
	case EASY:
		*numberOfLivesTiles = *livesCount = 5;
		break;
	case MEDIUM:
		*numberOfLivesTiles = *livesCount = 3;
		break;
	case HARD:
		*numberOfLivesTiles = *livesCount = 1;
		break;
	default:
		break;
	}
	*currentScore = 0;
}

extern SDL_Event event;

void playNewGame(enum DifficultySpeed difficulty) {
	extern int map[HEIGHT_OF_MAP][WIDTH_OF_MAP];

	int testMapTemp[HEIGHT_OF_MAP][WIDTH_OF_MAP];

	SDL_bool isLevelRunning = SDL_TRUE;

	PacStruct pacman;
	PacStruct ghosts[4];
	enum GameMode gameMode;
	int livesCount;
	int numberOfLivesTiles;
	int currentScore;
	int level;
	int delay;
	int pacDotCount;
	int isStartOfNewGame;

	int i;
	int isPacmanEaten = 0;
	pacDotCount = countPacDots(map); //Power Pellet-i nisu u broju dotova!!!

	initNewGame(difficulty, &delay, &level, &livesCount, &numberOfLivesTiles, &currentScore, &gameMode, &isStartOfNewGame);

	while (isLevelRunning && livesCount && delay - 2 * level > 0 && game.isRunning) {
		
		/*
		*	TODO:
		*	Prebaciti ovo u neki newGameInit
		*	da bi mogao continue game lepo da se radi
		*/
		// Inicijalizuje poziciju Pacman-a
		initPacmanPosition(&pacman);
		// Crtanje Pacman-a
		drawInitPacman(pacman);
		// Inicijalizuje pozicije duhova
		initGhostsPostitions(ghosts);
		
		if (isStartOfNewGame || pacDotCount == 0) { // OVO JE ZA NOVI NIVO
			if (isStartOfNewGame) {
				isStartOfNewGame = 0;
			}
			level++;
			printInitMap(map, pacman, pacDotCount);
			initTempMap(map, testMapTemp);
			updateScoreBox(currentScore);
			updateLivesBox(testMapTemp, numberOfLivesTiles, livesCount);
			pacDotCount = countPacDots(testMapTemp);
		}
		
		while (isLevelRunning && pacDotCount && livesCount && game.isRunning && !isPacmanEaten) {

			/*
			*	TODO:
			*	prebaciti u funkciju
			*	za dohvatanje user input-a
			*	za Pacman-a
			*/
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
			/*
			*	Popraviti ovu funkciju
			*	da bude elegantnija
			*/
			gameMode = updateScoreAndGameMode(testMapTemp, pacman, ghosts, &pacDotCount, &currentScore, &gameMode);

			// provera -> pacman i duh na istom polju pre pomeranja duhova
			for (i = 0; i < NUMBER_OF_GHOSTS; i++) {
				isPacmanEaten |= pacmanGhostCheck(pacman, ghosts[i]);
			}

			// Poziv funkcije za grafiku -> iscrtavanje nove mape
			updateMap(testMapTemp, pacman, ghosts, delay - 2 * level);

			// NOVI DIRECTION-I DUHOVA
			//ghosts[0] = BlinkyAI(map, pacman, ghosts, 0);
			//ghosts[1] = InkyAI(map, pacman, ghosts, 1);
			//ghosts[2] = PinkyAI(map, pacman, ghosts, 2);
			//ghosts[3] = ClydeAI(map, pacman, ghosts, 3);
			for (i = 0; i < NUMBER_OF_GHOSTS; i++) {
				wallCheckAndMove(map, &ghosts[i]);
			}

			// provera -> pacman i duh na istom polju kad se pomere duhovi
			for (i = 0; i < NUMBER_OF_GHOSTS; i++) {
				isPacmanEaten |= pacmanGhostCheck(pacman, ghosts[i]);
			}

			if (isPacmanEaten) {
				livesCount--;

				// Azurira livesBox sa trenutnim brojem zivota
				// Moze efikasnije ako se stavi da azurira samo kada se promeni broj zivota 
				updateLivesBox(testMapTemp, numberOfLivesTiles, livesCount);
			}
		}
		
		isPacmanEaten = 0;	// KADA SE POJEDE PACMAN, MORA DA SE RESETUJE

		// TODO: POPRAVITI OVO OBAVEZNO, MORA DA BRISE STARE POZICIJE
		for (i = 0; i < NUMBER_OF_GHOSTS; i++) {
			deletePacmanGhost(ghosts[i]);
		}
		if (pacman.iPosition != HEIGHT_OF_MAP / 2 + 7 || pacman.jPosition != WIDTH_OF_MAP / 2) {
			deletePacmanGhost(pacman);
		}
	}

	// TODO: ispis endgame ekrana -> pobeda ili poraz

	return;
}
