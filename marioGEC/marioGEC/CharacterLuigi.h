#pragma once
#include "Character.h"

class CharacterLuigi : public Character {
private:
	float m_single_sprite_w;
	float m_single_sprite_h;
	bool m_alive;

public:
	CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map);
	~CharacterLuigi();
	void TakeDamage();
	void Jump();
	void Render() override;
	virtual void Update(float deltaTime, SDL_Event e) override;
	void AddGravity(float deltaTime) override;
	Rect2D GetCollisionBox() { return Rect2D(m_position.x, m_position.y, (m_texture->GetWidth()), (m_texture->GetHeight())); }
};

