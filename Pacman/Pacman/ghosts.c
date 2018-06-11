#include "ghosts.h"

/*!	\file ghosts.c
*	\brief Contains function definitions for ghosts logic and AI and everything needed for them
*/

extern int countPacDots(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP]);

/*!
*	\brief Finds next position using BFS
*	\param Map map on which the game is played
*	\param ghostX x coordinate of ghost
*	\param ghostY y coordinate of ghost
*	\param pacmanX x coordinate of pacman
*	\param pacmanY y coordinate of pacman
*	\return BFS_solution (direction and number of steps from ghost to pacman)
*/
BFS_solution BFS_next(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], int ghostX, int ghostY, int pacmanX, int pacmanY) {
	short visited[HEIGHT_OF_MAP][WIDTH_OF_MAP];
	int x, y;
	for (x = 0; x < HEIGHT_OF_MAP; x++)
		for (y = 0; y < WIDTH_OF_MAP; y++)
			visited[x][y] = 0;
	int queueX[HEIGHT_OF_MAP * WIDTH_OF_MAP];
	int queueY[HEIGHT_OF_MAP * WIDTH_OF_MAP];
	int cnt = 0;
	BFS_solution sol[4] = { 0,0 };
	BFS_solution solution = { 0,0 };
	int i = 0;
	int queueCount = 1;
	queueX[0] = pacmanX;
	queueY[0] = pacmanY;
	visited[queueY[i]][queueX[i]] = 1;

	while (i < queueCount) {
		cnt = 0;
		if (queueY[i] == ghostY && queueX[i] == ghostX && Map[queueY[i]][queueX[i]] != WALL) {
			sol[cnt].direction = DIRECTION_UP;
			sol[cnt].count = visited[queueY[i]][queueX[i]] + 1;
			return sol[cnt];
		}
		if (queueY[i] + 1 == ghostY && queueX[i] == ghostX && Map[queueY[i]][queueX[i]] != WALL) {
			sol[cnt].direction = DIRECTION_UP;
			sol[cnt].count = visited[queueY[i]][queueX[i]]+1;
			cnt++;
		}
		if (queueY[i] < HEIGHT_OF_MAP - 1 && Map[queueY[i] + 1][queueX[i]] != WALL && visited[queueY[i] + 1][queueX[i]] <= 0) {
			queueY[queueCount] = queueY[i] + 1;
			queueX[queueCount++] = queueX[i];
			visited[queueY[i] + 1][queueX[i]] = visited[queueY[i]][queueX[i]] + 1;
		}
		if (queueY[i] - 1 == ghostY && queueX[i] == ghostX && Map[queueY[i]][queueX[i]] != WALL) {
			sol[cnt].direction = DIRECTION_DOWN;
			sol[cnt].count = visited[queueY[i]][queueX[i]]+1;
			cnt++;
		}
		if (queueY[i] > 0 && Map[queueY[i] - 1][queueX[i]] != WALL && visited[queueY[i] - 1][queueX[i]] <= 0) {

			queueY[queueCount] = queueY[i] - 1;
			queueX[queueCount++] = queueX[i];

			visited[queueY[i] - 1][queueX[i]] = visited[queueY[i]][queueX[i]] + 1;
		}
		if (queueY[i] == ghostY && (queueX[i] + 1) % WIDTH_OF_MAP == ghostX && Map[queueY[i]][queueX[i]] != WALL) {
			sol[cnt].direction = DIRECTION_LEFT;
			sol[cnt].count = visited[queueY[i]][queueX[i]]+1;
			cnt++;
		}
		if (queueX[i] < WIDTH_OF_MAP - 1 && Map[queueY[i]][queueX[i] + 1] != WALL && visited[queueY[i]][queueX[i] + 1] <= 0) {

			queueY[queueCount] = queueY[i];
			queueX[queueCount++] = queueX[i] + 1;

			visited[queueY[i]][queueX[i] + 1] = visited[queueY[i]][queueX[i]] + 1;
		}
		if (queueX[i] == WIDTH_OF_MAP - 1 && Map[queueY[i]][0] != WALL && visited[queueY[i]][0] <= 0) {

			queueY[queueCount] = queueY[i];
			queueX[queueCount++] = 0;

			visited[queueY[i]][0] = visited[queueY[i]][queueX[i]] + 1;
		}
		if (queueY[i] == ghostY && (queueX[i] - 1 + WIDTH_OF_MAP) % WIDTH_OF_MAP == ghostX && Map[queueY[i]][queueX[i]] != WALL) {
			sol[cnt].direction = DIRECTION_RIGHT;
			sol[cnt].count = visited[queueY[i]][queueX[i]]+1;
			cnt++;
		}
		if (queueX[i] > 0 && Map[queueY[i]][queueX[i] - 1] != WALL && visited[queueY[i]][queueX[i] - 1] <= 0) {

			queueY[queueCount] = queueY[i];
			queueX[queueCount++] = queueX[i] - 1;

			visited[queueY[i]][queueX[i] - 1] = visited[queueY[i]][queueX[i]] + 1;
		}
		if (queueX[i] == 0 && Map[queueY[i]][WIDTH_OF_MAP - 1] != WALL && visited[queueY[i]][WIDTH_OF_MAP - 1] <= 0) {

			queueY[queueCount] = queueY[i];
			queueX[queueCount++] = WIDTH_OF_MAP - 1;

			visited[queueY[i]][WIDTH_OF_MAP - 1] = visited[queueY[i]][queueX[i]] + 1;
		}
		i++;
		if (cnt > 0) {
			cnt = rand() % cnt;
			solution.direction = sol[cnt].direction;
			solution.count = sol[cnt].count;
			return solution;
		}
	}
	solution.direction = DIRECTION_NONE;
	solution.count = 0;
	return solution;
}

