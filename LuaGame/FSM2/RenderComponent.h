#pragma once

#include "Component.h"
#include <SDL.h>

class TransformComponent;

class RenderComponent : public ECS::Component
{
public:
	RenderComponent();
	RenderComponent(int w, int h, Uint8 r, Uint8 g, Uint8 b);

	void UpdateRect();

	SDL_Rect GetRect();
	SDL_Color GetColor();
public:
	static void RegisterWithLua(lua_State* L);
private:	
	TransformComponent* m_transform;
	SDL_Rect m_rect;
	SDL_Color m_color;
};