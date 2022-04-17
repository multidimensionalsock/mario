#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"
#include "Character.h"
#include "LevelMap.h"
#include "PowBlock.h"
#include "Collisions.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer) {
	SetUpLevel();
	spawnerFrameCount = 0;
}

GameScreenLevel1::~GameScreenLevel1() {
	m_background_texture = nullptr;
	delete my_character;
	my_character = nullptr;
	m_level_map = nullptr;
	m_pow_block = nullptr;

	m_enemies.clear();
}

void GameScreenLevel1::Render() {
	//draw background
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);
	if (my_character->GetAlive()) {
		my_character->Render();
	}
	if (luigi->GetAlive()) {
		luigi->Render();
	}
	m_pow_block->Render();
	for (int i = 0; i < m_coins.size(); i++) {
		m_coins[i]->Render();
	}
	for (int i = 0; i < m_enemies.size(); i++) {
		m_enemies[i]->Render();
	}
}

bool GameScreenLevel1::SetUpLevel() {
	SetLevelMap();

	my_character = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(40, 330),m_level_map);
	luigi = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(140, 330), m_level_map);
	m_pow_block = new PowBlock(m_renderer, m_level_map);
	m_screenshake = false;
	m_background_yPos = 0.0f;
	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, 0.005f);
	CreateCoin(Vector2D(100, 330), FACING_LEFT, 0.002f);

	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/BackgroundMB.png")) {
		std::cout << "Failed to load background texture! " << std::endl;
		return false;
	}
	return true;
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e) {
	//screen shake
	if (m_screenshake) {
		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble);
		m_background_yPos *= 3.0f;
		if (m_shake_time <= 0.0f) {
			m_shake_time = false;
			m_background_yPos = 0.0f;
		}
	}
	spawnerFrameCount += 1;
	//update character
	if (spawnerFrameCount > 5000) {
		EnemySpawner();
		spawnerFrameCount = 0;
	}
	if (my_character->GetAlive()) {
		my_character->Update(deltaTime, e);
	}
	if (luigi->GetAlive()) {
		luigi->Update(deltaTime, e);
	}
	UpdateCoins(deltaTime, e);
	UpdateEnemies(deltaTime, e);
	UpdatePOWBlock();
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

void GameScreenLevel1::UpdatePOWBlock() {
	if (Collisions::Instance()->Box(my_character->GetCollisionBox(), m_pow_block->GetCollisionsBox())) {
		if (m_pow_block->IsAvailable()) {
			if (my_character->Is_Jumping()) {
				DoScreenshake();
				m_pow_block->TakeHit();
				my_character->CancelJump();
			}
		}
	}
	if (Collisions::Instance()->Box(luigi->GetCollisionBox(), m_pow_block->GetCollisionsBox())) {
		if (m_pow_block->IsAvailable()) {
			if (luigi->Is_Jumping()) {
				DoScreenshake();
				m_pow_block->TakeHit();
				luigi->CancelJump();
			}
		}
	}
}

