#pragma once

#include "Component.h"
#include "Entity.h"

#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>

namespace ECS
{	
	Component::Component()
	{}
	
	Component::Component(Entity* entity)
		: m_entity(entity)
	{}
	
	void Component::SetEntity(Entity* entity)
	{
		m_entity = entity;
	}

	Entity* Component::GetEntity()
	{
		return m_entity;
	}
	
	void Component::RegisterWithLua(lua_State* L)
	{
		luabridge::getGlobalNamespace(L)
			.beginNamespace("Game")
				.beginClass<Component>("Component")
					.addFunction("GetEntity", &Component::GetEntity)
					.addFunction("SetEntity", &Component::SetEntity)
				.endClass()
			.endNamespace();
	}
}