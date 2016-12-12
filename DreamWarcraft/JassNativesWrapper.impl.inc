void JASS_WRAPPER_SetCineFilterStartUV(float a0, float a1, float a2, float a3) {
	JASS_NATIVE_SetCineFilterStartUV(&a0, &a1, &a2, &a3);
}

void JASS_WRAPPER_SetCineFilterEndUV(float a0, float a1, float a2, float a3) {
	JASS_NATIVE_SetCineFilterEndUV(&a0, &a1, &a2, &a3);
}

void JASS_WRAPPER_SetCineFilterDuration(float a0) {
	JASS_NATIVE_SetCineFilterDuration(&a0);
}

void JASS_WRAPPER_SetCinematicScene(int a0, DWORD a1, const char* a2, const char* a3, float a4, float a5) {
	JASS_NATIVE_SetCinematicScene(a0, a1, STR_TO_JASSSTR(a2), STR_TO_JASSSTR(a3), &a4, &a5);
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_NewSoundEnvironment(const char* a0) {
	JASS_NATIVE_NewSoundEnvironment(STR_TO_JASSSTR(a0));
	JASS_STR_CLEANUP();
}

DWORD JASS_WRAPPER_CreateSound(const char* a0, bool a1, bool a2, bool a3, int a4, int a5, const char* a6) {
	DWORD rv = JASS_NATIVE_CreateSound(STR_TO_JASSSTR(a0), a1, a2, a3, a4, a5, STR_TO_JASSSTR(a6));
	JASS_STR_CLEANUP();
	return rv;
}

DWORD JASS_WRAPPER_CreateSoundFilenameWithLabel(const char* a0, bool a1, bool a2, bool a3, int a4, int a5, const char* a6) {
	DWORD rv = JASS_NATIVE_CreateSoundFilenameWithLabel(STR_TO_JASSSTR(a0), a1, a2, a3, a4, a5, STR_TO_JASSSTR(a6));
	JASS_STR_CLEANUP();
	return rv;
}

DWORD JASS_WRAPPER_CreateSoundFromLabel(const char* a0, bool a1, bool a2, bool a3, int a4, int a5) {
	DWORD rv = JASS_NATIVE_CreateSoundFromLabel(STR_TO_JASSSTR(a0), a1, a2, a3, a4, a5);
	JASS_STR_CLEANUP();
	return rv;
}

DWORD JASS_WRAPPER_CreateMIDISound(const char* a0, int a1, int a2) {
	DWORD rv = JASS_NATIVE_CreateMIDISound(STR_TO_JASSSTR(a0), a1, a2);
	JASS_STR_CLEANUP();
	return rv;
}

void JASS_WRAPPER_SetStackedSound(const char* a0, float a1, float a2) {
	JASS_NATIVE_SetStackedSound(STR_TO_JASSSTR(a0), &a1, &a2);
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_ClearStackedSound(const char* a0, float a1, float a2) {
	JASS_NATIVE_ClearStackedSound(STR_TO_JASSSTR(a0), &a1, &a2);
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_SetStackedSoundRect(const char* a0, DWORD a1) {
	JASS_NATIVE_SetStackedSoundRect(STR_TO_JASSSTR(a0), a1);
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_ClearStackedSoundRect(const char* a0, DWORD a1) {
	JASS_NATIVE_ClearStackedSoundRect(STR_TO_JASSSTR(a0), a1);
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_SetSoundParamsFromLabel(DWORD a0, const char* a1) {
	JASS_NATIVE_SetSoundParamsFromLabel(a0, STR_TO_JASSSTR(a1));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_SetSoundPitch(DWORD a0, float a1) {
	JASS_NATIVE_SetSoundPitch(a0, &a1);
}

void JASS_WRAPPER_SetSoundDistances(DWORD a0, float a1, float a2) {
	JASS_NATIVE_SetSoundDistances(a0, &a1, &a2);
}

void JASS_WRAPPER_SetSoundDistanceCutoff(DWORD a0, float a1) {
	JASS_NATIVE_SetSoundDistanceCutoff(a0, &a1);
}

void JASS_WRAPPER_SetSoundConeAngles(DWORD a0, float a1, float a2, int a3) {
	JASS_NATIVE_SetSoundConeAngles(a0, &a1, &a2, a3);
}

void JASS_WRAPPER_SetSoundConeOrientation(DWORD a0, float a1, float a2, float a3) {
	JASS_NATIVE_SetSoundConeOrientation(a0, &a1, &a2, &a3);
}

void JASS_WRAPPER_SetSoundPosition(DWORD a0, float a1, float a2, float a3) {
	JASS_NATIVE_SetSoundPosition(a0, &a1, &a2, &a3);
}

void JASS_WRAPPER_SetSoundVelocity(DWORD a0, float a1, float a2, float a3) {
	JASS_NATIVE_SetSoundVelocity(a0, &a1, &a2, &a3);
}

void JASS_WRAPPER_SetMapMusic(const char* a0, bool a1, int a2) {
	JASS_NATIVE_SetMapMusic(STR_TO_JASSSTR(a0), a1, a2);
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_PlayMusic(const char* a0) {
	JASS_NATIVE_PlayMusic(STR_TO_JASSSTR(a0));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_PlayMusicEx(const char* a0, int a1, int a2) {
	JASS_NATIVE_PlayMusicEx(STR_TO_JASSSTR(a0), a1, a2);
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_PlayThematicMusic(const char* a0) {
	JASS_NATIVE_PlayThematicMusic(STR_TO_JASSSTR(a0));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_PlayThematicMusicEx(const char* a0, int a1) {
	JASS_NATIVE_PlayThematicMusicEx(STR_TO_JASSSTR(a0), a1);
	JASS_STR_CLEANUP();
}

int JASS_WRAPPER_GetSoundFileDuration(const char* a0) {
	int rv = JASS_NATIVE_GetSoundFileDuration(STR_TO_JASSSTR(a0));
	JASS_STR_CLEANUP();
	return rv;
}

void JASS_WRAPPER_VolumeGroupSetVolume(DWORD a0, float a1) {
	JASS_NATIVE_VolumeGroupSetVolume(a0, &a1);
}

void JASS_WRAPPER_RegisterStackedSound(DWORD a0, bool a1, float a2, float a3) {
	JASS_NATIVE_RegisterStackedSound(a0, a1, &a2, &a3);
}

void JASS_WRAPPER_UnregisterStackedSound(DWORD a0, bool a1, float a2, float a3) {
	JASS_NATIVE_UnregisterStackedSound(a0, a1, &a2, &a3);
}

DWORD JASS_WRAPPER_TerrainDeformCrater(float a0, float a1, float a2, float a3, int a4, bool a5) {
	DWORD rv = JASS_NATIVE_TerrainDeformCrater(&a0, &a1, &a2, &a3, a4, a5);
	return rv;
}

DWORD JASS_WRAPPER_TerrainDeformRipple(float a0, float a1, float a2, float a3, int a4, int a5, float a6, float a7, float a8, bool a9) {
	DWORD rv = JASS_NATIVE_TerrainDeformRipple(&a0, &a1, &a2, &a3, a4, a5, &a6, &a7, &a8, a9);
	return rv;
}

DWORD JASS_WRAPPER_TerrainDeformWave(float a0, float a1, float a2, float a3, float a4, float a5, float a6, float a7, int a8, int a9) {
	DWORD rv = JASS_NATIVE_TerrainDeformWave(&a0, &a1, &a2, &a3, &a4, &a5, &a6, &a7, a8, a9);
	return rv;
}

DWORD JASS_WRAPPER_TerrainDeformRandom(float a0, float a1, float a2, float a3, float a4, int a5, int a6) {
	DWORD rv = JASS_NATIVE_TerrainDeformRandom(&a0, &a1, &a2, &a3, &a4, a5, a6);
	return rv;
}

DWORD JASS_WRAPPER_AddSpecialEffect(const char* a0, float a1, float a2) {
	DWORD rv = JASS_NATIVE_AddSpecialEffect(STR_TO_JASSSTR(a0), &a1, &a2);
	JASS_STR_CLEANUP();
	return rv;
}

DWORD JASS_WRAPPER_AddSpecialEffectLoc(const char* a0, DWORD a1) {
	DWORD rv = JASS_NATIVE_AddSpecialEffectLoc(STR_TO_JASSSTR(a0), a1);
	JASS_STR_CLEANUP();
	return rv;
}

DWORD JASS_WRAPPER_AddSpecialEffectTarget(const char* a0, DWORD a1, const char* a2) {
	DWORD rv = JASS_NATIVE_AddSpecialEffectTarget(STR_TO_JASSSTR(a0), a1, STR_TO_JASSSTR(a2));
	JASS_STR_CLEANUP();
	return rv;
}

DWORD JASS_WRAPPER_AddSpellEffect(const char* a0, DWORD a1, float a2, float a3) {
	DWORD rv = JASS_NATIVE_AddSpellEffect(STR_TO_JASSSTR(a0), a1, &a2, &a3);
	JASS_STR_CLEANUP();
	return rv;
}

DWORD JASS_WRAPPER_AddSpellEffectLoc(const char* a0, DWORD a1, DWORD a2) {
	DWORD rv = JASS_NATIVE_AddSpellEffectLoc(STR_TO_JASSSTR(a0), a1, a2);
	JASS_STR_CLEANUP();
	return rv;
}

DWORD JASS_WRAPPER_AddSpellEffectById(int a0, DWORD a1, float a2, float a3) {
	DWORD rv = JASS_NATIVE_AddSpellEffectById(a0, a1, &a2, &a3);
	return rv;
}

DWORD JASS_WRAPPER_AddSpellEffectTarget(const char* a0, DWORD a1, DWORD a2, const char* a3) {
	DWORD rv = JASS_NATIVE_AddSpellEffectTarget(STR_TO_JASSSTR(a0), a1, a2, STR_TO_JASSSTR(a3));
	JASS_STR_CLEANUP();
	return rv;
}

DWORD JASS_WRAPPER_AddSpellEffectTargetById(int a0, DWORD a1, DWORD a2, const char* a3) {
	DWORD rv = JASS_NATIVE_AddSpellEffectTargetById(a0, a1, a2, STR_TO_JASSSTR(a3));
	JASS_STR_CLEANUP();
	return rv;
}

DWORD JASS_WRAPPER_AddLightning(const char* a0, bool a1, float a2, float a3, float a4, float a5) {
	DWORD rv = JASS_NATIVE_AddLightning(STR_TO_JASSSTR(a0), a1, &a2, &a3, &a4, &a5);
	JASS_STR_CLEANUP();
	return rv;
}

DWORD JASS_WRAPPER_AddLightningEx(const char* a0, bool a1, float a2, float a3, float a4, float a5, float a6, float a7) {
	DWORD rv = JASS_NATIVE_AddLightningEx(STR_TO_JASSSTR(a0), a1, &a2, &a3, &a4, &a5, &a6, &a7);
	JASS_STR_CLEANUP();
	return rv;
}

float JASS_WRAPPER_GetLightningColorA(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetLightningColorA(a0));
	return rv;
}

float JASS_WRAPPER_GetLightningColorR(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetLightningColorR(a0));
	return rv;
}

float JASS_WRAPPER_GetLightningColorG(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetLightningColorG(a0));
	return rv;
}

float JASS_WRAPPER_GetLightningColorB(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetLightningColorB(a0));
	return rv;
}

bool JASS_WRAPPER_MoveLightning(DWORD a0, bool a1, float a2, float a3, float a4, float a5) {
	bool rv = JASS_NATIVE_MoveLightning(a0, a1, &a2, &a3, &a4, &a5);
	return rv;
}

bool JASS_WRAPPER_MoveLightningEx(DWORD a0, bool a1, float a2, float a3, float a4, float a5, float a6, float a7) {
	bool rv = JASS_NATIVE_MoveLightningEx(a0, a1, &a2, &a3, &a4, &a5, &a6, &a7);
	return rv;
}

bool JASS_WRAPPER_SetLightningColor(DWORD a0, float a1, float a2, float a3, float a4) {
	bool rv = JASS_NATIVE_SetLightningColor(a0, &a1, &a2, &a3, &a4);
	return rv;
}

const char* JASS_WRAPPER_GetAbilityEffect(const char* a0, DWORD a1, int a2) {
	const char* rv = JASSSTR_TO_STR(JASS_NATIVE_GetAbilityEffect(STR_TO_JASSSTR(a0), a1, a2));
	JASS_STR_CLEANUP();
	return rv;
}

const char* JASS_WRAPPER_GetAbilityEffectById(int a0, DWORD a1, int a2) {
	const char* rv = JASSSTR_TO_STR(JASS_NATIVE_GetAbilityEffectById(a0, a1, a2));
	return rv;
}

const char* JASS_WRAPPER_GetAbilitySound(const char* a0, DWORD a1) {
	const char* rv = JASSSTR_TO_STR(JASS_NATIVE_GetAbilitySound(STR_TO_JASSSTR(a0), a1));
	JASS_STR_CLEANUP();
	return rv;
}

const char* JASS_WRAPPER_GetAbilitySoundById(int a0, DWORD a1) {
	const char* rv = JASSSTR_TO_STR(JASS_NATIVE_GetAbilitySoundById(a0, a1));
	return rv;
}

int JASS_WRAPPER_GetTerrainCliffLevel(float a0, float a1) {
	int rv = JASS_NATIVE_GetTerrainCliffLevel(&a0, &a1);
	return rv;
}

int JASS_WRAPPER_GetTerrainType(float a0, float a1) {
	int rv = JASS_NATIVE_GetTerrainType(&a0, &a1);
	return rv;
}

int JASS_WRAPPER_GetTerrainVariance(float a0, float a1) {
	int rv = JASS_NATIVE_GetTerrainVariance(&a0, &a1);
	return rv;
}

void JASS_WRAPPER_SetTerrainType(float a0, float a1, int a2, int a3, int a4, int a5) {
	JASS_NATIVE_SetTerrainType(&a0, &a1, a2, a3, a4, a5);
}

bool JASS_WRAPPER_IsTerrainPathable(float a0, float a1, DWORD a2) {
	bool rv = JASS_NATIVE_IsTerrainPathable(&a0, &a1, a2);
	return rv;
}

void JASS_WRAPPER_SetTerrainPathable(float a0, float a1, DWORD a2, bool a3) {
	JASS_NATIVE_SetTerrainPathable(&a0, &a1, a2, a3);
}

DWORD JASS_WRAPPER_CreateImage(const char* a0, float a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, int a10) {
	DWORD rv = JASS_NATIVE_CreateImage(STR_TO_JASSSTR(a0), &a1, &a2, &a3, &a4, &a5, &a6, &a7, &a8, &a9, a10);
	JASS_STR_CLEANUP();
	return rv;
}

void JASS_WRAPPER_SetImageConstantHeight(DWORD a0, bool a1, float a2) {
	JASS_NATIVE_SetImageConstantHeight(a0, a1, &a2);
}

void JASS_WRAPPER_SetImagePosition(DWORD a0, float a1, float a2, float a3) {
	JASS_NATIVE_SetImagePosition(a0, &a1, &a2, &a3);
}

DWORD JASS_WRAPPER_CreateUbersplat(float a0, float a1, const char* a2, int a3, int a4, int a5, int a6, bool a7, bool a8) {
	DWORD rv = JASS_NATIVE_CreateUbersplat(&a0, &a1, STR_TO_JASSSTR(a2), a3, a4, a5, a6, a7, a8);
	JASS_STR_CLEANUP();
	return rv;
}

void JASS_WRAPPER_SetBlight(DWORD a0, float a1, float a2, float a3, bool a4) {
	JASS_NATIVE_SetBlight(a0, &a1, &a2, &a3, a4);
}

void JASS_WRAPPER_SetBlightLoc(DWORD a0, DWORD a1, float a2, bool a3) {
	JASS_NATIVE_SetBlightLoc(a0, a1, &a2, a3);
}

void JASS_WRAPPER_SetBlightPoint(DWORD a0, float a1, float a2, bool a3) {
	JASS_NATIVE_SetBlightPoint(a0, &a1, &a2, a3);
}

DWORD JASS_WRAPPER_CreateBlightedGoldmine(DWORD a0, float a1, float a2, float a3) {
	DWORD rv = JASS_NATIVE_CreateBlightedGoldmine(a0, &a1, &a2, &a3);
	return rv;
}

bool JASS_WRAPPER_IsPointBlighted(float a0, float a1) {
	bool rv = JASS_NATIVE_IsPointBlighted(&a0, &a1);
	return rv;
}

void JASS_WRAPPER_SetDoodadAnimation(float a0, float a1, float a2, int a3, bool a4, const char* a5, bool a6) {
	JASS_NATIVE_SetDoodadAnimation(&a0, &a1, &a2, a3, a4, STR_TO_JASSSTR(a5), a6);
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_SetDoodadAnimationRect(DWORD a0, int a1, const char* a2, bool a3) {
	JASS_NATIVE_SetDoodadAnimationRect(a0, a1, STR_TO_JASSSTR(a2), a3);
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_StartMeleeAI(DWORD a0, const char* a1) {
	JASS_NATIVE_StartMeleeAI(a0, STR_TO_JASSSTR(a1));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_StartCampaignAI(DWORD a0, const char* a1) {
	JASS_NATIVE_StartCampaignAI(a0, STR_TO_JASSSTR(a1));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_ExecuteFunc(const char* a0) {
	JASS_NATIVE_ExecuteFunc(STR_TO_JASSSTR(a0));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_Cheat(const char* a0) {
	JASS_NATIVE_Cheat(STR_TO_JASSSTR(a0));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_Preload(const char* a0) {
	JASS_NATIVE_Preload(STR_TO_JASSSTR(a0));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_PreloadEnd(float a0) {
	JASS_NATIVE_PreloadEnd(&a0);
}

void JASS_WRAPPER_PreloadGenEnd(const char* a0) {
	JASS_NATIVE_PreloadGenEnd(STR_TO_JASSSTR(a0));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_Preloader(const char* a0) {
	JASS_NATIVE_Preloader(STR_TO_JASSSTR(a0));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_DebugS(const char* a0) {
	JASS_NATIVE_DebugS(STR_TO_JASSSTR(a0));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_DebugFI(const char* a0, int a1) {
	JASS_NATIVE_DebugFI(STR_TO_JASSSTR(a0), a1);
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_DebugUnitID(const char* a0, int a1) {
	JASS_NATIVE_DebugUnitID(STR_TO_JASSSTR(a0), a1);
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_DisplayText(int a0, const char* a1) {
	JASS_NATIVE_DisplayText(a0, STR_TO_JASSSTR(a1));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_DisplayTextI(int a0, const char* a1, int a2) {
	JASS_NATIVE_DisplayTextI(a0, STR_TO_JASSSTR(a1), a2);
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_DisplayTextII(int a0, const char* a1, int a2, int a3) {
	JASS_NATIVE_DisplayTextII(a0, STR_TO_JASSSTR(a1), a2, a3);
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_DisplayTextIII(int a0, const char* a1, int a2, int a3, int a4) {
	JASS_NATIVE_DisplayTextIII(a0, STR_TO_JASSSTR(a1), a2, a3, a4);
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_Sleep(float a0) {
	JASS_NATIVE_Sleep(&a0);
}

void JASS_WRAPPER_AddGuardPost(int a0, float a1, float a2) {
	JASS_NATIVE_AddGuardPost(a0, &a1, &a2);
}

void JASS_WRAPPER_SetCaptainHome(int a0, float a1, float a2) {
	JASS_NATIVE_SetCaptainHome(a0, &a1, &a2);
}

void JASS_WRAPPER_ShiftTownSpot(float a0, float a1) {
	JASS_NATIVE_ShiftTownSpot(&a0, &a1);
}

void JASS_WRAPPER_TeleportCaptain(float a0, float a1) {
	JASS_NATIVE_TeleportCaptain(&a0, &a1);
}

void JASS_WRAPPER_CaptainAttack(float a0, float a1) {
	JASS_NATIVE_CaptainAttack(&a0, &a1);
}

void JASS_WRAPPER_SetStagePoint(float a0, float a1) {
	JASS_NATIVE_SetStagePoint(&a0, &a1);
}

float JASS_WRAPPER_GetRandomReal(float a0, float a1) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetRandomReal(&a0, &a1));
	return rv;
}

void JASS_WRAPPER_UnitPoolAddUnitType(DWORD a0, int a1, float a2) {
	JASS_NATIVE_UnitPoolAddUnitType(a0, a1, &a2);
}

DWORD JASS_WRAPPER_PlaceRandomUnit(DWORD a0, DWORD a1, float a2, float a3, float a4) {
	DWORD rv = JASS_NATIVE_PlaceRandomUnit(a0, a1, &a2, &a3, &a4);
	return rv;
}

void JASS_WRAPPER_ItemPoolAddItemType(DWORD a0, int a1, float a2) {
	JASS_NATIVE_ItemPoolAddItemType(a0, a1, &a2);
}

DWORD JASS_WRAPPER_PlaceRandomItem(DWORD a0, float a1, float a2) {
	DWORD rv = JASS_NATIVE_PlaceRandomItem(a0, &a1, &a2);
	return rv;
}

void JASS_WRAPPER_DisplayTextToPlayer(DWORD a0, float a1, float a2, const char* a3) {
	JASS_NATIVE_DisplayTextToPlayer(a0, &a1, &a2, STR_TO_JASSSTR(a3));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_DisplayTimedTextToPlayer(DWORD a0, float a1, float a2, float a3, const char* a4) {
	JASS_NATIVE_DisplayTimedTextToPlayer(a0, &a1, &a2, &a3, STR_TO_JASSSTR(a4));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_DisplayTimedTextFromPlayer(DWORD a0, float a1, float a2, float a3, const char* a4) {
	JASS_NATIVE_DisplayTimedTextFromPlayer(a0, &a1, &a2, &a3, STR_TO_JASSSTR(a4));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_ForceUIKey(const char* a0) {
	JASS_NATIVE_ForceUIKey(STR_TO_JASSSTR(a0));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_SetTerrainFog(float a0, float a1, float a2, float a3, float a4) {
	JASS_NATIVE_SetTerrainFog(&a0, &a1, &a2, &a3, &a4);
}

void JASS_WRAPPER_SetUnitFog(float a0, float a1, float a2, float a3, float a4) {
	JASS_NATIVE_SetUnitFog(&a0, &a1, &a2, &a3, &a4);
}

void JASS_WRAPPER_SetTerrainFogEx(int a0, float a1, float a2, float a3, float a4, float a5, float a6) {
	JASS_NATIVE_SetTerrainFogEx(a0, &a1, &a2, &a3, &a4, &a5, &a6);
}

void JASS_WRAPPER_SetDayNightModels(const char* a0, const char* a1) {
	JASS_NATIVE_SetDayNightModels(STR_TO_JASSSTR(a0), STR_TO_JASSSTR(a1));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_SetSkyModel(const char* a0) {
	JASS_NATIVE_SetSkyModel(STR_TO_JASSSTR(a0));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_SetTimeOfDayScale(float a0) {
	JASS_NATIVE_SetTimeOfDayScale(&a0);
}

float JASS_WRAPPER_GetTimeOfDayScale() {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetTimeOfDayScale());
	return rv;
}

void JASS_WRAPPER_ShowInterface(bool a0, float a1) {
	JASS_NATIVE_ShowInterface(a0, &a1);
}

void JASS_WRAPPER_PingMinimap(float a0, float a1, float a2) {
	JASS_NATIVE_PingMinimap(&a0, &a1, &a2);
}

void JASS_WRAPPER_PingMinimapEx(float a0, float a1, float a2, int a3, int a4, int a5, bool a6) {
	JASS_NATIVE_PingMinimapEx(&a0, &a1, &a2, a3, a4, a5, a6);
}

void JASS_WRAPPER_SetIntroShotText(const char* a0) {
	JASS_NATIVE_SetIntroShotText(STR_TO_JASSSTR(a0));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_SetIntroShotModel(const char* a0) {
	JASS_NATIVE_SetIntroShotModel(STR_TO_JASSSTR(a0));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_PlayModelCinematic(const char* a0) {
	JASS_NATIVE_PlayModelCinematic(STR_TO_JASSSTR(a0));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_PlayCinematic(const char* a0) {
	JASS_NATIVE_PlayCinematic(STR_TO_JASSSTR(a0));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_SetAltMinimapIcon(const char* a0) {
	JASS_NATIVE_SetAltMinimapIcon(STR_TO_JASSSTR(a0));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_SetTextTagText(DWORD a0, const char* a1, float a2) {
	JASS_NATIVE_SetTextTagText(a0, STR_TO_JASSSTR(a1), &a2);
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_SetTextTagPos(DWORD a0, float a1, float a2, float a3) {
	JASS_NATIVE_SetTextTagPos(a0, &a1, &a2, &a3);
}

void JASS_WRAPPER_SetTextTagPosUnit(DWORD a0, DWORD a1, float a2) {
	JASS_NATIVE_SetTextTagPosUnit(a0, a1, &a2);
}

void JASS_WRAPPER_SetTextTagVelocity(DWORD a0, float a1, float a2) {
	JASS_NATIVE_SetTextTagVelocity(a0, &a1, &a2);
}

void JASS_WRAPPER_SetTextTagAge(DWORD a0, float a1) {
	JASS_NATIVE_SetTextTagAge(a0, &a1);
}

void JASS_WRAPPER_SetTextTagLifespan(DWORD a0, float a1) {
	JASS_NATIVE_SetTextTagLifespan(a0, &a1);
}

void JASS_WRAPPER_SetTextTagFadepoint(DWORD a0, float a1) {
	JASS_NATIVE_SetTextTagFadepoint(a0, &a1);
}

DWORD JASS_WRAPPER_CreateTrackable(const char* a0, float a1, float a2, float a3) {
	DWORD rv = JASS_NATIVE_CreateTrackable(STR_TO_JASSSTR(a0), &a1, &a2, &a3);
	JASS_STR_CLEANUP();
	return rv;
}

void JASS_WRAPPER_QuestSetTitle(DWORD a0, const char* a1) {
	JASS_NATIVE_QuestSetTitle(a0, STR_TO_JASSSTR(a1));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_QuestSetDescription(DWORD a0, const char* a1) {
	JASS_NATIVE_QuestSetDescription(a0, STR_TO_JASSSTR(a1));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_QuestSetIconPath(DWORD a0, const char* a1) {
	JASS_NATIVE_QuestSetIconPath(a0, STR_TO_JASSSTR(a1));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_QuestItemSetDescription(DWORD a0, const char* a1) {
	JASS_NATIVE_QuestItemSetDescription(a0, STR_TO_JASSSTR(a1));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_DefeatConditionSetDescription(DWORD a0, const char* a1) {
	JASS_NATIVE_DefeatConditionSetDescription(a0, STR_TO_JASSSTR(a1));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_TimerDialogSetTitle(DWORD a0, const char* a1) {
	JASS_NATIVE_TimerDialogSetTitle(a0, STR_TO_JASSSTR(a1));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_TimerDialogSetSpeed(DWORD a0, float a1) {
	JASS_NATIVE_TimerDialogSetSpeed(a0, &a1);
}

void JASS_WRAPPER_TimerDialogSetRealTimeRemaining(DWORD a0, float a1) {
	JASS_NATIVE_TimerDialogSetRealTimeRemaining(a0, &a1);
}

void JASS_WRAPPER_LeaderboardAddItem(DWORD a0, const char* a1, int a2, DWORD a3) {
	JASS_NATIVE_LeaderboardAddItem(a0, STR_TO_JASSSTR(a1), a2, a3);
	JASS_STR_CLEANUP();
}

const char* JASS_WRAPPER_LeaderboardGetLabelText(DWORD a0) {
	const char* rv = JASSSTR_TO_STR(JASS_NATIVE_LeaderboardGetLabelText(a0));
	return rv;
}

void JASS_WRAPPER_LeaderboardSetLabel(DWORD a0, const char* a1) {
	JASS_NATIVE_LeaderboardSetLabel(a0, STR_TO_JASSSTR(a1));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_LeaderboardSetItemLabel(DWORD a0, int a1, const char* a2) {
	JASS_NATIVE_LeaderboardSetItemLabel(a0, a1, STR_TO_JASSSTR(a2));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_MultiboardSetTitleText(DWORD a0, const char* a1) {
	JASS_NATIVE_MultiboardSetTitleText(a0, STR_TO_JASSSTR(a1));
	JASS_STR_CLEANUP();
}

const char* JASS_WRAPPER_MultiboardGetTitleText(DWORD a0) {
	const char* rv = JASSSTR_TO_STR(JASS_NATIVE_MultiboardGetTitleText(a0));
	return rv;
}

void JASS_WRAPPER_MultiboardSetItemsValue(DWORD a0, const char* a1) {
	JASS_NATIVE_MultiboardSetItemsValue(a0, STR_TO_JASSSTR(a1));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_MultiboardSetItemsWidth(DWORD a0, float a1) {
	JASS_NATIVE_MultiboardSetItemsWidth(a0, &a1);
}

void JASS_WRAPPER_MultiboardSetItemsIcon(DWORD a0, const char* a1) {
	JASS_NATIVE_MultiboardSetItemsIcon(a0, STR_TO_JASSSTR(a1));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_MultiboardSetItemValue(DWORD a0, const char* a1) {
	JASS_NATIVE_MultiboardSetItemValue(a0, STR_TO_JASSSTR(a1));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_MultiboardSetItemWidth(DWORD a0, float a1) {
	JASS_NATIVE_MultiboardSetItemWidth(a0, &a1);
}

void JASS_WRAPPER_MultiboardSetItemIcon(DWORD a0, const char* a1) {
	JASS_NATIVE_MultiboardSetItemIcon(a0, STR_TO_JASSSTR(a1));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_SetCameraBounds(float a0, float a1, float a2, float a3, float a4, float a5, float a6, float a7) {
	JASS_NATIVE_SetCameraBounds(&a0, &a1, &a2, &a3, &a4, &a5, &a6, &a7);
}

void JASS_WRAPPER_SetCameraPosition(float a0, float a1) {
	JASS_NATIVE_SetCameraPosition(&a0, &a1);
}

void JASS_WRAPPER_SetCameraQuickPosition(float a0, float a1) {
	JASS_NATIVE_SetCameraQuickPosition(&a0, &a1);
}

void JASS_WRAPPER_ResetToGameCamera(float a0) {
	JASS_NATIVE_ResetToGameCamera(&a0);
}

void JASS_WRAPPER_PanCameraTo(float a0, float a1) {
	JASS_NATIVE_PanCameraTo(&a0, &a1);
}

void JASS_WRAPPER_PanCameraToTimed(float a0, float a1, float a2) {
	JASS_NATIVE_PanCameraToTimed(&a0, &a1, &a2);
}

void JASS_WRAPPER_PanCameraToWithZ(float a0, float a1, float a2) {
	JASS_NATIVE_PanCameraToWithZ(&a0, &a1, &a2);
}

void JASS_WRAPPER_PanCameraToTimedWithZ(float a0, float a1, float a2, float a3) {
	JASS_NATIVE_PanCameraToTimedWithZ(&a0, &a1, &a2, &a3);
}

void JASS_WRAPPER_SetCinematicCamera(const char* a0) {
	JASS_NATIVE_SetCinematicCamera(STR_TO_JASSSTR(a0));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_SetCameraField(DWORD a0, float a1, float a2) {
	JASS_NATIVE_SetCameraField(a0, &a1, &a2);
}

void JASS_WRAPPER_AdjustCameraField(DWORD a0, float a1, float a2) {
	JASS_NATIVE_AdjustCameraField(a0, &a1, &a2);
}

void JASS_WRAPPER_SetCameraTargetController(DWORD a0, float a1, float a2, bool a3) {
	JASS_NATIVE_SetCameraTargetController(a0, &a1, &a2, a3);
}

void JASS_WRAPPER_SetCameraOrientController(DWORD a0, float a1, float a2) {
	JASS_NATIVE_SetCameraOrientController(a0, &a1, &a2);
}

void JASS_WRAPPER_SetCameraRotateMode(float a0, float a1, float a2, float a3) {
	JASS_NATIVE_SetCameraRotateMode(&a0, &a1, &a2, &a3);
}

void JASS_WRAPPER_CameraSetupSetField(DWORD a0, DWORD a1, float a2, float a3) {
	JASS_NATIVE_CameraSetupSetField(a0, a1, &a2, &a3);
}

float JASS_WRAPPER_CameraSetupGetField(DWORD a0, DWORD a1) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_CameraSetupGetField(a0, a1));
	return rv;
}

void JASS_WRAPPER_CameraSetupSetDestPosition(DWORD a0, float a1, float a2, float a3) {
	JASS_NATIVE_CameraSetupSetDestPosition(a0, &a1, &a2, &a3);
}

float JASS_WRAPPER_CameraSetupGetDestPositionX(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_CameraSetupGetDestPositionX(a0));
	return rv;
}

float JASS_WRAPPER_CameraSetupGetDestPositionY(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_CameraSetupGetDestPositionY(a0));
	return rv;
}

void JASS_WRAPPER_CameraSetupApplyWithZ(DWORD a0, float a1) {
	JASS_NATIVE_CameraSetupApplyWithZ(a0, &a1);
}

void JASS_WRAPPER_CameraSetupApplyForceDuration(DWORD a0, bool a1, float a2) {
	JASS_NATIVE_CameraSetupApplyForceDuration(a0, a1, &a2);
}

void JASS_WRAPPER_CameraSetupApplyForceDurationWithZ(DWORD a0, float a1, float a2) {
	JASS_NATIVE_CameraSetupApplyForceDurationWithZ(a0, &a1, &a2);
}

void JASS_WRAPPER_CameraSetTargetNoise(float a0, float a1) {
	JASS_NATIVE_CameraSetTargetNoise(&a0, &a1);
}

void JASS_WRAPPER_CameraSetSourceNoise(float a0, float a1) {
	JASS_NATIVE_CameraSetSourceNoise(&a0, &a1);
}

void JASS_WRAPPER_CameraSetTargetNoiseEx(float a0, float a1, bool a2) {
	JASS_NATIVE_CameraSetTargetNoiseEx(&a0, &a1, a2);
}

void JASS_WRAPPER_CameraSetSourceNoiseEx(float a0, float a1, bool a2) {
	JASS_NATIVE_CameraSetSourceNoiseEx(&a0, &a1, a2);
}

void JASS_WRAPPER_CameraSetSmoothingFactor(float a0) {
	JASS_NATIVE_CameraSetSmoothingFactor(&a0);
}

float JASS_WRAPPER_GetCameraMargin(int a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetCameraMargin(a0));
	return rv;
}

float JASS_WRAPPER_GetCameraBoundMinX() {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetCameraBoundMinX());
	return rv;
}

float JASS_WRAPPER_GetCameraBoundMinY() {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetCameraBoundMinY());
	return rv;
}

float JASS_WRAPPER_GetCameraBoundMaxX() {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetCameraBoundMaxX());
	return rv;
}

float JASS_WRAPPER_GetCameraBoundMaxY() {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetCameraBoundMaxY());
	return rv;
}

float JASS_WRAPPER_GetCameraField(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetCameraField(a0));
	return rv;
}

float JASS_WRAPPER_GetCameraTargetPositionX() {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetCameraTargetPositionX());
	return rv;
}

float JASS_WRAPPER_GetCameraTargetPositionY() {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetCameraTargetPositionY());
	return rv;
}

float JASS_WRAPPER_GetCameraTargetPositionZ() {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetCameraTargetPositionZ());
	return rv;
}

float JASS_WRAPPER_GetCameraEyePositionX() {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetCameraEyePositionX());
	return rv;
}

float JASS_WRAPPER_GetCameraEyePositionY() {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetCameraEyePositionY());
	return rv;
}

float JASS_WRAPPER_GetCameraEyePositionZ() {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetCameraEyePositionZ());
	return rv;
}

void JASS_WRAPPER_SetCineFilterTexture(const char* a0) {
	JASS_NATIVE_SetCineFilterTexture(STR_TO_JASSSTR(a0));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_UnitApplyTimedLife(DWORD a0, int a1, float a2) {
	JASS_NATIVE_UnitApplyTimedLife(a0, a1, &a2);
}

bool JASS_WRAPPER_UnitDamagePoint(DWORD a0, float a1, float a2, float a3, float a4, float a5, bool a6, bool a7, DWORD a8, DWORD a9, DWORD a10) {
	bool rv = JASS_NATIVE_UnitDamagePoint(a0, &a1, &a2, &a3, &a4, &a5, a6, a7, a8, a9, a10);
	return rv;
}

bool JASS_WRAPPER_UnitDamageTarget(DWORD a0, DWORD a1, float a2, bool a3, bool a4, DWORD a5, DWORD a6, DWORD a7) {
	bool rv = JASS_NATIVE_UnitDamageTarget(a0, a1, &a2, a3, a4, a5, a6, a7);
	return rv;
}

bool JASS_WRAPPER_IssuePointOrderById(DWORD a0, int a1, float a2, float a3) {
	bool rv = JASS_NATIVE_IssuePointOrderById(a0, a1, &a2, &a3);
	return rv;
}

bool JASS_WRAPPER_IssueInstantPointOrderById(DWORD a0, int a1, float a2, float a3, DWORD a4) {
	bool rv = JASS_NATIVE_IssueInstantPointOrderById(a0, a1, &a2, &a3, a4);
	return rv;
}

bool JASS_WRAPPER_IssueBuildOrderById(DWORD a0, int a1, float a2, float a3) {
	bool rv = JASS_NATIVE_IssueBuildOrderById(a0, a1, &a2, &a3);
	return rv;
}

bool JASS_WRAPPER_IssueNeutralPointOrderById(DWORD a0, DWORD a1, int a2, float a3, float a4) {
	bool rv = JASS_NATIVE_IssueNeutralPointOrderById(a0, a1, a2, &a3, &a4);
	return rv;
}

bool JASS_WRAPPER_IssueImmediateOrder(DWORD a0, const char* a1) {
	bool rv = JASS_NATIVE_IssueImmediateOrder(a0, STR_TO_JASSSTR(a1));
	JASS_STR_CLEANUP();
	return rv;
}

bool JASS_WRAPPER_IssuePointOrder(DWORD a0, const char* a1, float a2, float a3) {
	bool rv = JASS_NATIVE_IssuePointOrder(a0, STR_TO_JASSSTR(a1), &a2, &a3);
	JASS_STR_CLEANUP();
	return rv;
}

bool JASS_WRAPPER_IssuePointOrderLoc(DWORD a0, const char* a1, DWORD a2) {
	bool rv = JASS_NATIVE_IssuePointOrderLoc(a0, STR_TO_JASSSTR(a1), a2);
	JASS_STR_CLEANUP();
	return rv;
}

bool JASS_WRAPPER_IssueTargetOrder(DWORD a0, const char* a1, DWORD a2) {
	bool rv = JASS_NATIVE_IssueTargetOrder(a0, STR_TO_JASSSTR(a1), a2);
	JASS_STR_CLEANUP();
	return rv;
}

bool JASS_WRAPPER_IssueInstantPointOrder(DWORD a0, const char* a1, float a2, float a3, DWORD a4) {
	bool rv = JASS_NATIVE_IssueInstantPointOrder(a0, STR_TO_JASSSTR(a1), &a2, &a3, a4);
	JASS_STR_CLEANUP();
	return rv;
}

bool JASS_WRAPPER_IssueInstantTargetOrder(DWORD a0, const char* a1, DWORD a2, DWORD a3) {
	bool rv = JASS_NATIVE_IssueInstantTargetOrder(a0, STR_TO_JASSSTR(a1), a2, a3);
	JASS_STR_CLEANUP();
	return rv;
}

bool JASS_WRAPPER_IssueBuildOrder(DWORD a0, const char* a1, float a2, float a3) {
	bool rv = JASS_NATIVE_IssueBuildOrder(a0, STR_TO_JASSSTR(a1), &a2, &a3);
	JASS_STR_CLEANUP();
	return rv;
}

bool JASS_WRAPPER_IssueNeutralImmediateOrder(DWORD a0, DWORD a1, const char* a2) {
	bool rv = JASS_NATIVE_IssueNeutralImmediateOrder(a0, a1, STR_TO_JASSSTR(a2));
	JASS_STR_CLEANUP();
	return rv;
}

bool JASS_WRAPPER_IssueNeutralPointOrder(DWORD a0, DWORD a1, const char* a2, float a3, float a4) {
	bool rv = JASS_NATIVE_IssueNeutralPointOrder(a0, a1, STR_TO_JASSSTR(a2), &a3, &a4);
	JASS_STR_CLEANUP();
	return rv;
}

bool JASS_WRAPPER_IssueNeutralTargetOrder(DWORD a0, DWORD a1, const char* a2, DWORD a3) {
	bool rv = JASS_NATIVE_IssueNeutralTargetOrder(a0, a1, STR_TO_JASSSTR(a2), a3);
	JASS_STR_CLEANUP();
	return rv;
}

float JASS_WRAPPER_WaygateGetDestinationX(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_WaygateGetDestinationX(a0));
	return rv;
}

float JASS_WRAPPER_WaygateGetDestinationY(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_WaygateGetDestinationY(a0));
	return rv;
}

void JASS_WRAPPER_WaygateSetDestination(DWORD a0, float a1, float a2) {
	JASS_NATIVE_WaygateSetDestination(a0, &a1, &a2);
}

DWORD JASS_WRAPPER_CreateItem(int a0, float a1, float a2) {
	DWORD rv = JASS_NATIVE_CreateItem(a0, &a1, &a2);
	return rv;
}

float JASS_WRAPPER_GetItemX(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetItemX(a0));
	return rv;
}

float JASS_WRAPPER_GetItemY(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetItemY(a0));
	return rv;
}

void JASS_WRAPPER_SetItemPosition(DWORD a0, float a1, float a2) {
	JASS_NATIVE_SetItemPosition(a0, &a1, &a2);
}

const char* JASS_WRAPPER_GetItemName(DWORD a0) {
	const char* rv = JASSSTR_TO_STR(JASS_NATIVE_GetItemName(a0));
	return rv;
}

int JASS_WRAPPER_GetPlayerTypedUnitCount(DWORD a0, const char* a1, bool a2, bool a3) {
	int rv = JASS_NATIVE_GetPlayerTypedUnitCount(a0, STR_TO_JASSSTR(a1), a2, a3);
	JASS_STR_CLEANUP();
	return rv;
}

bool JASS_WRAPPER_IsVisibleToPlayer(float a0, float a1, DWORD a2) {
	bool rv = JASS_NATIVE_IsVisibleToPlayer(&a0, &a1, a2);
	return rv;
}

bool JASS_WRAPPER_IsFoggedToPlayer(float a0, float a1, DWORD a2) {
	bool rv = JASS_NATIVE_IsFoggedToPlayer(&a0, &a1, a2);
	return rv;
}

bool JASS_WRAPPER_IsMaskedToPlayer(float a0, float a1, DWORD a2) {
	bool rv = JASS_NATIVE_IsMaskedToPlayer(&a0, &a1, a2);
	return rv;
}

float JASS_WRAPPER_GetPlayerHandicap(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetPlayerHandicap(a0));
	return rv;
}

void JASS_WRAPPER_SetPlayerHandicap(DWORD a0, float a1) {
	JASS_NATIVE_SetPlayerHandicap(a0, &a1);
}

float JASS_WRAPPER_GetPlayerHandicapXP(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetPlayerHandicapXP(a0));
	return rv;
}

void JASS_WRAPPER_SetPlayerHandicapXP(DWORD a0, float a1) {
	JASS_NATIVE_SetPlayerHandicapXP(a0, &a1);
}

void JASS_WRAPPER_ChangeLevel(const char* a0, bool a1) {
	JASS_NATIVE_ChangeLevel(STR_TO_JASSSTR(a0), a1);
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_LoadGame(const char* a0, bool a1) {
	JASS_NATIVE_LoadGame(STR_TO_JASSSTR(a0), a1);
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_SaveGame(const char* a0) {
	JASS_NATIVE_SaveGame(STR_TO_JASSSTR(a0));
	JASS_STR_CLEANUP();
}

bool JASS_WRAPPER_RenameSaveDirectory(const char* a0, const char* a1) {
	bool rv = JASS_NATIVE_RenameSaveDirectory(STR_TO_JASSSTR(a0), STR_TO_JASSSTR(a1));
	JASS_STR_CLEANUP();
	return rv;
}

bool JASS_WRAPPER_RemoveSaveDirectory(const char* a0) {
	bool rv = JASS_NATIVE_RemoveSaveDirectory(STR_TO_JASSSTR(a0));
	JASS_STR_CLEANUP();
	return rv;
}

bool JASS_WRAPPER_CopySaveGame(const char* a0, const char* a1) {
	bool rv = JASS_NATIVE_CopySaveGame(STR_TO_JASSSTR(a0), STR_TO_JASSSTR(a1));
	JASS_STR_CLEANUP();
	return rv;
}

bool JASS_WRAPPER_SaveGameExists(const char* a0) {
	bool rv = JASS_NATIVE_SaveGameExists(STR_TO_JASSSTR(a0));
	JASS_STR_CLEANUP();
	return rv;
}

void JASS_WRAPPER_SetFloatGameState(DWORD a0, float a1) {
	JASS_NATIVE_SetFloatGameState(a0, &a1);
}

float JASS_WRAPPER_GetFloatGameState(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetFloatGameState(a0));
	return rv;
}

void JASS_WRAPPER_DialogSetMessage(DWORD a0, const char* a1) {
	JASS_NATIVE_DialogSetMessage(a0, STR_TO_JASSSTR(a1));
	JASS_STR_CLEANUP();
}

DWORD JASS_WRAPPER_DialogAddButton(DWORD a0, const char* a1, int a2) {
	DWORD rv = JASS_NATIVE_DialogAddButton(a0, STR_TO_JASSSTR(a1), a2);
	JASS_STR_CLEANUP();
	return rv;
}

DWORD JASS_WRAPPER_DialogAddQuitButton(DWORD a0, bool a1, const char* a2, int a3) {
	DWORD rv = JASS_NATIVE_DialogAddQuitButton(a0, a1, STR_TO_JASSSTR(a2), a3);
	JASS_STR_CLEANUP();
	return rv;
}

DWORD JASS_WRAPPER_InitGameCache(const char* a0) {
	DWORD rv = JASS_NATIVE_InitGameCache(STR_TO_JASSSTR(a0));
	JASS_STR_CLEANUP();
	return rv;
}

void JASS_WRAPPER_StoreInteger(DWORD a0, const char* a1, const char* a2, int a3) {
	JASS_NATIVE_StoreInteger(a0, STR_TO_JASSSTR(a1), STR_TO_JASSSTR(a2), a3);
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_StoreReal(DWORD a0, const char* a1, const char* a2, float a3) {
	JASS_NATIVE_StoreReal(a0, STR_TO_JASSSTR(a1), STR_TO_JASSSTR(a2), &a3);
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_StoreBoolean(DWORD a0, const char* a1, const char* a2, bool a3) {
	JASS_NATIVE_StoreBoolean(a0, STR_TO_JASSSTR(a1), STR_TO_JASSSTR(a2), a3);
	JASS_STR_CLEANUP();
}

bool JASS_WRAPPER_StoreUnit(DWORD a0, const char* a1, const char* a2, DWORD a3) {
	bool rv = JASS_NATIVE_StoreUnit(a0, STR_TO_JASSSTR(a1), STR_TO_JASSSTR(a2), a3);
	JASS_STR_CLEANUP();
	return rv;
}

bool JASS_WRAPPER_StoreString(DWORD a0, const char* a1, const char* a2, const char* a3) {
	bool rv = JASS_NATIVE_StoreString(a0, STR_TO_JASSSTR(a1), STR_TO_JASSSTR(a2), STR_TO_JASSSTR(a3));
	JASS_STR_CLEANUP();
	return rv;
}

void JASS_WRAPPER_SaveReal(DWORD a0, int a1, int a2, float a3) {
	JASS_NATIVE_SaveReal(a0, a1, a2, &a3);
}

bool JASS_WRAPPER_SaveStr(DWORD a0, int a1, int a2, const char* a3) {
	bool rv = JASS_NATIVE_SaveStr(a0, a1, a2, STR_TO_JASSSTR(a3));
	JASS_STR_CLEANUP();
	return rv;
}

void JASS_WRAPPER_SyncStoredInteger(DWORD a0, const char* a1, const char* a2) {
	JASS_NATIVE_SyncStoredInteger(a0, STR_TO_JASSSTR(a1), STR_TO_JASSSTR(a2));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_SyncStoredReal(DWORD a0, const char* a1, const char* a2) {
	JASS_NATIVE_SyncStoredReal(a0, STR_TO_JASSSTR(a1), STR_TO_JASSSTR(a2));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_SyncStoredBoolean(DWORD a0, const char* a1, const char* a2) {
	JASS_NATIVE_SyncStoredBoolean(a0, STR_TO_JASSSTR(a1), STR_TO_JASSSTR(a2));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_SyncStoredUnit(DWORD a0, const char* a1, const char* a2) {
	JASS_NATIVE_SyncStoredUnit(a0, STR_TO_JASSSTR(a1), STR_TO_JASSSTR(a2));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_SyncStoredString(DWORD a0, const char* a1, const char* a2) {
	JASS_NATIVE_SyncStoredString(a0, STR_TO_JASSSTR(a1), STR_TO_JASSSTR(a2));
	JASS_STR_CLEANUP();
}

int JASS_WRAPPER_GetStoredInteger(DWORD a0, const char* a1, const char* a2) {
	int rv = JASS_NATIVE_GetStoredInteger(a0, STR_TO_JASSSTR(a1), STR_TO_JASSSTR(a2));
	JASS_STR_CLEANUP();
	return rv;
}

float JASS_WRAPPER_GetStoredReal(DWORD a0, const char* a1, const char* a2) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetStoredReal(a0, STR_TO_JASSSTR(a1), STR_TO_JASSSTR(a2)));
	JASS_STR_CLEANUP();
	return rv;
}

bool JASS_WRAPPER_GetStoredBoolean(DWORD a0, const char* a1, const char* a2) {
	bool rv = JASS_NATIVE_GetStoredBoolean(a0, STR_TO_JASSSTR(a1), STR_TO_JASSSTR(a2));
	JASS_STR_CLEANUP();
	return rv;
}

DWORD JASS_WRAPPER_RestoreUnit(DWORD a0, const char* a1, const char* a2, DWORD a3, float a4, float a5, float a6) {
	DWORD rv = JASS_NATIVE_RestoreUnit(a0, STR_TO_JASSSTR(a1), STR_TO_JASSSTR(a2), a3, &a4, &a5, &a6);
	JASS_STR_CLEANUP();
	return rv;
}

const char* JASS_WRAPPER_GetStoredString(DWORD a0, const char* a1, const char* a2) {
	const char* rv = JASSSTR_TO_STR(JASS_NATIVE_GetStoredString(a0, STR_TO_JASSSTR(a1), STR_TO_JASSSTR(a2)));
	JASS_STR_CLEANUP();
	return rv;
}

bool JASS_WRAPPER_HaveStoredInteger(DWORD a0, const char* a1, const char* a2) {
	bool rv = JASS_NATIVE_HaveStoredInteger(a0, STR_TO_JASSSTR(a1), STR_TO_JASSSTR(a2));
	JASS_STR_CLEANUP();
	return rv;
}

bool JASS_WRAPPER_HaveStoredReal(DWORD a0, const char* a1, const char* a2) {
	bool rv = JASS_NATIVE_HaveStoredReal(a0, STR_TO_JASSSTR(a1), STR_TO_JASSSTR(a2));
	JASS_STR_CLEANUP();
	return rv;
}

bool JASS_WRAPPER_HaveStoredBoolean(DWORD a0, const char* a1, const char* a2) {
	bool rv = JASS_NATIVE_HaveStoredBoolean(a0, STR_TO_JASSSTR(a1), STR_TO_JASSSTR(a2));
	JASS_STR_CLEANUP();
	return rv;
}

bool JASS_WRAPPER_HaveStoredUnit(DWORD a0, const char* a1, const char* a2) {
	bool rv = JASS_NATIVE_HaveStoredUnit(a0, STR_TO_JASSSTR(a1), STR_TO_JASSSTR(a2));
	JASS_STR_CLEANUP();
	return rv;
}

bool JASS_WRAPPER_HaveStoredString(DWORD a0, const char* a1, const char* a2) {
	bool rv = JASS_NATIVE_HaveStoredString(a0, STR_TO_JASSSTR(a1), STR_TO_JASSSTR(a2));
	JASS_STR_CLEANUP();
	return rv;
}

void JASS_WRAPPER_FlushStoredMission(DWORD a0, const char* a1) {
	JASS_NATIVE_FlushStoredMission(a0, STR_TO_JASSSTR(a1));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_FlushStoredInteger(DWORD a0, const char* a1, const char* a2) {
	JASS_NATIVE_FlushStoredInteger(a0, STR_TO_JASSSTR(a1), STR_TO_JASSSTR(a2));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_FlushStoredReal(DWORD a0, const char* a1, const char* a2) {
	JASS_NATIVE_FlushStoredReal(a0, STR_TO_JASSSTR(a1), STR_TO_JASSSTR(a2));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_FlushStoredBoolean(DWORD a0, const char* a1, const char* a2) {
	JASS_NATIVE_FlushStoredBoolean(a0, STR_TO_JASSSTR(a1), STR_TO_JASSSTR(a2));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_FlushStoredUnit(DWORD a0, const char* a1, const char* a2) {
	JASS_NATIVE_FlushStoredUnit(a0, STR_TO_JASSSTR(a1), STR_TO_JASSSTR(a2));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_FlushStoredString(DWORD a0, const char* a1, const char* a2) {
	JASS_NATIVE_FlushStoredString(a0, STR_TO_JASSSTR(a1), STR_TO_JASSSTR(a2));
	JASS_STR_CLEANUP();
}

float JASS_WRAPPER_LoadReal(DWORD a0, int a1, int a2) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_LoadReal(a0, a1, a2));
	return rv;
}

const char* JASS_WRAPPER_LoadStr(DWORD a0, int a1, int a2) {
	const char* rv = JASSSTR_TO_STR(JASS_NATIVE_LoadStr(a0, a1, a2));
	return rv;
}

DWORD JASS_WRAPPER_TriggerRegisterPlayerChatEvent(DWORD a0, DWORD a1, const char* a2, bool a3) {
	DWORD rv = JASS_NATIVE_TriggerRegisterPlayerChatEvent(a0, a1, STR_TO_JASSSTR(a2), a3);
	JASS_STR_CLEANUP();
	return rv;
}

const char* JASS_WRAPPER_GetEventPlayerChatString() {
	const char* rv = JASSSTR_TO_STR(JASS_NATIVE_GetEventPlayerChatString());
	return rv;
}

const char* JASS_WRAPPER_GetEventPlayerChatStringMatched() {
	const char* rv = JASSSTR_TO_STR(JASS_NATIVE_GetEventPlayerChatStringMatched());
	return rv;
}

DWORD JASS_WRAPPER_TriggerRegisterUnitStateEvent(DWORD a0, DWORD a1, DWORD a2, DWORD a3, float a4) {
	DWORD rv = JASS_NATIVE_TriggerRegisterUnitStateEvent(a0, a1, a2, a3, &a4);
	return rv;
}

float JASS_WRAPPER_GetEventDamage() {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetEventDamage());
	return rv;
}

DWORD JASS_WRAPPER_TriggerRegisterUnitInRange(DWORD a0, DWORD a1, float a2, DWORD a3) {
	DWORD rv = JASS_NATIVE_TriggerRegisterUnitInRange(a0, a1, &a2, a3);
	return rv;
}

void JASS_WRAPPER_TriggerSleepAction(float a0) {
	JASS_NATIVE_TriggerSleepAction(&a0);
}

void JASS_WRAPPER_TriggerWaitForSound(DWORD a0, float a1) {
	JASS_NATIVE_TriggerWaitForSound(a0, &a1);
}

void JASS_WRAPPER_GroupEnumUnitsOfType(DWORD a0, const char* a1, DWORD a2) {
	JASS_NATIVE_GroupEnumUnitsOfType(a0, STR_TO_JASSSTR(a1), a2);
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_GroupEnumUnitsOfTypeCounted(DWORD a0, const char* a1, DWORD a2, int a3) {
	JASS_NATIVE_GroupEnumUnitsOfTypeCounted(a0, STR_TO_JASSSTR(a1), a2, a3);
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_GroupEnumUnitsInRange(DWORD a0, float a1, float a2, float a3, DWORD a4) {
	JASS_NATIVE_GroupEnumUnitsInRange(a0, &a1, &a2, &a3, a4);
}

void JASS_WRAPPER_GroupEnumUnitsInRangeOfLoc(DWORD a0, DWORD a1, float a2, DWORD a3) {
	JASS_NATIVE_GroupEnumUnitsInRangeOfLoc(a0, a1, &a2, a3);
}

void JASS_WRAPPER_GroupEnumUnitsInRangeCounted(DWORD a0, float a1, float a2, float a3, DWORD a4, int a5) {
	JASS_NATIVE_GroupEnumUnitsInRangeCounted(a0, &a1, &a2, &a3, a4, a5);
}

void JASS_WRAPPER_GroupEnumUnitsInRangeOfLocCounted(DWORD a0, DWORD a1, float a2, DWORD a3, int a4) {
	JASS_NATIVE_GroupEnumUnitsInRangeOfLocCounted(a0, a1, &a2, a3, a4);
}

bool JASS_WRAPPER_GroupImmediateOrder(DWORD a0, const char* a1) {
	bool rv = JASS_NATIVE_GroupImmediateOrder(a0, STR_TO_JASSSTR(a1));
	JASS_STR_CLEANUP();
	return rv;
}

bool JASS_WRAPPER_GroupPointOrder(DWORD a0, const char* a1, float a2, float a3) {
	bool rv = JASS_NATIVE_GroupPointOrder(a0, STR_TO_JASSSTR(a1), &a2, &a3);
	JASS_STR_CLEANUP();
	return rv;
}

bool JASS_WRAPPER_GroupPointOrderLoc(DWORD a0, const char* a1, DWORD a2) {
	bool rv = JASS_NATIVE_GroupPointOrderLoc(a0, STR_TO_JASSSTR(a1), a2);
	JASS_STR_CLEANUP();
	return rv;
}

bool JASS_WRAPPER_GroupPointOrderById(DWORD a0, int a1, float a2, float a3) {
	bool rv = JASS_NATIVE_GroupPointOrderById(a0, a1, &a2, &a3);
	return rv;
}

bool JASS_WRAPPER_GroupTargetOrder(DWORD a0, const char* a1, DWORD a2) {
	bool rv = JASS_NATIVE_GroupTargetOrder(a0, STR_TO_JASSSTR(a1), a2);
	JASS_STR_CLEANUP();
	return rv;
}

float JASS_WRAPPER_GetWidgetLife(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetWidgetLife(a0));
	return rv;
}

void JASS_WRAPPER_SetWidgetLife(DWORD a0, float a1) {
	JASS_NATIVE_SetWidgetLife(a0, &a1);
}

float JASS_WRAPPER_GetWidgetX(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetWidgetX(a0));
	return rv;
}

float JASS_WRAPPER_GetWidgetY(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetWidgetY(a0));
	return rv;
}

DWORD JASS_WRAPPER_CreateDestructable(int a0, float a1, float a2, float a3, float a4, int a5) {
	DWORD rv = JASS_NATIVE_CreateDestructable(a0, &a1, &a2, &a3, &a4, a5);
	return rv;
}

DWORD JASS_WRAPPER_CreateDestructableZ(int a0, float a1, float a2, float a3, float a4, float a5, int a6) {
	DWORD rv = JASS_NATIVE_CreateDestructableZ(a0, &a1, &a2, &a3, &a4, &a5, a6);
	return rv;
}

DWORD JASS_WRAPPER_CreateDeadDestructable(int a0, float a1, float a2, float a3, float a4, int a5) {
	DWORD rv = JASS_NATIVE_CreateDeadDestructable(a0, &a1, &a2, &a3, &a4, a5);
	return rv;
}

DWORD JASS_WRAPPER_CreateDeadDestructableZ(int a0, float a1, float a2, float a3, float a4, float a5, int a6) {
	DWORD rv = JASS_NATIVE_CreateDeadDestructableZ(a0, &a1, &a2, &a3, &a4, &a5, a6);
	return rv;
}

float JASS_WRAPPER_GetDestructableX(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetDestructableX(a0));
	return rv;
}

float JASS_WRAPPER_GetDestructableY(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetDestructableY(a0));
	return rv;
}

void JASS_WRAPPER_SetDestructableLife(DWORD a0, float a1) {
	JASS_NATIVE_SetDestructableLife(a0, &a1);
}

float JASS_WRAPPER_GetDestructableLife(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetDestructableLife(a0));
	return rv;
}

void JASS_WRAPPER_SetDestructableMaxLife(DWORD a0, float a1) {
	JASS_NATIVE_SetDestructableMaxLife(a0, &a1);
}

float JASS_WRAPPER_GetDestructableMaxLife(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetDestructableMaxLife(a0));
	return rv;
}

void JASS_WRAPPER_DestructableRestoreLife(DWORD a0, float a1, bool a2) {
	JASS_NATIVE_DestructableRestoreLife(a0, &a1, a2);
}

void JASS_WRAPPER_QueueDestructableAnimation(DWORD a0, const char* a1) {
	JASS_NATIVE_QueueDestructableAnimation(a0, STR_TO_JASSSTR(a1));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_SetDestructableAnimation(DWORD a0, const char* a1) {
	JASS_NATIVE_SetDestructableAnimation(a0, STR_TO_JASSSTR(a1));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_SetDestructableAnimationSpeed(DWORD a0, float a1) {
	JASS_NATIVE_SetDestructableAnimationSpeed(a0, &a1);
}

float JASS_WRAPPER_GetDestructableOccluderHeight(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetDestructableOccluderHeight(a0));
	return rv;
}

void JASS_WRAPPER_SetDestructableOccluderHeight(DWORD a0, float a1) {
	JASS_NATIVE_SetDestructableOccluderHeight(a0, &a1);
}

const char* JASS_WRAPPER_GetDestructableName(DWORD a0) {
	const char* rv = JASSSTR_TO_STR(JASS_NATIVE_GetDestructableName(a0));
	return rv;
}

DWORD JASS_WRAPPER_CreateUnit(DWORD a0, int a1, float a2, float a3, float a4) {
	DWORD rv = JASS_NATIVE_CreateUnit(a0, a1, &a2, &a3, &a4);
	return rv;
}

DWORD JASS_WRAPPER_CreateUnitByName(DWORD a0, const char* a1, float a2, float a3, float a4) {
	DWORD rv = JASS_NATIVE_CreateUnitByName(a0, STR_TO_JASSSTR(a1), &a2, &a3, &a4);
	JASS_STR_CLEANUP();
	return rv;
}

DWORD JASS_WRAPPER_CreateUnitAtLoc(DWORD a0, int a1, DWORD a2, float a3) {
	DWORD rv = JASS_NATIVE_CreateUnitAtLoc(a0, a1, a2, &a3);
	return rv;
}

DWORD JASS_WRAPPER_CreateUnitAtLocByName(DWORD a0, const char* a1, DWORD a2, float a3) {
	DWORD rv = JASS_NATIVE_CreateUnitAtLocByName(a0, STR_TO_JASSSTR(a1), a2, &a3);
	JASS_STR_CLEANUP();
	return rv;
}

DWORD JASS_WRAPPER_CreateCorpse(DWORD a0, int a1, float a2, float a3, float a4) {
	DWORD rv = JASS_NATIVE_CreateCorpse(a0, a1, &a2, &a3, &a4);
	return rv;
}

float JASS_WRAPPER_GetUnitState(DWORD a0, DWORD a1) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetUnitState(a0, a1));
	return rv;
}

float JASS_WRAPPER_GetUnitX(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetUnitX(a0));
	return rv;
}

float JASS_WRAPPER_GetUnitY(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetUnitY(a0));
	return rv;
}

float JASS_WRAPPER_GetUnitFacing(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetUnitFacing(a0));
	return rv;
}

float JASS_WRAPPER_GetUnitMoveSpeed(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetUnitMoveSpeed(a0));
	return rv;
}

float JASS_WRAPPER_GetUnitDefaultMoveSpeed(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetUnitDefaultMoveSpeed(a0));
	return rv;
}

const char* JASS_WRAPPER_GetUnitName(DWORD a0) {
	const char* rv = JASSSTR_TO_STR(JASS_NATIVE_GetUnitName(a0));
	return rv;
}

void JASS_WRAPPER_SetUnitX(DWORD a0, float a1) {
	JASS_NATIVE_SetUnitX(a0, &a1);
}

void JASS_WRAPPER_SetUnitY(DWORD a0, float a1) {
	JASS_NATIVE_SetUnitY(a0, &a1);
}

void JASS_WRAPPER_SetUnitPosition(DWORD a0, float a1, float a2) {
	JASS_NATIVE_SetUnitPosition(a0, &a1, &a2);
}

void JASS_WRAPPER_SetUnitFacing(DWORD a0, float a1) {
	JASS_NATIVE_SetUnitFacing(a0, &a1);
}

void JASS_WRAPPER_SetUnitFacingTimed(DWORD a0, float a1, float a2) {
	JASS_NATIVE_SetUnitFacingTimed(a0, &a1, &a2);
}

void JASS_WRAPPER_SetUnitFlyHeight(DWORD a0, float a1, float a2) {
	JASS_NATIVE_SetUnitFlyHeight(a0, &a1, &a2);
}

void JASS_WRAPPER_SetUnitMoveSpeed(DWORD a0, float a1) {
	JASS_NATIVE_SetUnitMoveSpeed(a0, &a1);
}

void JASS_WRAPPER_SetUnitTurnSpeed(DWORD a0, float a1) {
	JASS_NATIVE_SetUnitTurnSpeed(a0, &a1);
}

void JASS_WRAPPER_SetUnitPropWindow(DWORD a0, float a1) {
	JASS_NATIVE_SetUnitPropWindow(a0, &a1);
}

float JASS_WRAPPER_GetUnitAcquireRange(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetUnitAcquireRange(a0));
	return rv;
}

float JASS_WRAPPER_GetUnitTurnSpeed(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetUnitTurnSpeed(a0));
	return rv;
}

float JASS_WRAPPER_GetUnitPropWindow(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetUnitPropWindow(a0));
	return rv;
}

float JASS_WRAPPER_GetUnitFlyHeight(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetUnitFlyHeight(a0));
	return rv;
}

float JASS_WRAPPER_GetUnitDefaultAcquireRange(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetUnitDefaultAcquireRange(a0));
	return rv;
}

float JASS_WRAPPER_GetUnitDefaultTurnSpeed(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetUnitDefaultTurnSpeed(a0));
	return rv;
}

float JASS_WRAPPER_GetUnitDefaultPropWindow(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetUnitDefaultPropWindow(a0));
	return rv;
}

float JASS_WRAPPER_GetUnitDefaultFlyHeight(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetUnitDefaultFlyHeight(a0));
	return rv;
}

void JASS_WRAPPER_SetUnitAcquireRange(DWORD a0, float a1) {
	JASS_NATIVE_SetUnitAcquireRange(a0, &a1);
}

void JASS_WRAPPER_SetUnitState(DWORD a0, DWORD a1, float a2) {
	JASS_NATIVE_SetUnitState(a0, a1, &a2);
}

void JASS_WRAPPER_SetUnitRescueRange(DWORD a0, float a1) {
	JASS_NATIVE_SetUnitRescueRange(a0, &a1);
}

void JASS_WRAPPER_QueueUnitAnimation(DWORD a0, const char* a1) {
	JASS_NATIVE_QueueUnitAnimation(a0, STR_TO_JASSSTR(a1));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_SetUnitAnimation(DWORD a0, const char* a1) {
	JASS_NATIVE_SetUnitAnimation(a0, STR_TO_JASSSTR(a1));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_SetUnitAnimationWithRarity(DWORD a0, const char* a1, DWORD a2) {
	JASS_NATIVE_SetUnitAnimationWithRarity(a0, STR_TO_JASSSTR(a1), a2);
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_AddUnitAnimationProperties(DWORD a0, const char* a1, bool a2) {
	JASS_NATIVE_AddUnitAnimationProperties(a0, STR_TO_JASSSTR(a1), a2);
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_SetUnitScale(DWORD a0, float a1, float a2, float a3) {
	JASS_NATIVE_SetUnitScale(a0, &a1, &a2, &a3);
}

void JASS_WRAPPER_SetUnitTimeScale(DWORD a0, float a1) {
	JASS_NATIVE_SetUnitTimeScale(a0, &a1);
}

void JASS_WRAPPER_SetUnitBlendTime(DWORD a0, float a1) {
	JASS_NATIVE_SetUnitBlendTime(a0, &a1);
}

void JASS_WRAPPER_SetUnitLookAt(DWORD a0, const char* a1, DWORD a2, float a3, float a4, float a5) {
	JASS_NATIVE_SetUnitLookAt(a0, STR_TO_JASSSTR(a1), a2, &a3, &a4, &a5);
	JASS_STR_CLEANUP();
}

const char* JASS_WRAPPER_GetHeroProperName(DWORD a0) {
	const char* rv = JASSSTR_TO_STR(JASS_NATIVE_GetHeroProperName(a0));
	return rv;
}

bool JASS_WRAPPER_ReviveHero(DWORD a0, float a1, float a2, bool a3) {
	bool rv = JASS_NATIVE_ReviveHero(a0, &a1, &a2, a3);
	return rv;
}

bool JASS_WRAPPER_UnitDropItemPoint(DWORD a0, DWORD a1, float a2, float a3) {
	bool rv = JASS_NATIVE_UnitDropItemPoint(a0, a1, &a2, &a3);
	return rv;
}

bool JASS_WRAPPER_UnitUseItemPoint(DWORD a0, DWORD a1, float a2, float a3) {
	bool rv = JASS_NATIVE_UnitUseItemPoint(a0, a1, &a2, &a3);
	return rv;
}

bool JASS_WRAPPER_IsUnitInRange(DWORD a0, DWORD a1, float a2) {
	bool rv = JASS_NATIVE_IsUnitInRange(a0, a1, &a2);
	return rv;
}

bool JASS_WRAPPER_IsUnitInRangeXY(DWORD a0, float a1, float a2, float a3) {
	bool rv = JASS_NATIVE_IsUnitInRangeXY(a0, &a1, &a2, &a3);
	return rv;
}

bool JASS_WRAPPER_IsUnitInRangeLoc(DWORD a0, DWORD a1, float a2) {
	bool rv = JASS_NATIVE_IsUnitInRangeLoc(a0, a1, &a2);
	return rv;
}

float JASS_WRAPPER_Deg2Rad(float a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_Deg2Rad(&a0));
	return rv;
}

float JASS_WRAPPER_Rad2Deg(float a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_Rad2Deg(&a0));
	return rv;
}

float JASS_WRAPPER_Sin(float a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_Sin(&a0));
	return rv;
}

float JASS_WRAPPER_Cos(float a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_Cos(&a0));
	return rv;
}

float JASS_WRAPPER_Tan(float a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_Tan(&a0));
	return rv;
}

float JASS_WRAPPER_Asin(float a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_Asin(&a0));
	return rv;
}

float JASS_WRAPPER_Acos(float a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_Acos(&a0));
	return rv;
}

float JASS_WRAPPER_Atan(float a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_Atan(&a0));
	return rv;
}

float JASS_WRAPPER_Atan2(float a0, float a1) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_Atan2(&a0, &a1));
	return rv;
}

float JASS_WRAPPER_SquareRoot(float a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_SquareRoot(&a0));
	return rv;
}

float JASS_WRAPPER_Pow(float a0, float a1) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_Pow(&a0, &a1));
	return rv;
}

float JASS_WRAPPER_I2R(int a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_I2R(a0));
	return rv;
}

int JASS_WRAPPER_R2I(float a0) {
	int rv = JASS_NATIVE_R2I(&a0);
	return rv;
}

const char* JASS_WRAPPER_I2S(int a0) {
	const char* rv = JASSSTR_TO_STR(JASS_NATIVE_I2S(a0));
	return rv;
}

const char* JASS_WRAPPER_R2S(float a0) {
	const char* rv = JASSSTR_TO_STR(JASS_NATIVE_R2S(&a0));
	return rv;
}

const char* JASS_WRAPPER_R2SW(float a0, int a1, int a2) {
	const char* rv = JASSSTR_TO_STR(JASS_NATIVE_R2SW(&a0, a1, a2));
	return rv;
}

int JASS_WRAPPER_S2I(const char* a0) {
	int rv = JASS_NATIVE_S2I(STR_TO_JASSSTR(a0));
	JASS_STR_CLEANUP();
	return rv;
}

float JASS_WRAPPER_S2R(const char* a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_S2R(STR_TO_JASSSTR(a0)));
	JASS_STR_CLEANUP();
	return rv;
}

