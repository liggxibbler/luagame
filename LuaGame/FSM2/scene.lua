scene =
{
	paddle =
	{
		visual =
		{
			width = 50,
			height = 10,
			color = {0, 255, 128},
			hasCollider = true,
			isDynamic = true
		},		
		brain = {script="paddle"}--Paddle:new()
	},	
	game =
	{
		brain = {script="game_controller"}
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