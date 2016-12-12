#include "stdafx.h"
#include "Player.h"
#include "Unit.h"
#include "Jass.h"
#include "Offsets.h"
#include "Player.h"
#include "Jass.h"
#include <fp_call.h>
#include "Tools.h"

/*
PLAYER_COLOR_RED = 0;
PLAYER_COLOR_BLUE = 1;
PLAYER_COLOR_CYAN = 2;
PLAYER_COLOR_PURPLE = 3;
PLAYER_COLOR_YELLOW = 4;
PLAYER_COLOR_ORANGE = 5;
PLAYER_COLOR_GREEN = 6;
PLAYER_COLOR_PINK = 7;
PLAYER_COLOR_LIGHT_GRAY = 8;
PLAYER_COLOR_LIGHT_BLUE = 9;
PLAYER_COLOR_AQUA = 10;
PLAYER_COLOR_BROWN = 11;
*/

static const Color PlayerColors[12] = {
	Color((uint8_t)255, 3, 3),
	Color((uint8_t)0, 66, 255),
	Color((uint8_t)28, 230, 185),
	Color((uint8_t)84, 0, 129),
	Color((uint8_t)255, 252, 1),
	Color((uint8_t)254, 128, 0),//Color((uint8_t)254, 138, 14),	//检测正确与否
	Color((uint8_t)32, 192, 0),
	Color((uint8_t)229, 91, 176),
	Color((uint8_t)149, 150, 151),
	Color((uint8_t)126, 191, 241),
	Color((uint8_t)16, 98, 70),
	Color((uint8_t)78, 42, 4)
};

static const char* PlayerColorStrings[12] =
{
	"|c00ff0303",
	"|c000042ff",
	"|c001ce6b9",
	"|c00540081",
	"|c00fffc01",
	"|c00ff8000",
	"|c0020c000",
	"|c00e55bb0",
	"|c00959697",
	"|c007ebff1",
	"|c00106246",
	"|c004e2a04"
};


	//{3,		3,		255,	0xFF},
	//{255,	66,		0,		0xFF},
	//{185,	230,	28,		0xFF},
	//{129,	0,		84,		0xFF},
	//{1,		252,	255,	0xFF},
	//{14,	138,	254,	0xFF},
	//{0,		192,	32,		0xFF},
	//{176,	91,		229,	0xFF},
	//{151,	150,	149,	0xFF},
	//{241,	191,	126,	0xFF},
	//{70,	98,		16,		0xFF},
	//{4,		42,		78,		0xFF}

void RGB2HSV(float R, float G, float B, float &H, float &S, float &V)
{
	float M = max(max(R, G), B);
	float m = min(min(R, G), B);
	float C = M-m;

	H = 0;
	V = M;
	S = ( C == 0 ) ? 0 : C/V;
	if ( C == 0 )
	{
		H = 0;
	}
	else if ( M == R )
	{
		H = fmod(((G - B) / C), 6) ;
	}
	else if ( M == G )
	{
		H = (B - R) / C + 2;
	}
	else if ( M == B )
	{
		H = (R - G) / C + 4;
	}
	H *= 60.f;
	H = fmod( H, 360.f );
	if ( H < 0 ) H += 360.f;
}

void HSV2RGB(float H, float S, float V, float &R, float &G, float &B)
{
	float C = V * S;
	float H2 = H / 60.f;
	float X = C * ( 1 - abs(fmod(H2, 2) - 1) );
	float R1, G1, B1;

	if (0 <= H2 && H2 < 1)
	{
		R1 = C; G1 = X; B1 = 0;
	}
	else if (1 <= H2 && H2 < 2)
	{
		R1 = X; G1 = C; B1 = 0;
	}
	else if (2 <= H2 && H2 < 3)
	{
		R1 = 0; G1 = C; B1 = X;
	}
	else if (3 <= H2 && H2 < 4)
	{
		R1 = 0; G1 = X; B1 = C;
	}
	else if (4 <= H2 && H2 < 5)
	{
		R1 = X; G1 = 0; B1 = C;
	}
	else if (5 <= H2 && H2 < 6)
	{
		R1 = C; G1 = 0; B1 = X;
	}
	else
	{
		OutputScreen(3, "Error, H2 = %.3f", H2);
		R = 0; G = 0; B = 0; return;
	}

	float m = V - C;
	R = R1 + m;
	G = G1 + m;
	B = B1 + m;
}

