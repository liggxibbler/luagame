#include "RenderManager.h"
#include "RenderComponent.h"

namespace Game
{
	void RenderManager::Initialize()
	{
		// Half-assedly intialize SDL
		SDL_Init(SDL_INIT_VIDEO);
		m_sdlWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		m_sdlSurface = SDL_GetWindowSurface(m_sdlWindow);
		m_sdlRenderer = SDL_CreateRenderer(m_sdlWindow, -1, 0);
	}

	void RenderManager::Render()
	{
		SDL_SetRenderDrawColor(m_sdlRenderer, 0, 0, 0, 255);
		SDL_RenderClear(m_sdlRenderer);
		SDL_SetRenderDrawColor(m_sdlRenderer, 255, 0, 0, 255);

		for (auto iter = m_objects.begin(); iter != m_objects.end(); ++iter)
		{
			auto rect = (*iter)->GetRect();

			SDL_RenderFillRect(m_sdlRenderer, &rect);
		}

		SDL_RenderPresent(m_sdlRenderer);
	}

	void RenderManager::AddRenderComponent(RenderComponent* render)
	{
		m_objects.push_back(render);
	}

	void RenderManager::RemoveRenderComponent(RenderComponent* render)
	{

	}

	void RenderManager::UpdateSurface()
	{
		SDL_UpdateWindowSurface(m_sdlWindow);
	}
}