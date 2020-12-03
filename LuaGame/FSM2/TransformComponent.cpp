#include "TransformComponent.h"

#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>

#include <iostream>

TransformComponent::TransformComponent()
{
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

// --------

Vector2::Vector2() : x(0), y(0) {}
Vector2::Vector2(float x_, float y_) : x(x_), y(y_) {}
void Vector2::RegisterWithLua(lua_State* L)
{
	luabridge::getGlobalNamespace(L)
		.beginNamespace("Game")
			.beginClass<Vector2>("Vec2")
				.addProperty("x", &Vector2::x)
				.addProperty("y", &Vector2::y)
			.endClass()
		.endNamespace();
}