Color GetPlayerColor(int playerId, bool correntLightness) {
	if (playerId >= 0 && playerId <= 11) {
		Color color = *reinterpret_cast<const Color*>(&(PlayerColors[PlayerObject(playerId)->color]));
		//修正亮度
		if ( correntLightness )
		{
			//OutputScreen(3, "r, g, b before = (%d, %d, %d)", color.r, color.g, color.b);
			float R, G, B, H, S, V;
			R = (float)(color.r) / 255.f;
			G = (float)(color.g) / 255.f;
			B = (float)(color.b) / 255.f;
			RGB2HSV(R, G, B, H, S, V);
			//V = max(V, 0.9f);
			V = min( 1.f, V * 1.6f );
			HSV2RGB(H, S, V, R, G, B);
			color.r = (uint8_t)(R * 255.f);
			color.g = (uint8_t)(G * 255.f);
			color.b = (uint8_t)(B * 255.f);
			//OutputScreen(3, "r, g, b after = (%d, %d, %d)", color.r, color.g, color.b);
		}
		return color;
	}
	return Color::WHITE;
}

Color GetPlayerColor(int playerId, uint32_t &r, uint32_t &g, uint32_t &b, uint32_t &alpha, bool correntLightness){
	if (playerId >= 0 && playerId <= 11) {
		Color color = GetPlayerColor(playerId, correntLightness);
		r = color.r;
		g = color.g;
		b = color.b;
		alpha = color.a;
		return *reinterpret_cast<const Color*>(&color);
	}
	return Color::WHITE;
}

char ColorStringTmp[15];
const char * GetPlayerColorString( int playerId, bool correntLightness /*= true*/ )
{
	if (playerId >= 0 && playerId <= 11) 
	{
		Color color = GetPlayerColor(playerId, correntLightness);
		sprintf_s(ColorStringTmp, 15, "|c%02x%02x%02x%02x", color.a, color.r, color.g, color.b);
		return ColorStringTmp;
	}
	return "|c00ffffff";
}

int PlayerLocal () {
	war3::CGameWar3 * globalGame = *(war3::CGameWar3 **)(Offset(GLOBAL_WARCRAFT_GAME));
	if (globalGame){
		return (int)globalGame->localPlayerSlot;
	}
	return -1;
}

war3::CPlayerWar3* PlayerObject(int playerId) {
	if (playerId >= 0 && playerId <= 15) {
		war3::CGameWar3* gameObj = *(war3::CGameWar3 **)(Offset(GLOBAL_WARCRAFT_GAME));
		return gameObj->players[playerId];
	}
	return NULL;
}

war3::CPlayerWar3* PlayerObjectLocal() {
	 war3::CGameWar3* gameObj = *(war3::CGameWar3 **)(Offset(GLOBAL_WARCRAFT_GAME));
	 return gameObj->players[gameObj->localPlayerSlot];
}

uint32_t PlayerRace (int inPlayerId) {
	return Jass::GetPlayerRace(Jass::Player(inPlayerId));
}

int PlayerTeam( int inPlayerId )
{
	war3::CPlayerWar3 *p = PlayerObject(inPlayerId);
	if (p)
	{
		return (int)p->team;
	}
	return -1;
}


bool AllianceMatch (
	int playerIdSource,
	int playerIdOther,
	uint32_t reqField,
	uint32_t excludeField
	)  
{
	for (uint32_t field = 0; field <= 9; ++field){
		if (reqField & (1 << field)){
			if (!Jass::GetPlayerAlliance(Jass::Player(playerIdSource), Jass::Player(playerIdOther), field)) return false;
		}
		if (excludeField & (1 << field)){
			if (Jass::GetPlayerAlliance(Jass::Player(playerIdSource), Jass::Player(playerIdOther), field)) return false;
		}
	}
	return true;
}

