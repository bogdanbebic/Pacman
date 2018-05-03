#include <stdio.h>

#include <Windows.h>

#pragma comment(lib, "winmm.lib")

int main() {
	printf("Hello, World!\n");
	PlaySound(TEXT("Music/ImperialMarch"), NULL, SND_SYNC);
	return 0;
}
