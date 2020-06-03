#include "TextureManager.h"

TextureManager* TextureManager::s_pInstance = 0;

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}
// LOADS TEXTURES AND ADDS TO LIST
bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer)
{
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());

	if (pTempSurface == 0)
	{
		return false;
	}
	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

	SDL_FreeSurface(pTempSurface);

	
	if (pTexture != 0)
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
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &dstRect, 0, 0, flip);
}

void TextureManager::draw(std::string id, int x, int y, SDL_Renderer* pRenderer,int state, bool centered, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect dstRect;

	srcRect.x = 0 + 64 * state;
	srcRect.y = 0;

	int textureWidth, textureHeight;

	SDL_QueryTexture(m_textureMap[id], NULL, NULL, &textureWidth, &textureHeight);

	srcRect.w = dstRect.w = textureWidth;
	srcRect.h = dstRect.h = textureHeight;
	dstRect.x = x;
	dstRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &dstRect, 0, 0, flip);

}



glm::vec2 TextureManager::getTextureSize(std::string id)
{
	int width, height;
	SDL_QueryTexture(m_textureMap[id], NULL, NULL, &width, &height);
	glm::vec2 size;
	size.x = width;
	size.y = height;

	return size;

}