bool PlayerFilterMatch (int inPlayerIdSrc, PlayerFilter filter) {
	uint32_t require = filter.require;
	uint32_t exclude = filter.exclude;
	int playerIdDst = filter.player;

	player pSrc, pDst;
	pSrc = Jass::Player(inPlayerIdSrc);

	if (playerIdDst != PLAYER_ANY){
		pDst = Jass::Player(playerIdDst);
		for (uint32_t i = 0; i <= 9; i++) {
			if (require & (1 << i)) {
				if (!Jass::GetPlayerAlliance(pSrc, pDst, i)) return false;
			}
			if (exclude & (1 << i)) {
				if (Jass::GetPlayerAlliance(pSrc, pDst, i)) return false;
			}
		}
	}

	if (require & PlayerFilter::CONTROL_USER) { if (Jass::GetPlayerController(pSrc)!=Jass::MAP_CONTROL_USER) return false; }
	if (exclude & PlayerFilter::CONTROL_USER) { if (Jass::GetPlayerController(pSrc)==Jass::MAP_CONTROL_USER) return false; }

	if (require & PlayerFilter::CONTROL_COMPUTER) { if (Jass::GetPlayerController(pSrc)!=Jass::MAP_CONTROL_COMPUTER) return false; }
	if (exclude & PlayerFilter::CONTROL_COMPUTER) { if (Jass::GetPlayerController(pSrc)==Jass::MAP_CONTROL_COMPUTER) return false; }

	if (require & PlayerFilter::CONTROL_RESCUABLE) { if (Jass::GetPlayerController(pSrc)!=Jass::MAP_CONTROL_RESCUABLE) return false; }
	if (exclude & PlayerFilter::CONTROL_RESCUABLE) { if (Jass::GetPlayerController(pSrc)==Jass::MAP_CONTROL_RESCUABLE) return false; }

	if (require & PlayerFilter::CONTROL_NEUTRAL) { if (Jass::GetPlayerController(pSrc)!=Jass::MAP_CONTROL_NEUTRAL) return false; }
	if (exclude & PlayerFilter::CONTROL_NEUTRAL) { if (Jass::GetPlayerController(pSrc)==Jass::MAP_CONTROL_NEUTRAL) return false; }

	if (require & PlayerFilter::CONTROL_CREEP) { if (Jass::GetPlayerController(pSrc)!=Jass::MAP_CONTROL_CREEP) return false; }
	if (exclude & PlayerFilter::CONTROL_CREEP) { if (Jass::GetPlayerController(pSrc)==Jass::MAP_CONTROL_CREEP) return false; }

	if (require & PlayerFilter::CONTROL_NONE) { if (Jass::GetPlayerController(pSrc)!=Jass::MAP_CONTROL_NONE) return false; }
	if (exclude & PlayerFilter::CONTROL_NONE) { if (Jass::GetPlayerController(pSrc)==Jass::MAP_CONTROL_NONE) return false; }

	if (require & PlayerFilter::STATE_EMPTY) { if (Jass::GetPlayerSlotState(pSrc)!=Jass::PLAYER_SLOT_STATE_EMPTY) return false; }
	if (exclude & PlayerFilter::STATE_EMPTY) { if (Jass::GetPlayerSlotState(pSrc)==Jass::PLAYER_SLOT_STATE_EMPTY) return false; }

	if (require & PlayerFilter::STATE_PLAYING) { if (Jass::GetPlayerSlotState(pSrc)!=Jass::PLAYER_SLOT_STATE_PLAYING) return false; }
	if (exclude & PlayerFilter::STATE_PLAYING) { if (Jass::GetPlayerSlotState(pSrc)==Jass::PLAYER_SLOT_STATE_PLAYING) return false; }

	if (require & PlayerFilter::STATE_LEFT) { if (Jass::GetPlayerSlotState(pSrc)!=Jass::PLAYER_SLOT_STATE_LEFT) return false; }
	if (exclude & PlayerFilter::STATE_LEFT) { if (Jass::GetPlayerSlotState(pSrc)==Jass::PLAYER_SLOT_STATE_LEFT) return false; }

	if (require & PlayerFilter::OBSERVER) { if (!Jass::IsPlayerObserver(pSrc)) return false; }
	if (exclude & PlayerFilter::OBSERVER) { if (Jass::IsPlayerObserver(pSrc)) return false; }

	return true;
}


