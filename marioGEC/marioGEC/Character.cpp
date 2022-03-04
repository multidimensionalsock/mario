#include "Character.h"
#include "Texture2D.h"
#include "Constants.h"

Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position) {
	m_renderer = renderer;
	m_position = start_position;
	m_texture = new Texture2D(renderer);
	m_facing_direction = FACING_RIGHT;
    m_moving_left = false;
    m_moving_right = false;
    m_collision_radius = 15.0f;

	if (!m_texture->LoadFromFile(imagePath)) {
		std::cout << "Failed to load background texture! " << std::endl;
	}
}

Character::~Character() {
	m_renderer = nullptr;
}

void Character::Render() {
	if (m_facing_direction == FACING_RIGHT) {
		m_texture->Render(m_position, SDL_FLIP_NONE);
	}
	else {
		m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
	}
};

void Character::Update(float deltaTime, SDL_Event e) {
    AddGravity(deltaTime);
    if (m_jumping) {
        m_position.y -= m_jump_force * deltaTime;
        m_jump_force -= JUMP_FORCE_DECREMENT * deltaTime;
        

        if (m_jump_force <= 0.0f)
            m_jumping = false;
    }

    if (m_moving_left) {
        MoveLeft(deltaTime);
    }
    if (m_moving_right) {
        MoveRight(deltaTime);
    }

    switch (e.type) {
    case SDL_KEYDOWN:
        switch (e.key.keysym.sym) {
        case SDLK_LEFT:
            m_moving_left = true;
            break;

        case SDLK_RIGHT:
            m_moving_right = true;
            break;
        case SDLK_SPACE:
            if (m_can_jump) {
                Jump();
            }
        }
        break;
    case SDL_KEYUP:
        switch (e.key.keysym.sym) {
        case SDLK_LEFT:
            m_moving_left = false;
            break;

        case SDLK_RIGHT:
            m_moving_right = false;
            break;
        }
        break;
    }
};

void Character::SetPosition(Vector2D new_position) {
	m_position = new_position;
}
Vector2D Character::GetPosition() { return m_position; }

void Character::MoveLeft(float deltaTime) {
    m_position.x -= deltaTime * MOVEMENTSPEED;
    m_facing_direction = FACING_LEFT;
}

void Character::MoveRight(float deltaTime) {
    m_position.x += deltaTime * MOVEMENTSPEED;
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
    std::cout << m_jump_force <<std::endl;
    if (!m_jumping) {
        m_jump_force = INITIAL_JUMP_FORCE;
        m_jumping = true;
        m_can_jump = false;
    }
    std::cout << m_jump_force << std::endl;
}

float Character::GetCollisionRadius() {
    return m_collision_radius;
}

//Rect2D Character::GetCollisionBox() {
//    return Rect2D(m_position.x, m_position.y,
//        (m_texture->GetWidth()), (m_texture->GetHeight()));
//}