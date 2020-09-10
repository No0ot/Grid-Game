#pragma once
//CORE LIBRARIES
#include <iostream>
#include <string>
#include <unordered_map>

#include "Config.h"
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

	void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer,int state, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void draw(std::string id, int x, int y, SDL_Renderer* pRenderer,int state, bool centered = false, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawHex(std::string id, int x, int y, SDL_Renderer* pRenderer, int angle, int type,int hexstate, bool centered = false, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawSelector(std::string id, int x, int y, SDL_Renderer* pRenderer, int angle, int state, bool centered = false, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawMerc(std::string id, int x, int y, SDL_Renderer* pRenderer, int angle, int state,int owner, bool centered = false, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawText(const std::string& id, int x, int y, SDL_Renderer* renderer, double angle, int alpha, bool centered = false, SDL_RendererFlip flip = SDL_FLIP_NONE);

	glm::vec2 getTextureSize(std::string id);

	bool addTexture(const std::string& id, std::shared_ptr<SDL_Texture> texture);
	SDL_Texture* getTexture(const std::string& id);


private:

	TextureManager();
	~TextureManager();

	bool m_exists(const std::string& id);
	std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> m_textureMap;

	static TextureManager* s_pInstance;
};

typedef TextureManager TheTextureManager;


