#include "gameGraphics.h"
#include "gameMap.h"
#include "pacStruct.h"
#include "highscores.h"
#include "cheats.h"
#include <stdlib.h>
#include <string.h>

/*!	\file gameGraphics.c
 *	\brief Contains graphics functions definitions needed for gameplay
 */

static SDL_Surface* surface[HEIGHT_OF_MAP][WIDTH_OF_MAP];
static SDL_Texture *tile[HEIGHT_OF_MAP][WIDTH_OF_MAP];
static SDL_Rect tile_rect[HEIGHT_OF_MAP][WIDTH_OF_MAP];
SDL_Texture* ScoreBoxTexture, *LivesBoxTexture;
extern GameTextures gameTexturesManager;

void initGameTextures() {
	int i, j;
	SDL_Surface * PacSurface, *TempSurface;
	TTF_Font *font = TTF_OpenFont("impact.ttf", 46);
	SDL_Color yellow = { 255, 255, 0 };
	char buffer[2];

	// Pacman open mouth textures
	PacSurface = SDL_LoadBMP("Pictures/pacmanU.bmp");
	gameTexturesManager.pacmanOpenMouthTextures[DIRECTION_UP] = SDL_CreateTextureFromSurface(game.screen.renderer, PacSurface);
	SDL_FreeSurface(PacSurface);
	PacSurface = SDL_LoadBMP("Pictures/pacmanR.bmp");
	gameTexturesManager.pacmanOpenMouthTextures[DIRECTION_RIGHT] = SDL_CreateTextureFromSurface(game.screen.renderer, PacSurface);
	SDL_FreeSurface(PacSurface);
	PacSurface = SDL_LoadBMP("Pictures/pacmanL.bmp");
	gameTexturesManager.pacmanOpenMouthTextures[DIRECTION_LEFT] = SDL_CreateTextureFromSurface(game.screen.renderer, PacSurface);
	SDL_FreeSurface(PacSurface);
	PacSurface = SDL_LoadBMP("Pictures/pacmanD.bmp");
	gameTexturesManager.pacmanOpenMouthTextures[DIRECTION_DOWN] = SDL_CreateTextureFromSurface(game.screen.renderer, PacSurface);
	SDL_FreeSurface(PacSurface);

	// Pacman closed mouth textures
	PacSurface = SDL_LoadBMP("Pictures/pacmanUC.bmp");
	gameTexturesManager.pacmanShutMouthTextures[DIRECTION_UP] = SDL_CreateTextureFromSurface(game.screen.renderer, PacSurface);
	SDL_FreeSurface(PacSurface);
	PacSurface = SDL_LoadBMP("Pictures/pacmanRC.bmp");
	gameTexturesManager.pacmanShutMouthTextures[DIRECTION_RIGHT] = SDL_CreateTextureFromSurface(game.screen.renderer, PacSurface);
	SDL_FreeSurface(PacSurface);
	PacSurface = SDL_LoadBMP("Pictures/pacmanLC.bmp");
	gameTexturesManager.pacmanShutMouthTextures[DIRECTION_LEFT] = SDL_CreateTextureFromSurface(game.screen.renderer, PacSurface);
	SDL_FreeSurface(PacSurface);
	PacSurface = SDL_LoadBMP("Pictures/pacmanDC.bmp");
	gameTexturesManager.pacmanShutMouthTextures[DIRECTION_DOWN] = SDL_CreateTextureFromSurface(game.screen.renderer, PacSurface);
	SDL_FreeSurface(PacSurface);

	// Static environment textures
	TempSurface = SDL_LoadBMP("Pictures/WallGreenEmpty.bmp");
	gameTexturesManager.wallTexture = SDL_CreateTextureFromSurface(game.screen.renderer, TempSurface);
	SDL_FreeSurface(TempSurface);
	TempSurface = SDL_LoadBMP("Pictures/background.bmp");
	gameTexturesManager.backgroundTexture = SDL_CreateTextureFromSurface(game.screen.renderer, TempSurface);
	SDL_FreeSurface(TempSurface); 
	TempSurface = SDL_LoadBMP("Pictures/pacDot.bmp");
	gameTexturesManager.pacDotTexture = SDL_CreateTextureFromSurface(game.screen.renderer, TempSurface);
	SDL_FreeSurface(TempSurface); 
	TempSurface = SDL_LoadBMP("Pictures/powerPellet1.bmp");
	gameTexturesManager.powerPelletTexture = SDL_CreateTextureFromSurface(game.screen.renderer, TempSurface);
	SDL_FreeSurface(TempSurface);

	// Static environment textures for Srbenda mode
	TempSurface = SDL_LoadBMP("Pictures/WallSrb2.bmp");
	gameTexturesManager.wallSrbendaTexture = SDL_CreateTextureFromSurface(game.screen.renderer, TempSurface);
	SDL_FreeSurface(TempSurface);
	TempSurface = SDL_LoadBMP("Pictures/burek.bmp");
	gameTexturesManager.powerPelletSrbendaTexture = SDL_CreateTextureFromSurface(game.screen.renderer, TempSurface);
	SDL_FreeSurface(TempSurface);

	//Pacman open mouth textures for Srbenda mode
	PacSurface = SDL_LoadBMP("Pictures/SRBpacmanU.bmp");
	gameTexturesManager.pacmanSrbendaOpenMouth[DIRECTION_UP] = SDL_CreateTextureFromSurface(game.screen.renderer, PacSurface);
	SDL_FreeSurface(PacSurface);
	PacSurface = SDL_LoadBMP("Pictures/SRBpacmanR.bmp");
	gameTexturesManager.pacmanSrbendaOpenMouth[DIRECTION_RIGHT] = SDL_CreateTextureFromSurface(game.screen.renderer, PacSurface);
	SDL_FreeSurface(PacSurface);
	PacSurface = SDL_LoadBMP("Pictures/SRBpacmanL.bmp");
	gameTexturesManager.pacmanSrbendaOpenMouth[DIRECTION_LEFT] = SDL_CreateTextureFromSurface(game.screen.renderer, PacSurface);
	SDL_FreeSurface(PacSurface);
	PacSurface = SDL_LoadBMP("Pictures/SRBpacmanD.bmp");
	gameTexturesManager.pacmanSrbendaOpenMouth[DIRECTION_DOWN] = SDL_CreateTextureFromSurface(game.screen.renderer, PacSurface);
	SDL_FreeSurface(PacSurface);

	// Pacman closed mouth textures for Srbenda mode
	PacSurface = SDL_LoadBMP("Pictures/SRBpacmanUC.bmp");
	gameTexturesManager.pacmanSrbendaShutMouth[DIRECTION_UP] = SDL_CreateTextureFromSurface(game.screen.renderer, PacSurface);
	SDL_FreeSurface(PacSurface);
	PacSurface = SDL_LoadBMP("Pictures/SRBpacmanRC.bmp");
	gameTexturesManager.pacmanSrbendaShutMouth[DIRECTION_RIGHT] = SDL_CreateTextureFromSurface(game.screen.renderer, PacSurface);
	SDL_FreeSurface(PacSurface);
	PacSurface = SDL_LoadBMP("Pictures/SRBpacmanLC.bmp");
	gameTexturesManager.pacmanSrbendaShutMouth[DIRECTION_LEFT] = SDL_CreateTextureFromSurface(game.screen.renderer, PacSurface);
	SDL_FreeSurface(PacSurface);
	PacSurface = SDL_LoadBMP("Pictures/SRBpacmanDC.bmp");
	gameTexturesManager.pacmanSrbendaShutMouth[DIRECTION_DOWN] = SDL_CreateTextureFromSurface(game.screen.renderer, PacSurface);
	SDL_FreeSurface(PacSurface);

	// Ghost textures, reversed ghost texture and eaten ghost texture
	PacSurface = SDL_LoadBMP("Pictures/Blinky.bmp");
	gameTexturesManager.ghostTextures[0] = SDL_CreateTextureFromSurface(game.screen.renderer, PacSurface);
	SDL_FreeSurface(PacSurface);
	PacSurface = SDL_LoadBMP("Pictures/Inky.bmp");
	gameTexturesManager.ghostTextures[1] = SDL_CreateTextureFromSurface(game.screen.renderer, PacSurface);
	SDL_FreeSurface(PacSurface);
	PacSurface = SDL_LoadBMP("Pictures/Pinky.bmp");
	gameTexturesManager.ghostTextures[2] = SDL_CreateTextureFromSurface(game.screen.renderer, PacSurface);
	SDL_FreeSurface(PacSurface);
	PacSurface = SDL_LoadBMP("Pictures/Clyde.bmp");
	gameTexturesManager.ghostTextures[3] = SDL_CreateTextureFromSurface(game.screen.renderer, PacSurface);
	SDL_FreeSurface(PacSurface);

	PacSurface = SDL_LoadBMP("Pictures/reversedGhost.bmp");
	gameTexturesManager.reverseGhostTexture = SDL_CreateTextureFromSurface(game.screen.renderer, PacSurface);
	SDL_FreeSurface(PacSurface);

	PacSurface = SDL_LoadBMP("Pictures/EatenGhost.bmp");
	gameTexturesManager.eatenGhostTexture = SDL_CreateTextureFromSurface(game.screen.renderer, PacSurface);
	SDL_FreeSurface(PacSurface);

	// In-game box textures
	TempSurface = SDL_LoadBMP("Pictures/pacmanR.bmp");
	gameTexturesManager.livesBoxTexture = SDL_CreateTextureFromSurface(game.screen.renderer, TempSurface);
	SDL_FreeSurface(TempSurface);
	TempSurface = TTF_RenderText_Solid(font, "SCORE:", yellow);
	gameTexturesManager.scoreBoxTexture = SDL_CreateTextureFromSurface(game.screen.renderer, TempSurface);
	SDL_FreeSurface(TempSurface);
	TempSurface = TTF_RenderText_Solid(font, "LVL:", yellow);
	gameTexturesManager.levelBoxTexture = SDL_CreateTextureFromSurface(game.screen.renderer, TempSurface);
	SDL_FreeSurface(TempSurface);


	// In-game rects for score and level
	gameTexturesManager.levelBoxRect.x = (WIDTH_OF_MAP - 5) * game.screen.width / (WIDTH_OF_MAP * 3);
	gameTexturesManager.levelBoxRect.y = 0;
	gameTexturesManager.levelBoxRect.w = 2 * game.screen.width / (WIDTH_OF_MAP * 3);
	gameTexturesManager.levelBoxRect.h = 2 * game.screen.height / (HEIGHT_OF_MAP * 2);

	gameTexturesManager.scoreBoxRect.x = 0;
	gameTexturesManager.scoreBoxRect.y = 0;
	gameTexturesManager.scoreBoxRect.w = 4 * game.screen.width / (WIDTH_OF_MAP * 3);
	gameTexturesManager.scoreBoxRect.h = 2 * game.screen.height / (HEIGHT_OF_MAP * 2);

	// Textures and rects for score digits
	for (i = 0; i < NUMBER_OF_DIGITS; i++) {
		gameTexturesManager.scoreDigitRect[i].x = 4 * game.screen.width / (WIDTH_OF_MAP * 3) + 2 * i * game.screen.width / (WIDTH_OF_MAP * 9);
		gameTexturesManager.scoreDigitRect[i].y = 0;
		gameTexturesManager.scoreDigitRect[i].w = 2 * game.screen.width / (WIDTH_OF_MAP * 9);
		gameTexturesManager.scoreDigitRect[i].h = 2 * game.screen.height / (HEIGHT_OF_MAP * 2);
		sprintf(buffer, "%d", i);
		TempSurface = TTF_RenderText_Solid(font, buffer, yellow);
		gameTexturesManager.scoreDigitTextures[i] = SDL_CreateTextureFromSurface(game.screen.renderer, TempSurface);
		SDL_FreeSurface(TempSurface);
	}

	// Rects for lvl digits
	for (i = 0; i < NUMBER_OF_LVL_DIGITS; i++) {
		gameTexturesManager.levelDigitRect[i].x = (WIDTH_OF_MAP - 3) * game.screen.width / (WIDTH_OF_MAP * 3) + 2 * i * game.screen.width / (WIDTH_OF_MAP * 9);
		gameTexturesManager.levelDigitRect[i].y = 0;
		gameTexturesManager.levelDigitRect[i].w = 2 * game.screen.width / (WIDTH_OF_MAP * 9);
		gameTexturesManager.levelDigitRect[i].h = 2 * game.screen.height / (HEIGHT_OF_MAP * 2);
	}

	// Rectangles representing the map
	for (i = 0; i < HEIGHT_OF_MAP; i++) {
		for (j = 0; j < WIDTH_OF_MAP; j++) {
			gameTexturesManager.mapTileRects[i][j].x = j * game.screen.width / (WIDTH_OF_MAP * 3);
			gameTexturesManager.mapTileRects[i][j].y = (i + 2) * game.screen.height / (HEIGHT_OF_MAP * 2);
			gameTexturesManager.mapTileRects[i][j].w = game.screen.width / (WIDTH_OF_MAP * 3);
			gameTexturesManager.mapTileRects[i][j].h = game.screen.height / (HEIGHT_OF_MAP * 2);
		}
	}
	return;
}

