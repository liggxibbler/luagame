classA = {}

classA.new = function(self, obj)
    obj = obj or {}
    self.__index = self
    setmetatable(obj, self)
    return obj
end

classA.update = function(self)    
    if Input:GetMouseEvent() then        
        x = tostring(Input:GetMouseX())
        y = tostring(Input:GetMouseY())
        buttons = {
            x=Input:GetMouseButton(0),
            y=Input:GetMouseButton(1),
            z=Input:GetMouseButton(2)
        }
        
        print ("Mouse event detected! x=" .. x .. ", y=" .. y .. " buttons = " .. tostring(buttons.x) .. ", " .. tostring(buttons.y) .. ", " .. tostring(buttons.z))
    end
end

return classA