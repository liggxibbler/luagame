#pragma once

#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>
#include <unordered_map>

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

private:
    static std::unordered_map<std::string, luabridge::LuaRef> base_classes;
    static std::unordered_map<std::string, luabridge::LuaRef> new_funcs;
};