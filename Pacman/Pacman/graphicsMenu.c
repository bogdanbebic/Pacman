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

	//texture initialization and heading creation
	initGameTextures();
	createHeading();
	initPauseMenuTextures();
	initSettingsTextures();
	initEndGameTextures();
	initFinalScoreTextures();
	return;
}

/*
*	Quits the game and destroys the
*	renderers and windows
*/
void gameQuit() { //TODO: Delete all textures at the end
	extern Game game;
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
			tempSurface = SDL_LoadBMP("Pictures/easyWhite.bmp");
			settingsTextureManager.whiteDifficulty[0] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
			SDL_FreeSurface(tempSurface);
			tempSurface = SDL_LoadBMP("Pictures/mediumWhite.bmp");
			settingsTextureManager.whiteDifficulty[1] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
			SDL_FreeSurface(tempSurface);
			tempSurface = SDL_LoadBMP("Pictures/hardWhite.bmp");
			settingsTextureManager.whiteDifficulty[2] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
			SDL_FreeSurface(tempSurface);
			tempSurface = SDL_LoadBMP("Pictures/easyYellow.bmp");
			settingsTextureManager.yellowDifficulty[0] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
			SDL_FreeSurface(tempSurface);
			tempSurface = SDL_LoadBMP("Pictures/mediumYellow.bmp");
			settingsTextureManager.yellowDifficulty[1] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
			SDL_FreeSurface(tempSurface);
			tempSurface = SDL_LoadBMP("Pictures/hardYellow.bmp");
			settingsTextureManager.yellowDifficulty[2] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
			SDL_FreeSurface(tempSurface);
			tempSurface = SDL_LoadBMP("Pictures/easyWhiteFilled.bmp");
			settingsTextureManager.whiteFilledDiff[0] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
			SDL_FreeSurface(tempSurface);
			tempSurface = SDL_LoadBMP("Pictures/mediumWhiteFilled.bmp");
			settingsTextureManager.whiteFilledDiff[1] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
			SDL_FreeSurface(tempSurface);
			tempSurface = SDL_LoadBMP("Pictures/hardWhiteFilled.bmp");
			settingsTextureManager.whiteFilledDiff[2] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
			SDL_FreeSurface(tempSurface);
			tempSurface = SDL_LoadBMP("Pictures/easyYellowFilled.bmp");
			settingsTextureManager.yellowFilledDiff[0] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
			SDL_FreeSurface(tempSurface);
			tempSurface = SDL_LoadBMP("Pictures/mediumYellowFilled.bmp");
			settingsTextureManager.yellowFilledDiff[1] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
			SDL_FreeSurface(tempSurface);
			tempSurface = SDL_LoadBMP("Pictures/hardYellowFilled.bmp");
			settingsTextureManager.yellowFilledDiff[2] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
			SDL_FreeSurface(tempSurface);
			break;
		case musicOption:
			tempSurface = SDL_LoadBMP("Pictures/noWhite.bmp");
			settingsTextureManager.yesNoWhite[0] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
			SDL_FreeSurface(tempSurface);
			tempSurface = SDL_LoadBMP("Pictures/yesWhite.bmp");
			settingsTextureManager.yesNoWhite[1] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
			SDL_FreeSurface(tempSurface);
			tempSurface = SDL_LoadBMP("Pictures/noYellow.bmp");
			settingsTextureManager.yesNoYellow[0] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
			SDL_FreeSurface(tempSurface);
			tempSurface = SDL_LoadBMP("Pictures/yesYellow.bmp");
			settingsTextureManager.yesNoYellow[1] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
			SDL_FreeSurface(tempSurface);
			tempSurface = SDL_LoadBMP("Pictures/noWhiteFilled.bmp");
			settingsTextureManager.yesNoWhiteFilled[0] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
			SDL_FreeSurface(tempSurface);
			tempSurface = SDL_LoadBMP("Pictures/yesWhiteFilled.bmp");
			settingsTextureManager.yesNoWhiteFilled[1] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
			SDL_FreeSurface(tempSurface);
			tempSurface = SDL_LoadBMP("Pictures/noYellowFilled.bmp");
			settingsTextureManager.yesNoYellowFilled[0] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
			SDL_FreeSurface(tempSurface);
			tempSurface = SDL_LoadBMP("Pictures/yesYellowFilled.bmp");
			settingsTextureManager.yesNoYellowFilled[1] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
			SDL_FreeSurface(tempSurface);
			break;
		default:
			break;
		}
	}
	PacmanSurface = SDL_LoadBMP("Pictures/pacmanR.bmp");
	settingsTextureManager.pacmanTexture = SDL_CreateTextureFromSurface(game.screen.renderer, PacmanSurface);
	SDL_FreeSurface(PacmanSurface);

	
	return;
}

