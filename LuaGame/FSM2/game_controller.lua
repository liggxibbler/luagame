utility = require("utility")
brick_prefab = require("brick")
ball_prefab = require("ball")
paddle_prefab = require("paddle")

gc = {}

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
	self:MakePaddle()
	self:LayBrick(5, 5)
	self:MakeBall()
end

gc.MakePaddle = function(self)
	self.paddle = utility.instantiate(paddle_prefab)[1]:GetComponent("paddle_brain"):GetLuaBrain()
end

gc.LayBrick = function(self, rows, cols)
	self.bricks = {}
	for j = 1, rows do
		for i = 1, cols do
			ent = EntMan:CreateEntity("brick"..tostring(i).."x"..tostring(j))
			brick = utility.instantiate(brick_prefab)
			brick[1]:SetPosition(i * 22, j * 12);
			table.insert(self.bricks, brick)
		end
	end
end	

gc.MakeBall = function(self)
	self.ball = utility.instantiate(ball_prefab)[1]:GetComponent("ball_brain"):GetLuaBrain()	
	self.ball:SetPaddle(self.paddle)
	print ("PADDLE'S ENTITY IS " .. tostring(self.ball.paddle.entity))
end

gc.update = function(self)
end

return gc