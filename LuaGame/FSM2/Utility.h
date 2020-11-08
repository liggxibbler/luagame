#pragma once

#include "StateMachine.h"
#include "Miner.h"

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