paddle = {}

paddle.SetEntity = function(self, entity)
	print ("SETTING ENTITY ON PADDLE TO " .. tostring(entity))
	self.entity = entity;
end

paddle.new = function(self, obj)
	obj = obj or {}
	self.__index = self
	setmetatable(obj, self)
	return obj
end

paddle.update = function(self)	
	mouse_x = Input:GetMouseX()
	mouse_y = Input:GetMouseY()

	pos = self.entity:GetPosition()
	diff = {(mouse_x - pos.x) * .16, (mouse_y - pos.y) * .16}

	new_pos = {pos.x + diff[1], pos.y + diff[2]}

	self.entity:SetPosition(new_pos[1], 235)--new_pos[2])
end

paddle.OnCollision = function(self, point)
	--print (point.x, point.y)
end

paddle.OnStart = function(self)
end

return paddle