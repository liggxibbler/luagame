#include "Utility.h"

#include "Entity.h"
#include "Transform.h"

template <typename T>
void AddComponent(Entity* e, luabridge::LuaRef& componentTable) {
	e->AddComponent(std::type_index(typeid(T)), new T(componentTable));
}

Entity* LoadEntity(lua_State* L, const std::string& type)
{
	Entity* e = new Entity();
	e->SetType(type);
	auto keys = Utility::GetTableKeys(L, type);

	luabridge::LuaRef entityTable = luabridge::getGlobal(L, type.c_str());

	for (auto& componentName : keys)
	{
		if (componentName == "Transform")
		{
			luabridge::LuaRef ttable = entityTable["Transform"];
			AddComponent<Transform>(e, ttable);
		}
	}
	return e;
}

int main()
{
	lua_State* L = luaL_newstate();	
	luaL_openlibs(L);
	
	Utility::RegisterSplitFunction(L);
	Utility::RegisterGetKeysFunction(L);
	Utility::LoadScript(L, "ghost.lua");

	double ret = Utility::GetNumber(L, "ghost.FirstComponent.position.z");
	std::cout << "value of ghost.FirstComponent.pos.z is " << ret << std::endl;
	
	auto name = Utility::GetString(L, "ghost.SecondComponent.name");
	std::cout << "value of ghost.SecondComponent.name is " << name << std::endl;

	std::vector<std::string> ghost_keys = Utility::GetTableKeys(L, "ghost");
	for (int i = 0; i < ghost_keys.size(); ++i)
	{
		std::cout << "ghost key[" << i << "]=" << ghost_keys[i] << std::endl;
	}

	std::vector<std::string> pos_keys = Utility::GetTableKeys(L, "ghost.FirstComponent.position");
	for (int i = 0; i < pos_keys.size(); ++i)
	{
		std::cout << "pos key[" << i << "]=" << pos_keys[i] << std::endl;
	}

	std::cin.get();

	auto e = LoadEntity(L, "ghost");
	
	auto p = e->get<Transform>()->GetPosition();
	std::cout << "e.pos = (" << p.m_x << ", " << p.m_y << ", " << p.m_z << ")" << std::endl;

	std::cin.get();

	lua_close(L);

	return 0;
}