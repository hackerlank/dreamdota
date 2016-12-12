inline void SetDefendPlayer(bool a0) {JASS_WRAPPER_SetDefendPlayer(a0);}
inline void SetHeroesTakeItems(bool a0) {JASS_WRAPPER_SetHeroesTakeItems(a0);}
inline void SetUnitsFlee(bool a0) {JASS_WRAPPER_SetUnitsFlee(a0);}
inline void SetGroupsFlee(bool a0) {JASS_WRAPPER_SetGroupsFlee(a0);}
inline void SetSlowChopping(bool a0) {JASS_WRAPPER_SetSlowChopping(a0);}
inline void SetSmartArtillery(bool a0) {JASS_WRAPPER_SetSmartArtillery(a0);}
inline void SetWatchMegaTargets(bool a0) {JASS_WRAPPER_SetWatchMegaTargets(a0);}
inline void SetReplacementCount(int a0) {JASS_WRAPPER_SetReplacementCount(a0);}
inline void PurchaseZeppelin(void) {JASS_WRAPPER_PurchaseZeppelin();}
inline int MeleeDifficulty(void) {return JASS_WRAPPER_MeleeDifficulty();}
inline void DebugBreak(int a0) {JASS_WRAPPER_DebugBreak(a0);}
inline void SetCineFilterTexMapFlags(DWORD a0) {JASS_WRAPPER_SetCineFilterTexMapFlags(a0);}
inline void SetCineFilterStartUV(float a0, float a1, float a2, float a3) {JASS_WRAPPER_SetCineFilterStartUV(a0, a1, a2, a3);}
inline void SetCineFilterEndUV(float a0, float a1, float a2, float a3) {JASS_WRAPPER_SetCineFilterEndUV(a0, a1, a2, a3);}
inline void SetCineFilterStartColor(int a0, int a1, int a2, int a3) {JASS_WRAPPER_SetCineFilterStartColor(a0, a1, a2, a3);}
inline void SetCineFilterEndColor(int a0, int a1, int a2, int a3) {JASS_WRAPPER_SetCineFilterEndColor(a0, a1, a2, a3);}
inline void SetCineFilterDuration(float a0) {JASS_WRAPPER_SetCineFilterDuration(a0);}
inline void DisplayCineFilter(bool a0) {JASS_WRAPPER_DisplayCineFilter(a0);}
inline bool IsCineFilterDisplayed(void) {return JASS_WRAPPER_IsCineFilterDisplayed();}
inline void SetCinematicScene(int a0, DWORD a1, const char* a2, const char* a3, float a4, float a5) {JASS_WRAPPER_SetCinematicScene(a0, a1, a2, a3, a4, a5);}
inline void EndCinematicScene(void) {JASS_WRAPPER_EndCinematicScene();}
inline void ForceCinematicSubtitles(bool a0) {JASS_WRAPPER_ForceCinematicSubtitles(a0);}
inline void NewSoundEnvironment(const char* a0) {JASS_WRAPPER_NewSoundEnvironment(a0);}
inline DWORD CreateSound(const char* a0, bool a1, bool a2, bool a3, int a4, int a5, const char* a6) {return JASS_WRAPPER_CreateSound(a0, a1, a2, a3, a4, a5, a6);}
inline DWORD CreateSoundFilenameWithLabel(const char* a0, bool a1, bool a2, bool a3, int a4, int a5, const char* a6) {return JASS_WRAPPER_CreateSoundFilenameWithLabel(a0, a1, a2, a3, a4, a5, a6);}
inline DWORD CreateSoundFromLabel(const char* a0, bool a1, bool a2, bool a3, int a4, int a5) {return JASS_WRAPPER_CreateSoundFromLabel(a0, a1, a2, a3, a4, a5);}
inline DWORD CreateMIDISound(const char* a0, int a1, int a2) {return JASS_WRAPPER_CreateMIDISound(a0, a1, a2);}
inline void SetStackedSound(const char* a0, float a1, float a2) {JASS_WRAPPER_SetStackedSound(a0, a1, a2);}
inline void ClearStackedSound(const char* a0, float a1, float a2) {JASS_WRAPPER_ClearStackedSound(a0, a1, a2);}
inline void SetStackedSoundRect(const char* a0, DWORD a1) {JASS_WRAPPER_SetStackedSoundRect(a0, a1);}
inline void ClearStackedSoundRect(const char* a0, DWORD a1) {JASS_WRAPPER_ClearStackedSoundRect(a0, a1);}
inline void SetSoundParamsFromLabel(DWORD a0, const char* a1) {JASS_WRAPPER_SetSoundParamsFromLabel(a0, a1);}
inline void SetSoundChannel(DWORD a0, int a1) {JASS_WRAPPER_SetSoundChannel(a0, a1);}
inline void SetSoundVolume(DWORD a0, int a1) {JASS_WRAPPER_SetSoundVolume(a0, a1);}
inline void SetSoundPitch(DWORD a0, float a1) {JASS_WRAPPER_SetSoundPitch(a0, a1);}
inline void SetSoundPlayPosition(DWORD a0, int a1) {JASS_WRAPPER_SetSoundPlayPosition(a0, a1);}
inline void SetSoundDistances(DWORD a0, float a1, float a2) {JASS_WRAPPER_SetSoundDistances(a0, a1, a2);}
inline void SetSoundDistanceCutoff(DWORD a0, float a1) {JASS_WRAPPER_SetSoundDistanceCutoff(a0, a1);}
inline void SetSoundConeAngles(DWORD a0, float a1, float a2, int a3) {JASS_WRAPPER_SetSoundConeAngles(a0, a1, a2, a3);}
inline void SetSoundConeOrientation(DWORD a0, float a1, float a2, float a3) {JASS_WRAPPER_SetSoundConeOrientation(a0, a1, a2, a3);}
inline void SetSoundPosition(DWORD a0, float a1, float a2, float a3) {JASS_WRAPPER_SetSoundPosition(a0, a1, a2, a3);}
inline void SetSoundVelocity(DWORD a0, float a1, float a2, float a3) {JASS_WRAPPER_SetSoundVelocity(a0, a1, a2, a3);}
inline void AttachSoundToUnit(DWORD a0, DWORD a1) {JASS_WRAPPER_AttachSoundToUnit(a0, a1);}
inline void StartSound(DWORD a0) {JASS_WRAPPER_StartSound(a0);}
inline void StopSound(DWORD a0, bool a1, bool a2) {JASS_WRAPPER_StopSound(a0, a1, a2);}
inline void KillSoundWhenDone(DWORD a0) {JASS_WRAPPER_KillSoundWhenDone(a0);}
inline void SetMapMusic(const char* a0, bool a1, int a2) {JASS_WRAPPER_SetMapMusic(a0, a1, a2);}
inline void ClearMapMusic(void) {JASS_WRAPPER_ClearMapMusic();}
inline void PlayMusic(const char* a0) {JASS_WRAPPER_PlayMusic(a0);}
inline void PlayMusicEx(const char* a0, int a1, int a2) {JASS_WRAPPER_PlayMusicEx(a0, a1, a2);}
inline void StopMusic(bool a0) {JASS_WRAPPER_StopMusic(a0);}
inline void ResumeMusic(void) {JASS_WRAPPER_ResumeMusic();}
inline void PlayThematicMusic(const char* a0) {JASS_WRAPPER_PlayThematicMusic(a0);}
inline void PlayThematicMusicEx(const char* a0, int a1) {JASS_WRAPPER_PlayThematicMusicEx(a0, a1);}
inline void EndThematicMusic(void) {JASS_WRAPPER_EndThematicMusic();}
inline void SetMusicVolume(int a0) {JASS_WRAPPER_SetMusicVolume(a0);}
inline void SetMusicPlayPosition(int a0) {JASS_WRAPPER_SetMusicPlayPosition(a0);}
inline void SetThematicMusicPlayPosition(int a0) {JASS_WRAPPER_SetThematicMusicPlayPosition(a0);}
inline void SetSoundDuration(DWORD a0, int a1) {JASS_WRAPPER_SetSoundDuration(a0, a1);}
inline int GetSoundDuration(DWORD a0) {return JASS_WRAPPER_GetSoundDuration(a0);}
inline int GetSoundFileDuration(const char* a0) {return JASS_WRAPPER_GetSoundFileDuration(a0);}
inline void VolumeGroupSetVolume(DWORD a0, float a1) {JASS_WRAPPER_VolumeGroupSetVolume(a0, a1);}
inline void VolumeGroupReset(void) {JASS_WRAPPER_VolumeGroupReset();}
inline bool GetSoundIsPlaying(DWORD a0) {return JASS_WRAPPER_GetSoundIsPlaying(a0);}
inline bool GetSoundIsLoading(DWORD a0) {return JASS_WRAPPER_GetSoundIsLoading(a0);}
inline void RegisterStackedSound(DWORD a0, bool a1, float a2, float a3) {JASS_WRAPPER_RegisterStackedSound(a0, a1, a2, a3);}
inline void UnregisterStackedSound(DWORD a0, bool a1, float a2, float a3) {JASS_WRAPPER_UnregisterStackedSound(a0, a1, a2, a3);}
inline DWORD AddWeatherEffect(DWORD a0, int a1) {return JASS_WRAPPER_AddWeatherEffect(a0, a1);}
inline void RemoveWeatherEffect(DWORD a0) {JASS_WRAPPER_RemoveWeatherEffect(a0);}
inline void EnableWeatherEffect(DWORD a0, bool a1) {JASS_WRAPPER_EnableWeatherEffect(a0, a1);}
inline DWORD TerrainDeformCrater(float a0, float a1, float a2, float a3, int a4, bool a5) {return JASS_WRAPPER_TerrainDeformCrater(a0, a1, a2, a3, a4, a5);}
inline DWORD TerrainDeformRipple(float a0, float a1, float a2, float a3, int a4, int a5, float a6, float a7, float a8, bool a9) {return JASS_WRAPPER_TerrainDeformRipple(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);}
inline DWORD TerrainDeformWave(float a0, float a1, float a2, float a3, float a4, float a5, float a6, float a7, int a8, int a9) {return JASS_WRAPPER_TerrainDeformWave(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);}
inline DWORD TerrainDeformRandom(float a0, float a1, float a2, float a3, float a4, int a5, int a6) {return JASS_WRAPPER_TerrainDeformRandom(a0, a1, a2, a3, a4, a5, a6);}
inline void TerrainDeformStop(DWORD a0, int a1) {JASS_WRAPPER_TerrainDeformStop(a0, a1);}
inline void TerrainDeformStopAll(void) {JASS_WRAPPER_TerrainDeformStopAll();}
inline void DestroyEffect(DWORD a0) {JASS_WRAPPER_DestroyEffect(a0);}
inline DWORD AddSpecialEffect(const char* a0, float a1, float a2) {return JASS_WRAPPER_AddSpecialEffect(a0, a1, a2);}
inline DWORD AddSpecialEffectLoc(const char* a0, DWORD a1) {return JASS_WRAPPER_AddSpecialEffectLoc(a0, a1);}
inline DWORD AddSpecialEffectTarget(const char* a0, DWORD a1, const char* a2) {return JASS_WRAPPER_AddSpecialEffectTarget(a0, a1, a2);}
inline DWORD AddSpellEffect(const char* a0, DWORD a1, float a2, float a3) {return JASS_WRAPPER_AddSpellEffect(a0, a1, a2, a3);}
inline DWORD AddSpellEffectLoc(const char* a0, DWORD a1, DWORD a2) {return JASS_WRAPPER_AddSpellEffectLoc(a0, a1, a2);}
inline DWORD AddSpellEffectById(int a0, DWORD a1, float a2, float a3) {return JASS_WRAPPER_AddSpellEffectById(a0, a1, a2, a3);}
inline DWORD AddSpellEffectByIdLoc(int a0, DWORD a1, DWORD a2) {return JASS_WRAPPER_AddSpellEffectByIdLoc(a0, a1, a2);}
inline DWORD AddSpellEffectTarget(const char* a0, DWORD a1, DWORD a2, const char* a3) {return JASS_WRAPPER_AddSpellEffectTarget(a0, a1, a2, a3);}
inline DWORD AddSpellEffectTargetById(int a0, DWORD a1, DWORD a2, const char* a3) {return JASS_WRAPPER_AddSpellEffectTargetById(a0, a1, a2, a3);}
inline DWORD AddLightning(const char* a0, bool a1, float a2, float a3, float a4, float a5) {return JASS_WRAPPER_AddLightning(a0, a1, a2, a3, a4, a5);}
inline DWORD AddLightningEx(const char* a0, bool a1, float a2, float a3, float a4, float a5, float a6, float a7) {return JASS_WRAPPER_AddLightningEx(a0, a1, a2, a3, a4, a5, a6, a7);}
inline bool DestroyLightning(DWORD a0) {return JASS_WRAPPER_DestroyLightning(a0);}
inline float GetLightningColorA(DWORD a0) {return JASS_WRAPPER_GetLightningColorA(a0);}
inline float GetLightningColorR(DWORD a0) {return JASS_WRAPPER_GetLightningColorR(a0);}
inline float GetLightningColorG(DWORD a0) {return JASS_WRAPPER_GetLightningColorG(a0);}
inline float GetLightningColorB(DWORD a0) {return JASS_WRAPPER_GetLightningColorB(a0);}
inline bool MoveLightning(DWORD a0, bool a1, float a2, float a3, float a4, float a5) {return JASS_WRAPPER_MoveLightning(a0, a1, a2, a3, a4, a5);}
inline bool MoveLightningEx(DWORD a0, bool a1, float a2, float a3, float a4, float a5, float a6, float a7) {return JASS_WRAPPER_MoveLightningEx(a0, a1, a2, a3, a4, a5, a6, a7);}
inline bool SetLightningColor(DWORD a0, float a1, float a2, float a3, float a4) {return JASS_WRAPPER_SetLightningColor(a0, a1, a2, a3, a4);}
inline const char* GetAbilityEffect(const char* a0, DWORD a1, int a2) {return JASS_WRAPPER_GetAbilityEffect(a0, a1, a2);}
inline const char* GetAbilityEffectById(int a0, DWORD a1, int a2) {return JASS_WRAPPER_GetAbilityEffectById(a0, a1, a2);}
inline const char* GetAbilitySound(const char* a0, DWORD a1) {return JASS_WRAPPER_GetAbilitySound(a0, a1);}
inline const char* GetAbilitySoundById(int a0, DWORD a1) {return JASS_WRAPPER_GetAbilitySoundById(a0, a1);}
inline int GetTerrainCliffLevel(float a0, float a1) {return JASS_WRAPPER_GetTerrainCliffLevel(a0, a1);}
inline void SetWaterBaseColor(int a0, int a1, int a2, int a3) {JASS_WRAPPER_SetWaterBaseColor(a0, a1, a2, a3);}
inline void SetWaterDeforms(bool a0) {JASS_WRAPPER_SetWaterDeforms(a0);}
inline int GetTerrainType(float a0, float a1) {return JASS_WRAPPER_GetTerrainType(a0, a1);}
inline int GetTerrainVariance(float a0, float a1) {return JASS_WRAPPER_GetTerrainVariance(a0, a1);}
inline void SetTerrainType(float a0, float a1, int a2, int a3, int a4, int a5) {JASS_WRAPPER_SetTerrainType(a0, a1, a2, a3, a4, a5);}
inline bool IsTerrainPathable(float a0, float a1, DWORD a2) {return JASS_WRAPPER_IsTerrainPathable(a0, a1, a2);}
inline void SetTerrainPathable(float a0, float a1, DWORD a2, bool a3) {JASS_WRAPPER_SetTerrainPathable(a0, a1, a2, a3);}
inline DWORD CreateImage(const char* a0, float a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, int a10) {return JASS_WRAPPER_CreateImage(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);}
inline void DestroyImage(DWORD a0) {JASS_WRAPPER_DestroyImage(a0);}
inline void ShowImage(DWORD a0, bool a1) {JASS_WRAPPER_ShowImage(a0, a1);}
inline void SetImageConstantHeight(DWORD a0, bool a1, float a2) {JASS_WRAPPER_SetImageConstantHeight(a0, a1, a2);}
inline void SetImagePosition(DWORD a0, float a1, float a2, float a3) {JASS_WRAPPER_SetImagePosition(a0, a1, a2, a3);}
inline void SetImageColor(DWORD a0, int a1, int a2, int a3, int a4) {JASS_WRAPPER_SetImageColor(a0, a1, a2, a3, a4);}
inline void SetImageRender(DWORD a0, bool a1) {JASS_WRAPPER_SetImageRender(a0, a1);}
inline void SetImageRenderAlways(DWORD a0, bool a1) {JASS_WRAPPER_SetImageRenderAlways(a0, a1);}
inline void SetImageAboveWater(DWORD a0, bool a1, bool a2) {JASS_WRAPPER_SetImageAboveWater(a0, a1, a2);}
inline void SetImageType(DWORD a0, int a1) {JASS_WRAPPER_SetImageType(a0, a1);}
inline DWORD CreateUbersplat(float a0, float a1, const char* a2, int a3, int a4, int a5, int a6, bool a7, bool a8) {return JASS_WRAPPER_CreateUbersplat(a0, a1, a2, a3, a4, a5, a6, a7, a8);}
inline void DestroyUbersplat(DWORD a0) {JASS_WRAPPER_DestroyUbersplat(a0);}
inline void ResetUbersplat(DWORD a0) {JASS_WRAPPER_ResetUbersplat(a0);}
inline void FinishUbersplat(DWORD a0) {JASS_WRAPPER_FinishUbersplat(a0);}
inline void ShowUbersplat(DWORD a0, bool a1) {JASS_WRAPPER_ShowUbersplat(a0, a1);}
inline void SetUbersplatRender(DWORD a0, bool a1) {JASS_WRAPPER_SetUbersplatRender(a0, a1);}
inline void SetUbersplatRenderAlways(DWORD a0, bool a1) {JASS_WRAPPER_SetUbersplatRenderAlways(a0, a1);}
inline void SetBlight(DWORD a0, float a1, float a2, float a3, bool a4) {JASS_WRAPPER_SetBlight(a0, a1, a2, a3, a4);}
inline void SetBlightLoc(DWORD a0, DWORD a1, float a2, bool a3) {JASS_WRAPPER_SetBlightLoc(a0, a1, a2, a3);}
inline void SetBlightRect(DWORD a0, DWORD a1, bool a2) {JASS_WRAPPER_SetBlightRect(a0, a1, a2);}
inline void SetBlightPoint(DWORD a0, float a1, float a2, bool a3) {JASS_WRAPPER_SetBlightPoint(a0, a1, a2, a3);}
inline DWORD CreateBlightedGoldmine(DWORD a0, float a1, float a2, float a3) {return JASS_WRAPPER_CreateBlightedGoldmine(a0, a1, a2, a3);}
inline bool IsPointBlighted(float a0, float a1) {return JASS_WRAPPER_IsPointBlighted(a0, a1);}
inline void SetDoodadAnimation(float a0, float a1, float a2, int a3, bool a4, const char* a5, bool a6) {JASS_WRAPPER_SetDoodadAnimation(a0, a1, a2, a3, a4, a5, a6);}
inline void SetDoodadAnimationRect(DWORD a0, int a1, const char* a2, bool a3) {JASS_WRAPPER_SetDoodadAnimationRect(a0, a1, a2, a3);}
inline void StartMeleeAI(DWORD a0, const char* a1) {JASS_WRAPPER_StartMeleeAI(a0, a1);}
inline void StartCampaignAI(DWORD a0, const char* a1) {JASS_WRAPPER_StartCampaignAI(a0, a1);}
inline void CommandAI(DWORD a0, int a1, int a2) {JASS_WRAPPER_CommandAI(a0, a1, a2);}
inline void PauseCompAI(DWORD a0, bool a1) {JASS_WRAPPER_PauseCompAI(a0, a1);}
inline DWORD GetAIDifficulty(DWORD a0) {return JASS_WRAPPER_GetAIDifficulty(a0);}
inline void RemoveGuardPosition(DWORD a0) {JASS_WRAPPER_RemoveGuardPosition(a0);}
inline void RecycleGuardPosition(DWORD a0) {JASS_WRAPPER_RecycleGuardPosition(a0);}
inline void RemoveAllGuardPositions(DWORD a0) {JASS_WRAPPER_RemoveAllGuardPositions(a0);}
inline void ExecuteFunc(const char* a0) {JASS_WRAPPER_ExecuteFunc(a0);}
inline void Cheat(const char* a0) {JASS_WRAPPER_Cheat(a0);}
inline bool IsNoVictoryCheat(void) {return JASS_WRAPPER_IsNoVictoryCheat();}
inline bool IsNoDefeatCheat(void) {return JASS_WRAPPER_IsNoDefeatCheat();}
inline void Preload(const char* a0) {JASS_WRAPPER_Preload(a0);}
inline void PreloadEnd(float a0) {JASS_WRAPPER_PreloadEnd(a0);}
inline void PreloadStart(void) {JASS_WRAPPER_PreloadStart();}
inline void PreloadRefresh(void) {JASS_WRAPPER_PreloadRefresh();}
inline void PreloadEndEx(void) {JASS_WRAPPER_PreloadEndEx();}
inline void PreloadGenStart(void) {JASS_WRAPPER_PreloadGenStart();}
inline void PreloadGenClear(void) {JASS_WRAPPER_PreloadGenClear();}
inline void PreloadGenEnd(const char* a0) {JASS_WRAPPER_PreloadGenEnd(a0);}
inline void Preloader(const char* a0) {JASS_WRAPPER_Preloader(a0);}
inline void DebugS(const char* a0) {JASS_WRAPPER_DebugS(a0);}
inline void DebugFI(const char* a0, int a1) {JASS_WRAPPER_DebugFI(a0, a1);}
inline void DebugUnitID(const char* a0, int a1) {JASS_WRAPPER_DebugUnitID(a0, a1);}
inline void DisplayText(int a0, const char* a1) {JASS_WRAPPER_DisplayText(a0, a1);}
inline void DisplayTextI(int a0, const char* a1, int a2) {JASS_WRAPPER_DisplayTextI(a0, a1, a2);}
inline void DisplayTextII(int a0, const char* a1, int a2, int a3) {JASS_WRAPPER_DisplayTextII(a0, a1, a2, a3);}
inline void DisplayTextIII(int a0, const char* a1, int a2, int a3, int a4) {JASS_WRAPPER_DisplayTextIII(a0, a1, a2, a3, a4);}
inline void SuicideUnit(int a0, int a1) {JASS_WRAPPER_SuicideUnit(a0, a1);}
inline void SuicideUnitEx(int a0, int a1, int a2) {JASS_WRAPPER_SuicideUnitEx(a0, a1, a2);}
inline void Sleep(float a0) {JASS_WRAPPER_Sleep(a0);}
inline void StartThread(DWORD a0) {JASS_WRAPPER_StartThread(a0);}
inline int GetAiPlayer(void) {return JASS_WRAPPER_GetAiPlayer();}
inline bool DoAiScriptDebug(void) {return JASS_WRAPPER_DoAiScriptDebug();}
inline int GetHeroId(void) {return JASS_WRAPPER_GetHeroId();}
inline int GetHeroLevelAI(void) {return JASS_WRAPPER_GetHeroLevelAI();}
inline void SetHeroLevels(DWORD a0) {JASS_WRAPPER_SetHeroLevels(a0);}
inline void SetNewHeroes(bool a0) {JASS_WRAPPER_SetNewHeroes(a0);}
inline int GetUnitCount(int a0) {return JASS_WRAPPER_GetUnitCount(a0);}
inline int GetPlayerUnitTypeCount(DWORD a0, int a1) {return JASS_WRAPPER_GetPlayerUnitTypeCount(a0, a1);}
inline int GetTownUnitCount(int a0, int a1, bool a2) {return JASS_WRAPPER_GetTownUnitCount(a0, a1, a2);}
inline int GetUnitCountDone(int a0) {return JASS_WRAPPER_GetUnitCountDone(a0);}
inline int GetUpgradeLevel(int a0) {return JASS_WRAPPER_GetUpgradeLevel(a0);}
inline int GetUnitGoldCost(int a0) {return JASS_WRAPPER_GetUnitGoldCost(a0);}
inline int GetUnitWoodCost(int a0) {return JASS_WRAPPER_GetUnitWoodCost(a0);}
inline int GetUnitBuildTime(int a0) {return JASS_WRAPPER_GetUnitBuildTime(a0);}
inline int GetUpgradeGoldCost(int a0) {return JASS_WRAPPER_GetUpgradeGoldCost(a0);}
inline int GetUpgradeWoodCost(int a0) {return JASS_WRAPPER_GetUpgradeWoodCost(a0);}
inline int GetEnemyPower(void) {return JASS_WRAPPER_GetEnemyPower();}
inline int GetMinesOwned(void) {return JASS_WRAPPER_GetMinesOwned();}
inline int GetGoldOwned(void) {return JASS_WRAPPER_GetGoldOwned();}
inline int TownWithMine(void) {return JASS_WRAPPER_TownWithMine();}
inline bool TownHasMine(int a0) {return JASS_WRAPPER_TownHasMine(a0);}
inline bool TownHasHall(int a0) {return JASS_WRAPPER_TownHasHall(a0);}
inline int GetNextExpansion(void) {return JASS_WRAPPER_GetNextExpansion();}
inline DWORD GetExpansionPeon(void) {return JASS_WRAPPER_GetExpansionPeon();}
inline DWORD GetEnemyExpansion(void) {return JASS_WRAPPER_GetEnemyExpansion();}
inline bool SetExpansion(DWORD a0, int a1) {return JASS_WRAPPER_SetExpansion(a0, a1);}
inline DWORD GetBuilding(DWORD a0) {return JASS_WRAPPER_GetBuilding(a0);}
inline void SetAllianceTarget(DWORD a0) {JASS_WRAPPER_SetAllianceTarget(a0);}
inline DWORD GetAllianceTarget(void) {return JASS_WRAPPER_GetAllianceTarget();}
inline bool SetProduce(int a0, int a1, int a2) {return JASS_WRAPPER_SetProduce(a0, a1, a2);}
inline bool MergeUnits(int a0, int a1, int a2, int a3) {return JASS_WRAPPER_MergeUnits(a0, a1, a2, a3);}
inline bool ConvertUnits(int a0, int a1) {return JASS_WRAPPER_ConvertUnits(a0, a1);}
inline bool SetUpgrade(int a0) {return JASS_WRAPPER_SetUpgrade(a0);}
inline void Unsummon(DWORD a0) {JASS_WRAPPER_Unsummon(a0);}
inline void ClearHarvestAI(void) {JASS_WRAPPER_ClearHarvestAI();}
inline void HarvestGold(int a0, int a1) {JASS_WRAPPER_HarvestGold(a0, a1);}
inline void HarvestWood(int a0, int a1) {JASS_WRAPPER_HarvestWood(a0, a1);}
inline void StopGathering(void) {JASS_WRAPPER_StopGathering();}
inline void AddGuardPost(int a0, float a1, float a2) {JASS_WRAPPER_AddGuardPost(a0, a1, a2);}
inline void FillGuardPosts(void) {JASS_WRAPPER_FillGuardPosts();}
inline void ReturnGuardPosts(void) {JASS_WRAPPER_ReturnGuardPosts();}
inline void CreateCaptains(void) {JASS_WRAPPER_CreateCaptains();}
inline void SetCaptainHome(int a0, float a1, float a2) {JASS_WRAPPER_SetCaptainHome(a0, a1, a2);}
inline void ResetCaptainLocs(void) {JASS_WRAPPER_ResetCaptainLocs();}
inline void ShiftTownSpot(float a0, float a1) {JASS_WRAPPER_ShiftTownSpot(a0, a1);}
inline void SetCaptainChanges(bool a0) {JASS_WRAPPER_SetCaptainChanges(a0);}
inline void TeleportCaptain(float a0, float a1) {JASS_WRAPPER_TeleportCaptain(a0, a1);}
inline void ClearCaptainTargets(void) {JASS_WRAPPER_ClearCaptainTargets();}
inline void CaptainVsUnits(DWORD a0) {JASS_WRAPPER_CaptainVsUnits(a0);}
inline void CaptainVsPlayer(DWORD a0) {JASS_WRAPPER_CaptainVsPlayer(a0);}
inline void CaptainAttack(float a0, float a1) {JASS_WRAPPER_CaptainAttack(a0, a1);}
inline void GroupTimedLife(bool a0) {JASS_WRAPPER_GroupTimedLife(a0);}
inline void CaptainGoHome(void) {JASS_WRAPPER_CaptainGoHome();}
inline bool CaptainIsHome(void) {return JASS_WRAPPER_CaptainIsHome();}
inline bool CaptainRetreating(void) {return JASS_WRAPPER_CaptainRetreating();}
inline bool CaptainIsFull(void) {return JASS_WRAPPER_CaptainIsFull();}
inline bool CaptainIsEmpty(void) {return JASS_WRAPPER_CaptainIsEmpty();}
inline int CaptainGroupSize(void) {return JASS_WRAPPER_CaptainGroupSize();}
inline int CaptainReadiness(void) {return JASS_WRAPPER_CaptainReadiness();}
inline int CaptainReadinessHP(void) {return JASS_WRAPPER_CaptainReadinessHP();}
inline int CaptainReadinessMa(void) {return JASS_WRAPPER_CaptainReadinessMa();}
inline bool CaptainInCombat(bool a0) {return JASS_WRAPPER_CaptainInCombat(a0);}
inline bool TownThreatened(void) {return JASS_WRAPPER_TownThreatened();}
inline bool CaptainAtGoal(void) {return JASS_WRAPPER_CaptainAtGoal();}
inline bool CreepsOnMap(void) {return JASS_WRAPPER_CreepsOnMap();}
inline void RemoveInjuries(void) {JASS_WRAPPER_RemoveInjuries();}
inline void RemoveSiege(void) {JASS_WRAPPER_RemoveSiege();}
inline bool IsTowered(DWORD a0) {return JASS_WRAPPER_IsTowered(a0);}
inline void DisablePathing(void) {JASS_WRAPPER_DisablePathing();}
inline void SetAmphibious(void) {JASS_WRAPPER_SetAmphibious();}
inline void InitAssault(void) {JASS_WRAPPER_InitAssault();}
inline bool AddAssault(int a0, int a1) {return JASS_WRAPPER_AddAssault(a0, a1);}
inline bool AddDefenders(int a0, int a1) {return JASS_WRAPPER_AddDefenders(a0, a1);}
inline DWORD GetCreepCamp(int a0, int a1, bool a2) {return JASS_WRAPPER_GetCreepCamp(a0, a1, a2);}
inline void StartGetEnemyBase(void) {JASS_WRAPPER_StartGetEnemyBase();}
inline bool WaitGetEnemyBase(void) {return JASS_WRAPPER_WaitGetEnemyBase();}
inline DWORD GetMegaTarget(void) {return JASS_WRAPPER_GetMegaTarget();}
inline DWORD GetEnemyBase(void) {return JASS_WRAPPER_GetEnemyBase();}
inline DWORD GetExpansionFoe(void) {return JASS_WRAPPER_GetExpansionFoe();}
inline int GetExpansionX(void) {return JASS_WRAPPER_GetExpansionX();}
inline int GetExpansionY(void) {return JASS_WRAPPER_GetExpansionY();}
inline void SetStagePoint(float a0, float a1) {JASS_WRAPPER_SetStagePoint(a0, a1);}
inline void AttackMoveKill(DWORD a0) {JASS_WRAPPER_AttackMoveKill(a0);}
inline void AttackMoveXY(int a0, int a1) {JASS_WRAPPER_AttackMoveXY(a0, a1);}
inline void LoadZepWave(int a0, int a1) {JASS_WRAPPER_LoadZepWave(a0, a1);}
inline bool SuicidePlayer(DWORD a0, bool a1) {return JASS_WRAPPER_SuicidePlayer(a0, a1);}
inline bool SuicidePlayerUnits(DWORD a0, bool a1) {return JASS_WRAPPER_SuicidePlayerUnits(a0, a1);}
inline bool UnitAlive(DWORD a0) {return JASS_WRAPPER_UnitAlive(a0);}
inline bool UnitInvis(DWORD a0) {return JASS_WRAPPER_UnitInvis(a0);}
inline int IgnoredUnits(int a0) {return JASS_WRAPPER_IgnoredUnits(a0);}
inline int CommandsWaiting(void) {return JASS_WRAPPER_CommandsWaiting();}
inline int GetLastCommand(void) {return JASS_WRAPPER_GetLastCommand();}
inline int GetLastData(void) {return JASS_WRAPPER_GetLastData();}
inline void PopLastCommand(void) {JASS_WRAPPER_PopLastCommand();}
inline void SetCampaignAI(void) {JASS_WRAPPER_SetCampaignAI();}
inline void SetMeleeAI(void) {JASS_WRAPPER_SetMeleeAI();}
inline void SetTargetHeroes(bool a0) {JASS_WRAPPER_SetTargetHeroes(a0);}
inline void SetHeroesFlee(bool a0) {JASS_WRAPPER_SetHeroesFlee(a0);}
inline void SetHeroesBuyItems(bool a0) {JASS_WRAPPER_SetHeroesBuyItems(a0);}
inline void SetIgnoreInjured(bool a0) {JASS_WRAPPER_SetIgnoreInjured(a0);}
inline void SetPeonsRepair(bool a0) {JASS_WRAPPER_SetPeonsRepair(a0);}
inline void SetRandomPaths(bool a0) {JASS_WRAPPER_SetRandomPaths(a0);}
inline DWORD LoadWidgetHandle(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadWidgetHandle(a0, a1, a2);}
inline DWORD LoadDestructableHandle(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadDestructableHandle(a0, a1, a2);}
inline DWORD LoadItemHandle(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadItemHandle(a0, a1, a2);}
inline DWORD LoadUnitHandle(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadUnitHandle(a0, a1, a2);}
inline DWORD LoadAbilityHandle(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadAbilityHandle(a0, a1, a2);}
inline DWORD LoadTimerHandle(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadTimerHandle(a0, a1, a2);}
inline DWORD LoadRegionHandle(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadRegionHandle(a0, a1, a2);}
inline DWORD LoadTriggerHandle(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadTriggerHandle(a0, a1, a2);}
inline DWORD LoadTriggerConditionHandle(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadTriggerConditionHandle(a0, a1, a2);}
inline DWORD LoadTriggerActionHandle(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadTriggerActionHandle(a0, a1, a2);}
inline DWORD LoadTriggerEventHandle(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadTriggerEventHandle(a0, a1, a2);}
inline DWORD LoadForceHandle(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadForceHandle(a0, a1, a2);}
inline DWORD LoadGroupHandle(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadGroupHandle(a0, a1, a2);}
inline DWORD LoadLocationHandle(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadLocationHandle(a0, a1, a2);}
inline DWORD LoadRectHandle(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadRectHandle(a0, a1, a2);}
inline DWORD LoadBooleanExprHandle(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadBooleanExprHandle(a0, a1, a2);}
inline DWORD LoadSoundHandle(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadSoundHandle(a0, a1, a2);}
inline DWORD LoadEffectHandle(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadEffectHandle(a0, a1, a2);}
inline DWORD LoadUnitPoolHandle(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadUnitPoolHandle(a0, a1, a2);}
inline DWORD LoadItemPoolHandle(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadItemPoolHandle(a0, a1, a2);}
inline DWORD LoadQuestHandle(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadQuestHandle(a0, a1, a2);}
inline DWORD LoadQuestItemHandle(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadQuestItemHandle(a0, a1, a2);}
inline DWORD LoadDefeatConditionHandle(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadDefeatConditionHandle(a0, a1, a2);}
inline DWORD LoadTimerDialogHandle(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadTimerDialogHandle(a0, a1, a2);}
inline DWORD LoadLeaderboardHandle(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadLeaderboardHandle(a0, a1, a2);}
inline DWORD LoadMultiboardHandle(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadMultiboardHandle(a0, a1, a2);}
inline DWORD LoadMultiboardItemHandle(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadMultiboardItemHandle(a0, a1, a2);}
inline DWORD LoadTrackableHandle(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadTrackableHandle(a0, a1, a2);}
inline DWORD LoadDialogHandle(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadDialogHandle(a0, a1, a2);}
inline DWORD LoadButtonHandle(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadButtonHandle(a0, a1, a2);}
inline DWORD LoadTextTagHandle(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadTextTagHandle(a0, a1, a2);}
inline DWORD LoadLightningHandle(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadLightningHandle(a0, a1, a2);}
inline DWORD LoadImageHandle(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadImageHandle(a0, a1, a2);}
inline DWORD LoadUbersplatHandle(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadUbersplatHandle(a0, a1, a2);}
inline DWORD LoadFogStateHandle(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadFogStateHandle(a0, a1, a2);}
inline DWORD LoadFogModifierHandle(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadFogModifierHandle(a0, a1, a2);}
inline DWORD LoadHashtableHandle(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadHashtableHandle(a0, a1, a2);}
inline bool HaveSavedInteger(DWORD a0, int a1, int a2) {return JASS_WRAPPER_HaveSavedInteger(a0, a1, a2);}
inline bool HaveSavedReal(DWORD a0, int a1, int a2) {return JASS_WRAPPER_HaveSavedReal(a0, a1, a2);}
inline bool HaveSavedBoolean(DWORD a0, int a1, int a2) {return JASS_WRAPPER_HaveSavedBoolean(a0, a1, a2);}
inline bool HaveSavedString(DWORD a0, int a1, int a2) {return JASS_WRAPPER_HaveSavedString(a0, a1, a2);}
inline bool HaveSavedHandle(DWORD a0, int a1, int a2) {return JASS_WRAPPER_HaveSavedHandle(a0, a1, a2);}
inline void RemoveSavedInteger(DWORD a0, int a1, int a2) {JASS_WRAPPER_RemoveSavedInteger(a0, a1, a2);}
inline void RemoveSavedReal(DWORD a0, int a1, int a2) {JASS_WRAPPER_RemoveSavedReal(a0, a1, a2);}
inline void RemoveSavedBoolean(DWORD a0, int a1, int a2) {JASS_WRAPPER_RemoveSavedBoolean(a0, a1, a2);}
inline void RemoveSavedString(DWORD a0, int a1, int a2) {JASS_WRAPPER_RemoveSavedString(a0, a1, a2);}
inline void RemoveSavedHandle(DWORD a0, int a1, int a2) {JASS_WRAPPER_RemoveSavedHandle(a0, a1, a2);}
inline void FlushParentHashtable(DWORD a0) {JASS_WRAPPER_FlushParentHashtable(a0);}
inline void FlushChildHashtable(DWORD a0, int a1) {JASS_WRAPPER_FlushChildHashtable(a0, a1);}
inline int GetRandomInt(int a0, int a1) {return JASS_WRAPPER_GetRandomInt(a0, a1);}
inline float GetRandomReal(float a0, float a1) {return JASS_WRAPPER_GetRandomReal(a0, a1);}
inline DWORD CreateUnitPool(void) {return JASS_WRAPPER_CreateUnitPool();}
inline void DestroyUnitPool(DWORD a0) {JASS_WRAPPER_DestroyUnitPool(a0);}
inline void UnitPoolAddUnitType(DWORD a0, int a1, float a2) {JASS_WRAPPER_UnitPoolAddUnitType(a0, a1, a2);}
inline void UnitPoolRemoveUnitType(DWORD a0, int a1) {JASS_WRAPPER_UnitPoolRemoveUnitType(a0, a1);}
inline DWORD PlaceRandomUnit(DWORD a0, DWORD a1, float a2, float a3, float a4) {return JASS_WRAPPER_PlaceRandomUnit(a0, a1, a2, a3, a4);}
inline DWORD CreateItemPool(void) {return JASS_WRAPPER_CreateItemPool();}
inline void DestroyItemPool(DWORD a0) {JASS_WRAPPER_DestroyItemPool(a0);}
inline void ItemPoolAddItemType(DWORD a0, int a1, float a2) {JASS_WRAPPER_ItemPoolAddItemType(a0, a1, a2);}
inline void ItemPoolRemoveItemType(DWORD a0, int a1) {JASS_WRAPPER_ItemPoolRemoveItemType(a0, a1);}
inline DWORD PlaceRandomItem(DWORD a0, float a1, float a2) {return JASS_WRAPPER_PlaceRandomItem(a0, a1, a2);}
inline int ChooseRandomCreep(int a0) {return JASS_WRAPPER_ChooseRandomCreep(a0);}
inline int ChooseRandomNPBuilding(void) {return JASS_WRAPPER_ChooseRandomNPBuilding();}
inline int ChooseRandomItem(int a0) {return JASS_WRAPPER_ChooseRandomItem(a0);}
inline int ChooseRandomItemEx(DWORD a0, int a1) {return JASS_WRAPPER_ChooseRandomItemEx(a0, a1);}
inline void SetRandomSeed(int a0) {JASS_WRAPPER_SetRandomSeed(a0);}
inline void DisplayTextToPlayer(DWORD a0, float a1, float a2, const char* a3) {JASS_WRAPPER_DisplayTextToPlayer(a0, a1, a2, a3);}
inline void DisplayTimedTextToPlayer(DWORD a0, float a1, float a2, float a3, const char* a4) {JASS_WRAPPER_DisplayTimedTextToPlayer(a0, a1, a2, a3, a4);}
inline void DisplayTimedTextFromPlayer(DWORD a0, float a1, float a2, float a3, const char* a4) {JASS_WRAPPER_DisplayTimedTextFromPlayer(a0, a1, a2, a3, a4);}
inline void ClearTextMessages(void) {JASS_WRAPPER_ClearTextMessages();}
inline void EnableUserControl(bool a0) {JASS_WRAPPER_EnableUserControl(a0);}
inline void EnableUserUI(bool a0) {JASS_WRAPPER_EnableUserUI(a0);}
inline void DisableRestartMission(bool a0) {JASS_WRAPPER_DisableRestartMission(a0);}
inline void ForceUIKey(const char* a0) {JASS_WRAPPER_ForceUIKey(a0);}
inline void ForceUICancel(void) {JASS_WRAPPER_ForceUICancel();}
inline void DisplayLoadDialog(void) {JASS_WRAPPER_DisplayLoadDialog();}
inline void SetTerrainFog(float a0, float a1, float a2, float a3, float a4) {JASS_WRAPPER_SetTerrainFog(a0, a1, a2, a3, a4);}
inline void SetUnitFog(float a0, float a1, float a2, float a3, float a4) {JASS_WRAPPER_SetUnitFog(a0, a1, a2, a3, a4);}
inline void SetTerrainFogEx(int a0, float a1, float a2, float a3, float a4, float a5, float a6) {JASS_WRAPPER_SetTerrainFogEx(a0, a1, a2, a3, a4, a5, a6);}
inline void ResetTerrainFog(void) {JASS_WRAPPER_ResetTerrainFog();}
inline void SetDayNightModels(const char* a0, const char* a1) {JASS_WRAPPER_SetDayNightModels(a0, a1);}
inline void SetSkyModel(const char* a0) {JASS_WRAPPER_SetSkyModel(a0);}
inline void SuspendTimeOfDay(bool a0) {JASS_WRAPPER_SuspendTimeOfDay(a0);}
inline void SetTimeOfDayScale(float a0) {JASS_WRAPPER_SetTimeOfDayScale(a0);}
inline float GetTimeOfDayScale(void) {return JASS_WRAPPER_GetTimeOfDayScale();}
inline void ShowInterface(bool a0, float a1) {JASS_WRAPPER_ShowInterface(a0, a1);}
inline void PauseGame(bool a0) {JASS_WRAPPER_PauseGame(a0);}
inline void PingMinimap(float a0, float a1, float a2) {JASS_WRAPPER_PingMinimap(a0, a1, a2);}
inline void PingMinimapEx(float a0, float a1, float a2, int a3, int a4, int a5, bool a6) {JASS_WRAPPER_PingMinimapEx(a0, a1, a2, a3, a4, a5, a6);}
inline void SetIntroShotText(const char* a0) {JASS_WRAPPER_SetIntroShotText(a0);}
inline void SetIntroShotModel(const char* a0) {JASS_WRAPPER_SetIntroShotModel(a0);}
inline void EnableOcclusion(bool a0) {JASS_WRAPPER_EnableOcclusion(a0);}
inline void EnableWorldFogBoundary(bool a0) {JASS_WRAPPER_EnableWorldFogBoundary(a0);}
inline void PlayModelCinematic(const char* a0) {JASS_WRAPPER_PlayModelCinematic(a0);}
inline void PlayCinematic(const char* a0) {JASS_WRAPPER_PlayCinematic(a0);}
inline void SetAltMinimapIcon(const char* a0) {JASS_WRAPPER_SetAltMinimapIcon(a0);}
inline DWORD CreateTextTag(void) {return JASS_WRAPPER_CreateTextTag();}
inline void DestroyTextTag(DWORD a0) {JASS_WRAPPER_DestroyTextTag(a0);}
inline void SetTextTagText(DWORD a0, const char* a1, float a2) {JASS_WRAPPER_SetTextTagText(a0, a1, a2);}
inline void SetTextTagPos(DWORD a0, float a1, float a2, float a3) {JASS_WRAPPER_SetTextTagPos(a0, a1, a2, a3);}
inline void SetTextTagPosUnit(DWORD a0, DWORD a1, float a2) {JASS_WRAPPER_SetTextTagPosUnit(a0, a1, a2);}
inline void SetTextTagColor(DWORD a0, int a1, int a2, int a3, int a4) {JASS_WRAPPER_SetTextTagColor(a0, a1, a2, a3, a4);}
inline void SetTextTagVelocity(DWORD a0, float a1, float a2) {JASS_WRAPPER_SetTextTagVelocity(a0, a1, a2);}
inline void SetTextTagVisibility(DWORD a0, bool a1) {JASS_WRAPPER_SetTextTagVisibility(a0, a1);}
inline void SetTextTagSuspended(DWORD a0, bool a1) {JASS_WRAPPER_SetTextTagSuspended(a0, a1);}
inline void SetTextTagPermanent(DWORD a0, bool a1) {JASS_WRAPPER_SetTextTagPermanent(a0, a1);}
inline void SetTextTagAge(DWORD a0, float a1) {JASS_WRAPPER_SetTextTagAge(a0, a1);}
inline void SetTextTagLifespan(DWORD a0, float a1) {JASS_WRAPPER_SetTextTagLifespan(a0, a1);}
inline void SetTextTagFadepoint(DWORD a0, float a1) {JASS_WRAPPER_SetTextTagFadepoint(a0, a1);}
inline void SetReservedLocalHeroButtons(int a0) {JASS_WRAPPER_SetReservedLocalHeroButtons(a0);}
inline int GetAllyColorFilterState(void) {return JASS_WRAPPER_GetAllyColorFilterState();}
inline void SetAllyColorFilterState(int a0) {JASS_WRAPPER_SetAllyColorFilterState(a0);}
inline bool GetCreepCampFilterState(void) {return JASS_WRAPPER_GetCreepCampFilterState();}
inline void SetCreepCampFilterState(bool a0) {JASS_WRAPPER_SetCreepCampFilterState(a0);}
inline void EnableMinimapFilterButtons(bool a0, bool a1) {JASS_WRAPPER_EnableMinimapFilterButtons(a0, a1);}
inline void EnableDragSelect(bool a0, bool a1) {JASS_WRAPPER_EnableDragSelect(a0, a1);}
inline void EnablePreSelect(bool a0, bool a1) {JASS_WRAPPER_EnablePreSelect(a0, a1);}
inline void EnableSelect(bool a0, bool a1) {JASS_WRAPPER_EnableSelect(a0, a1);}
inline DWORD CreateTrackable(const char* a0, float a1, float a2, float a3) {return JASS_WRAPPER_CreateTrackable(a0, a1, a2, a3);}
inline DWORD TriggerRegisterTrackableHitEvent(DWORD a0, DWORD a1) {return JASS_WRAPPER_TriggerRegisterTrackableHitEvent(a0, a1);}
inline DWORD TriggerRegisterTrackableTrackEvent(DWORD a0, DWORD a1) {return JASS_WRAPPER_TriggerRegisterTrackableTrackEvent(a0, a1);}
inline DWORD GetTriggeringTrackable(void) {return JASS_WRAPPER_GetTriggeringTrackable();}
inline DWORD CreateQuest(void) {return JASS_WRAPPER_CreateQuest();}
inline void DestroyQuest(DWORD a0) {JASS_WRAPPER_DestroyQuest(a0);}
inline void QuestSetTitle(DWORD a0, const char* a1) {JASS_WRAPPER_QuestSetTitle(a0, a1);}
inline void QuestSetDescription(DWORD a0, const char* a1) {JASS_WRAPPER_QuestSetDescription(a0, a1);}
inline void QuestSetIconPath(DWORD a0, const char* a1) {JASS_WRAPPER_QuestSetIconPath(a0, a1);}
inline void QuestSetRequired(DWORD a0, bool a1) {JASS_WRAPPER_QuestSetRequired(a0, a1);}
inline void QuestSetCompleted(DWORD a0, bool a1) {JASS_WRAPPER_QuestSetCompleted(a0, a1);}
inline void QuestSetDiscovered(DWORD a0, bool a1) {JASS_WRAPPER_QuestSetDiscovered(a0, a1);}
inline void QuestSetFailed(DWORD a0, bool a1) {JASS_WRAPPER_QuestSetFailed(a0, a1);}
inline void QuestSetEnabled(DWORD a0, bool a1) {JASS_WRAPPER_QuestSetEnabled(a0, a1);}
inline bool IsQuestRequired(DWORD a0) {return JASS_WRAPPER_IsQuestRequired(a0);}
inline bool IsQuestCompleted(DWORD a0) {return JASS_WRAPPER_IsQuestCompleted(a0);}
inline bool IsQuestDiscovered(DWORD a0) {return JASS_WRAPPER_IsQuestDiscovered(a0);}
inline bool IsQuestFailed(DWORD a0) {return JASS_WRAPPER_IsQuestFailed(a0);}
inline bool IsQuestEnabled(DWORD a0) {return JASS_WRAPPER_IsQuestEnabled(a0);}
inline DWORD QuestCreateItem(DWORD a0) {return JASS_WRAPPER_QuestCreateItem(a0);}
inline void QuestItemSetDescription(DWORD a0, const char* a1) {JASS_WRAPPER_QuestItemSetDescription(a0, a1);}
inline void QuestItemSetCompleted(DWORD a0, bool a1) {JASS_WRAPPER_QuestItemSetCompleted(a0, a1);}
inline bool IsQuestItemCompleted(DWORD a0) {return JASS_WRAPPER_IsQuestItemCompleted(a0);}
inline DWORD CreateDefeatCondition(void) {return JASS_WRAPPER_CreateDefeatCondition();}
inline void DestroyDefeatCondition(DWORD a0) {JASS_WRAPPER_DestroyDefeatCondition(a0);}
inline void DefeatConditionSetDescription(DWORD a0, const char* a1) {JASS_WRAPPER_DefeatConditionSetDescription(a0, a1);}
inline void FlashQuestDialogButton(void) {JASS_WRAPPER_FlashQuestDialogButton();}
inline void ForceQuestDialogUpdate(void) {JASS_WRAPPER_ForceQuestDialogUpdate();}
inline DWORD CreateTimerDialog(DWORD a0) {return JASS_WRAPPER_CreateTimerDialog(a0);}
inline void DestroyTimerDialog(DWORD a0) {JASS_WRAPPER_DestroyTimerDialog(a0);}
inline void TimerDialogSetTitle(DWORD a0, const char* a1) {JASS_WRAPPER_TimerDialogSetTitle(a0, a1);}
inline void TimerDialogSetTitleColor(DWORD a0, int a1, int a2, int a3, int a4) {JASS_WRAPPER_TimerDialogSetTitleColor(a0, a1, a2, a3, a4);}
inline void TimerDialogSetTimeColor(DWORD a0, int a1, int a2, int a3, int a4) {JASS_WRAPPER_TimerDialogSetTimeColor(a0, a1, a2, a3, a4);}
inline void TimerDialogSetSpeed(DWORD a0, float a1) {JASS_WRAPPER_TimerDialogSetSpeed(a0, a1);}
inline void TimerDialogDisplay(DWORD a0, bool a1) {JASS_WRAPPER_TimerDialogDisplay(a0, a1);}
inline bool IsTimerDialogDisplayed(DWORD a0) {return JASS_WRAPPER_IsTimerDialogDisplayed(a0);}
inline void TimerDialogSetRealTimeRemaining(DWORD a0, float a1) {JASS_WRAPPER_TimerDialogSetRealTimeRemaining(a0, a1);}
inline DWORD CreateLeaderboard(void) {return JASS_WRAPPER_CreateLeaderboard();}
inline void DestroyLeaderboard(DWORD a0) {JASS_WRAPPER_DestroyLeaderboard(a0);}
inline int LeaderboardGetItemCount(DWORD a0) {return JASS_WRAPPER_LeaderboardGetItemCount(a0);}
inline void LeaderboardSetSizeByItemCount(DWORD a0, int a1) {JASS_WRAPPER_LeaderboardSetSizeByItemCount(a0, a1);}
inline void LeaderboardAddItem(DWORD a0, const char* a1, int a2, DWORD a3) {JASS_WRAPPER_LeaderboardAddItem(a0, a1, a2, a3);}
inline void LeaderboardRemoveItem(DWORD a0, int a1) {JASS_WRAPPER_LeaderboardRemoveItem(a0, a1);}
inline void LeaderboardRemovePlayerItem(DWORD a0, DWORD a1) {JASS_WRAPPER_LeaderboardRemovePlayerItem(a0, a1);}
inline void LeaderboardSortItemsByValue(DWORD a0, bool a1) {JASS_WRAPPER_LeaderboardSortItemsByValue(a0, a1);}
inline void LeaderboardSortItemsByPlayer(DWORD a0, bool a1) {JASS_WRAPPER_LeaderboardSortItemsByPlayer(a0, a1);}
inline void LeaderboardSortItemsByLabel(DWORD a0, bool a1) {JASS_WRAPPER_LeaderboardSortItemsByLabel(a0, a1);}
inline void LeaderboardClear(DWORD a0) {JASS_WRAPPER_LeaderboardClear(a0);}
inline void LeaderboardDisplay(DWORD a0, bool a1) {JASS_WRAPPER_LeaderboardDisplay(a0, a1);}
inline bool IsLeaderboardDisplayed(DWORD a0) {return JASS_WRAPPER_IsLeaderboardDisplayed(a0);}
inline const char* LeaderboardGetLabelText(DWORD a0) {return JASS_WRAPPER_LeaderboardGetLabelText(a0);}
inline void PlayerSetLeaderboard(DWORD a0, DWORD a1) {JASS_WRAPPER_PlayerSetLeaderboard(a0, a1);}
inline DWORD PlayerGetLeaderboard(DWORD a0) {return JASS_WRAPPER_PlayerGetLeaderboard(a0);}
inline bool LeaderboardHasPlayerItem(DWORD a0, DWORD a1) {return JASS_WRAPPER_LeaderboardHasPlayerItem(a0, a1);}
inline int LeaderboardGetPlayerIndex(DWORD a0, DWORD a1) {return JASS_WRAPPER_LeaderboardGetPlayerIndex(a0, a1);}
inline void LeaderboardSetLabel(DWORD a0, const char* a1) {JASS_WRAPPER_LeaderboardSetLabel(a0, a1);}
inline void LeaderboardSetLabelColor(DWORD a0, int a1, int a2, int a3, int a4) {JASS_WRAPPER_LeaderboardSetLabelColor(a0, a1, a2, a3, a4);}
inline void LeaderboardSetValueColor(DWORD a0, int a1, int a2, int a3, int a4) {JASS_WRAPPER_LeaderboardSetValueColor(a0, a1, a2, a3, a4);}
inline void LeaderboardSetStyle(DWORD a0, bool a1, bool a2, bool a3, bool a4) {JASS_WRAPPER_LeaderboardSetStyle(a0, a1, a2, a3, a4);}
inline void LeaderboardSetItemValue(DWORD a0, int a1, int a2) {JASS_WRAPPER_LeaderboardSetItemValue(a0, a1, a2);}
inline void LeaderboardSetItemLabel(DWORD a0, int a1, const char* a2) {JASS_WRAPPER_LeaderboardSetItemLabel(a0, a1, a2);}
inline void LeaderboardSetItemStyle(DWORD a0, int a1, bool a2, bool a3, bool a4) {JASS_WRAPPER_LeaderboardSetItemStyle(a0, a1, a2, a3, a4);}
inline void LeaderboardSetItemLabelColor(DWORD a0, int a1, int a2, int a3, int a4, int a5) {JASS_WRAPPER_LeaderboardSetItemLabelColor(a0, a1, a2, a3, a4, a5);}
inline void LeaderboardSetItemValueColor(DWORD a0, int a1, int a2, int a3, int a4, int a5) {JASS_WRAPPER_LeaderboardSetItemValueColor(a0, a1, a2, a3, a4, a5);}
inline DWORD CreateMultiboard(void) {return JASS_WRAPPER_CreateMultiboard();}
inline void DestroyMultiboard(DWORD a0) {JASS_WRAPPER_DestroyMultiboard(a0);}
inline void MultiboardDisplay(DWORD a0, bool a1) {JASS_WRAPPER_MultiboardDisplay(a0, a1);}
inline void MultiboardMinimize(DWORD a0, bool a1) {JASS_WRAPPER_MultiboardMinimize(a0, a1);}
inline bool IsMultiboardDisplayed(DWORD a0) {return JASS_WRAPPER_IsMultiboardDisplayed(a0);}
inline bool IsMultiboardMinimized(DWORD a0) {return JASS_WRAPPER_IsMultiboardMinimized(a0);}
inline void MultiboardClear(DWORD a0) {JASS_WRAPPER_MultiboardClear(a0);}
inline void MultiboardSetTitleText(DWORD a0, const char* a1) {JASS_WRAPPER_MultiboardSetTitleText(a0, a1);}
inline const char* MultiboardGetTitleText(DWORD a0) {return JASS_WRAPPER_MultiboardGetTitleText(a0);}
inline void MultiboardSetTitleTextColor(DWORD a0, int a1, int a2, int a3, int a4) {JASS_WRAPPER_MultiboardSetTitleTextColor(a0, a1, a2, a3, a4);}
inline int MultiboardGetRowCount(DWORD a0) {return JASS_WRAPPER_MultiboardGetRowCount(a0);}
inline int MultiboardGetColumnCount(DWORD a0) {return JASS_WRAPPER_MultiboardGetColumnCount(a0);}
inline void MultiboardSetColumnCount(DWORD a0, int a1) {JASS_WRAPPER_MultiboardSetColumnCount(a0, a1);}
inline void MultiboardSetRowCount(DWORD a0, int a1) {JASS_WRAPPER_MultiboardSetRowCount(a0, a1);}
inline void MultiboardSetItemsStyle(DWORD a0, bool a1, bool a2) {JASS_WRAPPER_MultiboardSetItemsStyle(a0, a1, a2);}
inline void MultiboardSetItemsValueColor(DWORD a0, int a1, int a2, int a3, int a4) {JASS_WRAPPER_MultiboardSetItemsValueColor(a0, a1, a2, a3, a4);}
inline void MultiboardSetItemsValue(DWORD a0, const char* a1) {JASS_WRAPPER_MultiboardSetItemsValue(a0, a1);}
inline void MultiboardSetItemsWidth(DWORD a0, float a1) {JASS_WRAPPER_MultiboardSetItemsWidth(a0, a1);}
inline void MultiboardSetItemsIcon(DWORD a0, const char* a1) {JASS_WRAPPER_MultiboardSetItemsIcon(a0, a1);}
inline DWORD MultiboardGetItem(DWORD a0, int a1, int a2) {return JASS_WRAPPER_MultiboardGetItem(a0, a1, a2);}
inline void MultiboardReleaseItem(DWORD a0) {JASS_WRAPPER_MultiboardReleaseItem(a0);}
inline void MultiboardSetItemStyle(DWORD a0, bool a1, bool a2) {JASS_WRAPPER_MultiboardSetItemStyle(a0, a1, a2);}
inline void MultiboardSetItemValue(DWORD a0, const char* a1) {JASS_WRAPPER_MultiboardSetItemValue(a0, a1);}
inline void MultiboardSetItemValueColor(DWORD a0, int a1, int a2, int a3, int a4) {JASS_WRAPPER_MultiboardSetItemValueColor(a0, a1, a2, a3, a4);}
inline void MultiboardSetItemWidth(DWORD a0, float a1) {JASS_WRAPPER_MultiboardSetItemWidth(a0, a1);}
inline void MultiboardSetItemIcon(DWORD a0, const char* a1) {JASS_WRAPPER_MultiboardSetItemIcon(a0, a1);}
inline void MultiboardSuppressDisplay(bool a0) {JASS_WRAPPER_MultiboardSuppressDisplay(a0);}
inline void SetCameraBounds(float a0, float a1, float a2, float a3, float a4, float a5, float a6, float a7) {JASS_WRAPPER_SetCameraBounds(a0, a1, a2, a3, a4, a5, a6, a7);}
inline void SetCameraPosition(float a0, float a1) {JASS_WRAPPER_SetCameraPosition(a0, a1);}
inline void SetCameraQuickPosition(float a0, float a1) {JASS_WRAPPER_SetCameraQuickPosition(a0, a1);}
inline void ResetToGameCamera(float a0) {JASS_WRAPPER_ResetToGameCamera(a0);}
inline void StopCamera(void) {JASS_WRAPPER_StopCamera();}
inline void PanCameraTo(float a0, float a1) {JASS_WRAPPER_PanCameraTo(a0, a1);}
inline void PanCameraToTimed(float a0, float a1, float a2) {JASS_WRAPPER_PanCameraToTimed(a0, a1, a2);}
inline void PanCameraToWithZ(float a0, float a1, float a2) {JASS_WRAPPER_PanCameraToWithZ(a0, a1, a2);}
inline void PanCameraToTimedWithZ(float a0, float a1, float a2, float a3) {JASS_WRAPPER_PanCameraToTimedWithZ(a0, a1, a2, a3);}
inline void SetCinematicCamera(const char* a0) {JASS_WRAPPER_SetCinematicCamera(a0);}
inline void SetCameraField(DWORD a0, float a1, float a2) {JASS_WRAPPER_SetCameraField(a0, a1, a2);}
inline void AdjustCameraField(DWORD a0, float a1, float a2) {JASS_WRAPPER_AdjustCameraField(a0, a1, a2);}
inline void SetCameraTargetController(DWORD a0, float a1, float a2, bool a3) {JASS_WRAPPER_SetCameraTargetController(a0, a1, a2, a3);}
inline void SetCameraOrientController(DWORD a0, float a1, float a2) {JASS_WRAPPER_SetCameraOrientController(a0, a1, a2);}
inline void SetCameraRotateMode(float a0, float a1, float a2, float a3) {JASS_WRAPPER_SetCameraRotateMode(a0, a1, a2, a3);}
inline DWORD CreateCameraSetup(void) {return JASS_WRAPPER_CreateCameraSetup();}
inline void CameraSetupSetField(DWORD a0, DWORD a1, float a2, float a3) {JASS_WRAPPER_CameraSetupSetField(a0, a1, a2, a3);}
inline float CameraSetupGetField(DWORD a0, DWORD a1) {return JASS_WRAPPER_CameraSetupGetField(a0, a1);}
inline void CameraSetupSetDestPosition(DWORD a0, float a1, float a2, float a3) {JASS_WRAPPER_CameraSetupSetDestPosition(a0, a1, a2, a3);}
inline DWORD CameraSetupGetDestPositionLoc(DWORD a0) {return JASS_WRAPPER_CameraSetupGetDestPositionLoc(a0);}
inline float CameraSetupGetDestPositionX(DWORD a0) {return JASS_WRAPPER_CameraSetupGetDestPositionX(a0);}
inline float CameraSetupGetDestPositionY(DWORD a0) {return JASS_WRAPPER_CameraSetupGetDestPositionY(a0);}
inline void CameraSetupApply(DWORD a0, bool a1, bool a2) {JASS_WRAPPER_CameraSetupApply(a0, a1, a2);}
inline void CameraSetupApplyWithZ(DWORD a0, float a1) {JASS_WRAPPER_CameraSetupApplyWithZ(a0, a1);}
inline void CameraSetupApplyForceDuration(DWORD a0, bool a1, float a2) {JASS_WRAPPER_CameraSetupApplyForceDuration(a0, a1, a2);}
inline void CameraSetupApplyForceDurationWithZ(DWORD a0, float a1, float a2) {JASS_WRAPPER_CameraSetupApplyForceDurationWithZ(a0, a1, a2);}
inline void CameraSetTargetNoise(float a0, float a1) {JASS_WRAPPER_CameraSetTargetNoise(a0, a1);}
inline void CameraSetSourceNoise(float a0, float a1) {JASS_WRAPPER_CameraSetSourceNoise(a0, a1);}
inline void CameraSetTargetNoiseEx(float a0, float a1, bool a2) {JASS_WRAPPER_CameraSetTargetNoiseEx(a0, a1, a2);}
inline void CameraSetSourceNoiseEx(float a0, float a1, bool a2) {JASS_WRAPPER_CameraSetSourceNoiseEx(a0, a1, a2);}
inline void CameraSetSmoothingFactor(float a0) {JASS_WRAPPER_CameraSetSmoothingFactor(a0);}
inline float GetCameraMargin(int a0) {return JASS_WRAPPER_GetCameraMargin(a0);}
inline float GetCameraBoundMinX(void) {return JASS_WRAPPER_GetCameraBoundMinX();}
inline float GetCameraBoundMinY(void) {return JASS_WRAPPER_GetCameraBoundMinY();}
inline float GetCameraBoundMaxX(void) {return JASS_WRAPPER_GetCameraBoundMaxX();}
inline float GetCameraBoundMaxY(void) {return JASS_WRAPPER_GetCameraBoundMaxY();}
inline float GetCameraField(DWORD a0) {return JASS_WRAPPER_GetCameraField(a0);}
inline float GetCameraTargetPositionX(void) {return JASS_WRAPPER_GetCameraTargetPositionX();}
inline float GetCameraTargetPositionY(void) {return JASS_WRAPPER_GetCameraTargetPositionY();}
inline float GetCameraTargetPositionZ(void) {return JASS_WRAPPER_GetCameraTargetPositionZ();}
inline DWORD GetCameraTargetPositionLoc(void) {return JASS_WRAPPER_GetCameraTargetPositionLoc();}
inline float GetCameraEyePositionX(void) {return JASS_WRAPPER_GetCameraEyePositionX();}
inline float GetCameraEyePositionY(void) {return JASS_WRAPPER_GetCameraEyePositionY();}
inline float GetCameraEyePositionZ(void) {return JASS_WRAPPER_GetCameraEyePositionZ();}
inline DWORD GetCameraEyePositionLoc(void) {return JASS_WRAPPER_GetCameraEyePositionLoc();}
inline void SetCineFilterTexture(const char* a0) {JASS_WRAPPER_SetCineFilterTexture(a0);}
inline void SetCineFilterBlendMode(DWORD a0) {JASS_WRAPPER_SetCineFilterBlendMode(a0);}
inline bool IsUnitIdType(int a0, DWORD a1) {return JASS_WRAPPER_IsUnitIdType(a0, a1);}
inline DWORD GetOwningPlayer(DWORD a0) {return JASS_WRAPPER_GetOwningPlayer(a0);}
inline void UnitShareVision(DWORD a0, DWORD a1, bool a2) {JASS_WRAPPER_UnitShareVision(a0, a1, a2);}
inline void UnitSuspendDecay(DWORD a0, bool a1) {JASS_WRAPPER_UnitSuspendDecay(a0, a1);}
inline bool UnitAddType(DWORD a0, DWORD a1) {return JASS_WRAPPER_UnitAddType(a0, a1);}
inline bool UnitRemoveType(DWORD a0, DWORD a1) {return JASS_WRAPPER_UnitRemoveType(a0, a1);}
inline bool UnitAddAbility(DWORD a0, int a1) {return JASS_WRAPPER_UnitAddAbility(a0, a1);}
inline bool UnitRemoveAbility(DWORD a0, int a1) {return JASS_WRAPPER_UnitRemoveAbility(a0, a1);}
inline bool UnitMakeAbilityPermanent(DWORD a0, bool a1, int a2) {return JASS_WRAPPER_UnitMakeAbilityPermanent(a0, a1, a2);}
inline bool UnitHasBuffsEx(DWORD a0, bool a1, bool a2, bool a3, bool a4, bool a5, bool a6, bool a7) {return JASS_WRAPPER_UnitHasBuffsEx(a0, a1, a2, a3, a4, a5, a6, a7);}
inline int UnitCountBuffsEx(DWORD a0, bool a1, bool a2, bool a3, bool a4, bool a5, bool a6, bool a7) {return JASS_WRAPPER_UnitCountBuffsEx(a0, a1, a2, a3, a4, a5, a6, a7);}
inline void UnitRemoveBuffs(DWORD a0, bool a1, bool a2) {JASS_WRAPPER_UnitRemoveBuffs(a0, a1, a2);}
inline void UnitRemoveBuffsEx(DWORD a0, bool a1, bool a2, bool a3, bool a4, bool a5, bool a6, bool a7) {JASS_WRAPPER_UnitRemoveBuffsEx(a0, a1, a2, a3, a4, a5, a6, a7);}
inline void UnitAddSleep(DWORD a0, bool a1) {JASS_WRAPPER_UnitAddSleep(a0, a1);}
inline bool UnitCanSleep(DWORD a0) {return JASS_WRAPPER_UnitCanSleep(a0);}
inline void UnitAddSleepPerm(DWORD a0, bool a1) {JASS_WRAPPER_UnitAddSleepPerm(a0, a1);}
inline bool UnitCanSleepPerm(DWORD a0) {return JASS_WRAPPER_UnitCanSleepPerm(a0);}
inline bool UnitIsSleeping(DWORD a0) {return JASS_WRAPPER_UnitIsSleeping(a0);}
inline void UnitWakeUp(DWORD a0) {JASS_WRAPPER_UnitWakeUp(a0);}
inline void UnitApplyTimedLife(DWORD a0, int a1, float a2) {JASS_WRAPPER_UnitApplyTimedLife(a0, a1, a2);}
inline bool UnitIgnoreAlarm(DWORD a0, bool a1) {return JASS_WRAPPER_UnitIgnoreAlarm(a0, a1);}
inline bool UnitIgnoreAlarmToggled(DWORD a0) {return JASS_WRAPPER_UnitIgnoreAlarmToggled(a0);}
inline bool UnitDamagePoint(DWORD a0, float a1, float a2, float a3, float a4, float a5, bool a6, bool a7, DWORD a8, DWORD a9, DWORD a10) {return JASS_WRAPPER_UnitDamagePoint(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);}
inline bool UnitDamageTarget(DWORD a0, DWORD a1, float a2, bool a3, bool a4, DWORD a5, DWORD a6, DWORD a7) {return JASS_WRAPPER_UnitDamageTarget(a0, a1, a2, a3, a4, a5, a6, a7);}
inline int DecUnitAbilityLevel(DWORD a0, int a1) {return JASS_WRAPPER_DecUnitAbilityLevel(a0, a1);}
inline int IncUnitAbilityLevel(DWORD a0, int a1) {return JASS_WRAPPER_IncUnitAbilityLevel(a0, a1);}
inline int SetUnitAbilityLevel(DWORD a0, int a1, int a2) {return JASS_WRAPPER_SetUnitAbilityLevel(a0, a1, a2);}
inline void UnitResetCooldown(DWORD a0) {JASS_WRAPPER_UnitResetCooldown(a0);}
inline void UnitSetConstructionProgress(DWORD a0, int a1) {JASS_WRAPPER_UnitSetConstructionProgress(a0, a1);}
inline void UnitSetUpgradeProgress(DWORD a0, int a1) {JASS_WRAPPER_UnitSetUpgradeProgress(a0, a1);}
inline void UnitPauseTimedLife(DWORD a0, bool a1) {JASS_WRAPPER_UnitPauseTimedLife(a0, a1);}
inline void UnitSetUsesAltIcon(DWORD a0, bool a1) {JASS_WRAPPER_UnitSetUsesAltIcon(a0, a1);}
inline bool IssueImmediateOrderById(DWORD a0, int a1) {return JASS_WRAPPER_IssueImmediateOrderById(a0, a1);}
inline bool IssuePointOrderById(DWORD a0, int a1, float a2, float a3) {return JASS_WRAPPER_IssuePointOrderById(a0, a1, a2, a3);}
inline bool IssuePointOrderByIdLoc(DWORD a0, int a1, DWORD a2) {return JASS_WRAPPER_IssuePointOrderByIdLoc(a0, a1, a2);}
inline bool IssueTargetOrderById(DWORD a0, int a1, DWORD a2) {return JASS_WRAPPER_IssueTargetOrderById(a0, a1, a2);}
inline bool IssueInstantPointOrderById(DWORD a0, int a1, float a2, float a3, DWORD a4) {return JASS_WRAPPER_IssueInstantPointOrderById(a0, a1, a2, a3, a4);}
inline bool IssueInstantTargetOrderById(DWORD a0, int a1, DWORD a2, DWORD a3) {return JASS_WRAPPER_IssueInstantTargetOrderById(a0, a1, a2, a3);}
inline bool IssueBuildOrderById(DWORD a0, int a1, float a2, float a3) {return JASS_WRAPPER_IssueBuildOrderById(a0, a1, a2, a3);}
inline bool IssueNeutralImmediateOrderById(DWORD a0, DWORD a1, int a2) {return JASS_WRAPPER_IssueNeutralImmediateOrderById(a0, a1, a2);}
inline bool IssueNeutralPointOrderById(DWORD a0, DWORD a1, int a2, float a3, float a4) {return JASS_WRAPPER_IssueNeutralPointOrderById(a0, a1, a2, a3, a4);}
inline bool IssueNeutralTargetOrderById(DWORD a0, DWORD a1, int a2, DWORD a3) {return JASS_WRAPPER_IssueNeutralTargetOrderById(a0, a1, a2, a3);}
inline bool IssueImmediateOrder(DWORD a0, const char* a1) {return JASS_WRAPPER_IssueImmediateOrder(a0, a1);}
inline bool IssuePointOrder(DWORD a0, const char* a1, float a2, float a3) {return JASS_WRAPPER_IssuePointOrder(a0, a1, a2, a3);}
inline bool IssuePointOrderLoc(DWORD a0, const char* a1, DWORD a2) {return JASS_WRAPPER_IssuePointOrderLoc(a0, a1, a2);}
inline bool IssueTargetOrder(DWORD a0, const char* a1, DWORD a2) {return JASS_WRAPPER_IssueTargetOrder(a0, a1, a2);}
inline bool IssueInstantPointOrder(DWORD a0, const char* a1, float a2, float a3, DWORD a4) {return JASS_WRAPPER_IssueInstantPointOrder(a0, a1, a2, a3, a4);}
inline bool IssueInstantTargetOrder(DWORD a0, const char* a1, DWORD a2, DWORD a3) {return JASS_WRAPPER_IssueInstantTargetOrder(a0, a1, a2, a3);}
inline bool IssueBuildOrder(DWORD a0, const char* a1, float a2, float a3) {return JASS_WRAPPER_IssueBuildOrder(a0, a1, a2, a3);}
inline bool IssueNeutralImmediateOrder(DWORD a0, DWORD a1, const char* a2) {return JASS_WRAPPER_IssueNeutralImmediateOrder(a0, a1, a2);}
inline bool IssueNeutralPointOrder(DWORD a0, DWORD a1, const char* a2, float a3, float a4) {return JASS_WRAPPER_IssueNeutralPointOrder(a0, a1, a2, a3, a4);}
inline bool IssueNeutralTargetOrder(DWORD a0, DWORD a1, const char* a2, DWORD a3) {return JASS_WRAPPER_IssueNeutralTargetOrder(a0, a1, a2, a3);}
inline float WaygateGetDestinationX(DWORD a0) {return JASS_WRAPPER_WaygateGetDestinationX(a0);}
inline float WaygateGetDestinationY(DWORD a0) {return JASS_WRAPPER_WaygateGetDestinationY(a0);}
inline void WaygateSetDestination(DWORD a0, float a1, float a2) {JASS_WRAPPER_WaygateSetDestination(a0, a1, a2);}
inline void WaygateActivate(DWORD a0, bool a1) {JASS_WRAPPER_WaygateActivate(a0, a1);}
inline bool WaygateIsActive(DWORD a0) {return JASS_WRAPPER_WaygateIsActive(a0);}
inline void AddItemToAllStock(int a0, int a1, int a2) {JASS_WRAPPER_AddItemToAllStock(a0, a1, a2);}
inline void AddItemToStock(DWORD a0, int a1, int a2, int a3) {JASS_WRAPPER_AddItemToStock(a0, a1, a2, a3);}
inline void AddUnitToAllStock(int a0, int a1, int a2) {JASS_WRAPPER_AddUnitToAllStock(a0, a1, a2);}
inline void AddUnitToStock(DWORD a0, int a1, int a2, int a3) {JASS_WRAPPER_AddUnitToStock(a0, a1, a2, a3);}
inline void RemoveItemFromAllStock(int a0) {JASS_WRAPPER_RemoveItemFromAllStock(a0);}
inline void RemoveItemFromStock(DWORD a0, int a1) {JASS_WRAPPER_RemoveItemFromStock(a0, a1);}
inline void RemoveUnitFromAllStock(int a0) {JASS_WRAPPER_RemoveUnitFromAllStock(a0);}
inline void RemoveUnitFromStock(DWORD a0, int a1) {JASS_WRAPPER_RemoveUnitFromStock(a0, a1);}
inline void SetAllItemTypeSlots(int a0) {JASS_WRAPPER_SetAllItemTypeSlots(a0);}
inline void SetAllUnitTypeSlots(int a0) {JASS_WRAPPER_SetAllUnitTypeSlots(a0);}
inline void SetItemTypeSlots(DWORD a0, int a1) {JASS_WRAPPER_SetItemTypeSlots(a0, a1);}
inline void SetUnitTypeSlots(DWORD a0, int a1) {JASS_WRAPPER_SetUnitTypeSlots(a0, a1);}
inline int GetUnitUserData(DWORD a0) {return JASS_WRAPPER_GetUnitUserData(a0);}
inline void SetUnitUserData(DWORD a0, int a1) {JASS_WRAPPER_SetUnitUserData(a0, a1);}
inline DWORD CreateItem(int a0, float a1, float a2) {return JASS_WRAPPER_CreateItem(a0, a1, a2);}
inline void RemoveItem(DWORD a0) {JASS_WRAPPER_RemoveItem(a0);}
inline DWORD GetItemPlayer(DWORD a0) {return JASS_WRAPPER_GetItemPlayer(a0);}
inline int GetItemTypeId(DWORD a0) {return JASS_WRAPPER_GetItemTypeId(a0);}
inline float GetItemX(DWORD a0) {return JASS_WRAPPER_GetItemX(a0);}
inline float GetItemY(DWORD a0) {return JASS_WRAPPER_GetItemY(a0);}
inline void SetItemPosition(DWORD a0, float a1, float a2) {JASS_WRAPPER_SetItemPosition(a0, a1, a2);}
inline void SetItemDropOnDeath(DWORD a0, bool a1) {JASS_WRAPPER_SetItemDropOnDeath(a0, a1);}
inline void SetItemDroppable(DWORD a0, bool a1) {JASS_WRAPPER_SetItemDroppable(a0, a1);}
inline void SetItemPawnable(DWORD a0, bool a1) {JASS_WRAPPER_SetItemPawnable(a0, a1);}
inline void SetItemPlayer(DWORD a0, DWORD a1, bool a2) {JASS_WRAPPER_SetItemPlayer(a0, a1, a2);}
inline void SetItemInvulnerable(DWORD a0, bool a1) {JASS_WRAPPER_SetItemInvulnerable(a0, a1);}
inline bool IsItemInvulnerable(DWORD a0) {return JASS_WRAPPER_IsItemInvulnerable(a0);}
inline int GetItemLevel(DWORD a0) {return JASS_WRAPPER_GetItemLevel(a0);}
inline DWORD GetItemType(DWORD a0) {return JASS_WRAPPER_GetItemType(a0);}
inline void SetItemVisible(DWORD a0, bool a1) {JASS_WRAPPER_SetItemVisible(a0, a1);}
inline bool IsItemVisible(DWORD a0) {return JASS_WRAPPER_IsItemVisible(a0);}
inline void EnumItemsInRect(DWORD a0, DWORD a1, DWORD a2) {JASS_WRAPPER_EnumItemsInRect(a0, a1, a2);}
inline bool IsItemOwned(DWORD a0) {return JASS_WRAPPER_IsItemOwned(a0);}
inline bool IsItemPowerup(DWORD a0) {return JASS_WRAPPER_IsItemPowerup(a0);}
inline bool IsItemSellable(DWORD a0) {return JASS_WRAPPER_IsItemSellable(a0);}
inline bool IsItemPawnable(DWORD a0) {return JASS_WRAPPER_IsItemPawnable(a0);}
inline bool IsItemIdPowerup(int a0) {return JASS_WRAPPER_IsItemIdPowerup(a0);}
inline bool IsItemIdSellable(int a0) {return JASS_WRAPPER_IsItemIdSellable(a0);}
inline bool IsItemIdPawnable(int a0) {return JASS_WRAPPER_IsItemIdPawnable(a0);}
inline void SetItemDropID(DWORD a0, int a1) {JASS_WRAPPER_SetItemDropID(a0, a1);}
inline const char* GetItemName(DWORD a0) {return JASS_WRAPPER_GetItemName(a0);}
inline int GetItemCharges(DWORD a0) {return JASS_WRAPPER_GetItemCharges(a0);}
inline void SetItemCharges(DWORD a0, int a1) {JASS_WRAPPER_SetItemCharges(a0, a1);}
inline int GetItemUserData(DWORD a0) {return JASS_WRAPPER_GetItemUserData(a0);}
inline void SetItemUserData(DWORD a0, int a1) {JASS_WRAPPER_SetItemUserData(a0, a1);}
inline DWORD Player(int a0) {return JASS_WRAPPER_Player(a0);}
inline DWORD GetLocalPlayer(void) {return JASS_WRAPPER_GetLocalPlayer();}
inline bool IsPlayerAlly(DWORD a0, DWORD a1) {return JASS_WRAPPER_IsPlayerAlly(a0, a1);}
inline bool IsPlayerEnemy(DWORD a0, DWORD a1) {return JASS_WRAPPER_IsPlayerEnemy(a0, a1);}
inline bool IsPlayerInForce(DWORD a0, DWORD a1) {return JASS_WRAPPER_IsPlayerInForce(a0, a1);}
inline bool IsPlayerObserver(DWORD a0) {return JASS_WRAPPER_IsPlayerObserver(a0);}
inline DWORD GetPlayerRace(DWORD a0) {return JASS_WRAPPER_GetPlayerRace(a0);}
inline int GetPlayerId(DWORD a0) {return JASS_WRAPPER_GetPlayerId(a0);}
inline void SetPlayerTechMaxAllowed(DWORD a0, int a1, int a2) {JASS_WRAPPER_SetPlayerTechMaxAllowed(a0, a1, a2);}
inline int GetPlayerTechMaxAllowed(DWORD a0, int a1) {return JASS_WRAPPER_GetPlayerTechMaxAllowed(a0, a1);}
inline void AddPlayerTechResearched(DWORD a0, int a1, int a2) {JASS_WRAPPER_AddPlayerTechResearched(a0, a1, a2);}
inline void SetPlayerTechResearched(DWORD a0, int a1, int a2) {JASS_WRAPPER_SetPlayerTechResearched(a0, a1, a2);}
inline bool GetPlayerTechResearched(DWORD a0, int a1, bool a2) {return JASS_WRAPPER_GetPlayerTechResearched(a0, a1, a2);}
inline int GetPlayerTechCount(DWORD a0, int a1, bool a2) {return JASS_WRAPPER_GetPlayerTechCount(a0, a1, a2);}
inline void SetPlayerAbilityAvailable(DWORD a0, int a1, bool a2) {JASS_WRAPPER_SetPlayerAbilityAvailable(a0, a1, a2);}
inline int GetPlayerUnitCount(DWORD a0, bool a1) {return JASS_WRAPPER_GetPlayerUnitCount(a0, a1);}
inline int GetPlayerTypedUnitCount(DWORD a0, const char* a1, bool a2, bool a3) {return JASS_WRAPPER_GetPlayerTypedUnitCount(a0, a1, a2, a3);}
inline int GetPlayerStructureCount(DWORD a0, bool a1) {return JASS_WRAPPER_GetPlayerStructureCount(a0, a1);}
inline bool IsVisibleToPlayer(float a0, float a1, DWORD a2) {return JASS_WRAPPER_IsVisibleToPlayer(a0, a1, a2);}
inline bool IsLocationVisibleToPlayer(DWORD a0, DWORD a1) {return JASS_WRAPPER_IsLocationVisibleToPlayer(a0, a1);}
inline bool IsFoggedToPlayer(float a0, float a1, DWORD a2) {return JASS_WRAPPER_IsFoggedToPlayer(a0, a1, a2);}
inline bool IsLocationFoggedToPlayer(DWORD a0, DWORD a1) {return JASS_WRAPPER_IsLocationFoggedToPlayer(a0, a1);}
inline bool IsMaskedToPlayer(float a0, float a1, DWORD a2) {return JASS_WRAPPER_IsMaskedToPlayer(a0, a1, a2);}
inline bool IsLocationMaskedToPlayer(DWORD a0, DWORD a1) {return JASS_WRAPPER_IsLocationMaskedToPlayer(a0, a1);}
inline void SetPlayerState(DWORD a0, DWORD a1, int a2) {JASS_WRAPPER_SetPlayerState(a0, a1, a2);}
inline int GetPlayerState(DWORD a0, DWORD a1) {return JASS_WRAPPER_GetPlayerState(a0, a1);}
inline int GetPlayerScore(DWORD a0, DWORD a1) {return JASS_WRAPPER_GetPlayerScore(a0, a1);}
inline bool GetPlayerAlliance(DWORD a0, DWORD a1, DWORD a2) {return JASS_WRAPPER_GetPlayerAlliance(a0, a1, a2);}
inline void RemovePlayer(DWORD a0, DWORD a1) {JASS_WRAPPER_RemovePlayer(a0, a1);}
inline void CachePlayerHeroData(DWORD a0) {JASS_WRAPPER_CachePlayerHeroData(a0);}
inline float GetPlayerHandicap(DWORD a0) {return JASS_WRAPPER_GetPlayerHandicap(a0);}
inline void SetPlayerHandicap(DWORD a0, float a1) {JASS_WRAPPER_SetPlayerHandicap(a0, a1);}
inline float GetPlayerHandicapXP(DWORD a0) {return JASS_WRAPPER_GetPlayerHandicapXP(a0);}
inline void SetPlayerHandicapXP(DWORD a0, float a1) {JASS_WRAPPER_SetPlayerHandicapXP(a0, a1);}
inline void SetPlayerUnitsOwner(DWORD a0, int a1) {JASS_WRAPPER_SetPlayerUnitsOwner(a0, a1);}
inline void CripplePlayer(DWORD a0, DWORD a1, bool a2) {JASS_WRAPPER_CripplePlayer(a0, a1, a2);}
inline DWORD VersionGet(void) {return JASS_WRAPPER_VersionGet();}
inline bool VersionCompatible(DWORD a0) {return JASS_WRAPPER_VersionCompatible(a0);}
inline bool VersionSupported(DWORD a0) {return JASS_WRAPPER_VersionSupported(a0);}
inline void EndGame(bool a0) {JASS_WRAPPER_EndGame(a0);}
inline void ChangeLevel(const char* a0, bool a1) {JASS_WRAPPER_ChangeLevel(a0, a1);}
inline void RestartGame(bool a0) {JASS_WRAPPER_RestartGame(a0);}
inline void ReloadGame(void) {JASS_WRAPPER_ReloadGame();}
inline void LoadGame(const char* a0, bool a1) {JASS_WRAPPER_LoadGame(a0, a1);}
inline void SaveGame(const char* a0) {JASS_WRAPPER_SaveGame(a0);}
inline bool RenameSaveDirectory(const char* a0, const char* a1) {return JASS_WRAPPER_RenameSaveDirectory(a0, a1);}
inline bool RemoveSaveDirectory(const char* a0) {return JASS_WRAPPER_RemoveSaveDirectory(a0);}
inline bool CopySaveGame(const char* a0, const char* a1) {return JASS_WRAPPER_CopySaveGame(a0, a1);}
inline bool SaveGameExists(const char* a0) {return JASS_WRAPPER_SaveGameExists(a0);}
inline void SetFloatGameState(DWORD a0, float a1) {JASS_WRAPPER_SetFloatGameState(a0, a1);}
inline float GetFloatGameState(DWORD a0) {return JASS_WRAPPER_GetFloatGameState(a0);}
inline void SetIntegerGameState(DWORD a0, int a1) {JASS_WRAPPER_SetIntegerGameState(a0, a1);}
inline int GetIntegerGameState(DWORD a0) {return JASS_WRAPPER_GetIntegerGameState(a0);}
inline void SyncSelections(void) {JASS_WRAPPER_SyncSelections();}
inline DWORD DialogCreate(void) {return JASS_WRAPPER_DialogCreate();}
inline void DialogDestroy(DWORD a0) {JASS_WRAPPER_DialogDestroy(a0);}
inline void DialogSetAsync(DWORD a0) {JASS_WRAPPER_DialogSetAsync(a0);}
inline void DialogClear(DWORD a0) {JASS_WRAPPER_DialogClear(a0);}
inline void DialogSetMessage(DWORD a0, const char* a1) {JASS_WRAPPER_DialogSetMessage(a0, a1);}
inline DWORD DialogAddButton(DWORD a0, const char* a1, int a2) {return JASS_WRAPPER_DialogAddButton(a0, a1, a2);}
inline DWORD DialogAddQuitButton(DWORD a0, bool a1, const char* a2, int a3) {return JASS_WRAPPER_DialogAddQuitButton(a0, a1, a2, a3);}
inline void DialogDisplay(DWORD a0, DWORD a1, bool a2) {JASS_WRAPPER_DialogDisplay(a0, a1, a2);}
inline void SetMissionAvailable(int a0, int a1, bool a2) {JASS_WRAPPER_SetMissionAvailable(a0, a1, a2);}
inline void SetCampaignAvailable(int a0, bool a1) {JASS_WRAPPER_SetCampaignAvailable(a0, a1);}
inline void SetCampaignMenuRace(DWORD a0) {JASS_WRAPPER_SetCampaignMenuRace(a0);}
inline void SetCampaignMenuRaceEx(int a0) {JASS_WRAPPER_SetCampaignMenuRaceEx(a0);}
inline void ForceCampaignSelectScreen(void) {JASS_WRAPPER_ForceCampaignSelectScreen();}
inline void SetOpCinematicAvailable(int a0, bool a1) {JASS_WRAPPER_SetOpCinematicAvailable(a0, a1);}
inline void SetEdCinematicAvailable(int a0, bool a1) {JASS_WRAPPER_SetEdCinematicAvailable(a0, a1);}
inline void SetTutorialCleared(bool a0) {JASS_WRAPPER_SetTutorialCleared(a0);}
inline DWORD GetDefaultDifficulty(void) {return JASS_WRAPPER_GetDefaultDifficulty();}
inline void SetDefaultDifficulty(DWORD a0) {JASS_WRAPPER_SetDefaultDifficulty(a0);}
inline bool ReloadGameCachesFromDisk(void) {return JASS_WRAPPER_ReloadGameCachesFromDisk();}
inline void SetCustomCampaignButtonVisible(int a0, bool a1) {JASS_WRAPPER_SetCustomCampaignButtonVisible(a0, a1);}
inline bool GetCustomCampaignButtonVisible(int a0) {return JASS_WRAPPER_GetCustomCampaignButtonVisible(a0);}
inline void DoNotSaveReplay(void) {JASS_WRAPPER_DoNotSaveReplay();}
inline DWORD InitGameCache(const char* a0) {return JASS_WRAPPER_InitGameCache(a0);}
inline bool SaveGameCache(DWORD a0) {return JASS_WRAPPER_SaveGameCache(a0);}
inline void StoreInteger(DWORD a0, const char* a1, const char* a2, int a3) {JASS_WRAPPER_StoreInteger(a0, a1, a2, a3);}
inline void StoreReal(DWORD a0, const char* a1, const char* a2, float a3) {JASS_WRAPPER_StoreReal(a0, a1, a2, a3);}
inline void StoreBoolean(DWORD a0, const char* a1, const char* a2, bool a3) {JASS_WRAPPER_StoreBoolean(a0, a1, a2, a3);}
inline bool StoreUnit(DWORD a0, const char* a1, const char* a2, DWORD a3) {return JASS_WRAPPER_StoreUnit(a0, a1, a2, a3);}
inline bool StoreString(DWORD a0, const char* a1, const char* a2, const char* a3) {return JASS_WRAPPER_StoreString(a0, a1, a2, a3);}
inline void SaveInteger(DWORD a0, int a1, int a2, int a3) {JASS_WRAPPER_SaveInteger(a0, a1, a2, a3);}
inline void SaveReal(DWORD a0, int a1, int a2, float a3) {JASS_WRAPPER_SaveReal(a0, a1, a2, a3);}
inline void SaveBoolean(DWORD a0, int a1, int a2, bool a3) {JASS_WRAPPER_SaveBoolean(a0, a1, a2, a3);}
inline bool SaveStr(DWORD a0, int a1, int a2, const char* a3) {return JASS_WRAPPER_SaveStr(a0, a1, a2, a3);}
inline bool SavePlayerHandle(DWORD a0, int a1, int a2, DWORD a3) {return JASS_WRAPPER_SavePlayerHandle(a0, a1, a2, a3);}
inline bool SaveWidgetHandle(DWORD a0, int a1, int a2, DWORD a3) {return JASS_WRAPPER_SaveWidgetHandle(a0, a1, a2, a3);}
inline bool SaveDestructableHandle(DWORD a0, int a1, int a2, DWORD a3) {return JASS_WRAPPER_SaveDestructableHandle(a0, a1, a2, a3);}
inline bool SaveItemHandle(DWORD a0, int a1, int a2, DWORD a3) {return JASS_WRAPPER_SaveItemHandle(a0, a1, a2, a3);}
inline bool SaveUnitHandle(DWORD a0, int a1, int a2, DWORD a3) {return JASS_WRAPPER_SaveUnitHandle(a0, a1, a2, a3);}
inline bool SaveAbilityHandle(DWORD a0, int a1, int a2, DWORD a3) {return JASS_WRAPPER_SaveAbilityHandle(a0, a1, a2, a3);}
inline bool SaveTimerHandle(DWORD a0, int a1, int a2, DWORD a3) {return JASS_WRAPPER_SaveTimerHandle(a0, a1, a2, a3);}
inline bool SaveRegionHandle(DWORD a0, int a1, int a2, DWORD a3) {return JASS_WRAPPER_SaveRegionHandle(a0, a1, a2, a3);}
inline bool SaveTriggerHandle(DWORD a0, int a1, int a2, DWORD a3) {return JASS_WRAPPER_SaveTriggerHandle(a0, a1, a2, a3);}
inline bool SaveTriggerConditionHandle(DWORD a0, int a1, int a2, DWORD a3) {return JASS_WRAPPER_SaveTriggerConditionHandle(a0, a1, a2, a3);}
inline bool SaveTriggerActionHandle(DWORD a0, int a1, int a2, DWORD a3) {return JASS_WRAPPER_SaveTriggerActionHandle(a0, a1, a2, a3);}
inline bool SaveTriggerEventHandle(DWORD a0, int a1, int a2, DWORD a3) {return JASS_WRAPPER_SaveTriggerEventHandle(a0, a1, a2, a3);}
inline bool SaveForceHandle(DWORD a0, int a1, int a2, DWORD a3) {return JASS_WRAPPER_SaveForceHandle(a0, a1, a2, a3);}
inline bool SaveGroupHandle(DWORD a0, int a1, int a2, DWORD a3) {return JASS_WRAPPER_SaveGroupHandle(a0, a1, a2, a3);}
inline bool SaveLocationHandle(DWORD a0, int a1, int a2, DWORD a3) {return JASS_WRAPPER_SaveLocationHandle(a0, a1, a2, a3);}
inline bool SaveRectHandle(DWORD a0, int a1, int a2, DWORD a3) {return JASS_WRAPPER_SaveRectHandle(a0, a1, a2, a3);}
inline bool SaveBooleanExprHandle(DWORD a0, int a1, int a2, DWORD a3) {return JASS_WRAPPER_SaveBooleanExprHandle(a0, a1, a2, a3);}
inline bool SaveSoundHandle(DWORD a0, int a1, int a2, DWORD a3) {return JASS_WRAPPER_SaveSoundHandle(a0, a1, a2, a3);}
inline bool SaveEffectHandle(DWORD a0, int a1, int a2, DWORD a3) {return JASS_WRAPPER_SaveEffectHandle(a0, a1, a2, a3);}
inline bool SaveUnitPoolHandle(DWORD a0, int a1, int a2, DWORD a3) {return JASS_WRAPPER_SaveUnitPoolHandle(a0, a1, a2, a3);}
inline bool SaveItemPoolHandle(DWORD a0, int a1, int a2, DWORD a3) {return JASS_WRAPPER_SaveItemPoolHandle(a0, a1, a2, a3);}
inline bool SaveQuestHandle(DWORD a0, int a1, int a2, DWORD a3) {return JASS_WRAPPER_SaveQuestHandle(a0, a1, a2, a3);}
inline bool SaveQuestItemHandle(DWORD a0, int a1, int a2, DWORD a3) {return JASS_WRAPPER_SaveQuestItemHandle(a0, a1, a2, a3);}
inline bool SaveDefeatConditionHandle(DWORD a0, int a1, int a2, DWORD a3) {return JASS_WRAPPER_SaveDefeatConditionHandle(a0, a1, a2, a3);}
inline bool SaveTimerDialogHandle(DWORD a0, int a1, int a2, DWORD a3) {return JASS_WRAPPER_SaveTimerDialogHandle(a0, a1, a2, a3);}
inline bool SaveLeaderboardHandle(DWORD a0, int a1, int a2, DWORD a3) {return JASS_WRAPPER_SaveLeaderboardHandle(a0, a1, a2, a3);}
inline bool SaveMultiboardHandle(DWORD a0, int a1, int a2, DWORD a3) {return JASS_WRAPPER_SaveMultiboardHandle(a0, a1, a2, a3);}
inline bool SaveMultiboardItemHandle(DWORD a0, int a1, int a2, DWORD a3) {return JASS_WRAPPER_SaveMultiboardItemHandle(a0, a1, a2, a3);}
inline bool SaveTrackableHandle(DWORD a0, int a1, int a2, DWORD a3) {return JASS_WRAPPER_SaveTrackableHandle(a0, a1, a2, a3);}
inline bool SaveDialogHandle(DWORD a0, int a1, int a2, DWORD a3) {return JASS_WRAPPER_SaveDialogHandle(a0, a1, a2, a3);}
inline bool SaveButtonHandle(DWORD a0, int a1, int a2, DWORD a3) {return JASS_WRAPPER_SaveButtonHandle(a0, a1, a2, a3);}
inline bool SaveTextTagHandle(DWORD a0, int a1, int a2, DWORD a3) {return JASS_WRAPPER_SaveTextTagHandle(a0, a1, a2, a3);}
inline bool SaveLightningHandle(DWORD a0, int a1, int a2, DWORD a3) {return JASS_WRAPPER_SaveLightningHandle(a0, a1, a2, a3);}
inline bool SaveImageHandle(DWORD a0, int a1, int a2, DWORD a3) {return JASS_WRAPPER_SaveImageHandle(a0, a1, a2, a3);}
inline bool SaveUbersplatHandle(DWORD a0, int a1, int a2, DWORD a3) {return JASS_WRAPPER_SaveUbersplatHandle(a0, a1, a2, a3);}
inline bool SaveFogStateHandle(DWORD a0, int a1, int a2, DWORD a3) {return JASS_WRAPPER_SaveFogStateHandle(a0, a1, a2, a3);}
inline bool SaveFogModifierHandle(DWORD a0, int a1, int a2, DWORD a3) {return JASS_WRAPPER_SaveFogModifierHandle(a0, a1, a2, a3);}
inline bool SaveAgentHandle(DWORD a0, int a1, int a2, DWORD a3) {return JASS_WRAPPER_SaveAgentHandle(a0, a1, a2, a3);}
inline bool SaveHashtableHandle(DWORD a0, int a1, int a2, DWORD a3) {return JASS_WRAPPER_SaveHashtableHandle(a0, a1, a2, a3);}
inline void SyncStoredInteger(DWORD a0, const char* a1, const char* a2) {JASS_WRAPPER_SyncStoredInteger(a0, a1, a2);}
inline void SyncStoredReal(DWORD a0, const char* a1, const char* a2) {JASS_WRAPPER_SyncStoredReal(a0, a1, a2);}
inline void SyncStoredBoolean(DWORD a0, const char* a1, const char* a2) {JASS_WRAPPER_SyncStoredBoolean(a0, a1, a2);}
inline void SyncStoredUnit(DWORD a0, const char* a1, const char* a2) {JASS_WRAPPER_SyncStoredUnit(a0, a1, a2);}
inline void SyncStoredString(DWORD a0, const char* a1, const char* a2) {JASS_WRAPPER_SyncStoredString(a0, a1, a2);}
inline int GetStoredInteger(DWORD a0, const char* a1, const char* a2) {return JASS_WRAPPER_GetStoredInteger(a0, a1, a2);}
inline float GetStoredReal(DWORD a0, const char* a1, const char* a2) {return JASS_WRAPPER_GetStoredReal(a0, a1, a2);}
inline bool GetStoredBoolean(DWORD a0, const char* a1, const char* a2) {return JASS_WRAPPER_GetStoredBoolean(a0, a1, a2);}
inline DWORD RestoreUnit(DWORD a0, const char* a1, const char* a2, DWORD a3, float a4, float a5, float a6) {return JASS_WRAPPER_RestoreUnit(a0, a1, a2, a3, a4, a5, a6);}
inline const char* GetStoredString(DWORD a0, const char* a1, const char* a2) {return JASS_WRAPPER_GetStoredString(a0, a1, a2);}
inline bool HaveStoredInteger(DWORD a0, const char* a1, const char* a2) {return JASS_WRAPPER_HaveStoredInteger(a0, a1, a2);}
inline bool HaveStoredReal(DWORD a0, const char* a1, const char* a2) {return JASS_WRAPPER_HaveStoredReal(a0, a1, a2);}
inline bool HaveStoredBoolean(DWORD a0, const char* a1, const char* a2) {return JASS_WRAPPER_HaveStoredBoolean(a0, a1, a2);}
inline bool HaveStoredUnit(DWORD a0, const char* a1, const char* a2) {return JASS_WRAPPER_HaveStoredUnit(a0, a1, a2);}
inline bool HaveStoredString(DWORD a0, const char* a1, const char* a2) {return JASS_WRAPPER_HaveStoredString(a0, a1, a2);}
inline void FlushGameCache(DWORD a0) {JASS_WRAPPER_FlushGameCache(a0);}
inline void FlushStoredMission(DWORD a0, const char* a1) {JASS_WRAPPER_FlushStoredMission(a0, a1);}
inline void FlushStoredInteger(DWORD a0, const char* a1, const char* a2) {JASS_WRAPPER_FlushStoredInteger(a0, a1, a2);}
inline void FlushStoredReal(DWORD a0, const char* a1, const char* a2) {JASS_WRAPPER_FlushStoredReal(a0, a1, a2);}
inline void FlushStoredBoolean(DWORD a0, const char* a1, const char* a2) {JASS_WRAPPER_FlushStoredBoolean(a0, a1, a2);}
inline void FlushStoredUnit(DWORD a0, const char* a1, const char* a2) {JASS_WRAPPER_FlushStoredUnit(a0, a1, a2);}
inline void FlushStoredString(DWORD a0, const char* a1, const char* a2) {JASS_WRAPPER_FlushStoredString(a0, a1, a2);}
inline DWORD InitHashtable(void) {return JASS_WRAPPER_InitHashtable();}
inline int LoadInteger(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadInteger(a0, a1, a2);}
inline float LoadReal(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadReal(a0, a1, a2);}
inline bool LoadBoolean(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadBoolean(a0, a1, a2);}
inline const char* LoadStr(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadStr(a0, a1, a2);}
inline DWORD LoadPlayerHandle(DWORD a0, int a1, int a2) {return JASS_WRAPPER_LoadPlayerHandle(a0, a1, a2);}
inline int GetLearnedSkill(void) {return JASS_WRAPPER_GetLearnedSkill();}
inline int GetLearnedSkillLevel(void) {return JASS_WRAPPER_GetLearnedSkillLevel();}
inline DWORD GetRevivableUnit(void) {return JASS_WRAPPER_GetRevivableUnit();}
inline DWORD GetRevivingUnit(void) {return JASS_WRAPPER_GetRevivingUnit();}
inline DWORD GetSummoningUnit(void) {return JASS_WRAPPER_GetSummoningUnit();}
inline DWORD GetSummonedUnit(void) {return JASS_WRAPPER_GetSummonedUnit();}
inline DWORD GetTransportUnit(void) {return JASS_WRAPPER_GetTransportUnit();}
inline DWORD GetLoadedUnit(void) {return JASS_WRAPPER_GetLoadedUnit();}
inline DWORD GetManipulatingUnit(void) {return JASS_WRAPPER_GetManipulatingUnit();}
inline DWORD GetManipulatedItem(void) {return JASS_WRAPPER_GetManipulatedItem();}
inline DWORD TriggerRegisterPlayerAllianceChange(DWORD a0, DWORD a1, DWORD a2) {return JASS_WRAPPER_TriggerRegisterPlayerAllianceChange(a0, a1, a2);}
inline DWORD TriggerRegisterPlayerChatEvent(DWORD a0, DWORD a1, const char* a2, bool a3) {return JASS_WRAPPER_TriggerRegisterPlayerChatEvent(a0, a1, a2, a3);}
inline const char* GetEventPlayerChatString(void) {return JASS_WRAPPER_GetEventPlayerChatString();}
inline const char* GetEventPlayerChatStringMatched(void) {return JASS_WRAPPER_GetEventPlayerChatStringMatched();}
inline DWORD TriggerRegisterUnitStateEvent(DWORD a0, DWORD a1, DWORD a2, DWORD a3, float a4) {return JASS_WRAPPER_TriggerRegisterUnitStateEvent(a0, a1, a2, a3, a4);}
inline DWORD GetEventUnitState(void) {return JASS_WRAPPER_GetEventUnitState();}
inline DWORD TriggerRegisterDeathEvent(DWORD a0, DWORD a1) {return JASS_WRAPPER_TriggerRegisterDeathEvent(a0, a1);}
inline DWORD TriggerRegisterUnitEvent(DWORD a0, DWORD a1, DWORD a2) {return JASS_WRAPPER_TriggerRegisterUnitEvent(a0, a1, a2);}
inline float GetEventDamage(void) {return JASS_WRAPPER_GetEventDamage();}
inline DWORD GetEventDamageSource(void) {return JASS_WRAPPER_GetEventDamageSource();}
inline DWORD GetEventDetectingPlayer(void) {return JASS_WRAPPER_GetEventDetectingPlayer();}
inline DWORD GetEventTargetUnit(void) {return JASS_WRAPPER_GetEventTargetUnit();}
inline DWORD TriggerRegisterFilterUnitEvent(DWORD a0, DWORD a1, DWORD a2, DWORD a3) {return JASS_WRAPPER_TriggerRegisterFilterUnitEvent(a0, a1, a2, a3);}
inline DWORD TriggerRegisterUnitInRange(DWORD a0, DWORD a1, float a2, DWORD a3) {return JASS_WRAPPER_TriggerRegisterUnitInRange(a0, a1, a2, a3);}
inline DWORD TriggerRegisterEnterRegion(DWORD a0, DWORD a1, DWORD a2) {return JASS_WRAPPER_TriggerRegisterEnterRegion(a0, a1, a2);}
inline DWORD TriggerRegisterLeaveRegion(DWORD a0, DWORD a1, DWORD a2) {return JASS_WRAPPER_TriggerRegisterLeaveRegion(a0, a1, a2);}
inline DWORD GetTriggeringRegion(void) {return JASS_WRAPPER_GetTriggeringRegion();}
inline DWORD GetEnteringUnit(void) {return JASS_WRAPPER_GetEnteringUnit();}
inline DWORD GetLeavingUnit(void) {return JASS_WRAPPER_GetLeavingUnit();}
inline DWORD TriggerAddCondition(DWORD a0, DWORD a1) {return JASS_WRAPPER_TriggerAddCondition(a0, a1);}
inline void TriggerRemoveCondition(DWORD a0, DWORD a1) {JASS_WRAPPER_TriggerRemoveCondition(a0, a1);}
inline void TriggerClearConditions(DWORD a0) {JASS_WRAPPER_TriggerClearConditions(a0);}
inline DWORD TriggerAddAction(DWORD a0, DWORD a1) {return JASS_WRAPPER_TriggerAddAction(a0, a1);}
inline void TriggerRemoveAction(DWORD a0, DWORD a1) {JASS_WRAPPER_TriggerRemoveAction(a0, a1);}
inline void TriggerClearActions(DWORD a0) {JASS_WRAPPER_TriggerClearActions(a0);}
inline void TriggerSleepAction(float a0) {JASS_WRAPPER_TriggerSleepAction(a0);}
inline void TriggerWaitForSound(DWORD a0, float a1) {JASS_WRAPPER_TriggerWaitForSound(a0, a1);}
inline void TriggerExecute(DWORD a0) {JASS_WRAPPER_TriggerExecute(a0);}
inline void TriggerExecuteWait(DWORD a0) {JASS_WRAPPER_TriggerExecuteWait(a0);}
inline bool TriggerEvaluate(DWORD a0) {return JASS_WRAPPER_TriggerEvaluate(a0);}
inline void TriggerSyncStart(void) {JASS_WRAPPER_TriggerSyncStart();}
inline void TriggerSyncReady(void) {JASS_WRAPPER_TriggerSyncReady();}
inline DWORD GetTriggerWidget(void) {return JASS_WRAPPER_GetTriggerWidget();}
inline DWORD GetTriggerDestructable(void) {return JASS_WRAPPER_GetTriggerDestructable();}
inline DWORD GetTriggerUnit(void) {return JASS_WRAPPER_GetTriggerUnit();}
inline DWORD GetTriggerPlayer(void) {return JASS_WRAPPER_GetTriggerPlayer();}
inline DWORD GetTriggeringTrigger(void) {return JASS_WRAPPER_GetTriggeringTrigger();}
inline DWORD GetTriggerEventId(void) {return JASS_WRAPPER_GetTriggerEventId();}
inline int GetTriggerEvalCount(DWORD a0) {return JASS_WRAPPER_GetTriggerEvalCount(a0);}
inline int GetTriggerExecCount(DWORD a0) {return JASS_WRAPPER_GetTriggerExecCount(a0);}
inline DWORD GetFilterUnit(void) {return JASS_WRAPPER_GetFilterUnit();}
inline DWORD GetEnumUnit(void) {return JASS_WRAPPER_GetEnumUnit();}
inline DWORD GetEnumPlayer(void) {return JASS_WRAPPER_GetEnumPlayer();}
inline DWORD GetFilterPlayer(void) {return JASS_WRAPPER_GetFilterPlayer();}
inline DWORD GetFilterDestructable(void) {return JASS_WRAPPER_GetFilterDestructable();}
inline DWORD GetEnumDestructable(void) {return JASS_WRAPPER_GetEnumDestructable();}
inline DWORD GetFilterItem(void) {return JASS_WRAPPER_GetFilterItem();}
inline DWORD GetEnumItem(void) {return JASS_WRAPPER_GetEnumItem();}
inline DWORD CreateGroup(void) {return JASS_WRAPPER_CreateGroup();}
inline void DestroyGroup(DWORD a0) {JASS_WRAPPER_DestroyGroup(a0);}
inline void GroupAddUnit(DWORD a0, DWORD a1) {JASS_WRAPPER_GroupAddUnit(a0, a1);}
inline void GroupRemoveUnit(DWORD a0, DWORD a1) {JASS_WRAPPER_GroupRemoveUnit(a0, a1);}
inline void GroupClear(DWORD a0) {JASS_WRAPPER_GroupClear(a0);}
inline void GroupEnumUnitsOfType(DWORD a0, const char* a1, DWORD a2) {JASS_WRAPPER_GroupEnumUnitsOfType(a0, a1, a2);}
inline void GroupEnumUnitsOfTypeCounted(DWORD a0, const char* a1, DWORD a2, int a3) {JASS_WRAPPER_GroupEnumUnitsOfTypeCounted(a0, a1, a2, a3);}
inline void GroupEnumUnitsInRect(DWORD a0, DWORD a1, DWORD a2) {JASS_WRAPPER_GroupEnumUnitsInRect(a0, a1, a2);}
inline void GroupEnumUnitsInRectCounted(DWORD a0, DWORD a1, DWORD a2, int a3) {JASS_WRAPPER_GroupEnumUnitsInRectCounted(a0, a1, a2, a3);}
inline void GroupEnumUnitsOfPlayer(DWORD a0, DWORD a1, DWORD a2) {JASS_WRAPPER_GroupEnumUnitsOfPlayer(a0, a1, a2);}
inline void GroupEnumUnitsInRange(DWORD a0, float a1, float a2, float a3, DWORD a4) {JASS_WRAPPER_GroupEnumUnitsInRange(a0, a1, a2, a3, a4);}
inline void GroupEnumUnitsInRangeOfLoc(DWORD a0, DWORD a1, float a2, DWORD a3) {JASS_WRAPPER_GroupEnumUnitsInRangeOfLoc(a0, a1, a2, a3);}
inline void GroupEnumUnitsInRangeCounted(DWORD a0, float a1, float a2, float a3, DWORD a4, int a5) {JASS_WRAPPER_GroupEnumUnitsInRangeCounted(a0, a1, a2, a3, a4, a5);}
inline void GroupEnumUnitsInRangeOfLocCounted(DWORD a0, DWORD a1, float a2, DWORD a3, int a4) {JASS_WRAPPER_GroupEnumUnitsInRangeOfLocCounted(a0, a1, a2, a3, a4);}
inline void GroupEnumUnitsSelected(DWORD a0, DWORD a1, DWORD a2) {JASS_WRAPPER_GroupEnumUnitsSelected(a0, a1, a2);}
inline bool GroupImmediateOrder(DWORD a0, const char* a1) {return JASS_WRAPPER_GroupImmediateOrder(a0, a1);}
inline bool GroupImmediateOrderById(DWORD a0, int a1) {return JASS_WRAPPER_GroupImmediateOrderById(a0, a1);}
inline bool GroupPointOrder(DWORD a0, const char* a1, float a2, float a3) {return JASS_WRAPPER_GroupPointOrder(a0, a1, a2, a3);}
inline bool GroupPointOrderLoc(DWORD a0, const char* a1, DWORD a2) {return JASS_WRAPPER_GroupPointOrderLoc(a0, a1, a2);}
inline bool GroupPointOrderById(DWORD a0, int a1, float a2, float a3) {return JASS_WRAPPER_GroupPointOrderById(a0, a1, a2, a3);}
inline bool GroupPointOrderByIdLoc(DWORD a0, int a1, DWORD a2) {return JASS_WRAPPER_GroupPointOrderByIdLoc(a0, a1, a2);}
inline bool GroupTargetOrder(DWORD a0, const char* a1, DWORD a2) {return JASS_WRAPPER_GroupTargetOrder(a0, a1, a2);}
inline bool GroupTargetOrderById(DWORD a0, int a1, DWORD a2) {return JASS_WRAPPER_GroupTargetOrderById(a0, a1, a2);}
inline void ForGroup(DWORD a0, DWORD a1) {JASS_WRAPPER_ForGroup(a0, a1);}
inline DWORD FirstOfGroup(DWORD a0) {return JASS_WRAPPER_FirstOfGroup(a0);}
inline DWORD CreateForce(void) {return JASS_WRAPPER_CreateForce();}
inline void DestroyForce(DWORD a0) {JASS_WRAPPER_DestroyForce(a0);}
inline void ForceAddPlayer(DWORD a0, DWORD a1) {JASS_WRAPPER_ForceAddPlayer(a0, a1);}
inline void ForceRemovePlayer(DWORD a0, DWORD a1) {JASS_WRAPPER_ForceRemovePlayer(a0, a1);}
inline void ForceClear(DWORD a0) {JASS_WRAPPER_ForceClear(a0);}
inline void ForceEnumPlayers(DWORD a0, DWORD a1) {JASS_WRAPPER_ForceEnumPlayers(a0, a1);}
inline void ForceEnumPlayersCounted(DWORD a0, DWORD a1, int a2) {JASS_WRAPPER_ForceEnumPlayersCounted(a0, a1, a2);}
inline void ForceEnumAllies(DWORD a0, DWORD a1, DWORD a2) {JASS_WRAPPER_ForceEnumAllies(a0, a1, a2);}
inline void ForceEnumEnemies(DWORD a0, DWORD a1, DWORD a2) {JASS_WRAPPER_ForceEnumEnemies(a0, a1, a2);}
inline void ForForce(DWORD a0, DWORD a1) {JASS_WRAPPER_ForForce(a0, a1);}
inline float GetWidgetLife(DWORD a0) {return JASS_WRAPPER_GetWidgetLife(a0);}
inline void SetWidgetLife(DWORD a0, float a1) {JASS_WRAPPER_SetWidgetLife(a0, a1);}
inline float GetWidgetX(DWORD a0) {return JASS_WRAPPER_GetWidgetX(a0);}
inline float GetWidgetY(DWORD a0) {return JASS_WRAPPER_GetWidgetY(a0);}
inline DWORD CreateDestructable(int a0, float a1, float a2, float a3, float a4, int a5) {return JASS_WRAPPER_CreateDestructable(a0, a1, a2, a3, a4, a5);}
inline DWORD CreateDestructableZ(int a0, float a1, float a2, float a3, float a4, float a5, int a6) {return JASS_WRAPPER_CreateDestructableZ(a0, a1, a2, a3, a4, a5, a6);}
inline DWORD CreateDeadDestructable(int a0, float a1, float a2, float a3, float a4, int a5) {return JASS_WRAPPER_CreateDeadDestructable(a0, a1, a2, a3, a4, a5);}
inline DWORD CreateDeadDestructableZ(int a0, float a1, float a2, float a3, float a4, float a5, int a6) {return JASS_WRAPPER_CreateDeadDestructableZ(a0, a1, a2, a3, a4, a5, a6);}
inline void RemoveDestructable(DWORD a0) {JASS_WRAPPER_RemoveDestructable(a0);}
inline void KillDestructable(DWORD a0) {JASS_WRAPPER_KillDestructable(a0);}
inline void SetDestructableInvulnerable(DWORD a0, bool a1) {JASS_WRAPPER_SetDestructableInvulnerable(a0, a1);}
inline bool IsDestructableInvulnerable(DWORD a0) {return JASS_WRAPPER_IsDestructableInvulnerable(a0);}
inline void EnumDestructablesInRect(DWORD a0, DWORD a1, DWORD a2) {JASS_WRAPPER_EnumDestructablesInRect(a0, a1, a2);}
inline int GetDestructableTypeId(DWORD a0) {return JASS_WRAPPER_GetDestructableTypeId(a0);}
inline float GetDestructableX(DWORD a0) {return JASS_WRAPPER_GetDestructableX(a0);}
inline float GetDestructableY(DWORD a0) {return JASS_WRAPPER_GetDestructableY(a0);}
inline void SetDestructableLife(DWORD a0, float a1) {JASS_WRAPPER_SetDestructableLife(a0, a1);}
inline float GetDestructableLife(DWORD a0) {return JASS_WRAPPER_GetDestructableLife(a0);}
inline void SetDestructableMaxLife(DWORD a0, float a1) {JASS_WRAPPER_SetDestructableMaxLife(a0, a1);}
inline float GetDestructableMaxLife(DWORD a0) {return JASS_WRAPPER_GetDestructableMaxLife(a0);}
inline void DestructableRestoreLife(DWORD a0, float a1, bool a2) {JASS_WRAPPER_DestructableRestoreLife(a0, a1, a2);}
inline void QueueDestructableAnimation(DWORD a0, const char* a1) {JASS_WRAPPER_QueueDestructableAnimation(a0, a1);}
inline void SetDestructableAnimation(DWORD a0, const char* a1) {JASS_WRAPPER_SetDestructableAnimation(a0, a1);}
inline void SetDestructableAnimationSpeed(DWORD a0, float a1) {JASS_WRAPPER_SetDestructableAnimationSpeed(a0, a1);}
inline void ShowDestructable(DWORD a0, bool a1) {JASS_WRAPPER_ShowDestructable(a0, a1);}
inline float GetDestructableOccluderHeight(DWORD a0) {return JASS_WRAPPER_GetDestructableOccluderHeight(a0);}
inline void SetDestructableOccluderHeight(DWORD a0, float a1) {JASS_WRAPPER_SetDestructableOccluderHeight(a0, a1);}
inline const char* GetDestructableName(DWORD a0) {return JASS_WRAPPER_GetDestructableName(a0);}
inline DWORD CreateUnit(DWORD a0, int a1, float a2, float a3, float a4) {return JASS_WRAPPER_CreateUnit(a0, a1, a2, a3, a4);}
inline DWORD CreateUnitByName(DWORD a0, const char* a1, float a2, float a3, float a4) {return JASS_WRAPPER_CreateUnitByName(a0, a1, a2, a3, a4);}
inline DWORD CreateUnitAtLoc(DWORD a0, int a1, DWORD a2, float a3) {return JASS_WRAPPER_CreateUnitAtLoc(a0, a1, a2, a3);}
inline DWORD CreateUnitAtLocByName(DWORD a0, const char* a1, DWORD a2, float a3) {return JASS_WRAPPER_CreateUnitAtLocByName(a0, a1, a2, a3);}
inline DWORD CreateCorpse(DWORD a0, int a1, float a2, float a3, float a4) {return JASS_WRAPPER_CreateCorpse(a0, a1, a2, a3, a4);}
inline float GetUnitState(DWORD a0, DWORD a1) {return JASS_WRAPPER_GetUnitState(a0, a1);}
inline int GetUnitFoodUsed(DWORD a0) {return JASS_WRAPPER_GetUnitFoodUsed(a0);}
inline int GetUnitFoodMade(DWORD a0) {return JASS_WRAPPER_GetUnitFoodMade(a0);}
inline int GetFoodMade(int a0) {return JASS_WRAPPER_GetFoodMade(a0);}
inline int GetFoodUsed(int a0) {return JASS_WRAPPER_GetFoodUsed(a0);}
inline void SetUnitUseFood(DWORD a0, bool a1) {JASS_WRAPPER_SetUnitUseFood(a0, a1);}
inline float GetUnitX(DWORD a0) {return JASS_WRAPPER_GetUnitX(a0);}
inline float GetUnitY(DWORD a0) {return JASS_WRAPPER_GetUnitY(a0);}
inline DWORD GetUnitLoc(DWORD a0) {return JASS_WRAPPER_GetUnitLoc(a0);}
inline DWORD GetUnitRallyPoint(DWORD a0) {return JASS_WRAPPER_GetUnitRallyPoint(a0);}
inline DWORD GetUnitRallyUnit(DWORD a0) {return JASS_WRAPPER_GetUnitRallyUnit(a0);}
inline DWORD GetUnitRallyDestructable(DWORD a0) {return JASS_WRAPPER_GetUnitRallyDestructable(a0);}
inline float GetUnitFacing(DWORD a0) {return JASS_WRAPPER_GetUnitFacing(a0);}
inline float GetUnitMoveSpeed(DWORD a0) {return JASS_WRAPPER_GetUnitMoveSpeed(a0);}
inline float GetUnitDefaultMoveSpeed(DWORD a0) {return JASS_WRAPPER_GetUnitDefaultMoveSpeed(a0);}
inline int GetUnitTypeId(DWORD a0) {return JASS_WRAPPER_GetUnitTypeId(a0);}
inline DWORD GetUnitRace(DWORD a0) {return JASS_WRAPPER_GetUnitRace(a0);}
inline const char* GetUnitName(DWORD a0) {return JASS_WRAPPER_GetUnitName(a0);}
inline int GetUnitPointValue(DWORD a0) {return JASS_WRAPPER_GetUnitPointValue(a0);}
inline int GetUnitPointValueByType(int a0) {return JASS_WRAPPER_GetUnitPointValueByType(a0);}
inline void SetUnitX(DWORD a0, float a1) {JASS_WRAPPER_SetUnitX(a0, a1);}
inline void SetUnitY(DWORD a0, float a1) {JASS_WRAPPER_SetUnitY(a0, a1);}
inline void SetUnitPosition(DWORD a0, float a1, float a2) {JASS_WRAPPER_SetUnitPosition(a0, a1, a2);}
inline void SetUnitPositionLoc(DWORD a0, DWORD a1) {JASS_WRAPPER_SetUnitPositionLoc(a0, a1);}
inline void SetUnitFacing(DWORD a0, float a1) {JASS_WRAPPER_SetUnitFacing(a0, a1);}
inline void SetUnitFacingTimed(DWORD a0, float a1, float a2) {JASS_WRAPPER_SetUnitFacingTimed(a0, a1, a2);}
inline void SetUnitFlyHeight(DWORD a0, float a1, float a2) {JASS_WRAPPER_SetUnitFlyHeight(a0, a1, a2);}
inline void SetUnitMoveSpeed(DWORD a0, float a1) {JASS_WRAPPER_SetUnitMoveSpeed(a0, a1);}
inline void SetUnitTurnSpeed(DWORD a0, float a1) {JASS_WRAPPER_SetUnitTurnSpeed(a0, a1);}
inline void SetUnitPropWindow(DWORD a0, float a1) {JASS_WRAPPER_SetUnitPropWindow(a0, a1);}
inline void SetUnitCreepGuard(DWORD a0, bool a1) {JASS_WRAPPER_SetUnitCreepGuard(a0, a1);}
inline float GetUnitAcquireRange(DWORD a0) {return JASS_WRAPPER_GetUnitAcquireRange(a0);}
inline float GetUnitTurnSpeed(DWORD a0) {return JASS_WRAPPER_GetUnitTurnSpeed(a0);}
inline float GetUnitPropWindow(DWORD a0) {return JASS_WRAPPER_GetUnitPropWindow(a0);}
inline float GetUnitFlyHeight(DWORD a0) {return JASS_WRAPPER_GetUnitFlyHeight(a0);}
inline float GetUnitDefaultAcquireRange(DWORD a0) {return JASS_WRAPPER_GetUnitDefaultAcquireRange(a0);}
inline float GetUnitDefaultTurnSpeed(DWORD a0) {return JASS_WRAPPER_GetUnitDefaultTurnSpeed(a0);}
inline float GetUnitDefaultPropWindow(DWORD a0) {return JASS_WRAPPER_GetUnitDefaultPropWindow(a0);}
inline float GetUnitDefaultFlyHeight(DWORD a0) {return JASS_WRAPPER_GetUnitDefaultFlyHeight(a0);}
inline void SetUnitAcquireRange(DWORD a0, float a1) {JASS_WRAPPER_SetUnitAcquireRange(a0, a1);}
inline void SetUnitState(DWORD a0, DWORD a1, float a2) {JASS_WRAPPER_SetUnitState(a0, a1, a2);}
inline void SetUnitOwner(DWORD a0, DWORD a1, bool a2) {JASS_WRAPPER_SetUnitOwner(a0, a1, a2);}
inline void SetUnitRescuable(DWORD a0, DWORD a1, bool a2) {JASS_WRAPPER_SetUnitRescuable(a0, a1, a2);}
inline void SetUnitRescueRange(DWORD a0, float a1) {JASS_WRAPPER_SetUnitRescueRange(a0, a1);}
inline void SetUnitColor(DWORD a0, DWORD a1) {JASS_WRAPPER_SetUnitColor(a0, a1);}
inline void QueueUnitAnimation(DWORD a0, const char* a1) {JASS_WRAPPER_QueueUnitAnimation(a0, a1);}
inline void SetUnitAnimation(DWORD a0, const char* a1) {JASS_WRAPPER_SetUnitAnimation(a0, a1);}
inline void SetUnitAnimationWithRarity(DWORD a0, const char* a1, DWORD a2) {JASS_WRAPPER_SetUnitAnimationWithRarity(a0, a1, a2);}
inline void SetUnitAnimationByIndex(DWORD a0, int a1) {JASS_WRAPPER_SetUnitAnimationByIndex(a0, a1);}
inline void AddUnitAnimationProperties(DWORD a0, const char* a1, bool a2) {JASS_WRAPPER_AddUnitAnimationProperties(a0, a1, a2);}
inline void SetUnitScale(DWORD a0, float a1, float a2, float a3) {JASS_WRAPPER_SetUnitScale(a0, a1, a2, a3);}
inline void SetUnitTimeScale(DWORD a0, float a1) {JASS_WRAPPER_SetUnitTimeScale(a0, a1);}
inline void SetUnitBlendTime(DWORD a0, float a1) {JASS_WRAPPER_SetUnitBlendTime(a0, a1);}
inline void SetUnitVertexColor(DWORD a0, int a1, int a2, int a3, int a4) {JASS_WRAPPER_SetUnitVertexColor(a0, a1, a2, a3, a4);}
inline void SetUnitLookAt(DWORD a0, const char* a1, DWORD a2, float a3, float a4, float a5) {JASS_WRAPPER_SetUnitLookAt(a0, a1, a2, a3, a4, a5);}
inline void SetUnitPathing(DWORD a0, bool a1) {JASS_WRAPPER_SetUnitPathing(a0, a1);}
inline void ResetUnitLookAt(DWORD a0) {JASS_WRAPPER_ResetUnitLookAt(a0);}
inline void SetHeroStr(DWORD a0, int a1, bool a2) {JASS_WRAPPER_SetHeroStr(a0, a1, a2);}
inline void SetHeroAgi(DWORD a0, int a1, bool a2) {JASS_WRAPPER_SetHeroAgi(a0, a1, a2);}
inline void SetHeroInt(DWORD a0, int a1, bool a2) {JASS_WRAPPER_SetHeroInt(a0, a1, a2);}
inline int GetHeroStr(DWORD a0, bool a1) {return JASS_WRAPPER_GetHeroStr(a0, a1);}
inline int GetHeroAgi(DWORD a0, bool a1) {return JASS_WRAPPER_GetHeroAgi(a0, a1);}
inline int GetHeroInt(DWORD a0, bool a1) {return JASS_WRAPPER_GetHeroInt(a0, a1);}
inline int GetHeroSkillPoints(DWORD a0) {return JASS_WRAPPER_GetHeroSkillPoints(a0);}
inline bool UnitStripHeroLevel(DWORD a0, int a1) {return JASS_WRAPPER_UnitStripHeroLevel(a0, a1);}
inline bool UnitModifySkillPoints(DWORD a0, int a1) {return JASS_WRAPPER_UnitModifySkillPoints(a0, a1);}
inline int GetHeroXP(DWORD a0) {return JASS_WRAPPER_GetHeroXP(a0);}
inline void SetHeroXP(DWORD a0, int a1, bool a2) {JASS_WRAPPER_SetHeroXP(a0, a1, a2);}
inline void AddHeroXP(DWORD a0, int a1, bool a2) {JASS_WRAPPER_AddHeroXP(a0, a1, a2);}
inline void SetHeroLevel(DWORD a0, int a1, bool a2) {JASS_WRAPPER_SetHeroLevel(a0, a1, a2);}
inline int GetHeroLevel(DWORD a0) {return JASS_WRAPPER_GetHeroLevel(a0);}
inline int GetUnitLevel(DWORD a0) {return JASS_WRAPPER_GetUnitLevel(a0);}
inline const char* GetHeroProperName(DWORD a0) {return JASS_WRAPPER_GetHeroProperName(a0);}
inline void SuspendHeroXP(DWORD a0, bool a1) {JASS_WRAPPER_SuspendHeroXP(a0, a1);}
inline bool IsSuspendedXP(DWORD a0) {return JASS_WRAPPER_IsSuspendedXP(a0);}
inline void SelectHeroSkill(DWORD a0, int a1) {JASS_WRAPPER_SelectHeroSkill(a0, a1);}
inline int GetUnitAbilityLevel(DWORD a0, int a1) {return JASS_WRAPPER_GetUnitAbilityLevel(a0, a1);}
inline bool ReviveHero(DWORD a0, float a1, float a2, bool a3) {return JASS_WRAPPER_ReviveHero(a0, a1, a2, a3);}
inline bool ReviveHeroLoc(DWORD a0, DWORD a1, bool a2) {return JASS_WRAPPER_ReviveHeroLoc(a0, a1, a2);}
inline void SetUnitExploded(DWORD a0, bool a1) {JASS_WRAPPER_SetUnitExploded(a0, a1);}
inline void SetUnitInvulnerable(DWORD a0, bool a1) {JASS_WRAPPER_SetUnitInvulnerable(a0, a1);}
inline void PauseUnit(DWORD a0, bool a1) {JASS_WRAPPER_PauseUnit(a0, a1);}
inline bool IsUnitPaused(DWORD a0) {return JASS_WRAPPER_IsUnitPaused(a0);}
inline bool UnitAddItem(DWORD a0, DWORD a1) {return JASS_WRAPPER_UnitAddItem(a0, a1);}
inline DWORD UnitAddItemById(DWORD a0, int a1) {return JASS_WRAPPER_UnitAddItemById(a0, a1);}
inline bool UnitAddItemToSlotById(DWORD a0, int a1, int a2) {return JASS_WRAPPER_UnitAddItemToSlotById(a0, a1, a2);}
inline void UnitRemoveItem(DWORD a0, DWORD a1) {JASS_WRAPPER_UnitRemoveItem(a0, a1);}
inline DWORD UnitRemoveItemFromSlot(DWORD a0, int a1) {return JASS_WRAPPER_UnitRemoveItemFromSlot(a0, a1);}
inline bool UnitHasItem(DWORD a0, DWORD a1) {return JASS_WRAPPER_UnitHasItem(a0, a1);}
inline DWORD UnitItemInSlot(DWORD a0, int a1) {return JASS_WRAPPER_UnitItemInSlot(a0, a1);}
inline int UnitInventorySize(DWORD a0) {return JASS_WRAPPER_UnitInventorySize(a0);}
inline bool UnitDropItemPoint(DWORD a0, DWORD a1, float a2, float a3) {return JASS_WRAPPER_UnitDropItemPoint(a0, a1, a2, a3);}
inline bool UnitDropItemSlot(DWORD a0, DWORD a1, int a2) {return JASS_WRAPPER_UnitDropItemSlot(a0, a1, a2);}
inline bool UnitDropItemTarget(DWORD a0, DWORD a1, DWORD a2) {return JASS_WRAPPER_UnitDropItemTarget(a0, a1, a2);}
inline bool UnitUseItem(DWORD a0, DWORD a1) {return JASS_WRAPPER_UnitUseItem(a0, a1);}
inline bool UnitUseItemPoint(DWORD a0, DWORD a1, float a2, float a3) {return JASS_WRAPPER_UnitUseItemPoint(a0, a1, a2, a3);}
inline bool UnitUseItemTarget(DWORD a0, DWORD a1, DWORD a2) {return JASS_WRAPPER_UnitUseItemTarget(a0, a1, a2);}
inline int GetUnitCurrentOrder(DWORD a0) {return JASS_WRAPPER_GetUnitCurrentOrder(a0);}
inline void SetResourceAmount(DWORD a0, int a1) {JASS_WRAPPER_SetResourceAmount(a0, a1);}
inline void AddResourceAmount(DWORD a0, int a1) {JASS_WRAPPER_AddResourceAmount(a0, a1);}
inline int GetResourceAmount(DWORD a0) {return JASS_WRAPPER_GetResourceAmount(a0);}
inline void SelectUnit(DWORD a0, bool a1) {JASS_WRAPPER_SelectUnit(a0, a1);}
inline void ClearSelection(void) {JASS_WRAPPER_ClearSelection();}
inline void UnitAddIndicator(DWORD a0, int a1, int a2, int a3, int a4) {JASS_WRAPPER_UnitAddIndicator(a0, a1, a2, a3, a4);}
inline void AddIndicator(DWORD a0, int a1, int a2, int a3, int a4) {JASS_WRAPPER_AddIndicator(a0, a1, a2, a3, a4);}
inline void KillUnit(DWORD a0) {JASS_WRAPPER_KillUnit(a0);}
inline void RemoveUnit(DWORD a0) {JASS_WRAPPER_RemoveUnit(a0);}
inline void ShowUnit(DWORD a0, bool a1) {JASS_WRAPPER_ShowUnit(a0, a1);}
inline bool IsUnitInForce(DWORD a0, DWORD a1) {return JASS_WRAPPER_IsUnitInForce(a0, a1);}
inline bool IsUnitInGroup(DWORD a0, DWORD a1) {return JASS_WRAPPER_IsUnitInGroup(a0, a1);}
inline bool IsUnitOwnedByPlayer(DWORD a0, DWORD a1) {return JASS_WRAPPER_IsUnitOwnedByPlayer(a0, a1);}
inline bool IsUnitAlly(DWORD a0, DWORD a1) {return JASS_WRAPPER_IsUnitAlly(a0, a1);}
inline bool IsUnitEnemy(DWORD a0, DWORD a1) {return JASS_WRAPPER_IsUnitEnemy(a0, a1);}
inline bool IsUnitVisible(DWORD a0, DWORD a1) {return JASS_WRAPPER_IsUnitVisible(a0, a1);}
inline bool IsUnitDetected(DWORD a0, DWORD a1) {return JASS_WRAPPER_IsUnitDetected(a0, a1);}
inline bool IsUnitInvisible(DWORD a0, DWORD a1) {return JASS_WRAPPER_IsUnitInvisible(a0, a1);}
inline bool IsUnitFogged(DWORD a0, DWORD a1) {return JASS_WRAPPER_IsUnitFogged(a0, a1);}
inline bool IsUnitMasked(DWORD a0, DWORD a1) {return JASS_WRAPPER_IsUnitMasked(a0, a1);}
inline bool IsUnitSelected(DWORD a0, DWORD a1) {return JASS_WRAPPER_IsUnitSelected(a0, a1);}
inline bool IsUnitRace(DWORD a0, DWORD a1) {return JASS_WRAPPER_IsUnitRace(a0, a1);}
inline bool IsUnitType(DWORD a0, DWORD a1) {return JASS_WRAPPER_IsUnitType(a0, a1);}
inline bool IsUnit(DWORD a0, DWORD a1) {return JASS_WRAPPER_IsUnit(a0, a1);}
inline bool IsUnitInRange(DWORD a0, DWORD a1, float a2) {return JASS_WRAPPER_IsUnitInRange(a0, a1, a2);}
inline bool IsUnitInRangeXY(DWORD a0, float a1, float a2, float a3) {return JASS_WRAPPER_IsUnitInRangeXY(a0, a1, a2, a3);}
inline bool IsUnitInRangeLoc(DWORD a0, DWORD a1, float a2) {return JASS_WRAPPER_IsUnitInRangeLoc(a0, a1, a2);}
inline bool IsUnitHidden(DWORD a0) {return JASS_WRAPPER_IsUnitHidden(a0);}
inline bool IsUnitIllusion(DWORD a0) {return JASS_WRAPPER_IsUnitIllusion(a0);}
inline bool IsUnitInTransport(DWORD a0, DWORD a1) {return JASS_WRAPPER_IsUnitInTransport(a0, a1);}
inline bool IsUnitLoaded(DWORD a0) {return JASS_WRAPPER_IsUnitLoaded(a0);}
inline bool IsHeroUnitId(int a0) {return JASS_WRAPPER_IsHeroUnitId(a0);}
inline float Deg2Rad(float a0) {return JASS_WRAPPER_Deg2Rad(a0);}
inline float Rad2Deg(float a0) {return JASS_WRAPPER_Rad2Deg(a0);}
inline float Sin(float a0) {return JASS_WRAPPER_Sin(a0);}
inline float Cos(float a0) {return JASS_WRAPPER_Cos(a0);}
inline float Tan(float a0) {return JASS_WRAPPER_Tan(a0);}
inline float Asin(float a0) {return JASS_WRAPPER_Asin(a0);}
inline float Acos(float a0) {return JASS_WRAPPER_Acos(a0);}
inline float Atan(float a0) {return JASS_WRAPPER_Atan(a0);}
inline float Atan2(float a0, float a1) {return JASS_WRAPPER_Atan2(a0, a1);}
inline float SquareRoot(float a0) {return JASS_WRAPPER_SquareRoot(a0);}
inline float Pow(float a0, float a1) {return JASS_WRAPPER_Pow(a0, a1);}
inline float I2R(int a0) {return JASS_WRAPPER_I2R(a0);}
inline int R2I(float a0) {return JASS_WRAPPER_R2I(a0);}
inline const char* I2S(int a0) {return JASS_WRAPPER_I2S(a0);}
inline const char* R2S(float a0) {return JASS_WRAPPER_R2S(a0);}
inline const char* R2SW(float a0, int a1, int a2) {return JASS_WRAPPER_R2SW(a0, a1, a2);}
inline int S2I(const char* a0) {return JASS_WRAPPER_S2I(a0);}
inline float S2R(const char* a0) {return JASS_WRAPPER_S2R(a0);}
inline int GetHandleId(DWORD a0) {return JASS_WRAPPER_GetHandleId(a0);}
inline const char* SubString(const char* a0, int a1, int a2) {return JASS_WRAPPER_SubString(a0, a1, a2);}
inline int StringLength(const char* a0) {return JASS_WRAPPER_StringLength(a0);}
inline const char* StringCase(const char* a0, bool a1) {return JASS_WRAPPER_StringCase(a0, a1);}
inline int StringHash(const char* a0) {return JASS_WRAPPER_StringHash(a0);}
inline const char* GetLocalizedString(const char* a0) {return JASS_WRAPPER_GetLocalizedString(a0);}
inline int GetLocalizedHotkey(const char* a0) {return JASS_WRAPPER_GetLocalizedHotkey(a0);}
inline DWORD ConvertRace(int a0) {return JASS_WRAPPER_ConvertRace(a0);}
inline DWORD ConvertAllianceType(int a0) {return JASS_WRAPPER_ConvertAllianceType(a0);}
inline DWORD ConvertRacePref(int a0) {return JASS_WRAPPER_ConvertRacePref(a0);}
inline DWORD ConvertIGameState(int a0) {return JASS_WRAPPER_ConvertIGameState(a0);}
inline DWORD ConvertFGameState(int a0) {return JASS_WRAPPER_ConvertFGameState(a0);}
inline DWORD ConvertPlayerState(int a0) {return JASS_WRAPPER_ConvertPlayerState(a0);}
inline DWORD ConvertPlayerScore(int a0) {return JASS_WRAPPER_ConvertPlayerScore(a0);}
inline DWORD ConvertStartLocPrio(int a0) {return JASS_WRAPPER_ConvertStartLocPrio(a0);}
inline DWORD ConvertPlayerGameResult(int a0) {return JASS_WRAPPER_ConvertPlayerGameResult(a0);}
inline DWORD ConvertUnitState(int a0) {return JASS_WRAPPER_ConvertUnitState(a0);}
inline DWORD ConvertAIDifficulty(int a0) {return JASS_WRAPPER_ConvertAIDifficulty(a0);}
inline DWORD ConvertGameEvent(int a0) {return JASS_WRAPPER_ConvertGameEvent(a0);}
inline DWORD ConvertPlayerEvent(int a0) {return JASS_WRAPPER_ConvertPlayerEvent(a0);}
inline DWORD ConvertPlayerUnitEvent(int a0) {return JASS_WRAPPER_ConvertPlayerUnitEvent(a0);}
inline DWORD ConvertUnitEvent(int a0) {return JASS_WRAPPER_ConvertUnitEvent(a0);}
inline DWORD ConvertWidgetEvent(int a0) {return JASS_WRAPPER_ConvertWidgetEvent(a0);}
inline DWORD ConvertDialogEvent(int a0) {return JASS_WRAPPER_ConvertDialogEvent(a0);}
inline DWORD ConvertLimitOp(int a0) {return JASS_WRAPPER_ConvertLimitOp(a0);}
inline DWORD ConvertUnitType(int a0) {return JASS_WRAPPER_ConvertUnitType(a0);}
inline DWORD ConvertGameSpeed(int a0) {return JASS_WRAPPER_ConvertGameSpeed(a0);}
inline DWORD ConvertPlacement(int a0) {return JASS_WRAPPER_ConvertPlacement(a0);}
inline DWORD ConvertGameDifficulty(int a0) {return JASS_WRAPPER_ConvertGameDifficulty(a0);}
inline DWORD ConvertGameType(int a0) {return JASS_WRAPPER_ConvertGameType(a0);}
inline DWORD ConvertMapFlag(int a0) {return JASS_WRAPPER_ConvertMapFlag(a0);}
inline DWORD ConvertMapVisibility(int a0) {return JASS_WRAPPER_ConvertMapVisibility(a0);}
inline DWORD ConvertMapSetting(int a0) {return JASS_WRAPPER_ConvertMapSetting(a0);}
inline DWORD ConvertMapDensity(int a0) {return JASS_WRAPPER_ConvertMapDensity(a0);}
inline DWORD ConvertMapControl(int a0) {return JASS_WRAPPER_ConvertMapControl(a0);}
inline DWORD ConvertPlayerColor(int a0) {return JASS_WRAPPER_ConvertPlayerColor(a0);}
inline DWORD ConvertPlayerSlotState(int a0) {return JASS_WRAPPER_ConvertPlayerSlotState(a0);}
inline DWORD ConvertVolumeGroup(int a0) {return JASS_WRAPPER_ConvertVolumeGroup(a0);}
inline DWORD ConvertCameraField(int a0) {return JASS_WRAPPER_ConvertCameraField(a0);}
inline DWORD ConvertBlendMode(int a0) {return JASS_WRAPPER_ConvertBlendMode(a0);}
inline DWORD ConvertRarityControl(int a0) {return JASS_WRAPPER_ConvertRarityControl(a0);}
inline DWORD ConvertTexMapFlags(int a0) {return JASS_WRAPPER_ConvertTexMapFlags(a0);}
inline DWORD ConvertFogState(int a0) {return JASS_WRAPPER_ConvertFogState(a0);}
inline DWORD ConvertEffectType(int a0) {return JASS_WRAPPER_ConvertEffectType(a0);}
inline DWORD ConvertVersion(int a0) {return JASS_WRAPPER_ConvertVersion(a0);}
inline DWORD ConvertItemType(int a0) {return JASS_WRAPPER_ConvertItemType(a0);}
inline DWORD ConvertAttackType(int a0) {return JASS_WRAPPER_ConvertAttackType(a0);}
inline DWORD ConvertDamageType(int a0) {return JASS_WRAPPER_ConvertDamageType(a0);}
inline DWORD ConvertWeaponType(int a0) {return JASS_WRAPPER_ConvertWeaponType(a0);}
inline DWORD ConvertSoundType(int a0) {return JASS_WRAPPER_ConvertSoundType(a0);}
inline DWORD ConvertPathingType(int a0) {return JASS_WRAPPER_ConvertPathingType(a0);}
inline void SetMapName(const char* a0) {JASS_WRAPPER_SetMapName(a0);}
inline void SetMapDescription(const char* a0) {JASS_WRAPPER_SetMapDescription(a0);}
inline void SetTeams(int a0) {JASS_WRAPPER_SetTeams(a0);}
inline void SetPlayers(int a0) {JASS_WRAPPER_SetPlayers(a0);}
inline void SetGameTypeSupported(DWORD a0, bool a1) {JASS_WRAPPER_SetGameTypeSupported(a0, a1);}
inline void SetMapFlag(DWORD a0, bool a1) {JASS_WRAPPER_SetMapFlag(a0, a1);}
inline void SetGameSpeed(DWORD a0) {JASS_WRAPPER_SetGameSpeed(a0);}
inline void SetGamePlacement(DWORD a0) {JASS_WRAPPER_SetGamePlacement(a0);}
inline void SetGameDifficulty(DWORD a0) {JASS_WRAPPER_SetGameDifficulty(a0);}
inline void SetResourceDensity(DWORD a0) {JASS_WRAPPER_SetResourceDensity(a0);}
inline void SetCreatureDensity(DWORD a0) {JASS_WRAPPER_SetCreatureDensity(a0);}
inline void DefineStartLocation(int a0, float a1, float a2) {JASS_WRAPPER_DefineStartLocation(a0, a1, a2);}
inline void DefineStartLocationLoc(int a0, DWORD a1) {JASS_WRAPPER_DefineStartLocationLoc(a0, a1);}
inline void SetStartLocPrioCount(int a0, int a1) {JASS_WRAPPER_SetStartLocPrioCount(a0, a1);}
inline void SetStartLocPrio(int a0, int a1, int a2, DWORD a3) {JASS_WRAPPER_SetStartLocPrio(a0, a1, a2, a3);}
inline int GetStartLocPrioSlot(int a0, int a1) {return JASS_WRAPPER_GetStartLocPrioSlot(a0, a1);}
inline DWORD GetStartLocPrio(int a0, int a1) {return JASS_WRAPPER_GetStartLocPrio(a0, a1);}
inline int GetTeams(void) {return JASS_WRAPPER_GetTeams();}
inline int GetPlayers(void) {return JASS_WRAPPER_GetPlayers();}
inline bool IsGameTypeSupported(DWORD a0) {return JASS_WRAPPER_IsGameTypeSupported(a0);}
inline bool IsMapFlagSet(DWORD a0) {return JASS_WRAPPER_IsMapFlagSet(a0);}
inline DWORD GetGameTypeSelected(void) {return JASS_WRAPPER_GetGameTypeSelected();}
inline DWORD GetGamePlacement(void) {return JASS_WRAPPER_GetGamePlacement();}
inline DWORD GetGameSpeed(void) {return JASS_WRAPPER_GetGameSpeed();}
inline DWORD GetGameDifficulty(void) {return JASS_WRAPPER_GetGameDifficulty();}
inline DWORD GetResourceDensity(void) {return JASS_WRAPPER_GetResourceDensity();}
inline DWORD GetCreatureDensity(void) {return JASS_WRAPPER_GetCreatureDensity();}
inline float GetStartLocationX(int a0) {return JASS_WRAPPER_GetStartLocationX(a0);}
inline float GetStartLocationY(int a0) {return JASS_WRAPPER_GetStartLocationY(a0);}
inline DWORD GetStartLocationLoc(int a0) {return JASS_WRAPPER_GetStartLocationLoc(a0);}
inline void SetPlayerTeam(DWORD a0, int a1) {JASS_WRAPPER_SetPlayerTeam(a0, a1);}
inline void SetPlayerStartLocation(DWORD a0, int a1) {JASS_WRAPPER_SetPlayerStartLocation(a0, a1);}
inline void ForcePlayerStartLocation(DWORD a0, int a1) {JASS_WRAPPER_ForcePlayerStartLocation(a0, a1);}
inline void SetPlayerAlliance(DWORD a0, DWORD a1, DWORD a2, bool a3) {JASS_WRAPPER_SetPlayerAlliance(a0, a1, a2, a3);}
inline void SetPlayerTaxRate(DWORD a0, DWORD a1, DWORD a2, int a3) {JASS_WRAPPER_SetPlayerTaxRate(a0, a1, a2, a3);}
inline void SetPlayerRacePreference(DWORD a0, DWORD a1) {JASS_WRAPPER_SetPlayerRacePreference(a0, a1);}
inline void SetPlayerRaceSelectable(DWORD a0, bool a1) {JASS_WRAPPER_SetPlayerRaceSelectable(a0, a1);}
inline void SetPlayerController(DWORD a0, DWORD a1) {JASS_WRAPPER_SetPlayerController(a0, a1);}
inline void SetPlayerColor(DWORD a0, DWORD a1) {JASS_WRAPPER_SetPlayerColor(a0, a1);}
inline void SetPlayerOnScoreScreen(DWORD a0, bool a1) {JASS_WRAPPER_SetPlayerOnScoreScreen(a0, a1);}
inline void SetPlayerName(DWORD a0, const char* a1) {JASS_WRAPPER_SetPlayerName(a0, a1);}
inline int GetPlayerTeam(DWORD a0) {return JASS_WRAPPER_GetPlayerTeam(a0);}
inline const char* GetPlayerName(DWORD a0) {return JASS_WRAPPER_GetPlayerName(a0);}
inline int GetPlayerStartLocation(DWORD a0) {return JASS_WRAPPER_GetPlayerStartLocation(a0);}
inline float GetPlayerStartLocationX(DWORD a0) {return JASS_WRAPPER_GetPlayerStartLocationX(a0);}
inline float GetPlayerStartLocationY(DWORD a0) {return JASS_WRAPPER_GetPlayerStartLocationY(a0);}
inline DWORD GetPlayerColor(DWORD a0) {return JASS_WRAPPER_GetPlayerColor(a0);}
inline bool GetPlayerSelectable(DWORD a0) {return JASS_WRAPPER_GetPlayerSelectable(a0);}
inline DWORD GetPlayerController(DWORD a0) {return JASS_WRAPPER_GetPlayerController(a0);}
inline DWORD GetPlayerSlotState(DWORD a0) {return JASS_WRAPPER_GetPlayerSlotState(a0);}
inline int GetPlayerTaxRate(DWORD a0, DWORD a1, DWORD a2) {return JASS_WRAPPER_GetPlayerTaxRate(a0, a1, a2);}
inline bool IsPlayerRacePrefSet(DWORD a0, DWORD a1) {return JASS_WRAPPER_IsPlayerRacePrefSet(a0, a1);}
inline DWORD Location(float a0, float a1) {return JASS_WRAPPER_Location(a0, a1);}
inline void RemoveLocation(DWORD a0) {JASS_WRAPPER_RemoveLocation(a0);}
inline void MoveLocation(DWORD a0, float a1, float a2) {JASS_WRAPPER_MoveLocation(a0, a1, a2);}
inline float GetLocationX(DWORD a0) {return JASS_WRAPPER_GetLocationX(a0);}
inline float GetLocationY(DWORD a0) {return JASS_WRAPPER_GetLocationY(a0);}
inline float GetLocationZ(DWORD a0) {return JASS_WRAPPER_GetLocationZ(a0);}
inline DWORD CreateTimer(void) {return JASS_WRAPPER_CreateTimer();}
inline void DestroyTimer(DWORD a0) {JASS_WRAPPER_DestroyTimer(a0);}
inline void TimerStart(DWORD a0, float a1, bool a2, DWORD a3) {JASS_WRAPPER_TimerStart(a0, a1, a2, a3);}
inline float TimerGetTimeout(DWORD a0) {return JASS_WRAPPER_TimerGetTimeout(a0);}
inline float TimerGetElapsed(DWORD a0) {return JASS_WRAPPER_TimerGetElapsed(a0);}
inline float TimerGetRemaining(DWORD a0) {return JASS_WRAPPER_TimerGetRemaining(a0);}
inline void PauseTimer(DWORD a0) {JASS_WRAPPER_PauseTimer(a0);}
inline void ResumeTimer(DWORD a0) {JASS_WRAPPER_ResumeTimer(a0);}
inline DWORD GetExpiredTimer(void) {return JASS_WRAPPER_GetExpiredTimer();}
inline DWORD Condition(DWORD a0) {return JASS_WRAPPER_Condition(a0);}
inline void DestroyCondition(DWORD a0) {JASS_WRAPPER_DestroyCondition(a0);}
inline DWORD Filter(DWORD a0) {return JASS_WRAPPER_Filter(a0);}
inline void DestroyFilter(DWORD a0) {JASS_WRAPPER_DestroyFilter(a0);}
inline void DestroyBoolExpr(DWORD a0) {JASS_WRAPPER_DestroyBoolExpr(a0);}
inline DWORD And(DWORD a0, DWORD a1) {return JASS_WRAPPER_And(a0, a1);}
inline DWORD Or(DWORD a0, DWORD a1) {return JASS_WRAPPER_Or(a0, a1);}
inline DWORD Not(DWORD a0) {return JASS_WRAPPER_Not(a0);}
inline DWORD CreateRegion(void) {return JASS_WRAPPER_CreateRegion();}
inline void RemoveRegion(DWORD a0) {JASS_WRAPPER_RemoveRegion(a0);}
inline void RegionAddRect(DWORD a0, DWORD a1) {JASS_WRAPPER_RegionAddRect(a0, a1);}
inline void RegionClearRect(DWORD a0, DWORD a1) {JASS_WRAPPER_RegionClearRect(a0, a1);}
inline void RegionAddCell(DWORD a0, float a1, float a2) {JASS_WRAPPER_RegionAddCell(a0, a1, a2);}
inline void RegionAddCellAtLoc(DWORD a0, DWORD a1) {JASS_WRAPPER_RegionAddCellAtLoc(a0, a1);}
inline void RegionClearCell(DWORD a0, float a1, float a2) {JASS_WRAPPER_RegionClearCell(a0, a1, a2);}
inline void RegionClearCellAtLoc(DWORD a0, DWORD a1) {JASS_WRAPPER_RegionClearCellAtLoc(a0, a1);}
inline bool IsUnitInRegion(DWORD a0, DWORD a1) {return JASS_WRAPPER_IsUnitInRegion(a0, a1);}
inline bool IsPointInRegion(DWORD a0, float a1, float a2) {return JASS_WRAPPER_IsPointInRegion(a0, a1, a2);}
inline bool IsLocationInRegion(DWORD a0, DWORD a1) {return JASS_WRAPPER_IsLocationInRegion(a0, a1);}
inline DWORD Rect(float a0, float a1, float a2, float a3) {return JASS_WRAPPER_Rect(a0, a1, a2, a3);}
inline DWORD RectFromLoc(DWORD a0, DWORD a1) {return JASS_WRAPPER_RectFromLoc(a0, a1);}
inline void RemoveRect(DWORD a0) {JASS_WRAPPER_RemoveRect(a0);}
inline void SetRect(DWORD a0, float a1, float a2, float a3, float a4) {JASS_WRAPPER_SetRect(a0, a1, a2, a3, a4);}
inline void SetRectFromLoc(DWORD a0, DWORD a1, DWORD a2) {JASS_WRAPPER_SetRectFromLoc(a0, a1, a2);}
inline float GetRectCenterX(DWORD a0) {return JASS_WRAPPER_GetRectCenterX(a0);}
inline float GetRectCenterY(DWORD a0) {return JASS_WRAPPER_GetRectCenterY(a0);}
inline void MoveRectTo(DWORD a0, float a1, float a2) {JASS_WRAPPER_MoveRectTo(a0, a1, a2);}
inline void MoveRectToLoc(DWORD a0, DWORD a1) {JASS_WRAPPER_MoveRectToLoc(a0, a1);}
inline float GetRectMinX(DWORD a0) {return JASS_WRAPPER_GetRectMinX(a0);}
inline float GetRectMinY(DWORD a0) {return JASS_WRAPPER_GetRectMinY(a0);}
inline float GetRectMaxX(DWORD a0) {return JASS_WRAPPER_GetRectMaxX(a0);}
inline float GetRectMaxY(DWORD a0) {return JASS_WRAPPER_GetRectMaxY(a0);}
inline DWORD GetWorldBounds(void) {return JASS_WRAPPER_GetWorldBounds();}
inline void SetFogStateRect(DWORD a0, DWORD a1, DWORD a2, bool a3) {JASS_WRAPPER_SetFogStateRect(a0, a1, a2, a3);}
inline void SetFogStateRadius(DWORD a0, DWORD a1, float a2, float a3, float a4, bool a5) {JASS_WRAPPER_SetFogStateRadius(a0, a1, a2, a3, a4, a5);}
inline void SetFogStateRadiusLoc(DWORD a0, DWORD a1, DWORD a2, float a3, bool a4) {JASS_WRAPPER_SetFogStateRadiusLoc(a0, a1, a2, a3, a4);}
inline void FogMaskEnable(bool a0) {JASS_WRAPPER_FogMaskEnable(a0);}
inline bool IsFogMaskEnabled(void) {return JASS_WRAPPER_IsFogMaskEnabled();}
inline void FogEnable(bool a0) {JASS_WRAPPER_FogEnable(a0);}
inline bool IsFogEnabled(void) {return JASS_WRAPPER_IsFogEnabled();}
inline DWORD CreateFogModifierRect(DWORD a0, DWORD a1, DWORD a2, bool a3, bool a4) {return JASS_WRAPPER_CreateFogModifierRect(a0, a1, a2, a3, a4);}
inline DWORD CreateFogModifierRadius(DWORD a0, DWORD a1, float a2, float a3, float a4, bool a5, bool a6) {return JASS_WRAPPER_CreateFogModifierRadius(a0, a1, a2, a3, a4, a5, a6);}
inline DWORD CreateFogModifierRadiusLoc(DWORD a0, DWORD a1, DWORD a2, float a3, bool a4, bool a5) {return JASS_WRAPPER_CreateFogModifierRadiusLoc(a0, a1, a2, a3, a4, a5);}
inline void DestroyFogModifier(DWORD a0) {JASS_WRAPPER_DestroyFogModifier(a0);}
inline void FogModifierStart(DWORD a0) {JASS_WRAPPER_FogModifierStart(a0);}
inline void FogModifierStop(DWORD a0) {JASS_WRAPPER_FogModifierStop(a0);}
inline DWORD CreateTrigger(void) {return JASS_WRAPPER_CreateTrigger();}
inline void DestroyTrigger(DWORD a0) {JASS_WRAPPER_DestroyTrigger(a0);}
inline void ResetTrigger(DWORD a0) {JASS_WRAPPER_ResetTrigger(a0);}
inline void EnableTrigger(DWORD a0) {JASS_WRAPPER_EnableTrigger(a0);}
inline void DisableTrigger(DWORD a0) {JASS_WRAPPER_DisableTrigger(a0);}
inline bool IsTriggerEnabled(DWORD a0) {return JASS_WRAPPER_IsTriggerEnabled(a0);}
inline void TriggerWaitOnSleeps(DWORD a0, bool a1) {JASS_WRAPPER_TriggerWaitOnSleeps(a0, a1);}
inline bool IsTriggerWaitOnSleeps(DWORD a0) {return JASS_WRAPPER_IsTriggerWaitOnSleeps(a0);}
inline DWORD TriggerRegisterVariableEvent(DWORD a0, const char* a1, DWORD a2, float a3) {return JASS_WRAPPER_TriggerRegisterVariableEvent(a0, a1, a2, a3);}
inline DWORD TriggerRegisterTimerEvent(DWORD a0, float a1, bool a2) {return JASS_WRAPPER_TriggerRegisterTimerEvent(a0, a1, a2);}
inline DWORD TriggerRegisterTimerExpireEvent(DWORD a0, DWORD a1) {return JASS_WRAPPER_TriggerRegisterTimerExpireEvent(a0, a1);}
inline DWORD TriggerRegisterGameStateEvent(DWORD a0, DWORD a1, DWORD a2, float a3) {return JASS_WRAPPER_TriggerRegisterGameStateEvent(a0, a1, a2, a3);}
inline DWORD GetEventGameState(void) {return JASS_WRAPPER_GetEventGameState();}
inline DWORD TriggerRegisterDialogEvent(DWORD a0, DWORD a1) {return JASS_WRAPPER_TriggerRegisterDialogEvent(a0, a1);}
inline DWORD TriggerRegisterDialogButtonEvent(DWORD a0, DWORD a1) {return JASS_WRAPPER_TriggerRegisterDialogButtonEvent(a0, a1);}
inline DWORD GetClickedButton(void) {return JASS_WRAPPER_GetClickedButton();}
inline DWORD GetClickedDialog(void) {return JASS_WRAPPER_GetClickedDialog();}
inline float GetTournamentFinishSoonTimeRemaining(void) {return JASS_WRAPPER_GetTournamentFinishSoonTimeRemaining();}
inline int GetTournamentFinishNowRule(void) {return JASS_WRAPPER_GetTournamentFinishNowRule();}
inline DWORD GetTournamentFinishNowPlayer(void) {return JASS_WRAPPER_GetTournamentFinishNowPlayer();}
inline int GetTournamentScore(DWORD a0) {return JASS_WRAPPER_GetTournamentScore(a0);}
inline const char* GetSaveBasicFilename(void) {return JASS_WRAPPER_GetSaveBasicFilename();}
inline DWORD TriggerRegisterGameEvent(DWORD a0, DWORD a1) {return JASS_WRAPPER_TriggerRegisterGameEvent(a0, a1);}
inline DWORD GetWinningPlayer(void) {return JASS_WRAPPER_GetWinningPlayer();}
inline DWORD TriggerRegisterPlayerStateEvent(DWORD a0, DWORD a1, DWORD a2, DWORD a3, float a4) {return JASS_WRAPPER_TriggerRegisterPlayerStateEvent(a0, a1, a2, a3, a4);}
inline DWORD GetEventPlayerState(void) {return JASS_WRAPPER_GetEventPlayerState();}
inline DWORD TriggerRegisterPlayerEvent(DWORD a0, DWORD a1, DWORD a2) {return JASS_WRAPPER_TriggerRegisterPlayerEvent(a0, a1, a2);}
inline DWORD TriggerRegisterPlayerUnitEvent(DWORD a0, DWORD a1, DWORD a2, DWORD a3) {return JASS_WRAPPER_TriggerRegisterPlayerUnitEvent(a0, a1, a2, a3);}
inline DWORD GetAttacker(void) {return JASS_WRAPPER_GetAttacker();}
inline DWORD GetRescuer(void) {return JASS_WRAPPER_GetRescuer();}
inline DWORD GetDyingUnit(void) {return JASS_WRAPPER_GetDyingUnit();}
inline DWORD GetKillingUnit(void) {return JASS_WRAPPER_GetKillingUnit();}
inline DWORD GetDecayingUnit(void) {return JASS_WRAPPER_GetDecayingUnit();}
inline DWORD GetConstructingStructure(void) {return JASS_WRAPPER_GetConstructingStructure();}
inline DWORD GetCancelledStructure(void) {return JASS_WRAPPER_GetCancelledStructure();}
inline DWORD GetConstructedStructure(void) {return JASS_WRAPPER_GetConstructedStructure();}
inline int GetTrainedUnitType(void) {return JASS_WRAPPER_GetTrainedUnitType();}
inline DWORD GetResearchingUnit(void) {return JASS_WRAPPER_GetResearchingUnit();}
inline int GetResearched(void) {return JASS_WRAPPER_GetResearched();}
inline DWORD GetTrainedUnit(void) {return JASS_WRAPPER_GetTrainedUnit();}
inline DWORD GetSellingUnit(void) {return JASS_WRAPPER_GetSellingUnit();}
inline DWORD GetSoldUnit(void) {return JASS_WRAPPER_GetSoldUnit();}
inline DWORD GetBuyingUnit(void) {return JASS_WRAPPER_GetBuyingUnit();}
inline DWORD GetSoldItem(void) {return JASS_WRAPPER_GetSoldItem();}
inline DWORD GetChangingUnit(void) {return JASS_WRAPPER_GetChangingUnit();}
inline DWORD GetChangingUnitPrevOwner(void) {return JASS_WRAPPER_GetChangingUnitPrevOwner();}
inline DWORD GetDetectedUnit(void) {return JASS_WRAPPER_GetDetectedUnit();}
inline DWORD GetOrderedUnit(void) {return JASS_WRAPPER_GetOrderedUnit();}
inline int OrderId(const char* a0) {return JASS_WRAPPER_OrderId(a0);}
inline const char* OrderId2String(int a0) {return JASS_WRAPPER_OrderId2String(a0);}
inline int AbilityId(const char* a0) {return JASS_WRAPPER_AbilityId(a0);}
inline const char* AbilityId2String(int a0) {return JASS_WRAPPER_AbilityId2String(a0);}
inline int UnitId(const char* a0) {return JASS_WRAPPER_UnitId(a0);}
inline const char* UnitId2String(int a0) {return JASS_WRAPPER_UnitId2String(a0);}
inline const char* GetObjectName(int a0) {return JASS_WRAPPER_GetObjectName(a0);}
inline int GetIssuedOrderId(void) {return JASS_WRAPPER_GetIssuedOrderId();}
inline float GetOrderPointX(void) {return JASS_WRAPPER_GetOrderPointX();}
inline float GetOrderPointY(void) {return JASS_WRAPPER_GetOrderPointY();}
inline DWORD GetOrderPointLoc(void) {return JASS_WRAPPER_GetOrderPointLoc();}
inline DWORD GetOrderTarget(void) {return JASS_WRAPPER_GetOrderTarget();}
inline DWORD GetOrderTargetDestructable(void) {return JASS_WRAPPER_GetOrderTargetDestructable();}
inline DWORD GetOrderTargetItem(void) {return JASS_WRAPPER_GetOrderTargetItem();}
inline DWORD GetOrderTargetUnit(void) {return JASS_WRAPPER_GetOrderTargetUnit();}
inline DWORD GetSpellAbilityUnit(void) {return JASS_WRAPPER_GetSpellAbilityUnit();}
inline int GetSpellAbilityId(void) {return JASS_WRAPPER_GetSpellAbilityId();}
inline DWORD GetSpellAbility(void) {return JASS_WRAPPER_GetSpellAbility();}
inline DWORD GetSpellTargetLoc(void) {return JASS_WRAPPER_GetSpellTargetLoc();}
inline float GetSpellTargetX(void) {return JASS_WRAPPER_GetSpellTargetX();}
inline float GetSpellTargetY(void) {return JASS_WRAPPER_GetSpellTargetY();}
inline DWORD GetSpellTargetDestructable(void) {return JASS_WRAPPER_GetSpellTargetDestructable();}
inline DWORD GetSpellTargetItem(void) {return JASS_WRAPPER_GetSpellTargetItem();}
inline DWORD GetSpellTargetUnit(void) {return JASS_WRAPPER_GetSpellTargetUnit();}
inline DWORD GetLevelingUnit(void) {return JASS_WRAPPER_GetLevelingUnit();}
inline DWORD GetLearningUnit(void) {return JASS_WRAPPER_GetLearningUnit();}
