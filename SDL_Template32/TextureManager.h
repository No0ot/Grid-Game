#pragma once
//CORE LIBRARIES
#include <iostream>
#include <string>
#include <map>


#include <glm/vec2.hpp>

//SDL LIBRARIES
#include <SDL.h>
#include <SDL_image.h>

class TextureManager
{
public:
	static TextureManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new TextureManager();
			return s_pInstance;
		}

		return s_pInstance;
	}
	bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);

	void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void draw(std::string id, int x, int y, SDL_Renderer* pRenderer, bool centered = false, SDL_RendererFlip flip = SDL_FLIP_NONE);

	glm::vec2 getTextureSize(std::string id);


private:

	TextureManager();
	~TextureManager();

	std::map<std::string, SDL_Texture*> m_textureMap;

	static TextureManager* s_pInstance;
};

typedef TextureManager TheTextureManager;


