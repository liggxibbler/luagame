wall = {}

wall.SetEntity = function(self, entity)
	self.entity = entity;
end

wall.new = function(self, obj)
	obj = obj or {}
	self.__index = self
	setmetatable(obj, self)
	return obj
end

wall.update = function(self)	
	--self.entity:SetPosition(self.x, self.y)
end

wall.OnCollision = function(self, point)
	_G.GameController:LostBall()
end

wall.OnStart = function(self)
end

return wall