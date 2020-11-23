//#include "Miner.h"
#include "Utility.h"

#include <iostream>

#define LUA_NEW(base) LuaNew(L, base)
#define CALL_LUA_FUNCTION(object, function) object[function](object)
#define CALL_LUA_FUNCTION1(object, function, arg) object[function](object, arg)

#define LUA_CHECK(L, func, arg)\
if (func(L, arg) != 0)\
{\
	std::cout << "Lua error: " << lua_tostring(L, -1) << std::endl;\
	return -1;\
}\
else\
	std::cout << "something" << std::endl;\


int main()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	 Buckland::RegisterEntityWithLua(L);
	 Buckland::RegisterMinerWithLua(L);
	 Buckland::RegisterStateMachineWithLua(L);

	LUA_CHECK(L, luaL_dofile, "main.lua");
	
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
		auto x3 = classA_inst2["x"];
		std::cout << "inst2.x (direct) = " << x3 << std::endl;
	}

	//lua_close(L);
	return 0;
}