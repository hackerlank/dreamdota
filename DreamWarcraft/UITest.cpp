#include "stdafx.h"
#include "UITest.h"
#include "DebugPanel.h"
#include "Event.h"
#include "Game.h"
#include "Unit.h"
#include "Tools.h"
#include "Timer.h"

#include "UISimpleTexture.h"
#include "Texture.h" 
#include "Table.h"
#include "Label.h"
#include "CheckBox.h"
#include "MultiIcon.h"
#include "RaceIcon.h"
#include "Bar.h"

void UITest() 
{
	Texture *tx = new Texture(UI_NULL, 0.038, 0.038, "ReplaceableTextures\\CommandButtons\\BTNAdvStruct.blp");
	tx->setAbsolutePosition(POS_C, 0.4, 0.3);
}

static void onLocalChat (const Event *evt) 
{
	LocalChatEventData* data = evt->data<LocalChatEventData>();
	const char* text = data->content;
	if (text[0] == 'u') 
	{
		OutputScreen(10, "UITest");
		UITest();
	}
}

void UITest_Init() 
{
	MainDispatcher()->listen(EVENT_LOCAL_CHAT, onLocalChat);
}

void UITest_Cleanup() 
{
}