void destroyGameTextures() {
	int i;
	for (i = 0; i < NUMBER_OF_DIRECTIONS; i++) {	
		SDL_DestroyTexture(gameTexturesManager.pacmanOpenMouthTextures[i]);
		SDL_DestroyTexture(gameTexturesManager.pacmanShutMouthTextures[i]);
		SDL_DestroyTexture(gameTexturesManager.pacmanSrbendaOpenMouth[i]);
		SDL_DestroyTexture(gameTexturesManager.pacmanSrbendaShutMouth[i]);
		SDL_DestroyTexture(gameTexturesManager.ghostTextures[i]);
	}
	SDL_DestroyTexture(gameTexturesManager.backgroundTexture);
	SDL_DestroyTexture(gameTexturesManager.levelBoxTexture);
	SDL_DestroyTexture(gameTexturesManager.pacDotTexture);
	SDL_DestroyTexture(gameTexturesManager.livesBoxTexture);
	SDL_DestroyTexture(gameTexturesManager.powerPelletSrbendaTexture);
	SDL_DestroyTexture(gameTexturesManager.powerPelletTexture);
	SDL_DestroyTexture(gameTexturesManager.reverseGhostTexture);
	SDL_DestroyTexture(gameTexturesManager.scoreBoxTexture);
	SDL_DestroyTexture(gameTexturesManager.wallSrbendaTexture);
	SDL_DestroyTexture(gameTexturesManager.wallTexture);
}