void printSettings(enum settingsOptions currentMenuOption, enum DifficultySpeed currentDifficulty, enum DifficultySpeed hoveringDiff, enum YesNo currentMusicOption, enum YesNo hoveringMusicOption) {
	extern Game game;
	extern SettingsMenuTextures settingsTextureManager;
	SDL_Rect menuRect, pacmanRect, diffRect;
	enum SettingsOptions menuOption;
	enum DifficultySpeed tempDiffArray[NUMBER_OF_DIFFICULTIES] = {EASY, MEDIUM, HARD};
	enum YesNo tempMusicArray[numberOfMusicOptions] = { no, yes };
	int i;

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
			for (i = 0; i < NUMBER_OF_DIFFICULTIES; i++) {
				diffRect.x = game.screen.width / 12 + i * game.screen.width / 18;
				diffRect.y = (8 + 3 * menuOption) * (game.screen.height / 44);
				diffRect.w = game.screen.width / 18;
				diffRect.h = game.screen.height / 22;
				if (tempDiffArray[i] == currentDifficulty && tempDiffArray[i] == hoveringDiff && currentMenuOption == menuOption) {
					SDL_RenderCopy(game.screen.renderer, settingsTextureManager.yellowFilledDiff[i], NULL, &diffRect);
				}
				else if ((tempDiffArray[i] == currentDifficulty && tempDiffArray[i] != hoveringDiff) ||(tempDiffArray[i] == currentDifficulty && currentMenuOption != menuOption)) {
					SDL_RenderCopy(game.screen.renderer, settingsTextureManager.whiteFilledDiff[i], NULL, &diffRect);
				}
				else if (tempDiffArray[i] == hoveringDiff && tempDiffArray[i] != currentDifficulty && currentMenuOption == menuOption) {
					SDL_RenderCopy(game.screen.renderer, settingsTextureManager.yellowDifficulty[i], NULL, &diffRect);
				}
				else {
					SDL_RenderCopy(game.screen.renderer, settingsTextureManager.whiteDifficulty[i], NULL, &diffRect);
				}
			}
			if (currentMenuOption == menuOption) {
				SDL_RenderCopy(game.screen.renderer, settingsTextureManager.pacmanTexture, NULL, &pacmanRect);
			}
			else {
				SDL_RenderFillRect(game.screen.renderer, &pacmanRect);
			}
		}
		if (menuOption == musicOption) {
			for (i = numberOfMusicOptions - 1; i >= 0; i--) {
				if (i == 1) {
					diffRect.x = game.screen.width / 12;
				}
				else {
					diffRect.x = game.screen.width / 12 + game.screen.width / 18;
				}
				diffRect.y = (8 + 3 * menuOption) * (game.screen.height / 44);
				diffRect.w = game.screen.width / 18;
				diffRect.h = game.screen.height / 22;
				if (tempMusicArray[i] == currentMusicOption && tempMusicArray[i] == hoveringMusicOption && currentMenuOption == menuOption) {
					SDL_RenderCopy(game.screen.renderer, settingsTextureManager.yesNoYellowFilled[i], NULL, &diffRect);
				}
				else if ((tempMusicArray[i] == currentMusicOption && tempMusicArray[i] != hoveringMusicOption) || (tempMusicArray[i] == currentMusicOption && currentMenuOption != menuOption)) {
					SDL_RenderCopy(game.screen.renderer, settingsTextureManager.yesNoWhiteFilled[i], NULL, &diffRect);
				}
				else if (tempMusicArray[i] == hoveringMusicOption && tempMusicArray[i] != currentMusicOption && currentMenuOption == menuOption) {
					SDL_RenderCopy(game.screen.renderer, settingsTextureManager.yesNoYellow[i], NULL, &diffRect);
				}
				else {
					SDL_RenderCopy(game.screen.renderer, settingsTextureManager.yesNoWhite[i], NULL, &diffRect);
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

void activateSettings(enum DifficultySpeed * currentDifficulty, enum YesNo * currentMusicOption) {
	SDL_Event event;
	extern Game game;
	int settingsRunning = 1;
	enum SettingsOptions selectedOption = gameDifficulty;
	enum DifficultySpeed hoveringDiff = EASY;
	enum YesNo hoveringMusicOption = yes;
	createSettingsHeading(); 
	while (game.isRunning) {
		while (SDL_PollEvent(&event)) {
			printSettings(selectedOption, *currentDifficulty, hoveringDiff, *currentMusicOption, hoveringMusicOption);
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
						if (selectedOption == musicOption) {
							*currentMusicOption = hoveringMusicOption;
						}
						if (selectedOption == gameDifficulty) {
							selectedOption = diffOption;
						}
						if (selectedOption == music) {
							selectedOption = musicOption;
						}
						if (*currentMusicOption) {
							PlaySound(TEXT("Music/PacmanFever"), NULL, SND_ASYNC);
						}
						else {
							PlaySound(NULL, NULL, SND_ASYNC);
						}
					}
					break;
				case SDLK_RIGHT:
					if (settingsRunning) {
						if (selectedOption == diffOption) {
							switch (hoveringDiff) {
							case EASY:
								hoveringDiff = MEDIUM;
								break;
							case MEDIUM:
								hoveringDiff = HARD;
								break;
							case HARD:
								hoveringDiff = EASY;
								break;
							}
						}
						if (selectedOption == musicOption) {
							switch (hoveringMusicOption) {
							case yes:
								hoveringMusicOption = no;
								break;
							case no:
								hoveringMusicOption = yes;
								break;
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
								break;
							case MEDIUM:
								hoveringDiff = EASY;
								break;
							case HARD:
								hoveringDiff = MEDIUM;
								break;
							}
						}
						if (selectedOption == musicOption) {
							switch (hoveringMusicOption) {
							case yes:
								hoveringMusicOption = no;
								break;
							case no:
								hoveringMusicOption = yes;
								break;
							}
						}
					}
					break;
				}
			break;
			case SDL_QUIT: 
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

void initEndGameTextures() {
	extern EndGameTextures endGameTextureManager;
	extern Game game;
	TTF_Font* font1 = TTF_OpenFont("impact.ttf", 80);
	TTF_Font * font2 = TTF_OpenFont("impact.ttf", 80);
	SDL_Color white = { 255, 255, 255 };
	SDL_Color yellow = { 255, 255, 0 };
	SDL_Surface *surface;
	surface = TTF_RenderText_Solid(font1, "GAME OVER", yellow);
	endGameTextureManager.gameOverTexture = SDL_CreateTextureFromSurface(game.screen.renderer, surface);
	SDL_FreeSurface(surface);
	surface = TTF_RenderText_Solid(font2, "PRESS ANY BUTTON TO CONTINUE", white);
	endGameTextureManager.pressAnyButtonTexture = SDL_CreateTextureFromSurface(game.screen.renderer, surface);
	SDL_FreeSurface(surface);
	return;
}

void endGameScreen() {
	SDL_Rect rect;
	SDL_Event event;
	int activeScreen = 1;
	extern EndGameTextures endGameTextureManager;
	extern Game game;
	rect.x = game.screen.width / 24;
	rect.y = game.screen.height / 10;
	rect.w = game.screen.width / 4;
	rect.h = game.screen.height / 6;
	SDL_RenderCopy(game.screen.renderer, endGameTextureManager.gameOverTexture, NULL, &rect);
	rect.x = game.screen.width / 24;
	rect.y = 15 * (game.screen.height / 40);
	rect.w = game.screen.width / 4;
	rect.h = game.screen.height / 12;
	SDL_RenderCopy(game.screen.renderer, endGameTextureManager.pressAnyButtonTexture, NULL, &rect);
	SDL_RenderPresent(game.screen.renderer);
	while (activeScreen) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				default:
					activeScreen = 0;
					return;
				}
			case SDL_QUIT:
				game.isRunning = 0;
				return;
			}

		}
	}
	return;
}

