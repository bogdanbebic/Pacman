#include "game.h"
#include "testMap.h"
#include "pauseMenuGraphics.h"
#include "saveGame.h"
#include "cheats.h"
#include <Windows.h>

SaveGame saveGame;

/*
 *	Initializes continue game
 *	with saved game parameters.
 *	Sets values for all arguments except difficulty
 */
void initContinueGame(enum DifficultySpeed *difficulty, int *delay, int *level, int *livesCount, Highscore *currentScore, int *isStartOfNewGame, PacStruct *home, int *pacDotCount, int *timer_tick, int *timer_tick_POWER_PELLET, int *isPowerPelletEaten) {
	extern SaveGame saveGame;
	*isPowerPelletEaten = saveGame.isPowerPelletEaten;
	*timer_tick_POWER_PELLET = saveGame.timer_tick_POWER_PELLET;
	*timer_tick = saveGame.timer_tick;
	*difficulty = saveGame.difficulty;
	*delay = saveGame.delay;
	*level = saveGame.level;
	*livesCount = saveGame.livesCount;
	*currentScore = saveGame.currentScore;
	*isStartOfNewGame = saveGame.isStartOfNewGame;
	*home = saveGame.home;
	*pacDotCount = saveGame.pacDotCount;
	return;
}

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

/*
*	Moves pacStruct on map,
*	pacman can go through the wall
*	Return value:
*	1 if pacStruct moved
*	0 otherwise
*/
int wallCheckAndMoveNoWall(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct *pacStruct) {
	switch (pacStruct->direction) {
	case DIRECTION_UP:
		pacStruct->iPosition = (pacStruct->iPosition - 1 + HEIGHT_OF_MAP) % HEIGHT_OF_MAP;
		break;
	case DIRECTION_RIGHT:
		pacStruct->jPosition = (pacStruct->jPosition + 1) % WIDTH_OF_MAP;
		break;
	case DIRECTION_DOWN:
		pacStruct->iPosition = (pacStruct->iPosition + 1) % HEIGHT_OF_MAP;
		break;
	case DIRECTION_LEFT:
		pacStruct->jPosition = (pacStruct->jPosition - 1 + WIDTH_OF_MAP) % WIDTH_OF_MAP;
		break;
	default:
		break;
	}
	if (pacStruct->direction == DIRECTION_NONE)
		return 0;
	else
		return 1;
}

