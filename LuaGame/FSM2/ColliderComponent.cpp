#include "ColliderComponent.h"
#include "Entity.h"

ColliderComponent::ColliderComponent()
{
}
ColliderComponent::ColliderComponent(float w, float h, bool isDynamic)
	: m_w(w), m_h(h), m_isDynamic(isDynamic)
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

void ColliderComponent::RegisterWithLua(lua_State* L)
{
	luabridge::getGlobalNamespace(L)
		.beginNamespace("Game")
			.deriveClass<ColliderComponent, Component>("ColliderComponent")
			.endClass()
		.endNamespace();
}
