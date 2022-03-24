#pragma once
#include "Character.h"

class Coin: public Character{
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;
	bool m_moving_left;
	bool m_moving_right;
	const bool m_jumping = false;
	const bool m_can_jump = false;
	const float m_jump_force = 0.0f;
	float m_collision_radius;
	FACING m_facing_direction;
	LevelMap* m_current_level_map;
	float m_movement_speed;
	bool m_alive;

	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);
	void AddGravity(float deltaTime);
	void Jump();

public: 
	Coin(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map, FACING direction);
	~Coin();
};

