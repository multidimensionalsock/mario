#include "TextRenderer.h"

TextRenderer::TextRenderer(SDL_Renderer* renderer)
{
	m_renderer = renderer;
}

TextRenderer::~TextRenderer()
{
	m_renderer = nullptr;
}

void TextRenderer::Render(int x, int y)
{
	m_textRect.x = x;
	m_textRect.y = y;
	SDL_RenderCopy(m_renderer, m_texture, nullptr, &m_textRect);

}

bool TextRenderer::LoadFont(const std::string path, int font_size, std::string message, SDL_Colour text_colour)
{
	m_font = TTF_OpenFont(path, font_size)
	return false;
}