const char* JASS_WRAPPER_SubString(const char* a0, int a1, int a2) {
	const char* rv = JASSSTR_TO_STR(JASS_NATIVE_SubString(STR_TO_JASSSTR(a0), a1, a2));
	JASS_STR_CLEANUP();
	return rv;
}

int JASS_WRAPPER_StringLength(const char* a0) {
	int rv = JASS_NATIVE_StringLength(STR_TO_JASSSTR(a0));
	JASS_STR_CLEANUP();
	return rv;
}

const char* JASS_WRAPPER_StringCase(const char* a0, bool a1) {
	const char* rv = JASSSTR_TO_STR(JASS_NATIVE_StringCase(STR_TO_JASSSTR(a0), a1));
	JASS_STR_CLEANUP();
	return rv;
}

int JASS_WRAPPER_StringHash(const char* a0) {
	int rv = JASS_NATIVE_StringHash(STR_TO_JASSSTR(a0));
	JASS_STR_CLEANUP();
	return rv;
}

const char* JASS_WRAPPER_GetLocalizedString(const char* a0) {
	const char* rv = JASSSTR_TO_STR(JASS_NATIVE_GetLocalizedString(STR_TO_JASSSTR(a0)));
	JASS_STR_CLEANUP();
	return rv;
}

int JASS_WRAPPER_GetLocalizedHotkey(const char* a0) {
	int rv = JASS_NATIVE_GetLocalizedHotkey(STR_TO_JASSSTR(a0));
	JASS_STR_CLEANUP();
	return rv;
}

