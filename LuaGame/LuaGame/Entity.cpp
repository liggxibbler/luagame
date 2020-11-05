#include "Entity.h"

Entity::~Entity()
{
	for (auto& c : m_components)
	{
		delete c.second;
	}
}

void Entity::AddComponent(std::type_index type, Component* c)
{
	m_components[type] = c;
}