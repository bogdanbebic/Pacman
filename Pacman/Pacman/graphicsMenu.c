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

	TTF_Font* font;

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
	extern Game game;
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

void initTexturesForMenu(SDL_Texture * menuTextureWhite[], SDL_Texture * menuTextureYellow[], SDL_Texture ** PacmanTexture) {
	SDL_Surface * PacmanSurface, *menuSurfaceYellow, *menuSurfaceWhite;
	enum MenuOptions menuOption;
	TTF_Font* font = TTF_OpenFont("impact.ttf", 46);
	SDL_Color white = { 255, 255, 255 };
	SDL_Color yellow = { 255, 255, 0 };

	for (menuOption = 0; menuOption < numberOfMenuOptions; menuOption++) {

		switch (menuOption) {
		case demoGame:
			menuSurfaceYellow = TTF_RenderText_Solid(font, "DEMO GAME", yellow);
			menuSurfaceWhite = TTF_RenderText_Solid(font, "DEMO GAME", white);
			break;
		case newGame:
			menuSurfaceYellow = TTF_RenderText_Solid(font, "NEW GAME", yellow);
			menuSurfaceWhite = TTF_RenderText_Solid(font, "NEW GAME", white);
			break;
		case continueGame:
			menuSurfaceYellow = TTF_RenderText_Solid(font, "CONTINUE", yellow);
			menuSurfaceWhite = TTF_RenderText_Solid(font, "CONTINUE", white);
			break;
		case highscore:
			menuSurfaceYellow = TTF_RenderText_Solid(font, "HIGHSCORE", yellow);
			menuSurfaceWhite = TTF_RenderText_Solid(font, "HIGHSCORE", white);
			break;
		case settings:
			menuSurfaceYellow = TTF_RenderText_Solid(font, "SETTINGS", yellow);
			menuSurfaceWhite = TTF_RenderText_Solid(font, "SETTINGS", white);
			break;
		case credits:
			menuSurfaceYellow = TTF_RenderText_Solid(font, "CREDITS", yellow);
			menuSurfaceWhite = TTF_RenderText_Solid(font, "CREDITS", white);
			break;
		case quitGame:
			menuSurfaceYellow = TTF_RenderText_Solid(font, "QUIT GAME", yellow);
			menuSurfaceWhite = TTF_RenderText_Solid(font, "QUIT GAME", white);
			break;
		default:
			break;
		}
		menuTextureWhite[menuOption] = SDL_CreateTextureFromSurface(game.screen.renderer, menuSurfaceWhite);
		menuTextureYellow[menuOption] = SDL_CreateTextureFromSurface(game.screen.renderer, menuSurfaceYellow);
		SDL_FreeSurface(menuSurfaceYellow);
		SDL_FreeSurface(menuSurfaceWhite);
	}
	PacmanSurface = SDL_LoadBMP("Pictures/pacmanR.bmp");
	*PacmanTexture = SDL_CreateTextureFromSurface(game.screen.renderer, PacmanSurface);
	SDL_FreeSurface(PacmanSurface);
	return;
}

void createHeading() {
	extern Game game;
	SDL_Surface *HeadingSurface;
	SDL_Texture *HeadingTexture;
	SDL_Rect HeadingRect;

	HeadingSurface = SDL_LoadBMP("Pictures/Heading.bmp");
	HeadingTexture = SDL_CreateTextureFromSurface(game.screen.renderer, HeadingSurface);
	SDL_FreeSurface(HeadingSurface);
	HeadingRect.x = game.screen.width / 24;
	HeadingRect.y = game.screen.height / 48;
	HeadingRect.w = game.screen.width / 4;
	HeadingRect.h = game.screen.height / 18;
	SDL_RenderCopy(game.screen.renderer, HeadingTexture, NULL, &HeadingRect);
	SDL_DestroyTexture(HeadingTexture);
}

void createSettingsHeading() {
	SDL_Surface *HeadingSurface;
	extern Game game;
	SDL_Texture *HeadingTexture;
	SDL_Rect HeadingRect;
	TTF_Font* font = TTF_OpenFont("impact.ttf", 50);
	TTF_Font * fontHeader = TTF_OpenFont("impact.ttf", 80);
	SDL_Color white = { 255, 255, 255 };

	HeadingSurface = TTF_RenderText_Solid(fontHeader, "SETTINGS", white);
	HeadingTexture = SDL_CreateTextureFromSurface(game.screen.renderer, HeadingSurface);
	SDL_FreeSurface(HeadingSurface);
	HeadingRect.x = game.screen.width / 22;
	HeadingRect.y = game.screen.height / 22;
	HeadingRect.w = game.screen.width / 4;
	HeadingRect.h = game.screen.height / 18;
	SDL_RenderCopy(game.screen.renderer, HeadingTexture, NULL, &HeadingRect);
	SDL_DestroyTexture(HeadingTexture);
}

