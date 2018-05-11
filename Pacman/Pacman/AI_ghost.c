#include "game.h"

typedef struct {
	int direction;
	int count;
} BFS_solution;

BFS_solution BFS_next(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], int ghostX, int ghostY, int pacmanX, int pacmanY){
	short visited[HEIGHT_OF_MAP][WIDTH_OF_MAP];
	int queueX[HEIGHT_OF_MAP * WIDTH_OF_MAP];
	int queueY[HEIGHT_OF_MAP * WIDTH_OF_MAP];

	BFS_solution sol;
	int i = 0;
	int queueCount = 1;
	queueX[0] = pacmanX;
	queueY[0] = pacmanY;
	visited[queueY[i]][queueX[i]] = 1;

	while (1){
		if (Map[queueY[i] + 1][queueX[i]] != WALL) {
			if (queueY[i] + 1 == ghostY && queueX[i] == ghostX) {
				sol.direction = DIRECTION_UP;
				sol.count = visited[queueY[i]][queueX[i]];
				return sol;
			}
			queueY[queueCount] = queueX[i] + 1;
			queueX[queueCount++] = queueX[i];
			visited[queueY[i] + 1][queueX[i]] = visited[queueY[i]][queueX[i]] + 1;
		}
		if (Map[queueY[i] - 1][queueX[i]] != WALL) {
			if (queueY[i] - 1 == ghostY && queueX[i] == ghostX) {
				sol.direction = DIRECTION_DOWN;
				sol.count = visited[queueY[i]][queueX[i]];
				return sol;
			}
			queueY[queueCount] = queueX[i] - 1;
			queueX[queueCount++] = queueX[i];

			visited[queueY[i] - 1][queueX[i]] = visited[queueY[i]][queueX[i]] + 1;
		}
		if (Map[queueY[i]][queueX[i] + 1] != WALL) {
			if (queueY[i] == ghostY && queueX[i] + 1 == ghostX) {
				sol.direction = DIRECTION_LEFT;
				sol.count = visited[queueY[i]][queueX[i]];
				return sol;
			}
			queueY[queueCount] = queueY[i];
			queueX[queueCount++] = queueX[i] + 1;

			visited[queueY[i]][queueX[i] + 1] = visited[queueY[i]][queueX[i]] + 1;
		}
		if (Map[queueY[i]][queueX[i] - 1] != WALL) {
			if (queueY[i] == ghostY && queueX[i] - 1 == ghostX) {
				sol.direction = DIRECTION_RIGHT;
				sol.count = visited[queueY[i]][queueX[i]];
				return sol;
			}
			queueY[queueCount] = queueY[i];
			queueX[queueCount++] = queueX[i] - 1;

			visited[queueY[i]][queueX[i] - 1] = visited[queueY[i]][queueX[i]] + 1;
		}

		i++;
	}
}

int BlinkyAI(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], int ghostX, int ghostY, int pacmanX, int pacmanY) {
	return BFS_next(Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], ghostX, ghostY, pacmanX, pacmanY).direction;
}

BFS_solution PinkyAI_logic(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], int ghostX, int ghostY, int pacmanX, int pacmanY) {
	BFS_solution solution;
	solution.count = HEIGHT_OF_MAP * WIDTH_OF_MAP;
	solution.direction = DIRECTION_NONE;
	BFS_solution currentSol;
	if (Map[pacmanX + 1][pacmanY] != WALL) {
		currentSol = BFS_next(Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], ghostX, ghostY, pacmanX + 1, pacmanY);
		if (currentSol.count < solution.count) {
			solution.count = currentSol.count;
			solution.direction = currentSol.direction;
		}
	}
	if (Map[pacmanX - 1][pacmanY] != WALL) {
		currentSol = BFS_next(Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], ghostX, ghostY, pacmanX - 1, pacmanY);
		if (currentSol.count < solution.count) {
			solution.count = currentSol.count;
			solution.direction = currentSol.direction;
		}
	}
	if (Map[pacmanX][pacmanY + 1] != WALL) {
		currentSol = BFS_next(Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], ghostX, ghostY, pacmanX, pacmanY + 1);
		if (currentSol.count < solution.count) {
			solution.count = currentSol.count;
			solution.direction = currentSol.direction;
		}
	}
	if (Map[pacmanX][pacmanY - 1] != WALL) {
		currentSol = BFS_next(Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], ghostX, ghostY, pacmanX, pacmanY - 1);
		if (currentSol.count < solution.count) {
			solution.count = currentSol.count;
			solution.direction = currentSol.direction;
		}
	}

	return solution;
}

int PinkyAI(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], int ghostX, int ghostY, int pacmanX, int pacmanY) {
	return PinkyAI_logic(Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], ghostX, ghostY, pacmanX, pacmanY).direction;
}

int InkyAI(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], int ghostX, int ghostY, int pacmanX, int pacmanY) {
	BFS_solution solution;
	solution.count = HEIGHT_OF_MAP * WIDTH_OF_MAP;
	solution.direction = DIRECTION_NONE;
	BFS_solution currentSol;
	if (Map[pacmanX + 1][pacmanY] != WALL) {
		currentSol = PinkyAI_logic(Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], ghostX, ghostY, pacmanX + 1, pacmanY);
		if (currentSol.count < solution.count) {
			solution.count = currentSol.count;
			solution.direction = currentSol.direction;
		}
	}
	if (Map[pacmanX - 1][pacmanY] != WALL) {
		currentSol = PinkyAI_logic(Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], ghostX, ghostY, pacmanX - 1, pacmanY);
		if (currentSol.count < solution.count) {
			solution.count = currentSol.count;
			solution.direction = currentSol.direction;
		}
	}
	if (Map[pacmanX][pacmanY + 1] != WALL) {
		currentSol = PinkyAI_logic(Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], ghostX, ghostY, pacmanX, pacmanY + 1);
		if (currentSol.count < solution.count) {
			solution.count = currentSol.count;
			solution.direction = currentSol.direction;
		}
	}
	if (Map[pacmanX][pacmanY - 1] != WALL) {
		currentSol = PinkyAI_logic(Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], ghostX, ghostY, pacmanX, pacmanY - 1);
		if (currentSol.count < solution.count) {
			solution.count = currentSol.count;
			solution.direction = currentSol.direction;
		}
	}

	return solution.direction;
}

int ClydeAI(int Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], int ghostX, int ghostY, int pacmanX, int pacmanY) {
	BFS_solution bfsSolution = BFS_next(Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], ghostX, ghostY, pacmanX, pacmanY);
	if (bfsSolution.count > 10)  //po pravilu je 8, ali mi se cini da je to premalo PROVERITI
		return BFS_next(Map[HEIGHT_OF_MAP][WIDTH_OF_MAP], ghostX, ghostY, HEIGHT_OF_MAP-1, 1).direction;
	return bfsSolution.direction;
}