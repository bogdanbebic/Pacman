#include "gameGraphics.h"
#include "gameMap.h"
#include "pacStruct.h"
#include <stdlib.h>
#include <string.h>

static SDL_Surface* surface[HEIGHT_OF_MAP][WIDTH_OF_MAP];
static SDL_Texture *tile[HEIGHT_OF_MAP][WIDTH_OF_MAP];
static SDL_Rect tile_rect[HEIGHT_OF_MAP][WIDTH_OF_MAP];
static SDL_Surface* ScoreBoxSurface, *LivesBoxSurface;
static SDL_Texture* ScoreBoxTexture, *LivesBoxTexture;
static SDL_Rect ScoreBoxRect, LivesBoxRect;

/*
*	Returns the previous position of pacStruct
*	Return value:
*	PacStruct containing the previous position
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
		oldPosition.iPosition = pacStruct.iPosition + 1;
		break;
	case DIRECTION_RIGHT:
		oldPosition.jPosition = pacStruct.jPosition - 1;
		break;
	case DIRECTION_DOWN:
		oldPosition.iPosition = pacStruct.iPosition - 1;
		break;
	case DIRECTION_LEFT:
		oldPosition.jPosition = pacStruct.jPosition + 1;
		break;
	default:
		break;
	}

	return oldPosition;
}

/*
*	Updates the score box in the game screen
*	according to the argument currentScore
*/
void updateScoreBox(int currentScore) {
	extern SDL_Surface* ScoreBoxSurface;
	extern SDL_Texture* ScoreBoxTexture;
	extern SDL_Rect ScoreBoxRect;
	TTF_Font *font = TTF_OpenFont("impact.ttf", 46);
	SDL_Color yellow = { 255, 255, 0 };
	extern Game game;
	char scoreBox[LEN_OF_SCORE_BOX] = "SCORE: ";
	char bufferString[LEN_OF_SCORE_BOX];

	//dopisuje broj dotova na kraj stringa scoreBox
	_itoa_s(currentScore, bufferString, sizeof(bufferString), 10);
	strcat_s(scoreBox, LEN_OF_SCORE_BOX, bufferString);

	//stampanje score box-a
	ScoreBoxSurface = TTF_RenderText_Solid(font, scoreBox, yellow);
	ScoreBoxTexture = SDL_CreateTextureFromSurface(game.screen.renderer, ScoreBoxSurface);
	ScoreBoxRect.x = 0;
	ScoreBoxRect.y = 0;
	ScoreBoxRect.w = 2 * game.screen.width / WIDTH_OF_MAP / 3;
	ScoreBoxRect.h = game.screen.height / HEIGHT_OF_MAP / 2;
	SDL_RenderFillRect(game.screen.renderer, &ScoreBoxRect);
	SDL_RenderCopy(game.screen.renderer, ScoreBoxTexture, NULL, &ScoreBoxRect);
	SDL_RenderPresent(game.screen.renderer);
	return;
}

/*
*	Updates the Pacman lives box in the game screen
*	according to the argument livesCount
*/
void updateLivesBox(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], int numberOfLivesTiles, int livesCount) {
	extern SDL_Surface* LivesBoxSurface;
	extern SDL_Texture* LivesBoxTexture;
	extern SDL_Rect LivesBoxRect;
	extern Game game;
	for (int i = 0; i < numberOfLivesTiles; i++) {
		if (numberOfLivesTiles == 1) { //biranje odgovarajuce slike u Livesbox-u
			LivesBoxSurface = SDL_LoadBMP("Pictures/SinglePacLife.bmp");
		}
		else {
			if (i < livesCount) { 
				if (i == 0) {
					LivesBoxSurface = SDL_LoadBMP("Pictures/FirstPacLife.bmp");
				}
				else if (i == numberOfLivesTiles - 1) {
					LivesBoxSurface = SDL_LoadBMP("Pictures/LastPacLife.bmp");
				}
				else {
					LivesBoxSurface = SDL_LoadBMP("Pictures/MidPacLife.bmp");
				}
			}
			else {
				if (i == numberOfLivesTiles - 1) {
					LivesBoxSurface = SDL_LoadBMP("Pictures/NoLastLife.bmp");
				}
				else {
					LivesBoxSurface = SDL_LoadBMP("Pictures/NoMidLife.bmp");
				}
			}
		}
		//stampanje odgovarajuce slike
		LivesBoxTexture = SDL_CreateTextureFromSurface(game.screen.renderer, LivesBoxSurface);
		LivesBoxRect.x = i * game.screen.width / WIDTH_OF_MAP / 3;
		LivesBoxRect.y = (HEIGHT_OF_MAP - 1) * game.screen.height / HEIGHT_OF_MAP / 2;
		LivesBoxRect.w = game.screen.width / WIDTH_OF_MAP / 3;
		LivesBoxRect.h = game.screen.height / HEIGHT_OF_MAP / 2;
		SDL_RenderFillRect(game.screen.renderer, &LivesBoxRect);
		SDL_RenderCopy(game.screen.renderer, LivesBoxTexture, NULL, &LivesBoxRect);
	}
	return;
}