void JASS_WRAPPER_SetMapName(const char* a0) {
	JASS_NATIVE_SetMapName(STR_TO_JASSSTR(a0));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_SetMapDescription(const char* a0) {
	JASS_NATIVE_SetMapDescription(STR_TO_JASSSTR(a0));
	JASS_STR_CLEANUP();
}

void JASS_WRAPPER_DefineStartLocation(int a0, float a1, float a2) {
	JASS_NATIVE_DefineStartLocation(a0, &a1, &a2);
}

float JASS_WRAPPER_GetStartLocationX(int a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetStartLocationX(a0));
	return rv;
}

float JASS_WRAPPER_GetStartLocationY(int a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetStartLocationY(a0));
	return rv;
}

void JASS_WRAPPER_SetPlayerName(DWORD a0, const char* a1) {
	JASS_NATIVE_SetPlayerName(a0, STR_TO_JASSSTR(a1));
	JASS_STR_CLEANUP();
}

const char* JASS_WRAPPER_GetPlayerName(DWORD a0) {
	const char* rv = JASSSTR_TO_STR(JASS_NATIVE_GetPlayerName(a0));
	return rv;
}

float JASS_WRAPPER_GetPlayerStartLocationX(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetPlayerStartLocationX(a0));
	return rv;
}

float JASS_WRAPPER_GetPlayerStartLocationY(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetPlayerStartLocationY(a0));
	return rv;
}

