

#ifndef SCREEN_TEXT_H_
#define SCREEN_TEXT_H_

#include "LTexture.hpp"


class ScreenText
{
public:
	ScreenText(SDL_Renderer * renderer) {
		m_texture = new LTexture(renderer);
	}
	~ScreenText() {
		m_texture->free();
		delete m_texture;
	}

	int screenPositionX = 0;
	int screenPositionY = 0;
	std::string text;

	LTexture* m_texture;
};

#endif //End def SCREEN_TEXT