/*
*	Prints argument map and pacman
*	on the game screen
*/
void printInitMap(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman) {
	int i, j;

	extern SDL_Surface* surface[HEIGHT_OF_MAP][WIDTH_OF_MAP];
	extern SDL_Texture* tile[HEIGHT_OF_MAP][WIDTH_OF_MAP];
	extern SDL_Rect tile_rect[HEIGHT_OF_MAP][WIDTH_OF_MAP];
	TTF_Font *font = TTF_OpenFont("impact.ttf", 46);
	SDL_Color yellow = { 255, 255, 0 };
	extern Game game;

	for (i = 0; i < HEIGHT_OF_MAP; i++) {
		for (j = 0; j < WIDTH_OF_MAP; j++) {
			if (map[i][j] == WALL)
				surface[i][j] = SDL_LoadBMP("Pictures/WallGreenEmpty.bmp");
			else if (map[i][j] == PAC_DOT)
				surface[i][j] = SDL_LoadBMP("Pictures/pacDot.bmp");
			else if (map[i][j] == POWER_PELLET)
				surface[i][j] = SDL_LoadBMP("Pictures/powerPellet1.bmp");
			else
				surface[i][j] = SDL_LoadBMP("Pictures/background.bmp");
			tile[i][j] = SDL_CreateTextureFromSurface(game.screen.renderer, surface[i][j]);
			tile_rect[i][j].x = j * game.screen.width / WIDTH_OF_MAP /3;
			tile_rect[i][j].y = i * game.screen.height / HEIGHT_OF_MAP/2;
			tile_rect[i][j].w = game.screen.width / WIDTH_OF_MAP/3;
			tile_rect[i][j].h = game.screen.height / HEIGHT_OF_MAP/2;
			SDL_RenderCopy(game.screen.renderer, tile[i][j], NULL, &tile_rect[i][j]);
		}
		SDL_RenderPresent(game.screen.renderer);
	}
	//pocetna pozicija pacmena
	surface[pacman.iPosition][pacman.jPosition] = SDL_LoadBMP("Pictures/pacmanR.bmp");
	//tile[pacman.iPosition][pacman.jPosition] = SDL_CreateTextureFromSurface(game.screen.renderer, surface[pacman.iPosition][pacman.jPosition]);
	//SDL_RenderCopy(game.screen.renderer, tile[pacman.iPosition][pacman.jPosition], NULL, &tile_rect[pacman.iPosition][pacman.jPosition]);
	SDL_RenderPresent(game.screen.renderer); //ako je unutar for-ova koji prave mapu, uspori znatno, zato je pomeren ovde
	return;
}

