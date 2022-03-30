#include "GameScreenTitle.h"
#include <iostream>

GameScreenTitle::GameScreenTitle(SDL_Renderer* renderer) : GameScreen(renderer)
{
	m_background_yPos = 0.0f;
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/TitleScreen.png")) {
		std::cout << "Failed to load background texture! " << std::endl;
	}
}

GameScreenTitle::~GameScreenTitle()
{
	m_renderer = nullptr;
}

void GameScreenTitle::Render()
{
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);
}

void GameScreenTitle::Update(float deltaTime, SDL_Event e)
{
}
