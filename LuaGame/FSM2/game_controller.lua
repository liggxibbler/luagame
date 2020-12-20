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
	_G.GameController = self	
	self:MakePaddle()
	self:LayBrick(5, 13)
	self:MakeBall()	
end

gc.MakePaddle = function(self)
	self.paddle = utility.instantiate(paddle_prefab)[1]:GetComponent("paddle_brain"):GetLuaBrain()
end

gc.LayBrick = function(self, rows, cols)
	self.bricks = {}
	x0 = 0--160
	y0 = 0--50
	for j = 1, rows do
		for i = 1, cols do
			ent = EntMan:CreateEntity("brick"..tostring(i).."x"..tostring(j))
			brick = utility.instantiate(brick_prefab)
			brick[1]:SetPosition(x0 + i * 21, y0 + j * 11);
			table.insert(self.bricks, brick)
		end
	end
end	

gc.MakeBall = function(self)
	self.ball = utility.instantiate(ball_prefab)[1]:GetComponent("ball_brain"):GetLuaBrain()	
	self.ball:SetPaddle(self.paddle)
	print ("PADDLE'S ENTITY IS " .. tostring(self.ball.paddle.entity))
end

gc.LostBall = function(self)
	self.ball:OnLost()
end

gc.update = function(self)
end

return gc