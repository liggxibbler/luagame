classA = {}
classA.x = 1

classA.getX = function(self)
    return self.x
end

classA.setX = function(self, val)
    print("setting x to " .. val)
    self.x = val
end

classA.new = function(self, obj)
    obj = obj or {}
    self.__index = self
    setmetatable(obj, self)
    return obj
end

classA.setEntity = function(self, e)
    self.entity = e
end

classA.getEntity = function(self)
    return self.e
end

classA.update = function(self)    
    self.x = -self.x    
end
