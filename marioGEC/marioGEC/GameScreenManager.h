#pragma once
#ifndef _SCREENMANAGER_H
#define _SCREENMANAGER_H
#include "SDL.h"
#include "Commons.h"
class GameScreen;

class GameScreenManager{
	private:
		SDL_Renderer* m_renderer;
		GameScreen* m_current_screen;
		SCREENS screen_input_check;

	public:
		GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen);
		~GameScreenManager();

		void Render();
		void Update(float deltaTime, SDL_Event e);
		void ChangeScreen(SCREENS new_screen);
};

#endif
