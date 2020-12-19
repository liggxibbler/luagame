#pragma once

#include "Component.h"
#include "Rector.h"

class ColliderComponent : public ECS::Component
{
public:
	ColliderComponent();
	ColliderComponent(float w, float h, bool isDynamic);

	ECS::ComponentType GetType() override;

	Rect GetRect();
public:
	static void RegisterWithLua(lua_State* L);
private:
	float m_w, m_h;
	bool m_isDynamic;
};