/*	
*	Unused function kept for historical purposes
*
*	Deletes pacStruct from the game screen,
*	draws background instead of pacStruct
*/
void deletePacmanGhost(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacStruct) {

	extern SDL_Surface* surface[HEIGHT_OF_MAP][WIDTH_OF_MAP];
	extern SDL_Texture* tile[HEIGHT_OF_MAP][WIDTH_OF_MAP];
	extern SDL_Rect tile_rect[HEIGHT_OF_MAP][WIDTH_OF_MAP];

	if (map[pacStruct.iPosition][pacStruct.jPosition] == WALL)
		surface[pacStruct.iPosition][pacStruct.jPosition] = SDL_LoadBMP("Pictures/WallGreenEmpty.bmp");
	else if (map[pacStruct.iPosition][pacStruct.jPosition] == PAC_DOT)
		surface[pacStruct.iPosition][pacStruct.jPosition] = SDL_LoadBMP("Pictures/pacDot.bmp");
	else if (map[pacStruct.iPosition][pacStruct.jPosition] == POWER_PELLET)
		surface[pacStruct.iPosition][pacStruct.jPosition] = SDL_LoadBMP("Pictures/powerPellet1.bmp");
	else
		surface[pacStruct.iPosition][pacStruct.jPosition] = SDL_LoadBMP("Pictures/background.bmp");

	pacStruct = getOldPacPosition(pacStruct);

	if (map[pacStruct.iPosition][pacStruct.jPosition] == WALL)
		surface[pacStruct.iPosition][pacStruct.jPosition] = SDL_LoadBMP("Pictures/WallGreenEmpty.bmp");
	else if (map[pacStruct.iPosition][pacStruct.jPosition] == PAC_DOT)
		surface[pacStruct.iPosition][pacStruct.jPosition] = SDL_LoadBMP("Pictures/pacDot.bmp");
	else if (map[pacStruct.iPosition][pacStruct.jPosition] == POWER_PELLET)
		surface[pacStruct.iPosition][pacStruct.jPosition] = SDL_LoadBMP("Pictures/powerPellet1.bmp");
	else
		surface[pacStruct.iPosition][pacStruct.jPosition] = SDL_LoadBMP("Pictures/background.bmp");

	SDL_RenderFillRect(game.screen.renderer, &tile_rect[pacStruct.iPosition][pacStruct.jPosition]);

	tile[pacStruct.iPosition][pacStruct.jPosition] = SDL_CreateTextureFromSurface(game.screen.renderer, surface[pacStruct.iPosition][pacStruct.jPosition]);

	SDL_RenderCopy(game.screen.renderer, tile[pacStruct.iPosition][pacStruct.jPosition], NULL, &tile_rect[pacStruct.iPosition][pacStruct.jPosition]);
	SDL_RenderPresent(game.screen.renderer);
	return;
}

/*
*	Draws pacman on it's initial position
*	on the game screen
*/
void drawInitPacman(PacStruct pacman) {
	surface[pacman.iPosition][pacman.jPosition] = SDL_LoadBMP("Pictures/pacmanR.bmp");
	return;
}

