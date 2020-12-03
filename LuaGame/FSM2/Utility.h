#pragma once

#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>
#include <unordered_map>

#ifdef _DEBUG
#define DUMP_LUA_STACK(x) DumpStack(x, __FUNCTION__)
#else
#define DUMP_LUA_STACK(x)
#endif

class LuaHelper
{
public:
	static luabridge::LuaRef GetLuaClassNew(lua_State* L, std::string className)
    {
        if (base_classes.find(className) == base_classes.end())
        {
            auto theClass = luabridge::getGlobal(L, className.c_str());
            base_classes.insert(std::make_pair(className, theClass));
            new_funcs.insert(std::make_pair(className, theClass["new"]));
        }
        return new_funcs.at(className);
    }

    static luabridge::LuaRef LuaNew(lua_State* L, std::string className)
    {
        auto new_ = GetLuaClassNew(L, className);
        return new_(base_classes.at(className));
    }

	static void DumpStack(lua_State* L, std::string func)
	{
		std::cout << "[" << func << "] Stack top is at " << lua_gettop(L) << std::endl;
		for (int i = 0; i < lua_gettop(L); ++i)
		{
			std::cout << "at [" << i + 1 << "] = " << lua_typename(L, lua_type(L, i + 1)) << std::endl;
		}
	}

	static std::vector<std::string> SplitVariableName(lua_State* L, std::string varName)
	{
		lua_getglobal(L, "split");
		lua_pushstring(L, varName.c_str());
		lua_pushstring(L, "[^.]+");

		DUMP_LUA_STACK(L);

		int res = lua_pcall(L, 2, 1, 0);
		if (res != 0)
		{
			std::cout << "Failed to call split function. Error: " << lua_tostring(L, -1) << std::endl;
		}

		DUMP_LUA_STACK(L);

		std::vector<std::string> keys;

		bool not_empty = true;
		int idx = 1;

		while (not_empty)
		{
			lua_pushinteger(L, idx++);
			lua_gettable(L, -2);

			DUMP_LUA_STACK(L);

			auto key = lua_tostring(L, -1);

			if (key != nullptr)
			{
				keys.push_back(key);
			}
			else
			{
				not_empty = false;
			}

			lua_pop(L, 1);

			DUMP_LUA_STACK(L);
		}

		DUMP_LUA_STACK(L);

		lua_pop(L, 1);
		return keys;
	}

	static void GetVariableOnStack(lua_State* L, std::string varName)
	{
		auto keys = SplitVariableName(L, varName);
		if (keys.size() == 0)
			return;

		DUMP_LUA_STACK(L);

		lua_getglobal(L, keys[0].c_str());

		DUMP_LUA_STACK(L);

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

		DUMP_LUA_STACK(L);
	}

	static std::vector<std::string> GetTableKeys(lua_State* L, std::string tableName)
	{
		DUMP_LUA_STACK(L);

		lua_getglobal(L, "getKeys");

		DUMP_LUA_STACK(L);

		GetVariableOnStack(L, tableName.c_str());

		DUMP_LUA_STACK(L);

		int result = lua_pcall(L, 1, 1, 0);
		{
			if (result != 0)
			{
				std::cout << "Failed to call getKeys. Error: " << lua_tostring(L, -1) << std::endl;
			}
		}
		lua_pushnil(L);

		DUMP_LUA_STACK(L);

		std::vector<std::string> keys;

		while (lua_next(L, -2))
		{
			if (lua_type(L, -1) == LUA_TSTRING)
			{
				keys.push_back(lua_tostring(L, -1));
			}
			lua_pop(L, 1);
		}

		DUMP_LUA_STACK(L);

		lua_settop(L, 0);

		DUMP_LUA_STACK(L);

		return keys;
	}

	static double GetNumber(lua_State* L, std::string varName)
	{
		GetVariableOnStack(L, varName.c_str());
		if (!lua_isnumber(L, -1))
		{
			std::cout << "Error: Attempting to retrieve non-number as number" << std::endl;
		}
		double ret = lua_tonumber(L, -1);
		lua_pop(L, 1);
		return ret;
	}

	static std::string GetString(lua_State* L, std::string varName)
	{
		GetVariableOnStack(L, varName.c_str());
		if (!lua_isstring(L, -1))
		{
			std::cout << "Error: Attempting to retrieve non-number as number" << std::endl;
		}
		std::string ret = lua_tostring(L, -1);
		lua_pop(L, 1);
		return ret;
	}

	static void LoadScript(lua_State* L, std::string scriptPath)
	{
		int res = luaL_dofile(L, scriptPath.c_str());
		if (res != 0)
			std::cout << "Failed to load script " << scriptPath << ". Error: " << lua_tostring(L, -1);
	}

private:
    static std::unordered_map<std::string, luabridge::LuaRef> base_classes;
    static std::unordered_map<std::string, luabridge::LuaRef> new_funcs;
};