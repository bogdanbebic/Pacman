#include "game.h"
#include "testMap.h"
#include "pauseMenuGraphics.h"
#include "saveGame.h"
#include <Windows.h>

SaveGame saveGame;

/*
*	Moves pacStruct on map,
*	prevents pacStruct to be in wall
*	Return value:
*	1 if pacStruct moved
*	0 otherwise
*/
int wallCheckAndMove(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct *pacStruct) {
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
		if (map[pacStruct->iPosition][((pacStruct->jPosition + 1) % WIDTH_OF_MAP)] == WALL) {
			pacStruct->direction = DIRECTION_NONE;
		}
		else {
			pacStruct->jPosition = (pacStruct->jPosition + 1) % WIDTH_OF_MAP;
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
		if (map[pacStruct->iPosition][(pacStruct->jPosition - 1 + WIDTH_OF_MAP) % WIDTH_OF_MAP] == WALL) {
			pacStruct->direction = DIRECTION_NONE;
		}
		else {
			pacStruct->jPosition = (pacStruct->jPosition - 1 + WIDTH_OF_MAP) % WIDTH_OF_MAP;
		}
		break;
	default:
		break;
	}
	if (pacStruct->direction == DIRECTION_NONE)
		return 0;
	else
		return 1;
}

//void changeDirectionForReverseGhost(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct *pacStruct) {
//	pacStruct->direction = (pacStruct->direction + (NUMBER_OF_DIRECTIONS / 2)) % NUMBER_OF_DIRECTIONS;
//	PacStruct temp = *pacStruct;
//	if (!wallCheckAndMove(map, &temp)) {
//		temp.direction = (pacStruct->direction + 1) % NUMBER_OF_DIRECTIONS;
//		if (wallCheckAndMove(map, &temp)) {
//			pacStruct->direction = (pacStruct->direction + 1) % NUMBER_OF_DIRECTIONS;
//		}
//		else {
//			pacStruct->direction = (pacStruct->direction - 1) % NUMBER_OF_DIRECTIONS;
//		}
//	}
//	return;
//}

void changeDirectionForReverseGhost(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct *pacStruct) {
	pacStruct->direction = (pacStruct->direction + (NUMBER_OF_DIRECTIONS / 2)) % NUMBER_OF_DIRECTIONS;
	PacStruct temp = *pacStruct;
	if (!wallCheckAndMove(map, &temp)) {
		temp.direction = (pacStruct->direction + 1) % NUMBER_OF_DIRECTIONS;
		if (wallCheckAndMove(map, &temp)) {
			pacStruct->direction = (pacStruct->direction + 1) % NUMBER_OF_DIRECTIONS;
		}
		else {
			pacStruct->direction = (pacStruct->direction - 1 + NUMBER_OF_DIRECTIONS) % NUMBER_OF_DIRECTIONS; //ovde je bila greska
		}
	}
	return;
}

/*
*	Initializes temporary map
*	which is used in a single level
*/
void initTempMap(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], int tempMap[HEIGHT_OF_MAP][WIDTH_OF_MAP]) {
	for (int i = 0; i < HEIGHT_OF_MAP; i++) {
		for (int j = 0; j < WIDTH_OF_MAP; j++) {
			tempMap[i][j] = map[i][j];
		}
	}
}

/*
*	Initializes starting ghosts
*	positions on map
*/
void initGhosts(PacStruct ghosts[NUMBER_OF_GHOSTS]) {
	
	ghosts[0].gameMode = Normal;
	ghosts[0].direction = DIRECTION_NONE;
	ghosts[0].iPosition = HEIGHT_OF_MAP / 2 - 2;
	ghosts[0].jPosition = WIDTH_OF_MAP / 2 - 2;

	ghosts[1].gameMode = Normal;
	ghosts[1].direction = DIRECTION_NONE;
	ghosts[1].iPosition = HEIGHT_OF_MAP / 2 - 2;
	ghosts[1].jPosition = WIDTH_OF_MAP / 2 - 1;

	ghosts[2].gameMode = Normal;
	ghosts[2].direction = DIRECTION_NONE;
	ghosts[2].iPosition = HEIGHT_OF_MAP / 2 - 2;
	ghosts[2].jPosition = WIDTH_OF_MAP / 2;

	ghosts[3].gameMode = Normal;
	ghosts[3].direction = DIRECTION_NONE;
	ghosts[3].iPosition = HEIGHT_OF_MAP / 2 - 2;
	ghosts[3].jPosition = WIDTH_OF_MAP / 2 + 1;
		
	return;
}

