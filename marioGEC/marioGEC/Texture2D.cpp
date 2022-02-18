#include "Texture2D.h"
#include <SDL_image.h>
#include <iostream>
using namespace std;

Texture2D::Texture2D(SDL_Renderer* renderer) {
	m_renderer = renderer;

}

Texture2D::~Texture2D() {
	Free();

	m_renderer = nullptr;
}

bool Texture2D::LoadFromFile(std::string path) {

}

void Texture2D::Free() {
	if (m_texture != nullptr) {
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
		m_width = 0;
		m_height = 0;
	}
}

void Texture2D::Render(Vector2D new_position, SDL_RendererFlip flip, double angle) {

}
