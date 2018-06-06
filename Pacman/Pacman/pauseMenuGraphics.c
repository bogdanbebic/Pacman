#include "pauseMenuGraphics.h"
#include "cheats.h"

/*! \file pauseMenuGraphics.c
*	\brief Contains function definitions needed for graphics of in game pause menu
*/

extern PauseMenuTextures pauseMenuTextureManager;

/*!
*	\brief Initializes the textures for pause menu
*/
void initPauseMenuTextures() {
	SDL_Surface * tempSurfaceWhite, *tempSurfaceYellow;
	enum PauseMenuOptions pauseMenuOption;
	TTF_Font* font = TTF_OpenFont("impact.ttf", 46);
	SDL_Color white = { 255, 255, 255 };
	SDL_Color yellow = { 255, 255, 0 };

	for (pauseMenuOption = 0; pauseMenuOption < numberOfPauseMenuOptions; pauseMenuOption++) {

		switch (pauseMenuOption) {
		case continueWithGame:
			tempSurfaceYellow = TTF_RenderText_Solid(font, "CONTINUE", yellow);
			tempSurfaceWhite = TTF_RenderText_Solid(font, "CONTINUE", white);
			break;
		case mainMenu:
			tempSurfaceYellow = TTF_RenderText_Solid(font, "MAIN MENU", yellow);
			tempSurfaceWhite = TTF_RenderText_Solid(font, "MAIN MENU", white);
			break;
		case finishGame:
			tempSurfaceYellow = TTF_RenderText_Solid(font, "FINISH GAME", yellow);
			tempSurfaceWhite = TTF_RenderText_Solid(font, "FINISH GAME", white);
			break;
		default:
			break;
		}
		pauseMenuTextureManager.whiteTextures[pauseMenuOption] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurfaceWhite);
		pauseMenuTextureManager.yellowTextures[pauseMenuOption] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurfaceYellow);
		SDL_FreeSurface(tempSurfaceWhite);
		SDL_FreeSurface(tempSurfaceYellow);
	}
	tempSurfaceWhite = SDL_LoadBMP("Pictures/pacmanR.bmp");
	pauseMenuTextureManager.pacmanTexture = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurfaceWhite);
	SDL_FreeSurface(tempSurfaceWhite);
	return;
}

/*!
*	\brief Creates a heading for pause menu
*/
void createPauseHeading() {
	SDL_Surface *HeadingSurface;
	SDL_Texture *HeadingTexture;
	SDL_Rect HeadingRect;
	TTF_Font* font = TTF_OpenFont("impact.ttf", 50);
	TTF_Font * fontHeader = TTF_OpenFont("impact.ttf", 80);
	SDL_Color white = { 255, 255, 255 };

	HeadingSurface = TTF_RenderText_Solid(fontHeader, "PAUSE MENU", white);
	HeadingTexture = SDL_CreateTextureFromSurface(game.screen.renderer, HeadingSurface);
	SDL_FreeSurface(HeadingSurface);
	HeadingRect.x = game.screen.width / 22;
	HeadingRect.y = game.screen.height / 22;
	HeadingRect.w = game.screen.width / 4;
	HeadingRect.h = game.screen.height / 18;
	SDL_RenderCopy(game.screen.renderer, HeadingTexture, NULL, &HeadingRect);
	SDL_DestroyTexture(HeadingTexture);
}

