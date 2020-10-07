#pragma once
#ifndef __FONT_MANAGER__
#define __FONT_MANAGER__

// Core Libraries
#include <iostream>
#include <string>
#include <unordered_map>

// SDL Libraries
#include<SDL.h>
#include<SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "Config.h"

class FontManager 
{
public:
	static FontManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new FontManager();
			return s_pInstance;
		}

		return s_pInstance;
	}

	bool load(const std::string& file_name, const std::string& id, int size, int style = TTF_STYLE_NORMAL);
	bool textToTexture(const std::string& text, const std::string& font_id, const std::string& texture_id, SDL_Color colour = { 0, 0, 0, 255 });
	TTF_Font* getFont(const std::string& id);
	void clean();

	void displayFontMap();

	// Define Custom Deleters for shared_ptr types
	static void SDL_DelRes(SDL_Window* r) { SDL_DestroyWindow(r); }
	static void SDL_DelRes(SDL_Renderer* r) { SDL_DestroyRenderer(r); }
	static void SDL_DelRes(SDL_Texture* r) { SDL_DestroyTexture(r); }
	static void SDL_DelRes(SDL_Surface* r) { SDL_FreeSurface(r); }
	static void SDL_DelRes(TTF_Font* r) { TTF_CloseFont(r); }

	// template function to create and return shared_ptr instance
	template <typename T>
	static std::shared_ptr<T> make_resource(T* t) {
		return std::shared_ptr<T>(t, [](T* t) { Config::SDL_DelRes(t); });
	}

private:
	FontManager();
	~FontManager();

	bool m_exists(const std::string& id);

	std::unordered_map<std::string, std::shared_ptr<TTF_Font>> m_fontMap;

	static FontManager* s_pInstance;
	
};


#endif /* defined(__FONT_MANAGER__) */
