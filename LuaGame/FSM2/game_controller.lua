utility = require("utility")
brick_prefab = require("brick")
ball_prefab = require("ball")
paddle_prefab = require("paddle")

gc = {score = 0, lives = 3, state = 0}

gc.states = 
{
	init = 0,
	play = 1,
	gameOver = 2
}

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
	self:LayBricks(5, 14)
	self:MakeBall()	
end

gc.MakePaddle = function(self)
	self.paddle = utility.instantiate(paddle_prefab)[1]:GetComponent("paddle_brain"):GetLuaBrain()
end

gc.LayBricks = function(self, rows, cols)
	self.bricks = {}
	x0 = 0--160
	y0 = 0--50
	for j = 1, rows do
		for i = 1, cols do
			ent = EntMan:CreateEntity("brick"..tostring(i).."x"..tostring(j))
			brick = utility.instantiate(brick_prefab)[1]:GetComponent("brick_brain"):GetLuaBrain()
			brick.entity:SetPosition(x0 + i * 21, y0 + j * 11);
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
	self.lives = self.lives - 1
	print ("Lost a ball - " .. tostring(self.lives) .. " balls remaining")
	if self.lives == 0 then self:OnGameOver() end
	self.ball:OnLost()
end

gc.ResetBricks = function(self)
	for i=1,#self.bricks do
		self.bricks[i].entity:SetActive(true)
	end
end

gc.OnGameOver = function(self)
	print ("Game Over!")
	self.state = self.states.gameOver
	self.score = 0
	self.lives = 3
end

gc.update = function(self)
	if self.state == self.states.gameOver then
		if Input:GetMouseButton(0) then
			self:ResetBricks()
			self.state = self.states.play
		end
	end
end

return gc