Paddle = require("paddle")

scene =
{
	paddle =
	{
		visual =
		{
			width = 20,
			height = 20,
			color = {0, 255, 128}
		},
		brain = Paddle:new()
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