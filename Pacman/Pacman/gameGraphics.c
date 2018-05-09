#include "gameGraphics.h"
#include "gameMap.h"
#include "pacStruct.h"

static SDL_Surface* surface[HEIGHT_OF_MAP][WIDTH_OF_MAP];
static SDL_Texture *tile[HEIGHT_OF_MAP][WIDTH_OF_MAP];
static SDL_Rect tile_rect[HEIGHT_OF_MAP][WIDTH_OF_MAP];

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
				surface[i][j] = SDL_LoadBMP("Pictures/weed1.bmp");
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
			SDL_RenderPresent(game.screen.renderer);
		}
	}
	surface[pacman.iPosition][pacman.jPosition] = SDL_LoadBMP("Pictures/pacmanR.bmp");
	return;
}

void updateMap(int map[HEIGHT_OF_MAP][HEIGHT_OF_MAP], PacStruct pacman, PacStruct ghosts[NUMBER_OF_GHOSTS]) {

	extern SDL_Surface* surface[HEIGHT_OF_MAP][WIDTH_OF_MAP];
	extern SDL_Texture* tile[HEIGHT_OF_MAP][WIDTH_OF_MAP];
	extern SDL_Rect tile_rect[HEIGHT_OF_MAP][WIDTH_OF_MAP];
	TTF_Font *font = TTF_OpenFont("impact.ttf", 46);
	SDL_Color yellow = { 255, 255, 0 }, black = { 0, 0, 0 };
	extern Game game;

	// TODO: update-uj staro mesto pacmana
	PacStruct oldPosition = getOldPacPosition(pacman);
	SDL_RenderFillRect(game.screen.renderer, &tile_rect[oldPosition.iPosition][oldPosition.jPosition]);

	SDL_RenderFillRect(game.screen.renderer, &tile_rect[pacman.iPosition][pacman.jPosition]);

	switch (pacman.direction) {
	case DIRECTION_NONE:
		break;
	case DIRECTION_UP:
		surface[pacman.iPosition][pacman.jPosition] = SDL_LoadBMP("Pictures/pacmanU.bmp");
		break;
	case DIRECTION_RIGHT:
		surface[pacman.iPosition][pacman.jPosition] = SDL_LoadBMP("Pictures/pacmanR.bmp");
		break;
	case DIRECTION_DOWN:
		surface[pacman.iPosition][pacman.jPosition] = SDL_LoadBMP("Pictures/pacmanD.bmp");
		break;
	case DIRECTION_LEFT:
		surface[pacman.iPosition][pacman.jPosition] = SDL_LoadBMP("Pictures/pacmanL.bmp");
		break;
	default:
		break;
	}

	// TODO: uradi isto ovo za duhove

	tile[pacman.iPosition][pacman.jPosition] = SDL_CreateTextureFromSurface(game.screen.renderer, surface[pacman.iPosition][pacman.jPosition]);

	SDL_RenderCopy(game.screen.renderer, tile[pacman.iPosition][pacman.jPosition], NULL, &tile_rect[pacman.iPosition][pacman.jPosition]);
	SDL_RenderPresent(game.screen.renderer);
	SDL_Delay(250);
	return;
}