/*!
 *	\brief Gets old position of pacStruct
 *	\param pacStruct PacStruct containing current position
 *	\return PacStruct with old postition
 */
static PacStruct getOldPacPosition(PacStruct pacStruct) {
	PacStruct oldPosition;

	oldPosition.iPosition = pacStruct.iPosition;
	oldPosition.jPosition = pacStruct.jPosition;
	oldPosition.direction = pacStruct.direction;

	switch (pacStruct.direction) {
	case DIRECTION_NONE:
		break;
	case DIRECTION_UP:
		oldPosition.iPosition = (pacStruct.iPosition + 1) % HEIGHT_OF_MAP;
		break;
	case DIRECTION_RIGHT:
		oldPosition.jPosition = (pacStruct.jPosition - 1 + WIDTH_OF_MAP) % WIDTH_OF_MAP;
		break;
	case DIRECTION_DOWN:
		oldPosition.iPosition = (pacStruct.iPosition - 1 + HEIGHT_OF_MAP) % HEIGHT_OF_MAP;
		break;
	case DIRECTION_LEFT:
		oldPosition.jPosition = (pacStruct.jPosition + 1) % WIDTH_OF_MAP;
		break;
	default:
		break;
	}

	return oldPosition;
}

void updateLevelBox(int level) {
	extern Game game;
	int i = 0, j = 0, bufferArray[NUMBER_OF_LVL_DIGITS] = { 0 };
	int templvl = level + 1;
	SDL_RenderCopy(game.screen.renderer, gameTexturesManager.levelBoxTexture, NULL, &gameTexturesManager.levelBoxRect);
	while (templvl > 0) {
		bufferArray[i++] = templvl % 10;
		templvl /= 10;
	}
	i--;
	for (; i >= 0; i--) {
		SDL_RenderFillRect(game.screen.renderer, &gameTexturesManager.levelDigitRect[j]);
		SDL_RenderCopy(game.screen.renderer, gameTexturesManager.scoreDigitTextures[bufferArray[i]], NULL, &gameTexturesManager.levelDigitRect[j]);
		j++;
	}
	SDL_RenderPresent(game.screen.renderer);
	
	return;
	
}

