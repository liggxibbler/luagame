utility = require('utility')
scene = require("scene")

print ("inp = " .. tostring(Input))
print ("ent = " .. tostring(EntMan.CreateEntity))

for entity, ent_data in pairs(scene) do	
	ret = EntMan:CreateEntity(entity)
	for component, comp_data in pairs(ent_data) do
		print ("component " .. component)		
		if component == "visual" then
			visual = EntMan:CreateRenderComponent(comp_data.width, comp_data.height, comp_data.color[1], comp_data.color[2], comp_data.color[3])
			visual:SetEntity(ret)
			RenderMan:Add(visual)
			ret:AddComponent(visual)
		elseif component == "brain" then
			lua = EntMan:CreateLuaComponent()
			lua:SetLuaBrain(comp_data)
			comp_data:SetEntity(ret)
			ret:AddComponent(lua)
		end
	end
end