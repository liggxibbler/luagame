#pragma once

#include "Entity.h"
#include "RenderComponent.h"
#include "LuaComponent.h"

namespace ECS
{
	class EntityManager
	{
	public:
		EntityManager();

		void Initialize();

		Entity* CreateEntity(std::string name);
		
		RenderComponent* CreateRenderComponent(int w, int h, Uint8 r, Uint8 g, Uint8 b);

		LuaComponent* CreateLuaComponent();

		void Update();
	private:
		std::vector<Entity*> m_entities;

	
	public:
		static void RegisterWithLua(lua_State* L);
	};
}