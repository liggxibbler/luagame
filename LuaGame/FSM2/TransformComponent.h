#pragma once

#include "Component.h"

class Vector2
{
public:
	Vector2();
	Vector2(float x, float y);
	float x, y;

public:
	static void RegisterWithLua(lua_State* L);
};

class TransformComponent : public ECS::Component
{
public:
	TransformComponent();

	Vector2 GetPosition();
	void SetPosition(float x, float y);

private:
	Vector2 m_pos;


public:
	static void RegisterWithLua(lua_State* L);
};