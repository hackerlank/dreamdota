#ifndef DREAMDOTAMAIN_H_
#define DREAMDOTAMAIN_H_

#include "Game.h"
#include "Event.h"
#include "Timer.h"
#include "GameTime.h"
#include "Profile.h"
#include "OptionMenu.h"
#include "Jass.h"
#include "Input.h"
#include "TextTagManager.h"
#include "DebugPanel.h"
#include "UnitGroup.h"
#include "Action.h"
#include "Latency.h"
#include "Stochastic.h"
#include "MissileManager.h"
#include "LastHit.h"
#include "DamageDisplay.h"
#include "CustomCamera.h"
#include "DirectionMove.h"
#include "SmartDeny.h"
#include "MapHack.h"
#include "MinimapPingEnemyHero.h"
#include "RuneNotify.h"
#include "ShowCooldown.h"
#include "CommandThrough.h"
#include "Invoker.h"
#include "InvisibleDisplay.h"

#include "../DreamAuth2/StringManager.h"


void DreamDota_Init( );
void DreamDota_Cleanup( );

#endif