void initFinalScoreTextures() {
	char temp[2], c;
	extern FinalScoreTextures finalScoreTextureManager;
	TTF_Font* font = TTF_OpenFont("impact.ttf", 80);
	SDL_Color white = { 255, 255, 255 };
	SDL_Color yellow = { 255, 255, 0 };
	SDL_Surface * tempSurface;
	int i = 0;
	temp[1] = '\0';
	for (c = '0'; c <= '9'; c++) {
		temp[0] = c;
		tempSurface = TTF_RenderText_Solid(font, temp, white);
		finalScoreTextureManager.characterTextures[c] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
		SDL_FreeSurface(tempSurface);
	}
	for (c = 'A'; c <= 'Z'; c++) {
		temp[0] = c;
		tempSurface = TTF_RenderText_Solid(font, temp, white);
		finalScoreTextureManager.characterTextures[c] = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
		SDL_FreeSurface(tempSurface);
	}
	tempSurface = SDL_LoadBMP("Pictures/blankChar.bmp");
	finalScoreTextureManager.blankTexture = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	tempSurface = TTF_RenderText_Solid(font, "TYPE IN YOUR NAME:", white);
	finalScoreTextureManager.typeInYourNameTexture = SDL_CreateTextureFromSurface(game.screen.renderer, tempSurface);
	SDL_FreeSurface(tempSurface); 
	return;
}

