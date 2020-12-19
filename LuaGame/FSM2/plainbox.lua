paddle = {}

paddle.SetEntity = function(self, entity)
	self.entity = entity;
end

paddle.new = function(self, obj)
	obj = obj or {}
	self.__index = self
	setmetatable(obj, self)
	return obj
end

paddle.update = function(self)	
	self.entity:SetPosition(self.x, self.y)
end

paddle.OnCollision = function(self, point)
	--print (point.x, point.y)
end

return paddle