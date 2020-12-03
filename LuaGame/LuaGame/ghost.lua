function moveRight(e)
	v = e:getPosition()
	x = v:getX() + 1
	v:setX(x)
	e:setPosition(v)
end

ghost =
{
	Transform = 
	{
		position =
		{
			x = 1,
			y = 5,
			z = 12
		}
	},
	FirstComponent = 
	{
		position =
		{
			x = 12.0,
			y = 1.5,
			z = 4.75			
		}
	},	
	SecondComponent = 
	{
		name = "Frederick",
		path = "C:/"
	}
}