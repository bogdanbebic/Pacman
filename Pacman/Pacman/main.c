#include <stdio.h>
#include <Windows.h>
#pragma comment(lib, "winmm.lib")
#include <SDL.h>
#include <SDL_ttf.h>
#include "graphicsMenu.h"
#include "game.h"
#include "pauseMenuGraphics.h"
#include "saveGame.h"
#include "highscores.h"

//extern map[29][28];

SDL_Event event;

extern SaveGame saveGame;

int main(int argc, char *argv[]) {
	extern SaveGame saveGame;
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

	//PlaySound(TEXT("Music/UzickoKolo"), NULL, SND_ASYNC); // za potrebe proslave

	enum ActiveScreen {isMenu, isDemo, isNew, isContinue, isHighscore, isSettings, isCredits, isQuit, numberOfScreens};
	enum ActiveScreen activeScreen = isMenu;
	game.init();
	SDL_Texture * menuTextureWhite[numberOfMenuOptions], *menuTextureYellow[numberOfMenuOptions], *pacmanTexture;
	initTexturesForMenu(menuTextureWhite, menuTextureYellow, &pacmanTexture);

	int isGameCreated = 0;
	enum MenuOptions menuOption = 1;	// Ovo je za izbor u meniju
	enum DifficulySpeed difficulty = MEDIUM;
	//SDL_Event event;

	Highscore newHighscore;

	// TODO: READ HIGHSCORES FROM FILE, NOT ALWAYS LIKE THIS
	makeGenericHighscores();

	PlaySound(TEXT("Music/PacmanFever"), NULL, SND_ASYNC);

	while (game.isRunning) {	
		printMenu(menuOption, menuTextureWhite, menuTextureYellow, pacmanTexture);
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
				printMenu(menuOption, menuTextureWhite, menuTextureYellow, pacmanTexture);
				break;
			case isDemo:
				SDL_RenderClear(game.screen.renderer);

				// OVO PROMENITI AKO NE ZELIMO DA MOZE IGRAC DA NASTAVI DEMO
				isGameCreated = 1;

				playGame(DEMO_GAME, difficulty);	
				SDL_RenderClear(game.screen.renderer);
				activeScreen = isMenu;
				if (game.isRunning) {
					createHeading();
					printMenu(menuOption, menuTextureWhite, menuTextureYellow, pacmanTexture);
				}
				PlaySound(TEXT("Music/PacmanFever"), NULL, SND_ASYNC);
				break;
			case isNew:
				SDL_RenderClear(game.screen.renderer);
				isGameCreated = 1;
				newHighscore = playGame(NEW_GAME, difficulty);	
				SDL_RenderClear(game.screen.renderer);
				activeScreen = isMenu;
				if (game.isRunning) {
					createHeading();
					printMenu(menuOption, menuTextureWhite, menuTextureYellow, pacmanTexture);
				}
				PlaySound(TEXT("Music/PacmanFever"), NULL, SND_ASYNC);
				break;
			case isContinue:
				if (isGameCreated && saveGame.level != -1) {
					SDL_RenderClear(game.screen.renderer);
					isGameCreated = 1;
					newHighscore = playGame(CONTINUE_GAME, difficulty);
					SDL_RenderClear(game.screen.renderer);
					activeScreen = isMenu;
					if (game.isRunning) {
						createHeading();
						printMenu(menuOption, menuTextureWhite, menuTextureYellow, pacmanTexture);
					}
					PlaySound(TEXT("Music/PacmanFever"), NULL, SND_ASYNC);
				}
				else {
					activeScreen = isMenu;
				}
				break;
			case isHighscore:
				// TODO: implement
				break;
			case isSettings:
				SDL_RenderClear(game.screen.renderer);
				activateSettings(&difficulty);
				SDL_RenderClear(game.screen.renderer);
				activeScreen = isMenu;
				if (game.isRunning) {
					createHeading();
					printMenu(menuOption, menuTextureWhite, menuTextureYellow, pacmanTexture);
				}
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
			if (newHighscore.name[0] != '\0') {
				updateHighscores(newHighscore);
			}
		}
	}

	game.quit();

	return 0;
}
