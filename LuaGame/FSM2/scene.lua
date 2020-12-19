scene =
{
	game =
	{
		brain = {script="game_controller"},
	},
	wall_left = 
	{
		visual =
		{
			position = {x=-10, y=120},
			width = 20,
			height = 250,
			color = {0, 0, 255},
			hasCollider = true,
			isDynamic = false
		}
	},
	wall_right = 
	{
		visual =
		{
			position = {x=330, y=120},
			width = 20,
			height = 250,
			color = {0, 0, 255},
			hasCollider = true,
			isDynamic = false
		}
	},
	wall_top = 
	{
		visual =
		{
			position = {x=160, y=-10},
			width = 330,
			height = 20,
			color = {0, 0, 255},
			hasCollider = true,
			isDynamic = false
		}
	},
	wall_bottom = 
	{
		visual =
		{
			position = {x=160, y=250},
			width = 330,
			height = 20,
			color = {0, 0, 255},
			hasCollider = true,
			isDynamic = false
		}
	}
}

return scene

--	ball = {
--		dimension = {
--			width = 10,
--			height = 10
--		},
--		color = {255, 255, 255},
--		brain = ""
--	}
--	
--	brick = {
--		dimension = {		
--			width = 30,
--			height = 15
--		},
--		color = {255, 255, 0},
--		brain = ""
--	}