void initSettingsTextures() {
	SDL_Surface * PacmanSurface, *menuSurfaceYellow, *menuSurfaceWhite, *tempSurface;
	extern SettingsMenuTextures settingsTextureManager;
	enum SettingsOptions menuOption;
	extern Game game;
	TTF_Font* font = TTF_OpenFont("impact.ttf", 46);
	SDL_Color white = { 255, 255, 255 };
	SDL_Color yellow = { 255, 255, 0 };

	for (menuOption = 0; menuOption < numberOfSettingsOptions; menuOption++) {
		switch (menuOption) {
		case gameDifficulty:
			menuSurfaceYellow = TTF_RenderText_Solid(font, "DIFFICULTY", yellow);
			menuSurfaceWhite = TTF_RenderText_Solid(font, "DIFFICULTY", white);
			settingsTextureManager.whiteTextures[menuOption] = SDL_CreateTextureFromSurface(game.screen.renderer, menuSurfaceWhite);
			settingsTextureManager.yellowTextures[menuOption] = SDL_CreateTextureFromSurface(game.screen.renderer, menuSurfaceYellow);
			SDL_FreeSurface(menuSurfaceYellow);
			SDL_FreeSurface(menuSurfaceWhite);
			break;
		case music:
			menuSurfaceYellow = TTF_RenderText_Solid(font, "MUSIC OPTION", yellow);
			menuSurfaceWhite = TTF_RenderText_Solid(font, "MUSIC OPTION", white);
			settingsTextureManager.whiteTextures[menuOption] = SDL_CreateTextureFromSurface(game.screen.renderer, menuSurfaceWhite);
			settingsTextureManager.yellowTextures[menuOption] = SDL_CreateTextureFromSurface(game.screen.renderer, menuSurfaceYellow);
			SDL_FreeSurface(menuSurfaceYellow);
			SDL_FreeSurface(menuSurfaceWhite);
			break;
		case diffOption:
			tempSurface = SDL_LoadBMP("Pictures/hardWhite.bmp");
			settingsTextureManager.whiteDifficulty[0] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
			SDL_FreeSurface(tempSurface);
			tempSurface = SDL_LoadBMP("Pictures/hardWhite.bmp");
			settingsTextureManager.whiteDifficulty[1] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
			SDL_FreeSurface(tempSurface);
			tempSurface = SDL_LoadBMP("Pictures/hardWhite.bmp");
			settingsTextureManager.whiteDifficulty[2] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
			SDL_FreeSurface(tempSurface);
			tempSurface = SDL_LoadBMP("Pictures/hardWhite.bmp");
			settingsTextureManager.yellowDifficulty[0] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
			SDL_FreeSurface(tempSurface);
			tempSurface = SDL_LoadBMP("Pictures/hardWhite.bmp");
			settingsTextureManager.yellowDifficulty[1] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
			SDL_FreeSurface(tempSurface);
			tempSurface = SDL_LoadBMP("Pictures/hardWhite.bmp");
			settingsTextureManager.yellowDifficulty[2] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
			SDL_FreeSurface(tempSurface);
			tempSurface = SDL_LoadBMP("Pictures/hardWhite.bmp");
			settingsTextureManager.whiteFilledDiff[0] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
			SDL_FreeSurface(tempSurface);
			tempSurface = SDL_LoadBMP("Pictures/hardWhite.bmp");
			settingsTextureManager.whiteFilledDiff[1] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
			SDL_FreeSurface(tempSurface);
			tempSurface = SDL_LoadBMP("Pictures/hardWhite.bmp");
			settingsTextureManager.whiteFilledDiff[2] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
			SDL_FreeSurface(tempSurface);
			tempSurface = SDL_LoadBMP("Pictures/hardWhite.bmp");
			settingsTextureManager.yellowFilledDiff[0] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
			SDL_FreeSurface(tempSurface);
			tempSurface = SDL_LoadBMP("Pictures/hardWhite.bmp");
			settingsTextureManager.yellowFilledDiff[1] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
			SDL_FreeSurface(tempSurface);
			tempSurface = SDL_LoadBMP("Pictures/hardWhite.bmp");
			settingsTextureManager.yellowFilledDiff[2] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
			SDL_FreeSurface(tempSurface);
			break;
		default:
			break;
		}
	}
	PacmanSurface = SDL_LoadBMP("Pictures/pacmanR.bmp");
	settingsTextureManager.pacmanTexture = SDL_CreateTextureFromSurface(game.screen.renderer, PacmanSurface);
	SDL_FreeSurface(PacmanSurface);

	/*tempSurface = SDL_LoadBMP("Pictures/hardWhite.bmp");
	settingsTextureManager.whiteDifficulty[0] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	tempSurface = SDL_LoadBMP("Pictures/hardWhite.bmp");
	settingsTextureManager.whiteDifficulty[1] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	tempSurface = SDL_LoadBMP("Pictures/hardWhite.bmp");
	settingsTextureManager.whiteDifficulty[2] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	tempSurface = SDL_LoadBMP("Pictures/hardWhite.bmp");
	settingsTextureManager.yellowDifficulty[0] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	tempSurface = SDL_LoadBMP("Pictures/hardWhite.bmp");
	settingsTextureManager.yellowDifficulty[1] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	tempSurface = SDL_LoadBMP("Pictures/hardWhite.bmp");
	settingsTextureManager.yellowDifficulty[2] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	tempSurface = SDL_LoadBMP("Pictures/hardWhite.bmp");
	settingsTextureManager.whiteFilledDiff[0] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	tempSurface = SDL_LoadBMP("Pictures/hardWhite.bmp");
	settingsTextureManager.whiteFilledDiff[1] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	tempSurface = SDL_LoadBMP("Pictures/hardWhite.bmp");
	settingsTextureManager.whiteFilledDiff[2] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	tempSurface = SDL_LoadBMP("Pictures/hardWhite.bmp");
	settingsTextureManager.yellowFilledDiff[0] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	tempSurface = SDL_LoadBMP("Pictures/hardWhite.bmp");
	settingsTextureManager.yellowFilledDiff[1] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	tempSurface = SDL_LoadBMP("Pictures/hardWhite.bmp");
	settingsTextureManager.yellowFilledDiff[2] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
	SDL_FreeSurface(tempSurface);*/
	return;
}