DWORD JASS_WRAPPER_Location(float a0, float a1) {
	DWORD rv = JASS_NATIVE_Location(&a0, &a1);
	return rv;
}

void JASS_WRAPPER_MoveLocation(DWORD a0, float a1, float a2) {
	JASS_NATIVE_MoveLocation(a0, &a1, &a2);
}

float JASS_WRAPPER_GetLocationX(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetLocationX(a0));
	return rv;
}

float JASS_WRAPPER_GetLocationY(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetLocationY(a0));
	return rv;
}

float JASS_WRAPPER_GetLocationZ(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetLocationZ(a0));
	return rv;
}

void JASS_WRAPPER_TimerStart(DWORD a0, float a1, bool a2, DWORD a3) {
	JASS_NATIVE_TimerStart(a0, &a1, a2, a3);
}

float JASS_WRAPPER_TimerGetTimeout(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_TimerGetTimeout(a0));
	return rv;
}

float JASS_WRAPPER_TimerGetElapsed(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_TimerGetElapsed(a0));
	return rv;
}

float JASS_WRAPPER_TimerGetRemaining(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_TimerGetRemaining(a0));
	return rv;
}

void JASS_WRAPPER_RegionAddCell(DWORD a0, float a1, float a2) {
	JASS_NATIVE_RegionAddCell(a0, &a1, &a2);
}