/*
*	Updates arguments map and pacman and ghosts
*	according to their values and values of
*	arguments delay and timer_tick
*/
void updateMap(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP], PacStruct pacman, PacStruct ghosts[NUMBER_OF_GHOSTS], int delay, int timer_tick) {

	extern SDL_Surface* surface[HEIGHT_OF_MAP][WIDTH_OF_MAP];
	extern SDL_Texture* tile[HEIGHT_OF_MAP][WIDTH_OF_MAP];
	extern SDL_Rect tile_rect[HEIGHT_OF_MAP][WIDTH_OF_MAP];
	TTF_Font *font = TTF_OpenFont("impact.ttf", 46);
	SDL_Color yellow = { 255, 255, 0 }, black = { 0, 0, 0 };
	extern Game game;

	PacStruct oldPosition = getOldPacPosition(pacman);
	if(timer_tick%4==0)
	SDL_RenderFillRect(game.screen.renderer, &tile_rect[oldPosition.iPosition][oldPosition.jPosition]);

	int i;
	PacStruct oldPositionGhost;
	for (i = 0; i < NUMBER_OF_GHOSTS; i++) {
		oldPositionGhost = getOldPacPosition(ghosts[i]);
		if (map[oldPositionGhost.iPosition][oldPositionGhost.jPosition] == PAC_DOT)
			surface[oldPositionGhost.iPosition][oldPositionGhost.jPosition] = SDL_LoadBMP("Pictures/pacDot.bmp");
		else if (map[oldPositionGhost.iPosition][oldPositionGhost.jPosition] == POWER_PELLET)
			surface[oldPositionGhost.iPosition][oldPositionGhost.jPosition] = SDL_LoadBMP("Pictures/powerPellet1.bmp");
		else if (map[oldPositionGhost.iPosition][oldPositionGhost.jPosition] == WALL)
			surface[oldPositionGhost.iPosition][oldPositionGhost.jPosition] = SDL_LoadBMP("Pictures/WallGreenEmpty.bmp");
		else
			surface[oldPositionGhost.iPosition][oldPositionGhost.jPosition] = SDL_LoadBMP("Pictures/background.bmp");

		tile[oldPositionGhost.iPosition][oldPositionGhost.jPosition] = SDL_CreateTextureFromSurface(game.screen.renderer, surface[oldPositionGhost.iPosition][oldPositionGhost.jPosition]);
		SDL_RenderCopy(game.screen.renderer, tile[oldPositionGhost.iPosition][oldPositionGhost.jPosition], NULL, &tile_rect[oldPositionGhost.iPosition][oldPositionGhost.jPosition]);
	}


	//SDL_RenderFillRect(game.screen.renderer, &tile_rect[pacman.iPosition][pacman.jPosition]);
	switch (pacman.direction) {
	case DIRECTION_NONE:
		break;
	case DIRECTION_UP:
		if (timer_tick % 2)
			surface[pacman.iPosition][pacman.jPosition] = SDL_LoadBMP("Pictures/pacmanU.bmp");
		else
			surface[pacman.iPosition][pacman.jPosition] = SDL_LoadBMP("Pictures/pacmanUC.bmp");
		break;
	case DIRECTION_RIGHT:
		if (timer_tick % 2)
			surface[pacman.iPosition][pacman.jPosition] = SDL_LoadBMP("Pictures/pacmanR.bmp");
		else
			surface[pacman.iPosition][pacman.jPosition] = SDL_LoadBMP("Pictures/pacmanRC.bmp");
		break;
	case DIRECTION_DOWN:
		if (timer_tick % 2)
			surface[pacman.iPosition][pacman.jPosition] = SDL_LoadBMP("Pictures/pacmanD.bmp");
		else
			surface[pacman.iPosition][pacman.jPosition] = SDL_LoadBMP("Pictures/pacmanDC.bmp");
		break;
	case DIRECTION_LEFT:
		if (timer_tick % 2)
			surface[pacman.iPosition][pacman.jPosition] = SDL_LoadBMP("Pictures/pacmanL.bmp");
		else
			surface[pacman.iPosition][pacman.jPosition] = SDL_LoadBMP("Pictures/pacmanLC.bmp");
		break;
	default:
		break;
	}

	surface[ghosts[0].iPosition][ghosts[0].jPosition] = SDL_LoadBMP("Pictures/Blinky.bmp");
	surface[ghosts[1].iPosition][ghosts[1].jPosition] = SDL_LoadBMP("Pictures/Inky.bmp");
	surface[ghosts[2].iPosition][ghosts[2].jPosition] = SDL_LoadBMP("Pictures/Pinky.bmp");
	surface[ghosts[3].iPosition][ghosts[3].jPosition] = SDL_LoadBMP("Pictures/Clyde.bmp");

	// TODO: uradi isto ovo za duhove

	tile[pacman.iPosition][pacman.jPosition] = SDL_CreateTextureFromSurface(game.screen.renderer, surface[pacman.iPosition][pacman.jPosition]);
	SDL_RenderCopy(game.screen.renderer, tile[pacman.iPosition][pacman.jPosition], NULL, &tile_rect[pacman.iPosition][pacman.jPosition]);
	
	for (i = 0; i < NUMBER_OF_GHOSTS; i++) {
		tile[ghosts[i].iPosition][ghosts[i].jPosition] = SDL_CreateTextureFromSurface(game.screen.renderer, surface[ghosts[i].iPosition][ghosts[i].jPosition]);
		SDL_RenderCopy(game.screen.renderer, tile[ghosts[i].iPosition][ghosts[i].jPosition], NULL, &tile_rect[ghosts[i].iPosition][ghosts[i].jPosition]);
	}
		

	SDL_RenderPresent(game.screen.renderer);
	SDL_Delay(delay);

	return;
}
