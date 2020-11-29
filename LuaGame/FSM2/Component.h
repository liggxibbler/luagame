#pragma once

#include <string>

namespace luabridge
{
	class LuaRef;
}
struct lua_State* L;

namespace ECS
{
	class Entity;

	class Component
	{
	public:
		Component();
		Component(Entity* entity);
		virtual ~Component() { }

		void SetEntity(Entity* entity);
		Entity* GetEntity();

		void SetLuaInstance(luabridge::LuaRef* instance);
		luabridge::LuaRef* GetLuaInstance();
	public:
		void RegisterWithLua(lua_State* L);
	private:
		std::string m_typeName;
		Entity* m_entity;		
		luabridge::LuaRef* m_luaInstance;
	};
}