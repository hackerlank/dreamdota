#ifndef PLAYER_H_
#define PLAYER_H_

class Unit;

#include "GameStructs.h"
#include "IUIObject.h"


const int PLAYER_ANY = -1;//常量，在filter中代表任意玩家

int PlayerLocal ();//本地玩家

war3::CPlayerWar3* PlayerObject(int playerId);

Color GetPlayerColor(int playerId, bool correntLightness);
Color GetPlayerColor(int playerId, uint32_t &r, uint32_t &g, uint32_t &b, uint32_t &alpha, bool correntLightness);
const char *GetPlayerColorString(int playerId, bool correntLightness = true);
uint32_t PlayerRace (int inPlayerId);
int PlayerTeam (int inPlayerId);
const char *PlayerName (int inPlayerId);
war3::CPlayerWar3* PlayerObjectLocal();
void SetLocalSubgroup (Unit *u);

//对应jass常量
bool AllianceMatch (
	int playerIdSource,
	int playerIdOther,
	uint32_t reqField,
	uint32_t excludeField
);

struct PlayerFilter {
	static const uint32_t ALLIANCE_PASSIVE					= (1 << 0);
	static const uint32_t ALLIANCE_HELP_REQUEST				= (1 << 1);
	static const uint32_t ALLIANCE_HELP_RESPONSE			= (1 << 2);
	static const uint32_t ALLIANCE_SHARED_XP				= (1 << 3);
	static const uint32_t ALLIANCE_SHARED_SPELLS			= (1 << 4);
	static const uint32_t ALLIANCE_SHARED_VISION			= (1 << 5);
	static const uint32_t ALLIANCE_SHARED_CONTROL			= (1 << 6);
	static const uint32_t ALLIANCE_SHARED_ADVANCED_CONTROL	= (1 << 7);
	static const uint32_t ALLIANCE_RESCUABLE				= (1 << 8);
	static const uint32_t ALLIANCE_SHARED_VISION_FORCED		= (1 << 9);
	
	static const uint32_t CONTROL_USER						= (1 << 10);
	static const uint32_t CONTROL_COMPUTER					= (1 << 11);
	static const uint32_t CONTROL_RESCUABLE					= (1 << 12);
	static const uint32_t CONTROL_NEUTRAL					= (1 << 13);
	static const uint32_t CONTROL_CREEP						= (1 << 14);
	static const uint32_t CONTROL_NONE						= (1 << 15);

	static const uint32_t STATE_EMPTY						= (1 << 16);
	static const uint32_t STATE_PLAYING						= (1 << 17);
	static const uint32_t STATE_LEFT						= (1 << 18);

	static const uint32_t OBSERVER							= (1 << 19);

	PlayerFilter(uint32_t requireField, uint32_t excludeField, int playerIdDst = PLAYER_ANY):
		require(requireField), exclude(excludeField), player(playerIdDst) { }

	uint32_t require;
	uint32_t exclude;
	int player;
};

//返回真，当源玩家满足filter(例如CONTROL_USER)，或者满足filter中的联盟关系(例如与目标玩家满足ALLIANCE_PASSIVE)
bool PlayerFilterMatch (int inPlayerIdSrc, PlayerFilter filter);

struct PlayerGroup;
typedef void (*PlayerGroupCallback) (PlayerGroup g, int player);
typedef void (*PlayerTeamCallback) (int team, int indexInTeam, int indexTotal, int player);

struct PlayerGroup {
private:
	bool players[16];
	uint8_t playerCount;
public:
	PlayerGroup (PlayerFilter filter);
	PlayerGroup (uint32_t requireField, uint32_t excludeField, int playerIdDst = PLAYER_ANY);
	PlayerGroup ( );

	bool	add ( int inPlayer );
	bool	remove ( int inPlayer );
	void	clear ( );
	int		count ( ) const;
	int		countTeam ( ) const;
	bool	has ( int inPlayer ) const;
	void	foreach (PlayerGroupCallback callback) const;
	void	forEachTeam (PlayerTeamCallback callback) const;
	int		position ( int inPlayer ) const;

	bool operator==(int rhs) {	return rhs==NULL ? playerCount == 0 : false; }
	
};

PlayerGroup PlayerGroupAll ();
PlayerGroup PlayerGroupSingle (int inPlayer);

#endif