#include "ghosts.h"

extern int countPacDots(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP]);

typedef struct {
	int direction;
	int count;
} BFS_solution;

/*
*	Finds next position using BFS
*	Return value:
*	BFS_solution (direction and number of steps from ghost to pacman)
*/
BFS_solution BFS_next(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], int ghostX, int ghostY, int pacmanX, int pacmanY) {
	short visited[HEIGHT_OF_MAP][WIDTH_OF_MAP];
	int x, y;
	for (x = 0; x < HEIGHT_OF_MAP; x++)
		for (y = 0; y < WIDTH_OF_MAP; y++)
			visited[x][y] = 0;
	int queueX[HEIGHT_OF_MAP * WIDTH_OF_MAP];
	int queueY[HEIGHT_OF_MAP * WIDTH_OF_MAP];

	BFS_solution sol = { 0 , 0 };
	int i = 0;
	int queueCount = 1;
	queueX[0] = pacmanX;
	queueY[0] = pacmanY;
	visited[queueY[i]][queueX[i]] = 1;

	while (i < queueCount) {
		if (queueY[i] + 1 == ghostY && queueX[i] == ghostX && Map[queueY[i]][queueX[i]] != WALL) {
			sol.direction = DIRECTION_UP;
			sol.count = visited[queueY[i]][queueX[i]];
			return sol;
		}
		if (queueY[i] < HEIGHT_OF_MAP - 1 && Map[queueY[i] + 1][queueX[i]] != WALL && visited[queueY[i] + 1][queueX[i]] <= 0) {
			queueY[queueCount] = queueY[i] + 1;
			queueX[queueCount++] = queueX[i];
			visited[queueY[i] + 1][queueX[i]] = visited[queueY[i]][queueX[i]] + 1;
		}
		if (queueY[i] - 1 == ghostY && queueX[i] == ghostX && Map[queueY[i]][queueX[i]] != WALL) {
			sol.direction = DIRECTION_DOWN;
			sol.count = visited[queueY[i]][queueX[i]];
			return sol;
		}
		if (queueY[i] > 0 && Map[queueY[i] - 1][queueX[i]] != WALL && visited[queueY[i] - 1][queueX[i]] <= 0) {
			
			queueY[queueCount] = queueY[i] - 1;
			queueX[queueCount++] = queueX[i];

			visited[queueY[i] - 1][queueX[i]] = visited[queueY[i]][queueX[i]] + 1;
		}
		if (queueY[i] == ghostY && (queueX[i] + 1)% WIDTH_OF_MAP == ghostX && Map[queueY[i]][queueX[i]] != WALL) {
			sol.direction = DIRECTION_LEFT ;
			sol.count = visited[queueY[i]][queueX[i]];
			return sol;
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
		if (queueY[i] == ghostY && (queueX[i] - 1+WIDTH_OF_MAP)%WIDTH_OF_MAP == ghostX && Map[queueY[i]][queueX[i]] != WALL) {
			sol.direction = DIRECTION_RIGHT   ;
			sol.count = visited[queueY[i]][queueX[i]];
			return sol;
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
	sol.direction = DIRECTION_NONE;
	sol.count = 0;
	return sol;
}

/*
*	Finds next AI move for Blinky
*	Blinky’s target tile is always Pac-Man’s current tile.
*	Return value:
*	PacStruct containing next position of Blinky
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

/*
*	Finds next AI move for Pinky
*	Pinky’s target tile is always a tile that is next to Pac-Man’s current tile.
*	Return value:
*	PacStruct containing next position of Pinky
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

/*
*	Finds next AI move for Pinky
*	This function uses PinkyAI_logic function.
*	Return value:
*	PacStruct containing next position of Pinky
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

/*
*	Finds next AI move for Inky
*	Inky’s target tile is always a tile that is two tiles from the Pac-Man’s current tile.
*	Return value:
*	PacStruct containing next position of Inky
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

/*
*	Finds next AI move for Clyde
*	Clyde’s target tile is Pac-Man’s current tile if Clyde is ten tiles from the Pac-Man.
*	Otherwise, target tile is bottom left tile on the map.
*	Return value:
*	PacStruct containing next position of Clyde
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

/*
*	Function finds the number of PAC_DOT/POWER_PELLET that surround current tile
*	Return value:
*	Number of neighbourhood tiles that contain PAC_DOT or POWER_PELLET
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

/*
*	Finds next AI move for Pac-Man
*	Pac-Man’s target tile is a tile that contains PAC_DOT or POWER_PELLET and that is opposite of ghosts.
*	Return value:
*	PacStruct containing next position of Pac-Man
*/
PacStruct PacmanDemo(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman, PacStruct ghosts[NUMBER_OF_GHOSTS], int time) {
	PacStruct sol = pacman;
	int pacmanY = pacman.iPosition;
	int pacmanX = pacman.jPosition;
	int ghostY;
	int ghostX;
	int left = 0, right = 0, up = 0, down = 0;
	for (int i = 0; i < NUMBER_OF_GHOSTS; i++) {
		ghostY = ghosts[i].iPosition;
		ghostX = ghosts[i].jPosition;
		sol.direction = BFS_next(Map, pacmanX, pacmanY, ghostX, ghostY).direction;
		if(ghosts[i].gameMode== Normal)
			switch (sol.direction)
			{
			case DIRECTION_UP:
				up++;
				break;
			case DIRECTION_LEFT:
				left++;
				break;
			case DIRECTION_DOWN:
				down++;
				break;
			default:
				right++;
				break;
			}
		else
			switch (sol.direction)
			{
			case DIRECTION_UP:
				down++;
				break;
			case DIRECTION_LEFT:
				right++;
				break;
			case DIRECTION_DOWN:
				up++;
				break;
			default:
				left++;
				break;
			}
	}
	if (Map[pacmanY - 1][pacmanX] == PAC_DOT || Map[pacmanY - 1][pacmanX] == POWER_PELLET)
		sol.direction = DIRECTION_UP;
	else if (Map[pacmanY][pacmanX - 1] == PAC_DOT || Map[pacmanY][pacmanX - 1] == POWER_PELLET)
		sol.direction = DIRECTION_LEFT;
	else if (Map[pacmanY + 1][pacmanX] == PAC_DOT || Map[pacmanY + 1][pacmanX] == POWER_PELLET)
		sol.direction = DIRECTION_DOWN;
	else if (Map[pacmanY][pacmanX + 1] == PAC_DOT || Map[pacmanY][pacmanX + 1] == POWER_PELLET)
		sol.direction = DIRECTION_RIGHT;
	else if (isDot(Map, pacmanX, pacmanY - 1))
		sol.direction = DIRECTION_UP;
	else if (isDot(Map, pacmanX - 1, pacmanY))
		sol.direction = DIRECTION_LEFT;
	else if (isDot(Map, pacmanX, pacmanY + 1))
		sol.direction = DIRECTION_DOWN;
	else if (isDot(Map, pacmanX + 1, pacmanY))
		sol.direction = DIRECTION_RIGHT;
	else if (time > 850 || countPacDots(Map)<30) {
		for (int i = 0; i < HEIGHT_OF_MAP; i++)
			for (int j = 0; j < WIDTH_OF_MAP; j++)
				if (Map[i][j] == PAC_DOT || Map[i][j] == POWER_PELLET) {
					sol.direction = BFS_next(Map, pacmanX, pacmanY, j, i).direction;
					return sol;
				}
	}
	else if (up == 0 && Map[pacmanY - 1][pacmanX] != WALL && pacman.direction!=DIRECTION_DOWN)
		sol.direction = DIRECTION_UP;
	else if (left == 0 && Map[pacmanY][pacmanX - 1] != WALL && pacman.direction != DIRECTION_RIGHT)
		sol.direction = DIRECTION_LEFT;
	else if (down == 0 && Map[pacmanY + 1][pacmanX] != WALL && pacman.direction != DIRECTION_UP)
		sol.direction = DIRECTION_DOWN;
	else if (right == 0 && Map[pacmanY][pacmanX + 1] != WALL && pacman.direction != DIRECTION_LEFT)
		sol.direction = DIRECTION_RIGHT; 
	else if (up == 1 && Map[pacmanY - 1][pacmanX] != WALL && pacman.direction != DIRECTION_DOWN)
		sol.direction = DIRECTION_UP;
	else if (left == 1 && Map[pacmanY][pacmanX - 1] != WALL && pacman.direction != DIRECTION_RIGHT)
		sol.direction = DIRECTION_LEFT;
	else if (down == 1 && Map[pacmanY + 1][pacmanX] != WALL && pacman.direction != DIRECTION_UP)
		sol.direction = DIRECTION_DOWN;
	else if (right == 1 && Map[pacmanY][pacmanX + 1] != WALL && pacman.direction != DIRECTION_LEFT)
		sol.direction = DIRECTION_RIGHT;
	else if (up == 2 && Map[pacmanY - 1][pacmanX] != WALL && pacman.direction != DIRECTION_DOWN)
		sol.direction = DIRECTION_UP;
	else if (left == 2 && Map[pacmanY][pacmanX - 1] != WALL && pacman.direction != DIRECTION_RIGHT)
		sol.direction = DIRECTION_LEFT;
	else if (down == 2 && Map[pacmanY + 1][pacmanX] != WALL && pacman.direction != DIRECTION_UP)
		sol.direction = DIRECTION_DOWN;
	else if (right == 2 && Map[pacmanY][pacmanX + 1] != WALL && pacman.direction != DIRECTION_LEFT)
		sol.direction = DIRECTION_RIGHT;
	else if (up == 4 && Map[pacmanY - 1][pacmanX] != WALL && pacman.direction != DIRECTION_DOWN)
		sol.direction = DIRECTION_UP;
	else if (left == 4 && Map[pacmanY][pacmanX - 1] != WALL && pacman.direction != DIRECTION_RIGHT)
		sol.direction = DIRECTION_LEFT;
	else if (down == 4 && Map[pacmanY + 1][pacmanX] != WALL && pacman.direction != DIRECTION_UP)
		sol.direction = DIRECTION_DOWN;
	else if (right == 4 && Map[pacmanY][pacmanX + 1] != WALL && pacman.direction != DIRECTION_LEFT)
		sol.direction = DIRECTION_RIGHT;
	else if (up == 0)
		sol.direction = DIRECTION_UP;
	else if (left == 0)
		sol.direction = DIRECTION_LEFT;
	else if (down == 0)
		sol.direction = DIRECTION_DOWN;
	else if (right == 0)
		sol.direction = DIRECTION_RIGHT;
	else if (up == 1)
		sol.direction = DIRECTION_UP;
	else if (left == 1)
		sol.direction = DIRECTION_LEFT;
	else if (down == 1 )
		sol.direction = DIRECTION_DOWN;
	else sol.direction = DIRECTION_RIGHT;
	
	return sol;
}