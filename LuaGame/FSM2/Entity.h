#pragma once

#include <string>
#include <vector>

struct lua_State;

namespace ECS
{
	class Component;

	class Entity
	{
	public:
		Entity();		
		Entity(Entity& other);

		Entity(std::string name);

		Component* AddComponent(std::string name);
		Component* GetComponent(std::string name);

		std::string GetName();
		void SetName(std::string name);

		void Update();

	public:
		static void RegisterWithLua(lua_State* L);

	private:
		std::string m_name;
		std::vector<Component*> m_components;
	};
}