#include "RenderComponent.h"
#include "TransformComponent.h"
#include "Entity.h"

#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>

RenderComponent::RenderComponent() {}
RenderComponent::RenderComponent(int w, int h, Uint8 r, Uint8 g, Uint8 b)
{
	m_rect.w = w;
	m_rect.h = h;
	m_color = SDL_Color{ r, g, b };
}

ECS::ComponentType RenderComponent::GetType()
{
	return ECS::ComponentType_Render;
}

void RenderComponent::UpdateRect()
{
	auto pos = GetEntity()->GetPosition();
	
	m_rect.x = pos.x - m_rect.w / 2;
	m_rect.y = pos.y - m_rect.h / 2;
}

SDL_Rect RenderComponent::GetRect()
{
	return m_rect;
}

SDL_Color RenderComponent::GetColor()
{
	return m_color;
}

void RenderComponent::RegisterWithLua(lua_State* L)
{
	luabridge::getGlobalNamespace(L)
		.beginNamespace("Game")
			.deriveClass<RenderComponent, Component>("RenderComponent")
				.addConstructor<void (*)(int, int, Uint8, Uint8, Uint8)>()
			.endClass()
		.endNamespace();
}