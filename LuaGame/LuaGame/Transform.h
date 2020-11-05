#pragma once

#include "Component.h"

class Vector3
{
public:
	Vector3(float x, float y, float z) :
		m_x(x), m_y(y), m_z(z) {}
	void Set(float x, float y, float z)
	{
		m_x = x;
		m_y = y;
		m_z = z;
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