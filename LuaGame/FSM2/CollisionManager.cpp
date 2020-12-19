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
		}
		else
		{
			m_staticObjects.push_back(collider);
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

		if (abs(mid1.x - mid2.x) < (r1.m_w + r2.m_w) && abs(mid1.y - mid2.y) < (r1.m_h + r2.m_h))
		{
			return true;
		}
	}

	void CollisionManager::Update()
	{
		for (auto dyniter1 = m_dynamicObjects.begin(); dyniter1 != m_dynamicObjects.end(); ++dyniter1)
			for (auto dyniter2 = std::next(dyniter1); dyniter2 != m_dynamicObjects.end(); ++dyniter2)
			{
				if (CheckCollision(*dyniter1, *dyniter2))
				{
					auto pos1 = (*dyniter1)->GetEntity()->GetPosition();
					auto pos2 = (*dyniter2)->GetEntity()->GetPosition();

					Vector2 one2two{ pos1.x - pos2.x, pos1.y - pos2.y };
					Vector2 two2one{ pos2.x - pos1.x, pos2.y - pos1.y };

					(*dyniter1)->GetEntity()->OnCollision(one2two);
					(*dyniter2)->GetEntity()->OnCollision(two2one);
				}
			}

		for (auto dyniter = m_dynamicObjects.begin(); dyniter != m_dynamicObjects.end(); ++dyniter)		
			for (auto statiter = m_dynamicObjects.begin(); statiter != m_dynamicObjects.end(); ++statiter)
			{
				if (CheckCollision(*dyniter, *statiter))
				{
					auto pos1 = (*dyniter)->GetEntity()->GetPosition();
					auto pos2 = (*statiter)->GetEntity()->GetPosition();

					Vector2 one2two{ pos1.x - pos2.x, pos1.y - pos2.y };
					Vector2 two2one{ pos2.x - pos1.x, pos2.y - pos1.y };

					(*dyniter)->GetEntity()->OnCollision(one2two);
					(*statiter)->GetEntity()->OnCollision(two2one);
				}
			}		
	}

	void CollisionManager::RegisterWithLua(lua_State* L)
	{

	}
}