#pragma once
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

class TextRenderer{
public:
	TextRenderer(SDL_Renderer* renderer);
	~TextRenderer();
	void Render(int x, int y);
	void Free();
	bool LoadFont(std::string path, int font_size, std::string message, SDL_Colour text_colour);

private:
	SDL_Renderer* m_renderer;
	SDL_Texture* m_texture;
	SDL_Rect m_textRect;
	TTF_Font* m_font;
	SDL_Surface*	text_surface;
};

