#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H
#include "GameScreen.h"
#include "Commons.h"
#include "Collisions.h"
#include <vector>
#include "CharacterKoopa.h"
#include "CharacterMario.h"

class Texture2D; //forward declaration
class Character;
class LevelMap;
class PowBlock;

class GameScreenLevel1 : GameScreen{
	private:
		Texture2D* m_background_texture;
		CharacterMario* my_character;
		//Character* luigi;
		CharacterKoopa* koopa;
		LevelMap* m_level_map;
		PowBlock* m_pow_block;
		bool m_screenshake;
		float m_shake_time;
		float m_wobble;
		float m_background_yPos;
		std::vector<CharacterKoopa*> m_enemies;

		bool SetUpLevel();
		void SetLevelMap(std::string path);
		void UpdatePOWBlock();
		void DoScreenshake();
		void UpdateEnemies(float deltaTime, SDL_Event e);
		void CreateKoopa(Vector2D position, FACING direction, float speed);

	public:
		GameScreenLevel1(SDL_Renderer* renderer);
		~GameScreenLevel1();

		void Render() override;
		void Update(float deltaTime, SDL_Event e) override;	
};

#endif

