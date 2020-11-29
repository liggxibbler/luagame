#pragma once

#include "Entity.h"
#include "TransformComponent.h"

#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>

namespace ECS
{
	Entity::Entity()
	{
		auto transform = new TransformComponent();
		m_components.push_back(transform);
	}

	Entity::Entity(Entity& other)
	{
	}

	Entity::Entity(std::string name)
	{
	}

	Component* Entity::AddComponent(std::string name)
	{		
	}

	Component* Entity::GetComponent(std::string name)
	{
	}

	std::string Entity::GetName()
	{
		return m_name;
	}

	void Entity::SetName(std::string name)
	{
		m_name = name;
	}

	void Entity::Update()
	{
	}

	void Entity::RegisterWithLua(lua_State* L)
	{
		luabridge::getGlobalNamespace(L)
			.beginNamespace("Game")
				.beginClass<Entity>("Entity")
					.addFunction("GetName", &Entity::GetName)
					.addFunction("SetName", &Entity::SetName)
				.endClass()
			.endNamespace();
	}
}