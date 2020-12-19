#pragma once

#include <string>
#include <vector>

#include "Component.h"
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

		Component* AddComponentByName(std::string name);
		Component* GetComponent(std::string name);

		std::string GetName();
		void SetName(std::string name);

		Vector2 GetPosition();
		void SetPosition(float x, float y);

		void Update();
		void OnCollision(Vector2 point);
		void OnStart();

	public:
		static void RegisterWithLua(lua_State* L);

	private:
		TransformComponent* m_transform;
		std::string m_name;
		std::vector<Component*> m_components;
	};
}