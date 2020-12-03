Vector2 = require ("vector2")

ball = {}

ball.new = function(self, obj)
	obj = obj or {}
	self.__index = self
	setmetatable(obj, self)
	return obj
end

ball.vel = Vector2()

ball.OnCollision = function(self, other, collision)
	if other:is("bottom_wall") then
		GameController:OnLoseBall()
	else
		point = collision:getPoint()
		pos = self.entity:getPosition()

		dir = point - pos
		
		point_above_or_below = math.abs(dir.y) > math.abs(dir.x)
		
		if (point_above_or_below) then
			self.vel = Vector2({x = self.vel.x, y = -self.vel.y})
		else
			self.vel = Vector2({x = -self.vel.x, y = self.vel.y})
		end
	end
end

return ball