#pragma once

#include "StateMachine.h"
#include "Miner.h"
#include <map>

void RegisterStateMachineWithLua(lua_State* L)
{
    luabridge::getGlobalNamespace(L)
        .beginNamespace("Game")
            .beginClass<StateMachine<Miner>>("StateMachine")
                .addFunction("ChangeState", &StateMachine<Miner>::ChangeState)
                .addFunction("GetState", &StateMachine<Miner>::GetState)
                .addFunction("SetState", &StateMachine<Miner>::SetState)
            .endClass()
        .endNamespace();
}

void RegisterEntityWithLua(lua_State* L)
{
    luabridge::getGlobalNamespace(L)
        .beginNamespace("Game")
            .beginClass<Entity>("Entity")
                .addFunction("Name", &Entity::Name)
                .addFunction("ID", &Entity::ID)
            .endClass()
        .endNamespace();
}

void RegisterMinerWithLua(lua_State* L)
{
    luabridge::getGlobalNamespace(L)
        .beginNamespace("Game")
            .deriveClass<Miner, Entity>("Miner")
                .addConstructor<void (*) (std::string)>()
                .addFunction("GetGold", &Miner::GetGold)
                .addFunction("SetGold", &Miner::SetGold)
                .addFunction("AddGold", &Miner::AddGold)
                .addFunction("Fatigued", &Miner::Fatigued)
                .addFunction("DecreaseFatigue", &Miner::DecreaseFatigue)
                .addFunction("IncreaseFatigue", &Miner::IncreaseFatigue)
                .addFunction("GetFSM", &Miner::GetFSM)
                .addFunction("Update", &Miner::Update)
            .endClass()
        .endNamespace();
}

static std::map<std::string, luabridge::LuaRef> base_classes;
static std::map<std::string, luabridge::LuaRef> new_funcs;

luabridge::LuaRef GetLuaClassNew(lua_State* L, std::string className)
{
    if (base_classes.find(className) == base_classes.end())
    {
        auto theClass = luabridge::getGlobal(L, className.c_str());
        base_classes.insert(std::make_pair(className, theClass));
        new_funcs.insert(std::make_pair(className, theClass["new"]));
    }
    return new_funcs.at(className);
}

luabridge::LuaRef LuaNew(lua_State* L, std::string className)
{
    auto new_ = GetLuaClassNew(L, className);
    return new_(base_classes.at(className));
}

