#pragma once

#include <SDL.h>
#include <lua.hpp>

namespace Game
{
	class InputManager
	{
	public:
		InputManager();

		void InitFrame();

		void HandleEvent(SDL_Event& e);

		bool GetMouseButton(int index);

		int GetMouseX();

		int GetMouseY();

		bool GetMouseEvent();

	public:
		static void RegisterWithLua(lua_State* L);

	private:
		bool m_mouseEvent = false;
		int m_mouseX;
		int m_mouseY;
		bool m_mouseButtons[3] = { false, false, false };
	};
}