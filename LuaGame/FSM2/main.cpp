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
SDL_Renderer* gRenderer = nullptr;
SDL_Surface* gSurface = nullptr;

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
	try
	{
		auto update = luabridge::getGlobal(L, "update");
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
	gSurface = SDL_GetWindowSurface(gWindow);
	gRenderer = SDL_CreateRenderer(gWindow, -1, 0);	
}

void RenderThings()
{
	SDL_Rect rect;
	
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
	SDL_RenderClear(gRenderer);
	SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
	
	rect.x = input_manager->GetMouseX();
	rect.y = input_manager->GetMouseY();
	rect.w = 10;
	rect.h = 10;
	SDL_RenderFillRect(gRenderer, &rect);

	rect.x = 320 - input_manager->GetMouseX();
	rect.y = 240 - input_manager->GetMouseY();
	rect.w = 10;
	rect.h = 10;
	SDL_RenderFillRect(gRenderer, &rect);
	
	SDL_RenderPresent(gRenderer);
}

void LoadScene(std::string scene)
{
	std::string path = scene + ".lua";
	
}

int main(int argc, char** argv)
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	// Run the main Lua script
	LUA_CHECK(L, luaL_dofile, "main.lua");

	InitializeInputManager(L);
	
	LoadScene("scene");

	InitializeSDL();
	
	bool quit = false;
	while (!quit)
	{
		quit = HandleSdlEvents(input_manager);
		UpdateEntities(L);
		RenderThings();
		SDL_Delay(15);
		SDL_UpdateWindowSurface(gWindow);
	}

	return 0;
}