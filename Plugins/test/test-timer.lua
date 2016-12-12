--[[Timer≤‚ ‘]]--

local t = CreateTimer(10, true, function()
	ScreenPrint("Timer:GameTime: "..GameTime())
end)
StartTimer(t)

while(true) do
	Wait(7)
	ScreenPrint("Wait:Elapsed: ".. TimerGetElapsed(t))
	ScreenPrint("Wait:Remaining: ".. TimerGetRemaining(t))
	ScreenPrint("Wait:Timeout: ".. TimerGetTimeout(t))
end