/*!
*	\brief Finds next AI move for Blinky, Blinky�s target tile is always Pac-Man�s current tile
*	\param Map map on which the game is played
*	\param pacman PacStruct containing info about pacman
*	\param ghosts PacStruct array containing info about ghosts
*	\param currentGhostIndex index in ghosts array which defines current ghost
*	\return PacStruct containing next position of Blinky
*/
PacStruct BlinkyAI(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman, PacStruct ghosts[NUMBER_OF_GHOSTS], int currentGhostIndex) {
	PacStruct sol = ghosts[currentGhostIndex];
	int ghostY = ghosts[currentGhostIndex].iPosition;
	int ghostX = ghosts[currentGhostIndex].jPosition;
	int pacmanY = pacman.iPosition;
	int pacmanX = pacman.jPosition;

	sol.direction = BFS_next(Map, ghostX, ghostY, pacmanX, pacmanY).direction;

	return sol;
}

/*!
*	\brief Finds next AI move for Pinky. Pinky�s target tile is always a tile that is next to Pac-Man�s current tile
*	\param Map map on which the game is played
*	\param ghostX x coordinate of ghost
*	\param ghostY y coordinate of ghost
*	\param pacmanX x coordinate of pacman
*	\param pacmanY y coordinate of pacma
*	\return PacStruct containing next position of Pinky
*/
BFS_solution PinkyAI_logic(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], int ghostX, int ghostY, int pacmanX, int pacmanY) {
	BFS_solution solution;

	solution.count = HEIGHT_OF_MAP * WIDTH_OF_MAP;
	solution.direction = DIRECTION_NONE;
	BFS_solution currentSol;
	if (pacmanX < HEIGHT_OF_MAP - 1 && Map[pacmanX + 1][pacmanY] != WALL) {
		currentSol = BFS_next(Map, ghostX, ghostY, pacmanX + 1, pacmanY);
		if (currentSol.count < solution.count) {
			solution.count = currentSol.count;
			solution.direction = currentSol.direction;
		}
	}
	if (pacmanX > 0 && Map[pacmanX - 1][pacmanY] != WALL) {
		currentSol = BFS_next(Map, ghostX, ghostY, pacmanX - 1, pacmanY);
		if (currentSol.count < solution.count) {
			solution.count = currentSol.count;
			solution.direction = currentSol.direction;
		}
	}
	if (pacmanY < WIDTH_OF_MAP - 1 && Map[pacmanX][pacmanY + 1] != WALL) {
		currentSol = BFS_next(Map, ghostX, ghostY, pacmanX, pacmanY + 1);
		if (currentSol.count < solution.count) {
			solution.count = currentSol.count;
			solution.direction = currentSol.direction;
		}
	}
	if (pacmanY > 0 && Map[pacmanX][pacmanY - 1] != WALL) {
		currentSol = BFS_next(Map, ghostX, ghostY, pacmanX, pacmanY - 1);
		if (currentSol.count < solution.count) {
			solution.count = currentSol.count;
			solution.direction = currentSol.direction;
		}
	}
	if (pacmanY == WIDTH_OF_MAP - 1 && Map[pacmanX][0] != WALL) {
		currentSol = BFS_next(Map, ghostX, ghostY, pacmanX, 0);
		if (currentSol.count < solution.count) {
			solution.count = currentSol.count;
			solution.direction = currentSol.direction;
		}
	}
	if (pacmanY == 0 && Map[pacmanX][WIDTH_OF_MAP - 1] != WALL) {
		currentSol = BFS_next(Map, ghostX, ghostY, pacmanX, WIDTH_OF_MAP - 1);
		if (currentSol.count < solution.count) {
			solution.count = currentSol.count;
			solution.direction = currentSol.direction;
		}
	}


	return solution;
}

