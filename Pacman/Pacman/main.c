#include <stdio.h>

#include <Windows.h>
#pragma comment(lib, "winmm.lib")

#include <SDL.h>

#include "graphicsMenu.h"

int main(int argc, char *argv[]) {

	extern Game game;
	game.init = gameInit;
	game.quit = gameQuit;
	getScreenResolution(&game.screen.width, &game.screen.height);
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	PlaySound(TEXT("Music/UzickoKolo"), NULL, SND_ASYNC);

	/*
	int width = 860, height = 640;
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	printf("Hello, World!\n");
	PlaySound(TEXT("Music/ImperialMarch"), NULL, SND_ASYNC);

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("SDL_Init failed: %s\n", SDL_GetError());
		return 0;
	}

	window = SDL_CreateWindow("Hello World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);

	if (window == NULL) return 0;

	SDL_Delay(5000);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_Quit();
	*/

	game.init();
	SDL_Event event;
	while (game.isRunning) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				game.isRunning = SDL_FALSE;
				break;
			}
		}

		SDL_RenderClear(game.screen.renderer);
		SDL_RenderPresent(game.screen.renderer);
	}

	game.quit();

	return 0;
}