void JASS_WRAPPER_RegionClearCell(DWORD a0, float a1, float a2) {
	JASS_NATIVE_RegionClearCell(a0, &a1, &a2);
}

bool JASS_WRAPPER_IsPointInRegion(DWORD a0, float a1, float a2) {
	bool rv = JASS_NATIVE_IsPointInRegion(a0, &a1, &a2);
	return rv;
}

DWORD JASS_WRAPPER_Rect(float a0, float a1, float a2, float a3) {
	DWORD rv = JASS_NATIVE_Rect(&a0, &a1, &a2, &a3);
	return rv;
}

void JASS_WRAPPER_SetRect(DWORD a0, float a1, float a2, float a3, float a4) {
	JASS_NATIVE_SetRect(a0, &a1, &a2, &a3, &a4);
}

float JASS_WRAPPER_GetRectCenterX(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetRectCenterX(a0));
	return rv;
}

float JASS_WRAPPER_GetRectCenterY(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetRectCenterY(a0));
	return rv;
}

void JASS_WRAPPER_MoveRectTo(DWORD a0, float a1, float a2) {
	JASS_NATIVE_MoveRectTo(a0, &a1, &a2);
}

float JASS_WRAPPER_GetRectMinX(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetRectMinX(a0));
	return rv;
}

