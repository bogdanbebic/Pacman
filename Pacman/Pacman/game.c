#include "game.h"
#include "testMap.h"

void wallCheckAndMove(int map[HEIGHT_OF_MAP][HEIGHT_OF_MAP], PacStruct *pacStruct) {
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
		if (map[pacStruct->iPosition][pacStruct->jPosition + 1] == WALL) {
			pacStruct->direction = DIRECTION_NONE;
		}
		else {
			pacStruct->jPosition++;
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
		if (map[pacStruct->iPosition][pacStruct->jPosition - 1] == WALL) {
			pacStruct->direction = DIRECTION_NONE;
		}
		else {
			pacStruct->jPosition--;
		}
		break;
	default:
		break;
	}
	return;
}

extern SDL_Event event;

void playNewGame() {
	extern int testMap1[HEIGHT_OF_MAP][WIDTH_OF_MAP];	// Za potrebe testiranja
	/* Promeniti mapu koja se koristi */
	extern int pacDotCountTestMap1;
	SDL_bool isLevelRunning = SDL_TRUE;

	PacStruct pacman;
	/*
	*	Ove vrednosti ispod su proizvoljne
	*	za	potrebe testiranja, kasnije ih
	*	treba promeniti u nesto smisleno
	*/
	pacman.direction = DIRECTION_NONE;	
	pacman.iPosition = HEIGHT_OF_MAP / 2;
	pacman.jPosition = WIDTH_OF_MAP / 2;



	printInitMap(testMap2, pacman);

	while (isLevelRunning) {


		while (SDL_PollEvent(&event) && isLevelRunning) {
			switch (event.type) {
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {

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
				break;
			case SDL_QUIT:
				isLevelRunning = SDL_FALSE;
				game.isRunning = SDL_FALSE;
				break;
			}
		}
		wallCheckAndMove(testMap2, &pacman);
		PacStruct ghosts[4];
		// TODO: odredjivanje novih pozicija duhova
		// TODO: wallCheckAndMove za duhove

		// TODO: poziv funkcije za grafiku -> iscrtavanje nove mape
		updateMap(testMap2, pacman, ghosts);

		// TODO: provera -> pacman i duh na istom polju
		// TODO: lives count provera

		// TODO: broj preostalih PAC_DOT-ova na mapi

		// TODO: azuriranje mape, da li je Pacman pojeo nesto

	}

	// TODO: ispis endgame ekrana -> pobeda ili poraz

	return;
}
