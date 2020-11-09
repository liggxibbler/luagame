#pragma once

#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>

template <class entity_type>
class StateMachine
{
private:

    entity_type* m_pOwner;
    luabridge::LuaRef m_CurrentState;

public:

    StateMachine(entity_type* owner) :m_pOwner(owner), m_CurrentState(nullptr) {}
    ~StateMachine()
    {        
    }

    void SetState(const luabridge::LuaRef& s) { m_CurrentState = s; }

    void Update()
    {
        if (!m_CurrentState.isNil() && m_CurrentState.isTable())
        {
            m_CurrentState["Execute"](m_pOwner);
        }
    }

    void ChangeState(const luabridge::LuaRef& new_state)
    {
        m_CurrentState["Exit"](m_pOwner);
        m_CurrentState = new_state;
        m_CurrentState["Enter"](m_pOwner);
    }

    const luabridge::LuaRef& GetState()const { return m_CurrentState; }
};