float JASS_WRAPPER_GetRectMinY(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetRectMinY(a0));
	return rv;
}

float JASS_WRAPPER_GetRectMaxX(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetRectMaxX(a0));
	return rv;
}

float JASS_WRAPPER_GetRectMaxY(DWORD a0) {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetRectMaxY(a0));
	return rv;
}

void JASS_WRAPPER_SetFogStateRadius(DWORD a0, DWORD a1, float a2, float a3, float a4, bool a5) {
	JASS_NATIVE_SetFogStateRadius(a0, a1, &a2, &a3, &a4, a5);
}

void JASS_WRAPPER_SetFogStateRadiusLoc(DWORD a0, DWORD a1, DWORD a2, float a3, bool a4) {
	JASS_NATIVE_SetFogStateRadiusLoc(a0, a1, a2, &a3, a4);
}

DWORD JASS_WRAPPER_CreateFogModifierRadius(DWORD a0, DWORD a1, float a2, float a3, float a4, bool a5, bool a6) {
	DWORD rv = JASS_NATIVE_CreateFogModifierRadius(a0, a1, &a2, &a3, &a4, a5, a6);
	return rv;
}

DWORD JASS_WRAPPER_CreateFogModifierRadiusLoc(DWORD a0, DWORD a1, DWORD a2, float a3, bool a4, bool a5) {
	DWORD rv = JASS_NATIVE_CreateFogModifierRadiusLoc(a0, a1, a2, &a3, a4, a5);
	return rv;
}

