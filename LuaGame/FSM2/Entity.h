#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "Component.h"
#include "LuaComponent.h"
#include "TransformComponent.h"

namespace ECS
{
	class Entity
	{
	public:
		Entity();		
		Entity(Entity& other);

		Entity(std::string name);

		void AddComponent(Component* c);

		void AddComponentByName(LuaComponent* c, std::string name);
		LuaComponent* GetComponent(std::string name);

		std::string GetName();
		void SetName(std::string name);

		Vector2 GetPosition();
		void SetPosition(float x, float y);

		void Update();
		void OnCollision(Vector2 point);
		void OnStart();

		void SetActive(bool state);
		bool IsActive();

	public:
		static void RegisterWithLua(lua_State* L);

	private:
		bool m_isActive = true;
		TransformComponent* m_transform;
		std::string m_name;
		std::vector<Component*> m_components;
		std::unordered_map<std::string, LuaComponent*> m_luaComponentMap;
	};
}