#pragma once

#include "Component.h"
#include "Rector.h"

class TransformComponent : public ECS::Component
{
public:
	TransformComponent();

	ECS::ComponentType GetType() override;

	Vector2 GetPosition();
	void SetPosition(float x, float y);

private:
	Vector2 m_pos;


public:
	static void RegisterWithLua(lua_State* L);
};