DWORD JASS_WRAPPER_TriggerRegisterVariableEvent(DWORD a0, const char* a1, DWORD a2, float a3) {
	DWORD rv = JASS_NATIVE_TriggerRegisterVariableEvent(a0, STR_TO_JASSSTR(a1), a2, &a3);
	JASS_STR_CLEANUP();
	return rv;
}

DWORD JASS_WRAPPER_TriggerRegisterTimerEvent(DWORD a0, float a1, bool a2) {
	DWORD rv = JASS_NATIVE_TriggerRegisterTimerEvent(a0, &a1, a2);
	return rv;
}

DWORD JASS_WRAPPER_TriggerRegisterGameStateEvent(DWORD a0, DWORD a1, DWORD a2, float a3) {
	DWORD rv = JASS_NATIVE_TriggerRegisterGameStateEvent(a0, a1, a2, &a3);
	return rv;
}

float JASS_WRAPPER_GetTournamentFinishSoonTimeRemaining() {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetTournamentFinishSoonTimeRemaining());
	return rv;
}

const char* JASS_WRAPPER_GetSaveBasicFilename() {
	const char* rv = JASSSTR_TO_STR(JASS_NATIVE_GetSaveBasicFilename());
	return rv;
}

DWORD JASS_WRAPPER_TriggerRegisterPlayerStateEvent(DWORD a0, DWORD a1, DWORD a2, DWORD a3, float a4) {
	DWORD rv = JASS_NATIVE_TriggerRegisterPlayerStateEvent(a0, a1, a2, a3, &a4);
	return rv;
}

