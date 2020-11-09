States =
{
	GoHome =
	{
		name = "S1",
		Enter = function(miner)
			print ("[Lua@GoHome]: Walkin' home in the hot n' thusty heat of the desert")
		end,

		Execute = function(miner)
			 print ("[Lua@GoHome]: Back at the shack. Yes siree!")

			if miner:Fatigued() then
				miner:GetFSM():ChangeState(States.Sleep)
			else
				miner:GetFSM():ChangeState(States.GoToMine)
			end
		end,

		Exit = function(miner)
			print ("[Lua@GoHome]: Puttin' mah boots on n' gettin' ready for a day at the mine")
		end
	},

	Sleep = 
	{
		name = "S2",
		Enter = function(miner)
			print ("[Lua@Sleep]: Miner " .. miner:Name() .." is dozin' off")	
		end,
	
		Execute = function(miner)
			if miner:Fatigued() then
				print ("[Lua@Sleep]: ZZZZZZ... ")
				miner:DecreaseFatigue()
			else
				miner:GetFSM():ChangeState(States.GoToMine)
			end
		end,
	
		Exit = function(miner)
			print ("[Lua@Sleep]: Miner " .. miner:Name() .." is feelin' mighty refreshed!")
		end
	},

	GoToMine =
	{
		name = "S3",
		Enter = function(miner)
			print ("[Lua@GoToMine]: Miner " .. miner:Name() .." enters gold mine")
		end,

		Execute = function(miner)
			miner:IncreaseFatigue()
			miner:AddGold(2)
			print ("[Lua@GoToMine]: Miner " .. miner:Name() .." has got " .. miner:GetGold() .. " nuggets")

			if miner:GetGold() > 4 then
				print ("[Lua@GoToMine]: Miner " .. miner:Name() .. " decides to go home, with his pockets full of nuggets")
				miner:GetFSM():ChangeState(States.GoHome)				
			end
		end,

		Exit = function(miner)
			print ("[Lua@GoToMine]: Miner " .. miner:Name() .. " exits gold mine")			
		end
	}
}