#include "stdafx.h"
#include "RaceIcon.h"
#include "Player.h"
#include "Jass.h"
#include "UISimpleFrame.h"

static const float RACE_ICON_PLAYER_ID_OFFSET = 0.0035f;

void RaceIconPathCalc (uint32_t race, const char **icon, const char **iconDis)
{
	switch (race)
	{
	case Jass::RACE_HUMAN:
		*icon = "UI\\Widgets\\BattleNet\\chaticons\\tier1-human.blp";
		*iconDis = "UI\\Widgets\\BattleNet\\chaticons\\tier1-human-off.blp";
		break;
	case Jass::RACE_ORC:
		*icon = "UI\\Widgets\\BattleNet\\chaticons\\tier1-orc.blp";
		*iconDis = "UI\\Widgets\\BattleNet\\chaticons\\tier1-orc-off.blp";
		break;
	case Jass::RACE_UNDEAD:
		*icon = "UI\\Widgets\\BattleNet\\chaticons\\tier1-undead.blp";
		*iconDis = "UI\\Widgets\\BattleNet\\chaticons\\tier1-undead-off.blp";
		break;
	case Jass::RACE_NIGHTELF:
		*icon = "UI\\Widgets\\BattleNet\\chaticons\\tier1-nightelf.blp";
		*iconDis = "UI\\Widgets\\BattleNet\\chaticons\\tier1-nightelf-off.blp";
		break;
	default:
		*icon = "UI\\Widgets\\BattleNet\\chaticons\\bnet-unknown.blp";
		*iconDis = "UI\\Widgets\\BattleNet\\chaticons\\bnet-unknown.blp";
		break;
	}
}

RaceIcon::RaceIcon( IUIObject *parent, float width, float height, int player )
	: Frame(parent, width, height), bWantRefresh(false), playerNumber(player)
{
	char playerNum[10];
	sprintf_s(playerNum, "%02d", (playerNumber >= 0 && playerNumber <= 15) ? playerNumber : 15);
	//std::string strPath = "ReplaceableTextures\\TeamColor\\TeamColor";
	//strPath += playerNum;
	//strPath += ".blp";

	colorTexture = new Texture(this, width, height);//, strPath.c_str(), strPath.c_str() );
	Color playerColor = GetPlayerColor(player, false);
	playerColor.a = 0xC0;
	colorTexture->fillColor(playerColor);
	colorTexture->setOwner(this);
	colorTexture->setRelativePosition(POS_C, this, POS_C);

	float size = min(width, height);

	const char *icon, *iconDis;
	RaceIconPathCalc(PlayerRace(player), &icon, &iconDis);

	raceIcon = new Texture(colorTexture, size, size, icon, iconDis);
	raceIcon->setOwner(this);
	raceIcon->setRelativePosition(POS_L, this, POS_L, 0, 0);

	playerId = new Label(colorTexture, "", size * 0.35f, Color::WHITE);
	playerId->setText("%d", player+1);
	playerId->setOwner(this);
	playerId->setRelativePosition(POS_C, this, POS_R, -RACE_ICON_PLAYER_ID_OFFSET, 0);
}

RaceIcon::~RaceIcon()
{
	delete raceIcon;
	delete colorTexture;
	delete playerId;
}

void RaceIcon::setAbsolutePosition( uint32_t originPos, float absoluteX, float absoluteY )
{
	Frame::setAbsolutePosition(originPos, absoluteX, absoluteY);
	//getFrame()->setAbsolutePosition(originPos, absoluteX, absoluteY);
	//getFrame()->applyPosition();
// 	colorTexture->setAbsolutePosition(originPos, absoluteX, absoluteY);
// 	raceIcon->setAbsolutePosition(originPos, absoluteX, absoluteY);
	bWantRefresh = true;
}

void RaceIcon::setRelativePosition( uint32_t originPos, IUIObject* target, uint32_t toPos, float relativeX /*= 0*/, float relativeY /*= 0 */ )
{
	Frame::setRelativePosition(originPos, target, toPos, relativeX, relativeY);
	//getFrame()->setRelativePosition(originPos, target->getFrame(), toPos, relativeX, relativeY);
	//getFrame()->applyPosition();
// 	colorTexture->setRelativePosition(originPos, target, toPos, relativeX, relativeY);
// 	raceIcon->setRelativePosition(originPos, target, toPos, relativeX, relativeY);
	bWantRefresh = true;
}

void RaceIcon::setRelativePosition( uint32_t originPos, UILayoutFrame* target, uint32_t toPos, float relativeX /*= 0*/, float relativeY /*= 0 */ )
{
	Frame::setRelativePosition(originPos, target, toPos, relativeX, relativeY);
	//getFrame()->setRelativePosition(originPos, target, toPos, relativeX, relativeY);
	//getFrame()->applyPosition();
// 	colorTexture->setRelativePosition(originPos, target, toPos, relativeX, relativeY);
// 	raceIcon->setRelativePosition(originPos, target, toPos, relativeX, relativeY);
	bWantRefresh = true;
}

void RaceIcon::setParent( IUIObject *parent )
{
	Frame::setParent(parent);
	colorTexture->setParent(this);
	raceIcon->setParent(colorTexture);
	playerId->setParent(colorTexture);
}

void RaceIcon::setParent( UISimpleFrame *parent )
{
	Frame::setParent(parent);
	colorTexture->setParent(this);
	raceIcon->setParent(colorTexture);
	playerId->setParent(colorTexture);
}

void RaceIcon::setHeight( float height )
{
	Frame::setHeight(height);
	colorTexture->setHeight(height);
}

void RaceIcon::tick()
{
	Frame::tick();
	if (bWantRefresh)
	{
		refresh();
		bWantRefresh = false;
	}
}

void RaceIcon::refresh()
{
	Frame::refresh();
	colorTexture->refresh();
	colorTexture->setRelativePosition(POS_C, this, POS_C);
	raceIcon->refresh();
	raceIcon->setRelativePosition(POS_L, this, POS_L, 0, 0);
	playerId->refresh();
	playerId->setRelativePosition(POS_C, this, POS_R, -RACE_ICON_PLAYER_ID_OFFSET, 0);
}

int RaceIcon::player() const
{
	return playerNumber;
}

void RaceIcon::setPlayer( int player )
{
	if (playerNumber != player)
	{
		playerNumber = player;
		bWantRefresh = true;
	}
}