int JASS_WRAPPER_OrderId(const char* a0) {
	int rv = JASS_NATIVE_OrderId(STR_TO_JASSSTR(a0));
	JASS_STR_CLEANUP();
	return rv;
}

const char* JASS_WRAPPER_OrderId2String(int a0) {
	const char* rv = JASSSTR_TO_STR(JASS_NATIVE_OrderId2String(a0));
	return rv;
}

int JASS_WRAPPER_AbilityId(const char* a0) {
	int rv = JASS_NATIVE_AbilityId(STR_TO_JASSSTR(a0));
	JASS_STR_CLEANUP();
	return rv;
}

const char* JASS_WRAPPER_AbilityId2String(int a0) {
	const char* rv = JASSSTR_TO_STR(JASS_NATIVE_AbilityId2String(a0));
	return rv;
}

int JASS_WRAPPER_UnitId(const char* a0) {
	int rv = JASS_NATIVE_UnitId(STR_TO_JASSSTR(a0));
	JASS_STR_CLEANUP();
	return rv;
}

const char* JASS_WRAPPER_UnitId2String(int a0) {
	const char* rv = JASSSTR_TO_STR(JASS_NATIVE_UnitId2String(a0));
	return rv;
}

const char* JASS_WRAPPER_GetObjectName(int a0) {
	const char* rv = JASSSTR_TO_STR(JASS_NATIVE_GetObjectName(a0));
	return rv;
}

float JASS_WRAPPER_GetOrderPointX() {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetOrderPointX());
	return rv;
}

float JASS_WRAPPER_GetOrderPointY() {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetOrderPointY());
	return rv;
}

float JASS_WRAPPER_GetSpellTargetX() {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetSpellTargetX());
	return rv;
}

float JASS_WRAPPER_GetSpellTargetY() {
	float rv = JASS_FLOAT_CAST(JASS_NATIVE_GetSpellTargetY());
	return rv;
}

