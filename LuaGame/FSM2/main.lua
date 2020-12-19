utility = require('utility')
scene = require("scene")

print ("inp = " .. tostring(Input))
print ("ent = " .. tostring(EntMan))
print ("col = " .. tostring(CollisionMan))

for entity, ent_data in pairs(scene) do	
	ret = EntMan:CreateEntity(entity)
	for component, comp_data in pairs(ent_data) do
		print ("component " .. component)		
		if component == "visual" then
			visual = EntMan:CreateRenderComponent(comp_data.width, comp_data.height, comp_data.color[1], comp_data.color[2], comp_data.color[3])			
			RenderMan:Add(visual)
			ret:AddComponent(visual)

			if comp_data.hasCollider == true then
				print ("has collider")
				collider = EntMan:CreateColliderComponent(comp_data.width, comp_data.height, comp_data.isDynamic)
				CollisionMan:Add(collider, comp_data.isDynamic)	-- These three lines (as well as their counterparts in the previous bit) need to be moved to C and unified
				ret:AddComponent(collider)	-- These three lines (as well as their counterparts in the previous bit) need to be moved to C and unified
			end

		elseif component == "brain" then
			lua = EntMan:CreateLuaComponent()			
			
			script = comp_data.script			
			args = comp_data.args			
			lua_module = require(script)
			brain = lua_module:new(args)

			lua:SetLuaBrain(brain)
			brain:SetEntity(ret)
			ret:AddComponent(lua)
		end
	end
end