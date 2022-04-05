#include "Coin.h"
#include "Constants.h"
#include "LevelMap.h"



Coin::Coin(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map, FACING start_facing, float movement_speed) : Character(renderer, imagePath, start_position, map) {
	m_facing_direction = start_facing;
	m_movement_speed = movement_speed;
	m_position = start_position;
	m_alive = true;

	m_single_sprite_w = m_texture->GetWidth() / 3;
	m_single_sprite_h = m_texture->GetHeight();
}

Coin::~Coin()
{
}


void Coin::Jump() {
	if (!m_jumping) {
		m_jump_force = INITIAL_JUMP_FORCE;
		m_jumping = true;
		m_can_jump = false;
	}
}

void Coin::Render() {
	int left = 0.0f; //left postion of sprite //left position of prite sheet
	SDL_Rect portion_of_sprite = { left, 0, m_single_sprite_w, m_single_sprite_h }; ///portion of sprite we want
	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h }; //where its to be drawn
	if (m_facing_direction == FACING_RIGHT) {
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
	}
	else {
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_HORIZONTAL);
	}


}

void Coin::Update(float deltaTime, SDL_Event e) {
	int centralX_position = (int)(m_position.x + (m_texture->GetWidth() * 0.5)) / TILE_WIDTH;
	int foot_position = (int)(m_position.y + m_texture->GetHeight()) / TILE_HEIGHT;
	if (m_current_level_map->GetTileAt(foot_position, centralX_position) == 0) {
		AddGravity(deltaTime);
	}
	Character::Update(deltaTime, e);
		if (m_moving_right) {
			m_position.x += m_movement_speed;
		}
		else {
			m_position.x -= m_movement_speed;
		}
}
