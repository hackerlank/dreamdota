int JASS_SetDefendPlayer(lua_State* L) {if (lua_gettop(L) != 1) return 0;bool a0 = lua_toboolean(L, 1) > 0;JASS_WRAPPER_SetDefendPlayer(a0);return 0;}
int JASS_SetHeroesTakeItems(lua_State* L) {if (lua_gettop(L) != 1) return 0;bool a0 = lua_toboolean(L, 1) > 0;JASS_WRAPPER_SetHeroesTakeItems(a0);return 0;}
int JASS_SetUnitsFlee(lua_State* L) {if (lua_gettop(L) != 1) return 0;bool a0 = lua_toboolean(L, 1) > 0;JASS_WRAPPER_SetUnitsFlee(a0);return 0;}
int JASS_SetGroupsFlee(lua_State* L) {if (lua_gettop(L) != 1) return 0;bool a0 = lua_toboolean(L, 1) > 0;JASS_WRAPPER_SetGroupsFlee(a0);return 0;}
int JASS_SetSlowChopping(lua_State* L) {if (lua_gettop(L) != 1) return 0;bool a0 = lua_toboolean(L, 1) > 0;JASS_WRAPPER_SetSlowChopping(a0);return 0;}
int JASS_SetSmartArtillery(lua_State* L) {if (lua_gettop(L) != 1) return 0;bool a0 = lua_toboolean(L, 1) > 0;JASS_WRAPPER_SetSmartArtillery(a0);return 0;}
int JASS_SetWatchMegaTargets(lua_State* L) {if (lua_gettop(L) != 1) return 0;bool a0 = lua_toboolean(L, 1) > 0;JASS_WRAPPER_SetWatchMegaTargets(a0);return 0;}
int JASS_SetReplacementCount(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);JASS_WRAPPER_SetReplacementCount(a0);return 0;}
int JASS_PurchaseZeppelin(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_PurchaseZeppelin();return 0;}
int JASS_MeleeDifficulty(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushinteger(L, JASS_WRAPPER_MeleeDifficulty());return 1;}
int JASS_DebugBreak(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);JASS_WRAPPER_DebugBreak(a0);return 0;}
int JASS_SetCineFilterTexMapFlags(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_SetCineFilterTexMapFlags(a0);return 0;}
int JASS_SetCineFilterStartUV(lua_State* L) {if (lua_gettop(L) != 4) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);JASS_WRAPPER_SetCineFilterStartUV((float)a0, (float)a1, (float)a2, (float)a3);return 0;}
int JASS_SetCineFilterEndUV(lua_State* L) {if (lua_gettop(L) != 4) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);JASS_WRAPPER_SetCineFilterEndUV((float)a0, (float)a1, (float)a2, (float)a3);return 0;}
int JASS_SetCineFilterStartColor(lua_State* L) {if (lua_gettop(L) != 4) return 0;int a0 = lua_tointeger(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);int a3 = lua_tointeger(L, 4);JASS_WRAPPER_SetCineFilterStartColor(a0, a1, a2, a3);return 0;}
int JASS_SetCineFilterEndColor(lua_State* L) {if (lua_gettop(L) != 4) return 0;int a0 = lua_tointeger(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);int a3 = lua_tointeger(L, 4);JASS_WRAPPER_SetCineFilterEndColor(a0, a1, a2, a3);return 0;}
int JASS_SetCineFilterDuration(lua_State* L) {if (lua_gettop(L) != 1) return 0;lua_Number a0 = lua_tonumber(L, 1);JASS_WRAPPER_SetCineFilterDuration((float)a0);return 0;}
int JASS_DisplayCineFilter(lua_State* L) {if (lua_gettop(L) != 1) return 0;bool a0 = lua_toboolean(L, 1) > 0;JASS_WRAPPER_DisplayCineFilter(a0);return 0;}
int JASS_IsCineFilterDisplayed(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushboolean(L, JASS_WRAPPER_IsCineFilterDisplayed() ? 1 : 0);return 1;}
int JASS_SetCinematicScene(lua_State* L) {if (lua_gettop(L) != 6) return 0;int a0 = lua_tointeger(L, 1);DWORD a1 = LUA_TODWORD(L, 2);const char* a2 = lua_tostring(L, 3);const char* a3 = lua_tostring(L, 4);lua_Number a4 = lua_tonumber(L, 5);lua_Number a5 = lua_tonumber(L, 6);JASS_WRAPPER_SetCinematicScene(a0, a1, a2, a3, (float)a4, (float)a5);return 0;}
int JASS_EndCinematicScene(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_EndCinematicScene();return 0;}
int JASS_ForceCinematicSubtitles(lua_State* L) {if (lua_gettop(L) != 1) return 0;bool a0 = lua_toboolean(L, 1) > 0;JASS_WRAPPER_ForceCinematicSubtitles(a0);return 0;}
int JASS_NewSoundEnvironment(lua_State* L) {if (lua_gettop(L) != 1) return 0;const char* a0 = lua_tostring(L, 1);JASS_WRAPPER_NewSoundEnvironment(a0);return 0;}
int JASS_CreateSound(lua_State* L) {if (lua_gettop(L) != 7) return 0;const char* a0 = lua_tostring(L, 1);bool a1 = lua_toboolean(L, 2) > 0;bool a2 = lua_toboolean(L, 3) > 0;bool a3 = lua_toboolean(L, 4) > 0;int a4 = lua_tointeger(L, 5);int a5 = lua_tointeger(L, 6);const char* a6 = lua_tostring(L, 7);LUA_PUSHDWORD(L, JASS_WRAPPER_CreateSound(a0, a1, a2, a3, a4, a5, a6));return 1;}
int JASS_CreateSoundFilenameWithLabel(lua_State* L) {if (lua_gettop(L) != 7) return 0;const char* a0 = lua_tostring(L, 1);bool a1 = lua_toboolean(L, 2) > 0;bool a2 = lua_toboolean(L, 3) > 0;bool a3 = lua_toboolean(L, 4) > 0;int a4 = lua_tointeger(L, 5);int a5 = lua_tointeger(L, 6);const char* a6 = lua_tostring(L, 7);LUA_PUSHDWORD(L, JASS_WRAPPER_CreateSoundFilenameWithLabel(a0, a1, a2, a3, a4, a5, a6));return 1;}
int JASS_CreateSoundFromLabel(lua_State* L) {if (lua_gettop(L) != 6) return 0;const char* a0 = lua_tostring(L, 1);bool a1 = lua_toboolean(L, 2) > 0;bool a2 = lua_toboolean(L, 3) > 0;bool a3 = lua_toboolean(L, 4) > 0;int a4 = lua_tointeger(L, 5);int a5 = lua_tointeger(L, 6);LUA_PUSHDWORD(L, JASS_WRAPPER_CreateSoundFromLabel(a0, a1, a2, a3, a4, a5));return 1;}
int JASS_CreateMIDISound(lua_State* L) {if (lua_gettop(L) != 3) return 0;const char* a0 = lua_tostring(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_CreateMIDISound(a0, a1, a2));return 1;}
int JASS_SetStackedSound(lua_State* L) {if (lua_gettop(L) != 3) return 0;const char* a0 = lua_tostring(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);JASS_WRAPPER_SetStackedSound(a0, (float)a1, (float)a2);return 0;}
int JASS_ClearStackedSound(lua_State* L) {if (lua_gettop(L) != 3) return 0;const char* a0 = lua_tostring(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);JASS_WRAPPER_ClearStackedSound(a0, (float)a1, (float)a2);return 0;}
int JASS_SetStackedSoundRect(lua_State* L) {if (lua_gettop(L) != 2) return 0;const char* a0 = lua_tostring(L, 1);DWORD a1 = LUA_TODWORD(L, 2);JASS_WRAPPER_SetStackedSoundRect(a0, a1);return 0;}
int JASS_ClearStackedSoundRect(lua_State* L) {if (lua_gettop(L) != 2) return 0;const char* a0 = lua_tostring(L, 1);DWORD a1 = LUA_TODWORD(L, 2);JASS_WRAPPER_ClearStackedSoundRect(a0, a1);return 0;}
int JASS_SetSoundParamsFromLabel(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);JASS_WRAPPER_SetSoundParamsFromLabel(a0, a1);return 0;}
int JASS_SetSoundChannel(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);JASS_WRAPPER_SetSoundChannel(a0, a1);return 0;}
int JASS_SetSoundVolume(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);JASS_WRAPPER_SetSoundVolume(a0, a1);return 0;}
int JASS_SetSoundPitch(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);JASS_WRAPPER_SetSoundPitch(a0, (float)a1);return 0;}
int JASS_SetSoundPlayPosition(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);JASS_WRAPPER_SetSoundPlayPosition(a0, a1);return 0;}
int JASS_SetSoundDistances(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);JASS_WRAPPER_SetSoundDistances(a0, (float)a1, (float)a2);return 0;}
int JASS_SetSoundDistanceCutoff(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);JASS_WRAPPER_SetSoundDistanceCutoff(a0, (float)a1);return 0;}
int JASS_SetSoundConeAngles(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);int a3 = lua_tointeger(L, 4);JASS_WRAPPER_SetSoundConeAngles(a0, (float)a1, (float)a2, a3);return 0;}
int JASS_SetSoundConeOrientation(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);JASS_WRAPPER_SetSoundConeOrientation(a0, (float)a1, (float)a2, (float)a3);return 0;}
int JASS_SetSoundPosition(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);JASS_WRAPPER_SetSoundPosition(a0, (float)a1, (float)a2, (float)a3);return 0;}
int JASS_SetSoundVelocity(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);JASS_WRAPPER_SetSoundVelocity(a0, (float)a1, (float)a2, (float)a3);return 0;}
int JASS_AttachSoundToUnit(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);JASS_WRAPPER_AttachSoundToUnit(a0, a1);return 0;}
int JASS_StartSound(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_StartSound(a0);return 0;}
int JASS_StopSound(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;bool a2 = lua_toboolean(L, 3) > 0;JASS_WRAPPER_StopSound(a0, a1, a2);return 0;}
int JASS_KillSoundWhenDone(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_KillSoundWhenDone(a0);return 0;}
int JASS_SetMapMusic(lua_State* L) {if (lua_gettop(L) != 3) return 0;const char* a0 = lua_tostring(L, 1);bool a1 = lua_toboolean(L, 2) > 0;int a2 = lua_tointeger(L, 3);JASS_WRAPPER_SetMapMusic(a0, a1, a2);return 0;}
int JASS_ClearMapMusic(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_ClearMapMusic();return 0;}
int JASS_PlayMusic(lua_State* L) {if (lua_gettop(L) != 1) return 0;const char* a0 = lua_tostring(L, 1);JASS_WRAPPER_PlayMusic(a0);return 0;}
int JASS_PlayMusicEx(lua_State* L) {if (lua_gettop(L) != 3) return 0;const char* a0 = lua_tostring(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);JASS_WRAPPER_PlayMusicEx(a0, a1, a2);return 0;}
int JASS_StopMusic(lua_State* L) {if (lua_gettop(L) != 1) return 0;bool a0 = lua_toboolean(L, 1) > 0;JASS_WRAPPER_StopMusic(a0);return 0;}
int JASS_ResumeMusic(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_ResumeMusic();return 0;}
int JASS_PlayThematicMusic(lua_State* L) {if (lua_gettop(L) != 1) return 0;const char* a0 = lua_tostring(L, 1);JASS_WRAPPER_PlayThematicMusic(a0);return 0;}
int JASS_PlayThematicMusicEx(lua_State* L) {if (lua_gettop(L) != 2) return 0;const char* a0 = lua_tostring(L, 1);int a1 = lua_tointeger(L, 2);JASS_WRAPPER_PlayThematicMusicEx(a0, a1);return 0;}
int JASS_EndThematicMusic(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_EndThematicMusic();return 0;}
int JASS_SetMusicVolume(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);JASS_WRAPPER_SetMusicVolume(a0);return 0;}
int JASS_SetMusicPlayPosition(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);JASS_WRAPPER_SetMusicPlayPosition(a0);return 0;}
int JASS_SetThematicMusicPlayPosition(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);JASS_WRAPPER_SetThematicMusicPlayPosition(a0);return 0;}
int JASS_SetSoundDuration(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);JASS_WRAPPER_SetSoundDuration(a0, a1);return 0;}
int JASS_GetSoundDuration(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushinteger(L, JASS_WRAPPER_GetSoundDuration(a0));return 1;}
int JASS_GetSoundFileDuration(lua_State* L) {if (lua_gettop(L) != 1) return 0;const char* a0 = lua_tostring(L, 1);lua_pushinteger(L, JASS_WRAPPER_GetSoundFileDuration(a0));return 1;}
int JASS_VolumeGroupSetVolume(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);JASS_WRAPPER_VolumeGroupSetVolume(a0, (float)a1);return 0;}
int JASS_VolumeGroupReset(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_VolumeGroupReset();return 0;}
int JASS_GetSoundIsPlaying(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_GetSoundIsPlaying(a0) ? 1 : 0);return 1;}
int JASS_GetSoundIsLoading(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_GetSoundIsLoading(a0) ? 1 : 0);return 1;}
int JASS_RegisterStackedSound(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);JASS_WRAPPER_RegisterStackedSound(a0, a1, (float)a2, (float)a3);return 0;}
int JASS_UnregisterStackedSound(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);JASS_WRAPPER_UnregisterStackedSound(a0, a1, (float)a2, (float)a3);return 0;}
int JASS_AddWeatherEffect(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);LUA_PUSHDWORD(L, JASS_WRAPPER_AddWeatherEffect(a0, a1));return 1;}
int JASS_RemoveWeatherEffect(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_RemoveWeatherEffect(a0);return 0;}
int JASS_EnableWeatherEffect(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_EnableWeatherEffect(a0, a1);return 0;}
int JASS_TerrainDeformCrater(lua_State* L) {if (lua_gettop(L) != 6) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);int a4 = lua_tointeger(L, 5);bool a5 = lua_toboolean(L, 6) > 0;LUA_PUSHDWORD(L, JASS_WRAPPER_TerrainDeformCrater((float)a0, (float)a1, (float)a2, (float)a3, a4, a5));return 1;}
int JASS_TerrainDeformRipple(lua_State* L) {if (lua_gettop(L) != 10) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);int a4 = lua_tointeger(L, 5);int a5 = lua_tointeger(L, 6);lua_Number a6 = lua_tonumber(L, 7);lua_Number a7 = lua_tonumber(L, 8);lua_Number a8 = lua_tonumber(L, 9);bool a9 = lua_toboolean(L, 10) > 0;LUA_PUSHDWORD(L, JASS_WRAPPER_TerrainDeformRipple((float)a0, (float)a1, (float)a2, (float)a3, a4, a5, (float)a6, (float)a7, (float)a8, a9));return 1;}
int JASS_TerrainDeformWave(lua_State* L) {if (lua_gettop(L) != 10) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);lua_Number a4 = lua_tonumber(L, 5);lua_Number a5 = lua_tonumber(L, 6);lua_Number a6 = lua_tonumber(L, 7);lua_Number a7 = lua_tonumber(L, 8);int a8 = lua_tointeger(L, 9);int a9 = lua_tointeger(L, 10);LUA_PUSHDWORD(L, JASS_WRAPPER_TerrainDeformWave((float)a0, (float)a1, (float)a2, (float)a3, (float)a4, (float)a5, (float)a6, (float)a7, a8, a9));return 1;}
int JASS_TerrainDeformRandom(lua_State* L) {if (lua_gettop(L) != 7) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);lua_Number a4 = lua_tonumber(L, 5);int a5 = lua_tointeger(L, 6);int a6 = lua_tointeger(L, 7);LUA_PUSHDWORD(L, JASS_WRAPPER_TerrainDeformRandom((float)a0, (float)a1, (float)a2, (float)a3, (float)a4, a5, a6));return 1;}
int JASS_TerrainDeformStop(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);JASS_WRAPPER_TerrainDeformStop(a0, a1);return 0;}
int JASS_TerrainDeformStopAll(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_TerrainDeformStopAll();return 0;}
int JASS_DestroyEffect(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_DestroyEffect(a0);return 0;}
int JASS_AddSpecialEffect(lua_State* L) {if (lua_gettop(L) != 3) return 0;const char* a0 = lua_tostring(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_AddSpecialEffect(a0, (float)a1, (float)a2));return 1;}
int JASS_AddSpecialEffectLoc(lua_State* L) {if (lua_gettop(L) != 2) return 0;const char* a0 = lua_tostring(L, 1);DWORD a1 = LUA_TODWORD(L, 2);LUA_PUSHDWORD(L, JASS_WRAPPER_AddSpecialEffectLoc(a0, a1));return 1;}
int JASS_AddSpecialEffectTarget(lua_State* L) {if (lua_gettop(L) != 3) return 0;const char* a0 = lua_tostring(L, 1);DWORD a1 = LUA_TODWORD(L, 2);const char* a2 = lua_tostring(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_AddSpecialEffectTarget(a0, a1, a2));return 1;}
int JASS_AddSpellEffect(lua_State* L) {if (lua_gettop(L) != 4) return 0;const char* a0 = lua_tostring(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);LUA_PUSHDWORD(L, JASS_WRAPPER_AddSpellEffect(a0, a1, (float)a2, (float)a3));return 1;}
int JASS_AddSpellEffectLoc(lua_State* L) {if (lua_gettop(L) != 3) return 0;const char* a0 = lua_tostring(L, 1);DWORD a1 = LUA_TODWORD(L, 2);DWORD a2 = LUA_TODWORD(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_AddSpellEffectLoc(a0, a1, a2));return 1;}
int JASS_AddSpellEffectById(lua_State* L) {if (lua_gettop(L) != 4) return 0;int a0 = lua_tointeger(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);LUA_PUSHDWORD(L, JASS_WRAPPER_AddSpellEffectById(a0, a1, (float)a2, (float)a3));return 1;}
int JASS_AddSpellEffectByIdLoc(lua_State* L) {if (lua_gettop(L) != 3) return 0;int a0 = lua_tointeger(L, 1);DWORD a1 = LUA_TODWORD(L, 2);DWORD a2 = LUA_TODWORD(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_AddSpellEffectByIdLoc(a0, a1, a2));return 1;}
int JASS_AddSpellEffectTarget(lua_State* L) {if (lua_gettop(L) != 4) return 0;const char* a0 = lua_tostring(L, 1);DWORD a1 = LUA_TODWORD(L, 2);DWORD a2 = LUA_TODWORD(L, 3);const char* a3 = lua_tostring(L, 4);LUA_PUSHDWORD(L, JASS_WRAPPER_AddSpellEffectTarget(a0, a1, a2, a3));return 1;}
int JASS_AddSpellEffectTargetById(lua_State* L) {if (lua_gettop(L) != 4) return 0;int a0 = lua_tointeger(L, 1);DWORD a1 = LUA_TODWORD(L, 2);DWORD a2 = LUA_TODWORD(L, 3);const char* a3 = lua_tostring(L, 4);LUA_PUSHDWORD(L, JASS_WRAPPER_AddSpellEffectTargetById(a0, a1, a2, a3));return 1;}
int JASS_AddLightning(lua_State* L) {if (lua_gettop(L) != 6) return 0;const char* a0 = lua_tostring(L, 1);bool a1 = lua_toboolean(L, 2) > 0;lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);lua_Number a4 = lua_tonumber(L, 5);lua_Number a5 = lua_tonumber(L, 6);LUA_PUSHDWORD(L, JASS_WRAPPER_AddLightning(a0, a1, (float)a2, (float)a3, (float)a4, (float)a5));return 1;}
int JASS_AddLightningEx(lua_State* L) {if (lua_gettop(L) != 8) return 0;const char* a0 = lua_tostring(L, 1);bool a1 = lua_toboolean(L, 2) > 0;lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);lua_Number a4 = lua_tonumber(L, 5);lua_Number a5 = lua_tonumber(L, 6);lua_Number a6 = lua_tonumber(L, 7);lua_Number a7 = lua_tonumber(L, 8);LUA_PUSHDWORD(L, JASS_WRAPPER_AddLightningEx(a0, a1, (float)a2, (float)a3, (float)a4, (float)a5, (float)a6, (float)a7));return 1;}
int JASS_DestroyLightning(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_DestroyLightning(a0) ? 1 : 0);return 1;}
int JASS_GetLightningColorA(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetLightningColorA(a0));return 1;}
int JASS_GetLightningColorR(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetLightningColorR(a0));return 1;}
int JASS_GetLightningColorG(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetLightningColorG(a0));return 1;}
int JASS_GetLightningColorB(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetLightningColorB(a0));return 1;}
int JASS_MoveLightning(lua_State* L) {if (lua_gettop(L) != 6) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);lua_Number a4 = lua_tonumber(L, 5);lua_Number a5 = lua_tonumber(L, 6);lua_pushboolean(L, JASS_WRAPPER_MoveLightning(a0, a1, (float)a2, (float)a3, (float)a4, (float)a5) ? 1 : 0);return 1;}
int JASS_MoveLightningEx(lua_State* L) {if (lua_gettop(L) != 8) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);lua_Number a4 = lua_tonumber(L, 5);lua_Number a5 = lua_tonumber(L, 6);lua_Number a6 = lua_tonumber(L, 7);lua_Number a7 = lua_tonumber(L, 8);lua_pushboolean(L, JASS_WRAPPER_MoveLightningEx(a0, a1, (float)a2, (float)a3, (float)a4, (float)a5, (float)a6, (float)a7) ? 1 : 0);return 1;}
int JASS_SetLightningColor(lua_State* L) {if (lua_gettop(L) != 5) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);lua_Number a4 = lua_tonumber(L, 5);lua_pushboolean(L, JASS_WRAPPER_SetLightningColor(a0, (float)a1, (float)a2, (float)a3, (float)a4) ? 1 : 0);return 1;}
int JASS_GetAbilityEffect(lua_State* L) {if (lua_gettop(L) != 3) return 0;const char* a0 = lua_tostring(L, 1);DWORD a1 = LUA_TODWORD(L, 2);int a2 = lua_tointeger(L, 3);lua_pushstring(L, JASS_WRAPPER_GetAbilityEffect(a0, a1, a2));return 1;}
int JASS_GetAbilityEffectById(lua_State* L) {if (lua_gettop(L) != 3) return 0;int a0 = lua_tointeger(L, 1);DWORD a1 = LUA_TODWORD(L, 2);int a2 = lua_tointeger(L, 3);lua_pushstring(L, JASS_WRAPPER_GetAbilityEffectById(a0, a1, a2));return 1;}
int JASS_GetAbilitySound(lua_State* L) {if (lua_gettop(L) != 2) return 0;const char* a0 = lua_tostring(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_pushstring(L, JASS_WRAPPER_GetAbilitySound(a0, a1));return 1;}
int JASS_GetAbilitySoundById(lua_State* L) {if (lua_gettop(L) != 2) return 0;int a0 = lua_tointeger(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_pushstring(L, JASS_WRAPPER_GetAbilitySoundById(a0, a1));return 1;}
int JASS_GetTerrainCliffLevel(lua_State* L) {if (lua_gettop(L) != 2) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_pushinteger(L, JASS_WRAPPER_GetTerrainCliffLevel((float)a0, (float)a1));return 1;}
int JASS_SetWaterBaseColor(lua_State* L) {if (lua_gettop(L) != 4) return 0;int a0 = lua_tointeger(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);int a3 = lua_tointeger(L, 4);JASS_WRAPPER_SetWaterBaseColor(a0, a1, a2, a3);return 0;}
int JASS_SetWaterDeforms(lua_State* L) {if (lua_gettop(L) != 1) return 0;bool a0 = lua_toboolean(L, 1) > 0;JASS_WRAPPER_SetWaterDeforms(a0);return 0;}
int JASS_GetTerrainType(lua_State* L) {if (lua_gettop(L) != 2) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_pushinteger(L, JASS_WRAPPER_GetTerrainType((float)a0, (float)a1));return 1;}
int JASS_GetTerrainVariance(lua_State* L) {if (lua_gettop(L) != 2) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_pushinteger(L, JASS_WRAPPER_GetTerrainVariance((float)a0, (float)a1));return 1;}
int JASS_SetTerrainType(lua_State* L) {if (lua_gettop(L) != 6) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);int a2 = lua_tointeger(L, 3);int a3 = lua_tointeger(L, 4);int a4 = lua_tointeger(L, 5);int a5 = lua_tointeger(L, 6);JASS_WRAPPER_SetTerrainType((float)a0, (float)a1, a2, a3, a4, a5);return 0;}
int JASS_IsTerrainPathable(lua_State* L) {if (lua_gettop(L) != 3) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);DWORD a2 = LUA_TODWORD(L, 3);lua_pushboolean(L, JASS_WRAPPER_IsTerrainPathable((float)a0, (float)a1, a2) ? 1 : 0);return 1;}
int JASS_SetTerrainPathable(lua_State* L) {if (lua_gettop(L) != 4) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);DWORD a2 = LUA_TODWORD(L, 3);bool a3 = lua_toboolean(L, 4) > 0;JASS_WRAPPER_SetTerrainPathable((float)a0, (float)a1, a2, a3);return 0;}
int JASS_CreateImage(lua_State* L) {if (lua_gettop(L) != 11) return 0;const char* a0 = lua_tostring(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);lua_Number a4 = lua_tonumber(L, 5);lua_Number a5 = lua_tonumber(L, 6);lua_Number a6 = lua_tonumber(L, 7);lua_Number a7 = lua_tonumber(L, 8);lua_Number a8 = lua_tonumber(L, 9);lua_Number a9 = lua_tonumber(L, 10);int a10 = lua_tointeger(L, 11);LUA_PUSHDWORD(L, JASS_WRAPPER_CreateImage(a0, (float)a1, (float)a2, (float)a3, (float)a4, (float)a5, (float)a6, (float)a7, (float)a8, (float)a9, a10));return 1;}
int JASS_DestroyImage(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_DestroyImage(a0);return 0;}
int JASS_ShowImage(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_ShowImage(a0, a1);return 0;}
int JASS_SetImageConstantHeight(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;lua_Number a2 = lua_tonumber(L, 3);JASS_WRAPPER_SetImageConstantHeight(a0, a1, (float)a2);return 0;}
int JASS_SetImagePosition(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);JASS_WRAPPER_SetImagePosition(a0, (float)a1, (float)a2, (float)a3);return 0;}
int JASS_SetImageColor(lua_State* L) {if (lua_gettop(L) != 5) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);int a3 = lua_tointeger(L, 4);int a4 = lua_tointeger(L, 5);JASS_WRAPPER_SetImageColor(a0, a1, a2, a3, a4);return 0;}
int JASS_SetImageRender(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_SetImageRender(a0, a1);return 0;}
int JASS_SetImageRenderAlways(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_SetImageRenderAlways(a0, a1);return 0;}
int JASS_SetImageAboveWater(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;bool a2 = lua_toboolean(L, 3) > 0;JASS_WRAPPER_SetImageAboveWater(a0, a1, a2);return 0;}
int JASS_SetImageType(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);JASS_WRAPPER_SetImageType(a0, a1);return 0;}
int JASS_CreateUbersplat(lua_State* L) {if (lua_gettop(L) != 9) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);const char* a2 = lua_tostring(L, 3);int a3 = lua_tointeger(L, 4);int a4 = lua_tointeger(L, 5);int a5 = lua_tointeger(L, 6);int a6 = lua_tointeger(L, 7);bool a7 = lua_toboolean(L, 8) > 0;bool a8 = lua_toboolean(L, 9) > 0;LUA_PUSHDWORD(L, JASS_WRAPPER_CreateUbersplat((float)a0, (float)a1, a2, a3, a4, a5, a6, a7, a8));return 1;}
int JASS_DestroyUbersplat(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_DestroyUbersplat(a0);return 0;}
int JASS_ResetUbersplat(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_ResetUbersplat(a0);return 0;}
int JASS_FinishUbersplat(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_FinishUbersplat(a0);return 0;}
int JASS_ShowUbersplat(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_ShowUbersplat(a0, a1);return 0;}
int JASS_SetUbersplatRender(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_SetUbersplatRender(a0, a1);return 0;}
int JASS_SetUbersplatRenderAlways(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_SetUbersplatRenderAlways(a0, a1);return 0;}
int JASS_SetBlight(lua_State* L) {if (lua_gettop(L) != 5) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);bool a4 = lua_toboolean(L, 5) > 0;JASS_WRAPPER_SetBlight(a0, (float)a1, (float)a2, (float)a3, a4);return 0;}
int JASS_SetBlightLoc(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_Number a2 = lua_tonumber(L, 3);bool a3 = lua_toboolean(L, 4) > 0;JASS_WRAPPER_SetBlightLoc(a0, a1, (float)a2, a3);return 0;}
int JASS_SetBlightRect(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);bool a2 = lua_toboolean(L, 3) > 0;JASS_WRAPPER_SetBlightRect(a0, a1, a2);return 0;}
int JASS_SetBlightPoint(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);bool a3 = lua_toboolean(L, 4) > 0;JASS_WRAPPER_SetBlightPoint(a0, (float)a1, (float)a2, a3);return 0;}
int JASS_CreateBlightedGoldmine(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);LUA_PUSHDWORD(L, JASS_WRAPPER_CreateBlightedGoldmine(a0, (float)a1, (float)a2, (float)a3));return 1;}
int JASS_IsPointBlighted(lua_State* L) {if (lua_gettop(L) != 2) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_pushboolean(L, JASS_WRAPPER_IsPointBlighted((float)a0, (float)a1) ? 1 : 0);return 1;}
int JASS_SetDoodadAnimation(lua_State* L) {if (lua_gettop(L) != 7) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);int a3 = lua_tointeger(L, 4);bool a4 = lua_toboolean(L, 5) > 0;const char* a5 = lua_tostring(L, 6);bool a6 = lua_toboolean(L, 7) > 0;JASS_WRAPPER_SetDoodadAnimation((float)a0, (float)a1, (float)a2, a3, a4, a5, a6);return 0;}
int JASS_SetDoodadAnimationRect(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);const char* a2 = lua_tostring(L, 3);bool a3 = lua_toboolean(L, 4) > 0;JASS_WRAPPER_SetDoodadAnimationRect(a0, a1, a2, a3);return 0;}
int JASS_StartMeleeAI(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);JASS_WRAPPER_StartMeleeAI(a0, a1);return 0;}
int JASS_StartCampaignAI(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);JASS_WRAPPER_StartCampaignAI(a0, a1);return 0;}
int JASS_CommandAI(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);JASS_WRAPPER_CommandAI(a0, a1, a2);return 0;}
int JASS_PauseCompAI(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_PauseCompAI(a0, a1);return 0;}
int JASS_GetAIDifficulty(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_GetAIDifficulty(a0));return 1;}
int JASS_RemoveGuardPosition(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_RemoveGuardPosition(a0);return 0;}
int JASS_RecycleGuardPosition(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_RecycleGuardPosition(a0);return 0;}
int JASS_RemoveAllGuardPositions(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_RemoveAllGuardPositions(a0);return 0;}
int JASS_ExecuteFunc(lua_State* L) {if (lua_gettop(L) != 1) return 0;const char* a0 = lua_tostring(L, 1);JASS_WRAPPER_ExecuteFunc(a0);return 0;}
int JASS_Cheat(lua_State* L) {if (lua_gettop(L) != 1) return 0;const char* a0 = lua_tostring(L, 1);JASS_WRAPPER_Cheat(a0);return 0;}
int JASS_IsNoVictoryCheat(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushboolean(L, JASS_WRAPPER_IsNoVictoryCheat() ? 1 : 0);return 1;}
int JASS_IsNoDefeatCheat(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushboolean(L, JASS_WRAPPER_IsNoDefeatCheat() ? 1 : 0);return 1;}
int JASS_Preload(lua_State* L) {if (lua_gettop(L) != 1) return 0;const char* a0 = lua_tostring(L, 1);JASS_WRAPPER_Preload(a0);return 0;}
int JASS_PreloadEnd(lua_State* L) {if (lua_gettop(L) != 1) return 0;lua_Number a0 = lua_tonumber(L, 1);JASS_WRAPPER_PreloadEnd((float)a0);return 0;}
int JASS_PreloadStart(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_PreloadStart();return 0;}
int JASS_PreloadRefresh(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_PreloadRefresh();return 0;}
int JASS_PreloadEndEx(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_PreloadEndEx();return 0;}
int JASS_PreloadGenStart(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_PreloadGenStart();return 0;}
int JASS_PreloadGenClear(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_PreloadGenClear();return 0;}
int JASS_PreloadGenEnd(lua_State* L) {if (lua_gettop(L) != 1) return 0;const char* a0 = lua_tostring(L, 1);JASS_WRAPPER_PreloadGenEnd(a0);return 0;}
int JASS_Preloader(lua_State* L) {if (lua_gettop(L) != 1) return 0;const char* a0 = lua_tostring(L, 1);JASS_WRAPPER_Preloader(a0);return 0;}
int JASS_DebugS(lua_State* L) {if (lua_gettop(L) != 1) return 0;const char* a0 = lua_tostring(L, 1);JASS_WRAPPER_DebugS(a0);return 0;}
int JASS_DebugFI(lua_State* L) {if (lua_gettop(L) != 2) return 0;const char* a0 = lua_tostring(L, 1);int a1 = lua_tointeger(L, 2);JASS_WRAPPER_DebugFI(a0, a1);return 0;}
int JASS_DebugUnitID(lua_State* L) {if (lua_gettop(L) != 2) return 0;const char* a0 = lua_tostring(L, 1);int a1 = lua_tointeger(L, 2);JASS_WRAPPER_DebugUnitID(a0, a1);return 0;}
int JASS_DisplayText(lua_State* L) {if (lua_gettop(L) != 2) return 0;int a0 = lua_tointeger(L, 1);const char* a1 = lua_tostring(L, 2);JASS_WRAPPER_DisplayText(a0, a1);return 0;}
int JASS_DisplayTextI(lua_State* L) {if (lua_gettop(L) != 3) return 0;int a0 = lua_tointeger(L, 1);const char* a1 = lua_tostring(L, 2);int a2 = lua_tointeger(L, 3);JASS_WRAPPER_DisplayTextI(a0, a1, a2);return 0;}
int JASS_DisplayTextII(lua_State* L) {if (lua_gettop(L) != 4) return 0;int a0 = lua_tointeger(L, 1);const char* a1 = lua_tostring(L, 2);int a2 = lua_tointeger(L, 3);int a3 = lua_tointeger(L, 4);JASS_WRAPPER_DisplayTextII(a0, a1, a2, a3);return 0;}
int JASS_DisplayTextIII(lua_State* L) {if (lua_gettop(L) != 5) return 0;int a0 = lua_tointeger(L, 1);const char* a1 = lua_tostring(L, 2);int a2 = lua_tointeger(L, 3);int a3 = lua_tointeger(L, 4);int a4 = lua_tointeger(L, 5);JASS_WRAPPER_DisplayTextIII(a0, a1, a2, a3, a4);return 0;}
int JASS_SuicideUnit(lua_State* L) {if (lua_gettop(L) != 2) return 0;int a0 = lua_tointeger(L, 1);int a1 = lua_tointeger(L, 2);JASS_WRAPPER_SuicideUnit(a0, a1);return 0;}
int JASS_SuicideUnitEx(lua_State* L) {if (lua_gettop(L) != 3) return 0;int a0 = lua_tointeger(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);JASS_WRAPPER_SuicideUnitEx(a0, a1, a2);return 0;}
int JASS_Sleep(lua_State* L) {if (lua_gettop(L) != 1) return 0;lua_Number a0 = lua_tonumber(L, 1);JASS_WRAPPER_Sleep((float)a0);return 0;}
int JASS_StartThread(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_StartThread(a0);return 0;}
int JASS_GetAiPlayer(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushinteger(L, JASS_WRAPPER_GetAiPlayer());return 1;}
int JASS_DoAiScriptDebug(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushboolean(L, JASS_WRAPPER_DoAiScriptDebug() ? 1 : 0);return 1;}
int JASS_GetHeroId(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushinteger(L, JASS_WRAPPER_GetHeroId());return 1;}
int JASS_GetHeroLevelAI(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushinteger(L, JASS_WRAPPER_GetHeroLevelAI());return 1;}
int JASS_SetHeroLevels(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_SetHeroLevels(a0);return 0;}
int JASS_SetNewHeroes(lua_State* L) {if (lua_gettop(L) != 1) return 0;bool a0 = lua_toboolean(L, 1) > 0;JASS_WRAPPER_SetNewHeroes(a0);return 0;}
int JASS_GetUnitCount(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);lua_pushinteger(L, JASS_WRAPPER_GetUnitCount(a0));return 1;}
int JASS_GetPlayerUnitTypeCount(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);lua_pushinteger(L, JASS_WRAPPER_GetPlayerUnitTypeCount(a0, a1));return 1;}
int JASS_GetTownUnitCount(lua_State* L) {if (lua_gettop(L) != 3) return 0;int a0 = lua_tointeger(L, 1);int a1 = lua_tointeger(L, 2);bool a2 = lua_toboolean(L, 3) > 0;lua_pushinteger(L, JASS_WRAPPER_GetTownUnitCount(a0, a1, a2));return 1;}
int JASS_GetUnitCountDone(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);lua_pushinteger(L, JASS_WRAPPER_GetUnitCountDone(a0));return 1;}
int JASS_GetUpgradeLevel(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);lua_pushinteger(L, JASS_WRAPPER_GetUpgradeLevel(a0));return 1;}
int JASS_GetUnitGoldCost(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);lua_pushinteger(L, JASS_WRAPPER_GetUnitGoldCost(a0));return 1;}
int JASS_GetUnitWoodCost(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);lua_pushinteger(L, JASS_WRAPPER_GetUnitWoodCost(a0));return 1;}
int JASS_GetUnitBuildTime(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);lua_pushinteger(L, JASS_WRAPPER_GetUnitBuildTime(a0));return 1;}
int JASS_GetUpgradeGoldCost(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);lua_pushinteger(L, JASS_WRAPPER_GetUpgradeGoldCost(a0));return 1;}
int JASS_GetUpgradeWoodCost(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);lua_pushinteger(L, JASS_WRAPPER_GetUpgradeWoodCost(a0));return 1;}
int JASS_GetEnemyPower(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushinteger(L, JASS_WRAPPER_GetEnemyPower());return 1;}
int JASS_GetMinesOwned(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushinteger(L, JASS_WRAPPER_GetMinesOwned());return 1;}
int JASS_GetGoldOwned(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushinteger(L, JASS_WRAPPER_GetGoldOwned());return 1;}
int JASS_TownWithMine(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushinteger(L, JASS_WRAPPER_TownWithMine());return 1;}
int JASS_TownHasMine(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);lua_pushboolean(L, JASS_WRAPPER_TownHasMine(a0) ? 1 : 0);return 1;}
int JASS_TownHasHall(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);lua_pushboolean(L, JASS_WRAPPER_TownHasHall(a0) ? 1 : 0);return 1;}
int JASS_GetNextExpansion(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushinteger(L, JASS_WRAPPER_GetNextExpansion());return 1;}
int JASS_GetExpansionPeon(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetExpansionPeon());return 1;}
int JASS_GetEnemyExpansion(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetEnemyExpansion());return 1;}
int JASS_SetExpansion(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);lua_pushboolean(L, JASS_WRAPPER_SetExpansion(a0, a1) ? 1 : 0);return 1;}
int JASS_GetBuilding(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_GetBuilding(a0));return 1;}
int JASS_SetAllianceTarget(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_SetAllianceTarget(a0);return 0;}
int JASS_GetAllianceTarget(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetAllianceTarget());return 1;}
int JASS_SetProduce(lua_State* L) {if (lua_gettop(L) != 3) return 0;int a0 = lua_tointeger(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);lua_pushboolean(L, JASS_WRAPPER_SetProduce(a0, a1, a2) ? 1 : 0);return 1;}
int JASS_MergeUnits(lua_State* L) {if (lua_gettop(L) != 4) return 0;int a0 = lua_tointeger(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);int a3 = lua_tointeger(L, 4);lua_pushboolean(L, JASS_WRAPPER_MergeUnits(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_ConvertUnits(lua_State* L) {if (lua_gettop(L) != 2) return 0;int a0 = lua_tointeger(L, 1);int a1 = lua_tointeger(L, 2);lua_pushboolean(L, JASS_WRAPPER_ConvertUnits(a0, a1) ? 1 : 0);return 1;}
int JASS_SetUpgrade(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);lua_pushboolean(L, JASS_WRAPPER_SetUpgrade(a0) ? 1 : 0);return 1;}
int JASS_Unsummon(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_Unsummon(a0);return 0;}
int JASS_ClearHarvestAI(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_ClearHarvestAI();return 0;}
int JASS_HarvestGold(lua_State* L) {if (lua_gettop(L) != 2) return 0;int a0 = lua_tointeger(L, 1);int a1 = lua_tointeger(L, 2);JASS_WRAPPER_HarvestGold(a0, a1);return 0;}
int JASS_HarvestWood(lua_State* L) {if (lua_gettop(L) != 2) return 0;int a0 = lua_tointeger(L, 1);int a1 = lua_tointeger(L, 2);JASS_WRAPPER_HarvestWood(a0, a1);return 0;}
int JASS_StopGathering(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_StopGathering();return 0;}
int JASS_AddGuardPost(lua_State* L) {if (lua_gettop(L) != 3) return 0;int a0 = lua_tointeger(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);JASS_WRAPPER_AddGuardPost(a0, (float)a1, (float)a2);return 0;}
int JASS_FillGuardPosts(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_FillGuardPosts();return 0;}
int JASS_ReturnGuardPosts(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_ReturnGuardPosts();return 0;}
int JASS_CreateCaptains(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_CreateCaptains();return 0;}
int JASS_SetCaptainHome(lua_State* L) {if (lua_gettop(L) != 3) return 0;int a0 = lua_tointeger(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);JASS_WRAPPER_SetCaptainHome(a0, (float)a1, (float)a2);return 0;}
int JASS_ResetCaptainLocs(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_ResetCaptainLocs();return 0;}
int JASS_ShiftTownSpot(lua_State* L) {if (lua_gettop(L) != 2) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);JASS_WRAPPER_ShiftTownSpot((float)a0, (float)a1);return 0;}
int JASS_SetCaptainChanges(lua_State* L) {if (lua_gettop(L) != 1) return 0;bool a0 = lua_toboolean(L, 1) > 0;JASS_WRAPPER_SetCaptainChanges(a0);return 0;}
int JASS_TeleportCaptain(lua_State* L) {if (lua_gettop(L) != 2) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);JASS_WRAPPER_TeleportCaptain((float)a0, (float)a1);return 0;}
int JASS_ClearCaptainTargets(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_ClearCaptainTargets();return 0;}
int JASS_CaptainVsUnits(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_CaptainVsUnits(a0);return 0;}
int JASS_CaptainVsPlayer(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_CaptainVsPlayer(a0);return 0;}
int JASS_CaptainAttack(lua_State* L) {if (lua_gettop(L) != 2) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);JASS_WRAPPER_CaptainAttack((float)a0, (float)a1);return 0;}
int JASS_GroupTimedLife(lua_State* L) {if (lua_gettop(L) != 1) return 0;bool a0 = lua_toboolean(L, 1) > 0;JASS_WRAPPER_GroupTimedLife(a0);return 0;}
int JASS_CaptainGoHome(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_CaptainGoHome();return 0;}
int JASS_CaptainIsHome(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushboolean(L, JASS_WRAPPER_CaptainIsHome() ? 1 : 0);return 1;}
int JASS_CaptainRetreating(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushboolean(L, JASS_WRAPPER_CaptainRetreating() ? 1 : 0);return 1;}
int JASS_CaptainIsFull(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushboolean(L, JASS_WRAPPER_CaptainIsFull() ? 1 : 0);return 1;}
int JASS_CaptainIsEmpty(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushboolean(L, JASS_WRAPPER_CaptainIsEmpty() ? 1 : 0);return 1;}
int JASS_CaptainGroupSize(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushinteger(L, JASS_WRAPPER_CaptainGroupSize());return 1;}
int JASS_CaptainReadiness(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushinteger(L, JASS_WRAPPER_CaptainReadiness());return 1;}
int JASS_CaptainReadinessHP(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushinteger(L, JASS_WRAPPER_CaptainReadinessHP());return 1;}
int JASS_CaptainReadinessMa(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushinteger(L, JASS_WRAPPER_CaptainReadinessMa());return 1;}
int JASS_CaptainInCombat(lua_State* L) {if (lua_gettop(L) != 1) return 0;bool a0 = lua_toboolean(L, 1) > 0;lua_pushboolean(L, JASS_WRAPPER_CaptainInCombat(a0) ? 1 : 0);return 1;}
int JASS_TownThreatened(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushboolean(L, JASS_WRAPPER_TownThreatened() ? 1 : 0);return 1;}
int JASS_CaptainAtGoal(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushboolean(L, JASS_WRAPPER_CaptainAtGoal() ? 1 : 0);return 1;}
int JASS_CreepsOnMap(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushboolean(L, JASS_WRAPPER_CreepsOnMap() ? 1 : 0);return 1;}
int JASS_RemoveInjuries(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_RemoveInjuries();return 0;}
int JASS_RemoveSiege(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_RemoveSiege();return 0;}
int JASS_IsTowered(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_IsTowered(a0) ? 1 : 0);return 1;}
int JASS_DisablePathing(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_DisablePathing();return 0;}
int JASS_SetAmphibious(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_SetAmphibious();return 0;}
int JASS_InitAssault(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_InitAssault();return 0;}
int JASS_AddAssault(lua_State* L) {if (lua_gettop(L) != 2) return 0;int a0 = lua_tointeger(L, 1);int a1 = lua_tointeger(L, 2);lua_pushboolean(L, JASS_WRAPPER_AddAssault(a0, a1) ? 1 : 0);return 1;}
int JASS_AddDefenders(lua_State* L) {if (lua_gettop(L) != 2) return 0;int a0 = lua_tointeger(L, 1);int a1 = lua_tointeger(L, 2);lua_pushboolean(L, JASS_WRAPPER_AddDefenders(a0, a1) ? 1 : 0);return 1;}
int JASS_GetCreepCamp(lua_State* L) {if (lua_gettop(L) != 3) return 0;int a0 = lua_tointeger(L, 1);int a1 = lua_tointeger(L, 2);bool a2 = lua_toboolean(L, 3) > 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetCreepCamp(a0, a1, a2));return 1;}
int JASS_StartGetEnemyBase(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_StartGetEnemyBase();return 0;}
int JASS_WaitGetEnemyBase(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushboolean(L, JASS_WRAPPER_WaitGetEnemyBase() ? 1 : 0);return 1;}
int JASS_GetMegaTarget(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetMegaTarget());return 1;}
int JASS_GetEnemyBase(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetEnemyBase());return 1;}
int JASS_GetExpansionFoe(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetExpansionFoe());return 1;}
int JASS_GetExpansionX(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushinteger(L, JASS_WRAPPER_GetExpansionX());return 1;}
int JASS_GetExpansionY(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushinteger(L, JASS_WRAPPER_GetExpansionY());return 1;}
int JASS_SetStagePoint(lua_State* L) {if (lua_gettop(L) != 2) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);JASS_WRAPPER_SetStagePoint((float)a0, (float)a1);return 0;}
int JASS_AttackMoveKill(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_AttackMoveKill(a0);return 0;}
int JASS_AttackMoveXY(lua_State* L) {if (lua_gettop(L) != 2) return 0;int a0 = lua_tointeger(L, 1);int a1 = lua_tointeger(L, 2);JASS_WRAPPER_AttackMoveXY(a0, a1);return 0;}
int JASS_LoadZepWave(lua_State* L) {if (lua_gettop(L) != 2) return 0;int a0 = lua_tointeger(L, 1);int a1 = lua_tointeger(L, 2);JASS_WRAPPER_LoadZepWave(a0, a1);return 0;}
int JASS_SuicidePlayer(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;lua_pushboolean(L, JASS_WRAPPER_SuicidePlayer(a0, a1) ? 1 : 0);return 1;}
int JASS_SuicidePlayerUnits(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;lua_pushboolean(L, JASS_WRAPPER_SuicidePlayerUnits(a0, a1) ? 1 : 0);return 1;}
int JASS_UnitAlive(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_UnitAlive(a0) ? 1 : 0);return 1;}
int JASS_UnitInvis(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_UnitInvis(a0) ? 1 : 0);return 1;}
int JASS_IgnoredUnits(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);lua_pushinteger(L, JASS_WRAPPER_IgnoredUnits(a0));return 1;}
int JASS_CommandsWaiting(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushinteger(L, JASS_WRAPPER_CommandsWaiting());return 1;}
int JASS_GetLastCommand(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushinteger(L, JASS_WRAPPER_GetLastCommand());return 1;}
int JASS_GetLastData(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushinteger(L, JASS_WRAPPER_GetLastData());return 1;}
int JASS_PopLastCommand(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_PopLastCommand();return 0;}
int JASS_SetCampaignAI(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_SetCampaignAI();return 0;}
int JASS_SetMeleeAI(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_SetMeleeAI();return 0;}
int JASS_SetTargetHeroes(lua_State* L) {if (lua_gettop(L) != 1) return 0;bool a0 = lua_toboolean(L, 1) > 0;JASS_WRAPPER_SetTargetHeroes(a0);return 0;}
int JASS_SetHeroesFlee(lua_State* L) {if (lua_gettop(L) != 1) return 0;bool a0 = lua_toboolean(L, 1) > 0;JASS_WRAPPER_SetHeroesFlee(a0);return 0;}
int JASS_SetHeroesBuyItems(lua_State* L) {if (lua_gettop(L) != 1) return 0;bool a0 = lua_toboolean(L, 1) > 0;JASS_WRAPPER_SetHeroesBuyItems(a0);return 0;}
int JASS_SetIgnoreInjured(lua_State* L) {if (lua_gettop(L) != 1) return 0;bool a0 = lua_toboolean(L, 1) > 0;JASS_WRAPPER_SetIgnoreInjured(a0);return 0;}
int JASS_SetPeonsRepair(lua_State* L) {if (lua_gettop(L) != 1) return 0;bool a0 = lua_toboolean(L, 1) > 0;JASS_WRAPPER_SetPeonsRepair(a0);return 0;}
int JASS_SetRandomPaths(lua_State* L) {if (lua_gettop(L) != 1) return 0;bool a0 = lua_toboolean(L, 1) > 0;JASS_WRAPPER_SetRandomPaths(a0);return 0;}
int JASS_LoadWidgetHandle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_LoadWidgetHandle(a0, a1, a2));return 1;}
int JASS_LoadDestructableHandle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_LoadDestructableHandle(a0, a1, a2));return 1;}
int JASS_LoadItemHandle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_LoadItemHandle(a0, a1, a2));return 1;}
int JASS_LoadUnitHandle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_LoadUnitHandle(a0, a1, a2));return 1;}
int JASS_LoadAbilityHandle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_LoadAbilityHandle(a0, a1, a2));return 1;}
int JASS_LoadTimerHandle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_LoadTimerHandle(a0, a1, a2));return 1;}
int JASS_LoadRegionHandle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_LoadRegionHandle(a0, a1, a2));return 1;}
int JASS_LoadTriggerHandle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_LoadTriggerHandle(a0, a1, a2));return 1;}
int JASS_LoadTriggerConditionHandle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_LoadTriggerConditionHandle(a0, a1, a2));return 1;}
int JASS_LoadTriggerActionHandle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_LoadTriggerActionHandle(a0, a1, a2));return 1;}
int JASS_LoadTriggerEventHandle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_LoadTriggerEventHandle(a0, a1, a2));return 1;}
int JASS_LoadForceHandle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_LoadForceHandle(a0, a1, a2));return 1;}
int JASS_LoadGroupHandle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_LoadGroupHandle(a0, a1, a2));return 1;}
int JASS_LoadLocationHandle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_LoadLocationHandle(a0, a1, a2));return 1;}
int JASS_LoadRectHandle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_LoadRectHandle(a0, a1, a2));return 1;}
int JASS_LoadBooleanExprHandle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_LoadBooleanExprHandle(a0, a1, a2));return 1;}
int JASS_LoadSoundHandle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_LoadSoundHandle(a0, a1, a2));return 1;}
int JASS_LoadEffectHandle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_LoadEffectHandle(a0, a1, a2));return 1;}
int JASS_LoadUnitPoolHandle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_LoadUnitPoolHandle(a0, a1, a2));return 1;}
int JASS_LoadItemPoolHandle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_LoadItemPoolHandle(a0, a1, a2));return 1;}
int JASS_LoadQuestHandle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_LoadQuestHandle(a0, a1, a2));return 1;}
int JASS_LoadQuestItemHandle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_LoadQuestItemHandle(a0, a1, a2));return 1;}
int JASS_LoadDefeatConditionHandle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_LoadDefeatConditionHandle(a0, a1, a2));return 1;}
int JASS_LoadTimerDialogHandle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_LoadTimerDialogHandle(a0, a1, a2));return 1;}
int JASS_LoadLeaderboardHandle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_LoadLeaderboardHandle(a0, a1, a2));return 1;}
int JASS_LoadMultiboardHandle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_LoadMultiboardHandle(a0, a1, a2));return 1;}
int JASS_LoadMultiboardItemHandle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_LoadMultiboardItemHandle(a0, a1, a2));return 1;}
int JASS_LoadTrackableHandle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_LoadTrackableHandle(a0, a1, a2));return 1;}
int JASS_LoadDialogHandle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_LoadDialogHandle(a0, a1, a2));return 1;}
int JASS_LoadButtonHandle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_LoadButtonHandle(a0, a1, a2));return 1;}
int JASS_LoadTextTagHandle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_LoadTextTagHandle(a0, a1, a2));return 1;}
int JASS_LoadLightningHandle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_LoadLightningHandle(a0, a1, a2));return 1;}
int JASS_LoadImageHandle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_LoadImageHandle(a0, a1, a2));return 1;}
int JASS_LoadUbersplatHandle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_LoadUbersplatHandle(a0, a1, a2));return 1;}
int JASS_LoadFogStateHandle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_LoadFogStateHandle(a0, a1, a2));return 1;}
int JASS_LoadFogModifierHandle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_LoadFogModifierHandle(a0, a1, a2));return 1;}
int JASS_LoadHashtableHandle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_LoadHashtableHandle(a0, a1, a2));return 1;}
int JASS_HaveSavedInteger(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);lua_pushboolean(L, JASS_WRAPPER_HaveSavedInteger(a0, a1, a2) ? 1 : 0);return 1;}
int JASS_HaveSavedReal(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);lua_pushboolean(L, JASS_WRAPPER_HaveSavedReal(a0, a1, a2) ? 1 : 0);return 1;}
int JASS_HaveSavedBoolean(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);lua_pushboolean(L, JASS_WRAPPER_HaveSavedBoolean(a0, a1, a2) ? 1 : 0);return 1;}
int JASS_HaveSavedString(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);lua_pushboolean(L, JASS_WRAPPER_HaveSavedString(a0, a1, a2) ? 1 : 0);return 1;}
int JASS_HaveSavedHandle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);lua_pushboolean(L, JASS_WRAPPER_HaveSavedHandle(a0, a1, a2) ? 1 : 0);return 1;}
int JASS_RemoveSavedInteger(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);JASS_WRAPPER_RemoveSavedInteger(a0, a1, a2);return 0;}
int JASS_RemoveSavedReal(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);JASS_WRAPPER_RemoveSavedReal(a0, a1, a2);return 0;}
int JASS_RemoveSavedBoolean(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);JASS_WRAPPER_RemoveSavedBoolean(a0, a1, a2);return 0;}
int JASS_RemoveSavedString(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);JASS_WRAPPER_RemoveSavedString(a0, a1, a2);return 0;}
int JASS_RemoveSavedHandle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);JASS_WRAPPER_RemoveSavedHandle(a0, a1, a2);return 0;}
int JASS_FlushParentHashtable(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_FlushParentHashtable(a0);return 0;}
int JASS_FlushChildHashtable(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);JASS_WRAPPER_FlushChildHashtable(a0, a1);return 0;}
int JASS_GetRandomInt(lua_State* L) {if (lua_gettop(L) != 2) return 0;int a0 = lua_tointeger(L, 1);int a1 = lua_tointeger(L, 2);lua_pushinteger(L, JASS_WRAPPER_GetRandomInt(a0, a1));return 1;}
int JASS_GetRandomReal(lua_State* L) {if (lua_gettop(L) != 2) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_pushnumber(L, JASS_WRAPPER_GetRandomReal((float)a0, (float)a1));return 1;}
int JASS_CreateUnitPool(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_CreateUnitPool());return 1;}
int JASS_DestroyUnitPool(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_DestroyUnitPool(a0);return 0;}
int JASS_UnitPoolAddUnitType(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);lua_Number a2 = lua_tonumber(L, 3);JASS_WRAPPER_UnitPoolAddUnitType(a0, a1, (float)a2);return 0;}
int JASS_UnitPoolRemoveUnitType(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);JASS_WRAPPER_UnitPoolRemoveUnitType(a0, a1);return 0;}
int JASS_PlaceRandomUnit(lua_State* L) {if (lua_gettop(L) != 5) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);lua_Number a4 = lua_tonumber(L, 5);LUA_PUSHDWORD(L, JASS_WRAPPER_PlaceRandomUnit(a0, a1, (float)a2, (float)a3, (float)a4));return 1;}
int JASS_CreateItemPool(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_CreateItemPool());return 1;}
int JASS_DestroyItemPool(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_DestroyItemPool(a0);return 0;}
int JASS_ItemPoolAddItemType(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);lua_Number a2 = lua_tonumber(L, 3);JASS_WRAPPER_ItemPoolAddItemType(a0, a1, (float)a2);return 0;}
int JASS_ItemPoolRemoveItemType(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);JASS_WRAPPER_ItemPoolRemoveItemType(a0, a1);return 0;}
int JASS_PlaceRandomItem(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_PlaceRandomItem(a0, (float)a1, (float)a2));return 1;}
int JASS_ChooseRandomCreep(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);lua_pushinteger(L, JASS_WRAPPER_ChooseRandomCreep(a0));return 1;}
int JASS_ChooseRandomNPBuilding(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushinteger(L, JASS_WRAPPER_ChooseRandomNPBuilding());return 1;}
int JASS_ChooseRandomItem(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);lua_pushinteger(L, JASS_WRAPPER_ChooseRandomItem(a0));return 1;}
int JASS_ChooseRandomItemEx(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);lua_pushinteger(L, JASS_WRAPPER_ChooseRandomItemEx(a0, a1));return 1;}
int JASS_SetRandomSeed(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);JASS_WRAPPER_SetRandomSeed(a0);return 0;}
int JASS_DisplayTextToPlayer(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);const char* a3 = lua_tostring(L, 4);JASS_WRAPPER_DisplayTextToPlayer(a0, (float)a1, (float)a2, a3);return 0;}
int JASS_DisplayTimedTextToPlayer(lua_State* L) {if (lua_gettop(L) != 5) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);const char* a4 = lua_tostring(L, 5);JASS_WRAPPER_DisplayTimedTextToPlayer(a0, (float)a1, (float)a2, (float)a3, a4);return 0;}
int JASS_DisplayTimedTextFromPlayer(lua_State* L) {if (lua_gettop(L) != 5) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);const char* a4 = lua_tostring(L, 5);JASS_WRAPPER_DisplayTimedTextFromPlayer(a0, (float)a1, (float)a2, (float)a3, a4);return 0;}
int JASS_ClearTextMessages(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_ClearTextMessages();return 0;}
int JASS_EnableUserControl(lua_State* L) {if (lua_gettop(L) != 1) return 0;bool a0 = lua_toboolean(L, 1) > 0;JASS_WRAPPER_EnableUserControl(a0);return 0;}
int JASS_EnableUserUI(lua_State* L) {if (lua_gettop(L) != 1) return 0;bool a0 = lua_toboolean(L, 1) > 0;JASS_WRAPPER_EnableUserUI(a0);return 0;}
int JASS_DisableRestartMission(lua_State* L) {if (lua_gettop(L) != 1) return 0;bool a0 = lua_toboolean(L, 1) > 0;JASS_WRAPPER_DisableRestartMission(a0);return 0;}
int JASS_ForceUIKey(lua_State* L) {if (lua_gettop(L) != 1) return 0;const char* a0 = lua_tostring(L, 1);JASS_WRAPPER_ForceUIKey(a0);return 0;}
int JASS_ForceUICancel(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_ForceUICancel();return 0;}
int JASS_DisplayLoadDialog(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_DisplayLoadDialog();return 0;}
int JASS_SetTerrainFog(lua_State* L) {if (lua_gettop(L) != 5) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);lua_Number a4 = lua_tonumber(L, 5);JASS_WRAPPER_SetTerrainFog((float)a0, (float)a1, (float)a2, (float)a3, (float)a4);return 0;}
int JASS_SetUnitFog(lua_State* L) {if (lua_gettop(L) != 5) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);lua_Number a4 = lua_tonumber(L, 5);JASS_WRAPPER_SetUnitFog((float)a0, (float)a1, (float)a2, (float)a3, (float)a4);return 0;}
int JASS_SetTerrainFogEx(lua_State* L) {if (lua_gettop(L) != 7) return 0;int a0 = lua_tointeger(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);lua_Number a4 = lua_tonumber(L, 5);lua_Number a5 = lua_tonumber(L, 6);lua_Number a6 = lua_tonumber(L, 7);JASS_WRAPPER_SetTerrainFogEx(a0, (float)a1, (float)a2, (float)a3, (float)a4, (float)a5, (float)a6);return 0;}
int JASS_ResetTerrainFog(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_ResetTerrainFog();return 0;}
int JASS_SetDayNightModels(lua_State* L) {if (lua_gettop(L) != 2) return 0;const char* a0 = lua_tostring(L, 1);const char* a1 = lua_tostring(L, 2);JASS_WRAPPER_SetDayNightModels(a0, a1);return 0;}
int JASS_SetSkyModel(lua_State* L) {if (lua_gettop(L) != 1) return 0;const char* a0 = lua_tostring(L, 1);JASS_WRAPPER_SetSkyModel(a0);return 0;}
int JASS_SuspendTimeOfDay(lua_State* L) {if (lua_gettop(L) != 1) return 0;bool a0 = lua_toboolean(L, 1) > 0;JASS_WRAPPER_SuspendTimeOfDay(a0);return 0;}
int JASS_SetTimeOfDayScale(lua_State* L) {if (lua_gettop(L) != 1) return 0;lua_Number a0 = lua_tonumber(L, 1);JASS_WRAPPER_SetTimeOfDayScale((float)a0);return 0;}
int JASS_GetTimeOfDayScale(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushnumber(L, JASS_WRAPPER_GetTimeOfDayScale());return 1;}
int JASS_ShowInterface(lua_State* L) {if (lua_gettop(L) != 2) return 0;bool a0 = lua_toboolean(L, 1) > 0;lua_Number a1 = lua_tonumber(L, 2);JASS_WRAPPER_ShowInterface(a0, (float)a1);return 0;}
int JASS_PauseGame(lua_State* L) {if (lua_gettop(L) != 1) return 0;bool a0 = lua_toboolean(L, 1) > 0;JASS_WRAPPER_PauseGame(a0);return 0;}
int JASS_PingMinimap(lua_State* L) {if (lua_gettop(L) != 3) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);JASS_WRAPPER_PingMinimap((float)a0, (float)a1, (float)a2);return 0;}
int JASS_PingMinimapEx(lua_State* L) {if (lua_gettop(L) != 7) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);int a3 = lua_tointeger(L, 4);int a4 = lua_tointeger(L, 5);int a5 = lua_tointeger(L, 6);bool a6 = lua_toboolean(L, 7) > 0;JASS_WRAPPER_PingMinimapEx((float)a0, (float)a1, (float)a2, a3, a4, a5, a6);return 0;}
int JASS_SetIntroShotText(lua_State* L) {if (lua_gettop(L) != 1) return 0;const char* a0 = lua_tostring(L, 1);JASS_WRAPPER_SetIntroShotText(a0);return 0;}
int JASS_SetIntroShotModel(lua_State* L) {if (lua_gettop(L) != 1) return 0;const char* a0 = lua_tostring(L, 1);JASS_WRAPPER_SetIntroShotModel(a0);return 0;}
int JASS_EnableOcclusion(lua_State* L) {if (lua_gettop(L) != 1) return 0;bool a0 = lua_toboolean(L, 1) > 0;JASS_WRAPPER_EnableOcclusion(a0);return 0;}
int JASS_EnableWorldFogBoundary(lua_State* L) {if (lua_gettop(L) != 1) return 0;bool a0 = lua_toboolean(L, 1) > 0;JASS_WRAPPER_EnableWorldFogBoundary(a0);return 0;}
int JASS_PlayModelCinematic(lua_State* L) {if (lua_gettop(L) != 1) return 0;const char* a0 = lua_tostring(L, 1);JASS_WRAPPER_PlayModelCinematic(a0);return 0;}
int JASS_PlayCinematic(lua_State* L) {if (lua_gettop(L) != 1) return 0;const char* a0 = lua_tostring(L, 1);JASS_WRAPPER_PlayCinematic(a0);return 0;}
int JASS_SetAltMinimapIcon(lua_State* L) {if (lua_gettop(L) != 1) return 0;const char* a0 = lua_tostring(L, 1);JASS_WRAPPER_SetAltMinimapIcon(a0);return 0;}
int JASS_CreateTextTag(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_CreateTextTag());return 1;}
int JASS_DestroyTextTag(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_DestroyTextTag(a0);return 0;}
int JASS_SetTextTagText(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);lua_Number a2 = lua_tonumber(L, 3);JASS_WRAPPER_SetTextTagText(a0, a1, (float)a2);return 0;}
int JASS_SetTextTagPos(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);JASS_WRAPPER_SetTextTagPos(a0, (float)a1, (float)a2, (float)a3);return 0;}
int JASS_SetTextTagPosUnit(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_Number a2 = lua_tonumber(L, 3);JASS_WRAPPER_SetTextTagPosUnit(a0, a1, (float)a2);return 0;}
int JASS_SetTextTagColor(lua_State* L) {if (lua_gettop(L) != 5) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);int a3 = lua_tointeger(L, 4);int a4 = lua_tointeger(L, 5);JASS_WRAPPER_SetTextTagColor(a0, a1, a2, a3, a4);return 0;}
int JASS_SetTextTagVelocity(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);JASS_WRAPPER_SetTextTagVelocity(a0, (float)a1, (float)a2);return 0;}
int JASS_SetTextTagVisibility(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_SetTextTagVisibility(a0, a1);return 0;}
int JASS_SetTextTagSuspended(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_SetTextTagSuspended(a0, a1);return 0;}
int JASS_SetTextTagPermanent(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_SetTextTagPermanent(a0, a1);return 0;}
int JASS_SetTextTagAge(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);JASS_WRAPPER_SetTextTagAge(a0, (float)a1);return 0;}
int JASS_SetTextTagLifespan(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);JASS_WRAPPER_SetTextTagLifespan(a0, (float)a1);return 0;}
int JASS_SetTextTagFadepoint(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);JASS_WRAPPER_SetTextTagFadepoint(a0, (float)a1);return 0;}
int JASS_SetReservedLocalHeroButtons(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);JASS_WRAPPER_SetReservedLocalHeroButtons(a0);return 0;}
int JASS_GetAllyColorFilterState(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushinteger(L, JASS_WRAPPER_GetAllyColorFilterState());return 1;}
int JASS_SetAllyColorFilterState(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);JASS_WRAPPER_SetAllyColorFilterState(a0);return 0;}
int JASS_GetCreepCampFilterState(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushboolean(L, JASS_WRAPPER_GetCreepCampFilterState() ? 1 : 0);return 1;}
int JASS_SetCreepCampFilterState(lua_State* L) {if (lua_gettop(L) != 1) return 0;bool a0 = lua_toboolean(L, 1) > 0;JASS_WRAPPER_SetCreepCampFilterState(a0);return 0;}
int JASS_EnableMinimapFilterButtons(lua_State* L) {if (lua_gettop(L) != 2) return 0;bool a0 = lua_toboolean(L, 1) > 0;bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_EnableMinimapFilterButtons(a0, a1);return 0;}
int JASS_EnableDragSelect(lua_State* L) {if (lua_gettop(L) != 2) return 0;bool a0 = lua_toboolean(L, 1) > 0;bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_EnableDragSelect(a0, a1);return 0;}
int JASS_EnablePreSelect(lua_State* L) {if (lua_gettop(L) != 2) return 0;bool a0 = lua_toboolean(L, 1) > 0;bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_EnablePreSelect(a0, a1);return 0;}
int JASS_EnableSelect(lua_State* L) {if (lua_gettop(L) != 2) return 0;bool a0 = lua_toboolean(L, 1) > 0;bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_EnableSelect(a0, a1);return 0;}
int JASS_CreateTrackable(lua_State* L) {if (lua_gettop(L) != 4) return 0;const char* a0 = lua_tostring(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);LUA_PUSHDWORD(L, JASS_WRAPPER_CreateTrackable(a0, (float)a1, (float)a2, (float)a3));return 1;}
int JASS_TriggerRegisterTrackableHitEvent(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);LUA_PUSHDWORD(L, JASS_WRAPPER_TriggerRegisterTrackableHitEvent(a0, a1));return 1;}
int JASS_TriggerRegisterTrackableTrackEvent(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);LUA_PUSHDWORD(L, JASS_WRAPPER_TriggerRegisterTrackableTrackEvent(a0, a1));return 1;}
int JASS_GetTriggeringTrackable(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetTriggeringTrackable());return 1;}
int JASS_CreateQuest(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_CreateQuest());return 1;}
int JASS_DestroyQuest(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_DestroyQuest(a0);return 0;}
int JASS_QuestSetTitle(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);JASS_WRAPPER_QuestSetTitle(a0, a1);return 0;}
int JASS_QuestSetDescription(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);JASS_WRAPPER_QuestSetDescription(a0, a1);return 0;}
int JASS_QuestSetIconPath(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);JASS_WRAPPER_QuestSetIconPath(a0, a1);return 0;}
int JASS_QuestSetRequired(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_QuestSetRequired(a0, a1);return 0;}
int JASS_QuestSetCompleted(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_QuestSetCompleted(a0, a1);return 0;}
int JASS_QuestSetDiscovered(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_QuestSetDiscovered(a0, a1);return 0;}
int JASS_QuestSetFailed(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_QuestSetFailed(a0, a1);return 0;}
int JASS_QuestSetEnabled(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_QuestSetEnabled(a0, a1);return 0;}
int JASS_IsQuestRequired(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_IsQuestRequired(a0) ? 1 : 0);return 1;}
int JASS_IsQuestCompleted(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_IsQuestCompleted(a0) ? 1 : 0);return 1;}
int JASS_IsQuestDiscovered(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_IsQuestDiscovered(a0) ? 1 : 0);return 1;}
int JASS_IsQuestFailed(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_IsQuestFailed(a0) ? 1 : 0);return 1;}
int JASS_IsQuestEnabled(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_IsQuestEnabled(a0) ? 1 : 0);return 1;}
int JASS_QuestCreateItem(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_QuestCreateItem(a0));return 1;}
int JASS_QuestItemSetDescription(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);JASS_WRAPPER_QuestItemSetDescription(a0, a1);return 0;}
int JASS_QuestItemSetCompleted(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_QuestItemSetCompleted(a0, a1);return 0;}
int JASS_IsQuestItemCompleted(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_IsQuestItemCompleted(a0) ? 1 : 0);return 1;}
int JASS_CreateDefeatCondition(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_CreateDefeatCondition());return 1;}
int JASS_DestroyDefeatCondition(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_DestroyDefeatCondition(a0);return 0;}
int JASS_DefeatConditionSetDescription(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);JASS_WRAPPER_DefeatConditionSetDescription(a0, a1);return 0;}
int JASS_FlashQuestDialogButton(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_FlashQuestDialogButton();return 0;}
int JASS_ForceQuestDialogUpdate(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_ForceQuestDialogUpdate();return 0;}
int JASS_CreateTimerDialog(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_CreateTimerDialog(a0));return 1;}
int JASS_DestroyTimerDialog(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_DestroyTimerDialog(a0);return 0;}
int JASS_TimerDialogSetTitle(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);JASS_WRAPPER_TimerDialogSetTitle(a0, a1);return 0;}
int JASS_TimerDialogSetTitleColor(lua_State* L) {if (lua_gettop(L) != 5) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);int a3 = lua_tointeger(L, 4);int a4 = lua_tointeger(L, 5);JASS_WRAPPER_TimerDialogSetTitleColor(a0, a1, a2, a3, a4);return 0;}
int JASS_TimerDialogSetTimeColor(lua_State* L) {if (lua_gettop(L) != 5) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);int a3 = lua_tointeger(L, 4);int a4 = lua_tointeger(L, 5);JASS_WRAPPER_TimerDialogSetTimeColor(a0, a1, a2, a3, a4);return 0;}
int JASS_TimerDialogSetSpeed(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);JASS_WRAPPER_TimerDialogSetSpeed(a0, (float)a1);return 0;}
int JASS_TimerDialogDisplay(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_TimerDialogDisplay(a0, a1);return 0;}
int JASS_IsTimerDialogDisplayed(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_IsTimerDialogDisplayed(a0) ? 1 : 0);return 1;}
int JASS_TimerDialogSetRealTimeRemaining(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);JASS_WRAPPER_TimerDialogSetRealTimeRemaining(a0, (float)a1);return 0;}
int JASS_CreateLeaderboard(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_CreateLeaderboard());return 1;}
int JASS_DestroyLeaderboard(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_DestroyLeaderboard(a0);return 0;}
int JASS_LeaderboardGetItemCount(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushinteger(L, JASS_WRAPPER_LeaderboardGetItemCount(a0));return 1;}
int JASS_LeaderboardSetSizeByItemCount(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);JASS_WRAPPER_LeaderboardSetSizeByItemCount(a0, a1);return 0;}
int JASS_LeaderboardAddItem(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);JASS_WRAPPER_LeaderboardAddItem(a0, a1, a2, a3);return 0;}
int JASS_LeaderboardRemoveItem(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);JASS_WRAPPER_LeaderboardRemoveItem(a0, a1);return 0;}
int JASS_LeaderboardRemovePlayerItem(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);JASS_WRAPPER_LeaderboardRemovePlayerItem(a0, a1);return 0;}
int JASS_LeaderboardSortItemsByValue(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_LeaderboardSortItemsByValue(a0, a1);return 0;}
int JASS_LeaderboardSortItemsByPlayer(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_LeaderboardSortItemsByPlayer(a0, a1);return 0;}
int JASS_LeaderboardSortItemsByLabel(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_LeaderboardSortItemsByLabel(a0, a1);return 0;}
int JASS_LeaderboardClear(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_LeaderboardClear(a0);return 0;}
int JASS_LeaderboardDisplay(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_LeaderboardDisplay(a0, a1);return 0;}
int JASS_IsLeaderboardDisplayed(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_IsLeaderboardDisplayed(a0) ? 1 : 0);return 1;}
int JASS_LeaderboardGetLabelText(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushstring(L, JASS_WRAPPER_LeaderboardGetLabelText(a0));return 1;}
int JASS_PlayerSetLeaderboard(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);JASS_WRAPPER_PlayerSetLeaderboard(a0, a1);return 0;}
int JASS_PlayerGetLeaderboard(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_PlayerGetLeaderboard(a0));return 1;}
int JASS_LeaderboardHasPlayerItem(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_pushboolean(L, JASS_WRAPPER_LeaderboardHasPlayerItem(a0, a1) ? 1 : 0);return 1;}
int JASS_LeaderboardGetPlayerIndex(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_pushinteger(L, JASS_WRAPPER_LeaderboardGetPlayerIndex(a0, a1));return 1;}
int JASS_LeaderboardSetLabel(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);JASS_WRAPPER_LeaderboardSetLabel(a0, a1);return 0;}
int JASS_LeaderboardSetLabelColor(lua_State* L) {if (lua_gettop(L) != 5) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);int a3 = lua_tointeger(L, 4);int a4 = lua_tointeger(L, 5);JASS_WRAPPER_LeaderboardSetLabelColor(a0, a1, a2, a3, a4);return 0;}
int JASS_LeaderboardSetValueColor(lua_State* L) {if (lua_gettop(L) != 5) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);int a3 = lua_tointeger(L, 4);int a4 = lua_tointeger(L, 5);JASS_WRAPPER_LeaderboardSetValueColor(a0, a1, a2, a3, a4);return 0;}
int JASS_LeaderboardSetStyle(lua_State* L) {if (lua_gettop(L) != 5) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;bool a2 = lua_toboolean(L, 3) > 0;bool a3 = lua_toboolean(L, 4) > 0;bool a4 = lua_toboolean(L, 5) > 0;JASS_WRAPPER_LeaderboardSetStyle(a0, a1, a2, a3, a4);return 0;}
int JASS_LeaderboardSetItemValue(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);JASS_WRAPPER_LeaderboardSetItemValue(a0, a1, a2);return 0;}
int JASS_LeaderboardSetItemLabel(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);const char* a2 = lua_tostring(L, 3);JASS_WRAPPER_LeaderboardSetItemLabel(a0, a1, a2);return 0;}
int JASS_LeaderboardSetItemStyle(lua_State* L) {if (lua_gettop(L) != 5) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);bool a2 = lua_toboolean(L, 3) > 0;bool a3 = lua_toboolean(L, 4) > 0;bool a4 = lua_toboolean(L, 5) > 0;JASS_WRAPPER_LeaderboardSetItemStyle(a0, a1, a2, a3, a4);return 0;}
int JASS_LeaderboardSetItemLabelColor(lua_State* L) {if (lua_gettop(L) != 6) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);int a3 = lua_tointeger(L, 4);int a4 = lua_tointeger(L, 5);int a5 = lua_tointeger(L, 6);JASS_WRAPPER_LeaderboardSetItemLabelColor(a0, a1, a2, a3, a4, a5);return 0;}
int JASS_LeaderboardSetItemValueColor(lua_State* L) {if (lua_gettop(L) != 6) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);int a3 = lua_tointeger(L, 4);int a4 = lua_tointeger(L, 5);int a5 = lua_tointeger(L, 6);JASS_WRAPPER_LeaderboardSetItemValueColor(a0, a1, a2, a3, a4, a5);return 0;}
int JASS_CreateMultiboard(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_CreateMultiboard());return 1;}
int JASS_DestroyMultiboard(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_DestroyMultiboard(a0);return 0;}
int JASS_MultiboardDisplay(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_MultiboardDisplay(a0, a1);return 0;}
int JASS_MultiboardMinimize(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_MultiboardMinimize(a0, a1);return 0;}
int JASS_IsMultiboardDisplayed(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_IsMultiboardDisplayed(a0) ? 1 : 0);return 1;}
int JASS_IsMultiboardMinimized(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_IsMultiboardMinimized(a0) ? 1 : 0);return 1;}
int JASS_MultiboardClear(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_MultiboardClear(a0);return 0;}
int JASS_MultiboardSetTitleText(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);JASS_WRAPPER_MultiboardSetTitleText(a0, a1);return 0;}
int JASS_MultiboardGetTitleText(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushstring(L, JASS_WRAPPER_MultiboardGetTitleText(a0));return 1;}
int JASS_MultiboardSetTitleTextColor(lua_State* L) {if (lua_gettop(L) != 5) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);int a3 = lua_tointeger(L, 4);int a4 = lua_tointeger(L, 5);JASS_WRAPPER_MultiboardSetTitleTextColor(a0, a1, a2, a3, a4);return 0;}
int JASS_MultiboardGetRowCount(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushinteger(L, JASS_WRAPPER_MultiboardGetRowCount(a0));return 1;}
int JASS_MultiboardGetColumnCount(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushinteger(L, JASS_WRAPPER_MultiboardGetColumnCount(a0));return 1;}
int JASS_MultiboardSetColumnCount(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);JASS_WRAPPER_MultiboardSetColumnCount(a0, a1);return 0;}
int JASS_MultiboardSetRowCount(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);JASS_WRAPPER_MultiboardSetRowCount(a0, a1);return 0;}
int JASS_MultiboardSetItemsStyle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;bool a2 = lua_toboolean(L, 3) > 0;JASS_WRAPPER_MultiboardSetItemsStyle(a0, a1, a2);return 0;}
int JASS_MultiboardSetItemsValueColor(lua_State* L) {if (lua_gettop(L) != 5) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);int a3 = lua_tointeger(L, 4);int a4 = lua_tointeger(L, 5);JASS_WRAPPER_MultiboardSetItemsValueColor(a0, a1, a2, a3, a4);return 0;}
int JASS_MultiboardSetItemsValue(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);JASS_WRAPPER_MultiboardSetItemsValue(a0, a1);return 0;}
int JASS_MultiboardSetItemsWidth(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);JASS_WRAPPER_MultiboardSetItemsWidth(a0, (float)a1);return 0;}
int JASS_MultiboardSetItemsIcon(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);JASS_WRAPPER_MultiboardSetItemsIcon(a0, a1);return 0;}
int JASS_MultiboardGetItem(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_MultiboardGetItem(a0, a1, a2));return 1;}
int JASS_MultiboardReleaseItem(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_MultiboardReleaseItem(a0);return 0;}
int JASS_MultiboardSetItemStyle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;bool a2 = lua_toboolean(L, 3) > 0;JASS_WRAPPER_MultiboardSetItemStyle(a0, a1, a2);return 0;}
int JASS_MultiboardSetItemValue(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);JASS_WRAPPER_MultiboardSetItemValue(a0, a1);return 0;}
int JASS_MultiboardSetItemValueColor(lua_State* L) {if (lua_gettop(L) != 5) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);int a3 = lua_tointeger(L, 4);int a4 = lua_tointeger(L, 5);JASS_WRAPPER_MultiboardSetItemValueColor(a0, a1, a2, a3, a4);return 0;}
int JASS_MultiboardSetItemWidth(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);JASS_WRAPPER_MultiboardSetItemWidth(a0, (float)a1);return 0;}
int JASS_MultiboardSetItemIcon(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);JASS_WRAPPER_MultiboardSetItemIcon(a0, a1);return 0;}
int JASS_MultiboardSuppressDisplay(lua_State* L) {if (lua_gettop(L) != 1) return 0;bool a0 = lua_toboolean(L, 1) > 0;JASS_WRAPPER_MultiboardSuppressDisplay(a0);return 0;}
int JASS_SetCameraBounds(lua_State* L) {if (lua_gettop(L) != 8) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);lua_Number a4 = lua_tonumber(L, 5);lua_Number a5 = lua_tonumber(L, 6);lua_Number a6 = lua_tonumber(L, 7);lua_Number a7 = lua_tonumber(L, 8);JASS_WRAPPER_SetCameraBounds((float)a0, (float)a1, (float)a2, (float)a3, (float)a4, (float)a5, (float)a6, (float)a7);return 0;}
int JASS_SetCameraPosition(lua_State* L) {if (lua_gettop(L) != 2) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);JASS_WRAPPER_SetCameraPosition((float)a0, (float)a1);return 0;}
int JASS_SetCameraQuickPosition(lua_State* L) {if (lua_gettop(L) != 2) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);JASS_WRAPPER_SetCameraQuickPosition((float)a0, (float)a1);return 0;}
int JASS_ResetToGameCamera(lua_State* L) {if (lua_gettop(L) != 1) return 0;lua_Number a0 = lua_tonumber(L, 1);JASS_WRAPPER_ResetToGameCamera((float)a0);return 0;}
int JASS_StopCamera(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_StopCamera();return 0;}
int JASS_PanCameraTo(lua_State* L) {if (lua_gettop(L) != 2) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);JASS_WRAPPER_PanCameraTo((float)a0, (float)a1);return 0;}
int JASS_PanCameraToTimed(lua_State* L) {if (lua_gettop(L) != 3) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);JASS_WRAPPER_PanCameraToTimed((float)a0, (float)a1, (float)a2);return 0;}
int JASS_PanCameraToWithZ(lua_State* L) {if (lua_gettop(L) != 3) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);JASS_WRAPPER_PanCameraToWithZ((float)a0, (float)a1, (float)a2);return 0;}
int JASS_PanCameraToTimedWithZ(lua_State* L) {if (lua_gettop(L) != 4) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);JASS_WRAPPER_PanCameraToTimedWithZ((float)a0, (float)a1, (float)a2, (float)a3);return 0;}
int JASS_SetCinematicCamera(lua_State* L) {if (lua_gettop(L) != 1) return 0;const char* a0 = lua_tostring(L, 1);JASS_WRAPPER_SetCinematicCamera(a0);return 0;}
int JASS_SetCameraField(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);JASS_WRAPPER_SetCameraField(a0, (float)a1, (float)a2);return 0;}
int JASS_AdjustCameraField(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);JASS_WRAPPER_AdjustCameraField(a0, (float)a1, (float)a2);return 0;}
int JASS_SetCameraTargetController(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);bool a3 = lua_toboolean(L, 4) > 0;JASS_WRAPPER_SetCameraTargetController(a0, (float)a1, (float)a2, a3);return 0;}
int JASS_SetCameraOrientController(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);JASS_WRAPPER_SetCameraOrientController(a0, (float)a1, (float)a2);return 0;}
int JASS_SetCameraRotateMode(lua_State* L) {if (lua_gettop(L) != 4) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);JASS_WRAPPER_SetCameraRotateMode((float)a0, (float)a1, (float)a2, (float)a3);return 0;}
int JASS_CreateCameraSetup(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_CreateCameraSetup());return 1;}
int JASS_CameraSetupSetField(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);JASS_WRAPPER_CameraSetupSetField(a0, a1, (float)a2, (float)a3);return 0;}
int JASS_CameraSetupGetField(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_pushnumber(L, JASS_WRAPPER_CameraSetupGetField(a0, a1));return 1;}
int JASS_CameraSetupSetDestPosition(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);JASS_WRAPPER_CameraSetupSetDestPosition(a0, (float)a1, (float)a2, (float)a3);return 0;}
int JASS_CameraSetupGetDestPositionLoc(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_CameraSetupGetDestPositionLoc(a0));return 1;}
int JASS_CameraSetupGetDestPositionX(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_CameraSetupGetDestPositionX(a0));return 1;}
int JASS_CameraSetupGetDestPositionY(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_CameraSetupGetDestPositionY(a0));return 1;}
int JASS_CameraSetupApply(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;bool a2 = lua_toboolean(L, 3) > 0;JASS_WRAPPER_CameraSetupApply(a0, a1, a2);return 0;}
int JASS_CameraSetupApplyWithZ(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);JASS_WRAPPER_CameraSetupApplyWithZ(a0, (float)a1);return 0;}
int JASS_CameraSetupApplyForceDuration(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;lua_Number a2 = lua_tonumber(L, 3);JASS_WRAPPER_CameraSetupApplyForceDuration(a0, a1, (float)a2);return 0;}
int JASS_CameraSetupApplyForceDurationWithZ(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);JASS_WRAPPER_CameraSetupApplyForceDurationWithZ(a0, (float)a1, (float)a2);return 0;}
int JASS_CameraSetTargetNoise(lua_State* L) {if (lua_gettop(L) != 2) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);JASS_WRAPPER_CameraSetTargetNoise((float)a0, (float)a1);return 0;}
int JASS_CameraSetSourceNoise(lua_State* L) {if (lua_gettop(L) != 2) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);JASS_WRAPPER_CameraSetSourceNoise((float)a0, (float)a1);return 0;}
int JASS_CameraSetTargetNoiseEx(lua_State* L) {if (lua_gettop(L) != 3) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);bool a2 = lua_toboolean(L, 3) > 0;JASS_WRAPPER_CameraSetTargetNoiseEx((float)a0, (float)a1, a2);return 0;}
int JASS_CameraSetSourceNoiseEx(lua_State* L) {if (lua_gettop(L) != 3) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);bool a2 = lua_toboolean(L, 3) > 0;JASS_WRAPPER_CameraSetSourceNoiseEx((float)a0, (float)a1, a2);return 0;}
int JASS_CameraSetSmoothingFactor(lua_State* L) {if (lua_gettop(L) != 1) return 0;lua_Number a0 = lua_tonumber(L, 1);JASS_WRAPPER_CameraSetSmoothingFactor((float)a0);return 0;}
int JASS_GetCameraMargin(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetCameraMargin(a0));return 1;}
int JASS_GetCameraBoundMinX(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushnumber(L, JASS_WRAPPER_GetCameraBoundMinX());return 1;}
int JASS_GetCameraBoundMinY(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushnumber(L, JASS_WRAPPER_GetCameraBoundMinY());return 1;}
int JASS_GetCameraBoundMaxX(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushnumber(L, JASS_WRAPPER_GetCameraBoundMaxX());return 1;}
int JASS_GetCameraBoundMaxY(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushnumber(L, JASS_WRAPPER_GetCameraBoundMaxY());return 1;}
int JASS_GetCameraField(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetCameraField(a0));return 1;}
int JASS_GetCameraTargetPositionX(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushnumber(L, JASS_WRAPPER_GetCameraTargetPositionX());return 1;}
int JASS_GetCameraTargetPositionY(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushnumber(L, JASS_WRAPPER_GetCameraTargetPositionY());return 1;}
int JASS_GetCameraTargetPositionZ(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushnumber(L, JASS_WRAPPER_GetCameraTargetPositionZ());return 1;}
int JASS_GetCameraTargetPositionLoc(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetCameraTargetPositionLoc());return 1;}
int JASS_GetCameraEyePositionX(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushnumber(L, JASS_WRAPPER_GetCameraEyePositionX());return 1;}
int JASS_GetCameraEyePositionY(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushnumber(L, JASS_WRAPPER_GetCameraEyePositionY());return 1;}
int JASS_GetCameraEyePositionZ(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushnumber(L, JASS_WRAPPER_GetCameraEyePositionZ());return 1;}
int JASS_GetCameraEyePositionLoc(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetCameraEyePositionLoc());return 1;}
int JASS_SetCineFilterTexture(lua_State* L) {if (lua_gettop(L) != 1) return 0;const char* a0 = lua_tostring(L, 1);JASS_WRAPPER_SetCineFilterTexture(a0);return 0;}
int JASS_SetCineFilterBlendMode(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_SetCineFilterBlendMode(a0);return 0;}
int JASS_IsUnitIdType(lua_State* L) {if (lua_gettop(L) != 2) return 0;int a0 = lua_tointeger(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_pushboolean(L, JASS_WRAPPER_IsUnitIdType(a0, a1) ? 1 : 0);return 1;}
int JASS_GetOwningPlayer(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_GetOwningPlayer(a0));return 1;}
int JASS_UnitShareVision(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);bool a2 = lua_toboolean(L, 3) > 0;JASS_WRAPPER_UnitShareVision(a0, a1, a2);return 0;}
int JASS_UnitSuspendDecay(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_UnitSuspendDecay(a0, a1);return 0;}
int JASS_UnitAddType(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_pushboolean(L, JASS_WRAPPER_UnitAddType(a0, a1) ? 1 : 0);return 1;}
int JASS_UnitRemoveType(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_pushboolean(L, JASS_WRAPPER_UnitRemoveType(a0, a1) ? 1 : 0);return 1;}
int JASS_UnitAddAbility(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);lua_pushboolean(L, JASS_WRAPPER_UnitAddAbility(a0, a1) ? 1 : 0);return 1;}
int JASS_UnitRemoveAbility(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);lua_pushboolean(L, JASS_WRAPPER_UnitRemoveAbility(a0, a1) ? 1 : 0);return 1;}
int JASS_UnitMakeAbilityPermanent(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;int a2 = lua_tointeger(L, 3);lua_pushboolean(L, JASS_WRAPPER_UnitMakeAbilityPermanent(a0, a1, a2) ? 1 : 0);return 1;}
int JASS_UnitHasBuffsEx(lua_State* L) {if (lua_gettop(L) != 8) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;bool a2 = lua_toboolean(L, 3) > 0;bool a3 = lua_toboolean(L, 4) > 0;bool a4 = lua_toboolean(L, 5) > 0;bool a5 = lua_toboolean(L, 6) > 0;bool a6 = lua_toboolean(L, 7) > 0;bool a7 = lua_toboolean(L, 8) > 0;lua_pushboolean(L, JASS_WRAPPER_UnitHasBuffsEx(a0, a1, a2, a3, a4, a5, a6, a7) ? 1 : 0);return 1;}
int JASS_UnitCountBuffsEx(lua_State* L) {if (lua_gettop(L) != 8) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;bool a2 = lua_toboolean(L, 3) > 0;bool a3 = lua_toboolean(L, 4) > 0;bool a4 = lua_toboolean(L, 5) > 0;bool a5 = lua_toboolean(L, 6) > 0;bool a6 = lua_toboolean(L, 7) > 0;bool a7 = lua_toboolean(L, 8) > 0;lua_pushinteger(L, JASS_WRAPPER_UnitCountBuffsEx(a0, a1, a2, a3, a4, a5, a6, a7));return 1;}
int JASS_UnitRemoveBuffs(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;bool a2 = lua_toboolean(L, 3) > 0;JASS_WRAPPER_UnitRemoveBuffs(a0, a1, a2);return 0;}
int JASS_UnitRemoveBuffsEx(lua_State* L) {if (lua_gettop(L) != 8) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;bool a2 = lua_toboolean(L, 3) > 0;bool a3 = lua_toboolean(L, 4) > 0;bool a4 = lua_toboolean(L, 5) > 0;bool a5 = lua_toboolean(L, 6) > 0;bool a6 = lua_toboolean(L, 7) > 0;bool a7 = lua_toboolean(L, 8) > 0;JASS_WRAPPER_UnitRemoveBuffsEx(a0, a1, a2, a3, a4, a5, a6, a7);return 0;}
int JASS_UnitAddSleep(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_UnitAddSleep(a0, a1);return 0;}
int JASS_UnitCanSleep(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_UnitCanSleep(a0) ? 1 : 0);return 1;}
int JASS_UnitAddSleepPerm(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_UnitAddSleepPerm(a0, a1);return 0;}
int JASS_UnitCanSleepPerm(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_UnitCanSleepPerm(a0) ? 1 : 0);return 1;}
int JASS_UnitIsSleeping(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_UnitIsSleeping(a0) ? 1 : 0);return 1;}
int JASS_UnitWakeUp(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_UnitWakeUp(a0);return 0;}
int JASS_UnitApplyTimedLife(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);lua_Number a2 = lua_tonumber(L, 3);JASS_WRAPPER_UnitApplyTimedLife(a0, a1, (float)a2);return 0;}
int JASS_UnitIgnoreAlarm(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;lua_pushboolean(L, JASS_WRAPPER_UnitIgnoreAlarm(a0, a1) ? 1 : 0);return 1;}
int JASS_UnitIgnoreAlarmToggled(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_UnitIgnoreAlarmToggled(a0) ? 1 : 0);return 1;}
int JASS_UnitDamagePoint(lua_State* L) {if (lua_gettop(L) != 11) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);lua_Number a4 = lua_tonumber(L, 5);lua_Number a5 = lua_tonumber(L, 6);bool a6 = lua_toboolean(L, 7) > 0;bool a7 = lua_toboolean(L, 8) > 0;DWORD a8 = LUA_TODWORD(L, 9);DWORD a9 = LUA_TODWORD(L, 10);DWORD a10 = LUA_TODWORD(L, 11);lua_pushboolean(L, JASS_WRAPPER_UnitDamagePoint(a0, (float)a1, (float)a2, (float)a3, (float)a4, (float)a5, a6, a7, a8, a9, a10) ? 1 : 0);return 1;}
int JASS_UnitDamageTarget(lua_State* L) {if (lua_gettop(L) != 8) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_Number a2 = lua_tonumber(L, 3);bool a3 = lua_toboolean(L, 4) > 0;bool a4 = lua_toboolean(L, 5) > 0;DWORD a5 = LUA_TODWORD(L, 6);DWORD a6 = LUA_TODWORD(L, 7);DWORD a7 = LUA_TODWORD(L, 8);lua_pushboolean(L, JASS_WRAPPER_UnitDamageTarget(a0, a1, (float)a2, a3, a4, a5, a6, a7) ? 1 : 0);return 1;}
int JASS_DecUnitAbilityLevel(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);lua_pushinteger(L, JASS_WRAPPER_DecUnitAbilityLevel(a0, a1));return 1;}
int JASS_IncUnitAbilityLevel(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);lua_pushinteger(L, JASS_WRAPPER_IncUnitAbilityLevel(a0, a1));return 1;}
int JASS_SetUnitAbilityLevel(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);lua_pushinteger(L, JASS_WRAPPER_SetUnitAbilityLevel(a0, a1, a2));return 1;}
int JASS_UnitResetCooldown(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_UnitResetCooldown(a0);return 0;}
int JASS_UnitSetConstructionProgress(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);JASS_WRAPPER_UnitSetConstructionProgress(a0, a1);return 0;}
int JASS_UnitSetUpgradeProgress(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);JASS_WRAPPER_UnitSetUpgradeProgress(a0, a1);return 0;}
int JASS_UnitPauseTimedLife(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_UnitPauseTimedLife(a0, a1);return 0;}
int JASS_UnitSetUsesAltIcon(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_UnitSetUsesAltIcon(a0, a1);return 0;}
int JASS_IssueImmediateOrderById(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);lua_pushboolean(L, JASS_WRAPPER_IssueImmediateOrderById(a0, a1) ? 1 : 0);return 1;}
int JASS_IssuePointOrderById(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);lua_pushboolean(L, JASS_WRAPPER_IssuePointOrderById(a0, a1, (float)a2, (float)a3) ? 1 : 0);return 1;}
int JASS_IssuePointOrderByIdLoc(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);DWORD a2 = LUA_TODWORD(L, 3);lua_pushboolean(L, JASS_WRAPPER_IssuePointOrderByIdLoc(a0, a1, a2) ? 1 : 0);return 1;}
int JASS_IssueTargetOrderById(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);DWORD a2 = LUA_TODWORD(L, 3);lua_pushboolean(L, JASS_WRAPPER_IssueTargetOrderById(a0, a1, a2) ? 1 : 0);return 1;}
int JASS_IssueInstantPointOrderById(lua_State* L) {if (lua_gettop(L) != 5) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);DWORD a4 = LUA_TODWORD(L, 5);lua_pushboolean(L, JASS_WRAPPER_IssueInstantPointOrderById(a0, a1, (float)a2, (float)a3, a4) ? 1 : 0);return 1;}
int JASS_IssueInstantTargetOrderById(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);DWORD a2 = LUA_TODWORD(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_IssueInstantTargetOrderById(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_IssueBuildOrderById(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);lua_pushboolean(L, JASS_WRAPPER_IssueBuildOrderById(a0, a1, (float)a2, (float)a3) ? 1 : 0);return 1;}
int JASS_IssueNeutralImmediateOrderById(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);int a2 = lua_tointeger(L, 3);lua_pushboolean(L, JASS_WRAPPER_IssueNeutralImmediateOrderById(a0, a1, a2) ? 1 : 0);return 1;}
int JASS_IssueNeutralPointOrderById(lua_State* L) {if (lua_gettop(L) != 5) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);int a2 = lua_tointeger(L, 3);lua_Number a3 = lua_tonumber(L, 4);lua_Number a4 = lua_tonumber(L, 5);lua_pushboolean(L, JASS_WRAPPER_IssueNeutralPointOrderById(a0, a1, a2, (float)a3, (float)a4) ? 1 : 0);return 1;}
int JASS_IssueNeutralTargetOrderById(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_IssueNeutralTargetOrderById(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_IssueImmediateOrder(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);lua_pushboolean(L, JASS_WRAPPER_IssueImmediateOrder(a0, a1) ? 1 : 0);return 1;}
int JASS_IssuePointOrder(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);lua_pushboolean(L, JASS_WRAPPER_IssuePointOrder(a0, a1, (float)a2, (float)a3) ? 1 : 0);return 1;}
int JASS_IssuePointOrderLoc(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);DWORD a2 = LUA_TODWORD(L, 3);lua_pushboolean(L, JASS_WRAPPER_IssuePointOrderLoc(a0, a1, a2) ? 1 : 0);return 1;}
int JASS_IssueTargetOrder(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);DWORD a2 = LUA_TODWORD(L, 3);lua_pushboolean(L, JASS_WRAPPER_IssueTargetOrder(a0, a1, a2) ? 1 : 0);return 1;}
int JASS_IssueInstantPointOrder(lua_State* L) {if (lua_gettop(L) != 5) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);DWORD a4 = LUA_TODWORD(L, 5);lua_pushboolean(L, JASS_WRAPPER_IssueInstantPointOrder(a0, a1, (float)a2, (float)a3, a4) ? 1 : 0);return 1;}
int JASS_IssueInstantTargetOrder(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);DWORD a2 = LUA_TODWORD(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_IssueInstantTargetOrder(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_IssueBuildOrder(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);lua_pushboolean(L, JASS_WRAPPER_IssueBuildOrder(a0, a1, (float)a2, (float)a3) ? 1 : 0);return 1;}
int JASS_IssueNeutralImmediateOrder(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);const char* a2 = lua_tostring(L, 3);lua_pushboolean(L, JASS_WRAPPER_IssueNeutralImmediateOrder(a0, a1, a2) ? 1 : 0);return 1;}
int JASS_IssueNeutralPointOrder(lua_State* L) {if (lua_gettop(L) != 5) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);const char* a2 = lua_tostring(L, 3);lua_Number a3 = lua_tonumber(L, 4);lua_Number a4 = lua_tonumber(L, 5);lua_pushboolean(L, JASS_WRAPPER_IssueNeutralPointOrder(a0, a1, a2, (float)a3, (float)a4) ? 1 : 0);return 1;}
int JASS_IssueNeutralTargetOrder(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);const char* a2 = lua_tostring(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_IssueNeutralTargetOrder(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_WaygateGetDestinationX(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_WaygateGetDestinationX(a0));return 1;}
int JASS_WaygateGetDestinationY(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_WaygateGetDestinationY(a0));return 1;}
int JASS_WaygateSetDestination(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);JASS_WRAPPER_WaygateSetDestination(a0, (float)a1, (float)a2);return 0;}
int JASS_WaygateActivate(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_WaygateActivate(a0, a1);return 0;}
int JASS_WaygateIsActive(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_WaygateIsActive(a0) ? 1 : 0);return 1;}
int JASS_AddItemToAllStock(lua_State* L) {if (lua_gettop(L) != 3) return 0;int a0 = lua_tointeger(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);JASS_WRAPPER_AddItemToAllStock(a0, a1, a2);return 0;}
int JASS_AddItemToStock(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);int a3 = lua_tointeger(L, 4);JASS_WRAPPER_AddItemToStock(a0, a1, a2, a3);return 0;}
int JASS_AddUnitToAllStock(lua_State* L) {if (lua_gettop(L) != 3) return 0;int a0 = lua_tointeger(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);JASS_WRAPPER_AddUnitToAllStock(a0, a1, a2);return 0;}
int JASS_AddUnitToStock(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);int a3 = lua_tointeger(L, 4);JASS_WRAPPER_AddUnitToStock(a0, a1, a2, a3);return 0;}
int JASS_RemoveItemFromAllStock(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);JASS_WRAPPER_RemoveItemFromAllStock(a0);return 0;}
int JASS_RemoveItemFromStock(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);JASS_WRAPPER_RemoveItemFromStock(a0, a1);return 0;}
int JASS_RemoveUnitFromAllStock(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);JASS_WRAPPER_RemoveUnitFromAllStock(a0);return 0;}
int JASS_RemoveUnitFromStock(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);JASS_WRAPPER_RemoveUnitFromStock(a0, a1);return 0;}
int JASS_SetAllItemTypeSlots(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);JASS_WRAPPER_SetAllItemTypeSlots(a0);return 0;}
int JASS_SetAllUnitTypeSlots(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);JASS_WRAPPER_SetAllUnitTypeSlots(a0);return 0;}
int JASS_SetItemTypeSlots(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);JASS_WRAPPER_SetItemTypeSlots(a0, a1);return 0;}
int JASS_SetUnitTypeSlots(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);JASS_WRAPPER_SetUnitTypeSlots(a0, a1);return 0;}
int JASS_GetUnitUserData(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushinteger(L, JASS_WRAPPER_GetUnitUserData(a0));return 1;}
int JASS_SetUnitUserData(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);JASS_WRAPPER_SetUnitUserData(a0, a1);return 0;}
int JASS_CreateItem(lua_State* L) {if (lua_gettop(L) != 3) return 0;int a0 = lua_tointeger(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_CreateItem(a0, (float)a1, (float)a2));return 1;}
int JASS_RemoveItem(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_RemoveItem(a0);return 0;}
int JASS_GetItemPlayer(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_GetItemPlayer(a0));return 1;}
int JASS_GetItemTypeId(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushinteger(L, JASS_WRAPPER_GetItemTypeId(a0));return 1;}
int JASS_GetItemX(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetItemX(a0));return 1;}
int JASS_GetItemY(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetItemY(a0));return 1;}
int JASS_SetItemPosition(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);JASS_WRAPPER_SetItemPosition(a0, (float)a1, (float)a2);return 0;}
int JASS_SetItemDropOnDeath(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_SetItemDropOnDeath(a0, a1);return 0;}
int JASS_SetItemDroppable(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_SetItemDroppable(a0, a1);return 0;}
int JASS_SetItemPawnable(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_SetItemPawnable(a0, a1);return 0;}
int JASS_SetItemPlayer(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);bool a2 = lua_toboolean(L, 3) > 0;JASS_WRAPPER_SetItemPlayer(a0, a1, a2);return 0;}
int JASS_SetItemInvulnerable(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_SetItemInvulnerable(a0, a1);return 0;}
int JASS_IsItemInvulnerable(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_IsItemInvulnerable(a0) ? 1 : 0);return 1;}
int JASS_GetItemLevel(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushinteger(L, JASS_WRAPPER_GetItemLevel(a0));return 1;}
int JASS_GetItemType(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_GetItemType(a0));return 1;}
int JASS_SetItemVisible(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_SetItemVisible(a0, a1);return 0;}
int JASS_IsItemVisible(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_IsItemVisible(a0) ? 1 : 0);return 1;}
int JASS_EnumItemsInRect(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);DWORD a2 = LUA_TODWORD(L, 3);JASS_WRAPPER_EnumItemsInRect(a0, a1, a2);return 0;}
int JASS_IsItemOwned(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_IsItemOwned(a0) ? 1 : 0);return 1;}
int JASS_IsItemPowerup(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_IsItemPowerup(a0) ? 1 : 0);return 1;}
int JASS_IsItemSellable(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_IsItemSellable(a0) ? 1 : 0);return 1;}
int JASS_IsItemPawnable(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_IsItemPawnable(a0) ? 1 : 0);return 1;}
int JASS_IsItemIdPowerup(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);lua_pushboolean(L, JASS_WRAPPER_IsItemIdPowerup(a0) ? 1 : 0);return 1;}
int JASS_IsItemIdSellable(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);lua_pushboolean(L, JASS_WRAPPER_IsItemIdSellable(a0) ? 1 : 0);return 1;}
int JASS_IsItemIdPawnable(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);lua_pushboolean(L, JASS_WRAPPER_IsItemIdPawnable(a0) ? 1 : 0);return 1;}
int JASS_SetItemDropID(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);JASS_WRAPPER_SetItemDropID(a0, a1);return 0;}
int JASS_GetItemName(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushstring(L, JASS_WRAPPER_GetItemName(a0));return 1;}
int JASS_GetItemCharges(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushinteger(L, JASS_WRAPPER_GetItemCharges(a0));return 1;}
int JASS_SetItemCharges(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);JASS_WRAPPER_SetItemCharges(a0, a1);return 0;}
int JASS_GetItemUserData(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushinteger(L, JASS_WRAPPER_GetItemUserData(a0));return 1;}
int JASS_SetItemUserData(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);JASS_WRAPPER_SetItemUserData(a0, a1);return 0;}
int JASS_Player(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_Player(a0));return 1;}
int JASS_GetLocalPlayer(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetLocalPlayer());return 1;}
int JASS_IsPlayerAlly(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_pushboolean(L, JASS_WRAPPER_IsPlayerAlly(a0, a1) ? 1 : 0);return 1;}
int JASS_IsPlayerEnemy(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_pushboolean(L, JASS_WRAPPER_IsPlayerEnemy(a0, a1) ? 1 : 0);return 1;}
int JASS_IsPlayerInForce(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_pushboolean(L, JASS_WRAPPER_IsPlayerInForce(a0, a1) ? 1 : 0);return 1;}
int JASS_IsPlayerObserver(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_IsPlayerObserver(a0) ? 1 : 0);return 1;}
int JASS_GetPlayerRace(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_GetPlayerRace(a0));return 1;}
int JASS_GetPlayerId(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushinteger(L, JASS_WRAPPER_GetPlayerId(a0));return 1;}
int JASS_SetPlayerTechMaxAllowed(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);JASS_WRAPPER_SetPlayerTechMaxAllowed(a0, a1, a2);return 0;}
int JASS_GetPlayerTechMaxAllowed(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);lua_pushinteger(L, JASS_WRAPPER_GetPlayerTechMaxAllowed(a0, a1));return 1;}
int JASS_AddPlayerTechResearched(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);JASS_WRAPPER_AddPlayerTechResearched(a0, a1, a2);return 0;}
int JASS_SetPlayerTechResearched(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);JASS_WRAPPER_SetPlayerTechResearched(a0, a1, a2);return 0;}
int JASS_GetPlayerTechResearched(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);bool a2 = lua_toboolean(L, 3) > 0;lua_pushboolean(L, JASS_WRAPPER_GetPlayerTechResearched(a0, a1, a2) ? 1 : 0);return 1;}
int JASS_GetPlayerTechCount(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);bool a2 = lua_toboolean(L, 3) > 0;lua_pushinteger(L, JASS_WRAPPER_GetPlayerTechCount(a0, a1, a2));return 1;}
int JASS_SetPlayerAbilityAvailable(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);bool a2 = lua_toboolean(L, 3) > 0;JASS_WRAPPER_SetPlayerAbilityAvailable(a0, a1, a2);return 0;}
int JASS_GetPlayerUnitCount(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;lua_pushinteger(L, JASS_WRAPPER_GetPlayerUnitCount(a0, a1));return 1;}
int JASS_GetPlayerTypedUnitCount(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);bool a2 = lua_toboolean(L, 3) > 0;bool a3 = lua_toboolean(L, 4) > 0;lua_pushinteger(L, JASS_WRAPPER_GetPlayerTypedUnitCount(a0, a1, a2, a3));return 1;}
int JASS_GetPlayerStructureCount(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;lua_pushinteger(L, JASS_WRAPPER_GetPlayerStructureCount(a0, a1));return 1;}
int JASS_IsVisibleToPlayer(lua_State* L) {if (lua_gettop(L) != 3) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);DWORD a2 = LUA_TODWORD(L, 3);lua_pushboolean(L, JASS_WRAPPER_IsVisibleToPlayer((float)a0, (float)a1, a2) ? 1 : 0);return 1;}
int JASS_IsLocationVisibleToPlayer(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_pushboolean(L, JASS_WRAPPER_IsLocationVisibleToPlayer(a0, a1) ? 1 : 0);return 1;}
int JASS_IsFoggedToPlayer(lua_State* L) {if (lua_gettop(L) != 3) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);DWORD a2 = LUA_TODWORD(L, 3);lua_pushboolean(L, JASS_WRAPPER_IsFoggedToPlayer((float)a0, (float)a1, a2) ? 1 : 0);return 1;}
int JASS_IsLocationFoggedToPlayer(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_pushboolean(L, JASS_WRAPPER_IsLocationFoggedToPlayer(a0, a1) ? 1 : 0);return 1;}
int JASS_IsMaskedToPlayer(lua_State* L) {if (lua_gettop(L) != 3) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);DWORD a2 = LUA_TODWORD(L, 3);lua_pushboolean(L, JASS_WRAPPER_IsMaskedToPlayer((float)a0, (float)a1, a2) ? 1 : 0);return 1;}
int JASS_IsLocationMaskedToPlayer(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_pushboolean(L, JASS_WRAPPER_IsLocationMaskedToPlayer(a0, a1) ? 1 : 0);return 1;}
int JASS_SetPlayerState(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);int a2 = lua_tointeger(L, 3);JASS_WRAPPER_SetPlayerState(a0, a1, a2);return 0;}
int JASS_GetPlayerState(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_pushinteger(L, JASS_WRAPPER_GetPlayerState(a0, a1));return 1;}
int JASS_GetPlayerScore(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_pushinteger(L, JASS_WRAPPER_GetPlayerScore(a0, a1));return 1;}
int JASS_GetPlayerAlliance(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);DWORD a2 = LUA_TODWORD(L, 3);lua_pushboolean(L, JASS_WRAPPER_GetPlayerAlliance(a0, a1, a2) ? 1 : 0);return 1;}
int JASS_RemovePlayer(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);JASS_WRAPPER_RemovePlayer(a0, a1);return 0;}
int JASS_CachePlayerHeroData(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_CachePlayerHeroData(a0);return 0;}
int JASS_GetPlayerHandicap(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetPlayerHandicap(a0));return 1;}
int JASS_SetPlayerHandicap(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);JASS_WRAPPER_SetPlayerHandicap(a0, (float)a1);return 0;}
int JASS_GetPlayerHandicapXP(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetPlayerHandicapXP(a0));return 1;}
int JASS_SetPlayerHandicapXP(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);JASS_WRAPPER_SetPlayerHandicapXP(a0, (float)a1);return 0;}
int JASS_SetPlayerUnitsOwner(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);JASS_WRAPPER_SetPlayerUnitsOwner(a0, a1);return 0;}
int JASS_CripplePlayer(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);bool a2 = lua_toboolean(L, 3) > 0;JASS_WRAPPER_CripplePlayer(a0, a1, a2);return 0;}
int JASS_VersionGet(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_VersionGet());return 1;}
int JASS_VersionCompatible(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_VersionCompatible(a0) ? 1 : 0);return 1;}
int JASS_VersionSupported(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_VersionSupported(a0) ? 1 : 0);return 1;}
int JASS_EndGame(lua_State* L) {if (lua_gettop(L) != 1) return 0;bool a0 = lua_toboolean(L, 1) > 0;JASS_WRAPPER_EndGame(a0);return 0;}
int JASS_ChangeLevel(lua_State* L) {if (lua_gettop(L) != 2) return 0;const char* a0 = lua_tostring(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_ChangeLevel(a0, a1);return 0;}
int JASS_RestartGame(lua_State* L) {if (lua_gettop(L) != 1) return 0;bool a0 = lua_toboolean(L, 1) > 0;JASS_WRAPPER_RestartGame(a0);return 0;}
int JASS_ReloadGame(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_ReloadGame();return 0;}
int JASS_LoadGame(lua_State* L) {if (lua_gettop(L) != 2) return 0;const char* a0 = lua_tostring(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_LoadGame(a0, a1);return 0;}
int JASS_SaveGame(lua_State* L) {if (lua_gettop(L) != 1) return 0;const char* a0 = lua_tostring(L, 1);JASS_WRAPPER_SaveGame(a0);return 0;}
int JASS_RenameSaveDirectory(lua_State* L) {if (lua_gettop(L) != 2) return 0;const char* a0 = lua_tostring(L, 1);const char* a1 = lua_tostring(L, 2);lua_pushboolean(L, JASS_WRAPPER_RenameSaveDirectory(a0, a1) ? 1 : 0);return 1;}
int JASS_RemoveSaveDirectory(lua_State* L) {if (lua_gettop(L) != 1) return 0;const char* a0 = lua_tostring(L, 1);lua_pushboolean(L, JASS_WRAPPER_RemoveSaveDirectory(a0) ? 1 : 0);return 1;}
int JASS_CopySaveGame(lua_State* L) {if (lua_gettop(L) != 2) return 0;const char* a0 = lua_tostring(L, 1);const char* a1 = lua_tostring(L, 2);lua_pushboolean(L, JASS_WRAPPER_CopySaveGame(a0, a1) ? 1 : 0);return 1;}
int JASS_SaveGameExists(lua_State* L) {if (lua_gettop(L) != 1) return 0;const char* a0 = lua_tostring(L, 1);lua_pushboolean(L, JASS_WRAPPER_SaveGameExists(a0) ? 1 : 0);return 1;}
int JASS_SetFloatGameState(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);JASS_WRAPPER_SetFloatGameState(a0, (float)a1);return 0;}
int JASS_GetFloatGameState(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetFloatGameState(a0));return 1;}
int JASS_SetIntegerGameState(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);JASS_WRAPPER_SetIntegerGameState(a0, a1);return 0;}
int JASS_GetIntegerGameState(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushinteger(L, JASS_WRAPPER_GetIntegerGameState(a0));return 1;}
int JASS_SyncSelections(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_SyncSelections();return 0;}
int JASS_DialogCreate(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_DialogCreate());return 1;}
int JASS_DialogDestroy(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_DialogDestroy(a0);return 0;}
int JASS_DialogSetAsync(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_DialogSetAsync(a0);return 0;}
int JASS_DialogClear(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_DialogClear(a0);return 0;}
int JASS_DialogSetMessage(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);JASS_WRAPPER_DialogSetMessage(a0, a1);return 0;}
int JASS_DialogAddButton(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);int a2 = lua_tointeger(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_DialogAddButton(a0, a1, a2));return 1;}
int JASS_DialogAddQuitButton(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;const char* a2 = lua_tostring(L, 3);int a3 = lua_tointeger(L, 4);LUA_PUSHDWORD(L, JASS_WRAPPER_DialogAddQuitButton(a0, a1, a2, a3));return 1;}
int JASS_DialogDisplay(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);bool a2 = lua_toboolean(L, 3) > 0;JASS_WRAPPER_DialogDisplay(a0, a1, a2);return 0;}
int JASS_SetMissionAvailable(lua_State* L) {if (lua_gettop(L) != 3) return 0;int a0 = lua_tointeger(L, 1);int a1 = lua_tointeger(L, 2);bool a2 = lua_toboolean(L, 3) > 0;JASS_WRAPPER_SetMissionAvailable(a0, a1, a2);return 0;}
int JASS_SetCampaignAvailable(lua_State* L) {if (lua_gettop(L) != 2) return 0;int a0 = lua_tointeger(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_SetCampaignAvailable(a0, a1);return 0;}
int JASS_SetCampaignMenuRace(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_SetCampaignMenuRace(a0);return 0;}
int JASS_SetCampaignMenuRaceEx(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);JASS_WRAPPER_SetCampaignMenuRaceEx(a0);return 0;}
int JASS_ForceCampaignSelectScreen(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_ForceCampaignSelectScreen();return 0;}
int JASS_SetOpCinematicAvailable(lua_State* L) {if (lua_gettop(L) != 2) return 0;int a0 = lua_tointeger(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_SetOpCinematicAvailable(a0, a1);return 0;}
int JASS_SetEdCinematicAvailable(lua_State* L) {if (lua_gettop(L) != 2) return 0;int a0 = lua_tointeger(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_SetEdCinematicAvailable(a0, a1);return 0;}
int JASS_SetTutorialCleared(lua_State* L) {if (lua_gettop(L) != 1) return 0;bool a0 = lua_toboolean(L, 1) > 0;JASS_WRAPPER_SetTutorialCleared(a0);return 0;}
int JASS_GetDefaultDifficulty(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetDefaultDifficulty());return 1;}
int JASS_SetDefaultDifficulty(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_SetDefaultDifficulty(a0);return 0;}
int JASS_ReloadGameCachesFromDisk(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushboolean(L, JASS_WRAPPER_ReloadGameCachesFromDisk() ? 1 : 0);return 1;}
int JASS_SetCustomCampaignButtonVisible(lua_State* L) {if (lua_gettop(L) != 2) return 0;int a0 = lua_tointeger(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_SetCustomCampaignButtonVisible(a0, a1);return 0;}
int JASS_GetCustomCampaignButtonVisible(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);lua_pushboolean(L, JASS_WRAPPER_GetCustomCampaignButtonVisible(a0) ? 1 : 0);return 1;}
int JASS_DoNotSaveReplay(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_DoNotSaveReplay();return 0;}
int JASS_InitGameCache(lua_State* L) {if (lua_gettop(L) != 1) return 0;const char* a0 = lua_tostring(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_InitGameCache(a0));return 1;}
int JASS_SaveGameCache(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_SaveGameCache(a0) ? 1 : 0);return 1;}
int JASS_StoreInteger(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);const char* a2 = lua_tostring(L, 3);int a3 = lua_tointeger(L, 4);JASS_WRAPPER_StoreInteger(a0, a1, a2, a3);return 0;}
int JASS_StoreReal(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);const char* a2 = lua_tostring(L, 3);lua_Number a3 = lua_tonumber(L, 4);JASS_WRAPPER_StoreReal(a0, a1, a2, (float)a3);return 0;}
int JASS_StoreBoolean(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);const char* a2 = lua_tostring(L, 3);bool a3 = lua_toboolean(L, 4) > 0;JASS_WRAPPER_StoreBoolean(a0, a1, a2, a3);return 0;}
int JASS_StoreUnit(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);const char* a2 = lua_tostring(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_StoreUnit(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_StoreString(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);const char* a2 = lua_tostring(L, 3);const char* a3 = lua_tostring(L, 4);lua_pushboolean(L, JASS_WRAPPER_StoreString(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_SaveInteger(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);int a3 = lua_tointeger(L, 4);JASS_WRAPPER_SaveInteger(a0, a1, a2, a3);return 0;}
int JASS_SaveReal(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);lua_Number a3 = lua_tonumber(L, 4);JASS_WRAPPER_SaveReal(a0, a1, a2, (float)a3);return 0;}
int JASS_SaveBoolean(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);bool a3 = lua_toboolean(L, 4) > 0;JASS_WRAPPER_SaveBoolean(a0, a1, a2, a3);return 0;}
int JASS_SaveStr(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);const char* a3 = lua_tostring(L, 4);lua_pushboolean(L, JASS_WRAPPER_SaveStr(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_SavePlayerHandle(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_SavePlayerHandle(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_SaveWidgetHandle(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_SaveWidgetHandle(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_SaveDestructableHandle(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_SaveDestructableHandle(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_SaveItemHandle(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_SaveItemHandle(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_SaveUnitHandle(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_SaveUnitHandle(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_SaveAbilityHandle(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_SaveAbilityHandle(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_SaveTimerHandle(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_SaveTimerHandle(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_SaveRegionHandle(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_SaveRegionHandle(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_SaveTriggerHandle(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_SaveTriggerHandle(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_SaveTriggerConditionHandle(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_SaveTriggerConditionHandle(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_SaveTriggerActionHandle(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_SaveTriggerActionHandle(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_SaveTriggerEventHandle(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_SaveTriggerEventHandle(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_SaveForceHandle(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_SaveForceHandle(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_SaveGroupHandle(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_SaveGroupHandle(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_SaveLocationHandle(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_SaveLocationHandle(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_SaveRectHandle(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_SaveRectHandle(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_SaveBooleanExprHandle(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_SaveBooleanExprHandle(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_SaveSoundHandle(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_SaveSoundHandle(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_SaveEffectHandle(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_SaveEffectHandle(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_SaveUnitPoolHandle(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_SaveUnitPoolHandle(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_SaveItemPoolHandle(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_SaveItemPoolHandle(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_SaveQuestHandle(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_SaveQuestHandle(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_SaveQuestItemHandle(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_SaveQuestItemHandle(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_SaveDefeatConditionHandle(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_SaveDefeatConditionHandle(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_SaveTimerDialogHandle(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_SaveTimerDialogHandle(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_SaveLeaderboardHandle(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_SaveLeaderboardHandle(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_SaveMultiboardHandle(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_SaveMultiboardHandle(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_SaveMultiboardItemHandle(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_SaveMultiboardItemHandle(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_SaveTrackableHandle(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_SaveTrackableHandle(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_SaveDialogHandle(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_SaveDialogHandle(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_SaveButtonHandle(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_SaveButtonHandle(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_SaveTextTagHandle(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_SaveTextTagHandle(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_SaveLightningHandle(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_SaveLightningHandle(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_SaveImageHandle(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_SaveImageHandle(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_SaveUbersplatHandle(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_SaveUbersplatHandle(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_SaveFogStateHandle(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_SaveFogStateHandle(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_SaveFogModifierHandle(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_SaveFogModifierHandle(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_SaveAgentHandle(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_SaveAgentHandle(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_SaveHashtableHandle(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_pushboolean(L, JASS_WRAPPER_SaveHashtableHandle(a0, a1, a2, a3) ? 1 : 0);return 1;}
int JASS_SyncStoredInteger(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);const char* a2 = lua_tostring(L, 3);JASS_WRAPPER_SyncStoredInteger(a0, a1, a2);return 0;}
int JASS_SyncStoredReal(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);const char* a2 = lua_tostring(L, 3);JASS_WRAPPER_SyncStoredReal(a0, a1, a2);return 0;}
int JASS_SyncStoredBoolean(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);const char* a2 = lua_tostring(L, 3);JASS_WRAPPER_SyncStoredBoolean(a0, a1, a2);return 0;}
int JASS_SyncStoredUnit(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);const char* a2 = lua_tostring(L, 3);JASS_WRAPPER_SyncStoredUnit(a0, a1, a2);return 0;}
int JASS_SyncStoredString(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);const char* a2 = lua_tostring(L, 3);JASS_WRAPPER_SyncStoredString(a0, a1, a2);return 0;}
int JASS_GetStoredInteger(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);const char* a2 = lua_tostring(L, 3);lua_pushinteger(L, JASS_WRAPPER_GetStoredInteger(a0, a1, a2));return 1;}
int JASS_GetStoredReal(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);const char* a2 = lua_tostring(L, 3);lua_pushnumber(L, JASS_WRAPPER_GetStoredReal(a0, a1, a2));return 1;}
int JASS_GetStoredBoolean(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);const char* a2 = lua_tostring(L, 3);lua_pushboolean(L, JASS_WRAPPER_GetStoredBoolean(a0, a1, a2) ? 1 : 0);return 1;}
int JASS_RestoreUnit(lua_State* L) {if (lua_gettop(L) != 7) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);const char* a2 = lua_tostring(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_Number a4 = lua_tonumber(L, 5);lua_Number a5 = lua_tonumber(L, 6);lua_Number a6 = lua_tonumber(L, 7);LUA_PUSHDWORD(L, JASS_WRAPPER_RestoreUnit(a0, a1, a2, a3, (float)a4, (float)a5, (float)a6));return 1;}
int JASS_GetStoredString(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);const char* a2 = lua_tostring(L, 3);lua_pushstring(L, JASS_WRAPPER_GetStoredString(a0, a1, a2));return 1;}
int JASS_HaveStoredInteger(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);const char* a2 = lua_tostring(L, 3);lua_pushboolean(L, JASS_WRAPPER_HaveStoredInteger(a0, a1, a2) ? 1 : 0);return 1;}
int JASS_HaveStoredReal(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);const char* a2 = lua_tostring(L, 3);lua_pushboolean(L, JASS_WRAPPER_HaveStoredReal(a0, a1, a2) ? 1 : 0);return 1;}
int JASS_HaveStoredBoolean(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);const char* a2 = lua_tostring(L, 3);lua_pushboolean(L, JASS_WRAPPER_HaveStoredBoolean(a0, a1, a2) ? 1 : 0);return 1;}
int JASS_HaveStoredUnit(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);const char* a2 = lua_tostring(L, 3);lua_pushboolean(L, JASS_WRAPPER_HaveStoredUnit(a0, a1, a2) ? 1 : 0);return 1;}
int JASS_HaveStoredString(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);const char* a2 = lua_tostring(L, 3);lua_pushboolean(L, JASS_WRAPPER_HaveStoredString(a0, a1, a2) ? 1 : 0);return 1;}
int JASS_FlushGameCache(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_FlushGameCache(a0);return 0;}
int JASS_FlushStoredMission(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);JASS_WRAPPER_FlushStoredMission(a0, a1);return 0;}
int JASS_FlushStoredInteger(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);const char* a2 = lua_tostring(L, 3);JASS_WRAPPER_FlushStoredInteger(a0, a1, a2);return 0;}
int JASS_FlushStoredReal(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);const char* a2 = lua_tostring(L, 3);JASS_WRAPPER_FlushStoredReal(a0, a1, a2);return 0;}
int JASS_FlushStoredBoolean(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);const char* a2 = lua_tostring(L, 3);JASS_WRAPPER_FlushStoredBoolean(a0, a1, a2);return 0;}
int JASS_FlushStoredUnit(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);const char* a2 = lua_tostring(L, 3);JASS_WRAPPER_FlushStoredUnit(a0, a1, a2);return 0;}
int JASS_FlushStoredString(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);const char* a2 = lua_tostring(L, 3);JASS_WRAPPER_FlushStoredString(a0, a1, a2);return 0;}
int JASS_InitHashtable(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_InitHashtable());return 1;}
int JASS_LoadInteger(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);lua_pushinteger(L, JASS_WRAPPER_LoadInteger(a0, a1, a2));return 1;}
int JASS_LoadReal(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);lua_pushnumber(L, JASS_WRAPPER_LoadReal(a0, a1, a2));return 1;}
int JASS_LoadBoolean(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);lua_pushboolean(L, JASS_WRAPPER_LoadBoolean(a0, a1, a2) ? 1 : 0);return 1;}
int JASS_LoadStr(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);lua_pushstring(L, JASS_WRAPPER_LoadStr(a0, a1, a2));return 1;}
int JASS_LoadPlayerHandle(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_LoadPlayerHandle(a0, a1, a2));return 1;}
int JASS_GetLearnedSkill(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushinteger(L, JASS_WRAPPER_GetLearnedSkill());return 1;}
int JASS_GetLearnedSkillLevel(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushinteger(L, JASS_WRAPPER_GetLearnedSkillLevel());return 1;}
int JASS_GetRevivableUnit(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetRevivableUnit());return 1;}
int JASS_GetRevivingUnit(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetRevivingUnit());return 1;}
int JASS_GetSummoningUnit(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetSummoningUnit());return 1;}
int JASS_GetSummonedUnit(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetSummonedUnit());return 1;}
int JASS_GetTransportUnit(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetTransportUnit());return 1;}
int JASS_GetLoadedUnit(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetLoadedUnit());return 1;}
int JASS_GetManipulatingUnit(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetManipulatingUnit());return 1;}
int JASS_GetManipulatedItem(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetManipulatedItem());return 1;}
int JASS_TriggerRegisterPlayerAllianceChange(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);DWORD a2 = LUA_TODWORD(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_TriggerRegisterPlayerAllianceChange(a0, a1, a2));return 1;}
int JASS_TriggerRegisterPlayerChatEvent(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);const char* a2 = lua_tostring(L, 3);bool a3 = lua_toboolean(L, 4) > 0;LUA_PUSHDWORD(L, JASS_WRAPPER_TriggerRegisterPlayerChatEvent(a0, a1, a2, a3));return 1;}
int JASS_GetEventPlayerChatString(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushstring(L, JASS_WRAPPER_GetEventPlayerChatString());return 1;}
int JASS_GetEventPlayerChatStringMatched(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushstring(L, JASS_WRAPPER_GetEventPlayerChatStringMatched());return 1;}
int JASS_TriggerRegisterUnitStateEvent(lua_State* L) {if (lua_gettop(L) != 5) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);DWORD a2 = LUA_TODWORD(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_Number a4 = lua_tonumber(L, 5);LUA_PUSHDWORD(L, JASS_WRAPPER_TriggerRegisterUnitStateEvent(a0, a1, a2, a3, (float)a4));return 1;}
int JASS_GetEventUnitState(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetEventUnitState());return 1;}
int JASS_TriggerRegisterDeathEvent(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);LUA_PUSHDWORD(L, JASS_WRAPPER_TriggerRegisterDeathEvent(a0, a1));return 1;}
int JASS_TriggerRegisterUnitEvent(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);DWORD a2 = LUA_TODWORD(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_TriggerRegisterUnitEvent(a0, a1, a2));return 1;}
int JASS_GetEventDamage(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushnumber(L, JASS_WRAPPER_GetEventDamage());return 1;}
int JASS_GetEventDamageSource(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetEventDamageSource());return 1;}
int JASS_GetEventDetectingPlayer(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetEventDetectingPlayer());return 1;}
int JASS_GetEventTargetUnit(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetEventTargetUnit());return 1;}
int JASS_TriggerRegisterFilterUnitEvent(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);DWORD a2 = LUA_TODWORD(L, 3);DWORD a3 = LUA_TODWORD(L, 4);LUA_PUSHDWORD(L, JASS_WRAPPER_TriggerRegisterFilterUnitEvent(a0, a1, a2, a3));return 1;}
int JASS_TriggerRegisterUnitInRange(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_Number a2 = lua_tonumber(L, 3);DWORD a3 = LUA_TODWORD(L, 4);LUA_PUSHDWORD(L, JASS_WRAPPER_TriggerRegisterUnitInRange(a0, a1, (float)a2, a3));return 1;}
int JASS_TriggerRegisterEnterRegion(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);DWORD a2 = LUA_TODWORD(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_TriggerRegisterEnterRegion(a0, a1, a2));return 1;}
int JASS_TriggerRegisterLeaveRegion(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);DWORD a2 = LUA_TODWORD(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_TriggerRegisterLeaveRegion(a0, a1, a2));return 1;}
int JASS_GetTriggeringRegion(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetTriggeringRegion());return 1;}
int JASS_GetEnteringUnit(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetEnteringUnit());return 1;}
int JASS_GetLeavingUnit(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetLeavingUnit());return 1;}
int JASS_TriggerAddCondition(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);LUA_PUSHDWORD(L, JASS_WRAPPER_TriggerAddCondition(a0, a1));return 1;}
int JASS_TriggerRemoveCondition(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);JASS_WRAPPER_TriggerRemoveCondition(a0, a1);return 0;}
int JASS_TriggerClearConditions(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_TriggerClearConditions(a0);return 0;}
int JASS_TriggerAddAction(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);LUA_PUSHDWORD(L, JASS_WRAPPER_TriggerAddAction(a0, a1));return 1;}
int JASS_TriggerRemoveAction(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);JASS_WRAPPER_TriggerRemoveAction(a0, a1);return 0;}
int JASS_TriggerClearActions(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_TriggerClearActions(a0);return 0;}
int JASS_TriggerSleepAction(lua_State* L) {if (lua_gettop(L) != 1) return 0;lua_Number a0 = lua_tonumber(L, 1);JASS_WRAPPER_TriggerSleepAction((float)a0);return 0;}
int JASS_TriggerWaitForSound(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);JASS_WRAPPER_TriggerWaitForSound(a0, (float)a1);return 0;}
int JASS_TriggerExecute(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_TriggerExecute(a0);return 0;}
int JASS_TriggerExecuteWait(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_TriggerExecuteWait(a0);return 0;}
int JASS_TriggerEvaluate(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_TriggerEvaluate(a0) ? 1 : 0);return 1;}
int JASS_TriggerSyncStart(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_TriggerSyncStart();return 0;}
int JASS_TriggerSyncReady(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_TriggerSyncReady();return 0;}
int JASS_GetTriggerWidget(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetTriggerWidget());return 1;}
int JASS_GetTriggerDestructable(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetTriggerDestructable());return 1;}
int JASS_GetTriggerUnit(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetTriggerUnit());return 1;}
int JASS_GetTriggerPlayer(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetTriggerPlayer());return 1;}
int JASS_GetTriggeringTrigger(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetTriggeringTrigger());return 1;}
int JASS_GetTriggerEventId(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetTriggerEventId());return 1;}
int JASS_GetTriggerEvalCount(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushinteger(L, JASS_WRAPPER_GetTriggerEvalCount(a0));return 1;}
int JASS_GetTriggerExecCount(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushinteger(L, JASS_WRAPPER_GetTriggerExecCount(a0));return 1;}
int JASS_GetFilterUnit(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetFilterUnit());return 1;}
int JASS_GetEnumUnit(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetEnumUnit());return 1;}
int JASS_GetEnumPlayer(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetEnumPlayer());return 1;}
int JASS_GetFilterPlayer(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetFilterPlayer());return 1;}
int JASS_GetFilterDestructable(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetFilterDestructable());return 1;}
int JASS_GetEnumDestructable(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetEnumDestructable());return 1;}
int JASS_GetFilterItem(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetFilterItem());return 1;}
int JASS_GetEnumItem(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetEnumItem());return 1;}
int JASS_CreateGroup(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_CreateGroup());return 1;}
int JASS_DestroyGroup(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_DestroyGroup(a0);return 0;}
int JASS_GroupAddUnit(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);JASS_WRAPPER_GroupAddUnit(a0, a1);return 0;}
int JASS_GroupRemoveUnit(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);JASS_WRAPPER_GroupRemoveUnit(a0, a1);return 0;}
int JASS_GroupClear(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_GroupClear(a0);return 0;}
int JASS_GroupEnumUnitsOfType(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);DWORD a2 = LUA_TODWORD(L, 3);JASS_WRAPPER_GroupEnumUnitsOfType(a0, a1, a2);return 0;}
int JASS_GroupEnumUnitsOfTypeCounted(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);DWORD a2 = LUA_TODWORD(L, 3);int a3 = lua_tointeger(L, 4);JASS_WRAPPER_GroupEnumUnitsOfTypeCounted(a0, a1, a2, a3);return 0;}
int JASS_GroupEnumUnitsInRect(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);DWORD a2 = LUA_TODWORD(L, 3);JASS_WRAPPER_GroupEnumUnitsInRect(a0, a1, a2);return 0;}
int JASS_GroupEnumUnitsInRectCounted(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);DWORD a2 = LUA_TODWORD(L, 3);int a3 = lua_tointeger(L, 4);JASS_WRAPPER_GroupEnumUnitsInRectCounted(a0, a1, a2, a3);return 0;}
int JASS_GroupEnumUnitsOfPlayer(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);DWORD a2 = LUA_TODWORD(L, 3);JASS_WRAPPER_GroupEnumUnitsOfPlayer(a0, a1, a2);return 0;}
int JASS_GroupEnumUnitsInRange(lua_State* L) {if (lua_gettop(L) != 5) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);DWORD a4 = LUA_TODWORD(L, 5);JASS_WRAPPER_GroupEnumUnitsInRange(a0, (float)a1, (float)a2, (float)a3, a4);return 0;}
int JASS_GroupEnumUnitsInRangeOfLoc(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_Number a2 = lua_tonumber(L, 3);DWORD a3 = LUA_TODWORD(L, 4);JASS_WRAPPER_GroupEnumUnitsInRangeOfLoc(a0, a1, (float)a2, a3);return 0;}
int JASS_GroupEnumUnitsInRangeCounted(lua_State* L) {if (lua_gettop(L) != 6) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);DWORD a4 = LUA_TODWORD(L, 5);int a5 = lua_tointeger(L, 6);JASS_WRAPPER_GroupEnumUnitsInRangeCounted(a0, (float)a1, (float)a2, (float)a3, a4, a5);return 0;}
int JASS_GroupEnumUnitsInRangeOfLocCounted(lua_State* L) {if (lua_gettop(L) != 5) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_Number a2 = lua_tonumber(L, 3);DWORD a3 = LUA_TODWORD(L, 4);int a4 = lua_tointeger(L, 5);JASS_WRAPPER_GroupEnumUnitsInRangeOfLocCounted(a0, a1, (float)a2, a3, a4);return 0;}
int JASS_GroupEnumUnitsSelected(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);DWORD a2 = LUA_TODWORD(L, 3);JASS_WRAPPER_GroupEnumUnitsSelected(a0, a1, a2);return 0;}
int JASS_GroupImmediateOrder(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);lua_pushboolean(L, JASS_WRAPPER_GroupImmediateOrder(a0, a1) ? 1 : 0);return 1;}
int JASS_GroupImmediateOrderById(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);lua_pushboolean(L, JASS_WRAPPER_GroupImmediateOrderById(a0, a1) ? 1 : 0);return 1;}
int JASS_GroupPointOrder(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);lua_pushboolean(L, JASS_WRAPPER_GroupPointOrder(a0, a1, (float)a2, (float)a3) ? 1 : 0);return 1;}
int JASS_GroupPointOrderLoc(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);DWORD a2 = LUA_TODWORD(L, 3);lua_pushboolean(L, JASS_WRAPPER_GroupPointOrderLoc(a0, a1, a2) ? 1 : 0);return 1;}
int JASS_GroupPointOrderById(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);lua_pushboolean(L, JASS_WRAPPER_GroupPointOrderById(a0, a1, (float)a2, (float)a3) ? 1 : 0);return 1;}
int JASS_GroupPointOrderByIdLoc(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);DWORD a2 = LUA_TODWORD(L, 3);lua_pushboolean(L, JASS_WRAPPER_GroupPointOrderByIdLoc(a0, a1, a2) ? 1 : 0);return 1;}
int JASS_GroupTargetOrder(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);DWORD a2 = LUA_TODWORD(L, 3);lua_pushboolean(L, JASS_WRAPPER_GroupTargetOrder(a0, a1, a2) ? 1 : 0);return 1;}
int JASS_GroupTargetOrderById(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);DWORD a2 = LUA_TODWORD(L, 3);lua_pushboolean(L, JASS_WRAPPER_GroupTargetOrderById(a0, a1, a2) ? 1 : 0);return 1;}
int JASS_ForGroup(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);JASS_WRAPPER_ForGroup(a0, a1);return 0;}
int JASS_FirstOfGroup(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_FirstOfGroup(a0));return 1;}
int JASS_CreateForce(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_CreateForce());return 1;}
int JASS_DestroyForce(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_DestroyForce(a0);return 0;}
int JASS_ForceAddPlayer(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);JASS_WRAPPER_ForceAddPlayer(a0, a1);return 0;}
int JASS_ForceRemovePlayer(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);JASS_WRAPPER_ForceRemovePlayer(a0, a1);return 0;}
int JASS_ForceClear(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_ForceClear(a0);return 0;}
int JASS_ForceEnumPlayers(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);JASS_WRAPPER_ForceEnumPlayers(a0, a1);return 0;}
int JASS_ForceEnumPlayersCounted(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);int a2 = lua_tointeger(L, 3);JASS_WRAPPER_ForceEnumPlayersCounted(a0, a1, a2);return 0;}
int JASS_ForceEnumAllies(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);DWORD a2 = LUA_TODWORD(L, 3);JASS_WRAPPER_ForceEnumAllies(a0, a1, a2);return 0;}
int JASS_ForceEnumEnemies(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);DWORD a2 = LUA_TODWORD(L, 3);JASS_WRAPPER_ForceEnumEnemies(a0, a1, a2);return 0;}
int JASS_ForForce(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);JASS_WRAPPER_ForForce(a0, a1);return 0;}
int JASS_GetWidgetLife(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetWidgetLife(a0));return 1;}
int JASS_SetWidgetLife(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);JASS_WRAPPER_SetWidgetLife(a0, (float)a1);return 0;}
int JASS_GetWidgetX(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetWidgetX(a0));return 1;}
int JASS_GetWidgetY(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetWidgetY(a0));return 1;}
int JASS_CreateDestructable(lua_State* L) {if (lua_gettop(L) != 6) return 0;int a0 = lua_tointeger(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);lua_Number a4 = lua_tonumber(L, 5);int a5 = lua_tointeger(L, 6);LUA_PUSHDWORD(L, JASS_WRAPPER_CreateDestructable(a0, (float)a1, (float)a2, (float)a3, (float)a4, a5));return 1;}
int JASS_CreateDestructableZ(lua_State* L) {if (lua_gettop(L) != 7) return 0;int a0 = lua_tointeger(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);lua_Number a4 = lua_tonumber(L, 5);lua_Number a5 = lua_tonumber(L, 6);int a6 = lua_tointeger(L, 7);LUA_PUSHDWORD(L, JASS_WRAPPER_CreateDestructableZ(a0, (float)a1, (float)a2, (float)a3, (float)a4, (float)a5, a6));return 1;}
int JASS_CreateDeadDestructable(lua_State* L) {if (lua_gettop(L) != 6) return 0;int a0 = lua_tointeger(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);lua_Number a4 = lua_tonumber(L, 5);int a5 = lua_tointeger(L, 6);LUA_PUSHDWORD(L, JASS_WRAPPER_CreateDeadDestructable(a0, (float)a1, (float)a2, (float)a3, (float)a4, a5));return 1;}
int JASS_CreateDeadDestructableZ(lua_State* L) {if (lua_gettop(L) != 7) return 0;int a0 = lua_tointeger(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);lua_Number a4 = lua_tonumber(L, 5);lua_Number a5 = lua_tonumber(L, 6);int a6 = lua_tointeger(L, 7);LUA_PUSHDWORD(L, JASS_WRAPPER_CreateDeadDestructableZ(a0, (float)a1, (float)a2, (float)a3, (float)a4, (float)a5, a6));return 1;}
int JASS_RemoveDestructable(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_RemoveDestructable(a0);return 0;}
int JASS_KillDestructable(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_KillDestructable(a0);return 0;}
int JASS_SetDestructableInvulnerable(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_SetDestructableInvulnerable(a0, a1);return 0;}
int JASS_IsDestructableInvulnerable(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_IsDestructableInvulnerable(a0) ? 1 : 0);return 1;}
int JASS_EnumDestructablesInRect(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);DWORD a2 = LUA_TODWORD(L, 3);JASS_WRAPPER_EnumDestructablesInRect(a0, a1, a2);return 0;}
int JASS_GetDestructableTypeId(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushinteger(L, JASS_WRAPPER_GetDestructableTypeId(a0));return 1;}
int JASS_GetDestructableX(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetDestructableX(a0));return 1;}
int JASS_GetDestructableY(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetDestructableY(a0));return 1;}
int JASS_SetDestructableLife(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);JASS_WRAPPER_SetDestructableLife(a0, (float)a1);return 0;}
int JASS_GetDestructableLife(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetDestructableLife(a0));return 1;}
int JASS_SetDestructableMaxLife(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);JASS_WRAPPER_SetDestructableMaxLife(a0, (float)a1);return 0;}
int JASS_GetDestructableMaxLife(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetDestructableMaxLife(a0));return 1;}
int JASS_DestructableRestoreLife(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);bool a2 = lua_toboolean(L, 3) > 0;JASS_WRAPPER_DestructableRestoreLife(a0, (float)a1, a2);return 0;}
int JASS_QueueDestructableAnimation(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);JASS_WRAPPER_QueueDestructableAnimation(a0, a1);return 0;}
int JASS_SetDestructableAnimation(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);JASS_WRAPPER_SetDestructableAnimation(a0, a1);return 0;}
int JASS_SetDestructableAnimationSpeed(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);JASS_WRAPPER_SetDestructableAnimationSpeed(a0, (float)a1);return 0;}
int JASS_ShowDestructable(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_ShowDestructable(a0, a1);return 0;}
int JASS_GetDestructableOccluderHeight(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetDestructableOccluderHeight(a0));return 1;}
int JASS_SetDestructableOccluderHeight(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);JASS_WRAPPER_SetDestructableOccluderHeight(a0, (float)a1);return 0;}
int JASS_GetDestructableName(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushstring(L, JASS_WRAPPER_GetDestructableName(a0));return 1;}
int JASS_CreateUnit(lua_State* L) {if (lua_gettop(L) != 5) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);lua_Number a4 = lua_tonumber(L, 5);LUA_PUSHDWORD(L, JASS_WRAPPER_CreateUnit(a0, a1, (float)a2, (float)a3, (float)a4));return 1;}
int JASS_CreateUnitByName(lua_State* L) {if (lua_gettop(L) != 5) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);lua_Number a4 = lua_tonumber(L, 5);LUA_PUSHDWORD(L, JASS_WRAPPER_CreateUnitByName(a0, a1, (float)a2, (float)a3, (float)a4));return 1;}
int JASS_CreateUnitAtLoc(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);DWORD a2 = LUA_TODWORD(L, 3);lua_Number a3 = lua_tonumber(L, 4);LUA_PUSHDWORD(L, JASS_WRAPPER_CreateUnitAtLoc(a0, a1, a2, (float)a3));return 1;}
int JASS_CreateUnitAtLocByName(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);DWORD a2 = LUA_TODWORD(L, 3);lua_Number a3 = lua_tonumber(L, 4);LUA_PUSHDWORD(L, JASS_WRAPPER_CreateUnitAtLocByName(a0, a1, a2, (float)a3));return 1;}
int JASS_CreateCorpse(lua_State* L) {if (lua_gettop(L) != 5) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);lua_Number a4 = lua_tonumber(L, 5);LUA_PUSHDWORD(L, JASS_WRAPPER_CreateCorpse(a0, a1, (float)a2, (float)a3, (float)a4));return 1;}
int JASS_GetUnitState(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_pushnumber(L, JASS_WRAPPER_GetUnitState(a0, a1));return 1;}
int JASS_GetUnitFoodUsed(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushinteger(L, JASS_WRAPPER_GetUnitFoodUsed(a0));return 1;}
int JASS_GetUnitFoodMade(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushinteger(L, JASS_WRAPPER_GetUnitFoodMade(a0));return 1;}
int JASS_GetFoodMade(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);lua_pushinteger(L, JASS_WRAPPER_GetFoodMade(a0));return 1;}
int JASS_GetFoodUsed(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);lua_pushinteger(L, JASS_WRAPPER_GetFoodUsed(a0));return 1;}
int JASS_SetUnitUseFood(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_SetUnitUseFood(a0, a1);return 0;}
int JASS_GetUnitX(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetUnitX(a0));return 1;}
int JASS_GetUnitY(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetUnitY(a0));return 1;}
int JASS_GetUnitLoc(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_GetUnitLoc(a0));return 1;}
int JASS_GetUnitRallyPoint(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_GetUnitRallyPoint(a0));return 1;}
int JASS_GetUnitRallyUnit(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_GetUnitRallyUnit(a0));return 1;}
int JASS_GetUnitRallyDestructable(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_GetUnitRallyDestructable(a0));return 1;}
int JASS_GetUnitFacing(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetUnitFacing(a0));return 1;}
int JASS_GetUnitMoveSpeed(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetUnitMoveSpeed(a0));return 1;}
int JASS_GetUnitDefaultMoveSpeed(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetUnitDefaultMoveSpeed(a0));return 1;}
int JASS_GetUnitTypeId(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushinteger(L, JASS_WRAPPER_GetUnitTypeId(a0));return 1;}
int JASS_GetUnitRace(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_GetUnitRace(a0));return 1;}
int JASS_GetUnitName(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushstring(L, JASS_WRAPPER_GetUnitName(a0));return 1;}
int JASS_GetUnitPointValue(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushinteger(L, JASS_WRAPPER_GetUnitPointValue(a0));return 1;}
int JASS_GetUnitPointValueByType(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);lua_pushinteger(L, JASS_WRAPPER_GetUnitPointValueByType(a0));return 1;}
int JASS_SetUnitX(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);JASS_WRAPPER_SetUnitX(a0, (float)a1);return 0;}
int JASS_SetUnitY(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);JASS_WRAPPER_SetUnitY(a0, (float)a1);return 0;}
int JASS_SetUnitPosition(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);JASS_WRAPPER_SetUnitPosition(a0, (float)a1, (float)a2);return 0;}
int JASS_SetUnitPositionLoc(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);JASS_WRAPPER_SetUnitPositionLoc(a0, a1);return 0;}
int JASS_SetUnitFacing(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);JASS_WRAPPER_SetUnitFacing(a0, (float)a1);return 0;}
int JASS_SetUnitFacingTimed(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);JASS_WRAPPER_SetUnitFacingTimed(a0, (float)a1, (float)a2);return 0;}
int JASS_SetUnitFlyHeight(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);JASS_WRAPPER_SetUnitFlyHeight(a0, (float)a1, (float)a2);return 0;}
int JASS_SetUnitMoveSpeed(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);JASS_WRAPPER_SetUnitMoveSpeed(a0, (float)a1);return 0;}
int JASS_SetUnitTurnSpeed(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);JASS_WRAPPER_SetUnitTurnSpeed(a0, (float)a1);return 0;}
int JASS_SetUnitPropWindow(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);JASS_WRAPPER_SetUnitPropWindow(a0, (float)a1);return 0;}
int JASS_SetUnitCreepGuard(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_SetUnitCreepGuard(a0, a1);return 0;}
int JASS_GetUnitAcquireRange(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetUnitAcquireRange(a0));return 1;}
int JASS_GetUnitTurnSpeed(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetUnitTurnSpeed(a0));return 1;}
int JASS_GetUnitPropWindow(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetUnitPropWindow(a0));return 1;}
int JASS_GetUnitFlyHeight(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetUnitFlyHeight(a0));return 1;}
int JASS_GetUnitDefaultAcquireRange(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetUnitDefaultAcquireRange(a0));return 1;}
int JASS_GetUnitDefaultTurnSpeed(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetUnitDefaultTurnSpeed(a0));return 1;}
int JASS_GetUnitDefaultPropWindow(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetUnitDefaultPropWindow(a0));return 1;}
int JASS_GetUnitDefaultFlyHeight(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetUnitDefaultFlyHeight(a0));return 1;}
int JASS_SetUnitAcquireRange(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);JASS_WRAPPER_SetUnitAcquireRange(a0, (float)a1);return 0;}
int JASS_SetUnitState(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_Number a2 = lua_tonumber(L, 3);JASS_WRAPPER_SetUnitState(a0, a1, (float)a2);return 0;}
int JASS_SetUnitOwner(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);bool a2 = lua_toboolean(L, 3) > 0;JASS_WRAPPER_SetUnitOwner(a0, a1, a2);return 0;}
int JASS_SetUnitRescuable(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);bool a2 = lua_toboolean(L, 3) > 0;JASS_WRAPPER_SetUnitRescuable(a0, a1, a2);return 0;}
int JASS_SetUnitRescueRange(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);JASS_WRAPPER_SetUnitRescueRange(a0, (float)a1);return 0;}
int JASS_SetUnitColor(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);JASS_WRAPPER_SetUnitColor(a0, a1);return 0;}
int JASS_QueueUnitAnimation(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);JASS_WRAPPER_QueueUnitAnimation(a0, a1);return 0;}
int JASS_SetUnitAnimation(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);JASS_WRAPPER_SetUnitAnimation(a0, a1);return 0;}
int JASS_SetUnitAnimationWithRarity(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);DWORD a2 = LUA_TODWORD(L, 3);JASS_WRAPPER_SetUnitAnimationWithRarity(a0, a1, a2);return 0;}
int JASS_SetUnitAnimationByIndex(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);JASS_WRAPPER_SetUnitAnimationByIndex(a0, a1);return 0;}
int JASS_AddUnitAnimationProperties(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);bool a2 = lua_toboolean(L, 3) > 0;JASS_WRAPPER_AddUnitAnimationProperties(a0, a1, a2);return 0;}
int JASS_SetUnitScale(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);JASS_WRAPPER_SetUnitScale(a0, (float)a1, (float)a2, (float)a3);return 0;}
int JASS_SetUnitTimeScale(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);JASS_WRAPPER_SetUnitTimeScale(a0, (float)a1);return 0;}
int JASS_SetUnitBlendTime(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);JASS_WRAPPER_SetUnitBlendTime(a0, (float)a1);return 0;}
int JASS_SetUnitVertexColor(lua_State* L) {if (lua_gettop(L) != 5) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);int a3 = lua_tointeger(L, 4);int a4 = lua_tointeger(L, 5);JASS_WRAPPER_SetUnitVertexColor(a0, a1, a2, a3, a4);return 0;}
int JASS_SetUnitLookAt(lua_State* L) {if (lua_gettop(L) != 6) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);DWORD a2 = LUA_TODWORD(L, 3);lua_Number a3 = lua_tonumber(L, 4);lua_Number a4 = lua_tonumber(L, 5);lua_Number a5 = lua_tonumber(L, 6);JASS_WRAPPER_SetUnitLookAt(a0, a1, a2, (float)a3, (float)a4, (float)a5);return 0;}
int JASS_SetUnitPathing(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_SetUnitPathing(a0, a1);return 0;}
int JASS_ResetUnitLookAt(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_ResetUnitLookAt(a0);return 0;}
int JASS_SetHeroStr(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);bool a2 = lua_toboolean(L, 3) > 0;JASS_WRAPPER_SetHeroStr(a0, a1, a2);return 0;}
int JASS_SetHeroAgi(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);bool a2 = lua_toboolean(L, 3) > 0;JASS_WRAPPER_SetHeroAgi(a0, a1, a2);return 0;}
int JASS_SetHeroInt(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);bool a2 = lua_toboolean(L, 3) > 0;JASS_WRAPPER_SetHeroInt(a0, a1, a2);return 0;}
int JASS_GetHeroStr(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;lua_pushinteger(L, JASS_WRAPPER_GetHeroStr(a0, a1));return 1;}
int JASS_GetHeroAgi(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;lua_pushinteger(L, JASS_WRAPPER_GetHeroAgi(a0, a1));return 1;}
int JASS_GetHeroInt(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;lua_pushinteger(L, JASS_WRAPPER_GetHeroInt(a0, a1));return 1;}
int JASS_GetHeroSkillPoints(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushinteger(L, JASS_WRAPPER_GetHeroSkillPoints(a0));return 1;}
int JASS_UnitStripHeroLevel(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);lua_pushboolean(L, JASS_WRAPPER_UnitStripHeroLevel(a0, a1) ? 1 : 0);return 1;}
int JASS_UnitModifySkillPoints(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);lua_pushboolean(L, JASS_WRAPPER_UnitModifySkillPoints(a0, a1) ? 1 : 0);return 1;}
int JASS_GetHeroXP(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushinteger(L, JASS_WRAPPER_GetHeroXP(a0));return 1;}
int JASS_SetHeroXP(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);bool a2 = lua_toboolean(L, 3) > 0;JASS_WRAPPER_SetHeroXP(a0, a1, a2);return 0;}
int JASS_AddHeroXP(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);bool a2 = lua_toboolean(L, 3) > 0;JASS_WRAPPER_AddHeroXP(a0, a1, a2);return 0;}
int JASS_SetHeroLevel(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);bool a2 = lua_toboolean(L, 3) > 0;JASS_WRAPPER_SetHeroLevel(a0, a1, a2);return 0;}
int JASS_GetHeroLevel(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushinteger(L, JASS_WRAPPER_GetHeroLevel(a0));return 1;}
int JASS_GetUnitLevel(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushinteger(L, JASS_WRAPPER_GetUnitLevel(a0));return 1;}
int JASS_GetHeroProperName(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushstring(L, JASS_WRAPPER_GetHeroProperName(a0));return 1;}
int JASS_SuspendHeroXP(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_SuspendHeroXP(a0, a1);return 0;}
int JASS_IsSuspendedXP(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_IsSuspendedXP(a0) ? 1 : 0);return 1;}
int JASS_SelectHeroSkill(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);JASS_WRAPPER_SelectHeroSkill(a0, a1);return 0;}
int JASS_GetUnitAbilityLevel(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);lua_pushinteger(L, JASS_WRAPPER_GetUnitAbilityLevel(a0, a1));return 1;}
int JASS_ReviveHero(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);bool a3 = lua_toboolean(L, 4) > 0;lua_pushboolean(L, JASS_WRAPPER_ReviveHero(a0, (float)a1, (float)a2, a3) ? 1 : 0);return 1;}
int JASS_ReviveHeroLoc(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);bool a2 = lua_toboolean(L, 3) > 0;lua_pushboolean(L, JASS_WRAPPER_ReviveHeroLoc(a0, a1, a2) ? 1 : 0);return 1;}
int JASS_SetUnitExploded(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_SetUnitExploded(a0, a1);return 0;}
int JASS_SetUnitInvulnerable(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_SetUnitInvulnerable(a0, a1);return 0;}
int JASS_PauseUnit(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_PauseUnit(a0, a1);return 0;}
int JASS_IsUnitPaused(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_IsUnitPaused(a0) ? 1 : 0);return 1;}
int JASS_UnitAddItem(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_pushboolean(L, JASS_WRAPPER_UnitAddItem(a0, a1) ? 1 : 0);return 1;}
int JASS_UnitAddItemById(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);LUA_PUSHDWORD(L, JASS_WRAPPER_UnitAddItemById(a0, a1));return 1;}
int JASS_UnitAddItemToSlotById(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);lua_pushboolean(L, JASS_WRAPPER_UnitAddItemToSlotById(a0, a1, a2) ? 1 : 0);return 1;}
int JASS_UnitRemoveItem(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);JASS_WRAPPER_UnitRemoveItem(a0, a1);return 0;}
int JASS_UnitRemoveItemFromSlot(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);LUA_PUSHDWORD(L, JASS_WRAPPER_UnitRemoveItemFromSlot(a0, a1));return 1;}
int JASS_UnitHasItem(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_pushboolean(L, JASS_WRAPPER_UnitHasItem(a0, a1) ? 1 : 0);return 1;}
int JASS_UnitItemInSlot(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);LUA_PUSHDWORD(L, JASS_WRAPPER_UnitItemInSlot(a0, a1));return 1;}
int JASS_UnitInventorySize(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushinteger(L, JASS_WRAPPER_UnitInventorySize(a0));return 1;}
int JASS_UnitDropItemPoint(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);lua_pushboolean(L, JASS_WRAPPER_UnitDropItemPoint(a0, a1, (float)a2, (float)a3) ? 1 : 0);return 1;}
int JASS_UnitDropItemSlot(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);int a2 = lua_tointeger(L, 3);lua_pushboolean(L, JASS_WRAPPER_UnitDropItemSlot(a0, a1, a2) ? 1 : 0);return 1;}
int JASS_UnitDropItemTarget(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);DWORD a2 = LUA_TODWORD(L, 3);lua_pushboolean(L, JASS_WRAPPER_UnitDropItemTarget(a0, a1, a2) ? 1 : 0);return 1;}
int JASS_UnitUseItem(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_pushboolean(L, JASS_WRAPPER_UnitUseItem(a0, a1) ? 1 : 0);return 1;}
int JASS_UnitUseItemPoint(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);lua_pushboolean(L, JASS_WRAPPER_UnitUseItemPoint(a0, a1, (float)a2, (float)a3) ? 1 : 0);return 1;}
int JASS_UnitUseItemTarget(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);DWORD a2 = LUA_TODWORD(L, 3);lua_pushboolean(L, JASS_WRAPPER_UnitUseItemTarget(a0, a1, a2) ? 1 : 0);return 1;}
int JASS_GetUnitCurrentOrder(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushinteger(L, JASS_WRAPPER_GetUnitCurrentOrder(a0));return 1;}
int JASS_SetResourceAmount(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);JASS_WRAPPER_SetResourceAmount(a0, a1);return 0;}
int JASS_AddResourceAmount(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);JASS_WRAPPER_AddResourceAmount(a0, a1);return 0;}
int JASS_GetResourceAmount(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushinteger(L, JASS_WRAPPER_GetResourceAmount(a0));return 1;}
int JASS_SelectUnit(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_SelectUnit(a0, a1);return 0;}
int JASS_ClearSelection(lua_State* L) {if (lua_gettop(L) != 0) return 0;JASS_WRAPPER_ClearSelection();return 0;}
int JASS_UnitAddIndicator(lua_State* L) {if (lua_gettop(L) != 5) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);int a3 = lua_tointeger(L, 4);int a4 = lua_tointeger(L, 5);JASS_WRAPPER_UnitAddIndicator(a0, a1, a2, a3, a4);return 0;}
int JASS_AddIndicator(lua_State* L) {if (lua_gettop(L) != 5) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);int a3 = lua_tointeger(L, 4);int a4 = lua_tointeger(L, 5);JASS_WRAPPER_AddIndicator(a0, a1, a2, a3, a4);return 0;}
int JASS_KillUnit(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_KillUnit(a0);return 0;}
int JASS_RemoveUnit(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_RemoveUnit(a0);return 0;}
int JASS_ShowUnit(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_ShowUnit(a0, a1);return 0;}
int JASS_IsUnitInForce(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_pushboolean(L, JASS_WRAPPER_IsUnitInForce(a0, a1) ? 1 : 0);return 1;}
int JASS_IsUnitInGroup(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_pushboolean(L, JASS_WRAPPER_IsUnitInGroup(a0, a1) ? 1 : 0);return 1;}
int JASS_IsUnitOwnedByPlayer(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_pushboolean(L, JASS_WRAPPER_IsUnitOwnedByPlayer(a0, a1) ? 1 : 0);return 1;}
int JASS_IsUnitAlly(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_pushboolean(L, JASS_WRAPPER_IsUnitAlly(a0, a1) ? 1 : 0);return 1;}
int JASS_IsUnitEnemy(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_pushboolean(L, JASS_WRAPPER_IsUnitEnemy(a0, a1) ? 1 : 0);return 1;}
int JASS_IsUnitVisible(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_pushboolean(L, JASS_WRAPPER_IsUnitVisible(a0, a1) ? 1 : 0);return 1;}
int JASS_IsUnitDetected(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_pushboolean(L, JASS_WRAPPER_IsUnitDetected(a0, a1) ? 1 : 0);return 1;}
int JASS_IsUnitInvisible(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_pushboolean(L, JASS_WRAPPER_IsUnitInvisible(a0, a1) ? 1 : 0);return 1;}
int JASS_IsUnitFogged(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_pushboolean(L, JASS_WRAPPER_IsUnitFogged(a0, a1) ? 1 : 0);return 1;}
int JASS_IsUnitMasked(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_pushboolean(L, JASS_WRAPPER_IsUnitMasked(a0, a1) ? 1 : 0);return 1;}
int JASS_IsUnitSelected(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_pushboolean(L, JASS_WRAPPER_IsUnitSelected(a0, a1) ? 1 : 0);return 1;}
int JASS_IsUnitRace(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_pushboolean(L, JASS_WRAPPER_IsUnitRace(a0, a1) ? 1 : 0);return 1;}
int JASS_IsUnitType(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_pushboolean(L, JASS_WRAPPER_IsUnitType(a0, a1) ? 1 : 0);return 1;}
int JASS_IsUnit(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_pushboolean(L, JASS_WRAPPER_IsUnit(a0, a1) ? 1 : 0);return 1;}
int JASS_IsUnitInRange(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_pushboolean(L, JASS_WRAPPER_IsUnitInRange(a0, a1, (float)a2) ? 1 : 0);return 1;}
int JASS_IsUnitInRangeXY(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);lua_pushboolean(L, JASS_WRAPPER_IsUnitInRangeXY(a0, (float)a1, (float)a2, (float)a3) ? 1 : 0);return 1;}
int JASS_IsUnitInRangeLoc(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_pushboolean(L, JASS_WRAPPER_IsUnitInRangeLoc(a0, a1, (float)a2) ? 1 : 0);return 1;}
int JASS_IsUnitHidden(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_IsUnitHidden(a0) ? 1 : 0);return 1;}
int JASS_IsUnitIllusion(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_IsUnitIllusion(a0) ? 1 : 0);return 1;}
int JASS_IsUnitInTransport(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_pushboolean(L, JASS_WRAPPER_IsUnitInTransport(a0, a1) ? 1 : 0);return 1;}
int JASS_IsUnitLoaded(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_IsUnitLoaded(a0) ? 1 : 0);return 1;}
int JASS_IsHeroUnitId(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);lua_pushboolean(L, JASS_WRAPPER_IsHeroUnitId(a0) ? 1 : 0);return 1;}
int JASS_Deg2Rad(lua_State* L) {if (lua_gettop(L) != 1) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_pushnumber(L, JASS_WRAPPER_Deg2Rad((float)a0));return 1;}
int JASS_Rad2Deg(lua_State* L) {if (lua_gettop(L) != 1) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_pushnumber(L, JASS_WRAPPER_Rad2Deg((float)a0));return 1;}
int JASS_Sin(lua_State* L) {if (lua_gettop(L) != 1) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_pushnumber(L, JASS_WRAPPER_Sin((float)a0));return 1;}
int JASS_Cos(lua_State* L) {if (lua_gettop(L) != 1) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_pushnumber(L, JASS_WRAPPER_Cos((float)a0));return 1;}
int JASS_Tan(lua_State* L) {if (lua_gettop(L) != 1) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_pushnumber(L, JASS_WRAPPER_Tan((float)a0));return 1;}
int JASS_Asin(lua_State* L) {if (lua_gettop(L) != 1) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_pushnumber(L, JASS_WRAPPER_Asin((float)a0));return 1;}
int JASS_Acos(lua_State* L) {if (lua_gettop(L) != 1) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_pushnumber(L, JASS_WRAPPER_Acos((float)a0));return 1;}
int JASS_Atan(lua_State* L) {if (lua_gettop(L) != 1) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_pushnumber(L, JASS_WRAPPER_Atan((float)a0));return 1;}
int JASS_Atan2(lua_State* L) {if (lua_gettop(L) != 2) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_pushnumber(L, JASS_WRAPPER_Atan2((float)a0, (float)a1));return 1;}
int JASS_SquareRoot(lua_State* L) {if (lua_gettop(L) != 1) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_pushnumber(L, JASS_WRAPPER_SquareRoot((float)a0));return 1;}
int JASS_Pow(lua_State* L) {if (lua_gettop(L) != 2) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_pushnumber(L, JASS_WRAPPER_Pow((float)a0, (float)a1));return 1;}
int JASS_I2R(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);lua_pushnumber(L, JASS_WRAPPER_I2R(a0));return 1;}
int JASS_R2I(lua_State* L) {if (lua_gettop(L) != 1) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_pushinteger(L, JASS_WRAPPER_R2I((float)a0));return 1;}
int JASS_I2S(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);lua_pushstring(L, JASS_WRAPPER_I2S(a0));return 1;}
int JASS_R2S(lua_State* L) {if (lua_gettop(L) != 1) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_pushstring(L, JASS_WRAPPER_R2S((float)a0));return 1;}
int JASS_R2SW(lua_State* L) {if (lua_gettop(L) != 3) return 0;lua_Number a0 = lua_tonumber(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);lua_pushstring(L, JASS_WRAPPER_R2SW((float)a0, a1, a2));return 1;}
int JASS_S2I(lua_State* L) {if (lua_gettop(L) != 1) return 0;const char* a0 = lua_tostring(L, 1);lua_pushinteger(L, JASS_WRAPPER_S2I(a0));return 1;}
int JASS_S2R(lua_State* L) {if (lua_gettop(L) != 1) return 0;const char* a0 = lua_tostring(L, 1);lua_pushnumber(L, JASS_WRAPPER_S2R(a0));return 1;}
int JASS_GetHandleId(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushinteger(L, JASS_WRAPPER_GetHandleId(a0));return 1;}
int JASS_SubString(lua_State* L) {if (lua_gettop(L) != 3) return 0;const char* a0 = lua_tostring(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);lua_pushstring(L, JASS_WRAPPER_SubString(a0, a1, a2));return 1;}
int JASS_StringLength(lua_State* L) {if (lua_gettop(L) != 1) return 0;const char* a0 = lua_tostring(L, 1);lua_pushinteger(L, JASS_WRAPPER_StringLength(a0));return 1;}
int JASS_StringCase(lua_State* L) {if (lua_gettop(L) != 2) return 0;const char* a0 = lua_tostring(L, 1);bool a1 = lua_toboolean(L, 2) > 0;lua_pushstring(L, JASS_WRAPPER_StringCase(a0, a1));return 1;}
int JASS_StringHash(lua_State* L) {if (lua_gettop(L) != 1) return 0;const char* a0 = lua_tostring(L, 1);lua_pushinteger(L, JASS_WRAPPER_StringHash(a0));return 1;}
int JASS_GetLocalizedString(lua_State* L) {if (lua_gettop(L) != 1) return 0;const char* a0 = lua_tostring(L, 1);lua_pushstring(L, JASS_WRAPPER_GetLocalizedString(a0));return 1;}
int JASS_GetLocalizedHotkey(lua_State* L) {if (lua_gettop(L) != 1) return 0;const char* a0 = lua_tostring(L, 1);lua_pushinteger(L, JASS_WRAPPER_GetLocalizedHotkey(a0));return 1;}
int JASS_ConvertRace(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertRace(a0));return 1;}
int JASS_ConvertAllianceType(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertAllianceType(a0));return 1;}
int JASS_ConvertRacePref(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertRacePref(a0));return 1;}
int JASS_ConvertIGameState(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertIGameState(a0));return 1;}
int JASS_ConvertFGameState(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertFGameState(a0));return 1;}
int JASS_ConvertPlayerState(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertPlayerState(a0));return 1;}
int JASS_ConvertPlayerScore(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertPlayerScore(a0));return 1;}
int JASS_ConvertStartLocPrio(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertStartLocPrio(a0));return 1;}
int JASS_ConvertPlayerGameResult(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertPlayerGameResult(a0));return 1;}
int JASS_ConvertUnitState(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertUnitState(a0));return 1;}
int JASS_ConvertAIDifficulty(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertAIDifficulty(a0));return 1;}
int JASS_ConvertGameEvent(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertGameEvent(a0));return 1;}
int JASS_ConvertPlayerEvent(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertPlayerEvent(a0));return 1;}
int JASS_ConvertPlayerUnitEvent(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertPlayerUnitEvent(a0));return 1;}
int JASS_ConvertUnitEvent(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertUnitEvent(a0));return 1;}
int JASS_ConvertWidgetEvent(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertWidgetEvent(a0));return 1;}
int JASS_ConvertDialogEvent(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertDialogEvent(a0));return 1;}
int JASS_ConvertLimitOp(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertLimitOp(a0));return 1;}
int JASS_ConvertUnitType(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertUnitType(a0));return 1;}
int JASS_ConvertGameSpeed(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertGameSpeed(a0));return 1;}
int JASS_ConvertPlacement(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertPlacement(a0));return 1;}
int JASS_ConvertGameDifficulty(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertGameDifficulty(a0));return 1;}
int JASS_ConvertGameType(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertGameType(a0));return 1;}
int JASS_ConvertMapFlag(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertMapFlag(a0));return 1;}
int JASS_ConvertMapVisibility(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertMapVisibility(a0));return 1;}
int JASS_ConvertMapSetting(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertMapSetting(a0));return 1;}
int JASS_ConvertMapDensity(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertMapDensity(a0));return 1;}
int JASS_ConvertMapControl(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertMapControl(a0));return 1;}
int JASS_ConvertPlayerColor(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertPlayerColor(a0));return 1;}
int JASS_ConvertPlayerSlotState(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertPlayerSlotState(a0));return 1;}
int JASS_ConvertVolumeGroup(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertVolumeGroup(a0));return 1;}
int JASS_ConvertCameraField(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertCameraField(a0));return 1;}
int JASS_ConvertBlendMode(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertBlendMode(a0));return 1;}
int JASS_ConvertRarityControl(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertRarityControl(a0));return 1;}
int JASS_ConvertTexMapFlags(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertTexMapFlags(a0));return 1;}
int JASS_ConvertFogState(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertFogState(a0));return 1;}
int JASS_ConvertEffectType(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertEffectType(a0));return 1;}
int JASS_ConvertVersion(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertVersion(a0));return 1;}
int JASS_ConvertItemType(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertItemType(a0));return 1;}
int JASS_ConvertAttackType(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertAttackType(a0));return 1;}
int JASS_ConvertDamageType(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertDamageType(a0));return 1;}
int JASS_ConvertWeaponType(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertWeaponType(a0));return 1;}
int JASS_ConvertSoundType(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertSoundType(a0));return 1;}
int JASS_ConvertPathingType(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_ConvertPathingType(a0));return 1;}
int JASS_SetMapName(lua_State* L) {if (lua_gettop(L) != 1) return 0;const char* a0 = lua_tostring(L, 1);JASS_WRAPPER_SetMapName(a0);return 0;}
int JASS_SetMapDescription(lua_State* L) {if (lua_gettop(L) != 1) return 0;const char* a0 = lua_tostring(L, 1);JASS_WRAPPER_SetMapDescription(a0);return 0;}
int JASS_SetTeams(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);JASS_WRAPPER_SetTeams(a0);return 0;}
int JASS_SetPlayers(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);JASS_WRAPPER_SetPlayers(a0);return 0;}
int JASS_SetGameTypeSupported(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_SetGameTypeSupported(a0, a1);return 0;}
int JASS_SetMapFlag(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_SetMapFlag(a0, a1);return 0;}
int JASS_SetGameSpeed(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_SetGameSpeed(a0);return 0;}
int JASS_SetGamePlacement(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_SetGamePlacement(a0);return 0;}
int JASS_SetGameDifficulty(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_SetGameDifficulty(a0);return 0;}
int JASS_SetResourceDensity(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_SetResourceDensity(a0);return 0;}
int JASS_SetCreatureDensity(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_SetCreatureDensity(a0);return 0;}
int JASS_DefineStartLocation(lua_State* L) {if (lua_gettop(L) != 3) return 0;int a0 = lua_tointeger(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);JASS_WRAPPER_DefineStartLocation(a0, (float)a1, (float)a2);return 0;}
int JASS_DefineStartLocationLoc(lua_State* L) {if (lua_gettop(L) != 2) return 0;int a0 = lua_tointeger(L, 1);DWORD a1 = LUA_TODWORD(L, 2);JASS_WRAPPER_DefineStartLocationLoc(a0, a1);return 0;}
int JASS_SetStartLocPrioCount(lua_State* L) {if (lua_gettop(L) != 2) return 0;int a0 = lua_tointeger(L, 1);int a1 = lua_tointeger(L, 2);JASS_WRAPPER_SetStartLocPrioCount(a0, a1);return 0;}
int JASS_SetStartLocPrio(lua_State* L) {if (lua_gettop(L) != 4) return 0;int a0 = lua_tointeger(L, 1);int a1 = lua_tointeger(L, 2);int a2 = lua_tointeger(L, 3);DWORD a3 = LUA_TODWORD(L, 4);JASS_WRAPPER_SetStartLocPrio(a0, a1, a2, a3);return 0;}
int JASS_GetStartLocPrioSlot(lua_State* L) {if (lua_gettop(L) != 2) return 0;int a0 = lua_tointeger(L, 1);int a1 = lua_tointeger(L, 2);lua_pushinteger(L, JASS_WRAPPER_GetStartLocPrioSlot(a0, a1));return 1;}
int JASS_GetStartLocPrio(lua_State* L) {if (lua_gettop(L) != 2) return 0;int a0 = lua_tointeger(L, 1);int a1 = lua_tointeger(L, 2);LUA_PUSHDWORD(L, JASS_WRAPPER_GetStartLocPrio(a0, a1));return 1;}
int JASS_GetTeams(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushinteger(L, JASS_WRAPPER_GetTeams());return 1;}
int JASS_GetPlayers(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushinteger(L, JASS_WRAPPER_GetPlayers());return 1;}
int JASS_IsGameTypeSupported(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_IsGameTypeSupported(a0) ? 1 : 0);return 1;}
int JASS_IsMapFlagSet(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_IsMapFlagSet(a0) ? 1 : 0);return 1;}
int JASS_GetGameTypeSelected(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetGameTypeSelected());return 1;}
int JASS_GetGamePlacement(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetGamePlacement());return 1;}
int JASS_GetGameSpeed(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetGameSpeed());return 1;}
int JASS_GetGameDifficulty(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetGameDifficulty());return 1;}
int JASS_GetResourceDensity(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetResourceDensity());return 1;}
int JASS_GetCreatureDensity(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetCreatureDensity());return 1;}
int JASS_GetStartLocationX(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetStartLocationX(a0));return 1;}
int JASS_GetStartLocationY(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetStartLocationY(a0));return 1;}
int JASS_GetStartLocationLoc(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_GetStartLocationLoc(a0));return 1;}
int JASS_SetPlayerTeam(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);JASS_WRAPPER_SetPlayerTeam(a0, a1);return 0;}
int JASS_SetPlayerStartLocation(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);JASS_WRAPPER_SetPlayerStartLocation(a0, a1);return 0;}
int JASS_ForcePlayerStartLocation(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);int a1 = lua_tointeger(L, 2);JASS_WRAPPER_ForcePlayerStartLocation(a0, a1);return 0;}
int JASS_SetPlayerAlliance(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);DWORD a2 = LUA_TODWORD(L, 3);bool a3 = lua_toboolean(L, 4) > 0;JASS_WRAPPER_SetPlayerAlliance(a0, a1, a2, a3);return 0;}
int JASS_SetPlayerTaxRate(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);DWORD a2 = LUA_TODWORD(L, 3);int a3 = lua_tointeger(L, 4);JASS_WRAPPER_SetPlayerTaxRate(a0, a1, a2, a3);return 0;}
int JASS_SetPlayerRacePreference(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);JASS_WRAPPER_SetPlayerRacePreference(a0, a1);return 0;}
int JASS_SetPlayerRaceSelectable(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_SetPlayerRaceSelectable(a0, a1);return 0;}
int JASS_SetPlayerController(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);JASS_WRAPPER_SetPlayerController(a0, a1);return 0;}
int JASS_SetPlayerColor(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);JASS_WRAPPER_SetPlayerColor(a0, a1);return 0;}
int JASS_SetPlayerOnScoreScreen(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_SetPlayerOnScoreScreen(a0, a1);return 0;}
int JASS_SetPlayerName(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);JASS_WRAPPER_SetPlayerName(a0, a1);return 0;}
int JASS_GetPlayerTeam(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushinteger(L, JASS_WRAPPER_GetPlayerTeam(a0));return 1;}
int JASS_GetPlayerName(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushstring(L, JASS_WRAPPER_GetPlayerName(a0));return 1;}
int JASS_GetPlayerStartLocation(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushinteger(L, JASS_WRAPPER_GetPlayerStartLocation(a0));return 1;}
int JASS_GetPlayerStartLocationX(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetPlayerStartLocationX(a0));return 1;}
int JASS_GetPlayerStartLocationY(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetPlayerStartLocationY(a0));return 1;}
int JASS_GetPlayerColor(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_GetPlayerColor(a0));return 1;}
int JASS_GetPlayerSelectable(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_GetPlayerSelectable(a0) ? 1 : 0);return 1;}
int JASS_GetPlayerController(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_GetPlayerController(a0));return 1;}
int JASS_GetPlayerSlotState(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_GetPlayerSlotState(a0));return 1;}
int JASS_GetPlayerTaxRate(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);DWORD a2 = LUA_TODWORD(L, 3);lua_pushinteger(L, JASS_WRAPPER_GetPlayerTaxRate(a0, a1, a2));return 1;}
int JASS_IsPlayerRacePrefSet(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_pushboolean(L, JASS_WRAPPER_IsPlayerRacePrefSet(a0, a1) ? 1 : 0);return 1;}
int JASS_Location(lua_State* L) {if (lua_gettop(L) != 2) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);LUA_PUSHDWORD(L, JASS_WRAPPER_Location((float)a0, (float)a1));return 1;}
int JASS_RemoveLocation(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_RemoveLocation(a0);return 0;}
int JASS_MoveLocation(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);JASS_WRAPPER_MoveLocation(a0, (float)a1, (float)a2);return 0;}
int JASS_GetLocationX(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetLocationX(a0));return 1;}
int JASS_GetLocationY(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetLocationY(a0));return 1;}
int JASS_GetLocationZ(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetLocationZ(a0));return 1;}
int JASS_CreateTimer(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_CreateTimer());return 1;}
int JASS_DestroyTimer(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_DestroyTimer(a0);return 0;}
int JASS_TimerStart(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);bool a2 = lua_toboolean(L, 3) > 0;DWORD a3 = LUA_TODWORD(L, 4);JASS_WRAPPER_TimerStart(a0, (float)a1, a2, a3);return 0;}
int JASS_TimerGetTimeout(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_TimerGetTimeout(a0));return 1;}
int JASS_TimerGetElapsed(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_TimerGetElapsed(a0));return 1;}
int JASS_TimerGetRemaining(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_TimerGetRemaining(a0));return 1;}
int JASS_PauseTimer(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_PauseTimer(a0);return 0;}
int JASS_ResumeTimer(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_ResumeTimer(a0);return 0;}
int JASS_GetExpiredTimer(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetExpiredTimer());return 1;}
int JASS_Condition(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_Condition(a0));return 1;}
int JASS_DestroyCondition(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_DestroyCondition(a0);return 0;}
int JASS_Filter(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_Filter(a0));return 1;}
int JASS_DestroyFilter(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_DestroyFilter(a0);return 0;}
int JASS_DestroyBoolExpr(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_DestroyBoolExpr(a0);return 0;}
int JASS_And(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);LUA_PUSHDWORD(L, JASS_WRAPPER_And(a0, a1));return 1;}
int JASS_Or(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);LUA_PUSHDWORD(L, JASS_WRAPPER_Or(a0, a1));return 1;}
int JASS_Not(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);LUA_PUSHDWORD(L, JASS_WRAPPER_Not(a0));return 1;}
int JASS_CreateRegion(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_CreateRegion());return 1;}
int JASS_RemoveRegion(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_RemoveRegion(a0);return 0;}
int JASS_RegionAddRect(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);JASS_WRAPPER_RegionAddRect(a0, a1);return 0;}
int JASS_RegionClearRect(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);JASS_WRAPPER_RegionClearRect(a0, a1);return 0;}
int JASS_RegionAddCell(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);JASS_WRAPPER_RegionAddCell(a0, (float)a1, (float)a2);return 0;}
int JASS_RegionAddCellAtLoc(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);JASS_WRAPPER_RegionAddCellAtLoc(a0, a1);return 0;}
int JASS_RegionClearCell(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);JASS_WRAPPER_RegionClearCell(a0, (float)a1, (float)a2);return 0;}
int JASS_RegionClearCellAtLoc(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);JASS_WRAPPER_RegionClearCellAtLoc(a0, a1);return 0;}
int JASS_IsUnitInRegion(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_pushboolean(L, JASS_WRAPPER_IsUnitInRegion(a0, a1) ? 1 : 0);return 1;}
int JASS_IsPointInRegion(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_pushboolean(L, JASS_WRAPPER_IsPointInRegion(a0, (float)a1, (float)a2) ? 1 : 0);return 1;}
int JASS_IsLocationInRegion(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_pushboolean(L, JASS_WRAPPER_IsLocationInRegion(a0, a1) ? 1 : 0);return 1;}
int JASS_Rect(lua_State* L) {if (lua_gettop(L) != 4) return 0;lua_Number a0 = lua_tonumber(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);LUA_PUSHDWORD(L, JASS_WRAPPER_Rect((float)a0, (float)a1, (float)a2, (float)a3));return 1;}
int JASS_RectFromLoc(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);LUA_PUSHDWORD(L, JASS_WRAPPER_RectFromLoc(a0, a1));return 1;}
int JASS_RemoveRect(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_RemoveRect(a0);return 0;}
int JASS_SetRect(lua_State* L) {if (lua_gettop(L) != 5) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);lua_Number a4 = lua_tonumber(L, 5);JASS_WRAPPER_SetRect(a0, (float)a1, (float)a2, (float)a3, (float)a4);return 0;}
int JASS_SetRectFromLoc(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);DWORD a2 = LUA_TODWORD(L, 3);JASS_WRAPPER_SetRectFromLoc(a0, a1, a2);return 0;}
int JASS_GetRectCenterX(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetRectCenterX(a0));return 1;}
int JASS_GetRectCenterY(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetRectCenterY(a0));return 1;}
int JASS_MoveRectTo(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);lua_Number a2 = lua_tonumber(L, 3);JASS_WRAPPER_MoveRectTo(a0, (float)a1, (float)a2);return 0;}
int JASS_MoveRectToLoc(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);JASS_WRAPPER_MoveRectToLoc(a0, a1);return 0;}
int JASS_GetRectMinX(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetRectMinX(a0));return 1;}
int JASS_GetRectMinY(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetRectMinY(a0));return 1;}
int JASS_GetRectMaxX(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetRectMaxX(a0));return 1;}
int JASS_GetRectMaxY(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushnumber(L, JASS_WRAPPER_GetRectMaxY(a0));return 1;}
int JASS_GetWorldBounds(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetWorldBounds());return 1;}
int JASS_SetFogStateRect(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);DWORD a2 = LUA_TODWORD(L, 3);bool a3 = lua_toboolean(L, 4) > 0;JASS_WRAPPER_SetFogStateRect(a0, a1, a2, a3);return 0;}
int JASS_SetFogStateRadius(lua_State* L) {if (lua_gettop(L) != 6) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);lua_Number a4 = lua_tonumber(L, 5);bool a5 = lua_toboolean(L, 6) > 0;JASS_WRAPPER_SetFogStateRadius(a0, a1, (float)a2, (float)a3, (float)a4, a5);return 0;}
int JASS_SetFogStateRadiusLoc(lua_State* L) {if (lua_gettop(L) != 5) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);DWORD a2 = LUA_TODWORD(L, 3);lua_Number a3 = lua_tonumber(L, 4);bool a4 = lua_toboolean(L, 5) > 0;JASS_WRAPPER_SetFogStateRadiusLoc(a0, a1, a2, (float)a3, a4);return 0;}
int JASS_FogMaskEnable(lua_State* L) {if (lua_gettop(L) != 1) return 0;bool a0 = lua_toboolean(L, 1) > 0;JASS_WRAPPER_FogMaskEnable(a0);return 0;}
int JASS_IsFogMaskEnabled(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushboolean(L, JASS_WRAPPER_IsFogMaskEnabled() ? 1 : 0);return 1;}
int JASS_FogEnable(lua_State* L) {if (lua_gettop(L) != 1) return 0;bool a0 = lua_toboolean(L, 1) > 0;JASS_WRAPPER_FogEnable(a0);return 0;}
int JASS_IsFogEnabled(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushboolean(L, JASS_WRAPPER_IsFogEnabled() ? 1 : 0);return 1;}
int JASS_CreateFogModifierRect(lua_State* L) {if (lua_gettop(L) != 5) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);DWORD a2 = LUA_TODWORD(L, 3);bool a3 = lua_toboolean(L, 4) > 0;bool a4 = lua_toboolean(L, 5) > 0;LUA_PUSHDWORD(L, JASS_WRAPPER_CreateFogModifierRect(a0, a1, a2, a3, a4));return 1;}
int JASS_CreateFogModifierRadius(lua_State* L) {if (lua_gettop(L) != 7) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);lua_Number a2 = lua_tonumber(L, 3);lua_Number a3 = lua_tonumber(L, 4);lua_Number a4 = lua_tonumber(L, 5);bool a5 = lua_toboolean(L, 6) > 0;bool a6 = lua_toboolean(L, 7) > 0;LUA_PUSHDWORD(L, JASS_WRAPPER_CreateFogModifierRadius(a0, a1, (float)a2, (float)a3, (float)a4, a5, a6));return 1;}
int JASS_CreateFogModifierRadiusLoc(lua_State* L) {if (lua_gettop(L) != 6) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);DWORD a2 = LUA_TODWORD(L, 3);lua_Number a3 = lua_tonumber(L, 4);bool a4 = lua_toboolean(L, 5) > 0;bool a5 = lua_toboolean(L, 6) > 0;LUA_PUSHDWORD(L, JASS_WRAPPER_CreateFogModifierRadiusLoc(a0, a1, a2, (float)a3, a4, a5));return 1;}
int JASS_DestroyFogModifier(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_DestroyFogModifier(a0);return 0;}
int JASS_FogModifierStart(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_FogModifierStart(a0);return 0;}
int JASS_FogModifierStop(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_FogModifierStop(a0);return 0;}
int JASS_CreateTrigger(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_CreateTrigger());return 1;}
int JASS_DestroyTrigger(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_DestroyTrigger(a0);return 0;}
int JASS_ResetTrigger(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_ResetTrigger(a0);return 0;}
int JASS_EnableTrigger(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_EnableTrigger(a0);return 0;}
int JASS_DisableTrigger(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);JASS_WRAPPER_DisableTrigger(a0);return 0;}
int JASS_IsTriggerEnabled(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_IsTriggerEnabled(a0) ? 1 : 0);return 1;}
int JASS_TriggerWaitOnSleeps(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);bool a1 = lua_toboolean(L, 2) > 0;JASS_WRAPPER_TriggerWaitOnSleeps(a0, a1);return 0;}
int JASS_IsTriggerWaitOnSleeps(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushboolean(L, JASS_WRAPPER_IsTriggerWaitOnSleeps(a0) ? 1 : 0);return 1;}
int JASS_TriggerRegisterVariableEvent(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);const char* a1 = lua_tostring(L, 2);DWORD a2 = LUA_TODWORD(L, 3);lua_Number a3 = lua_tonumber(L, 4);LUA_PUSHDWORD(L, JASS_WRAPPER_TriggerRegisterVariableEvent(a0, a1, a2, (float)a3));return 1;}
int JASS_TriggerRegisterTimerEvent(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_Number a1 = lua_tonumber(L, 2);bool a2 = lua_toboolean(L, 3) > 0;LUA_PUSHDWORD(L, JASS_WRAPPER_TriggerRegisterTimerEvent(a0, (float)a1, a2));return 1;}
int JASS_TriggerRegisterTimerExpireEvent(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);LUA_PUSHDWORD(L, JASS_WRAPPER_TriggerRegisterTimerExpireEvent(a0, a1));return 1;}
int JASS_TriggerRegisterGameStateEvent(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);DWORD a2 = LUA_TODWORD(L, 3);lua_Number a3 = lua_tonumber(L, 4);LUA_PUSHDWORD(L, JASS_WRAPPER_TriggerRegisterGameStateEvent(a0, a1, a2, (float)a3));return 1;}
int JASS_GetEventGameState(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetEventGameState());return 1;}
int JASS_TriggerRegisterDialogEvent(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);LUA_PUSHDWORD(L, JASS_WRAPPER_TriggerRegisterDialogEvent(a0, a1));return 1;}
int JASS_TriggerRegisterDialogButtonEvent(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);LUA_PUSHDWORD(L, JASS_WRAPPER_TriggerRegisterDialogButtonEvent(a0, a1));return 1;}
int JASS_GetClickedButton(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetClickedButton());return 1;}
int JASS_GetClickedDialog(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetClickedDialog());return 1;}
int JASS_GetTournamentFinishSoonTimeRemaining(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushnumber(L, JASS_WRAPPER_GetTournamentFinishSoonTimeRemaining());return 1;}
int JASS_GetTournamentFinishNowRule(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushinteger(L, JASS_WRAPPER_GetTournamentFinishNowRule());return 1;}
int JASS_GetTournamentFinishNowPlayer(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetTournamentFinishNowPlayer());return 1;}
int JASS_GetTournamentScore(lua_State* L) {if (lua_gettop(L) != 1) return 0;DWORD a0 = LUA_TODWORD(L, 1);lua_pushinteger(L, JASS_WRAPPER_GetTournamentScore(a0));return 1;}
int JASS_GetSaveBasicFilename(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushstring(L, JASS_WRAPPER_GetSaveBasicFilename());return 1;}
int JASS_TriggerRegisterGameEvent(lua_State* L) {if (lua_gettop(L) != 2) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);LUA_PUSHDWORD(L, JASS_WRAPPER_TriggerRegisterGameEvent(a0, a1));return 1;}
int JASS_GetWinningPlayer(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetWinningPlayer());return 1;}
int JASS_TriggerRegisterPlayerStateEvent(lua_State* L) {if (lua_gettop(L) != 5) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);DWORD a2 = LUA_TODWORD(L, 3);DWORD a3 = LUA_TODWORD(L, 4);lua_Number a4 = lua_tonumber(L, 5);LUA_PUSHDWORD(L, JASS_WRAPPER_TriggerRegisterPlayerStateEvent(a0, a1, a2, a3, (float)a4));return 1;}
int JASS_GetEventPlayerState(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetEventPlayerState());return 1;}
int JASS_TriggerRegisterPlayerEvent(lua_State* L) {if (lua_gettop(L) != 3) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);DWORD a2 = LUA_TODWORD(L, 3);LUA_PUSHDWORD(L, JASS_WRAPPER_TriggerRegisterPlayerEvent(a0, a1, a2));return 1;}
int JASS_TriggerRegisterPlayerUnitEvent(lua_State* L) {if (lua_gettop(L) != 4) return 0;DWORD a0 = LUA_TODWORD(L, 1);DWORD a1 = LUA_TODWORD(L, 2);DWORD a2 = LUA_TODWORD(L, 3);DWORD a3 = LUA_TODWORD(L, 4);LUA_PUSHDWORD(L, JASS_WRAPPER_TriggerRegisterPlayerUnitEvent(a0, a1, a2, a3));return 1;}
int JASS_GetAttacker(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetAttacker());return 1;}
int JASS_GetRescuer(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetRescuer());return 1;}
int JASS_GetDyingUnit(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetDyingUnit());return 1;}
int JASS_GetKillingUnit(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetKillingUnit());return 1;}
int JASS_GetDecayingUnit(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetDecayingUnit());return 1;}
int JASS_GetConstructingStructure(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetConstructingStructure());return 1;}
int JASS_GetCancelledStructure(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetCancelledStructure());return 1;}
int JASS_GetConstructedStructure(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetConstructedStructure());return 1;}
int JASS_GetTrainedUnitType(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushinteger(L, JASS_WRAPPER_GetTrainedUnitType());return 1;}
int JASS_GetResearchingUnit(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetResearchingUnit());return 1;}
int JASS_GetResearched(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushinteger(L, JASS_WRAPPER_GetResearched());return 1;}
int JASS_GetTrainedUnit(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetTrainedUnit());return 1;}
int JASS_GetSellingUnit(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetSellingUnit());return 1;}
int JASS_GetSoldUnit(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetSoldUnit());return 1;}
int JASS_GetBuyingUnit(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetBuyingUnit());return 1;}
int JASS_GetSoldItem(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetSoldItem());return 1;}
int JASS_GetChangingUnit(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetChangingUnit());return 1;}
int JASS_GetChangingUnitPrevOwner(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetChangingUnitPrevOwner());return 1;}
int JASS_GetDetectedUnit(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetDetectedUnit());return 1;}
int JASS_GetOrderedUnit(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetOrderedUnit());return 1;}
int JASS_OrderId(lua_State* L) {if (lua_gettop(L) != 1) return 0;const char* a0 = lua_tostring(L, 1);lua_pushinteger(L, JASS_WRAPPER_OrderId(a0));return 1;}
int JASS_OrderId2String(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);lua_pushstring(L, JASS_WRAPPER_OrderId2String(a0));return 1;}
int JASS_AbilityId(lua_State* L) {if (lua_gettop(L) != 1) return 0;const char* a0 = lua_tostring(L, 1);lua_pushinteger(L, JASS_WRAPPER_AbilityId(a0));return 1;}
int JASS_AbilityId2String(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);lua_pushstring(L, JASS_WRAPPER_AbilityId2String(a0));return 1;}
int JASS_UnitId(lua_State* L) {if (lua_gettop(L) != 1) return 0;const char* a0 = lua_tostring(L, 1);lua_pushinteger(L, JASS_WRAPPER_UnitId(a0));return 1;}
int JASS_UnitId2String(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);lua_pushstring(L, JASS_WRAPPER_UnitId2String(a0));return 1;}
int JASS_GetObjectName(lua_State* L) {if (lua_gettop(L) != 1) return 0;int a0 = lua_tointeger(L, 1);lua_pushstring(L, JASS_WRAPPER_GetObjectName(a0));return 1;}
int JASS_GetIssuedOrderId(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushinteger(L, JASS_WRAPPER_GetIssuedOrderId());return 1;}
int JASS_GetOrderPointX(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushnumber(L, JASS_WRAPPER_GetOrderPointX());return 1;}
int JASS_GetOrderPointY(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushnumber(L, JASS_WRAPPER_GetOrderPointY());return 1;}
int JASS_GetOrderPointLoc(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetOrderPointLoc());return 1;}
int JASS_GetOrderTarget(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetOrderTarget());return 1;}
int JASS_GetOrderTargetDestructable(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetOrderTargetDestructable());return 1;}
int JASS_GetOrderTargetItem(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetOrderTargetItem());return 1;}
int JASS_GetOrderTargetUnit(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetOrderTargetUnit());return 1;}
int JASS_GetSpellAbilityUnit(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetSpellAbilityUnit());return 1;}
int JASS_GetSpellAbilityId(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushinteger(L, JASS_WRAPPER_GetSpellAbilityId());return 1;}
int JASS_GetSpellAbility(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetSpellAbility());return 1;}
int JASS_GetSpellTargetLoc(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetSpellTargetLoc());return 1;}
int JASS_GetSpellTargetX(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushnumber(L, JASS_WRAPPER_GetSpellTargetX());return 1;}
int JASS_GetSpellTargetY(lua_State* L) {if (lua_gettop(L) != 0) return 0;lua_pushnumber(L, JASS_WRAPPER_GetSpellTargetY());return 1;}
int JASS_GetSpellTargetDestructable(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetSpellTargetDestructable());return 1;}
int JASS_GetSpellTargetItem(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetSpellTargetItem());return 1;}
int JASS_GetSpellTargetUnit(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetSpellTargetUnit());return 1;}
int JASS_GetLevelingUnit(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetLevelingUnit());return 1;}
int JASS_GetLearningUnit(lua_State* L) {if (lua_gettop(L) != 0) return 0;LUA_PUSHDWORD(L, JASS_WRAPPER_GetLearningUnit());return 1;}
