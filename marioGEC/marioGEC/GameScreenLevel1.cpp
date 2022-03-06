#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"
#include "Character.h"
#include "LevelMap.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer) {
	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1() {
	m_background_texture = nullptr;
	delete my_character;
	my_character = nullptr;
	m_level_map = nullptr;
}

void GameScreenLevel1::Render() {
	//draw background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
	my_character->Render();
	//luigi->Render();
}

bool GameScreenLevel1::SetUpLevel() {
	SetLevelMap();

	my_character = new Character(m_renderer, "Images/Mario.png", Vector2D(64, 330),m_level_map);
	//luigi = new Character(m_renderer, "Images/Mario.png", Vector2D(150, 330));

	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/BackgroundMB.png")) {
		std::cout << "Failed to load background texture! " << std::endl;
		return false;
	}
	return true;
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e) {
	//update character
	my_character->Update(deltaTime, e);
	/*if (Collisions::Instance()->Circle(my_character, luigi)) {
		std::cout << "Circle hit!" << std::endl;
	}
	if (Collisions::Instance()->Box(my_character->GetCollisionBox(), luigi->GetCollisionBox())) {
		std::cout << "box hit " << std::endl;
	}*/
}

void GameScreenLevel1::SetLevelMap() {
	int map[MAP_HEIGHT][MAP_WIDTH] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0},
		{1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	//clear any old maps
	if (m_level_map != nullptr) {
		delete m_level_map;
	}
	//set new one
	m_level_map = new LevelMap(map);
}