-- table GroupUnitAll() native

-- table GroupUnitsOfTypeId(int typeid) native

-- table GroupUnitsOfPlayer(int player_id) native

-- table GroupUnitsOfPlayerSelected(int player_id) native

-- table GroupUnitsInRange(float x, float y, float r) native

-- int GroupSize(table which) native

-- void ForGroup(table which, function callback) native

-- void FilterGroup(table which, function callback) native

-- int/false GroupHasUnit(table g, unit u) native

-- void GroupAddUnit(unitgroup g, unit u)
function GroupAddUnit(g, u)
	if (not GroupHasUnit(g, u)) then
		table.insert(g, u)
	end
end

-- void GroupRemoveUnit(unitgroup g, unit u)
function GroupRemoveUnit(g, u)
	local index = GroupHasUnit(g, u)
	if (index ~= false) then
		table.remove(g, index)
	end
end