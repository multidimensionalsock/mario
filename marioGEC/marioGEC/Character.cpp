#include "Character.h"
#include "Texture2D.h"
#include "Constants.h"
#include "LevelMap.h"

Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map) {
	m_renderer = renderer;
	m_position = start_position;
	m_texture = new Texture2D(renderer);
	m_facing_direction = FACING_RIGHT;
    m_moving_left = false;
    m_moving_right = false;
    m_collision_radius = 15.0f;
    m_current_level_map = map;
    m_movement_speed = 75.0f;
    m_alive = true;
    m_injured_time = 1000.0f;
    m_injured = false;

	if (!m_texture->LoadFromFile(imagePath)) {
		std::cout << "Failed to load background texture! " << std::endl;
	}
}

Character::~Character() {
	m_renderer = nullptr;
}

void Character::Render() {
};

void Character::Update(float deltaTime, SDL_Event e) {
};

void Character::SetPosition(Vector2D new_position) {
	m_position = new_position;
}
Vector2D Character::GetPosition() { return m_position; }

void Character::MoveLeft(float deltaTime) {
    m_position.x -= deltaTime * m_movement_speed;
    m_facing_direction = FACING_LEFT;
}

void Character::MoveRight(float deltaTime) {
    m_position.x += deltaTime * m_movement_speed;
    m_facing_direction = FACING_RIGHT;
}

void Character::AddGravity(float deltaTime) {
    if ((m_position.y + 64) <= SCREEN_HEIGHT) {
        m_position.y += GRAVITY;
    }
    else {
        m_can_jump = true;
    }
}

void Character::Jump() {
}

float Character::GetCollisionRadius() {
    return m_collision_radius;
}

