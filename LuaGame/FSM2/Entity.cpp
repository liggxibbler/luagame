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

	Entity::~Entity()
	{
		for (auto compiter = m_components.begin(); compiter != m_components.end(); ++compiter)
			delete* compiter;
	}

	void Entity::AddComponent(Component* c)
	{
		c->SetEntity(this);
		m_components.push_back(c);
	}

	void Entity::AddComponentByName(LuaComponent* c, std::string name)
	{
		AddComponent(c);
		m_luaComponentMap[name] = c;
	}

	LuaComponent* Entity::GetComponent(std::string name)
	{
		return m_luaComponentMap[name];
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
		for (auto itercmp = m_components.begin(); itercmp != m_components.end(); ++itercmp)
			(*itercmp)->Update();
	}

	void Entity::OnCollision(Entity* other, Vector2 point)
	{
		for (auto luaiter = m_components.begin(); luaiter != m_components.end(); ++luaiter)
		{
			if ((*luaiter)->GetType() == ComponentType_Lua)
			{
				((LuaComponent*)(*luaiter))->OnCollision(other, point);
			}
		}
	}

	void Entity::OnStart()
	{
		for (auto iter = m_components.begin(); iter != m_components.end(); ++iter)
			if ((*iter)->GetType() == ComponentType_Lua)
				((LuaComponent*)(*iter))->OnStart();
	}

	void Entity::SetActive(bool state)
	{
		m_isActive = state;
	}

	bool Entity::IsActive()
	{
		return m_isActive;
	}

	std::string Entity::GetTag()
	{
		return m_tag;
	}

	void Entity::SetTag(std::string tag)
	{
		m_tag = tag;
	}

	void Entity::RegisterWithLua(lua_State* L)
	{
		luabridge::getGlobalNamespace(L)
			.beginNamespace("Game")
				.beginClass<Entity>("Entity")
					.addConstructor<void (*) (std::string)>()
					.addFunction("GetName", &Entity::GetName)
					.addFunction("SetName", &Entity::SetName)
					.addFunction("GetPosition", &Entity::GetPosition)
					.addFunction("SetPosition", &Entity::SetPosition)
					.addFunction("AddComponent", &Entity::AddComponent)
					.addFunction("AddComponentByName", &Entity::AddComponentByName)
					.addFunction("GetComponent", &Entity::GetComponent)
					.addFunction("OnStart", &Entity::OnStart)
					.addFunction("IsActive", &Entity::IsActive)
					.addFunction("SetActive", &Entity::SetActive)
					.addFunction("SetTag", &Entity::SetTag)
					.addFunction("GetTag", &Entity::GetTag)
				.endClass()
			.endNamespace();
	}
}