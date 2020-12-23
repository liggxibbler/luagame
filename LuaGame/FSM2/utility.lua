m = {}

function m.split(s, d)
	--print ("splitting " .. s .. " by " .. d)
	t = {}
	for k, v in string.gmatch(s, d) do
		--print ("found key: " .. k)
		table.insert(t, k)
	end
	return t
end

function m.getKeys(t)
    s = {}
    for k, v in pairs(t) do 
        table.insert(s, k)
    end 
    return s 
end

m.instantiate = function(scene)
	scene_instance = {}
	
	for entity, ent_data in pairs(scene) do
		ret = EntMan:CreateEntity(entity)
		table.insert(scene_instance, ret)
		for component, comp_data in pairs(ent_data) do
			print ("component " .. component)
			if component == "tag" then
				ret:SetTag(comp_data)			
			elseif component == "visual" then
				visual = EntMan:CreateRenderComponent(comp_data.width, comp_data.height, comp_data.color[1], comp_data.color[2], comp_data.color[3])			
				RenderMan:Add(visual)
				ret:AddComponent(visual)
				if comp_data.position ~= nil then
					ret:SetPosition(comp_data.position.x, comp_data.position.y)
				end
	
				if comp_data.hasCollider == true then
					print ("has collider")
					collider = EntMan:CreateColliderComponent(comp_data.width, comp_data.height, comp_data.isDynamic)
					CollisionMan:Add(collider, comp_data.isDynamic)	-- These three lines (as well as their counterparts in the previous bit) need to be moved to C and unified
					ret:AddComponent(collider)	-- These three lines (as well as their counterparts in the previous bit) need to be moved to C and unified
				end
	
			elseif component == "brain" then
				lua = EntMan:CreateLuaComponent()
				
				script_name = comp_data.script			
				args = comp_data.args			
				lua_module = require(script_name)
				brain = lua_module:new(args)
	
				lua:SetLuaBrain(brain)
				brain:SetEntity(ret)
				ret:AddComponentByName(lua, script_name)
			end
		end
	end

	for _, v in ipairs(scene_instance) do
		v:OnStart()
	end		

	return scene_instance	
end

m.copyTable = function(source)
	ret = {}	
	for i, v in pairs(source) do
		ret[i] = v
	end
	return ret
end

return m