void updateScoreBox(Highscore currentScore) {
	extern Game game;
	int i = 0, j = 0, bufferArray[NUMBER_OF_DIGITS] = {0};
	SDL_RenderCopy(game.screen.renderer, gameTexturesManager.scoreBoxTexture, NULL, &gameTexturesManager.scoreBoxRect);
	while (currentScore.points > 0) {
		bufferArray[i++] = currentScore.points % 10;
		currentScore.points /= 10;
	}
	i--;
	for (; i >= 0; i--) {
		SDL_RenderFillRect(game.screen.renderer, &gameTexturesManager.scoreDigitRect[j]);
		SDL_RenderCopy(game.screen.renderer, gameTexturesManager.scoreDigitTextures[bufferArray[i]], NULL, &gameTexturesManager.scoreDigitRect[j]);
		j++;
	}
	SDL_RenderPresent(game.screen.renderer);
	return;
}

void updateLivesBox(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], int numberOfLivesTiles, int livesCount) {
	SDL_Rect LivesBoxRect;
	extern Game game;
	for (int i = 0; i < numberOfLivesTiles; i++) {
		LivesBoxRect.x = 2 * i * game.screen.width / (WIDTH_OF_MAP * 3);
		LivesBoxRect.y = (HEIGHT_OF_MAP + 2) * game.screen.height / (HEIGHT_OF_MAP * 2);
		LivesBoxRect.w = 2 * game.screen.width / (WIDTH_OF_MAP * 3);
		LivesBoxRect.h = 2 * game.screen.height / (HEIGHT_OF_MAP * 2);
		if (i < livesCount) { 
			SDL_RenderCopy(game.screen.renderer, gameTexturesManager.livesBoxTexture, NULL, &LivesBoxRect);
		}
		else {
			SDL_RenderCopy(game.screen.renderer, gameTexturesManager.backgroundTexture, NULL, &LivesBoxRect);
		}
	}
	return;
}

