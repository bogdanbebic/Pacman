#include <stdio.h>

#include <Windows.h>
#pragma comment(lib, "winmm.lib")

#include <SDL.h>


int main(int argc, char *argv[]) {


	printf("Hello, World!\n");
	PlaySound(TEXT("Music/ImperialMarch"), NULL, SND_SYNC);

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("SDL_Init failed: %s\n", SDL_GetError());
		return 0;
	}



	return 0;
}
