#pragma once

#include "Entity.h"
#include "RenderManager.h"
#include "LuaComponent.h"
#include "CollisionManager.h"

namespace ECS
{
	class EntityManager
	{
	public:
		EntityManager();
		~EntityManager();

		void Initialize();

		Entity* CreateEntity(std::string name);		
		RenderComponent* CreateRenderComponent(int w, int h, Uint8 r, Uint8 g, Uint8 b);
		LuaComponent* CreateLuaComponent();
		ColliderComponent* CreateColliderComponent(int w, int h, bool isDynamic);

		void Update();
	private:
		std::vector<Entity*> m_entities;

	
	public:
		static void RegisterWithLua(lua_State* L);
	};
}