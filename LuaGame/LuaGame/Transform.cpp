#include "Transform.h"

#include "lua.hpp"
#include "LuaBridge/LuaBridge.h"

Transform::Transform()
	: m_position(0, 0, 0) {}

Transform::Transform(luabridge::LuaRef& componentTable)
	: m_position(0, 0, 0)
{
	using namespace luabridge;

	auto positionRef = componentTable["position"];
	auto x = static_cast<double>(positionRef["x"]);
	auto y = static_cast<double>(positionRef["y"]);
	auto z = static_cast<double>(positionRef["z"]);
	std::cout << "position is " << x << ", " << y << ", " << z << std::endl;
	SetPosition(x, y, z);
}

Transform::~Transform()
{}

Vector3 Transform::GetPosition()
{
	return m_position;
}

void Transform::SetPosition(float x, float y, float z)
{
	m_position.Set(x, y, z);
}