void printSettings(enum settingsOptions currentMenuOption, enum DifficultySpeed currentDifficulty, enum DifficultySpeed hoveringDiff) {
	extern Game game;
	extern SettingsMenuTextures settingsTextureManager;
	SDL_Rect menuRect, pacmanRect;
	enum SettingsOptions menuOption;
	enum DifficultySpeed temp;

	for (menuOption = 0; menuOption < numberOfSettingsOptions; menuOption++) {
		menuRect.x = game.screen.width / 12;
		menuRect.y = (8 + 3 * menuOption) * (game.screen.height / 44);
		menuRect.w = game.screen.width / 6;
		menuRect.h = game.screen.height / 22;
		pacmanRect.x = game.screen.width / 24;
		pacmanRect.y = (8 + 3 * menuOption) * (game.screen.height / 44);
		pacmanRect.w = game.screen.width / 30;
		pacmanRect.h = game.screen.height / 22;
		if (menuOption != diffOption) {
			if (currentMenuOption == menuOption) {
				SDL_RenderCopy(game.screen.renderer, settingsTextureManager.yellowTextures[menuOption], NULL, &menuRect);
				SDL_RenderCopy(game.screen.renderer, settingsTextureManager.pacmanTexture, NULL, &pacmanRect);
			}
			else {
				SDL_RenderCopy(game.screen.renderer, settingsTextureManager.whiteTextures[menuOption], NULL, &menuRect);
				SDL_RenderFillRect(game.screen.renderer, &pacmanRect);
			}
		}
		if (menuOption == diffOption) {
			for (temp = EASY; temp < numberOfDifficulties; temp++) {
				menuRect.x = game.screen.width / 12 + temp * game.screen.width / 18;
				menuRect.w = game.screen.width / 18;
				if (temp == currentDifficulty && temp == hoveringDiff) {
					SDL_RenderCopy(game.screen.renderer, settingsTextureManager.yellowFilledDiff[temp], NULL, &menuRect);
				}
				else if (temp == currentDifficulty) {
					SDL_RenderCopy(game.screen.renderer, settingsTextureManager.whiteFilledDiff[temp], NULL, &menuRect);
				}
				else if (temp == hoveringDiff) {
					SDL_RenderCopy(game.screen.renderer, settingsTextureManager.yellowDifficulty[temp], NULL, &menuRect);
				}
				else {
					SDL_RenderCopy(game.screen.renderer, settingsTextureManager.whiteDifficulty[temp], NULL, &menuRect);
				}
			}
			if (currentMenuOption == menuOption) {
				SDL_RenderCopy(game.screen.renderer, settingsTextureManager.pacmanTexture, NULL, &pacmanRect);
			}
			else {
				SDL_RenderFillRect(game.screen.renderer, &pacmanRect);
			}
		}
	}
	SDL_RenderPresent(game.screen.renderer);

	return;
}

