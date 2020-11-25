#pragma once

#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>

#include <string>

namespace Buckland
{
	class Entity
	{

	private:

		int m_id;
		std::string m_name;

		//used by the constructor to give each entity a unique ID
		int NextValidID() { static int NextID = 0; return NextID++; }

	public:

		Entity(std::string name = "NoName") :m_id(NextValidID()), m_name(name) {}

		virtual ~Entity() {}

		//all entities must implement an update function
		virtual void Update() = 0;

		//accessors
		int         ID()const { return m_id; }
		std::string Name()const { return m_name; }
	};
}