#include "Character.h"
#include "Texture2D.h"

Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position) {
	m_renderer = renderer;
	m_position = start_position;
	m_texture = new Texture2D(renderer);
	m_facing_direction = FACING_RIGHT;

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
    SDL_PollEvent(&e);

    switch (e.type) {
    case SDL_KEYDOWN:
        switch (e.key.keysym.sym){
        case SDLK_LEFT:
            m_position.x -= 1;
            m_facing_direction = FACING_LEFT;
            break;

        case SDLK_RIGHT:
            m_position.x += 1;
            m_facing_direction = FACING_RIGHT;
            break;

        default:
            break;
        }
    break;
    }
};

void Character::SetPosition(Vector2D new_position) {
	m_position = new_position;
}
Vector2D Character::GetPosition() { return m_position; }
