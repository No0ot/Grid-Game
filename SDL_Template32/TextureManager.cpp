#include "TextureManager.h"

#include <utility>

#include <fstream>
#include <sstream>
#include <iterator>

TextureManager* TextureManager::s_pInstance = 0;

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

inline bool TextureManager::m_exists(const std::string& id)
{
	return m_textureMap.find(id) != m_textureMap.end();
}

// LOADS TEXTURES AND ADDS TO LIST
bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer)
{
	if (m_exists(id))
	{
		return true;
	}

	const auto pTempSurface(Config::make_resource(IMG_Load(fileName.c_str())));


	if (pTempSurface == nullptr)
	{
		return false;
	}

	const auto pTexture(Config::make_resource(SDL_CreateTextureFromSurface(pRenderer, pTempSurface.get())));

	// everything went ok, add the texture to our list
	if (pTexture != nullptr)
	{
		m_textureMap[id] = pTexture;
		return true;
	}

	return false;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer,int state, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect dstRect;
	srcRect.x = 0 + (64 * state);
	srcRect.y = 0;
	srcRect.w = dstRect.w = width;
	srcRect.h = dstRect.h = height;
	dstRect.x = x;
	dstRect.y = y;
	SDL_RenderCopyEx(pRenderer, m_textureMap[id].get(), &srcRect, &dstRect, 0, 0, flip);
}

void TextureManager::draw(std::string id, int x, int y, SDL_Renderer* pRenderer,int state, bool centered, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect dstRect;

	srcRect.x = 0;
	srcRect.y = 0;

	int textureWidth, textureHeight;

	SDL_QueryTexture(m_textureMap[id].get(), NULL, NULL, &textureWidth, &textureHeight);

	srcRect.h = 31;
	dstRect.h = 62;
	srcRect.w = 31;
	dstRect.w = 62;
	dstRect.x = x;
	dstRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id].get(), &srcRect, &dstRect, 0, 0, flip);

}

void TextureManager::drawHex(std::string id, int x, int y, SDL_Renderer* pRenderer, int angle, int type,int hexstate, bool centered, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect dstRect;

	srcRect.x = 0 + 31 * type;
	srcRect.y = 0 + 31 * hexstate;

	srcRect.h = 31;
	dstRect.h = srcRect.h * 2;
	srcRect.w = 31;
	dstRect.w = srcRect.w * 2;
	dstRect.x = x;
	dstRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id].get(), &srcRect, &dstRect, angle, 0, flip);
}

void TextureManager::drawSelector(std::string id, int x, int y, SDL_Renderer* pRenderer, int angle, int state, bool centered, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect dstRect;

	srcRect.x = 0 + 29 * state;
	srcRect.y = 0;

	srcRect.h = 29;
	dstRect.h = srcRect.h * 2;
	srcRect.w = 29;
	dstRect.w = srcRect.w * 2;
	dstRect.x = x + 2;
	dstRect.y = y + 2;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id].get(), &srcRect, &dstRect, angle, 0, flip);
}

//ANGLES FOR HEX DIRECTIONS : 
//	UP = 0
//	UPRIGHT = 60
//	DOWNRIGHT = 120
//	DOWN = 180
//	DOWNLEFT = 240
//	UPLEFT = 300

void TextureManager::drawMerc(std::string id, int x, int y, SDL_Renderer* pRenderer, int angle, int state,int owner, bool centered, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect dstRect;

	srcRect.x = 0 + 21 * state;
	srcRect.y = 0 + 23 * owner;

	srcRect.h = 23;
	dstRect.h = srcRect.h * 2;
	srcRect.w = 21;
	dstRect.w = srcRect.w * 2;
	dstRect.x = x;
	dstRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id].get(), &srcRect, &dstRect, angle, 0, flip);
}

void TextureManager::drawUnitProfile(std::string id, int x, int y, SDL_Renderer* pRenderer, int angle, bool centered, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect dstRect;

	srcRect.x = 0;
	srcRect.y = 0;

	srcRect.h = 350;
	dstRect.h = srcRect.h / 2;
	srcRect.w = 500;
	dstRect.w = srcRect.w / 2;
	dstRect.x = x;
	dstRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id].get(), &srcRect, &dstRect, angle, 0, flip);
}

void TextureManager::drawText(const std::string& id, int x, int y, SDL_Renderer* renderer, double angle, int alpha, bool centered, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;

	int textureWidth, textureHeight;

	SDL_QueryTexture(m_textureMap[id].get(), nullptr, nullptr, &textureWidth, &textureHeight);

	srcRect.w = destRect.w = textureWidth;
	srcRect.h = destRect.h = textureHeight;

	if (centered) {
		const int xOffset = textureWidth * 0.5;
		const int yOffset = textureHeight * 0.5;
		destRect.x = x - xOffset;
		destRect.y = y - yOffset;
	}
	else {
		destRect.x = x;
		destRect.y = y;
	}

	SDL_SetTextureAlphaMod(m_textureMap[id].get(), alpha);
	SDL_RenderCopyEx(renderer, m_textureMap[id].get(), &srcRect, &destRect, angle, nullptr, flip);
}



glm::vec2 TextureManager::getTextureSize(std::string id)
{
	int width, height;
	SDL_QueryTexture(m_textureMap[id].get(), NULL, NULL, &width, &height);
	glm::vec2 size;
	size.x = width;
	size.y = height;

	return size;

}

bool TextureManager::addTexture(const std::string& id, std::shared_ptr<SDL_Texture> texture)
{
	if (m_exists(id))
	{
		return true;
	}

	m_textureMap[id] = std::move(texture);

	return true;
}

SDL_Texture* TextureManager::getTexture(const std::string& id)
{
	return m_textureMap[id].get();
}