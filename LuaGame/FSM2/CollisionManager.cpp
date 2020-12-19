#include <cmath>

#include "CollisionManager.h"
#include "Entity.h"

namespace Game
{
	void CollisionManager::Initialize()
	{

	}

	void CollisionManager::AddColliderComponent(ColliderComponent* collider, bool is_dynamic)
	{
		if (is_dynamic)
		{
			m_dynamicObjects.push_back(collider);
			std::cout << "Added dynamic collider. count is now " << m_dynamicObjects.size();
		}
		else
		{
			m_staticObjects.push_back(collider);
			std::cout << "Added static collider. count is now " << m_staticObjects.size();
		}
	}
	
	void CollisionManager::RemoveColliderComponent(ColliderComponent* collider)
	{

	}

	bool CollisionManager::CheckCollision(ColliderComponent* first, ColliderComponent* second)
	{
		auto r1 = first->GetRect();
		auto r2 = second->GetRect();

		auto mid1 = first->GetEntity()->GetPosition(); // (Vector2{ r1.m_x, r1.m_y } + Vector2{ r1.m_w, r1.m_h }) / 2;
		auto mid2 = second->GetEntity()->GetPosition(); //(Vector2{ r2.m_x, r2.m_y } + Vector2{ r2.m_w, r2.m_h }) / 2;

		//std::cout << "checking rects: " << mid1.x << ", " << mid1.y << ", " << r1.m_w << ", " << r1.m_h << " and " << mid2.x << ", " << mid2.y << ", " << r2.m_w << ", " << r2.m_h << std::endl;

		auto xdiff = abs(mid1.x - mid2.x);
		auto ydiff = abs(mid1.y - mid2.y);
		auto wavg = .5 * (r1.m_w + r2.m_w);
		auto havg = .5 * (r1.m_h + r2.m_h);
		auto xcond = xdiff < wavg;
		auto ycond = ydiff < havg;

		return xcond && ycond;
	}

	void CollisionManager::HandlePossibleCollision(ColliderComponent* first, ColliderComponent* second)
	{
		if (CheckCollision(first, second))
		{
			auto pos1 = first->GetEntity()->GetPosition();
			auto pos2 = second->GetEntity()->GetPosition();

			Vector2 one2two = pos1 - pos2;
			Vector2 two2one = pos2 - pos1;

			first->GetEntity()->OnCollision(one2two);
			second->GetEntity()->OnCollision(two2one);
		}
	}

	void CollisionManager::Update()
	{
		for (auto dyniter1 = m_dynamicObjects.begin(); dyniter1 != m_dynamicObjects.end(); ++dyniter1)
			for (auto dyniter2 = std::next(dyniter1); dyniter2 != m_dynamicObjects.end(); ++dyniter2)
			{
				if (dyniter1 != dyniter2)
					HandlePossibleCollision(*dyniter1, *dyniter2);
			}

		for (auto dyniter = m_dynamicObjects.begin(); dyniter != m_dynamicObjects.end(); ++dyniter)		
			for (auto statiter = m_staticObjects.begin(); statiter != m_staticObjects.end(); ++statiter)
			{
				if (dyniter != statiter)
					HandlePossibleCollision(*dyniter, *statiter);
			}		
	}

	void CollisionManager::RegisterWithLua(lua_State* L)
	{
		ColliderComponent::RegisterWithLua(L);

		luabridge::getGlobalNamespace(L)
			.beginNamespace("Game")
				.beginClass<CollisionManager>("CollisionManager")
					.addFunction("Add", &CollisionManager::AddColliderComponent)
				.endClass()
			.endNamespace();
	}
}