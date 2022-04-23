#include "GameScreenLevel2.h"
#include <iostream>
#include <fstream>
#include "Texture2D.h"
#include "Character.h"
#include "LevelMap.h"
#include "PowBlock.h"
#include "Collisions.h"

GameScreenLevel2::GameScreenLevel2(SDL_Renderer * renderer) : GameScreen(renderer) {
	SetUpLevel();
	spawnerFrameCount = 0;
	std::cout << "gamescreenl2 created";
}

GameScreenLevel2::~GameScreenLevel2() {
	m_background_texture = nullptr;
	delete mario;
	mario = nullptr;
	m_level_map = nullptr;
	m_pow_block = nullptr;

	m_enemies.clear();
}

void GameScreenLevel2::Render() {
	//draw background
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);
	if (mario->GetAlive()) {
		mario->Render();
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

bool GameScreenLevel2::SetUpLevel() {
	SetLevelMap();

	mario = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(40, 330), m_level_map);
	luigi = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(140, 330), m_level_map);
	m_pow_block = new PowBlock(m_renderer, m_level_map);
	m_screenshake = false;
	m_background_yPos = 0.0f;
	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, 0.005f);
	CreateCoin(Vector2D(100, 330), FACING_LEFT, 0.002f);

	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/Level2Background.png")) {
		std::cout << "Failed to load background texture! " << std::endl;
		return false;
	}
	return true;
}

void GameScreenLevel2::Update(float deltaTime, SDL_Event e) {
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
	if (mario->GetAlive()) {
		mario->Update(deltaTime, e);
	}
	if (luigi->GetAlive()) {
		luigi->Update(deltaTime, e);
	}
	UpdateCoins(deltaTime, e);
	UpdateEnemies(deltaTime, e);
	UpdatePOWBlock();
}

void GameScreenLevel2::SetLevelMap() {
	int map[MAP_HEIGHT][MAP_WIDTH];
	std::ifstream inFile;
	inFile.open("Levels/Level2.txt");

	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			int temp = 0;
			inFile >> temp;
			map[i][j] = temp;
		}
	}
	//clear any old maps
	if (m_level_map != nullptr) {
		delete m_level_map;
	}
	//set new one
	m_level_map = new LevelMap(map);
}

void GameScreenLevel2::UpdatePOWBlock() {
	if (Collisions::Instance()->Box(mario->GetCollisionBox(), m_pow_block->GetCollisionsBox())) {
		if (m_pow_block->IsAvailable()) {
			if (mario->Is_Jumping()) {
				DoScreenshake();
				m_pow_block->TakeHit();
				mario->CancelJump();
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

void GameScreenLevel2::DoScreenshake() {
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;
	for (unsigned int i = 0; i < m_enemies.size(); i++) {
		m_enemies[i]->TakeDamage();
	}
}

void GameScreenLevel2::UpdateEnemies(float deltaTime, SDL_Event e) {
	//need t  add mario hit code myself 

	if (!m_enemies.empty()) {
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_enemies.size(); i++) {
			//check if the enemy is on bottom row of tiles
			if (m_enemies[i]->GetPosition().y > 300.0f) {
				//check if enemy is left/right
				if (m_enemies[i]->GetPosition().x < (float)(-m_enemies[i]->GetCollisionBox().width * 0.5f) || m_enemies[
					i]->GetPosition().x > SCREEN_WIDTH - (float)(m_enemies[i]->GetCollisionBox().width * 0.55f))
					m_enemies[i]->SetAlive(false);
			}

			m_enemies[i]->Update(deltaTime, e);

			if (mario->GetAlive() != false) {
				if (Collisions::Instance()->Box(m_enemies[i]->GetCollisionBox(), mario->GetCollisionBox())) {
					std::cout << "koopa collision mario";
					if (m_enemies[i]->GetInjured()) {
						m_enemies[i]->SetAlive(false);
					}
					else if (!m_enemies[i]->GetInjured() && mario->Is_Jumping()) {
						m_enemies[i]->SetInjured(true);
					}
					else {
						if (mario->mariocoins == 0) {
							mario->SetAlive(false);
							mario_death = true;
						}
						else {
							mario->SetInjured(true);
							for (int i = 0; i < mario->mariocoins; i++) {
								CoinSpawner();
							}
							mario->mariocoins = 0;
						}
					}
				}
			}
			if (luigi->GetAlive() != false) {
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
							luigi_death = true;
						}
						else {
							luigi->SetInjured(true);
							for (int i = 0; i < luigi->luigicoins; i++) {
								CoinSpawner();
							}
							luigi->luigicoins = 0;
						}
					}
				}
			}

			if (!m_enemies[i]->GetAlive()) {
				enemyIndexToDelete = i; //schedule dead enemies deletion
			}
		}

		if (enemyIndexToDelete != -1) {
			m_enemies.erase(m_enemies.begin() + enemyIndexToDelete); // remove dead enemies
		}

	}

}

void GameScreenLevel2::UpdateCoins(float deltaTime, SDL_Event e) {
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

			if (mario->GetInjured() == false && mario->GetAlive() == true) {
				if (Collisions::Instance()->Circle(m_coins[i], mario)) {
					m_coins[i]->SetAlive(false);
					mario->mariocoins++;
				}
			}
			if (luigi->GetInjured() == false && luigi->GetAlive() == true) {
				if (Collisions::Instance()->Circle(m_coins[i], luigi)) {
					m_coins[i]->SetAlive(false);
					luigi->luigicoins++;
				}
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

void GameScreenLevel2::CreateKoopa(Vector2D position, FACING direction, float speed) {
	koopa = new CharacterKoopa(m_renderer, "Images/Koopa.png", position, m_level_map, direction, speed);

	m_enemies.push_back(koopa);
}

void GameScreenLevel2::CreateCoin(Vector2D position, FACING direction, float speed) {
	coin = new Coin(m_renderer, "Images/Coin.png", position, m_level_map, direction, speed);
	m_coins.push_back(coin);
}

void GameScreenLevel2::EnemySpawner() {
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

void GameScreenLevel2::CoinSpawner() {
	int spawner = std::rand() % 3;
	Vector2D coinPos;

	switch (spawner) {
	case 0:
		//coin from top
		coinPos.x = rand() % 513;
		coinPos.y = 0;
		//if x is bigger or equal to centre pick direction based on
		if (coinPos.x > 261) {
			CreateCoin(coinPos, FACING_RIGHT, 0.02f);
		}
		else {
			CreateCoin(coinPos, FACING_LEFT, 0.02f);
		}
		break;
	case 1:
		//coin from left
		coinPos.x = 0;
		coinPos.y = rand() % 385;
		CreateCoin(coinPos, FACING_RIGHT, 0.02f);
		break;
	case 2:
		//coin from right
		coinPos.x = 512;
		coinPos.y = rand() % 385;
		CreateCoin(coinPos, FACING_LEFT, 0.02f);
	}
}