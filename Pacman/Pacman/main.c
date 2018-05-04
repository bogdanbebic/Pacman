#include <stdio.h>

#include <Windows.h>
#pragma comment(lib, "winmm.lib")

#include <SDL.h>
#include <SDL_ttf.h>

#include "graphicsMenu.h"


int main(int argc, char *argv[]) {

	extern Game game;
	

	game.init = gameInit;
	game.quit = gameQuit;
	getScreenResolution(&game.screen.width, &game.screen.height);
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	//PlaySound(TEXT("Music/UzickoKolo"), NULL, SND_ASYNC); // za potrebe proslave

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

		printMenu();
	}

	game.quit();

	return 0;
}
