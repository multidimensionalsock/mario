#pragma once
#include "Texture2D.h"
#include "GameScreen.h"

class GameScreenDeath : public GameScreen
{
	private:
		Texture2D* m_background_texture;
		float m_background_yPos;

	public:
		SDL_Renderer* m_renderer;

		GameScreenDeath(SDL_Renderer* renderer);
		~GameScreenDeath();

		void Render();
		void Update(float deltaTime, SDL_Event e);
		bool SetUpLevel();
};

