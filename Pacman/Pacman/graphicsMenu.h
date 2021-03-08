#ifndef _graphicsMenu_h_
#define _graphicsMenu_h_

/*!	\file graphicsMenu.h
*	\brief Contains declarations and constants for menu and screen graphics
*/

#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string.h>
#include <stdlib.h>

#include "game.h"
#include "pauseMenuGraphics.h"
#include "gameMap.h"
#include "highscores.h"

#define SCREEN_SCALE 1
#define SCREEN_NAME ("Pacman")
#define MAX_STRING_LINE 20
#define NUMBER_OF_CHARACTERS ('Z')

/*!
*	\brief Enum containing all possible menu options
*/
enum MenuOptions { demoGame, newGame, continueGame, highscore, settings, credits, quitGame, numberOfMenuOptions };

/*!
*	\brief Enum containing all possible settings options
*/
enum SettingsOptions { gameDifficulty, diffOption, music, musicOption, numberOfSettingsOptions };

/*!
*	\brief Enum containing all possible music options
*/
enum YesNo { no, yes, numberOfMusicOptions };

/*!
 *	\brief Initializes the game and everything needed for it
 */
void gameInit();

/*!
 *	\brief Quits the game and destroys the renderers and windows
 */
void gameQuit();

/*!
 *	\brief Gets the current hardware screen resolution using arguments width and height
 *	\param width argument in which the width will be put
 *	\param height argument in which the height will be put
 */
void getScreenResolution(int *width, int *height);

/*!
 *	\brief Initializes the textures for menu
 *	\param menuTextureWhite SDL texture which contains white texture for menu
 *	\param menuTextureYellow SDL texture which contains yellow texture for menu
 *	\param PacmanTexture SDL texture which contains pacman texture for menu
 */
void initTexturesForMenu(SDL_Texture * menuTextureWhite[], SDL_Texture * menuTextureYellow[], SDL_Texture ** PacmanTexture);

/*!
 *	\brief Destroys all menu textures
 *	\param menuTextureWhite SDL texture which contains white texture for menu
 *	\param menuTextureYellow SDL texture which contains yellow texture for menu
 *	\param PacmanTexture SDL texture which contains pacman texture for menu
 */
void destroyMenuTextures(SDL_Texture * menuTextureWhite[], SDL_Texture * menuTextureYellow[], SDL_Texture ** PacmanTexture);

/*!
 *	\brief Creates a heading for menu
 */
void createHeading();

/*!	\brief Prints the menu
 *
 *	Prints the menu on the game screen
 *	using the argument enum menuOptions currentMenuOption
 *	for printing all of the menu options
 *	\param currentMenuOption indicates which menu option is highlighted
 *	\param menuTextureWhite SDL texture which contains white texture for menu
 *	\param menuTextureYellow SDL texture which contains yellow texture for menu
 *	\param PacmanTexture SDL texture which contains pacman texture for menu
 */
void printMenu(enum MenuOptions currentMenuOption, SDL_Texture * menuTextureWhite[], SDL_Texture * menuTextureYellow[], SDL_Texture * PacmanTexture);

/*!
 *	\brief Initializes the textures for settings
 */
void initSettingsTextures();

/*!
 *	\brief Destroys all the textures used in settings
 */
void destroySettingsTextures();

/*!
 *	\brief Creates a heading for settings
 */
void createSettingsHeading();

/*!	\brief Activates settings
 *
 *	Activates the settings on the game screen by
 *	handling all the user related input in the
 *	settings and prints the newly activated menu
 *   on the game screen
 *	\param currentDifficulty indicates which difficulty is on
 *	\param currentMusicOption indicates which music option is on
 */
void activateSettings(enum DifficultySpeed * currentDifficulty, enum YesNo * currentMusicOption);

/*!	\brief Prints settings
 *
 *	Prints the settings on the game screen
 *	using the arguments enum settingsOptions currentMenuOption,
 *	enum DifficultySpeed currentDifficulty and hoveringDiff,
 *  and enum YesNo currentMusicOption and hoveringMusicOption
 *	for printing all of the settings menu options
 *	\param currentMenuOption indicates which menu option is highlighted
 *	\param currentDifficulty indicates which difficulty is on
 *	\param hoveringDiff indicates which difficulty is highlighted
 *	\param currentMusicOption indicates which music option is on
 *	\param hoveringMusicOption indicates which music option is highlighted
 */
void printSettings(enum SettingsOptions currentMenuOption, enum DifficultySpeed currentDifficulty, enum DifficultySpeed hoveringDiff, enum YesNo currentMusicOption, enum YesNo hoveringMusicOption);

/*!
 *	\brief Initializes the textures for end game screen
 */
void initEndGameTextures();

/*!
 *	\brief Destroys all end game textures
 */
void destroyEndGameTextures();

/*!
 *	\brief Prints the end game screen
 */
void endGameScreen();

/*!
 *	\brief Initializes the textures for the final score screen
 */
void initFinalScoreTextures();

/*!
 *	\brief Destroys all end game textures
 */
void destroyFinalScoreTextures();

/*!
 *	\brief Prints the final score screen and input of name for the highscore
 *	\param currScore final score which will be saved
 *	\param name name of the player
 *	\param nameSave if name should be saved has value 1, otherwise 0
 */
void finalScoreScreen(int currScore, char * name, int *nameSave);

/*!
 *	\brief Creates a heading for highscore
 */
void createHighScoreHeading();

/*!
 *	\brief Prints the highscore
 */
void printHighScore();

/*!
 *	\brief Creates a heading for credits
 */
void createCreditsHeading();

/*!
 *	\brief Prints credits
 */
void printCredits();

/*!
 *	\brief Struct containing needed variables for settings textures
 */
typedef struct SettingsTexturesStruct {
	SDL_Texture * whiteTextures[numberOfSettingsOptions];
	SDL_Texture * yellowTextures[numberOfSettingsOptions];
	SDL_Texture * whiteDifficulty[NUMBER_OF_DIFFICULTIES];
	SDL_Texture * yellowDifficulty[NUMBER_OF_DIFFICULTIES];
	SDL_Texture * whiteFilledDiff[NUMBER_OF_DIFFICULTIES];
	SDL_Texture * yellowFilledDiff[NUMBER_OF_DIFFICULTIES];
	SDL_Texture * yesNoWhite[numberOfMusicOptions];
	SDL_Texture * yesNoYellow[numberOfMusicOptions];
	SDL_Texture * yesNoWhiteFilled[numberOfMusicOptions];
	SDL_Texture * yesNoYellowFilled[numberOfMusicOptions];
	SDL_Texture * pacmanTexture;
}SettingsMenuTextures;

/*!
 *	\brief Struct containing needed variables for end game textures
 */
typedef struct EndGameTextureStruct {
	SDL_Texture * gameOverTexture;
	SDL_Texture * pressAnyButtonTexture;
}EndGameTextures;

/*!
 *	\brief Struct containing needed variables for final score textures
 */
typedef struct finalScoreTexturesStruct {
	SDL_Texture * typeInYourNameTexture;
	SDL_Texture * characterTextures[NUMBER_OF_CHARACTERS];
	SDL_Texture * blankTexture;
}FinalScoreTextures;

/*!
 *	\brief Global variable which contains settings menu textures information
 */
SettingsMenuTextures settingsTextureManager;

/*!
*	\brief Global variable which contains end game textures information
*/
EndGameTextures endGameTextureManager;

/*!
 *	\brief Global variable which contains final score textures information
 */
FinalScoreTextures finalScoreTextureManager;

#endif
