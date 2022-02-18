#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Constants.h"
#include <iostream>
using namespace std;

//global varaibles
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
SDL_Texture* g_texture = nullptr;

bool InitSDL();
void CloseSDL();
bool Update();
void Render();
SDL_Texture* LoadTextureFromFile(string path);
void FreeTexture();

int main(int argc, char* args[]) {
	InitSDL();
	bool quit = false;
	while (!quit) {
		Render();
		quit = Update();
	}
	CloseSDL();

	return 0;
}

bool InitSDL() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "SDL did not initialise. ERROR: " << SDL_GetError();
		return false;
	}
	else {
		//create window
		g_window = SDL_CreateWindow("Games Engine Creation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		if (g_window == nullptr) {
			cout << "Window was not creared. ERROR: " << SDL_GetError();
			return false;
		}
	}
	g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED); //window, driver, render flags
	if (g_renderer != nullptr) {
		int imageFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imageFlags) & imageFlags)) {
			cout << "SDL_Image could not initialise. error: " << IMG_GetError();
			return false;
		}
	}
	else {
		cout << "Renderer could not initialise. Error: " << SDL_GetError();
		return false;
	}
	g_texture = LoadTextureFromFile("Images/test.bmp");
	if (g_texture == nullptr) {
		return false;
	}
	return true;
}

void CloseSDL() {

	//release window
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	//quit SDL subsystem 
	IMG_Quit();
	SDL_Quit();

	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;

}

bool Update() {
	SDL_Event e;
	SDL_PollEvent(&e);
	switch (e.type) {
	case SDL_QUIT:
		return true;
		break;
	}
	return false;
}

void Render() {
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);

	SDL_Rect renderLocation = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	SDL_RenderCopyEx(g_renderer, g_texture, NULL, &renderLocation, 0, NULL, SDL_FLIP_NONE); //renderer, texture, soruce rect, destination rect, angle, point for texture centre, flag

	SDL_RenderPresent(g_renderer);
}

SDL_Texture* LoadTextureFromFile(string path) {
	FreeTexture();
	SDL_Texture* p_texture = nullptr;
	SDL_Surface* p_surface = IMG_Load(path.c_str());
	if (p_surface != nullptr) {
		p_texture = SDL_CreateTextureFromSurface(g_renderer, p_surface);
		if (p_texture == nullptr) {
			cout << "unable to create texture from surface. error: " << SDL_GetError();
		}
		else {
			cout << "unable to create texture from surface. error " << IMG_GetError();
		}
		SDL_FreeSurface(p_surface);
	}
	return p_texture;
}

