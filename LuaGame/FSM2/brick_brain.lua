brick = {hp = 1}

brick.new = function(self, obj)
	obj = obj or {}
	self.__index = self
	setmetatable(obj, self)
	return obj
end

brick.OnHit = function(self)
	self.hp = self.hp - 1
	if self.hp == 0 then
		Game:OnEvent("brick_destroyed", self)
		Destroy(self)
	end
end

brick.OnCollision = function(self, other)
	self:OnHit()
end

return brick