void GameScreenLevel1::DoScreenshake() {
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;
	for (unsigned int i = 0; i < m_enemies.size(); i++) {
		m_enemies[i]->TakeDamage();
	}
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e){
	//need t  add mario hit code myself 

	if (!m_enemies.empty()){
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_enemies.size(); i++){
			//check if the enemy is on bottom row of tiles
			if (m_enemies[i]->GetPosition().y > 300.0f){
				//check if enemy is left/right
				if (m_enemies[i]->GetPosition().x < (float)(-m_enemies[i]->GetCollisionBox().width * 0.5f) || m_enemies[
					i]->GetPosition().x > SCREEN_WIDTH - (float)(m_enemies[i]->GetCollisionBox().width * 0.55f))
					m_enemies[i]->SetAlive(false);
			}

			m_enemies[i]->Update(deltaTime, e);

			if (Collisions::Instance()->Box(m_enemies[i]->GetCollisionBox(), my_character->GetCollisionBox())) {
				if (m_enemies[i]->GetInjured()) {
					m_enemies[i]->SetAlive(false);
				}
				else if (!m_enemies[i]->GetInjured() && my_character->Is_Jumping()) {
					m_enemies[i]->SetInjured(true);
				}
				else {
					if (my_character->mariocoins == 0) {
						my_character->SetAlive(false);
					}
					else {
						for (int i = 0; i < my_character->mariocoins; i++) {
							int facing_random = rand() % 1;
							int speed_random = (rand() % 100 + 1) / 100;
							if (facing_random == 0) {
								CreateCoin(my_character->GetPosition(), FACING_RIGHT, speed_random);
							}
							else if (facing_random == 1) {
								CreateCoin(my_character->GetPosition(), FACING_LEFT, speed_random);
							}
						}
					}
				}
			}
			if (Collisions::Instance()->Box(m_enemies[i]->GetCollisionBox(), luigi->GetCollisionBox())) {
				if (m_enemies[i]->GetInjured()) {
					m_enemies[i]->SetAlive(false);
				}
				else if (!m_enemies[i]->GetInjured() && luigi->Is_Jumping()) {
					m_enemies[i]->SetInjured(true);
				}
				else {
					if (luigi->luigicoins == 0) {
						luigi->SetAlive(false);
					}
					else {
						for (int i = 0; i < luigi->luigicoins; i++) {
							int facing_random = rand() % 1;
							int speed_random = (rand() % 100 + 1) / 100;
							if (facing_random == 0) {
								CreateCoin(luigi->GetPosition(), FACING_RIGHT, speed_random);
							}
							else if (facing_random == 1) {
								CreateCoin(luigi->GetPosition(), FACING_LEFT, speed_random);
							}
						}
					}
				}
			}

			////check if enemy collides with player
			//if ((m_enemies[i]->GetPosition().y > 300.0f || m_enemies[i]->GetPosition().y <= 64.0f) && (m_enemies[i]->
			//	GetPosition().x < 64.0f || m_enemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f)){
			//	//ignore collisions if behind pipe
			//}
			//else{
			//	if (Collisions::Instance()->Circle(m_enemies[i], my_character)){
			//		if (m_enemies[i]->GetInjured()){
			//			m_enemies[i]->SetAlive(false);
			//		}
			//		else{
			//			my_character->SetAlive(false);
			//		}
			//	}
			//	if (Collisions::Instance()->Circle(m_enemies[i], luigi)) {
			//		if (m_enemies[i]->GetInjured()) {
			//			m_enemies[i]->SetAlive(false);
			//		}
			//		else {
			//			luigi->SetAlive(false);
			//		}
			//	}

			if (!m_enemies[i]->GetAlive()){
				enemyIndexToDelete = i; //schedule dead enemies deletion
			}
		}

		if (enemyIndexToDelete != -1){
			m_enemies.erase(m_enemies.begin() + enemyIndexToDelete); // remove dead enemies
		}
		 
	}

}

void GameScreenLevel1::UpdateCoins(float deltaTime, SDL_Event e) {
	if (!m_coins.empty()) {
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_coins.size(); i++) {
			//check if the enemy is on bottom row of tiles
			if (m_coins[i]->GetPosition().y > 300.0f) {
				//check if enemy is left/right
				if (m_coins[i]->GetPosition().x < (float)(-m_coins[i]->GetCollisionBox().width * 0.5f) || m_coins[
					i]->GetPosition().x > SCREEN_WIDTH - (float)(m_coins[i]->GetCollisionBox().width * 0.55f))
					m_coins[i]->SetAlive(false);
			}
			m_coins[i]->Update(deltaTime, e);

			if (Collisions::Instance()->Circle(m_coins[i], my_character)) {	
				m_coins[i]->SetAlive(false);
			}
			if (Collisions::Instance()->Circle(m_coins[i], luigi)) {
				m_coins[i]->SetAlive(false);
			}
			if (!m_coins[i]->GetAlive()) {
				enemyIndexToDelete = i; //schedule dead enemies deletion
			}
		}

		if (enemyIndexToDelete != -1) {
			m_coins.erase(m_coins.begin() + enemyIndexToDelete); // remove dead enemies
		}

	}

}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed){
	koopa = new CharacterKoopa(m_renderer, "Images/Koopa.png", position, m_level_map, direction, speed);
	
	m_enemies.push_back(koopa);
}

void GameScreenLevel1::CreateCoin(Vector2D position, FACING direction, float speed){
	coin = new Coin(m_renderer, "Images/Coin.png", position, m_level_map, direction, speed);
	m_coins.push_back(coin);
}

void GameScreenLevel1::EnemySpawner(){
	int spawner = std::rand() % 2;
	int random = std::rand() % 100;

	switch (spawner) {
	case 0:
		if (random < 70) {
			CreateCoin(Vector2D(32, 30), FACING_RIGHT, 0.02f);
		}
		else {
			CreateKoopa(Vector2D(32, 30), FACING_RIGHT, 0.02f);
		}
		break;
	case 1:
		if (random < 70) {
			CreateCoin(Vector2D(480, 30), FACING_LEFT, 0.02f);
		}
		else {
			CreateKoopa(Vector2D(480, 30), FACING_LEFT, 0.02f);
		}
		break;
	}
}