void finalScoreScreen(int currScore, char * name, int * nameSave) {
	int currPos = 0, finalScoreActive = 1, i;
	SDL_Event event;
	SDL_Rect rect;
	SDL_Surface *surface;
	SDL_Texture *tex;
	TTF_Font* font = TTF_OpenFont("impact.ttf", 80);
	SDL_Color white = { 255, 255, 255 };
	char buffer[10], string[50] = "YOUR FINAL SCORE IS: ";

	_itoa_s(currScore, buffer, 10, 10);
	strcat_s(string, 50, buffer);
	surface = TTF_RenderText_Solid(font, string, white);
	tex = SDL_CreateTextureFromSurface(game.screen.renderer, surface);
	SDL_FreeSurface(surface);

	rect.x = game.screen.width / 15;
	rect.y = 4 * (game.screen.height / 40);
	rect.w = game.screen.width / 5;
	rect.h = game.screen.height / 12;
	SDL_RenderCopy(game.screen.renderer, tex, NULL, &rect);
	SDL_DestroyTexture(tex);

	rect.x = game.screen.width / 15;
	rect.y = 10 * (game.screen.height / 40);
	rect.w = game.screen.width / 5;
	rect.h = game.screen.height / 12;
	SDL_RenderCopy(game.screen.renderer, finalScoreTextureManager.typeInYourNameTexture, NULL, &rect);

	rect.y = 14 * (game.screen.height / 40);
	rect.w = game.screen.width / 50;
	rect.h = game.screen.height / 18;
	for (i = currPos; i <= MAX_NAME - 1; i++) {
		rect.x = game.screen.width / 18 + i * game.screen.width / 50;
		SDL_RenderFillRect(game.screen.renderer, &rect);
		if (i != MAX_NAME - 1)
			SDL_RenderCopy(game.screen.renderer, finalScoreTextureManager.blankTexture, NULL, &rect);
	}
	while (finalScoreActive) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				rect.x = game.screen.width / 18 + currPos * game.screen.width / 50;
				switch (event.key.keysym.sym) {
				case SDLK_0:
					name[currPos] = '0';
					SDL_RenderFillRect(game.screen.renderer, &rect);
					SDL_RenderCopy(game.screen.renderer, finalScoreTextureManager.characterTextures['0'], NULL, &rect);
					if (currPos < MAX_NAME - 1) { name[currPos] = '0'; currPos++; } 
					break;
				case SDLK_1:
					name[currPos] = '1';
					SDL_RenderFillRect(game.screen.renderer, &rect);
					SDL_RenderCopy(game.screen.renderer, finalScoreTextureManager.characterTextures['1'], NULL, &rect);
					if (currPos < MAX_NAME - 1) { name[currPos] = '1'; currPos++; }
					break;
				case SDLK_2:
					name[currPos] = '2';
					SDL_RenderFillRect(game.screen.renderer, &rect);
					SDL_RenderCopy(game.screen.renderer, finalScoreTextureManager.characterTextures['2'], NULL, &rect);
					if (currPos < MAX_NAME - 1) { name[currPos] = '2'; currPos++; }
					break;
				case SDLK_3:
					name[currPos] = '3';
					SDL_RenderFillRect(game.screen.renderer, &rect);
					SDL_RenderCopy(game.screen.renderer, finalScoreTextureManager.characterTextures['3'], NULL, &rect);
					if (currPos < MAX_NAME - 1) { name[currPos] = '3'; currPos++; }
					break;
				case SDLK_4:
					name[currPos] = '4';
					SDL_RenderFillRect(game.screen.renderer, &rect);
					SDL_RenderCopy(game.screen.renderer, finalScoreTextureManager.characterTextures['4'], NULL, &rect);
					if (currPos < MAX_NAME - 1) { name[currPos] = '4'; currPos++; }
					break;
				case SDLK_5:
					name[currPos] = '5';
					SDL_RenderFillRect(game.screen.renderer, &rect);
					SDL_RenderCopy(game.screen.renderer, finalScoreTextureManager.characterTextures['5'], NULL, &rect);
					if (currPos < MAX_NAME - 1) { name[currPos] = '5'; currPos++; }
					break;
				case SDLK_6:
					name[currPos] = '6';
					SDL_RenderFillRect(game.screen.renderer, &rect);
					SDL_RenderCopy(game.screen.renderer, finalScoreTextureManager.characterTextures['6'], NULL, &rect);
					if (currPos < MAX_NAME - 1) { name[currPos] = '6'; currPos++; }
					break;
				case SDLK_7:
					name[currPos] = '7';
					SDL_RenderFillRect(game.screen.renderer, &rect);
					SDL_RenderCopy(game.screen.renderer, finalScoreTextureManager.characterTextures['7'], NULL, &rect);
					if (currPos < MAX_NAME - 1) { name[currPos] = '7'; currPos++; }
					break;
				case SDLK_8:
					name[currPos] = '8';
					SDL_RenderFillRect(game.screen.renderer, &rect);
					SDL_RenderCopy(game.screen.renderer, finalScoreTextureManager.characterTextures['8'], NULL, &rect);
					if (currPos < MAX_NAME - 1) { name[currPos] = '8'; currPos++; }
					break;
				case SDLK_9:
					name[currPos] = '9';
					SDL_RenderFillRect(game.screen.renderer, &rect);
					SDL_RenderCopy(game.screen.renderer, finalScoreTextureManager.characterTextures['9'], NULL, &rect);
					if (currPos < MAX_NAME - 1) { name[currPos] = '9'; currPos++; }
					break;
				case SDLK_a:
					name[currPos] = 'A';
					SDL_RenderFillRect(game.screen.renderer, &rect);
					SDL_RenderCopy(game.screen.renderer, finalScoreTextureManager.characterTextures['A'], NULL, &rect);
					if (currPos < MAX_NAME - 1) { name[currPos] = 'A'; currPos++; }
					break;
				case SDLK_b:
					name[currPos] = 'B';
					SDL_RenderFillRect(game.screen.renderer, &rect);
					SDL_RenderCopy(game.screen.renderer, finalScoreTextureManager.characterTextures['B'], NULL, &rect);
					if (currPos < MAX_NAME - 1) { name[currPos] = 'B'; currPos++; }
					break;
				case SDLK_c:
					name[currPos] = 'C';
					SDL_RenderFillRect(game.screen.renderer, &rect);
					SDL_RenderCopy(game.screen.renderer, finalScoreTextureManager.characterTextures['C'], NULL, &rect);
					if (currPos < MAX_NAME - 1) { name[currPos] = 'C'; currPos++; }
					break;
				case SDLK_d:
					name[currPos] = 'D';
					SDL_RenderFillRect(game.screen.renderer, &rect);
					SDL_RenderCopy(game.screen.renderer, finalScoreTextureManager.characterTextures['D'], NULL, &rect);
					if (currPos < MAX_NAME - 1) { name[currPos] = 'D'; currPos++; }
					break;
				case SDLK_e:
					name[currPos] = 'E';
					SDL_RenderFillRect(game.screen.renderer, &rect);
					SDL_RenderCopy(game.screen.renderer, finalScoreTextureManager.characterTextures['E'], NULL, &rect);
					if (currPos < MAX_NAME - 1) { name[currPos] = 'E'; currPos++; }
					break;
				case SDLK_f:
					name[currPos] = 'F';
					SDL_RenderFillRect(game.screen.renderer, &rect);
					SDL_RenderCopy(game.screen.renderer, finalScoreTextureManager.characterTextures['F'], NULL, &rect);
					if (currPos < MAX_NAME - 1) { name[currPos] = 'F'; currPos++; }
					break;
				case SDLK_g:
					name[currPos] = 'G';
					SDL_RenderFillRect(game.screen.renderer, &rect);
					SDL_RenderCopy(game.screen.renderer, finalScoreTextureManager.characterTextures['G'], NULL, &rect);
					if (currPos < MAX_NAME - 1) { name[currPos] = 'G'; currPos++; }
					break;
				case SDLK_h:
					name[currPos] = 'H';
					SDL_RenderFillRect(game.screen.renderer, &rect);
					SDL_RenderCopy(game.screen.renderer, finalScoreTextureManager.characterTextures['H'], NULL, &rect);
					if (currPos < MAX_NAME - 1) { name[currPos] = 'H'; currPos++; }
					break;
				case SDLK_i:
					name[currPos] = 'I';
					SDL_RenderFillRect(game.screen.renderer, &rect);
					SDL_RenderCopy(game.screen.renderer, finalScoreTextureManager.characterTextures['I'], NULL, &rect);
					if (currPos < MAX_NAME - 1) { name[currPos] = 'I'; currPos++; }
					break;
				case SDLK_j:
					name[currPos] = 'J';
					SDL_RenderFillRect(game.screen.renderer, &rect);
					SDL_RenderCopy(game.screen.renderer, finalScoreTextureManager.characterTextures['J'], NULL, &rect);
					if (currPos < MAX_NAME - 1) { name[currPos] = 'J'; currPos++; }
					break;
				case SDLK_k:
					name[currPos] = 'K';
					SDL_RenderFillRect(game.screen.renderer, &rect);
					SDL_RenderCopy(game.screen.renderer, finalScoreTextureManager.characterTextures['K'], NULL, &rect);
					if (currPos < MAX_NAME - 1) { name[currPos] = 'K'; currPos++; }
					break;
				case SDLK_l:
					name[currPos] = 'L';
					SDL_RenderFillRect(game.screen.renderer, &rect);
					SDL_RenderCopy(game.screen.renderer, finalScoreTextureManager.characterTextures['L'], NULL, &rect);
					if (currPos < MAX_NAME - 1) { name[currPos] = 'L'; currPos++; }
					break;
				case SDLK_m:
					name[currPos] = 'M';
					SDL_RenderFillRect(game.screen.renderer, &rect);
					SDL_RenderCopy(game.screen.renderer, finalScoreTextureManager.characterTextures['M'], NULL, &rect);
					if (currPos < MAX_NAME - 1) { name[currPos] = 'M'; currPos++; }
					break;
				case SDLK_n:
					name[currPos] = 'N';
					SDL_RenderFillRect(game.screen.renderer, &rect);
					SDL_RenderCopy(game.screen.renderer, finalScoreTextureManager.characterTextures['N'], NULL, &rect);
					if (currPos < MAX_NAME - 1) { name[currPos] = 'N'; currPos++; }
					break;
				case SDLK_o:
					name[currPos] = 'O';
					SDL_RenderFillRect(game.screen.renderer, &rect);
					SDL_RenderCopy(game.screen.renderer, finalScoreTextureManager.characterTextures['O'], NULL, &rect);
					if (currPos < MAX_NAME - 1) { name[currPos] = 'O'; currPos++; }
					break;
				case SDLK_p:
					name[currPos] = 'P';
					SDL_RenderFillRect(game.screen.renderer, &rect);
					SDL_RenderCopy(game.screen.renderer, finalScoreTextureManager.characterTextures['P'], NULL, &rect);
					if (currPos < MAX_NAME - 1) { name[currPos] = 'P'; currPos++; }
					break;
				case SDLK_q:
					name[currPos] = 'Q';
					SDL_RenderFillRect(game.screen.renderer, &rect);
					SDL_RenderCopy(game.screen.renderer, finalScoreTextureManager.characterTextures['Q'], NULL, &rect);
					if (currPos < MAX_NAME - 1) { name[currPos] = 'Q'; currPos++; }
					break;
				case SDLK_r:
					name[currPos] = 'R';
					SDL_RenderFillRect(game.screen.renderer, &rect);
					SDL_RenderCopy(game.screen.renderer, finalScoreTextureManager.characterTextures['R'], NULL, &rect);
					if (currPos < MAX_NAME - 1) { name[currPos] = 'R'; currPos++; }
					break;
				case SDLK_s:
					name[currPos] = 'S';
					SDL_RenderFillRect(game.screen.renderer, &rect);
					SDL_RenderCopy(game.screen.renderer, finalScoreTextureManager.characterTextures['S'], NULL, &rect);
					if (currPos < MAX_NAME - 1) { name[currPos] = 'S'; currPos++; }
					break;
				case SDLK_t:
					name[currPos] = 'T';
					SDL_RenderFillRect(game.screen.renderer, &rect);
					SDL_RenderCopy(game.screen.renderer, finalScoreTextureManager.characterTextures['T'], NULL, &rect);
					if (currPos < MAX_NAME - 1) { name[currPos] = 'T'; currPos++; }
					break;
				case SDLK_u:
					name[currPos] = 'U';
					SDL_RenderFillRect(game.screen.renderer, &rect);
					SDL_RenderCopy(game.screen.renderer, finalScoreTextureManager.characterTextures['U'], NULL, &rect);
					if (currPos < MAX_NAME - 1) { name[currPos] = 'U'; currPos++; }
					break;
				case SDLK_v:
					name[currPos] = 'V';
					SDL_RenderFillRect(game.screen.renderer, &rect);
					SDL_RenderCopy(game.screen.renderer, finalScoreTextureManager.characterTextures['V'], NULL, &rect);
					if (currPos < MAX_NAME - 1) { name[currPos] = 'V'; currPos++; }
					break;
				case SDLK_w:
					name[currPos] = 'W';
					SDL_RenderFillRect(game.screen.renderer, &rect);
					SDL_RenderCopy(game.screen.renderer, finalScoreTextureManager.characterTextures['W'], NULL, &rect);
					if (currPos < MAX_NAME - 1) { name[currPos] = 'W'; currPos++; }
					break;
				case SDLK_x:
					name[currPos] = 'X';
					SDL_RenderFillRect(game.screen.renderer, &rect);
					SDL_RenderCopy(game.screen.renderer, finalScoreTextureManager.characterTextures['X'], NULL, &rect);
					if (currPos < MAX_NAME - 1) { name[currPos] = 'X'; currPos++; }
					break;
				case SDLK_y:
					name[currPos] = 'Y';
					SDL_RenderFillRect(game.screen.renderer, &rect);
					SDL_RenderCopy(game.screen.renderer, finalScoreTextureManager.characterTextures['Y'], NULL, &rect);
					if (currPos < MAX_NAME - 1) { name[currPos] = 'Y'; currPos++; }
					break;
				case SDLK_z:
					name[currPos] = 'Z';
					SDL_RenderFillRect(game.screen.renderer, &rect);
					SDL_RenderCopy(game.screen.renderer, finalScoreTextureManager.characterTextures['Z'], NULL, &rect);
					if (currPos < MAX_NAME - 1) { name[currPos] = 'Z'; currPos++; }
					break;
				case SDLK_BACKSPACE:
					name[currPos] = '\0';
					currPos = currPos ? currPos - 1 : currPos;
					break;
				case SDLK_RETURN:
					finalScoreActive = 0;
					break;
				case SDLK_ESCAPE:
					finalScoreActive = 0;
					*nameSave = 0;
					break;
				}
				
				for (i = currPos; i <= MAX_NAME - 1; i++) {
					rect.x = game.screen.width / 18 + i * game.screen.width / 50;
					SDL_RenderFillRect(game.screen.renderer, &rect);
					if (i != MAX_NAME - 1)
						SDL_RenderCopy(game.screen.renderer, finalScoreTextureManager.blankTexture, NULL, &rect);
				}
				break;
			case SDL_QUIT:
				game.isRunning = 0;
				return;
			}
		}
		SDL_RenderPresent(game.screen.renderer);
	}
	name[currPos] = '\0';
	return;
}

