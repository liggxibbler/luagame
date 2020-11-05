#include "Utility.h"

namespace Utility
{

	void RegisterSplitFunction(lua_State* L)
	{
		std::string cmd = R"(
function split(s, d)
	--print ("splitting " .. s .. " by " .. d)
	t = {}
	for k, v in string.gmatch(s, d) do
		--print ("found key: " .. k)
		table.insert(t, k)
	end
	return t
end

ghost =
{
	FirstComponent = 
	{
		pos =
		{
			x = 12.0,
			y = 1.5,
			z = 4.75			
		}
	},
	
	SecondComponent = 
	{
		name = "Frederick",
		path = "C:/"
	}
}
)";

		int res = luaL_dostring(L, cmd.c_str());
		if (res != 0)
		{
			std::cout << "Failed to register split function. Error: " << lua_tostring(L, -1) << std::endl;
		}
		else
		{
			std::cout << "split function registered successfully" << std::endl;
		}
	}


	std::vector<std::string> SplitVariableName(lua_State* L, std::string varName)
	{
		lua_getglobal(L, "split");
		lua_pushstring(L, varName.c_str());
		lua_pushstring(L, "[^.]+");

		int res = lua_pcall(L, 2, 1, 0);
		if (res != 0)
		{
			std::cout << "Failed to call split function. Error: " << lua_tostring(L, -1) << std::endl;
		}

		std::vector<std::string> keys;

		bool not_empty = true;
		int idx = 1;

		while (not_empty)
		{
			lua_pushinteger(L, idx++);
			lua_gettable(L, -2);

			auto key = lua_tostring(L, -1);

			if (key == nullptr)
			{
				not_empty = false;
				continue;
			}

			keys.push_back(key);
			lua_pop(L, 1);
		}

		return keys;
	}

	void GetVariableOnStack(lua_State* L, std::string varName)
	{
		auto keys = SplitVariableName(L, varName);
		if (keys.size() == 0)
			return;

		lua_getglobal(L, keys[0].c_str());

		if (keys.size() > 1)
		{
			for (int i = 1; i < keys.size(); ++i)
			{
				lua_getfield(L, -1, keys[i].c_str());
			}

			int retIndex = lua_gettop(L) - keys.size() + 1;
			lua_replace(L, retIndex);
			lua_settop(L, retIndex);
		}
	}

	float GetNumber(lua_State* L, std::string varName)
	{
		GetVariableOnStack(L, varName.c_str());
		if (!lua_isnumber(L, -1))
		{
			std::cout << "Error: Attempting to retrieve non-number as number" << std::endl;
		}
		return lua_tonumber(L, -1);
	}
	
	std::string GetString(lua_State* L, std::string varName)
	{
		GetVariableOnStack(L, varName.c_str());
		if (!lua_isstring(L, -1))
		{
			std::cout << "Error: Attempting to retrieve non-number as number" << std::endl;
		}
		return lua_tostring(L, -1);
	}
}