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

return m