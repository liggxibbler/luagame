#include "TransformComponent.h"

#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>

TransformComponent::TransformComponent()
{
}

float TransformComponent::GetX()
{
	return m_x;
}
float TransformComponent::GetY()
{
	return m_y;
}

void TransformComponent::SetX(float x)
{
	m_x = x;
}
void TransformComponent::SetY(float y)
{
	m_y = y;
}

void TransformComponent::RegisterWithLua(lua_State* L)
{
	luabridge::getGlobalNamespace(L)
		.beginNamespace("Game")
			.beginClass<TransformComponent>("Transform")
				.addFunction("GetX", &TransformComponent::GetX)
				.addFunction("GetY", &TransformComponent::GetY)
				.addFunction("SetX", &TransformComponent::SetX)
				.addFunction("SetY", &TransformComponent::SetY)
			.endClass()
		.endNamespace();
}