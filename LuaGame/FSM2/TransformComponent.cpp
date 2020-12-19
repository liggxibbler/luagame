#include "TransformComponent.h"

#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>

#include <iostream>

TransformComponent::TransformComponent()
{
}

ECS::ComponentType TransformComponent::GetType()
{
	return ECS::ComponentType_Transform;
}

Vector2 TransformComponent::GetPosition()
{
	return m_pos;
}

void TransformComponent::SetPosition(float x, float y)
{
	m_pos.x = x;
	m_pos.y = y;
}

void TransformComponent::RegisterWithLua(lua_State* L)
{
	luabridge::getGlobalNamespace(L)
		.beginNamespace("Game")
			.beginClass<TransformComponent>("Transform")
				.addFunction("GetPosition", &TransformComponent::GetPosition)				
				.addFunction("SetPosition", &TransformComponent::SetPosition)
			.endClass()
		.endNamespace();
}