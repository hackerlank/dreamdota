--[[²âÊÔµ¥Î»²Ù×÷]]--

function onKeyDown()
	if (GetEventKey() == 0x1) then

		ScreenPrint('========================================');
		all = GroupUnitAll()
		ScreenPrint('All group size: ' .. GroupSize(all))
		ForGroup(all, function(u) 
			jass.SetUnitState(u, UNIT_STATE_LIFE, jass.GetUnitState(u, UNIT_STATE_LIFE) - 10)
		end)

		ScreenPrint('========================================');
		selected = GroupUnitsOfPlayerSelected(LocalPlayerId())
		ScreenPrint('selected size: ' .. GroupSize(selected))
		typeid = jass.GetUnitTypeId(selected[1])
		ScreenPrint('selected type id: ' .. ObjectId2S(typeid))

		ScreenPrint('========================================');
		gtypeid = GroupUnitsOfTypeId(typeid)
		ScreenPrint('GroupUnitsOfTypeId size: ' .. GroupSize(gtypeid))

		ScreenPrint('========================================');
		gplayer = GroupUnitsOfPlayer(0)
		ScreenPrint('GroupUnitsOfPlayer size: ' .. GroupSize(gplayer))
		
		ScreenPrint('========================================');
		u = selected[1]
		grange = GroupUnitsInRange(jass.GetUnitX(u), jass.GetUnitY(u), 500)
		ScreenPrint('GroupUnitsInRange size: ' .. GroupSize(grange))
		FilterGroup(grange, function(fu)
			return fu ~= u
		end)
		ScreenPrint('GroupUnitsInRange after size: ' .. GroupSize(grange))
		ForGroup(grange, function(u) 
			jass.SetUnitState(u, UNIT_STATE_LIFE, jass.GetUnitState(u, UNIT_STATE_LIFE) / 2)
		end)
	
	end

	if (GetEventKey() == 0x30) then
		ForGroup(GroupUnitsOfPlayerSelected(LocalPlayerId()), function(u)
			jass.KillUnit(u)
		end)
	end
end

function onKeyUp()
	
end

-- Event handlers
AddEventFunction(EVENT_PLAYER_KEY_DOWN, onKeyDown);
AddEventFunction(EVENT_PLAYER_KEY_UP, onKeyUp);