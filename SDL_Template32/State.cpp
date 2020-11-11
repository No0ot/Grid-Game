#include "State.h"
#include "Engine.h"

void State::Render()
{
	SDL_RenderPresent(Engine::Instance().GetRenderer());
}

void State::HandleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT: // User pressed window's 'x' button.
			Engine::Instance().QuitGame();
			break;
		case SDL_KEYDOWN: // Try SDL_KEYUP instead.
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				Engine::Instance().QuitGame();
				break;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (!mouseDown) {
				if (event.button.button >= 1 && event.button.button <= 3) {
					Engine::Instance().SetMouseState(event.button.button - 1, true);
					mouseDown = true;
				}
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button >= 1 && event.button.button <= 3) {
				Engine::Instance().SetMouseState(event.button.button - 1, false);
				mouseDown = false;
			}
			break;
		case SDL_MOUSEMOTION:
			SDL_GetMouseState(&Engine::Instance().GetMousePos().x, &Engine::Instance().GetMousePos().y);
			break;
		}
	}
}

void State::Resume() {}
// End State.