/*!
*	\brief Finds next AI move for Pinky. This function uses PinkyAI_logic function
*	\param Map map on which the game is played
*	\param pacman PacStruct containing info about pacman
*	\param ghosts PacStruct array containing info about ghosts
*	\param currentGhostIndex index in ghosts array which defines current ghost
*	\return PacStruct containing next position of Pinky
*/
PacStruct PinkyAI(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman, PacStruct ghosts[NUMBER_OF_GHOSTS], int currentGhostIndex) {
	PacStruct sol = ghosts[currentGhostIndex];
	int ghostY = ghosts[currentGhostIndex].iPosition;
	int ghostX = ghosts[currentGhostIndex].jPosition;
	int pacmanY = pacman.iPosition;
	int pacmanX = pacman.jPosition;

	sol.direction = PinkyAI_logic(Map, ghostX, ghostY, pacmanX, pacmanY).direction;

	return sol;
}

/*!
*	\brief Finds next AI move for Inky. Inky�s target tile is always a tile that is two tiles from the Pac-Man�s current tile
*	\param Map map on which the game is played
*	\param pacman PacStruct containing info about pacman
*	\param ghosts PacStruct array containing info about ghosts
*	\param currentGhostIndex index in ghosts array which defines current ghost
*	\return	PacStruct containing next position of Inky
*/
PacStruct InkyAI(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman, PacStruct ghosts[NUMBER_OF_GHOSTS], int currentGhostIndex) {
	PacStruct sol = ghosts[currentGhostIndex];
	int ghostY = ghosts[currentGhostIndex].iPosition;
	int ghostX = ghosts[currentGhostIndex].jPosition;
	int pacmanY = pacman.iPosition;
	int pacmanX = pacman.jPosition;

	BFS_solution solution;
	solution.count = HEIGHT_OF_MAP * WIDTH_OF_MAP;
	solution.direction = DIRECTION_NONE;
	BFS_solution currentSol;
	if (pacmanX < HEIGHT_OF_MAP - 1 && Map[pacmanX + 1][pacmanY] != WALL) {
		currentSol = PinkyAI_logic(Map, ghostX, ghostY, pacmanX + 1, pacmanY);
		if (currentSol.count < solution.count) {
			solution.count = currentSol.count;
			solution.direction = currentSol.direction;
		}
	}
	if (pacmanX > 0 && Map[pacmanX - 1][pacmanY] != WALL) {
		currentSol = PinkyAI_logic(Map, ghostX, ghostY, pacmanX - 1, pacmanY);
		if (currentSol.count < solution.count) {
			solution.count = currentSol.count;
			solution.direction = currentSol.direction;
		}
	}
	if (pacmanY < WIDTH_OF_MAP - 1 && Map[pacmanX][pacmanY + 1] != WALL) {
		currentSol = PinkyAI_logic(Map, ghostX, ghostY, pacmanX, pacmanY + 1);
		if (currentSol.count < solution.count) {
			solution.count = currentSol.count;
			solution.direction = currentSol.direction;
		}
	}
	if (pacmanY > 0 && Map[pacmanX][pacmanY - 1] != WALL) {
		currentSol = PinkyAI_logic(Map, ghostX, ghostY, pacmanX, pacmanY - 1);
		if (currentSol.count < solution.count) {
			solution.count = currentSol.count;
			solution.direction = currentSol.direction;
		}
	}
	if (pacmanY == WIDTH_OF_MAP - 1 && Map[pacmanX][0] != WALL) {
		currentSol = PinkyAI_logic(Map, ghostX, ghostY, pacmanX, 0);
		if (currentSol.count < solution.count) {
			solution.count = currentSol.count;
			solution.direction = currentSol.direction;
		}
	}
	if (pacmanY == 0 && Map[pacmanX][WIDTH_OF_MAP - 1] != WALL) {
		currentSol = PinkyAI_logic(Map, ghostX, ghostY, pacmanX, WIDTH_OF_MAP - 1);
		if (currentSol.count < solution.count) {
			solution.count = currentSol.count;
			solution.direction = currentSol.direction;
		}
	}


	sol.direction = solution.direction;
	
	return sol;
}

