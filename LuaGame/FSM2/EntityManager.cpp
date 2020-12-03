#include "EntityManager.h"

#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>

namespace ECS
{
	EntityManager::EntityManager() {}

	void EntityManager::Initialize()
	{
	}

	Entity* EntityManager::CreateEntity(std::string name)
	{
		std::cout << "CREATING ENTITY " << name << std::endl;
		auto ret = new Entity(name);
		m_entities.push_back(ret);
		std::cout << name << " PUSHED" << std::endl;
		return ret;
	}

	RenderComponent* EntityManager::CreateRenderComponent(int w, int h, Uint8 r, Uint8 g, Uint8 b)
	{
		return new RenderComponent(w, h, r, g, b);
	}

	LuaComponent* EntityManager::CreateLuaComponent()
	{
		return new LuaComponent();
	}

	void EntityManager::Update()
	{
		for (auto iterent = m_entities.begin(); iterent != m_entities.end(); ++iterent)
		{
			(*iterent)->Update();
		}
	}

	void EntityManager::RegisterWithLua(lua_State* L)
	{
		ECS::Component::RegisterWithLua(L);
		RenderComponent::RegisterWithLua(L);
		LuaComponent::RegisterWithLua(L);
		ECS::Entity::RegisterWithLua(L);

		luabridge::getGlobalNamespace(L)
			.beginNamespace("Game")
				.beginClass<EntityManager>("EntityManager")
					.addFunction("CreateEntity", &EntityManager::CreateEntity)
					.addFunction("CreateLuaComponent", &EntityManager::CreateLuaComponent)
					.addFunction("CreateRenderComponent", &EntityManager::CreateRenderComponent)
				.endClass()
			.endNamespace();
	}
}