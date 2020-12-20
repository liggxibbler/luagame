#pragma once

#include <vector>
#include <SDL.h>

#include "ColliderComponent.h"

#define SKIN_DEPTH 3.0f

namespace Game
{
	class CollisionManager
	{
	public:
		void Initialize();

		void AddColliderComponent(ColliderComponent* collider, bool is_dynamic);
		void RemoveColliderComponent(ColliderComponent* collider);
		
		bool CheckCollision(ColliderComponent* first, ColliderComponent* second);
		void HandlePossibleCollision(ColliderComponent* first, ColliderComponent* second);
		Vector2 GetCollisionPoint(Rect r1, Rect r2);
		void Update();

	private:		
		std::vector<ColliderComponent*> m_dynamicObjects;
		std::vector<ColliderComponent*> m_staticObjects;

	public:
		static void RegisterWithLua(lua_State* L);
	};
}