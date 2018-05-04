#include "graphicsMenu.h"


void getScreenResolution(int *width, int *height) {
	*width = GetSystemMetrics(SM_CXSCREEN);
	*height = GetSystemMetrics(SM_CYSCREEN);
	return;
}

void gameInit() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL error: %s\n", SDL_GetError());
		exit(-1);
	}
	TTF_Init();


	SDL_Color white = { 255, 255, 255 };
	extern TTF_Font* font;

	font = TTF_OpenFont("arial.ttf", 24);

	extern Game game;
	unsigned int width = game.screen.width / 3;
	unsigned int height = game.screen.height / 2;
	const char* name = SCREEN_NAME;

	game.screen.window = SDL_CreateWindow(name,	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,	width, height, 0);
	game.screen.renderer = SDL_CreateRenderer(game.screen.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	game.isRunning = SDL_TRUE;
	return;
}

void gameQuit() {
	SDL_DestroyRenderer(game.screen.renderer);
	SDL_DestroyWindow(game.screen.window);

	game.screen.window = NULL;
	game.screen.renderer = NULL;
	game.isRunning = SDL_FALSE;

	SDL_Quit();
	return;
}

void printMenu() {

	/* !!!!! TODO: implementiraj crtanje pacmana !!!!! */

	SDL_Color white = { 255, 255, 255 };
	extern TTF_Font* font;

	SDL_Surface* surface[numberOfMenuOptions];
	SDL_Texture* Message[numberOfMenuOptions];
	SDL_Rect Message_rect[numberOfMenuOptions];

	enum MenuOptions menuOption;

	
	for (menuOption = 0; menuOption < numberOfMenuOptions; menuOption++) {

		switch (menuOption) {
		case newGame:
			surface[menuOption] = TTF_RenderText_Solid(font, "NEW GAME", white);
			break;
		case continueGame:
			surface[menuOption] = TTF_RenderText_Solid(font, "CONTINUE", white);
			break;
		case highscore:
			surface[menuOption] = TTF_RenderText_Solid(font, "HIGHSCORE", white);
			break;
		case settings:
			surface[menuOption] = TTF_RenderText_Solid(font, "SETTINGS", white);
			break;
		case credits:
			surface[menuOption] = TTF_RenderText_Solid(font, "CREDITS", white);
			break;
		case quit:
			surface[menuOption] = TTF_RenderText_Solid(font, "QUIT GAME", white);
			break;
		default:
			break;
		}
		
		Message[menuOption] = SDL_CreateTextureFromSurface(game.screen.renderer, surface[menuOption]);
		Message_rect[menuOption].x = game.screen.width / 12;
		Message_rect[menuOption].y = (menuOption + 1) * (game.screen.height / 16);	// OVDE MENJAS !!!!!!!!!!
		Message_rect[menuOption].w = game.screen.width / 6;
		Message_rect[menuOption].h = game.screen.height / 24;


		SDL_RenderCopy(game.screen.renderer, Message[menuOption], NULL, &Message_rect[menuOption]);
	}
	


	SDL_RenderPresent(game.screen.renderer);
	return;
}
