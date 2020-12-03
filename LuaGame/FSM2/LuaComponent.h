#pragma once

#include "Component.h"

#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>

class LuaComponent : public ECS::Component
{
public:
	LuaComponent();

	void SetLuaBrain(luabridge::LuaRef instance);
	luabridge::LuaRef GetLuaBrain();

	virtual void Update();

private:
	luabridge::LuaRef m_luaBrain;

public:
	static void RegisterWithLua(lua_State* L);
};