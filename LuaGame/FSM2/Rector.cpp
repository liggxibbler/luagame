#include "Rector.h"

/* Vector2 */

Vector2::Vector2() : x(0), y(0) {}
Vector2::Vector2(float x_, float y_) : x(x_), y(y_) {}

Vector2 Vector2::operator + (Vector2 other)
{
	auto ret = Vector2{ x + other.x, y + other.y };
	return ret;
}

Vector2 Vector2::operator - (Vector2 other)
{
	auto ret = Vector2{ x - other.x, y - other.y };
	return ret;
}
Vector2 Vector2::operator* (float scale)
{
	auto ret = Vector2{ x * scale, y * scale };
	return ret;
}
Vector2 Vector2::operator / (float scale)
{
	auto ret = Vector2{ x / scale, y / scale };
	return ret;
}

void Vector2::RegisterWithLua(lua_State* L)
{
	luabridge::getGlobalNamespace(L)
		.beginNamespace("Game")
			.beginClass<Vector2>("Vec2")
				.addProperty("x", &Vector2::x)
				.addProperty("y", &Vector2::y)
				.addFunction("__add", &Vector2::operator+)
				.addFunction("__sub", &Vector2::operator-)
				.addFunction("__mul", &Vector2::operator*)
				.addFunction("__div", &Vector2::operator/)
			.endClass()
		.endNamespace();
}

/* Rect */

Rect::Rect()
	: m_x(0), m_y(0), m_w(0), m_h(0)
{}

Rect::Rect(float x, float y, float w, float h)
	: m_x(x), m_y(y), m_w(w), m_h(h)
{
}

void Rect::RegisterWithLua(lua_State* L)
{

}