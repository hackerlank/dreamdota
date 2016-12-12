function LocalPlayerId()
	return jass.GetPlayerId(jass.GetLocalPlayer())
end

LocalPlayer = jass.GetLocalPlayer

local player_color_table = {}
player_color_table[PLAYER_COLOR_RED] = {r = 255, g = 3, b = 3}
player_color_table[PLAYER_COLOR_BLUE] = {r = 0, g = 66, b = 255}
player_color_table[PLAYER_COLOR_CYAN] = {r = 28, g = 230, b = 185}
player_color_table[PLAYER_COLOR_PURPLE] = {r = 84, g = 0, b = 129}
player_color_table[PLAYER_COLOR_YELLOW] = {r = 255, g = 252, b = 1}
player_color_table[PLAYER_COLOR_ORANGE] = {r = 254, g = 138, b = 14}
player_color_table[PLAYER_COLOR_GREEN] = {r = 32, g = 192, b = 0}
player_color_table[PLAYER_COLOR_PINK] = {r = 229, g = 91, b = 176}
player_color_table[PLAYER_COLOR_LIGHT_GRAY] = {r = 149, g = 150, b = 151}
player_color_table[PLAYER_COLOR_LIGHT_BLUE] = {r = 126, g = 191, b = 241}
player_color_table[PLAYER_COLOR_AQUA] = {r = 16, g = 98, b = 70}
player_color_table[PLAYER_COLOR_BROWN] = {r = 78, g = 42, b = 4}

function GetPlayerColorRGB(color) 
	data = player_color_table[color];
	if (data) then
		return data.r, data.g, data.b
	else
		return 255, 255, 255
	end
end