//#include <iostream>
//#include <string>
//#include <math.h>
//#include "TextureManager.h"
//#include "Game.h"
//
//
//const int FPS = 60;
//const int DELAY_TIME = 1000 / FPS;
//
//int main(int argc, char* args[]) // Main MUST have these parameters for SDL.
//{
//	Uint32 frameStart, frameTime;
//	Uint32 frames = 0;
//
//	TheGame::Instance()->init("Grid Game", 100, 100, 1040, 768, false);
//
//	while (TheGame::Instance()->running())
//	{
//		frameStart = SDL_GetTicks();
//
//		TheGame::Instance()->handleEvents();
//		TheGame::Instance()->update();
//		TheGame::Instance()->render();
//
//		frameTime = SDL_GetTicks() - frameStart;
//		if (frameTime < DELAY_TIME)
//		{
//			SDL_Delay((int)(DELAY_TIME - frameStart));
//		}
//
//		frames++;
//		TheGame::Instance()->setFrames(frames);
//	}
//
//	TheGame::Instance()->clean();
//
//	return 0;
//}

#include "Game.h"

int main(int argc, char* args[]) // Main MUST have these parameters for SDL.
{
	return Engine::Instance().Run();
}



