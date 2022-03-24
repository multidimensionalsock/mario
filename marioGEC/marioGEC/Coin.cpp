#include "Coin.h"

void Coin::MoveLeft(float deltaTime)
{
}

void Coin::MoveRight(float deltaTime)
{
}

void Coin::AddGravity(float deltaTime)
{
}

void Coin::Jump()
{
}

Coin::Coin(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map, FACING direction) : Character(renderer, imagePath, start_position, map)
{
	Texture2D* m_texture;
	bool m_moving_left;
	bool m_moving_right;
	float m_collision_radius;
	FACING m_facing_direction = direction;
	float m_movement_speed = 0.01f;
	bool m_alive = true;
}

Coin::~Coin()
{

}
