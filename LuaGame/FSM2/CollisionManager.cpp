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
			std::cout << "Added dynamic collider. count is now " << m_dynamicObjects.size() << std::endl;
		}
		else
		{
			m_staticObjects.push_back(collider);
			std::cout << "Added static collider. count is now " << m_staticObjects.size() << std::endl;
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

			//std::cout << "from " << first->GetEntity()->GetName() << ": ";
			Vector2 one2two = GetCollisionPoint(first->GetRect(), second->GetRect());
			first->GetEntity()->OnCollision(second->GetEntity(), one2two);
			//std::cout << ", from " << second->GetEntity()->GetName() << ": ";
			Vector2 two2one = GetCollisionPoint(second->GetRect(), first->GetRect());
			//std::cout << std::endl;
			second->GetEntity()->OnCollision(first->GetEntity(), two2one);
		}
	}

	Vector2 CollisionManager::GetCollisionPoint(Rect r1, Rect r2)
	{
		auto right = r1.m_x + r1.m_w - r2.m_x;
		auto top = r2.m_y + r2.m_h - r1.m_y;
		auto left = r2.m_x + r2.m_w - r1.m_x;
		auto bottom = r1.m_y + r1.m_h - r2.m_y;

		if (right <= SKIN_DEPTH)
		{
			//std::cout << "RIGHT";
			return Vector2(r1.m_w / 2, 0);
		}
		else if (left <= SKIN_DEPTH)
		{
			//std::cout << "LEFT";
			return Vector2(-r1.m_w / 2, 0);
		}
		else if (top <= SKIN_DEPTH)
		{
			//std::cout << "TOP";
			return Vector2(0, -r1.m_h / 2);
		}
		else if (bottom <= SKIN_DEPTH)
		{
			//std::cout << "BOTTOM";
			return Vector2(0, r1.m_h / 2);
		}
	}

	void CollisionManager::Update()
	{
		for (auto dyniter1 = m_dynamicObjects.begin(); dyniter1 != m_dynamicObjects.end(); ++dyniter1)
		{
			if (!(*dyniter1)->GetEntity()->IsActive())
				continue;
			for (auto dyniter2 = std::next(dyniter1); dyniter2 != m_dynamicObjects.end(); ++dyniter2)
			{
				if (!(*dyniter2)->GetEntity()->IsActive())
					continue;
				if (dyniter1 != dyniter2)
					HandlePossibleCollision(*dyniter1, *dyniter2);
			}

			for (auto statiter = m_staticObjects.begin(); statiter != m_staticObjects.end(); ++statiter)
			{
				if (!(*statiter)->GetEntity()->IsActive())
					continue;
				if (dyniter1 != statiter)
					HandlePossibleCollision(*dyniter1, *statiter);
			}
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