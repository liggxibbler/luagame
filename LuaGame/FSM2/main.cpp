//#include "Miner.h"
#include "Utility.h"

#include <iostream>

#define LUA_NEW(base) LuaNew(L, base)
#define CALL_LUA_FUNCTION(object, function) object[function](object)
#define CALL_LUA_FUNCTION1(object, function, arg) object[function](object, arg)

int main()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	RegisterEntityWithLua(L);
	RegisterMinerWithLua(L);
	RegisterStateMachineWithLua(L);

	/*if (luaL_dofile(L, "miner_states.lua") != 0)
	{
		std::cout << "Failed to load script - error: " << lua_tostring(L, -1) << std::endl;
		return -2;
	}*/

	if (luaL_dofile(L, "test_component.lua") != 0)
	{
		std::cout << "Failed to load script - error: " << lua_tostring(L, -1) << std::endl;
		return -3;
	}

	auto classA_inst1 = LUA_NEW("classA");
	CALL_LUA_FUNCTION1(classA_inst1, "setX", 12);
	auto x1 = CALL_LUA_FUNCTION(classA_inst1, "getX");
	std::cout << "inst1.x = " << x1 << std::endl;

	
	auto classA_inst2 = LUA_NEW("classA");
	CALL_LUA_FUNCTION1(classA_inst2, "setX", 45);
	auto x2 = CALL_LUA_FUNCTION(classA_inst2, "getX");
	std::cout << "inst2.x = " << x2 << std::endl;

	for (int i = 0; i < 10; ++i)
	{
		CALL_LUA_FUNCTION(classA_inst2, "update");
		auto x2 = CALL_LUA_FUNCTION(classA_inst2, "getX");
		std::cout << "inst2.x = " << x2 << std::endl;
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