#include "graphicsMenu.h"

/*
*	Gets the current hardware screen resolution
*	using arguments width and height
*/
void getScreenResolution(int *width, int *height) {
	*width = GetSystemMetrics(SM_CXSCREEN);
	*height = GetSystemMetrics(SM_CYSCREEN);
	return;
}

/*
*	Initializes the game and everything needed for it
*/
void gameInit() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL error: %s\n", SDL_GetError());
		exit(-1);
	}

	TTF_Init();

	extern TTF_Font* font;

	font = TTF_OpenFont("impact.ttf", 46);

	extern Game game;
	unsigned int width = game.screen.width / 3;
	unsigned int height = game.screen.height / 2 + 2 * game.screen.height / HEIGHT_OF_MAP;
	const char* name = SCREEN_NAME;

	game.screen.window = SDL_CreateWindow(name,	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
	game.screen.renderer = SDL_CreateRenderer(game.screen.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	game.isRunning = SDL_TRUE;
	return;
}

/*
*	Quits the game and destroys the
*	renderers and windows
*/
void gameQuit() {
	extern SDL_Texture* Message[numberOfMenuOptions];
	enum MenuOptions menuOption;
	for (menuOption = 0; menuOption < numberOfMenuOptions; menuOption++) { // za brisanje teksture i rendera
		SDL_DestroyTexture(Message[menuOption]);
	}
	SDL_DestroyRenderer(game.screen.renderer);
	SDL_DestroyWindow(game.screen.window);

	game.screen.window = NULL;
	game.screen.renderer = NULL;
	game.isRunning = SDL_FALSE;

	SDL_Quit();
	return;
}

/*
*	Prints the menu on the game screen
*	using the argument enum menuOptions currentMenuOption
*	for printing all of the menu options
*/
void printMenu(enum menuOptions currentMenuOption) {

	/* !!!!! TODO: implementiraj crtanje pacmana !!!!! */
	/*crtanje ispred selektovane stavke menija*/

	SDL_Color white = { 255, 255, 255 };
	SDL_Color yellow = { 255, 255, 0 };
	extern TTF_Font* font;

	SDL_Surface* surface[numberOfMenuOptions], * PacmanSurface;
	extern SDL_Texture* Message[numberOfMenuOptions];
	SDL_Texture * PacmanTexture;
	SDL_Rect Message_rect[numberOfMenuOptions], PacmanRect;

	enum MenuOptions menuOption;

	
	for (menuOption = 0; menuOption < numberOfMenuOptions; menuOption++) {

		switch (menuOption) {
		case demoGame:
			if (currentMenuOption == menuOption) {
				surface[menuOption] = TTF_RenderText_Solid(font, "DEMO GAME", yellow);
			}
			else {
				surface[menuOption] = TTF_RenderText_Solid(font, "DEMO GAME", white);
			}
			break;
		case newGame:
			if (currentMenuOption == menuOption) {
				surface[menuOption] = TTF_RenderText_Solid(font, "NEW GAME", yellow);
			}
			else {
				surface[menuOption] = TTF_RenderText_Solid(font, "NEW GAME", white);
			}
			break;
		case continueGame:
			if (currentMenuOption == menuOption) {
				surface[menuOption] = TTF_RenderText_Solid(font, "CONTINUE", yellow);
			}
			else {
				surface[menuOption] = TTF_RenderText_Solid(font, "CONTINUE", white);
			}
			break;
		case highscore:
			if (currentMenuOption == menuOption) {
				surface[menuOption] = TTF_RenderText_Solid(font, "HIGHSCORE", yellow);
			}
			else {
				surface[menuOption] = TTF_RenderText_Solid(font, "HIGHSCORE", white);
			}
			break;
		case settings:
			if (currentMenuOption == menuOption) {
				surface[menuOption] = TTF_RenderText_Solid(font, "SETTINGS", yellow);
			}
			else {
				surface[menuOption] = TTF_RenderText_Solid(font, "SETTINGS", white);
			}
			break;
		case credits:
			if (currentMenuOption == menuOption) {
				surface[menuOption] = TTF_RenderText_Solid(font, "CREDITS", yellow);
			}
			else {
				surface[menuOption] = TTF_RenderText_Solid(font, "CREDITS", white);
			}
			break;
		case quitGame:
			if (currentMenuOption == menuOption) {
				surface[menuOption] = TTF_RenderText_Solid(font, "QUIT GAME", yellow);
			}
			else {
				surface[menuOption] = TTF_RenderText_Solid(font, "QUIT GAME", white);
			}
			break;
		default:
			break;
		}
		
		Message[menuOption] = SDL_CreateTextureFromSurface(game.screen.renderer, surface[menuOption]);
		SDL_FreeSurface(surface[menuOption]);

		//Pacman koji stoji ispred selektovane stavke u meniju
		PacmanRect.x = game.screen.width / 24;
		PacmanRect.y = (5 + 3 * menuOption) * (game.screen.height / 48);
		PacmanRect.w = game.screen.width / 30;
		PacmanRect.h = game.screen.height / 24;
		if (menuOption == currentMenuOption) {
			PacmanSurface = SDL_LoadBMP("Pictures/pacmanR.bmp");
			PacmanTexture = SDL_CreateTextureFromSurface(game.screen.renderer, PacmanSurface);
			SDL_FreeSurface(PacmanSurface);
			SDL_RenderCopy(game.screen.renderer, PacmanTexture, NULL, &PacmanRect);
		}
		else {
			SDL_RenderFillRect(game.screen.renderer, &PacmanRect);
		}

		Message_rect[menuOption].x = game.screen.width / 12;
		Message_rect[menuOption].y = (5 + 3 * menuOption) * (game.screen.height / 48);	// OVDE MENJAS !!!!!!!!!!
		Message_rect[menuOption].w = game.screen.width / 6;
		Message_rect[menuOption].h = game.screen.height / 24;


		SDL_RenderCopy(game.screen.renderer, Message[menuOption], NULL, &Message_rect[menuOption]);
		
	}
	SDL_RenderPresent(game.screen.renderer);
	return;
}
