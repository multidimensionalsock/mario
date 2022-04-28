#include "GameScreen.h"
#include <SDL.h>

GameScreen::GameScreen(SDL_Renderer* renderer) {
	m_renderer = renderer;
	FPS = 0;
}
GameScreen::~GameScreen() {
	m_renderer = nullptr;
}

void GameScreen::Render() {}

void GameScreen::Update(float deltaTime, SDL_Event e) {
}