/*
*	Initializes starting pacman
*	position on map
*/
void initPacmanPosition(PacStruct *pacman) {
	pacman->direction = DIRECTION_NONE;
	pacman->iPosition = HEIGHT_OF_MAP / 2 + 7;
	pacman->jPosition = WIDTH_OF_MAP / 2;
	return;
}

/*
*	Checks if pacman and and ghost
*	have the same coordinates
*	Return value:
*	1 for same coordinates
*	0 for different coordinates
*/
int pacmanGhostCheck(PacStruct pacman, PacStruct ghost) {
	if (pacman.iPosition == ghost.iPosition && pacman.jPosition == ghost.jPosition)
		return 1;
	else
		return 0;
}

/*
*	Updates the currentScore and
*	gameMode if pacman has eaten
*	a power pellet
*	Returnn value:
*	Reverse if pacman has eaten a power pellet
*	gameMode (unchanged) otherwise
*/
void updateScoreAndGameMode(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman, PacStruct ghosts[], int * pacDotCount, Highscore * currentScore) {
	int i;
	if (map[pacman.iPosition][pacman.jPosition] == PAC_DOT) {
		currentScore->points += 10;
		map[pacman.iPosition][pacman.jPosition] = NO_WALL;
		(*pacDotCount)--;
	}
	else if (map[pacman.iPosition][pacman.jPosition] == POWER_PELLET) {
		map[pacman.iPosition][pacman.jPosition] = NO_WALL;
		currentScore->points += 50;
		for (i = 0; i < NUMBER_OF_GHOSTS; i++)
			if (ghosts[i].gameMode != GhostEaten) {
				ghosts[i].gameMode = Reverse;
			}
	}
	for (i = 0; i < NUMBER_OF_GHOSTS; i++) {
		if (pacmanGhostCheck(pacman, ghosts[i]) && (ghosts[i].gameMode == Reverse || ghosts[i].gameMode == EndReverse)) {
			currentScore->points += 200;
			// TODO: VRATI DUHA NA POCETNO MESTO !!!!!!!!!
		}
	}
	// TODO: update-ovanje scora kada pacman pojede vockice
	updateScoreBox(*currentScore);
	return;
}

/*
*	Counts pacDot-s on given map
*	Return value:
*	count of pacDot-s
*/
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

void initLevel(PacStruct *pacman, PacStruct *ghosts) {
	// Inicijalizuje poziciju Pacman-a
	initPacmanPosition(pacman);
	// Crtanje Pacman-a
	//drawInitPacman(*pacman);
	// Inicijalizuje pozicije duhova
	initGhosts(ghosts);
	return;
}

/*
*	Initializes a new game
*	with new game parameters.
*	Sets values for all arguments except difficulty
*/
void initNewGame(enum DifficultySpeed difficulty, int *delay, int *level, int *livesCount, int *numberOfLivesTiles, Highscore *currentScore, int *isStartOfNewGame, PacStruct *home) {
	*isStartOfNewGame = 1;
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
	currentScore->ghosts = 0;
	currentScore->pacDots = 0;
	currentScore->points = 0;
	currentScore->powerPellets = 0;

	home->gameMode = Normal;
	home->direction = DIRECTION_NONE;
	home->iPosition = HEIGHT_OF_MAP / 2 - 1;
	home->jPosition = WIDTH_OF_MAP / 2 - 2;

	return;
}

/*
*	Initializes continue game
*	with saved game parameters.
*	Sets values for all arguments except difficulty
*/
void initContinueGame(enum DifficultySpeed difficulty, int *delay, int *level, int *livesCount, int *numberOfLivesTiles, Highscore *currentScore, int *isStartOfNewGame, PacStruct *home, int *pacDotCount) {
	extern SaveGame saveGame;

	*delay = saveGame.delay;
	*level = saveGame.level;
	*livesCount = saveGame.livesCount;
	*numberOfLivesTiles = saveGame.numberOfLivesTiles;
	*currentScore = saveGame.currentScore;
	*isStartOfNewGame = saveGame.isStartOfNewGame;
	*home = saveGame.home;
	*pacDotCount = saveGame.pacDotCount;
	return;
}

