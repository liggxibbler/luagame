require ("math")

ball = {vx_default = 15, vy_default = -15, vx = 0, vy = 0}

ball.SetEntity = function(self, entity)
	self.entity = entity;
end

ball.new = function(self, obj)
	obj = obj or {}
	self.__index = self
	setmetatable(obj, self)
	return obj
end

ball.states =
{
	init = 0,
	play = 1
}

ball.state = 0

ball.OnCollision = function(self, point)
	--if other:is("bottom_wall") then
	--	GameController:OnLoseBall()
	--else
		--point = collision:getPoint()
		--pos = self.entity:getPosition()

		if math.abs(point.y) > math.abs(point.x) then
			self.vy = -self.vy
		else
			self.vx = -self.vx
		end	
end

ball.SetPaddle = function(self, paddle)	
	self.paddle = paddle
end

ball.update = function(self)	
	if self.state == self.states.init then		
		pos = self.paddle.entity:GetPosition()
		self.entity:SetPosition(pos.x, pos.y - 10)
		if Input:GetMouseButton(0) then
			self.state = self.states.play
			self.vx = self.vx_default
			self.vy = self.vy_default
		end
	elseif self.state == self.states.play then
		pos = self.entity:GetPosition()
		dx, dy = self.vx * .16, self.vy * .16
		--print (tostring(dx) .. ", " .. tostring(dy))
		self.entity:SetPosition(pos.x + dx, pos.y + dy)
	end
end

ball.OnStart = function(self)
end

return ball