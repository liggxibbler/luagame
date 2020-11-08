#include "Miner.h"
#include "Utility.h"

#include <iostream>

int main()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	RegisterEntityWithLua(L);
	RegisterMinerWithLua(L);
	RegisterStateMachineWithLua(L);

	if (luaL_dofile(L, "miner_states.lua") != 0)
	{
		std::cout << "Failed to load script - error: " << lua_tostring(L, -1) << std::endl;
		return -2;
	}

	//Miner stan("Stan");
	//
	//auto states = luabridge::getGlobal(L, "States");
	//stan.GetFSM()->SetState(states["GoHome"]);
	//
	//for (int i = 0; i < 10; ++i)
	//{
	//	try
	//	{
	//		stan.Update();
	//	}
	//	catch (luabridge::LuaException e)
	//	{
	//		std::cout << "Failed to update: " << e.what() << std::endl;
	//	}
	//}

	//lua_close(L);
	return 0;
}