void printInitMap(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman, int srbendaMod, int newLevel) {
	int i, j;
	TTF_Font *font = TTF_OpenFont("impact.ttf", 46);
	SDL_Color yellow = { 255, 255, 0 };
	extern Game game;
	for (i = 0; i < HEIGHT_OF_MAP; i++) {
		for (j = 0; j < WIDTH_OF_MAP; j++) {
			if (map[i][j] == WALL) {
				if (srbendaMod) {
					SDL_RenderCopy(game.screen.renderer, gameTexturesManager.wallSrbendaTexture, NULL, &gameTexturesManager.mapTileRects[i][j]);
				}
				else {
					SDL_RenderCopy(game.screen.renderer, gameTexturesManager.wallTexture, NULL, &gameTexturesManager.mapTileRects[i][j]);
				}
			}
			else if (map[i][j] == PAC_DOT) {
				if (srbendaMod) {
					SDL_RenderCopy(game.screen.renderer, gameTexturesManager.pacDotTexture, NULL, &gameTexturesManager.mapTileRects[i][j]);
				}
				else {
					SDL_RenderCopy(game.screen.renderer, gameTexturesManager.pacDotTexture, NULL, &gameTexturesManager.mapTileRects[i][j]);
				}
			}
			else if (map[i][j] == POWER_PELLET) {
				if (srbendaMod) {
					SDL_RenderCopy(game.screen.renderer, gameTexturesManager.powerPelletSrbendaTexture, NULL, &gameTexturesManager.mapTileRects[i][j]);
				}
				else {
					SDL_RenderCopy(game.screen.renderer, gameTexturesManager.powerPelletTexture, NULL, &gameTexturesManager.mapTileRects[i][j]);
				}
			}
			else {
				SDL_RenderCopy(game.screen.renderer, gameTexturesManager.backgroundTexture, NULL, &gameTexturesManager.mapTileRects[i][j]);
			}
			SDL_FreeSurface(surface[i][j]);
		}
		if (newLevel) {
			SDL_RenderPresent(game.screen.renderer);
		}
	}
	if (!invisibilityCheat) {
		if (srbendaMod) {
			SDL_RenderCopy(game.screen.renderer, gameTexturesManager.pacmanSrbendaOpenMouth[DIRECTION_RIGHT], NULL, &gameTexturesManager.mapTileRects[pacman.iPosition][pacman.jPosition]);
		}
		else {
			SDL_RenderCopy(game.screen.renderer, gameTexturesManager.pacmanOpenMouthTextures[DIRECTION_RIGHT], NULL, &gameTexturesManager.mapTileRects[pacman.iPosition][pacman.jPosition]);
		}
	}
	else {
		SDL_RenderFillRect(game.screen.renderer, &gameTexturesManager.mapTileRects[pacman.iPosition][pacman.jPosition]);
	}
	SDL_RenderPresent(game.screen.renderer);
	return;
}

