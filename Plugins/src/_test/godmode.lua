function onKeyDown()
	key = GetEventKey()

	groupSelected = GroupUnitsOfPlayerSelected(LocalPlayerId())
	if (GroupSize(groupSelected) < 1) then
		return 
	end

	u = groupSelected[1]

	if (key == 0x209) then
		ForGroup(GroupUnitsOfPlayerSelected(LocalPlayerId()), function(u)
			jass.KillUnit(u)
		end)
		return
	end	

	if (key == 0x105) then
		jass.SetUnitInvulnerable(u, true)
	end
		
	gRange = GroupUnitsInRange(jass.GetUnitX(u), jass.GetUnitY(u), 500)
	FilterGroup(gRange, function(fu)
		return fu ~= u
	end)
	ForGroup(gRange, function(u) 
		if (key == 0x102) then
			jass.SetUnitState(u, UNIT_STATE_LIFE, jass.GetUnitState(u, UNIT_STATE_LIFE) / 2)
		end

		if (key == 0x103) then
			jass.SetUnitOwner(u, LocalPlayer(), true)
		end

		if (key == 0x104) then
			jass.PauseUnit(u, not jass.IsUnitPaused(u))
		end
	end)
end

-- Event handlers
AddEventFunction(EVENT_PLAYER_KEY_DOWN, onKeyDown);
ScreenPrint('|CFFFFF799God mod activated.|R')