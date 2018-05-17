#include <stdio.h>

#include <Windows.h>
#pragma comment(lib, "winmm.lib")

#include <SDL.h>
#include <SDL_ttf.h>

#include "graphicsMenu.h"
#include "game.h"

//extern map[29][28];

SDL_Event event;

int main(int argc, char *argv[]) {

	extern Game game;
	game.init = gameInit;
	game.quit = gameQuit;
	getScreenResolution(&game.screen.width, &game.screen.height);
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	/*int i, j;
	for (i = 0; i < 29; i++) {
		for (j = 0; j < 28; j++) {
			printf("%3d ", map[i][j]);
		}
		putchar('\n');
	}*/

	PlaySound(TEXT("Music/UzickoKolo"), NULL, SND_ASYNC); // za potrebe proslave

	enum ActiveScreen {isMenu, isDemo, isNew, isContinue, isHighscore, isSettings, isCredits, isQuit, numberOfScreens};

	enum ActiveScreen activeScreen = isMenu;

	game.init();

	int isGameCreated = 0;

	enum MenuOptions menuOption = 1;	// Ovo je za izbor u meniju
	//SDL_Event event;

	while (game.isRunning) {	
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {

				case SDLK_ESCAPE:
					if (activeScreen != isMenu) {
						activeScreen = isMenu;
					}
					break;

				case SDLK_UP:
					if (activeScreen == isMenu) {
						menuOption = menuOption ? menuOption - 1 : numberOfMenuOptions - 1;
					}
					break;

				case SDLK_DOWN:
					if (activeScreen == isMenu) {
						menuOption = (menuOption + 1) % numberOfMenuOptions;
					}
					break;

				case SDLK_RETURN: case SDLK_RIGHT:
					// printf("Menu option: %d\n", menuOption);	// za potrebe debagovanja
					if (activeScreen == isMenu) {
						activeScreen = menuOption + 1;
						//switch (menuOption) {
						//case newGame:
						//	isGameCreated = 1;
						//	//TODO: implement window for new game
						//	break;
						//case continueGame:
						//	if (isGameCreated) {
						//		//TODO: implement game continuation
						//	}
						//	break;
						//case highscore:
						//	//TODO: implement highscore window
						//	break;
						//case settings:
						//	//TODO: implement settings window
						//	break;
						//case quitGame:
						//	game.isRunning = SDL_FALSE;
						//	// TODO: implement
						//	break;
						//}
					}
					break;
				}
				break;	// !!!!! NE DIRAJ, OVO SPRECAVA GASENJE PROGRAMA !!!!!

			/* videcemo da li cemo i ovo da implmentiramo */
			/* case SDL_MOUSEBUTTONDOWN: 		// !!!!! ovo je za mis, NE DIRAJ, NE BRISI !!!!!
					int x, y;
					SDL_GetMouseState(&x, &y);
					printf("%s button mouse clicked at: (%d,%d)\n",
						(event.button.button == SDL_BUTTON_LEFT) ? "left" : "right", x, y);
					break;*/

			case SDL_QUIT:
				game.isRunning = SDL_FALSE;
				break;
			}
		
			switch (activeScreen) {
			case isMenu:
				printMenu(menuOption);
				break;
			case isDemo:
				SDL_RenderClear(game.screen.renderer);
				isGameCreated = 1;
				playGame(DEMO_GAME, HARD);	// TODO: difficulty
				SDL_RenderClear(game.screen.renderer);
				activeScreen = isMenu;
				if (game.isRunning)
					printMenu(menuOption);
				break;
			case isNew:
				SDL_RenderClear(game.screen.renderer);
				isGameCreated = 1;
				playGame(NEW_GAME, MEDIUM);	// TODO: difficulty
				SDL_RenderClear(game.screen.renderer);
				activeScreen = isMenu;
				if (game.isRunning)
					printMenu(menuOption);
				break;
			case isContinue:
				if (isGameCreated) {
					SDL_RenderClear(game.screen.renderer);
					isGameCreated = 1;
					playGame(CONTINUE_GAME, HARD);	// TODO: difficulty
					SDL_RenderClear(game.screen.renderer);
					activeScreen = isMenu;
					if (game.isRunning)
						printMenu(menuOption);
				}
				else {
					activeScreen = isMenu;
				}
				break;
			case isHighscore:
				// TODO: implement
				break;
			case isSettings:
				// TODO: implement
				break;
			case isCredits:
				// TODO: implement
				break;
			case isQuit:
				game.isRunning = SDL_FALSE;
				break;
			default:
				break;
			}
		}
	}

	game.quit();

	return 0;
}
