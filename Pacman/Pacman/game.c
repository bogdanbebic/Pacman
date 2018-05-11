#include "game.h"
#include "testMap.h"

void wallCheckAndMove(int map[HEIGHT_OF_MAP][HEIGHT_OF_MAP], PacStruct *pacStruct) {
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

void initTempMap(int map[HEIGHT_OF_MAP][HEIGHT_OF_MAP], int tempMap[HEIGHT_OF_MAP][HEIGHT_OF_MAP]) {
	for (int i = 0; i < HEIGHT_OF_MAP; i++) {
		for (int j = 0; j < WIDTH_OF_MAP; j++) {
			tempMap[i][j] = map[i][j];
		}
	}
}

extern SDL_Event event;

void playNewGame(enum DifficultySpeed difficulty) {
	extern int testMap2[HEIGHT_OF_MAP][WIDTH_OF_MAP];	// Za potrebe testiranja
	int testMapTemp[HEIGHT_OF_MAP][WIDTH_OF_MAP];
	/* Promeniti mapu koja se koristi */
	extern int pacDotCountTestMap2;
	enum GameMode gameMode = Normal;
	SDL_bool isLevelRunning = SDL_TRUE;

	PacStruct pacman;
	PacStruct ghosts[4];

	int level = -1;
	int delay;
	delay = (int)difficulty;
	int isStartOfNewGame = 1;	// NE DIRAJ OVO !!!!!

	int livesCount;	// TODO: ovo promeni da bude promenljivo
	int numberOfLivesTiles;
	int pacDotCount = 0;

	//broj rezervisanih pozicija za zivote na mapi
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

	//int pacDotCount = pacDotCountTestMap2;	// TODO: ucitaj broj coinova sa mape, NE OVAKO !!!!!
	int currentScore = 0;


	while (isLevelRunning && livesCount && delay - 2 * level > 0 && game.isRunning) {
		
		/*
		*	Ove vrednosti ispod su proizvoljne
		*	za	potrebe testiranja, kasnije ih
		*	treba promeniti u nesto smisleno
		*/
		pacman.direction = DIRECTION_NONE;
			// TODO: ucitaj broj coinova sa mape, NE OVAKO !!!!!
		pacman.iPosition = HEIGHT_OF_MAP / 2;
		pacman.jPosition = WIDTH_OF_MAP / 2;
		
		if (pacDotCount == 0 || isStartOfNewGame) { // OVO JE ZA NOVI NIVO
			if (isStartOfNewGame) {
				isStartOfNewGame = 0;
			}
			pacDotCount = pacDotCountTestMap2; //Power Pellet-i nisu u broju dotova!!!
			level++;
			printInitMap(testMap2, pacman, pacDotCount);
			initTempMap(testMap2, testMapTemp);
			updateScoreBox(currentScore);
			updateLivesBox(testMapTemp, numberOfLivesTiles, livesCount);
		}
		
		while (isLevelRunning && pacDotCount && livesCount && game.isRunning) {
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
			
			//azuriranje Score-a, da li je Pacman pojeo nesto
			//TODO: updateovanje gamemode-a igre, ko koga juri!!!!
			gameMode = updateScoreAndGameMode(testMapTemp, pacman, &pacDotCount, &currentScore);

			// TODO: odredjivanje novih pozicija duhova
			// TODO: wallCheckAndMove za duhove
			// TODO: provera -> pacman i duh na istom polju

			//azurira livesBox sa trenutnim brojem zivota
			//moze efikasnije ako se stavi da azurira samo kada se promeni broj zivota 
			updateLivesBox(testMapTemp, numberOfLivesTiles, livesCount);

			// Poziv funkcije za grafiku -> iscrtavanje nove mape
			updateMap(testMapTemp, pacman, ghosts, delay - 2 * level);
		}
		//ako se stavi u komentar igrica moze da se ugasi samo ako se direktno zatvori prozor igre
		if (pacDotCount != 0) { // TODO: ne menjaj ga ovako, nego kad crkne !!!!!!!!!!
			livesCount--;		
		}

		// OVO JE OVDE ZBOG DEBAGOVANJA
		isLevelRunning = SDL_TRUE;	// TODO: OVO SE NE MENJA OVDE, SAMO GORE
		
		if (pacman.iPosition != HEIGHT_OF_MAP / 2 || pacman.jPosition != WIDTH_OF_MAP / 2) {
			deletePacmanGhost(pacman.iPosition, pacman.jPosition);
		}
	}
	// TODO: ispis endgame ekrana -> pobeda ili poraz
	return;
}