/*!
*	\brief Prints the pause menu
*	\param currentOption option which is currently highlighted
*/
void printPauseMenu(enum PauseMenuOptions currentOption) {
	SDL_Rect menuRect, pacmanRect;
	enum PauseMenuOptions menuOption;

	for (menuOption = 0; menuOption < numberOfPauseMenuOptions; menuOption++) {
		menuRect.x = game.screen.width / 12;
		menuRect.y = (8 + 3 * menuOption) * (game.screen.height / 44);
		menuRect.w = game.screen.width / 6;
		menuRect.h = game.screen.height / 22;
		pacmanRect.x = game.screen.width / 24;
		pacmanRect.y = (8 + 3 * menuOption) * (game.screen.height / 44);
		pacmanRect.w = game.screen.width / 30;
		pacmanRect.h = game.screen.height / 22;
		if (currentOption == menuOption) {
			SDL_RenderCopy(game.screen.renderer, pauseMenuTextureManager.yellowTextures[menuOption], NULL, &menuRect);
			SDL_RenderCopy(game.screen.renderer, pauseMenuTextureManager.pacmanTexture, NULL, &pacmanRect);
		}
		else {
			SDL_RenderCopy(game.screen.renderer, pauseMenuTextureManager.whiteTextures[menuOption], NULL, &menuRect);
			SDL_RenderFillRect(game.screen.renderer, &pacmanRect);
		}
	}
	SDL_RenderPresent(game.screen.renderer);
	return;
}

/*!	\brief Activates pause menu
*
*	Activates pause menu on the game screen by
*	handling all the user related input in the
*	menu itself and prints the newly activated menu
*   on the game screen
*	\param difficulty difficulty of the game
*/
enum PauseMenuOptions ActivatePauseMenu(int difficulty) { // STA CE NAM DIFFICULTY ZA PARAMETAR OVDE
	int activePauseMenu = 1, currPos = 0;
	char cheat[MAX_CHEAT];
	SDL_Event event;
	enum PauseMenuOptions selectedOption = continueWithGame;
	enum PauseMenuOptions currentOption = selectedOption;

	createPauseHeading();

	while (game.isRunning) {
		printPauseMenu(currentOption);
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {

				case SDLK_ESCAPE:
					if (activePauseMenu) {
						return continueWithGame;
					}
					break;

				case SDLK_UP:
					if (activePauseMenu) {
						selectedOption = selectedOption ? selectedOption - 1 : numberOfPauseMenuOptions - 1;
					}
					break;

				case SDLK_DOWN:
					if (activePauseMenu) {
						selectedOption = (selectedOption + 1) % numberOfPauseMenuOptions;
					}
					break;

				case SDLK_RETURN: case SDLK_RIGHT:
					switch (selectedOption) {
					case continueWithGame:
						return continueWithGame;
					case mainMenu:
						return mainMenu;
					case finishGame:
						return finishGame;
					}
					break;

				case SDLK_BACKSPACE:
					cheat[currPos = 0] = '\0';
					break;

				default:
					if (currPos < MAX_CHEAT - 1) {
						if (event.key.keysym.sym <= SDLK_9 && event.key.keysym.sym >= SDLK_0) {
							cheat[currPos++] = MAP_SDL_NUMBERS(event.key.keysym.sym);
						}
						else if (event.key.keysym.sym <= SDLK_z && event.key.keysym.sym >= SDLK_a) {
							cheat[currPos++] = MAP_SDL_LETTERS(event.key.keysym.sym);
						}
						cheat[currPos] = '\0';
					}
					toggleIfCheat(cheat);
				}


				break;	// break SDL_KEYDOWN
			case SDL_QUIT:
				game.isRunning = SDL_FALSE;

				break;
			}
			currentOption = selectedOption;
		}
	}
	return quitInGame;
	activePauseMenu = 0;
}

/*
*	\brief Destroys all the textures used in the pause menu
*/
void destroyPauseMenuTextures() {
	enum PauseMenuOptions pauseMenuOption;

	for (pauseMenuOption = 0; pauseMenuOption < numberOfPauseMenuOptions; pauseMenuOption++) {
		SDL_DestroyTexture(pauseMenuTextureManager.whiteTextures[pauseMenuOption]);
		SDL_DestroyTexture(pauseMenuTextureManager.yellowTextures[pauseMenuOption]);
	}
	SDL_DestroyTexture(pauseMenuTextureManager.pacmanTexture);
}
