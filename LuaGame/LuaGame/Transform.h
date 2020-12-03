#pragma once

#include "Component.h"
#include "lua.hpp"
#include "LuaBridge/LuaBridge.h"

class Vector3
{
public:
	static void Register(lua_State* L)
	{
		luabridge::getGlobalNamespace(L)
			.beginClass<Vector3>("Vector3")
				.addFunction("getX", &Vector3::GetX)
				.addFunction("setX", &Vector3::SetX)
			.endClass();
	}

public:
	Vector3(float x, float y, float z) :
		m_x(x), m_y(y), m_z(z) {}
	void Set(float x, float y, float z)
	{
		m_x = x;
		m_y = y;
		m_z = z;
	}
	float GetX()
	{
		return m_x;
	}
	void SetX(float x)
	{
		m_x = x;
	}

public:
	float m_x, m_y, m_z;
};

class Transform : public Component
{
public:
	Transform();
	Transform(luabridge::LuaRef& componentTable);
	~Transform();

	Vector3 GetPosition();
	void SetPosition(float x, float y, float z);

private:
	Vector3 m_position;
};