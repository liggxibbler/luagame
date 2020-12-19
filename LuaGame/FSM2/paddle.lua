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
		brain = {script="paddle_brain"}--Paddle:new()
	}
}

return scene