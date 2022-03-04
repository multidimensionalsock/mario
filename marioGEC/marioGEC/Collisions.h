#pragma once
#include "Commons.h"

class Character;

class Collisions{
public:
	~Collisions();
	static Collisions* Instance();
	bool Circle(Character* character1, Character* character2);
	bool Box(Rect2D rect1, Rect2D rect2);

private:
	Collisions();
	static Collisions* m_instance;
	//The static keyword states that only one of these variables will be created regardless of how many times you instantiate the Collisions class.
};