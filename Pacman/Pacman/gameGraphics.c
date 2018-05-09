#include "gameGraphics.h"
#include "gameMap.h"

SDL_Surface* surface[HEIGHT_OF_MAP][WIDTH_OF_MAP];
SDL_Texture *message[HEIGHT_OF_MAP][WIDTH_OF_MAP];
SDL_Rect Message_rect[HEIGHT_OF_MAP][WIDTH_OF_MAP];

void printInitMap(int map[HEIGHT_OF_MAP][WIDTH_OF_MAP]) {
	int i, j;

	extern SDL_Surface* surface[HEIGHT_OF_MAP][WIDTH_OF_MAP];
	extern SDL_Texture* message[HEIGHT_OF_MAP][WIDTH_OF_MAP];
	extern SDL_Rect Message_rect[HEIGHT_OF_MAP][WIDTH_OF_MAP];
	TTF_Font *font = TTF_OpenFont("impact.ttf", 46);
	SDL_Color yellow = { 255, 255, 0 };
	extern Game game;

	for (i = 0; i < HEIGHT_OF_MAP; i++) {
		for (j = 0; j < WIDTH_OF_MAP; j++) {
			if (map[i][j] == WALL)
				surface[i][j] = TTF_RenderText_Solid(font, "#", yellow);
			else if (map[i][j] == PAC_DOT)
				surface[i][j] = TTF_RenderText_Solid(font, ".", yellow);
			else if (map[i][j] == POWER_PELLET)
				surface[i][j] = TTF_RenderText_Solid(font, "o", yellow);
			else 
				surface[i][j] = TTF_RenderText_Solid(font, " ", yellow);

			message[i][j] = SDL_CreateTextureFromSurface(game.screen.renderer, surface[i][j]);
			SDL_FreeSurface(surface[i][j]);
			Message_rect[i][j].x = j * game.screen.width / WIDTH_OF_MAP /3;
			Message_rect[i][j].y = i * game.screen.height / HEIGHT_OF_MAP/2;
			Message_rect[i][j].w = game.screen.width / WIDTH_OF_MAP/3;
			Message_rect[i][j].h = game.screen.height / HEIGHT_OF_MAP/2;

			SDL_RenderCopy(game.screen.renderer, message[i][j], NULL, &Message_rect[i][j]);
			SDL_RenderPresent(game.screen.renderer);
		}
	}
	return;
}

void updateMap(int map[HEIGHT_OF_MAP][HEIGHT_OF_MAP], PacStruct pacman, PacStruct ghosts[NUMBER_OF_GHOSTS]) {

	extern SDL_Surface* surface[HEIGHT_OF_MAP][WIDTH_OF_MAP];
	extern SDL_Texture* message[HEIGHT_OF_MAP][WIDTH_OF_MAP];
	extern SDL_Rect Message_rect[HEIGHT_OF_MAP][WIDTH_OF_MAP];
	TTF_Font *font = TTF_OpenFont("impact.ttf", 46);
	SDL_Color yellow = { 255, 255, 0 };
	extern Game game;

	surface[pacman.iPosition][pacman.jPosition] = TTF_RenderText_Solid(font, "<", yellow);
	// TODO: update-uj staro i novo mesto pacmana

	// TODO: uradi isto ovo za duhove

	message[pacman.iPosition][pacman.jPosition] = SDL_CreateTextureFromSurface(game.screen.renderer, surface[pacman.iPosition][pacman.jPosition]);
	SDL_FreeSurface(surface[pacman.iPosition][pacman.jPosition]);

	SDL_RenderCopy(game.screen.renderer, message[pacman.iPosition][pacman.jPosition], NULL, &Message_rect[pacman.iPosition][pacman.jPosition]);
	SDL_RenderPresent(game.screen.renderer);

	return;
}
