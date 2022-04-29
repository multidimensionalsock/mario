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
	//call load font each time?
	m_textRect.x = x;
	m_textRect.y = y;
	SDL_RenderCopy(m_renderer, m_texture, nullptr, &m_textRect);

}

bool TextRenderer::LoadFont(std::string path, int font_size, std::string message)
{
	//do loading error catching 
	m_font = TTF_OpenFont(path.c_str(), font_size);
	SDL_Color white = { 255, 255, 255 };
	text_surface = TTF_RenderText_Solid(m_font, message.c_str(), white);
	SDL_CreateTextureFromSurface(m_renderer, text_surface);
	TTF_CloseFont(m_font);
	Free();

	SDL_QueryTexture(m_texture, nullptr, nullptr, &m_textRect.w, &m_textRect.h);
	return m_texture;
}

void TextRenderer::Free() {
	if (m_texture != nullptr) {
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
	}
}