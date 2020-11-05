#pragma once

extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

#include <iostream>
#include <vector>

namespace Utility
{
	void RegisterSplitFunction(lua_State* L);
	std::vector<std::string> SplitVariableName(lua_State* L, std::string varName);
	void GetVariableOnStack(lua_State* L, std::string varName);
	
	float GetNumber(lua_State* L, std::string varName);
	std::string GetString(lua_State* L, std::string varName);
}