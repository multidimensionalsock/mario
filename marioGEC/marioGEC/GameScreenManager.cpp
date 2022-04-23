#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "GameScreenLevel2.h"
#include "GameScreenTitle.h"
#include "GameScreenDeath.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen) {
	m_renderer = renderer;
	m_current_screen = nullptr;
	ChangeScreen(startScreen);
	screen_input_check = startScreen;
}

GameScreenManager::~GameScreenManager() {
	m_renderer = nullptr;
	delete m_current_screen;
	m_current_screen = nullptr;
}

void GameScreenManager::Render() {
	m_current_screen->Render();
}

void GameScreenManager::Update(float deltaTime, SDL_Event e) {
	m_current_screen->Update(deltaTime, e);
	if (screen_input_check == SCREEN_INTRO) {
		switch (e.type) {
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym) {
			case SDLK_1:
				ChangeScreen(SCREEN_LEVEL1);
				break;
			case SDLK_2:
				ChangeScreen(SCREEN_LEVEL2);
				break;
			}
		}
	}
	else if (screen_input_check == SCREEN_DEATH) {
		switch (e.type) {
		case SDL_KEYDOWN:
			ChangeScreen(SCREEN_INTRO);
		}
	}
	if (m_current_screen->marioDeathGet() == true && m_current_screen->luigiDeathGet() == true) {
		ChangeScreen(SCREEN_DEATH);
	}
}

void GameScreenManager::ChangeScreen(SCREENS new_screen) {
	if (m_current_screen != nullptr) {
		delete m_current_screen;
	}

	GameScreen* tempScreen;
	switch (new_screen) {
		case SCREEN_INTRO:
			tempScreen = new GameScreenTitle(m_renderer);
			m_current_screen = (GameScreen*)tempScreen;
			screen_input_check = SCREEN_INTRO;
			tempScreen = nullptr;
			break;
		case SCREEN_LEVEL1:
			tempScreen = new GameScreenLevel1(m_renderer);
			m_current_screen = (GameScreen*)tempScreen;
			screen_input_check = SCREEN_LEVEL1;
			tempScreen = nullptr;
			break;
		case SCREEN_LEVEL2:
			tempScreen = new GameScreenLevel2(m_renderer);
			m_current_screen = (GameScreen*)tempScreen;
			screen_input_check = SCREEN_LEVEL2;
			tempScreen = nullptr;
			break;
		case SCREEN_DEATH:
			tempScreen = new GameScreenDeath(m_renderer);
			m_current_screen = (GameScreen*)tempScreen;
			screen_input_check = SCREEN_DEATH;
			tempScreen = nullptr;
			break;
		default:;
	}
}