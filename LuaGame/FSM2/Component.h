#pragma once

#include <string>

struct lua_State;

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

		virtual void Update() {}
	public:
		static void RegisterWithLua(lua_State* L);
	private:
		std::string m_typeName;	
		Entity* m_entity;
	};
}