/*!
*	\brief Finds next AI move for Clyde. Clyde�s target tile is Pac-Man�s current tile if Clyde is ten tiles from the Pac-Man
*	Otherwise, target tile is bottom left tile on the map.
*	\param Map map on which the game is played
*	\param pacman PacStruct containing info about pacman
*	\param ghosts PacStruct array containing info about ghosts
*	\param currentGhostIndex index in ghosts array which defines current ghost
*	\return	PacStruct containing next position of Clyde
*/
PacStruct ClydeAI(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman, PacStruct ghosts[NUMBER_OF_GHOSTS], int currentGhostIndex) {
	PacStruct sol = ghosts[currentGhostIndex];
	int ghostY = ghosts[currentGhostIndex].iPosition;
	int ghostX = ghosts[currentGhostIndex].jPosition;
	int pacmanY = pacman.iPosition;
	int pacmanX = pacman.jPosition;

	BFS_solution bfsSolution = BFS_next(Map, ghostX, ghostY, pacmanX, pacmanY);
	if (bfsSolution.count > 10)  //po pravilu je 8, ali mi se cini da je to premalo PROVERITI
		bfsSolution = BFS_next(Map, ghostX, ghostY, 1, HEIGHT_OF_MAP - 2);

	sol.direction = bfsSolution.direction;
		
	return sol;
}

