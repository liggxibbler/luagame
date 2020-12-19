Paddle = require("paddle")
PlainBox = require("plainbox")

scene =
{
	paddle =
	{
		visual =
		{
			width = 20,
			height = 80,
			color = {0, 255, 128},
			hasCollider = true,
			isDynamic = true
		},		
		brain = {script="paddle"}--Paddle:new()
	},
	plain =
	{
		visual =
		{
			width = 40,
			height = 10,
			color = {255, 0, 255},
			hasCollider = true,
			isDynamic = false
		},		
		brain = {script="plainbox", args={x=20, y=30}}--PlainBox:new({x=20, y=30})
	},
	plain2 =
	{
		visual =
		{
			width = 40,
			height = 10,
			color = {255, 0, 255},
			hasCollider = true,
			isDynamic = false
		},		
		brain = {script="plainbox", args={x=100, y=200}}--PlainBox:new({x=100, y=200})
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