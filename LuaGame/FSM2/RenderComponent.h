#pragma once

#include "Component.h"
#include <SDL.h>

class TransformComponent;
struct lua_State;

class RenderComponent : public ECS::Component
{
public:
	RenderComponent();
	RenderComponent(int w, int h);

	void UpdateRect();

	SDL_Rect GetRect();
public:
	static void RegisterWithLua(lua_State* L);
private:
	int m_w;
	int m_h;
	TransformComponent* m_transform;
	SDL_Rect m_rect;
};