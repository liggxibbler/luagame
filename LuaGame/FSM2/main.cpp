#include "Utility.h"
#include "InputManager.h"
#include <iostream>
#include <SDL.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define LUA_NEW(base) LuaHelper::LuaNew(L, base)
#define CALL_LUA_FUNCTION(object, function) object[function](object)
#define CALL_LUA_FUNCTION1(object, function, arg) object[function](object, arg)

#define LUA_CHECK(L, func, arg)\
if (func(L, arg) != 0)\
{\
	std::cout << "Lua error: " << lua_tostring(L, -1) << std::endl;\
	return -1;\
}\
else\
	std::cout << "something" << std::endl;\


Game::InputManager* input_manager = nullptr;
SDL_Window* gWindow = nullptr;

bool HandleSdlEvents(Game::InputManager* input_manager)
{
	static bool quit = false;
	SDL_Event e;
	input_manager->InitFrame();
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
			quit = true;
		input_manager->HandleEvent(e);		
	}
	return quit;
}

void UpdateEntities(lua_State* L)
{
	auto update = luabridge::getGlobal(L, "update");
	try
	{
		update();
	}
	catch (luabridge::LuaException e)
	{
		std::cout << "failed to call - " << e.what() << std::endl;
	}
}

void InitializeInputManager(lua_State* L)
{
	// Register InputManager class with Lua
	Game::InputManager::RegisterWithLua(L);

	// Construct InputManager "Singleton instance"
	input_manager = new Game::InputManager();

	// Pass pointer of InputManager "Singleton instance" to Lua
	luabridge::setGlobal<Game::InputManager*>(L, input_manager, "Input");
}

void InitializeSDL()
{
	// Half-assedly intialize SDL
	SDL_Init(SDL_INIT_VIDEO);
	gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
}

int main(int argc, char** argv)
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	InitializeInputManager(L);
	
	InitializeSDL();
	
	// Run the main Lua script
	LUA_CHECK(L, luaL_dofile, "main.lua");
	
	bool quit = false;
	while (!quit)
	{
		quit = HandleSdlEvents(input_manager);
		UpdateEntities(L);
	}

	return 0;
}