#include "Utility.h"
#include "EntityManager.h"
#include "InputManager.h"
#include "Entity.h"
#include <iostream>
#include <SDL.h>

#define LUA_NEW(base) LuaHelper::LuaNew(L, base)
#define CALL_LUA_FUNCTION(object, function) object[function](object)
#define CALL_LUA_FUNCTION1(object, function, arg) object[function](object, arg)

#define LUA_CHECK(L, func, arg)\
if (func(L, arg) != 0)\
{\
	std::cout << "Lua error: " << lua_tostring(L, -1) << std::endl;\
	return -1;\
}\

Game::InputManager gInputManager;
Game::RenderManager gRenderManager;
ECS::EntityManager gEntityManager;
Game::CollisionManager gCollisionManager;

std::vector<ECS::Entity*> gEntites;

bool HandleSdlEvents(Game::InputManager& input_manager)
{
	static bool quit = false;
	SDL_Event e;
	input_manager.InitFrame();
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
			quit = true;
		input_manager.HandleEvent(e);		
	}
	return quit;
}

void UpdateEntities(lua_State* L)
{
	try
	{
		gEntityManager.Update();
	}
	catch (luabridge::LuaException e)
	{
		std::cout << "failed to call - " << e.what() << std::endl;
	}
}

void InitializeInputManager(lua_State* L)
{
	Game::InputManager::RegisterWithLua(L);
	luabridge::setGlobal<Game::InputManager*>(L, &gInputManager, "Input");
}

void InitializeEntityManager(lua_State* L)
{
	ECS::EntityManager::RegisterWithLua(L);
	luabridge::setGlobal<ECS::EntityManager*>(L, &gEntityManager, "EntMan");
}

void InitializeRenderManager(lua_State* L)
{
	gRenderManager.Initialize();
	Game::RenderManager::RegisterWithLua(L);
	luabridge::setGlobal<Game::RenderManager*>(L, &gRenderManager, "RenderMan");	
}

void InitializeCollisionManager(lua_State* L)
{
	gCollisionManager.Initialize();
	Game::CollisionManager::RegisterWithLua(L);
	luabridge::setGlobal<Game::CollisionManager*>(L, &gCollisionManager, "CollisionMan");
}

int main(int argc, char** argv)
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	InitializeInputManager(L);
	InitializeEntityManager(L);
	InitializeRenderManager(L);
	InitializeCollisionManager(L);

	// Run the main Lua script
	LUA_CHECK(L, luaL_dofile, "main.lua");

	bool quit = false;
	while (!quit)
	{
		gCollisionManager.Update();
		quit = HandleSdlEvents(gInputManager);
		UpdateEntities(L);
		gRenderManager.Render();
		SDL_Delay(15);
		gRenderManager.UpdateSurface();
	}

	return 0;
}