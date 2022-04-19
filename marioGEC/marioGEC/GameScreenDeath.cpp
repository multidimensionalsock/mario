#include "GameScreenDeath.h"
#include <iostream>

GameScreenDeath::GameScreenDeath(SDL_Renderer* renderer) : GameScreen(renderer)
{
	m_renderer = renderer;
	SetUpLevel();
}

GameScreenDeath::~GameScreenDeath()
{
	m_renderer = nullptr;
}

void GameScreenDeath::Render()
{
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);
}

void GameScreenDeath::Update(float deltaTime, SDL_Event e)
{
}

bool GameScreenDeath::SetUpLevel()
{
	m_background_yPos = 0.0f;

	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/DeathScreen.png")) {
		std::cout << "Failed to load background texture! " << std::endl;
		return false;
	}
	return true;
}
