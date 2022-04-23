#include "CharacterMario.h"
#include "Constants.h"
#include "Texture2D.h"
#include "LevelMap.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map) : Character(renderer, imagePath, start_position, map) {
    mariocoins = 0;
    m_alive = true;
}
CharacterMario::~CharacterMario() {
    m_renderer = nullptr;
}

void CharacterMario::Update(float deltaTime, SDL_Event e) {
    //collision position variables
    int centralX_position = (int)(m_position.x + (m_texture->GetWidth() * 0.5)) / TILE_WIDTH;
    int foot_position = (int)(m_position.y + m_texture->GetHeight()) / TILE_HEIGHT;
    if (m_current_level_map->GetTileAt(foot_position, centralX_position) <= 0) {
        AddGravity(deltaTime);
    }
    else {
        m_can_jump = true;
    }


    if (m_jumping) {
        m_position.y -= m_jump_force * 0.00055;
        m_jump_force -= JUMP_FORCE_DECREMENT;// *0.0001;


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
        case SDLK_UP:
            if (m_can_jump) {
                Jump();
            }
            break;
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
    if (m_injured) {
        m_injured_time -= deltaTime;

        if (m_injured_time <= 0.0) {
            m_injured = false;
        }
    }
}
void CharacterMario::AddGravity(float deltaTime)
{
    if ((m_position.y + 64) <= SCREEN_HEIGHT) {
        m_position.y += GRAVITY;
    }
    else {
        m_can_jump = true;
    }
}
;

void CharacterMario::Render() {
    if (m_facing_direction == FACING_RIGHT) {
        m_texture->Render(m_position, SDL_FLIP_NONE);
    }
    else {
        m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
    }
};

void CharacterMario::Jump() {
    std::cout << m_jump_force << std::endl;
    if (!m_jumping) {
        m_jump_force = INITIAL_JUMP_FORCE;
        m_jumping = true;
        m_can_jump = false;
    }
    std::cout << m_jump_force << std::endl;
}

