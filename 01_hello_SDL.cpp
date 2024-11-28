

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <iostream>

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 960;

enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

SDL_Surface* loadSurface(string path);

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHelloWorld = NULL;

SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface* gCurrentSurface = NULL;

SDL_Surface* loadSurface(string path) {
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}
	
	return loadedSurface;
}

bool init() {
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not init SDL_ERROR: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow("Proto Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (gWindow == NULL) {
			printf("SDL could not create window SDL_ERROR: %s\n", SDL_GetError());
			success = false;
		}
		else {
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}

	return success;
}

bool loadMedia() {
	bool success = true;

	gHelloWorld = SDL_LoadBMP("assets/2018-06-15.bmp");

	if (gHelloWorld == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError());
		success = false;
	}

	return success;
}

void close() {
	SDL_FreeSurface(gScreenSurface);

	gScreenSurface = NULL;

	SDL_DestroyWindow(gWindow);

	gWindow = NULL;

	SDL_Quit();
}

int main( int argc, char* args[] )
{

	if (!init()) {
		printf("Failed to initialize\n");
	}
	else {
		if (!loadMedia()) {
			printf("Failed to load image\n");
		}
		else {
			bool quit = false;
			SDL_Event e;

			while (!quit) {
				while (SDL_PollEvent(&e) != 0) {
					if (e.type == SDL_QUIT) {
						quit = true;
					}
				}

				SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);

				SDL_UpdateWindowSurface(gWindow);
			}
		}
	}

	void close();

	return 0;
}
