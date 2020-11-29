#include "RenderComponent.h"
#include "TransformComponent.h"

#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>

RenderComponent::RenderComponent() {}
RenderComponent::RenderComponent(int w, int h) :
	m_w(w), m_h(h)
{
	m_rect.w = w;
	m_rect.h = h;
}

void RenderComponent::UpdateRect()
{
	int x = m_transform->GetX();
	int y = m_transform->GetY();
	
	m_rect.x = x - m_w / 2;
	m_rect.y = y - m_h / 2;
}

SDL_Rect RenderComponent::GetRect()
{
	return m_rect;
}

void RenderComponent::RegisterWithLua(lua_State* L)
{
}