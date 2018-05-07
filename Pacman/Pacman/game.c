#include "game.h"
#include "gameMap.h"

void playNewGame() {
	extern int testMap1[HEIGHT_OF_MAP][WIDTH_OF_MAP];	// Za potrebe testiranja
	/* Promeniti mapu koja se koristi */
	extern int pacDotCountTestMap1;
	SDL_bool isLevelRunning = SDL_TRUE;
	SDL_Event newGameEvent;

	PacStruct pacman;
	/*
	*	Ove vrednosti ispod su proizvoljne
	*	za	potrebe testiranja, kasnije ih
	*	treba promeniti u nesto smisleno
	*/
	pacman.direction = DIRECTION_NONE;	
	pacman.iPosition = HEIGHT_OF_MAP / 2;
	pacman.jPosition = WIDTH_OF_MAP / 2;

	while (game.isRunning) {

		switch (pacman.direction) {
		case DIRECTION_UP:
			if (pacman.iPosition - 1 == WALL) {
				pacman.direction = DIRECTION_NONE;
			}
			else {
				pacman.iPosition--;
			}
			break;
		case DIRECTION_RIGHT:
			if (pacman.jPosition + 1 == WALL) {
				pacman.direction = DIRECTION_NONE;
			}
			else {
				pacman.jPosition++;
			}
			break;
		case DIRECTION_DOWN:
			if (pacman.iPosition + 1 == WALL) {
				pacman.direction = DIRECTION_NONE;
			}
			else {
				pacman.iPosition++;
			}
			break;
		case DIRECTION_LEFT:
			if (pacman.jPosition - 1 == WALL) {
				pacman.direction = DIRECTION_NONE;
			}
			else {
				pacman.jPosition--;
			}
			break;
		default:
			break;
		}

		// TODO: odredjivanje novih pozicija duhova

		// TODO: poziv funkcije za grafiku -> iscrtavanje mape 

		// TODO: provera -> pacman i duh na istom polju

		// TODO: broj preostalih PAC_DOT-ova na mapi

		// TODO: ovde mozda treba i da se delay-uje ekran i potez zbog ljudskog igranja i gledanja

		while (SDL_PollEvent(&newGameEvent)) {
			switch (newGameEvent.type) {
			case SDL_KEYDOWN:
				switch (newGameEvent.key.keysym.sym) {

				case SDLK_ESCAPE:
					isLevelRunning = SDL_FALSE;
					break;

				case SDLK_UP:
					pacman.direction = DIRECTION_UP;
					break;

				case SDLK_DOWN:
					pacman.direction = DIRECTION_DOWN;
					break;

				case SDLK_RIGHT:
					pacman.direction = DIRECTION_RIGHT;
					break;

				case SDLK_LEFT:
					pacman.direction = DIRECTION_LEFT;
					break;

				default:
					break;
				}
			}
		}
	}

	// TODO: ispis endgame ekrana -> pobeda ili poraz

	return;
}