/*
*	Changes direction for ghost
*	in reverse mode
*/
void changeDirectionForReverseGhost(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct *pacStruct) {
	pacStruct->direction = (pacStruct->direction + (NUMBER_OF_DIRECTIONS / 2)) % NUMBER_OF_DIRECTIONS;
	PacStruct temp = *pacStruct;
	if (!wallCheckAndMove(map, &temp)) {
		temp.direction = (pacStruct->direction + 1) % NUMBER_OF_DIRECTIONS;
		if (wallCheckAndMove(map, &temp)) {
			pacStruct->direction = (pacStruct->direction + 1) % NUMBER_OF_DIRECTIONS;
		}
		else {
			pacStruct->direction = (pacStruct->direction - 1 + NUMBER_OF_DIRECTIONS) % NUMBER_OF_DIRECTIONS;
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
void updateScoreAndGameMode(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman, PacStruct ghosts[], int * pacDotCount, Highscore * currentScore, int *timer_tick, int *isPowerPelletEaten, enum DifficultySpeed difficulty) {
	int i;
	int difficultyCoefficient;
	switch (difficulty) {
	case EASY:
		difficultyCoefficient = 1;
		break;
	case MEDIUM:
		difficultyCoefficient = 2;
		break;
	case HARD:
		difficultyCoefficient = 4;
		break;
	default:
		break;
	}
	if (map[pacman.iPosition][pacman.jPosition] == PAC_DOT) {
		currentScore->points += 5 * difficultyCoefficient;
		map[pacman.iPosition][pacman.jPosition] = NO_WALL;
		(*pacDotCount)--;
	}
	else if (map[pacman.iPosition][pacman.jPosition] == POWER_PELLET) {
		map[pacman.iPosition][pacman.jPosition] = NO_WALL;
		currentScore->points += 25 * difficultyCoefficient;
		*timer_tick = 0;
		*isPowerPelletEaten = 1;
		for (i = 0; i < NUMBER_OF_GHOSTS; i++)
			if (ghosts[i].gameMode != GhostEaten) {
				ghosts[i].gameMode = Reverse;
			}
	}
	for (i = 0; i < NUMBER_OF_GHOSTS; i++) {
		if (pacmanGhostCheck(pacman, ghosts[i]) && (ghosts[i].gameMode == Reverse || ghosts[i].gameMode == EndReverse)) {
			currentScore->points += 100 * difficultyCoefficient;
		}
	}
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

/*
*	Initializes a new level
*	with new level pacman and ghost 
*	parameters
*/
void initLevel(PacStruct *pacman, PacStruct *ghosts) {
	initPacmanPosition(pacman);
	initGhosts(ghosts);
	return;
}

/*
*	Initializes a new game
*	with new game parameters.
*	Sets values for all arguments except difficulty
*/
void initNewGame(enum DifficultySpeed difficulty, int *delay, int *level, int *livesCount, Highscore *currentScore, int *isStartOfNewGame, PacStruct *home) {
	*isStartOfNewGame = 1;
	*level = -1;
	*delay = (int)difficulty;
	switch (difficulty) {
	case EASY:
		*livesCount = 5;
		break;
	case MEDIUM:
		*livesCount = 3;
		break;
	case HARD:
		*livesCount = 1;
		break;
	default:
		break;
	}
	
	currentScore->points = 0;

	home->gameMode = Normal;
	home->direction = DIRECTION_NONE;
	home->iPosition = HEIGHT_OF_MAP / 2 - 1;
	home->jPosition = WIDTH_OF_MAP / 2 - 2;

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
void saveGameForContinue(enum DifficultySpeed difficulty, int delay, int level, int livesCount, Highscore currentScore, int isStartOfNewGame, PacStruct home, PacStruct pacman, PacStruct ghosts[], int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], int pacDotCount, int srbendaMod, int timer_tick, int timer_tick_POWER_PELLET, int isPowerPelletEaten) {
	extern SaveGame saveGame;
	int i, j;
	saveGame.isPowerPelletEaten = isPowerPelletEaten;
	saveGame.timer_tick_POWER_PELLET = timer_tick_POWER_PELLET;
	saveGame.timer_tick = timer_tick;
	saveGame.difficulty = difficulty;
	saveGame.delay = delay;
	saveGame.level = level;
	saveGame.livesCount = livesCount;
	saveGame.currentScore = currentScore;
	saveGame.isStartOfNewGame = isStartOfNewGame;
	saveGame.home = home;
	saveGame.pacman = pacman;
	saveGame.pacDotCount = pacDotCount;
	saveGame.srbendaMod = srbendaMod;
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
Highscore playGame(enum GameType gameType, enum DifficultySpeed difficulty, enum YesNo isMusicOn) {
	extern int map[HEIGHT_OF_MAP][WIDTH_OF_MAP];

	int testMapTemp[HEIGHT_OF_MAP][WIDTH_OF_MAP];

	extern SaveGame saveGame;

	SDL_bool isLevelRunning = SDL_TRUE;
	SDL_bool isPauseMenu = SDL_FALSE;
	
	int isGameFinished = 0;

	enum PauseMenuOptions selectedOption;
	PacStruct pacman;
	PacStruct ghosts[4];
	int livesCount;
	int numberOfLivesTiles = MAX_LIVES;
	int level;
	int delay;
	int pacDotCount;
	int isStartOfNewGame;
	int gameContinuation = 0;
	
	PacStruct home;

	extern SaveGame saveGame;

	Highscore currentScore;
	currentScore.name[0] = '\0';

	int srbendaMod = 0;

	extern int speed;

	int timer_tick = 0;
	int timer_tick_POWER_PELLET = 0;
	int isPowerPelletEaten = 0;
	int newLevel;
	int i;
	int isPacmanEaten = 0;
	int nameSave;
	pacDotCount = countPacDots(map); // Power Pellets are not counted as pacDots!!!

	switch (gameType) {
	case DEMO_GAME:
	case NEW_GAME:
		initNewGame(difficulty, &delay, &level, &livesCount, &currentScore, &isStartOfNewGame, &home);
		break;
	case CONTINUE_GAME:
		gameContinuation = 1;
		initContinueGame(&difficulty, &delay, &level, &livesCount, &currentScore, &isStartOfNewGame, &home, &pacDotCount, &timer_tick, &timer_tick_POWER_PELLET, &isPowerPelletEaten);
		srbendaMod = saveGame.srbendaMod;
		if (srbendaMod) {
			PlaySound(NULL, NULL, SND_ASYNC);
			if (isMusicOn)
				PlaySound(TEXT("Music/UzickoKolo"), NULL, SND_LOOP | SND_ASYNC);
		}
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
		if (!gameContinuation || isStartOfNewGame)
			initLevel(&pacman, ghosts);
		else {
			gameContinuation = 0;
		}
		newLevel = 1;
		printInitMap(testMapTemp, pacman, srbendaMod, newLevel);
		updateScoreAndGameMode(testMapTemp, pacman, ghosts, &pacDotCount, &currentScore, &timer_tick_POWER_PELLET, &isPowerPelletEaten, difficulty);
		updateLivesBox(testMapTemp, numberOfLivesTiles, livesCount);
		updateLevelBox(level);

		timer_tick = 0;
		if (isStartOfNewGame || pacDotCount == 0) {
			if (isStartOfNewGame) {
				isStartOfNewGame = 0;
			}
			level++; 
			printInitMap(map, pacman, srbendaMod, newLevel);
			initTempMap(map, testMapTemp);
			updateLevelBox(level);
			updateScoreBox(currentScore);
			updateLivesBox(testMapTemp, numberOfLivesTiles, livesCount);
			pacDotCount = countPacDots(testMapTemp);
		}

		while (isLevelRunning && pacDotCount && livesCount && game.isRunning && !isPacmanEaten) {
			timer_tick++;
			if (isPowerPelletEaten) {
				timer_tick_POWER_PELLET++;
				if (timer_tick_POWER_PELLET > 120 && !infinityReverseCheat) {
					for (i = 0; i < NUMBER_OF_GHOSTS; i++) {
						if (ghosts[i].gameMode == Reverse)
							ghosts[i].gameMode = EndReverse;
					}
				}
				if (timer_tick_POWER_PELLET == 150 && !infinityReverseCheat) {
					for (i = 0; i < NUMBER_OF_GHOSTS; i++) {
						if (ghosts[i].gameMode == EndReverse)
							ghosts[i].gameMode = Normal;
					}
					timer_tick_POWER_PELLET = 0;
					isPowerPelletEaten = 0;
				}
			}
			while (SDL_PollEvent(&event) && isLevelRunning && livesCount) {

				switch (event.type) {
				case SDL_KEYDOWN:

					// SRBENDA MOD
					switch (event.key.keysym.sym) {
						case SDLK_SPACE:
							srbendaMod ^= -1;	// MUST BE ALL 1 IN BINARY FORM FOR XOR
							if (srbendaMod) {
								PlaySound(NULL, NULL, SND_ASYNC);
								if (isMusicOn)
									PlaySound(TEXT("Music/UzickoKolo"), NULL, SND_LOOP | SND_ASYNC);
							}
							else {
								PlaySound(NULL, NULL, SND_ASYNC);
								if (isMusicOn)
									PlaySound(TEXT("Music/PacmanFever"), NULL, SND_LOOP | SND_ASYNC);
							}
							newLevel = 0;
							printInitMap(testMapTemp, pacman, srbendaMod, newLevel);
							break;
							default:
								break;
								
					}

					if (gameType != DEMO_GAME) {
						enum Direction temp;
						temp = getPacmanDirectionFromUser(event);
						if (temp != DIRECTION_NONE) {
							if (drunkCheat) {
								temp = (temp + (NUMBER_OF_DIRECTIONS / 2)) % NUMBER_OF_DIRECTIONS;
							}
							pacman.direction = temp;
						}
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

			if (timer_tick % (MAX_SPEED - speed) == 0) {
				if (gameType == DEMO_GAME) {
					PacStruct pacTry = pacman;
					pacTry = PacmanDemo(testMapTemp, pacman, ghosts, timer_tick);
					if (wallCheckAndMove(testMapTemp, &pacTry))
						pacman = PacmanDemo(testMapTemp, pacman, ghosts, timer_tick);
				}
				if(throughTheWallCheat) 
					wallCheckAndMoveNoWall(testMapTemp, &pacman);
				else 
					wallCheckAndMove(testMapTemp, &pacman);
			}

			updateScoreAndGameMode(testMapTemp, pacman, ghosts, &pacDotCount, &currentScore, &timer_tick_POWER_PELLET, &isPowerPelletEaten, difficulty);

			for (i = 0; i < NUMBER_OF_GHOSTS; i++) {
				if (ghosts[i].gameMode == Normal) {
					if (!immortalityCheat) {
						isPacmanEaten |= pacmanGhostCheck(pacman, ghosts[i]);
					}
				}
				else if (pacmanGhostCheck(pacman, ghosts[i]) && (ghosts[i].gameMode == Reverse || ghosts[i].gameMode == EndReverse)) {
					ghosts[i].gameMode = GhostEaten;
				}
			}
		
			updateGhosts(testMapTemp, ghosts, timer_tick, srbendaMod);
			updatePacman(testMapTemp, pacman, timer_tick, srbendaMod);

			// NEW GHOSTS DIRECTIONS
			if (timer_tick % 6 == 0) {
				ghosts[0] = BlinkyAI(map, pacman, ghosts, 0);
				ghosts[1] = InkyAI(map, pacman, ghosts, 1);
				ghosts[2] = PinkyAI(map, pacman, ghosts, 2);
				ghosts[3] = ClydeAI(map, pacman, ghosts, 3);
				for (i = 0; i < NUMBER_OF_GHOSTS; i++) {
					if (ghosts[i].gameMode == Reverse || ghosts[i].gameMode == EndReverse) {
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

			for (i = 0; i < NUMBER_OF_GHOSTS; i++) {
				if (ghosts[i].gameMode == Normal) {
					if (!immortalityCheat) {
						isPacmanEaten |= pacmanGhostCheck(pacman, ghosts[i]);
					}
				}
				else if (pacmanGhostCheck(pacman, ghosts[i]) && (ghosts[i].gameMode == Reverse || ghosts[i].gameMode == EndReverse) ) {
					ghosts[i].gameMode = GhostEaten;
				}
			}

			if (isPacmanEaten) {
				livesCount--;
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
				if (extraLifeCheat) {
					livesCount += livesCount < MAX_LIVES ? 1 : 0;
					extraLifeCheat = 0;
				}
				break;
			case mainMenu:
				// OVO PROMENITI AKO NE ZELIMO DA MOZE IGRAC DA NASTAVI DEMO
				saveGameForContinue(difficulty, delay, level, livesCount, currentScore, isStartOfNewGame, home, pacman, ghosts, testMapTemp, pacDotCount, srbendaMod, timer_tick, timer_tick_POWER_PELLET, isPowerPelletEaten);
				break;
			case finishGame:
				isGameFinished = 1;
				saveGame.level = -1;
				break;
			}
		}

		isPacmanEaten = 0;
	}
	if ((isGameFinished || !livesCount) && game.isRunning) {
		extern Highscore highscores[MAX_HIGHSCORES];
		SDL_RenderClear(game.screen.renderer);
		endGameScreen();
		if (game.isRunning && gameType != DEMO_GAME && currentScore.points > highscores[MAX_HIGHSCORES - 1].points) {
			nameSave = 1;
			SDL_RenderClear(game.screen.renderer);
			finalScoreScreen(currentScore.points, currentScore.name, &nameSave);
			SDL_RenderClear(game.screen.renderer);
		}
	}
	
	return currentScore;
}
