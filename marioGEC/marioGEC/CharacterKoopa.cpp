#include "CharacterKoopa.h"
#include "Constants.h"
#include "LevelMap.h"

void CharacterKoopa::FlipRightWayUp(){
	if (m_facing_direction == FACING_RIGHT) {
		m_facing_direction = FACING_LEFT;
	}
	else if (m_facing_direction == FACING_LEFT) {
		m_facing_direction = FACING_RIGHT;
	}
	m_injured = false;
}

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map, FACING start_facing, float movement_speed) : Character(renderer, imagePath, start_position, map){
	m_facing_direction = start_facing;
	m_movement_speed = movement_speed;
	m_position = start_position;
	m_alive = true;
	m_current_level_map = map;
	
	m_single_sprite_w = m_texture->GetWidth() /2;
	m_single_sprite_h = m_texture->GetHeight();
}

CharacterKoopa::~CharacterKoopa()
{
}

void CharacterKoopa::TakeDamage(){
	m_injured = true;
	m_injured_time = 2.5f;
	Jump();
}

void CharacterKoopa::Jump(){
	if (!m_jumping) {
		m_jump_force = INITIAL_JUMP_FORCE;
		m_jumping = true;
		m_can_jump = false;
	}
}

void CharacterKoopa::Render(){
	int left = 0.0f; //left postion of sprite
	if (m_injured)
		left = m_single_sprite_w; //left position of prite sheet
	SDL_Rect portion_of_sprite = { left, 0, m_single_sprite_w, m_single_sprite_h }; ///portion of sprite we want
	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h }; //where its to be drawn
	if (m_facing_direction == FACING_RIGHT) {
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
	}
	else {
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_HORIZONTAL);
	}


}

void CharacterKoopa::Update(float deltaTime, SDL_Event e){
	int centralX_position = (int)(m_position.x + (m_texture->GetWidth() * 0.5)) / TILE_WIDTH;
	int foot_position = (int)(m_position.y + m_texture->GetHeight()) / TILE_HEIGHT;
	if (m_current_level_map->GetTileAt(foot_position, centralX_position) == 0) {
		AddGravity(deltaTime);
	}
	Character::Update(deltaTime, e);
	if (!m_injured) {
		
		if (m_facing_direction == FACING_LEFT) {
			m_moving_left = true;
			m_moving_right = false;
		}
		else if (m_facing_direction == FACING_RIGHT) {
			m_moving_right = true;
			m_moving_left = false;
		}
		else {
			//cant move while injured
			m_moving_right = false;
			m_moving_left = false;

			m_injured_time -= deltaTime;

			if (m_injured_time <= 0.0) {
				FlipRightWayUp();
			}
		}
		if (m_moving_right) {
			m_position.x += deltaTime * m_movement_speed;
		}
		else {
			m_position.x -= deltaTime * m_movement_speed;
		}
	}
	if (m_position.x <= 0) {
		m_facing_direction = FACING_RIGHT;
	}
	else if (m_position.x >= 512) {
		m_facing_direction = FACING_LEFT;
	}
}
