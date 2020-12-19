#pragma once

#include "Component.h"
#include "TransformComponent.h"

#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>

class LuaComponent : public ECS::Component
{
public:
	LuaComponent();

	void SetLuaBrain(luabridge::LuaRef instance);
	luabridge::LuaRef GetLuaBrain();

	ECS::ComponentType GetType() override;

	virtual void Update();
	virtual void OnCollision(Vector2 point);
	virtual void OnStart();

private:
	luabridge::LuaRef m_luaBrain;

public:
	static void RegisterWithLua(lua_State* L);
};