#include "InputManager.h"
#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>

#include <iostream>

namespace Game
{
	InputManager::InputManager() {}

	void InputManager::InitFrame()
	{
		m_mouseEvent = false;
	}

	void InputManager::HandleEvent(SDL_Event& e)
	{
		if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
		{
			m_mouseEvent = true;
			auto buttons = SDL_GetMouseState(&m_mouseX, &m_mouseY);
			m_mouseButtons[0] = SDL_BUTTON_LMASK & buttons;
			m_mouseButtons[1] = SDL_BUTTON_MMASK & buttons;
			m_mouseButtons[2] = SDL_BUTTON_RMASK & buttons;
		}	
	}

	bool InputManager::GetMouseButton(int index)
	{
		return m_mouseButtons[index];
	}

	int InputManager::GetMouseX()
	{
		return m_mouseX;
	}

	int InputManager::GetMouseY()
	{
		return m_mouseY;
	}

	bool InputManager::GetMouseEvent()
	{
		return m_mouseEvent;
	}

	void InputManager::RegisterWithLua(lua_State* L)
	{
		luabridge::getGlobalNamespace(L)
			.beginNamespace("Game")
				.beginClass<InputManager>("InputManager")
					.addFunction("GetMouseButton", &InputManager::GetMouseButton)
					.addFunction("GetMouseX", &InputManager::GetMouseX)
					.addFunction("GetMouseY", &InputManager::GetMouseY)
					.addFunction("GetMouseEvent", &InputManager::GetMouseEvent)
				.endClass()
			.endNamespace();
	}
}