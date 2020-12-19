#pragma once

#include <string>

struct lua_State;

namespace ECS
{
	enum ComponentType
	{
		ComponentType_Base = 0,
		ComponentType_Transform = 1,
		ComponentType_Render = 2,
		ComponentType_Collider = 3,
		ComponentType_Lua = 4
	};

	class Entity;

	class Component
	{
	public:
		Component();
		Component(Entity* entity);
		virtual ~Component() { }

		void SetEntity(Entity* entity);
		Entity* GetEntity();

		virtual ComponentType GetType() = 0;

		virtual void Update() {}
	public:
		static void RegisterWithLua(lua_State* L);
	private:
		std::string m_typeName;	
		Entity* m_entity;
	};
}