States =
{
	GoHome =
	{
		name = "S1",
		Enter = function(miner)
			print ("[Lua]: Walkin' home in the hot n' thusty heat of the desert")
		end,

		Execute = function(miner)
			 print ("[Lua]: Back at the shack. Yes siree!")

			if miner:Fatigued() then
				miner:GetFSM():ChangeState(States.Sleep)
			else
				miner:GetFSM():ChangeState(States.GoToMine)
			end
		end,

		Exit = function(miner)
			print ("[Lua]: Puttin' mah boots on n' gettin' ready for a day at the mine")
		end
	},

	Sleep = 
	{
		name = "S2",
		Enter = function(miner)
			print ("[Lua]: Miner " .. miner:Name() .." is dozin' off")	
		end,
	
		Execute = function(miner)
			if miner:Fatigued() then
				print ("[Lua]: ZZZZZZ... ")
				miner:DecreaseFatigue()
			else
				miner:GetFSM():ChangeState(States.GoToMine)
			end
		end,
	
		Exit = function(miner)
			if miner == nil then
				print (name .. "miner is nil")
			else
				print ("[Lua]: Miner " .. miner:Name() .." is feelin' mighty refreshed!")	
			end
		end
	},

	GoToMine =
	{
		name = "S3",
		Enter = function(miner)
			print ("[Lua]: Miner " .. miner:Name() .." enters gold mine")
		end,

		Execute = function(miner)
			miner:IncreaseFatigue()
			miner:AddGold(2)
			print ("[Lua]: Miner " .. miner:Name() .." has got " .. miner:GetGold() .. " nuggets")

			if miner:GetGold() > 4 then
				print ("[Lua]: Miner " .. miner:Name() .. " decides to go home, with his pockets full of nuggets")
				miner:GetFSM():ChangeState(States.GoHome)
				print ("TEST")
			end
		end,

		Exit = function(miner)
			if miner == nil then
				print (name .. "miner is nil")
			else
				print ("[Lua]: Miner " .. miner:Name() .. " exits gold mine")
			end
		end
	}
}