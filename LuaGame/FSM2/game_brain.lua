Ball = require("Ball")
Paddle = require("Paddle")

game = {balls = 3, score = 0}

game.new = function(self, obj)
	obj = obj or {}
	self.__index = self
	setmetatable(obj, self)
	return obj
end

game.OnEvent = function(self, event)
	
end
	