#pragma once

#include "Entity.h"
#include <lua.hpp>
#include "LuaBridge/LuaBridge.h"

#include "Transform.h"

class LuaEntityHandle
{
public:
	LuaEntityHandle(Entity* e)
	{
		m_entity = e;
	}

	static void Register(lua_State* L);
public:
	void SetPosition(Vector3 v);
	Vector3 GetPosition();
private:
	Entity* m_entity;
};