utility = require("utility")
brick_prefab = require("brick")

gc = {brickPrefab = nil}

gc.SetEntity = function(self, entity)
	self.entity = entity;
end

gc.new = function(self, obj)
	obj = obj or {}
	self.__index = self
	setmetatable(obj, self)
	return obj
end

gc.OnStart = function(self)
	self.brickPrefab = brick_prefab	
	self:LayBrick(5, 5)
end

gc.LayBrick = function(self, rows, cols)
	self.bricks = {}
	for j = 1, rows do
		for i = 1, cols do
			ent = EntMan:CreateEntity("brick"..tostring(i).."x"..tostring(j))
			brick = utility.instantiate(self.brickPrefab)			
			print("brick1="..tostring(brick[1]))
			brick[1]:SetPosition(i * 30, j * 30);
			table.insert(self.bricks, brick)
		end
	end
end	

gc.update = function(self)
end

return gc