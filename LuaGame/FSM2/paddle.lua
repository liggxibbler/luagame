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
	mouse_x = Input:GetMouseX()
	mouse_y = Input:GetMouseX()
	if Input:GetMouseEvent() then
		print (tostring(mouse_x) .. " " .. tostring(mouse_y))
	end
	self.entity:SetPosition(mouse_x, mouse_y)
end

return paddle