void createHighScoreHeading() {
	SDL_Surface *HeadingSurface;
	extern Game game;
	SDL_Texture *HeadingTexture;
	SDL_Rect HeadingRect;
	TTF_Font* font = TTF_OpenFont("impact.ttf", 50);
	TTF_Font * fontHeader = TTF_OpenFont("impact.ttf", 80);
	SDL_Color white = { 255, 255, 255 };

	HeadingSurface = TTF_RenderText_Solid(fontHeader, "HIGHSCORES", white);
	HeadingTexture = SDL_CreateTextureFromSurface(game.screen.renderer, HeadingSurface);
	SDL_FreeSurface(HeadingSurface);
	HeadingRect.x = game.screen.width / 22;
	HeadingRect.y = game.screen.height / 22;
	HeadingRect.w = game.screen.width / 4;
	HeadingRect.h = game.screen.height / 18;
	SDL_RenderCopy(game.screen.renderer, HeadingTexture, NULL, &HeadingRect);
	SDL_DestroyTexture(HeadingTexture);
}

void printHighScore() {
	extern Highscore highscores[MAX_HIGHSCORES];
	SDL_Event event;
	SDL_Surface *surface;
	SDL_Rect rect;
	SDL_Texture *texture;
	TTF_Font* font = TTF_OpenFont("impact.ttf", 80);
	SDL_Color white = { 255, 255, 255 };
	int i, highScoreRunning = 1, j;
	char buffer[40] = {0}, temp[40], temp2[40], buffer1[40] = { 0 };
	char string[3] = ". \0", whiteSpace[2] = " ";

	createHighScoreHeading();

	for (i = 0; i < MAX_HIGHSCORES; i++) {
		j = i + 1;
		_itoa_s(j, buffer, 40, 10);
		strcat_s(buffer, 40, string);
		_itoa_s(highscores[i].points, buffer1, 40, 10);
		strcpy_s(temp, 40, highscores[i].name);
		strcat_s(temp, 40, whiteSpace);
		strcpy_s(temp2, 40, buffer);
		strcat_s(temp, 40, buffer1);
		strcat_s(temp2, 40, temp);

		surface = TTF_RenderText_Solid(font, temp2, white);
		texture = SDL_CreateTextureFromSurface(game.screen.renderer, surface);
		SDL_FreeSurface(surface);

		rect.x = game.screen.width / 12;
		rect.y = (5 + 3 * i) * (game.screen.height / 48);
		rect.w = game.screen.width / 6;
		rect.h = game.screen.height / 24;
		SDL_RenderCopy(game.screen.renderer, texture, NULL, &rect);
		SDL_DestroyTexture(texture);
	}
	SDL_RenderPresent(game.screen.renderer);
	while (game.isRunning && highScoreRunning) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					highScoreRunning = 0;
					return;
					break;
				}
				break;
			case SDL_QUIT:
				game.isRunning = SDL_FALSE;
				highScoreRunning = 0;
				return;
				break;
			}
		}
	}

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


