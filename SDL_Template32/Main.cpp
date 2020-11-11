#include "Engine.h"
#include "TextureManager.h"

int main(int argc, char* args[]) // Main MUST have these parameters for SDL.
{
	
		if (Engine::Instance().Init("Grid Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1260, 800, 0) == false)
			return 1;
		while (Engine::Instance().m_bRunning)
		{
			Engine::Instance().Wake();
			Engine::Instance().HandleEvents();
			Engine::Instance().Update();
			Engine::Instance().Render();
			if (Engine::Instance().m_bRunning)
				Engine::Instance().Sleep();
		}
		Engine::Instance().Clean();
		return 0;
	
}