/*!
*	\brief Function finds the number of PAC_DOT/POWER_PELLET that surround current tile
*	\param Map map on which the game is played
*	\param pacmanX x coordinate of pacman
*	\param pacmanY y coordinate of pacma
*	\return	Number of neighbourhood tiles that contain PAC_DOT or POWER_PELLET
*/
int isDot(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], int pacmanX, int pacmanY) {
	int cnt = 0;
	if (pacmanY < HEIGHT_OF_MAP - 1 && (Map[pacmanY + 1][pacmanX] == PAC_DOT || Map[pacmanY + 1][pacmanX] == POWER_PELLET)) {
		cnt++;
	}
	if (pacmanY > 0 && (Map[pacmanY - 1][pacmanX] == PAC_DOT || Map[pacmanY - 1][pacmanX] == POWER_PELLET)) {
		cnt++;
	}
	if (pacmanX < WIDTH_OF_MAP - 1 && (Map[pacmanY][pacmanX + 1] == PAC_DOT || Map[pacmanY][pacmanX + 1] == POWER_PELLET)) {
		cnt++;
	}
	if (pacmanX > 0 && (Map[pacmanY][pacmanX - 1] == PAC_DOT || Map[pacmanY][pacmanX - 1] == POWER_PELLET)) {
		cnt++;
	}
	return cnt;
}

/*!
*	\brief Function finds the maximum of four numbers
*	\param a one of the numbers of which to find max
*	\param b one of the numbers of which to find max
*	\param c one of the numbers of which to find max
*	\param d one of the numbers of which to find max
*	\return	Maximum of numbers
*/
int maximum(int a, int b, int c, int d) {
	int sol = a;
	if (b > sol)
		sol = b;
	if (c > sol)
		sol = c;
	if (d > sol)
		sol = d;
	return sol;
}

/*!
*	\brief Function finds the minimum of four numbers
*	\param a one of the numbers of which to find min
*	\param b one of the numbers of which to find min
*	\param c one of the numbers of which to find min
*	\param d one of the numbers of which to find min
*	\return	Minimum of numbers
*/
int minimum(int a, int b, int c, int d) {
	int sol = a;
	if (b < sol)
		sol = b;
	if (c < sol)
		sol = c;
	if (d < sol)
		sol = d;
	return sol;
}

/*!
*	\brief Finds the nearest PAC_DOT/POWER_PELLET using BFS
*	\param Map map on which the game is played
*	\param pacmanX x coordinate of pacman
*	\param pacmanY y coordinate of pacman
*	\return	Number of tiles between Pac-Man and the nearest PAC_DOT/POWER_PELLET
*/
int BFS_nextDot(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], int pacmanX, int pacmanY) {
	short visited[HEIGHT_OF_MAP][WIDTH_OF_MAP];
	for (int x = 0; x < HEIGHT_OF_MAP; x++)
		for (int y = 0; y < WIDTH_OF_MAP; y++)
			visited[x][y] = 0;
	int i = 0;
	int queueX[HEIGHT_OF_MAP * WIDTH_OF_MAP];
	int queueY[HEIGHT_OF_MAP * WIDTH_OF_MAP];
	int queueCount = 1;
	queueX[0] = pacmanX;
	queueY[0] = pacmanY;
	visited[queueY[i]][queueX[i]] = 1;
	if (Map[pacmanY][pacmanX] == WALL)
		return 1200;
	while (i < queueCount) {
		if (Map[queueY[i]][queueX[i]]==PAC_DOT || Map[queueY[i]][queueX[i]] == POWER_PELLET ) {
			return visited[queueY[i]][queueX[i]];
		}
		if (queueY[i] < HEIGHT_OF_MAP - 1 && Map[queueY[i] + 1][queueX[i]] != WALL && visited[queueY[i] + 1][queueX[i]] <= 0) {
			queueY[queueCount] = queueY[i] + 1;
			queueX[queueCount++] = queueX[i];
			visited[queueY[i] + 1][queueX[i]] = visited[queueY[i]][queueX[i]] + 1;
		}
		if (queueY[i] > 0 && Map[queueY[i] - 1][queueX[i]] != WALL && visited[queueY[i] - 1][queueX[i]] <= 0) {

			queueY[queueCount] = queueY[i] - 1;
			queueX[queueCount++] = queueX[i];

			visited[queueY[i] - 1][queueX[i]] = visited[queueY[i]][queueX[i]] + 1;
		}
		if (queueX[i] < WIDTH_OF_MAP - 1 && Map[queueY[i]][queueX[i] + 1] != WALL && visited[queueY[i]][queueX[i] + 1] <= 0) {

			queueY[queueCount] = queueY[i];
			queueX[queueCount++] = queueX[i] + 1;

			visited[queueY[i]][queueX[i] + 1] = visited[queueY[i]][queueX[i]] + 1;
		}
		if (queueX[i] == WIDTH_OF_MAP - 1 && Map[queueY[i]][0] != WALL && visited[queueY[i]][0] <= 0) {

			queueY[queueCount] = queueY[i];
			queueX[queueCount++] = 0;

			visited[queueY[i]][0] = visited[queueY[i]][queueX[i]] + 1;
		}
		if (queueX[i] > 0 && Map[queueY[i]][queueX[i] - 1] != WALL && visited[queueY[i]][queueX[i] - 1] <= 0) {

			queueY[queueCount] = queueY[i];
			queueX[queueCount++] = queueX[i] - 1;

			visited[queueY[i]][queueX[i] - 1] = visited[queueY[i]][queueX[i]] + 1;
		}
		if (queueX[i] == 0 && Map[queueY[i]][WIDTH_OF_MAP - 1] != WALL && visited[queueY[i]][WIDTH_OF_MAP - 1] <= 0) {

			queueY[queueCount] = queueY[i];
			queueX[queueCount++] = WIDTH_OF_MAP - 1;

			visited[queueY[i]][WIDTH_OF_MAP - 1] = visited[queueY[i]][queueX[i]] + 1;
		}
		i++;
	}
	
	return 0;
}

