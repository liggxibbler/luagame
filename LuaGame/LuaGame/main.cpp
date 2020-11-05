#include "Utility.h"


int main()
{
	lua_State* L = luaL_newstate();	
	luaL_openlibs(L);
	
	Utility::RegisterSplitFunction(L);
	Utility::RegisterGetKeysFunction(L);
	Utility::LoadScript(L, "ghost.lua");

	double ret = Utility::GetNumber(L, "ghost.FirstComponent.pos.z");
	std::cout << "value of ghost.FirstComponent.pos.z is " << ret << std::endl;
	
	auto name = Utility::GetString(L, "ghost.SecondComponent.name");
	std::cout << "value of ghost.SecondComponent.name is " << name << std::endl;

	std::vector<std::string> ghost_keys = Utility::GetTableKeys(L, "ghost");
	for (int i = 0; i < ghost_keys.size(); ++i)
	{
		std::cout << "ghost key[" << i << "]=" << ghost_keys[i] << std::endl;
	}

	std::vector<std::string> pos_keys = Utility::GetTableKeys(L, "ghost.FirstComponent.pos");
	for (int i = 0; i < pos_keys.size(); ++i)
	{
		std::cout << "pos key[" << i << "]=" << pos_keys[i] << std::endl;
	}

	std::cin.get();

	


	std::cin.get();

	return 0;
}