#pragma once
#include "Character.h"

class CharacterMario : public Character{
	private:
		float m_single_sprite_w;
		float m_single_sprite_h;
		bool m_alive;

	public:
		int mariocoins;

		CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map);
		~CharacterMario();
		void TakeDamage();
		void Jump();
		void Render() override;
		virtual void Update(float deltaTime, SDL_Event e) override;
		void AddGravity(float deltaTime) override;
		Rect2D GetCollisionBox() { return Rect2D(m_position.x, m_position.y, (m_texture->GetWidth()), (m_texture->GetHeight())); }
};

