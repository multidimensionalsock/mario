#pragma once
#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H
#include "SDL.h";

class GameScreen{
protected:
	bool mario_death=false;
	bool luigi_death=false;

public:
	SDL_Renderer* m_renderer;

	GameScreen(SDL_Renderer* renderer);
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	bool marioDeathGet() { return mario_death; }
	bool luigiDeathGet() { return luigi_death; }
};

#endif