static bool PlayerGroupInitState[16] = {false};

PlayerGroup::PlayerGroup() : playerCount() { memcpy(players, PlayerGroupInitState, sizeof(players)); }

PlayerGroup::PlayerGroup(PlayerFilter filter) : playerCount() {
	memcpy(players, PlayerGroupInitState, sizeof(players));
	for (uint32_t i = 0; i < 16; i++) {
		if (PlayerFilterMatch(i, filter)) add(i);
	}
}

PlayerGroup::PlayerGroup(uint32_t requireField, uint32_t excludeField, int playerIdDst) : playerCount()
{
	PlayerFilter filter = PlayerFilter(requireField, excludeField, playerIdDst);
	memcpy(players, PlayerGroupInitState, sizeof(players));
	for (uint32_t i = 0; i < 16; i++) {
		if (PlayerFilterMatch(i, filter)) add(i);
	}
}


bool PlayerGroup::add (int inPlayerId) {
	if (inPlayerId >= 0 && inPlayerId < 16){
		if (!players[inPlayerId]){
			players[inPlayerId] = true;
			playerCount += 1;
			return true;
		}
	}
	return false;
}

bool PlayerGroup::remove (int inPlayerId) {
	if (inPlayerId >= 0 && inPlayerId < 16){
		if (players[inPlayerId]){
			players[inPlayerId] = false;
			playerCount -= 1;
			return true;
		}
	}
	return false;
}

void PlayerGroup::clear () {
	for (uint8_t i = 0; i < 16; ++i){
		players[i] = false;
	}
	playerCount = 0;
}

int PlayerGroup::count () const {	return playerCount; }

bool PlayerGroup::has (int inPlayerId) const { return players[inPlayerId]; }

void PlayerGroup::foreach( PlayerGroupCallback callback ) const
{
	for (uint8_t i = 0; i < 16; ++i)
	{
		if (players[i])
		{
			callback(*this, (int)i);
		}
	}
}

int PlayerGroup::position( int inPlayer ) const
{
	int pos = 0;
	for (uint8_t i = 0; i < 16; ++i)
	{
		if (players[i])
		{
			if (i == inPlayer)
			{
				return pos;
			}
			else{pos++;}
		}
	}
	return -1;
}

void PlayerGroup::forEachTeam( PlayerTeamCallback callback ) const
{
	PlayerGroup teams[16];
	int team = -1;
	for (uint8_t i = 0; i < 16; ++i)
	{
		if (players[i])
		{
			team = PlayerTeam(i);
			if (team > -1)
			{
				teams[team].add(i);
			}
		}
	}

	int indexInTeam;
	int indexTotal = 0;
	for (uint8_t i = 0; i < 16; ++i)
	{
		indexInTeam = 0;
		for (uint8_t j = 0; j < 16; ++j)
		{
			if (teams[i].has(j))
			{
				callback(i, indexInTeam, indexTotal, j);
				indexInTeam++;
				indexTotal++;
			}
		}
	}
}

int PlayerGroup::countTeam() const
{
	std::set<int> teams;
	for (uint8_t i = 0; i < 16; ++i)
	{
		if (players[i])
		{
			teams.insert(PlayerTeam(i));
		}
	}
	return teams.size();
}

PlayerGroup PlayerGroupAll () {
	PlayerGroup g = PlayerGroup();
	for (uint8_t i = 0; i < 16; ++i){ g.add(i); }
	return g;
}

PlayerGroup PlayerGroupSingle (int inPlayer) {
	PlayerGroup g = PlayerGroup();
	g.add(inPlayer);
	return g;
}

const char * PlayerName( int inPlayerId )
{
	/*void *funcNameGet = Offset(PLAYER_NAME_GET);
	war3::CPlayerWar3 *playerObj = PlayerObject(inPlayerId);
	if (playerObj)
	{
		return aero::generic_this_call<const char *>(funcNameGet, playerObj, 1);
	}*/
	return PlayerNameGet(inPlayerId, 1);
}

void SetLocalSubgroup( Unit *u )
{
	ActiveSubgroupSet(UnitGetObject(u->handleId()));
}