void updatePacman(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman, int timer_tick, int srbendaMod) {
	extern Game game;
	PacStruct oldPosition = getOldPacPosition(pacman);
	if (timer_tick % 4 == 0 && (oldPosition.iPosition != pacman.iPosition || oldPosition.jPosition != pacman.jPosition))
		if (map[oldPosition.iPosition][oldPosition.jPosition] == WALL) {
			if (srbendaMod) {
				SDL_RenderCopy(game.screen.renderer, gameTexturesManager.wallSrbendaTexture, NULL, &gameTexturesManager.mapTileRects[oldPosition.iPosition][oldPosition.jPosition]);
			}
			else {
				SDL_RenderCopy(game.screen.renderer, gameTexturesManager.wallTexture, NULL, &gameTexturesManager.mapTileRects[oldPosition.iPosition][oldPosition.jPosition]);
			}
		}
		else {
			SDL_RenderCopy(game.screen.renderer, gameTexturesManager.backgroundTexture, NULL, &gameTexturesManager.mapTileRects[oldPosition.iPosition][oldPosition.jPosition]);
		}
	if (pacman.direction != DIRECTION_NONE) {
		if (!invisibilityCheat) {
			if (timer_tick % 2) {
				if (srbendaMod) {
					SDL_RenderCopy(game.screen.renderer, gameTexturesManager.pacmanSrbendaOpenMouth[pacman.direction], NULL, &gameTexturesManager.mapTileRects[pacman.iPosition][pacman.jPosition]);
				}
				else {
					SDL_RenderCopy(game.screen.renderer, gameTexturesManager.pacmanOpenMouthTextures[pacman.direction], NULL, &gameTexturesManager.mapTileRects[pacman.iPosition][pacman.jPosition]);
				}
			}
			else {
				if (srbendaMod) {
					SDL_RenderCopy(game.screen.renderer, gameTexturesManager.pacmanSrbendaShutMouth[pacman.direction], NULL, &gameTexturesManager.mapTileRects[pacman.iPosition][pacman.jPosition]);
				}
				else {
					SDL_RenderCopy(game.screen.renderer, gameTexturesManager.pacmanShutMouthTextures[pacman.direction], NULL, &gameTexturesManager.mapTileRects[pacman.iPosition][pacman.jPosition]);
				}
			}
		}
		else {
			SDL_RenderFillRect(game.screen.renderer, &gameTexturesManager.mapTileRects[pacman.iPosition][pacman.jPosition]);
		}
	}
	return;
}

