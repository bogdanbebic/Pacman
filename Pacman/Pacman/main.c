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

	PlaySound(TEXT("Music/UzickoKolo"), NULL, SND_ASYNC); // za potrebe proslave

	game.init();

	enum MenuOptions menuOption = 0;	// Ovo je za izbor u meniju

	SDL_Event event;
	while (game.isRunning) {
		while (SDL_PollEvent(&event)) {

			if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_UP:
					// TODO: implement
					menuOption = menuOption ? menuOption - 1 : numberOfMenuOptions - 1;
					break;
				case SDLK_DOWN:
					// TODO: implement
					menuOption = (menuOption + 1) % numberOfMenuOptions;
					break;
				case SDLK_RIGHT:
					// printf("Menu option: %d\n", menuOption);	// za potrebe debagovanja
					if (menuOption == quit) {
						game.isRunning = SDL_FALSE;
					}

					// TODO: implement
					break;
				default:
					break;
				}
			}

			/* videcemo da li cemo i ovo da implmentiramo */
			/*else if (event.type == SDL_MOUSEBUTTONDOWN) {		// !!!!! ovo je za mis, NE DIRAJ, NE BRISI !!!!!
				int x, y;

				SDL_GetMouseState(&x, &y);
				printf("%s button mouse clicked at: (%d,%d)\n",
					(event.button.button == SDL_BUTTON_LEFT) ? "left" : "right",
					x, y);
			}*/

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
