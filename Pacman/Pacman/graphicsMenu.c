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
	SDL_Color white = { 255, 255, 255 };
	extern TTF_Font* font;

	SDL_Surface* surface = TTF_RenderText_Solid(font, "New game", white);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(game.screen.renderer, surface);

	SDL_Rect Message_rect;
	Message_rect.x = game.screen.width / 12;
	Message_rect.y = game.screen.height / 16;
	Message_rect.w = game.screen.width / 6;
	Message_rect.h = game.screen.height / 12;
	SDL_RenderCopy(game.screen.renderer, Message, NULL, &Message_rect);

	SDL_RenderPresent(game.screen.renderer);
	return;
}
