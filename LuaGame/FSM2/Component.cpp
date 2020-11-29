#pragma once

#include "Component.h"
#include "Entity.h"

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
	
	void Component::SetLuaInstance(luabridge::LuaRef* instance)
	{
		m_luaInstance = instance;
	}

	luabridge::LuaRef* Component::GetLuaInstance()
	{
		return m_luaInstance;
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