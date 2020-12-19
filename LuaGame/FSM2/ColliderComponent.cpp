#include "ColliderComponent.h"
#include "Entity.h"

ColliderComponent::ColliderComponent()
{
}
ColliderComponent::ColliderComponent(float w, float h)
{

}

ECS::ComponentType ColliderComponent::GetType()
{
	return ECS::ComponentType_Collider;
}

Rect ColliderComponent::GetRect()
{
	auto pos = GetEntity()->GetPosition();
	return Rect{ pos.x - m_w / 2, pos.y - m_h / 2, pos.x + m_w / 2, pos.y + m_h / 2 };
}