extern SDL_Event event;
extern SDL_Texture* ScoreBoxTexture, *LivesBoxTexture;

/*
*	Gets pacman direction from user
*	Return value:
*	enum Direction which marks direction that 
*	the user has given as input or DIRECTION_NONE
*	if user has given input whhich is not correct
*/
enum Direction getPacmanDirectionFromUser(SDL_Event event) {
	switch (event.key.keysym.sym) {
	case SDLK_UP:
		return DIRECTION_UP;
		break;

	case SDLK_DOWN:
		return DIRECTION_DOWN;
		break;

	case SDLK_RIGHT:
		return DIRECTION_RIGHT;
		break;

	case SDLK_LEFT:
		return DIRECTION_LEFT;
		break;
	default:
		return DIRECTION_NONE;
		break;
	}
}

/*
*	Saves current game
*	and makes it possible
*	to continue game
*/
void saveGameForContinue(enum DifficultySpeed difficulty, int delay, int level, int livesCount, int numberOfLivesTiles, Highscore currentScore, int isStartOfNewGame, PacStruct home, PacStruct pacman, PacStruct ghosts[], int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], int pacDotCount) {
	extern SaveGame saveGame;
	int i, j;
	saveGame.difficulty = difficulty;
	saveGame.delay = delay;
	saveGame.level = level;
	saveGame.livesCount = livesCount;
	saveGame.numberOfLivesTiles = numberOfLivesTiles;
	saveGame.currentScore = currentScore;
	saveGame.isStartOfNewGame = isStartOfNewGame;
	saveGame.home = home;
	saveGame.pacman = pacman;
	saveGame.pacDotCount = pacDotCount;
	for (i = 0; i < NUMBER_OF_GHOSTS; i++) {
		saveGame.ghosts[i] = ghosts[i];
	}
	for (i = 0; i < HEIGHT_OF_MAP; i++) {
		for (j = 0; j < WIDTH_OF_MAP; j++) {
			saveGame.map[i][j] = map[i][j];
		}
	}
	return;
}

