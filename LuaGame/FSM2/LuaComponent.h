#pragma once

#include "Component.h"

namespace luabridge
{
	class LuaRef;
}
struct lua_State;

class LuaComponent : public ECS::Component
{
public:
	LuaComponent();

	void SetLuaBrain(luabridge::LuaRef* instance);
	luabridge::LuaRef* GetLuaBrain();

private:
	luabridge::LuaRef* m_luaBrain;

public:
	static void RegisterWithLua(lua_State* L);
};