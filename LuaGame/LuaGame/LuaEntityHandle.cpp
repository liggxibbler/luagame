#include "LuaEntityHandle.h"

void LuaEntityHandle::Register(lua_State* L)
{
	luabridge::getGlobalNamespace(L)
		.beginClass<LuaEntityHandle>("LuaEntityHandle")
			.addFunction("setPosition", &LuaEntityHandle::SetPosition)
			.addFunction("getPosition", &LuaEntityHandle::GetPosition)
		.endClass();
}

void LuaEntityHandle::SetPosition(Vector3 v)
{
	auto trans = m_entity->get<Transform>();
	if (trans)
	{
		trans->SetPosition(v.m_x, v.m_y, v.m_z);
	}
}

Vector3 LuaEntityHandle::GetPosition()
{
	return m_entity->get<Transform>()->GetPosition();
}