/*!
*	\brief Finds next AI move for Pac-Man. Pac-Man�s target tile is a tile that contains PAC_DOT or POWER_PELLET and that is opposite of ghosts.
*	\param Map map on which the game is played
*	\param pacman PacStruct containing info about pacman
*	\param ghosts PacStruct array containing info about ghosts
*	\return	PacStruct containing next position of Pac-Man
*/
PacStruct PacmanDemo(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman, PacStruct ghosts[NUMBER_OF_GHOSTS]) {
	//Map[HEIGHT_OF_MAP / 2 - 3][WIDTH_OF_MAP / 2 - 1] = WALL;
	//Map[HEIGHT_OF_MAP / 2 - 3][WIDTH_OF_MAP / 2] = WALL;
	PacStruct sol[4];
	for (int i = 0; i < 4; i++)
		sol[i] = pacman;
	int pacmanY = pacman.iPosition;
	int pacmanX = pacman.jPosition;
	int ghostY;
	int ghostX;
	int left = 0, right = 0, up = 0, down = 0;
	int min = 1000;
	int count = 0;
	for (int i = 0; i < NUMBER_OF_GHOSTS; i++) {
		ghostY = ghosts[i].iPosition;
		ghostX = ghosts[i].jPosition;
		count = BFS_next(Map, ghostX, ghostY,(pacmanX - 1 + WIDTH_OF_MAP) % WIDTH_OF_MAP, pacmanY).count;
		if (count == 0)
			count = 1000;
		if (ghosts[i].gameMode == Reverse)
			count += 1200;
		if (count < min)
			min = count;
	}
	if (Map[pacmanY][(pacmanX - 1 + WIDTH_OF_MAP) % WIDTH_OF_MAP] == WALL)
		min = -1;
	left = min - 1;
	min = 1000;
	count = 0;
	for (int i = 0; i < NUMBER_OF_GHOSTS; i++) {
		ghostY = ghosts[i].iPosition;
		ghostX = ghosts[i].jPosition;
		count = BFS_next(Map, ghostX, ghostY, (pacmanX + 1) % WIDTH_OF_MAP, pacmanY).count;
		if (count == 0)
			count = 1000;
		if (ghosts[i].gameMode == Reverse)
			count += 1200;
		if (count < min)
			min = count;
	}
	if (Map[pacmanY][(pacmanX + 1) % WIDTH_OF_MAP] == WALL)
		min = -1;
	right = min - 1;
	min = 1000;
	count = 0;
	for (int i = 0; i < NUMBER_OF_GHOSTS; i++) {
		ghostY = ghosts[i].iPosition;
		ghostX = ghosts[i].jPosition;
		count = BFS_next(Map, ghostX, ghostY, pacmanX, (pacmanY - 1 + HEIGHT_OF_MAP) % HEIGHT_OF_MAP).count;
		if (count == 0)
			count = 1000;
		if (ghosts[i].gameMode == Reverse)
			count += 1200;
		if (count < min)
			min = count;
	}

	if (Map[(pacmanY - 1 + HEIGHT_OF_MAP) % HEIGHT_OF_MAP][pacmanX] == WALL)
		min = -1;
	up = min - 1;
	min = 1000;
	count = 0;
	for (int i = 0; i < NUMBER_OF_GHOSTS; i++) {
		ghostY = ghosts[i].iPosition;
		ghostX = ghosts[i].jPosition;
		count = BFS_next(Map, ghostX, ghostY, pacmanX, (pacmanY + 1) % HEIGHT_OF_MAP).count;
		if (count == 0)
			count = 1000;
		if (ghosts[i].gameMode == Reverse)
			count += 1200;
		if (count < min)
			min = count;
	}

	if (Map[(pacmanY + 1) % HEIGHT_OF_MAP][pacmanX] == WALL)
		min = -1;
	down = min - 1;

	int dotUp = BFS_nextDot(Map, pacmanX, pacmanY - 1);
	int dotLeft = BFS_nextDot(Map, (pacmanX - 1 + WIDTH_OF_MAP) % WIDTH_OF_MAP, pacmanY);
	int dotRight = BFS_nextDot(Map, (pacmanX + 1) % WIDTH_OF_MAP, pacmanY);
	int dotDown = BFS_nextDot(Map, pacmanX, pacmanY + 1);
	int minDot = minimum(dotDown, dotLeft, dotRight, dotUp);
	int max = maximum(up, down, left, right);
	min = minimum(up, down, left, right);
	count = 0;

	if (minDot == dotUp && dotUp < up && sol[count].direction != DIRECTION_DOWN) {
		sol[count].direction = DIRECTION_UP;
		count++;
	}
	if (minDot == dotLeft && dotLeft < left && sol[count].direction != DIRECTION_RIGHT) {
		sol[count].direction = DIRECTION_LEFT;
		count++;
	}
	if (minDot == dotDown && dotDown < down && sol[count].direction != DIRECTION_UP) {
		sol[count].direction = DIRECTION_DOWN;
		count++;
	}
	if (minDot == dotRight && dotRight < right && sol[count].direction != DIRECTION_LEFT) {
		sol[count].direction = DIRECTION_RIGHT;
		count++;
	}
	if (count > 0)
	{
		count = rand() % count;
		return sol[count];
	}

	if (minDot == dotUp && dotUp < up) {
		sol[count].direction = DIRECTION_UP;
		count++;
	}
	if (minDot == dotLeft && dotLeft < left) {
		sol[count].direction = DIRECTION_LEFT;
		count++;
	}
	if (minDot == dotDown && dotDown < down) {
		sol[count].direction = DIRECTION_DOWN;
		count++;
	}
	if (minDot == dotRight && dotRight < right) {
		sol[count].direction = DIRECTION_RIGHT;
		count++;
	}
	if (count > 0)
	{
		count = rand() % count;
		return sol[count];
	}

	if (max == up && sol[count].direction != DIRECTION_DOWN && max <10) {
		sol[count].direction = DIRECTION_UP;
		count++;
	}
	if (max == left && sol[count].direction != DIRECTION_RIGHT && max <10) {
		sol[count].direction = DIRECTION_LEFT;
		count++;
	}
	if (max == down && sol[count].direction != DIRECTION_UP && max <10) {
		sol[count].direction = DIRECTION_DOWN;
		count++;
	}
	if (max == right && sol[count].direction != DIRECTION_LEFT && max <10) {
		sol[count].direction = DIRECTION_RIGHT;
		count++;
	}
	if (count > 0)
	{
		count = rand() % count;
		return sol[count];
	}
	count = 0;


	if (Map[pacmanY - 1][pacmanX] != WALL && sol[count].direction != DIRECTION_DOWN) {
		sol[count].direction = DIRECTION_UP;
		count++;
	}
	if (Map[pacmanY][pacmanX - 1] != WALL && sol[count].direction != DIRECTION_RIGHT) {
		sol[count].direction = DIRECTION_LEFT;
		count++;
	}
	if (Map[pacmanY + 1][pacmanX] != WALL && sol[count].direction != DIRECTION_UP) {
		sol[count].direction = DIRECTION_DOWN;
		count++;
	}
	if (Map[pacmanY][pacmanX + 1] != WALL && sol[count].direction != DIRECTION_LEFT) {
		sol[count].direction = DIRECTION_RIGHT;
		count++;
	}
	if (count > 0)
	{
		count = rand() % count;
		return sol[count];
	}
	count = 0;

	if (Map[pacmanY - 1][pacmanX] != WALL) {
		sol[count].direction = DIRECTION_UP;
		count++;
	}
	if (Map[pacmanY][pacmanX - 1] != WALL) {
		sol[count].direction = DIRECTION_LEFT;
		count++;
	}
	if (Map[pacmanY + 1][pacmanX] != WALL) {
		sol[count].direction = DIRECTION_DOWN;
		count++;
	}
	if (Map[pacmanY][pacmanX + 1] != WALL) {
		sol[count].direction = DIRECTION_RIGHT;
		count++;
	}

	if (count > 0)
	{
		count = rand() % count;
		return sol[count];
	}

	count = 0;
	if (dotUp < up && sol[count].direction != DIRECTION_DOWN) {
		sol[count].direction = DIRECTION_UP;
		count++;
	}
	if (dotLeft < left && sol[count].direction != DIRECTION_RIGHT) {
		sol[count].direction = DIRECTION_LEFT;
		count++;
	}
	if (dotDown < down && sol[count].direction != DIRECTION_UP) {
		sol[count].direction = DIRECTION_DOWN;
		count++;
	}
	if (dotRight < right && sol[count].direction != DIRECTION_LEFT) {
		sol[count].direction = DIRECTION_RIGHT;
		count++;
	}
	if (count > 0)
	{
		count = rand() % count;
		return sol[count];
	}
	count = 0;

	if (dotUp < up) {
		sol[count].direction = DIRECTION_UP;
		count++;
	}
	if (dotLeft < left) {
		sol[count].direction = DIRECTION_LEFT;
		count++;
	}
	if (dotDown < down) {
		sol[count].direction = DIRECTION_DOWN;
		count++;
	}
	if (dotRight < right) {
		sol[count].direction = DIRECTION_RIGHT;
		count++;
	}
	if (count > 0)
	{
		count = rand() % count;
		return sol[count];
	}
	count = 0;

	if (dotUp > 10 && Map[pacmanY - 1][pacmanX] != WALL) {
		sol[count].direction = DIRECTION_UP;
		count++;
	}
	if (dotLeft > 10 && Map[pacmanY][pacmanX - 1] != WALL) {
		sol[count].direction = DIRECTION_LEFT;
		count++;
	}
	if (dotDown > 10 && Map[pacmanY+1][pacmanX] != WALL) {
		sol[count].direction = DIRECTION_DOWN;
		count++;
	}
	if (dotRight > 10 && Map[pacmanY][pacmanX + 1] != WALL) {
		sol[count].direction = DIRECTION_RIGHT;
		count++;
	}
	if (count > 0)
	{
		count = rand() % count;
		return sol[count];
	}
	count = 0;


	count = rand() % count;
	return sol[count];

}
