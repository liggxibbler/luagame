#pragma once

#define SCREEN_WIDTH 320 * 2
#define SCREEN_HEIGHT 240 * 2

#include <vector>
#include <SDL.h>

#include "RenderComponent.h"

namespace Game
{
	class RenderManager
	{
	public:
		void Initialize();

		void Render();

		void AddRenderComponent(RenderComponent* render);
		void RemoveRenderComponent(RenderComponent* render);
		void UpdateSurface();

	private:
		SDL_Window* m_sdlWindow = nullptr;
		SDL_Renderer* m_sdlRenderer = nullptr;
		SDL_Surface* m_sdlSurface = nullptr;
		std::vector<RenderComponent*> m_objects;

	public:
		static void RegisterWithLua(lua_State* L);
	};
}