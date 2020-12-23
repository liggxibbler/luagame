#pragma once

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

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

		Vector2 GetScreenSize();
		void SetScreenSize(int w, int h);

	private:
		SDL_Window* m_sdlWindow = nullptr;
		SDL_Renderer* m_sdlRenderer = nullptr;
		SDL_Surface* m_sdlSurface = nullptr;
		std::vector<RenderComponent*> m_objects;
		int m_width = 320;
		int m_height = 240;

	public:
		static void RegisterWithLua(lua_State* L);
	};
}