--[[
Plugin Name: Minimap Ping
Plugin URI: http://dreamdota.com/
Description: 定期小地图ping敌方英雄位置
Author: DreamDota
Version: 1.0.1
Author URI: http://dreamdota.com/
]]

local keycode = ConfigData('KEY_MINIMAPPING') or 36 --default is [HOME]
local enabled = false
local enemy_hero_map = {}
local timer = CreateTimer(1.0, true, function()
	for u, dummy in pairs(enemy_hero_map) do
		if (jass.GetUnitState(u, UNIT_STATE_LIFE) > 0) then
			r, g, b = GetPlayerColorRGB(jass.GetPlayerColor(jass.GetOwningPlayer(u)))
			jass.PingMinimapEx(jass.GetUnitX(u), jass.GetUnitY(u), 1.0 ,r ,g, b, false)
		end
	end
end)

AddEventFunction(EVENT_GAME_ENTER_REGION, function()
	local u = jass.GetTriggerUnit()
	if (jass.IsUnitType(u, UNIT_TYPE_HERO) and jass.IsPlayerEnemy(LocalPlayer(), jass.GetOwningPlayer(u))) then
		if (nil == enemy_hero_map[u]) then
			enemy_hero_map[u] = true
		end
	end
end)

ListenKeyCode(keycode)
AddEventFunction(EVENT_PLAYER_KEY_DOWN, function()
	if (GetEventKey() == keycode) then
		enabled = enabled == false
		if (enabled) then
			ScreenPrint("Minimap Ping Enabled")
			StartTimer(timer)
		else
			ScreenPrint("Minimap Ping Disabled")
			PauseTimer(timer)
		end
	end
end)