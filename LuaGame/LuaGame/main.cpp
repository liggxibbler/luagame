extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

#include "LuaBridge/LuaBridge.h"

#include <iostream>
#include <string>
#include <vector>

int main()
{
	lua_State* L = luaL_newstate();
	
	luaL_openlibs(L);
	
	std::string cmd = R"(
function split(s, d)
	print ("splitting " .. s .. " by " .. d)
	t = {}
	for k, v in string.gmatch(s, d) do
		print ("found key: " .. k)
		table.insert(t, k)
	end
	return t
end
)";
	
	int res = luaL_dostring(L, cmd.c_str());
	if (res != 0)
	{
		std::cout << "do failed!" << std::endl;
		std::cout << "error: " << lua_tostring(L, -1) << std::endl;
	}
	else
	{
		std::cout << "string was did" << std::endl;
	}

	lua_getglobal(L, "split");
	lua_pushstring(L, "ghost.FirstComponent.pos.x");
	lua_pushstring(L, "[^.]+");

	res = lua_pcall(L, 2, 1, 0);
	if (res != 0)
	{
		std::cout << "call failed!" << std::endl;
		std::cout << "error: " << lua_tostring(L, -1) << std::endl;
	}
	else
	{
		std::cout << "function was called" << std::endl;
	}

	std::vector<std::string> keys;

	bool not_empty = true;
	int idx = 1;
	
	while(not_empty)
	{
		lua_pushinteger(L, idx++);
		lua_gettable(L, -2);
		
		auto key = lua_tostring(L, -1);
		
		if (key == nullptr)
		{
			not_empty = false;
			continue;
		}		
		
		std::cout << "key found: " << key << std::endl;
		keys.push_back(key);
		lua_pop(L, 1);
	}

	std::cin.get();

	return 0;
}