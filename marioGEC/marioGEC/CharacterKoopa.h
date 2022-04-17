#pragma once
#include "Character.h"

class CharacterKoopa : public Character{
private: 
	float m_single_sprite_w;
	float m_single_sprite_h;
	bool m_injured;
	bool m_alive;

	void FlipRightWayUp();

public:
	CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map, FACING start_facing, float movement_speed);
	~CharacterKoopa();
	void TakeDamage();
	void Jump();
	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	bool GetInjured() { return m_injured; }
	void SetInjured(bool IsInjured) { m_injured = IsInjured; }
	bool GetAlive() { return m_alive;  }
	void SetAlive(bool isAlive) { m_alive = isAlive;  }
	Rect2D GetCollisionBox() { return Rect2D(m_position.x, m_position.y, (m_texture->GetWidth()), (m_texture->GetHeight())); }

};

