#include "ghosts.h"


typedef struct {
	int direction;
	int count;
} BFS_solution;

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
		if (Map[queueY[i] + 1][queueX[i]] != WALL && visited[queueY[i] + 1][queueX[i]] <= 0) {
			queueY[queueCount] = queueY[i] + 1;
			queueX[queueCount++] = queueX[i];
			visited[queueY[i] + 1][queueX[i]] = visited[queueY[i]][queueX[i]] + 1;
		}
		if (queueY[i] - 1 == ghostY && queueX[i] == ghostX && Map[queueY[i]][queueX[i]] != WALL) {
			sol.direction = DIRECTION_DOWN;
			sol.count = visited[queueY[i]][queueX[i]];
			return sol;
		}
		if (Map[queueY[i] - 1][queueX[i]] != WALL && visited[queueY[i] - 1][queueX[i]] <= 0) {
			
			queueY[queueCount] = queueY[i] - 1;
			queueX[queueCount++] = queueX[i];

			visited[queueY[i] - 1][queueX[i]] = visited[queueY[i]][queueX[i]] + 1;
		}
		if (queueY[i] == ghostY && queueX[i] + 1 == ghostX && Map[queueY[i]][queueX[i]] != WALL) {
			sol.direction = DIRECTION_LEFT ;
			sol.count = visited[queueY[i]][queueX[i]];
			return sol;
		}
		if (Map[queueY[i]][queueX[i] + 1] != WALL && visited[queueY[i]][queueX[i] + 1] <= 0) {
			
			queueY[queueCount] = queueY[i];
			queueX[queueCount++] = queueX[i] + 1;

			visited[queueY[i]][queueX[i] + 1] = visited[queueY[i]][queueX[i]] + 1;
		}
		if (queueY[i] == ghostY && queueX[i] - 1 == ghostX && Map[queueY[i]][queueX[i]] != WALL) {
			sol.direction = DIRECTION_RIGHT   ;
			sol.count = visited[queueY[i]][queueX[i]];
			return sol;
		}
		if (Map[queueY[i]][queueX[i] - 1] != WALL && visited[queueY[i]][queueX[i] - 1] <= 0) {
			
			queueY[queueCount] = queueY[i];
			queueX[queueCount++] = queueX[i] - 1;

			visited[queueY[i]][queueX[i] - 1] = visited[queueY[i]][queueX[i]] + 1;
		}

		i++;
	}
	sol.direction = DIRECTION_NONE;
	sol.count = 0;
	return sol;
}

PacStruct BlinkyAI(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman, PacStruct ghosts[NUMBER_OF_GHOSTS], int currentGhostIndex) {
	PacStruct sol = ghosts[currentGhostIndex];
	int ghostY = ghosts[currentGhostIndex].iPosition;
	int ghostX = ghosts[currentGhostIndex].jPosition;
	int pacmanY = pacman.iPosition;
	int pacmanX = pacman.jPosition;

	sol.direction = BFS_next(Map, ghostX, ghostY, pacmanX, pacmanY).direction;

	return sol;
}

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


	return solution;
}

PacStruct PinkyAI(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman, PacStruct ghosts[NUMBER_OF_GHOSTS], int currentGhostIndex) {
	PacStruct sol = ghosts[currentGhostIndex];
	int ghostY = ghosts[currentGhostIndex].iPosition;
	int ghostX = ghosts[currentGhostIndex].jPosition;
	int pacmanY = pacman.iPosition;
	int pacmanX = pacman.jPosition;

	sol.direction = PinkyAI_logic(Map, ghostX, ghostY, pacmanX, pacmanY).direction;

	return sol;
}

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

	sol.direction = solution.direction;
	
	return sol;
}

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