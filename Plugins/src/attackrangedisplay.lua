-- Copyright (c) 2012, DreamDota Team
-- All rights reserved.
-- 
-- ---
-- Author: flux
--
-- A plugin shows current selected unit's attack range.
--


local DisplayRange = false
local TexturePath = 'ReplaceableTextures\\Selection\\SpellAreaOfEffect_basic.blp'
local UnitImageMap = {} -- imagedata:{image, alpha, alpha_from, alpha_to, alpha_d, range}
setmetatable(UnitImageMap, {__mode = 'k'}) -- weak key
-- local ImageList = {} -- imagedata:{image, alpha, alpha_from, alpha_to, alpha_d, range}
local LastTargetUnit = nil
local RenderInverval = 0.01
local FadeinDuration = 0.5
local FadeoutDuration = 0.5
local MaxAlpha = 192
local MinUpdateAlphaDiff = .5

local function createImage(x, y, radius, r, g, b, alpha)
	local size = radius * 2.13
	local rv = jass.CreateImage(TexturePath, size, size, size, x, y, 0, size / 2 + 12, size / 2 + 12, 0, 2)
	jass.SetImageColor(rv, r, g, b, alpha or 0)
	return rv
end

local function showImage(image, show)
	jass.SetImageRenderAlways(image, show)
	jass.ShowImage(image, show)
end

local function destroyImage(image)
	showImage(image, false)
	jass.DestroyImage(image)
end

local function getHotkey()
	return ProfileGetInt('LastHit', 'Hotkey', KEY_TILDE)
end

local function addUnit(u)
	if UnitImageMap[u] == nil then
		DebugPrint(tostring(u))
		local range = u:range(0)
		local r, g, b = GetPlayerColorRGB(owner)
		local image = createImage(u:x(), u:y(), range, r, g, b, 0)
		showImage(image, true)
		UnitImageMap[u] = {
			image = image, 
			alpha = 0, 
			alpha_from = 0, 
			alpha_to = MaxAlpha, 
			alpha_d = 0, 
			range = range
		}
	end
end

local function removeUnit(u)
	if UnitImageMap[u] ~= nil then
		destroyImage(UnitImageMap[u].image)
		UnitImageMap[u]= nil
	end
end

local function updateTarget()
	if DisplayRange then
		local selected = GroupUnitsOfPlayerSelected(LocalPlayerId())
		if (#selected == 1) then
			if LastTargetUnit ~= nil then
				if selected[1] ~= LastTargetUnit:handleId() then
					-- Selection change
					UnitImageMap[LastTargetUnit].alpha_to = 0
					LastTargetUnit = Unit(selected[1])
					addUnit(LastTargetUnit)
				end
			else
				-- New selection
				LastTargetUnit = Unit(selected[1])
				addUnit(LastTargetUnit)
			end
		else
			-- No selection / More than one unit selected: cancel target
			LastTargetUnit = nil
		end
	else
		if LastTargetUnit ~= nil then
			-- Cancel target
			UnitImageMap[LastTargetUnit].alpha_to = 0
			LastTargetUnit = nil
		end		
	end
end

local function updateUnitImage(unit, imagedata)
	local image = imagedata.image
	
	if unit == LastTargetUnit then
		imagedata.alpha_to = MaxAlpha
	else
		imagedata.alpha_to = 0
	end

	-- resize image
	local range = unit:range(0)
	local owner = unit:owner()
	local r, g, b = GetPlayerColorRGB(jass.GetPlayerColor(jass.Player(owner)))
	if imagedata.range ~= range then
		destroyImage(image)
		image = createImage(unit:x(), unit:y(), range, r, g, b, imagedata.alpha)
		imagedata.image = image
		showImage(image, true)
	end
	
	if imagedata.alpha_to > imagedata.alpha then
		imagedata.alpha_d = imagedata.alpha_d + (MaxAlpha * (RenderInverval / FadeinDuration))
	elseif imagedata.alpha_to < imagedata.alpha then
		imagedata.alpha_d = imagedata.alpha_d - (MaxAlpha * (RenderInverval / FadeoutDuration))
	end

	jass.SetImagePosition(image, unit:x(), unit:y(), 0)
	
	if math.abs(imagedata.alpha_d) >= MinUpdateAlphaDiff then
		-- apply change
		local diff = imagedata.alpha_to - imagedata.alpha
		local d = math.min(math.abs(diff), math.abs(imagedata.alpha_d)) * ((imagedata.alpha_d < 0 and -1) or 1)
		local alpha = imagedata.alpha + d
		imagedata.alpha = alpha
		jass.SetImageColor(image, r, g, b, alpha)
		imagedata.alpha_d = 0
		
		-- finished
		if alpha <= 0 and imagedata.alpha_to == 0 then
			removeUnit(unit)
		end
	end
end

local function render()
	updateTarget()
	for unit, imagedata in pairs(UnitImageMap) do
		updateUnitImage(unit, imagedata)	
	end
end

local function onKeyDown()
	if (GetEventKey() == getHotkey()) then
		DisplayRange = true
	end
end

local function onKeyUp()
	if (GetEventKey() == getHotkey()) then
		DisplayRange = false
	end
end

-- Event handlers
AddEventFunction(EVENT_PLAYER_KEY_DOWN, onKeyDown);
AddEventFunction(EVENT_PLAYER_KEY_UP, onKeyUp);

while true do
	render()
	Wait(RenderInverval)
end