void activateSettings(enum DifficultySpeed * currentDifficulty) {
	SDL_Event event;
	extern Game game;
	int settingsRunning = 1;
	enum SettingsOptions selectedOption = gameDifficulty;
	enum DifficultySpeed hoveringDiff = EASY;
	createSettingsHeading();
	while (game.isRunning) {
		printSettings(selectedOption, *currentDifficulty, hoveringDiff);
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {

				case SDLK_ESCAPE:
					settingsRunning = 0;
					return;
					break;

				case SDLK_UP:
					if (settingsRunning) {

						selectedOption = selectedOption ? selectedOption - 1 : numberOfSettingsOptions - 1;
					}
					break;

				case SDLK_DOWN:
					if (settingsRunning) {
						selectedOption = (selectedOption + 1) % numberOfSettingsOptions;
					}
					break;

				case SDLK_RETURN:
					if (settingsRunning) {
						if (selectedOption == diffOption) {
							*currentDifficulty = hoveringDiff;
						}
					}
					break;
				case SDLK_RIGHT:
					if (settingsRunning) {
						if (selectedOption == diffOption) {
							switch (hoveringDiff) {
							case EASY:
								hoveringDiff = MEDIUM;
							case MEDIUM:
								hoveringDiff = HARD;
							case HARD:
								hoveringDiff = EASY;
							}
						}
					}
					break;
				case SDLK_LEFT:
					if (settingsRunning) {
						if (selectedOption == diffOption) {
							switch (hoveringDiff) {
							case EASY:
								hoveringDiff = HARD;
							case MEDIUM:
								hoveringDiff = EASY;
							case HARD:
								hoveringDiff = MEDIUM;
							}
						}
					}
					break;
				}
			break;
			case SDL_QUIT: //ne radi
					game.isRunning = SDL_FALSE;
					settingsRunning = 0;
					return;
					break;
			}
		}
	}
	settingsRunning = 0;
	return;
}

/*
*	Prints the menu on the game screen
*	using the argument enum menuOptions currentMenuOption
*	for printing all of the menu options
*/
void printMenu(enum menuOptions currentMenuOption, SDL_Texture * menuTextureWhite[], SDL_Texture * menuTextureYellow[], SDL_Texture * PacmanTexture) {
	SDL_Rect menuRect, pacmanRect;
	enum MenuOptions menuOption;

	for (menuOption = 0; menuOption < numberOfMenuOptions; menuOption++) {
		menuRect.x = game.screen.width / 12;
		menuRect.y = (5 + 3 * menuOption) * (game.screen.height / 48);
		menuRect.w = game.screen.width / 6;
		menuRect.h = game.screen.height / 24;
		pacmanRect.x = game.screen.width / 24;
		pacmanRect.y = (5 + 3 * menuOption) * (game.screen.height / 48);
		pacmanRect.w = game.screen.width / 30;
		pacmanRect.h = game.screen.height / 24;
		if (currentMenuOption == menuOption) {
			SDL_RenderCopy(game.screen.renderer, menuTextureYellow[menuOption], NULL, &menuRect);
			SDL_RenderCopy(game.screen.renderer, PacmanTexture, NULL, &pacmanRect);
		}
		else {
			SDL_RenderCopy(game.screen.renderer, menuTextureWhite[menuOption], NULL, &menuRect);
			SDL_RenderFillRect(game.screen.renderer, &pacmanRect);
		}
	}
	SDL_RenderPresent(game.screen.renderer);
	return;
}


