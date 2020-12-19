#pragma once

#include "Component.h"
#include "Rector.h"

class ColliderComponent : public ECS::Component
{
public:
	ColliderComponent();
	ColliderComponent(float w, float h);

	ECS::ComponentType GetType() override;

	Rect GetRect();
public:
private:
	float m_w, m_h;
};