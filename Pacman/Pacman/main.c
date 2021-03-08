#include <stdio.h>
#ifdef _WIN32
#include <Windows.h>
#pragma comment(lib, "winmm.lib")
#endif
#include <SDL.h>
#include <SDL_ttf.h>
#include "graphicsMenu.h"
#include "game.h"
#include "pauseMenuGraphics.h"
#include "saveGame.h"
#include "highscores.h"

/*! \file main.c
 *	\brief Contains the main program from which the whole game runs
 */


/*!
 *	\brief Global variable used for getting user keyboard input
 */
SDL_Event event;
extern SaveGame saveGame;

/*!
 *	\brief main
 */
int main(int argc, char *argv[]) {
	extern SaveGame saveGame;
	extern Game game;
	game.init = gameInit;
	game.quit = gameQuit;
	getScreenResolution(&game.screen.width, &game.screen.height);
#ifdef _WIN32
	ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif

	//PlaySound(TEXT("Music/UzickoKolo"), NULL, SND_ASYNC); // za potrebe proslave

	enum ActiveScreen {isMenu, isDemo, isNew, isContinue, isHighscore, isSettings, isCredits, isQuit, numberOfScreens};
	enum ActiveScreen activeScreen = isMenu;
	game.init();
	SDL_Texture * menuTextureWhite[numberOfMenuOptions], *menuTextureYellow[numberOfMenuOptions], *pacmanTexture;
	createHeading();
	initTexturesForMenu(menuTextureWhite, menuTextureYellow, &pacmanTexture);

	int isGameCreated = 0;
	enum MenuOptions menuOption = 1;	// Ovo je za izbor u meniju
	enum DifficulySpeed difficulty = MEDIUM;
	enum YesNo isMusicOn = yes;

	Highscore newHighscore;

	newHighscore.name[0] = '\0';
	
	// TODO: READ HIGHSCORES FROM FILE, NOT ALWAYS LIKE THIS
	readHighscoresFromFiles();

#ifdef _WIN32
	PlaySound(TEXT("Music/PacmanFever"), NULL, SND_LOOP | SND_ASYNC);
#endif

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
					if (activeScreen == isMenu) {
						activeScreen = menuOption + 1;
					}
					break;
				}
				break;	// !!!!! NE DIRAJ, OVO SPRECAVA GASENJE PROGRAMA !!!!!

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

				playGame(DEMO_GAME, difficulty, isMusicOn);
				SDL_RenderClear(game.screen.renderer);
				activeScreen = isMenu;
				if (game.isRunning) {
					createHeading();
					printMenu(menuOption, menuTextureWhite, menuTextureYellow, pacmanTexture);
				}
#ifdef _WIN32
				if (isMusicOn)
					PlaySound(TEXT("Music/PacmanFever"), NULL, SND_LOOP | SND_ASYNC);
#endif
				break;
			case isNew:
				SDL_RenderClear(game.screen.renderer);
				isGameCreated = 1;
				newHighscore = playGame(NEW_GAME, difficulty, isMusicOn);
				SDL_RenderClear(game.screen.renderer);
				activeScreen = isMenu;
				if (game.isRunning) {
					createHeading();
					printMenu(menuOption, menuTextureWhite, menuTextureYellow, pacmanTexture);
				}
#ifdef _WIN32
				if (isMusicOn)
					PlaySound(TEXT("Music/PacmanFever"), NULL, SND_LOOP | SND_ASYNC);
#endif
				break;
			case isContinue:
				if (isGameCreated && saveGame.level != -1) {
					SDL_RenderClear(game.screen.renderer);
					isGameCreated = 1;
					newHighscore = playGame(CONTINUE_GAME, difficulty, isMusicOn);
					SDL_RenderClear(game.screen.renderer);
					activeScreen = isMenu;
					if (game.isRunning) {
						createHeading();
						printMenu(menuOption, menuTextureWhite, menuTextureYellow, pacmanTexture);
					}
#ifdef _WIN32
					if (isMusicOn)
						PlaySound(TEXT("Music/PacmanFever"), NULL, SND_LOOP | SND_ASYNC);
#endif
				}
				else {
					activeScreen = isMenu;
				}
				break;
			case isHighscore:
				SDL_RenderClear(game.screen.renderer);
				printHighScore();
				SDL_RenderClear(game.screen.renderer);
				activeScreen = isMenu;
				if (game.isRunning) {
					createHeading();
					printMenu(menuOption, menuTextureWhite, menuTextureYellow, pacmanTexture);
				}
				break;
				break;
			case isSettings:
				SDL_RenderClear(game.screen.renderer);
				activateSettings(&difficulty, &isMusicOn);
				SDL_RenderClear(game.screen.renderer);
				activeScreen = isMenu;
				if (game.isRunning) {
					createHeading();
					printMenu(menuOption, menuTextureWhite, menuTextureYellow, pacmanTexture);
				}
				break;
			case isCredits:
				SDL_RenderClear(game.screen.renderer);
#ifdef _WIN32
				if (isMusicOn)
					PlaySound(TEXT("Music/BombeDevedesetih"), NULL, SND_LOOP | SND_ASYNC);
#endif
				printCredits();
				SDL_RenderClear(game.screen.renderer);
				activeScreen = isMenu;
				if (game.isRunning) {
					createHeading();
					printMenu(menuOption, menuTextureWhite, menuTextureYellow, pacmanTexture);
				}
#ifdef _WIN32
				if (isMusicOn)
					PlaySound(TEXT("Music/PacmanFever"), NULL, SND_LOOP | SND_ASYNC);
#endif
				break;
			case isQuit:
				game.isRunning = SDL_FALSE;
				break;
			default:
				break;
			}
			if (newHighscore.name[0] != '\0') {
				updateHighscores(newHighscore);
				newHighscore.name[0] = '\0';
			}
		}
	}
	makeDecoyHighscoreFiles();
	writeHighscoresToFiles();
	destroyMenuTextures(menuTextureWhite, menuTextureYellow, &pacmanTexture);
	game.quit();

	return 0;
}
