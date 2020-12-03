#include "LuaComponent.h"

#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>

LuaComponent::LuaComponent() {}

void LuaComponent::SetLuaBrain(luabridge::LuaRef* instance)
{
	m_luaBrain = instance;
}

luabridge::LuaRef* LuaComponent::GetLuaBrain()
{
	return m_luaBrain;
}

void LuaComponent::RegisterWithLua(lua_State* L)
{
	luabridge::getGlobalNamespace(L)
		.beginNamespace("Game")
			.deriveClass<LuaComponent, Component>("LuaComponent")
				.addConstructor<void (*) ()>()
				.addFunction("SetLuaBrain", &LuaComponent::SetLuaBrain)
				.addFunction("GetLuaBrain", &LuaComponent::GetLuaBrain)
			.endClass()
		.endNamespace();
}