/*
*	Sets up and plays new Pacman game
*	according to the argument difficulty
*	Return value:
*	currentScore is the score that 
*	the player has accumulated in the game
*/
Highscore playGame(enum GameType gameType, enum DifficultySpeed difficulty) {
	extern int map[HEIGHT_OF_MAP][WIDTH_OF_MAP];

	int testMapTemp[HEIGHT_OF_MAP][WIDTH_OF_MAP];

	SDL_bool isLevelRunning = SDL_TRUE;
	SDL_bool isPauseMenu = SDL_FALSE;

	enum PauseMenuOptions selectedOption;
	PacStruct pacman;
	PacStruct ghosts[4];
	int livesCount;
	int numberOfLivesTiles;
	Highscore currentScore;
	int level;
	int delay;
	int pacDotCount;
	int isStartOfNewGame;
	int gameContinuation = 0;//dodati u funkciju za inicijalizaciju

	PacStruct home;

	int srbendaMod = 0;

	int timer_tick = 0;
	int i;
	int isPacmanEaten = 0;
	pacDotCount = countPacDots(map); // Power Pellet-i nisu u broju dotova!!!

	switch (gameType) {
	case DEMO_GAME:
	case NEW_GAME:
		initNewGame(difficulty, &delay, &level, &livesCount, &numberOfLivesTiles, &currentScore, &isStartOfNewGame, &home);
		break;
	case CONTINUE_GAME:
		gameContinuation = 1;
		initContinueGame(difficulty, &delay, &level, &livesCount, &numberOfLivesTiles, &currentScore, &isStartOfNewGame, &home, &pacDotCount);
		int i, j;
		for (i = 0; i < HEIGHT_OF_MAP; i++) {
			for (j = 0; j < WIDTH_OF_MAP; j++) {
				testMapTemp[i][j] = saveGame.map[i][j];
			}
		}
		pacman = saveGame.pacman;
		for (i = 0; i < NUMBER_OF_GHOSTS; i++) {
			ghosts[i] = saveGame.ghosts[i];
		}
		break;
	default:
		break;
	}
	
	int cnt = 0;
	while (isLevelRunning && livesCount && delay - 2 * level > 0 && game.isRunning) {

			// TODO: ovo popraviti, ne radi za continue game
		if (!gameContinuation || isStartOfNewGame)
			initLevel(&pacman, ghosts);

		printInitMap(testMapTemp, pacman);
		updateScoreAndGameMode(testMapTemp, pacman, ghosts, &pacDotCount, &currentScore);
		updateLivesBox(testMapTemp, numberOfLivesTiles, livesCount);
		updateLevelBox(level);
		timer_tick = 0;
		if (isStartOfNewGame || pacDotCount == 0) { // OVO JE ZA NOVI NIVO
			if (isStartOfNewGame) {
				isStartOfNewGame = 0;
			}
			level++;
			printInitMap(map, pacman);
			initTempMap(map, testMapTemp);
			updateLevelBox(level);
			updateScoreBox(currentScore);
			updateLivesBox(testMapTemp, numberOfLivesTiles, livesCount);
			pacDotCount = countPacDots(testMapTemp);
		}

		while (isLevelRunning && pacDotCount && livesCount && game.isRunning && !isPacmanEaten) {
			timer_tick++;

			while (SDL_PollEvent(&event) && isLevelRunning && livesCount) {

				switch (event.type) {
				case SDL_KEYDOWN:
					
					// SRBENDA MOD
					switch (event.key.keysym.sym) {
					case SDLK_SPACE:
						srbendaMod ^= -1;	// MUST BE ALL 1 IN BINARY FORM FOR XOR
						if (srbendaMod)
							PlaySound(TEXT("Music/UzickoKolo"), NULL, SND_ASYNC);
						else
							PlaySound(TEXT("Music/PacmanFever"), NULL, SND_ASYNC);
						break;
					default:
						break;
					}

					if (gameType != DEMO_GAME) {
						enum Direction temp;
						temp = getPacmanDirectionFromUser(event);
						if (temp != DIRECTION_NONE)
							pacman.direction = temp;
					}
					else {
						// TODO: Implement Pacman AI for demo game
					}

					switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						isLevelRunning = SDL_FALSE;
						isPauseMenu = SDL_TRUE;
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

			if (timer_tick % 4 == 0) {
				wallCheckAndMove(testMapTemp, &pacman);
			}

			// azuriranje Score-a, da li je Pacman pojeo nesto
			updateScoreAndGameMode(testMapTemp, pacman, ghosts, &pacDotCount, &currentScore);

			// provera -> pacman i duh na istom polju pre pomeranja duhova
			for (i = 0; i < NUMBER_OF_GHOSTS; i++) {
				if (ghosts[i].gameMode == Normal) {
					isPacmanEaten |= pacmanGhostCheck(pacman, ghosts[i]);
				}
				else if (pacmanGhostCheck(pacman, ghosts[i]) && (ghosts[i].gameMode == Reverse || ghosts[i].gameMode == EndReverse)) {
					ghosts[i].gameMode = GhostEaten;
				}
			}

			// Poziv funkcije za updateovanje pacmana i duhova 			
			updateGhosts(testMapTemp, ghosts, timer_tick);
			updatePacman(testMapTemp, pacman, timer_tick);

			// NOVI DIRECTION-I DUHOVA
			//if (timer_tick % 7 == 0) {
			//	ghosts[0] = BlinkyAI(map, pacman, ghosts, 0);
			//	ghosts[1] = InkyAI(map, pacman, ghosts, 1);
			//	ghosts[2] = PinkyAI(map, pacman, ghosts, 2);
			//	ghosts[3] = ClydeAI(map, pacman, ghosts, 3);
			//	for (i = 0; i < NUMBER_OF_GHOSTS; i++) {
			//		if (ghosts[i].gameMode == Reverse || ghosts[i].gameMode == EndReverse) {
			//			// ghosts[i].direction = (ghosts[i].direction + (NUMBER_OF_DIRECTIONS / 2)) % NUMBER_OF_DIRECTIONS;
			//			changeDirectionForReverseGhost(map, &ghosts[i]);
			//		}
			//	}
			//	for (i = 0; i < NUMBER_OF_GHOSTS; i++) {
			//		wallCheckAndMove(map, &ghosts[i]);
			//	}
			//}

			// NOVI DIRECTION-I DUHOVA
			if (timer_tick % 7 == 0) {
				ghosts[0] = BlinkyAI(map, pacman, ghosts, 0);
				ghosts[1] = InkyAI(map, pacman, ghosts, 1);
				ghosts[2] = PinkyAI(map, pacman, ghosts, 2);
				ghosts[3] = ClydeAI(map, pacman, ghosts, 3);
				for (i = 0; i < NUMBER_OF_GHOSTS; i++) {
					if (ghosts[i].gameMode == Reverse || ghosts[i].gameMode == EndReverse) {
						// ghosts[i].direction = (ghosts[i].direction + (NUMBER_OF_DIRECTIONS / 2))  % NUMBER_OF_DIRECTIONS;
						changeDirectionForReverseGhost(map, &ghosts[i]);
					}
					else if (ghosts[i].gameMode == GhostEaten) {
						ghosts[i] = BlinkyAI(map, home, ghosts, i);
						if (ghosts[i].iPosition == home.iPosition && ghosts[i].jPosition == home.jPosition)
							ghosts[i].gameMode = Normal;
					}
				}
				for (i = 0; i < NUMBER_OF_GHOSTS; i++) {
					wallCheckAndMove(map, &ghosts[i]);
				}
			}

			// provera -> pacman i duh na istom polju kad se pomere duhovi
			for (i = 0; i < NUMBER_OF_GHOSTS; i++) {
				if (ghosts[i].gameMode == Normal) {
					isPacmanEaten |= pacmanGhostCheck(pacman, ghosts[i]);
				}
				else if (pacmanGhostCheck(pacman, ghosts[i]) && (ghosts[i].gameMode == Reverse || ghosts[i].gameMode == EndReverse) ) {
					ghosts[i].gameMode = GhostEaten;
				}
			}
			//provera broja zivota pacman-a
			if (isPacmanEaten) {
				livesCount--;
				// Azurira livesBox sa trenutnim brojem zivota
				updateLivesBox(testMapTemp, numberOfLivesTiles, livesCount);
			}

			SDL_RenderPresent(game.screen.renderer);
			SDL_Delay(delay - 2 * level);
		}
		if (isPauseMenu && !isLevelRunning && game.isRunning && livesCount) {
			SDL_RenderClear(game.screen.renderer);
			selectedOption = ActivatePauseMenu(difficulty);
			SDL_RenderClear(game.screen.renderer);
			switch (selectedOption) {
			case continueWithGame:
				isLevelRunning = SDL_TRUE;
				gameContinuation = 1;
				break;
			case settingsInGame:
				SDL_RenderClear(game.screen.renderer);
				activateSettings(&difficulty);
				SDL_RenderClear(game.screen.renderer);
				isLevelRunning = SDL_TRUE;
				gameContinuation = 1;
				break;
			case mainMenu:
				saveGameForContinue(difficulty, delay, level, livesCount, numberOfLivesTiles, currentScore, isStartOfNewGame, home, pacman, ghosts, testMapTemp, pacDotCount);
				break;
			case finishGame:
				break;
			}
		}

		isPacmanEaten = 0;	// KADA SE POJEDE PACMAN, MORA DA SE RESETUJE
	}
	if ((!isLevelRunning || !livesCount) && game.isRunning) {
		SDL_RenderClear(game.screen.renderer);
		endGameScreen();
		SDL_RenderClear(game.screen.renderer);
	}
	// TODO: videti da li je korisnik hteo da se unese score
	// ako jeste, onda vracamo currentScore
	// ako je hteo da sacuva partiju, vracamo neki flag (verovatno -1)
	// ako je sacuvao partiju, moramo da sacuvamo partiju u binaran fajl
	return currentScore;
}
