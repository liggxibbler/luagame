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
	static luabridge::LuaRef GetLuaClassNew(lua_State* L, std::string className);
	static luabridge::LuaRef LuaNew(lua_State* L, std::string className);

	static void DumpStack(lua_State* L, std::string func);

	static std::vector<std::string> SplitVariableName(lua_State* L, std::string varName);

	static void GetVariableOnStack(lua_State* L, std::string varName);

	static std::vector<std::string> GetTableKeys(lua_State* L, std::string tableName);

	static double GetNumber(lua_State* L, std::string varName);

	static std::string GetString(lua_State* L, std::string varName);

	static void LoadScript(lua_State* L, std::string scriptPath);

private:
    static std::unordered_map<std::string, luabridge::LuaRef> base_classes;
    static std::unordered_map<std::string, luabridge::LuaRef> new_funcs;
};