void updateGhosts(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct ghosts[NUMBER_OF_GHOSTS], int timer_tick, int srbendaMod, PacStruct pacman, enum Direction lastPacmanDirection, int lastMovingTimerTick) {
	int i;
	extern Game game;
	PacStruct oldPositionGhost;
	for (i = 0; i < NUMBER_OF_GHOSTS; i++) {
		oldPositionGhost = getOldPacPosition(ghosts[i]);
		if ((ghosts[i].gameMode != Normal || immortalityCheat) && oldPositionGhost.iPosition == pacman.iPosition && oldPositionGhost.jPosition == pacman.jPosition && pacman.direction == DIRECTION_NONE) {
			if (!invisibilityCheat) {
				if (lastMovingTimerTick % 2) {
					if (srbendaMod) {
						SDL_RenderCopy(game.screen.renderer, gameTexturesManager.pacmanSrbendaOpenMouth[lastPacmanDirection], NULL, &gameTexturesManager.mapTileRects[oldPositionGhost.iPosition][oldPositionGhost.jPosition]);
					}
					else {
						SDL_RenderCopy(game.screen.renderer, gameTexturesManager.pacmanOpenMouthTextures[lastPacmanDirection], NULL, &gameTexturesManager.mapTileRects[oldPositionGhost.iPosition][oldPositionGhost.jPosition]);
					}
				}
				else {
					if (srbendaMod) {
						SDL_RenderCopy(game.screen.renderer, gameTexturesManager.pacmanSrbendaShutMouth[lastPacmanDirection], NULL, &gameTexturesManager.mapTileRects[oldPositionGhost.iPosition][oldPositionGhost.jPosition]);
					}
					else {
						SDL_RenderCopy(game.screen.renderer, gameTexturesManager.pacmanShutMouthTextures[lastPacmanDirection], NULL, &gameTexturesManager.mapTileRects[oldPositionGhost.iPosition][oldPositionGhost.jPosition]);
					}
				}
			}
			else {
				SDL_RenderFillRect(game.screen.renderer, &gameTexturesManager.mapTileRects[oldPositionGhost.iPosition][oldPositionGhost.jPosition]);
			}
		}
		else if (map[oldPositionGhost.iPosition][oldPositionGhost.jPosition] == PAC_DOT) {
			SDL_RenderCopy(game.screen.renderer, gameTexturesManager.pacDotTexture, NULL, &gameTexturesManager.mapTileRects[oldPositionGhost.iPosition][oldPositionGhost.jPosition]);
		}
		else if (map[oldPositionGhost.iPosition][oldPositionGhost.jPosition] == POWER_PELLET) {
			if (srbendaMod) {
				SDL_RenderCopy(game.screen.renderer, gameTexturesManager.powerPelletSrbendaTexture, NULL, &gameTexturesManager.mapTileRects[oldPositionGhost.iPosition][oldPositionGhost.jPosition]);
			}
			else {
				SDL_RenderCopy(game.screen.renderer, gameTexturesManager.powerPelletTexture, NULL, &gameTexturesManager.mapTileRects[oldPositionGhost.iPosition][oldPositionGhost.jPosition]);
			}
		}
		else if (map[oldPositionGhost.iPosition][oldPositionGhost.jPosition] == WALL) {
			if (srbendaMod) {
				SDL_RenderCopy(game.screen.renderer, gameTexturesManager.wallSrbendaTexture, NULL, &gameTexturesManager.mapTileRects[oldPositionGhost.iPosition][oldPositionGhost.jPosition]);
			}
			else {
				SDL_RenderCopy(game.screen.renderer, gameTexturesManager.wallTexture, NULL, &gameTexturesManager.mapTileRects[oldPositionGhost.iPosition][oldPositionGhost.jPosition]);
			}
		}
		else if (map[oldPositionGhost.iPosition][oldPositionGhost.jPosition] == NO_WALL) {
			SDL_RenderCopy(game.screen.renderer, gameTexturesManager.backgroundTexture, NULL, &gameTexturesManager.mapTileRects[oldPositionGhost.iPosition][oldPositionGhost.jPosition]);
		}

		if (ghosts[i].gameMode == Normal) {
			SDL_RenderCopy(game.screen.renderer, gameTexturesManager.ghostTextures[i], NULL, &gameTexturesManager.mapTileRects[ghosts[i].iPosition][ghosts[i].jPosition]);
		}
		else if (ghosts[i].gameMode == Reverse || (ghosts[i].gameMode == EndReverse && (timer_tick % 2))) {
			SDL_RenderCopy(game.screen.renderer, gameTexturesManager.reverseGhostTexture, NULL, &gameTexturesManager.mapTileRects[ghosts[i].iPosition][ghosts[i].jPosition]);
		}
		else if (ghosts[i].gameMode == EndReverse && (timer_tick % 2 == 0)) {
			SDL_RenderCopy(game.screen.renderer, gameTexturesManager.backgroundTexture, NULL, &gameTexturesManager.mapTileRects[ghosts[i].iPosition][ghosts[i].jPosition]);
		}
		else if (ghosts[i].gameMode == GhostEaten) {
			SDL_RenderCopy(game.screen.renderer, gameTexturesManager.eatenGhostTexture, NULL, &gameTexturesManager.mapTileRects[ghosts[i].iPosition][ghosts[i].jPosition]);
		}
	}
	return;
}
