#pragma once

#include <string>
#include <map>
#include <typeindex>

#include "Component.h"

class Entity
{
public:	
	~Entity();

	void AddComponent(std::type_index type, Component* c);

	template <typename T>
	T* get()
	{
		auto it = m_components.find(std::type_index(typeid(T)));
		if (it != m_components.end())
			return dynamic_cast<T*>(it->second);
		return nullptr;
	}

	void SetType(std::string type)
	{
		m_type = type;
	}

	std::string GetType()
	{
		return m_type;
	}

private:
	std::string m_type;
	std::map<std::type_index, Component*> m_components;

};