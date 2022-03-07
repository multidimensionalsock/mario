#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H
#include "GameScreen.h"
#include "Commons.h"
#include "Collisions.h"

class Texture2D; //forward declaration
class Character;
class LevelMap;
class PowBlock;

class GameScreenLevel1 : GameScreen{
	private:
		Texture2D* m_background_texture;
		Character* my_character;
		//Character* luigi;
		LevelMap* m_level_map;
		PowBlock* m_pow_block;


		bool SetUpLevel();
		void SetLevelMap();
		void UpdatePOWBlock();

	public:
		GameScreenLevel1(SDL_Renderer* renderer);
		~GameScreenLevel1();

		void Render() override;
		void Update(float deltaTime, SDL_Event e) override;	
};

#endif

