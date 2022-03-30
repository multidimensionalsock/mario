#pragma once
#include "Texture2D.h"
#include "GameScreen.h"

class GameScreenTitle : public GameScreen
{
private:
	Texture2D* m_background_texture;
	float m_background_yPos;

public:
	SDL_Renderer* m_renderer;

	GameScreenTitle(SDL_Renderer* renderer);
	~GameScreenTitle();

	void Render();
	void Update(float deltaTime, SDL_Event e);
	bool SetUpLevel();
};

