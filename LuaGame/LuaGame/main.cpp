//#include "LuaBridge/LuaBridge.h"

#include "Utility.h"

#include <iostream>
#include <string>
#include <vector>

int main()
{
	lua_State* L = luaL_newstate();	
	luaL_openlibs(L);
	
	Utility::RegisterSplitFunction(L);
	Utility::LoadScript(L, "ghost.lua");


	float ret = Utility::GetNumber(L, "ghost.FirstComponent.pos.z");
	std::cout << "value of ghost.FirstComponent.pos.z is " << ret << std::endl;

	auto name = Utility::GetString(L, "ghost.SecondComponent.name");
	std::cout << "value of ghost.SecondComponent.name is " << name << std::endl;

	std::cin.get();

	return 0;
}