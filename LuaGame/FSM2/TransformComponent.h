#pragma once

#include "Component.h"

struct lua_State;

class TransformComponent : public ECS::Component
{
public:
	TransformComponent();

	float GetX();
	float GetY();

	void SetX(float x);
	void SetY(float y);

public:
	static void RegisterWithLua(lua_State* L);
private:
	float m_x;
	float m_y;
};