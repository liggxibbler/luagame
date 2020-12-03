#pragma once

#include "Entity.h"
#include "TransformComponent.h"

#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>

namespace ECS
{
	Entity::Entity()
	{
		m_transform = new TransformComponent();
		m_components.push_back(m_transform);
	}

	Entity::Entity(Entity& other)
	{
	}

	Entity::Entity(std::string name) : m_name(name)
	{
		std::cout << "ENTITY CONSTRUCTOR FOR " << name << std::endl;
		m_transform = new TransformComponent();
		m_components.push_back(m_transform);
	}

	void Entity::AddComponent(Component* c)
	{
		m_components.push_back(c);
	}

	Component* Entity::AddComponentByName(std::string name)
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

	Vector2 Entity::GetPosition()
	{
		return m_transform->GetPosition();
	}

	void Entity::SetPosition(float x, float y)
	{
		m_transform->SetPosition(x, y);
	}

	void Entity::Update()
	{
	}

	void Entity::RegisterWithLua(lua_State* L)
	{
		luabridge::getGlobalNamespace(L)
			.beginNamespace("Game")
				.beginClass<Entity>("Entity")
					.addConstructor<void (*) (std::string)>()
					.addFunction("GetName", &Entity::GetName)
					.addFunction("SetName", &Entity::SetName)
					.addFunction("AddComponent", &Entity::AddComponent)
				.endClass()
			.endNamespace();
	}
}