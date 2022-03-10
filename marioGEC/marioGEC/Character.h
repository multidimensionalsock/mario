#pragma once
#ifndef _CHARACTER_H
#define _CHARACTER_H
#include <iostream>
#include "SDL.h"
#include "Commons.h"
#include <string>
#include "Texture2D.h"

class Texture2D;
class Character;
class LevelMap;

class Character{
	protected:
		SDL_Renderer* m_renderer;
		Vector2D m_position;
		Texture2D* m_texture;
		bool m_moving_left;
		bool m_moving_right;
		bool m_jumping;
		bool m_can_jump;
		float m_jump_force;
		float m_collision_radius;
		FACING m_facing_direction;
		LevelMap* m_current_level_map;
		float m_movement_speed;
		bool m_alive;

		virtual void MoveLeft(float deltaTime);
		virtual void MoveRight(float deltaTime);
		virtual void AddGravity(float deltaTime);
		virtual void Jump();

	public:
		Character(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map);
		~Character();

		virtual void Render();
		virtual void Update(float deltaTime, SDL_Event e);
		void SetPosition(Vector2D new_position);
		Vector2D GetPosition();
		float GetCollisionRadius();
		Rect2D GetCollisionBox() { return Rect2D(m_position.x, m_position.y, (m_texture->GetWidth()), (m_texture->GetHeight())); }
		bool Is_Jumping() { return m_jumping; }
		void CancelJump() { m_jumping = false; }
		bool GetAlive() { return m_alive; }
		void SetAlive(bool isAlive) { m_alive = isAlive;  }
};

#endif

