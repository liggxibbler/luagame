#pragma once

#include <lua.hpp>
#include <LuaBridge/LuaBridge.h> 

class Vector2
{
public:
	Vector2();
	Vector2(float x, float y);
	Vector2 operator + (Vector2 other);
	Vector2 operator - (Vector2 other);
	Vector2 operator * (float scale);
	Vector2 operator / (float scale);

	float x, y;

public:
	static void RegisterWithLua(lua_State* L);
};

class Rect
{
public:
	Rect();
	Rect(float x, float y, float w, float h);
	float m_x, m_y, m_w, m_h;

public:
	static void RegisterWithLua(lua_State* L);
};