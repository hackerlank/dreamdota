lua_register(L, "SetReplacementCount", JASS_SetReplacementCount);
,
lua_register(L, "PurchaseZeppelin", JASS_PurchaseZeppelin);
,
lua_register(L, "MeleeDifficulty", JASS_MeleeDifficulty);
,
lua_register(L, "DebugBreak", JASS_DebugBreak);
,
lua_register(L, "SetCineFilterTexMapFlags", JASS_SetCineFilterTexMapFlags);
,
lua_register(L, "SetCineFilterStartUV", JASS_SetCineFilterStartUV);
,
lua_register(L, "SetCineFilterEndUV", JASS_SetCineFilterEndUV);
,
lua_register(L, "SetCineFilterStartColor", JASS_SetCineFilterStartColor);
,
lua_register(L, "SetCineFilterEndColor", JASS_SetCineFilterEndColor);
,
lua_register(L, "SetCineFilterDuration", JASS_SetCineFilterDuration);
,
lua_register(L, "SetCinematicScene", JASS_SetCinematicScene);
,
lua_register(L, "EndCinematicScene", JASS_EndCinematicScene);
,
lua_register(L, "NewSoundEnvironment", JASS_NewSoundEnvironment);
,
lua_register(L, "CreateMIDISound", JASS_CreateMIDISound);
,
lua_register(L, "SetStackedSound", JASS_SetStackedSound);
,
lua_register(L, "ClearStackedSound", JASS_ClearStackedSound);
,
lua_register(L, "SetStackedSoundRect", JASS_SetStackedSoundRect);
,
lua_register(L, "ClearStackedSoundRect", JASS_ClearStackedSoundRect);
,
lua_register(L, "SetSoundParamsFromLabel", JASS_SetSoundParamsFromLabel);
,
lua_register(L, "SetSoundChannel", JASS_SetSoundChannel);
,
lua_register(L, "SetSoundVolume", JASS_SetSoundVolume);
,
lua_register(L, "SetSoundPitch", JASS_SetSoundPitch);
,
lua_register(L, "SetSoundPlayPosition", JASS_SetSoundPlayPosition);
,
lua_register(L, "SetSoundDistances", JASS_SetSoundDistances);
,
lua_register(L, "SetSoundDistanceCutoff", JASS_SetSoundDistanceCutoff);
,
lua_register(L, "SetSoundConeAngles", JASS_SetSoundConeAngles);
,
lua_register(L, "SetSoundConeOrientation", JASS_SetSoundConeOrientation);
,
lua_register(L, "SetSoundPosition", JASS_SetSoundPosition);
,
lua_register(L, "SetSoundVelocity", JASS_SetSoundVelocity);
,
lua_register(L, "AttachSoundToUnit", JASS_AttachSoundToUnit);
,
lua_register(L, "StartSound", JASS_StartSound);
,
lua_register(L, "KillSoundWhenDone", JASS_KillSoundWhenDone);
,
lua_register(L, "ClearMapMusic", JASS_ClearMapMusic);
,
lua_register(L, "PlayMusic", JASS_PlayMusic);
,
lua_register(L, "PlayMusicEx", JASS_PlayMusicEx);
,
lua_register(L, "ResumeMusic", JASS_ResumeMusic);
,
lua_register(L, "PlayThematicMusic", JASS_PlayThematicMusic);
,
lua_register(L, "PlayThematicMusicEx", JASS_PlayThematicMusicEx);
,
lua_register(L, "EndThematicMusic", JASS_EndThematicMusic);
,
lua_register(L, "SetMusicVolume", JASS_SetMusicVolume);
,
lua_register(L, "SetMusicPlayPosition", JASS_SetMusicPlayPosition);
,
lua_register(L, "SetThematicMusicPlayPosition", JASS_SetThematicMusicPlayPosition);
,
lua_register(L, "SetSoundDuration", JASS_SetSoundDuration);
,
lua_register(L, "GetSoundDuration", JASS_GetSoundDuration);
,
lua_register(L, "GetSoundFileDuration", JASS_GetSoundFileDuration);
,
lua_register(L, "AddWeatherEffect", JASS_AddWeatherEffect);
,
lua_register(L, "RemoveWeatherEffect", JASS_RemoveWeatherEffect);
,
lua_register(L, "TerrainDeformWave", JASS_TerrainDeformWave);
,
lua_register(L, "TerrainDeformRandom", JASS_TerrainDeformRandom);
,
lua_register(L, "TerrainDeformStop", JASS_TerrainDeformStop);
,
lua_register(L, "TerrainDeformStopAll", JASS_TerrainDeformStopAll);
,
lua_register(L, "DestroyEffect", JASS_DestroyEffect);
,
lua_register(L, "AddSpecialEffect", JASS_AddSpecialEffect);
,
lua_register(L, "AddSpecialEffectLoc", JASS_AddSpecialEffectLoc);
,
lua_register(L, "AddSpecialEffectTarget", JASS_AddSpecialEffectTarget);
,
lua_register(L, "AddSpellEffect", JASS_AddSpellEffect);
,
lua_register(L, "AddSpellEffectLoc", JASS_AddSpellEffectLoc);
,
lua_register(L, "AddSpellEffectById", JASS_AddSpellEffectById);
,
lua_register(L, "AddSpellEffectByIdLoc", JASS_AddSpellEffectByIdLoc);
,
lua_register(L, "AddSpellEffectTarget", JASS_AddSpellEffectTarget);
,
lua_register(L, "AddSpellEffectTargetById", JASS_AddSpellEffectTargetById);
,
lua_register(L, "GetLightningColorA", JASS_GetLightningColorA);
,
lua_register(L, "GetLightningColorR", JASS_GetLightningColorR);
,
lua_register(L, "GetLightningColorG", JASS_GetLightningColorG);
,
lua_register(L, "GetLightningColorB", JASS_GetLightningColorB);
,
lua_register(L, "GetAbilityEffect", JASS_GetAbilityEffect);
,
lua_register(L, "GetAbilityEffectById", JASS_GetAbilityEffectById);
,
lua_register(L, "GetAbilitySound", JASS_GetAbilitySound);
,
lua_register(L, "GetAbilitySoundById", JASS_GetAbilitySoundById);
,
lua_register(L, "GetTerrainCliffLevel", JASS_GetTerrainCliffLevel);
,
lua_register(L, "SetWaterBaseColor", JASS_SetWaterBaseColor);
,
lua_register(L, "GetTerrainType", JASS_GetTerrainType);
,
lua_register(L, "GetTerrainVariance", JASS_GetTerrainVariance);
,
lua_register(L, "SetTerrainType", JASS_SetTerrainType);
,
lua_register(L, "CreateImage", JASS_CreateImage);
,
lua_register(L, "DestroyImage", JASS_DestroyImage);
,
lua_register(L, "SetImagePosition", JASS_SetImagePosition);
,
lua_register(L, "SetImageColor", JASS_SetImageColor);
,
lua_register(L, "SetImageType", JASS_SetImageType);
,
lua_register(L, "DestroyUbersplat", JASS_DestroyUbersplat);
,
lua_register(L, "ResetUbersplat", JASS_ResetUbersplat);
,
lua_register(L, "FinishUbersplat", JASS_FinishUbersplat);
,
lua_register(L, "CreateBlightedGoldmine", JASS_CreateBlightedGoldmine);
,
lua_register(L, "StartMeleeAI", JASS_StartMeleeAI);
,
lua_register(L, "StartCampaignAI", JASS_StartCampaignAI);
,
lua_register(L, "CommandAI", JASS_CommandAI);
,
lua_register(L, "GetAIDifficulty", JASS_GetAIDifficulty);
,
lua_register(L, "RemoveGuardPosition", JASS_RemoveGuardPosition);
,
lua_register(L, "RecycleGuardPosition", JASS_RecycleGuardPosition);
,
lua_register(L, "RemoveAllGuardPositions", JASS_RemoveAllGuardPositions);
,
lua_register(L, "ExecuteFunc", JASS_ExecuteFunc);
,
lua_register(L, "Cheat", JASS_Cheat);
,
lua_register(L, "Preload", JASS_Preload);
,
lua_register(L, "PreloadEnd", JASS_PreloadEnd);
,
lua_register(L, "PreloadStart", JASS_PreloadStart);
,
lua_register(L, "PreloadRefresh", JASS_PreloadRefresh);
,
lua_register(L, "PreloadEndEx", JASS_PreloadEndEx);
,
lua_register(L, "PreloadGenStart", JASS_PreloadGenStart);
,
lua_register(L, "PreloadGenClear", JASS_PreloadGenClear);
,
lua_register(L, "PreloadGenEnd", JASS_PreloadGenEnd);
,
lua_register(L, "Preloader", JASS_Preloader);
,
lua_register(L, "DebugS", JASS_DebugS);
,
lua_register(L, "DebugFI", JASS_DebugFI);
,
lua_register(L, "DebugUnitID", JASS_DebugUnitID);
,
lua_register(L, "DisplayText", JASS_DisplayText);
,
lua_register(L, "DisplayTextI", JASS_DisplayTextI);
,
lua_register(L, "DisplayTextII", JASS_DisplayTextII);
,
lua_register(L, "DisplayTextIII", JASS_DisplayTextIII);
,
lua_register(L, "SuicideUnit", JASS_SuicideUnit);
,
lua_register(L, "SuicideUnitEx", JASS_SuicideUnitEx);
,
lua_register(L, "Sleep", JASS_Sleep);
,
lua_register(L, "GetAiPlayer", JASS_GetAiPlayer);
,
lua_register(L, "GetHeroId", JASS_GetHeroId);
,
lua_register(L, "GetHeroLevelAI", JASS_GetHeroLevelAI);
,
lua_register(L, "GetUnitCount", JASS_GetUnitCount);
,
lua_register(L, "GetPlayerUnitTypeCount", JASS_GetPlayerUnitTypeCount);
,
lua_register(L, "GetUnitCountDone", JASS_GetUnitCountDone);
,
lua_register(L, "GetUpgradeLevel", JASS_GetUpgradeLevel);
,
lua_register(L, "GetUnitGoldCost", JASS_GetUnitGoldCost);
,
lua_register(L, "GetUnitWoodCost", JASS_GetUnitWoodCost);
,
lua_register(L, "GetUnitBuildTime", JASS_GetUnitBuildTime);
,
lua_register(L, "GetUpgradeGoldCost", JASS_GetUpgradeGoldCost);
,
lua_register(L, "GetUpgradeWoodCost", JASS_GetUpgradeWoodCost);
,
lua_register(L, "GetEnemyPower", JASS_GetEnemyPower);
,
lua_register(L, "GetMinesOwned", JASS_GetMinesOwned);
,
lua_register(L, "GetGoldOwned", JASS_GetGoldOwned);
,
lua_register(L, "TownWithMine", JASS_TownWithMine);
,
lua_register(L, "GetNextExpansion", JASS_GetNextExpansion);
,
lua_register(L, "GetExpansionPeon", JASS_GetExpansionPeon);
,
lua_register(L, "GetEnemyExpansion", JASS_GetEnemyExpansion);
,
lua_register(L, "GetBuilding", JASS_GetBuilding);
,
lua_register(L, "SetAllianceTarget", JASS_SetAllianceTarget);
,
lua_register(L, "GetAllianceTarget", JASS_GetAllianceTarget);
,
lua_register(L, "Unsummon", JASS_Unsummon);
,
lua_register(L, "ClearHarvestAI", JASS_ClearHarvestAI);
,
lua_register(L, "HarvestGold", JASS_HarvestGold);
,
lua_register(L, "HarvestWood", JASS_HarvestWood);
,
lua_register(L, "StopGathering", JASS_StopGathering);
,
lua_register(L, "AddGuardPost", JASS_AddGuardPost);
,
lua_register(L, "FillGuardPosts", JASS_FillGuardPosts);
,
lua_register(L, "ReturnGuardPosts", JASS_ReturnGuardPosts);
,
lua_register(L, "CreateCaptains", JASS_CreateCaptains);
,
lua_register(L, "SetCaptainHome", JASS_SetCaptainHome);
,
lua_register(L, "ResetCaptainLocs", JASS_ResetCaptainLocs);
,
lua_register(L, "ShiftTownSpot", JASS_ShiftTownSpot);
,
lua_register(L, "TeleportCaptain", JASS_TeleportCaptain);
,
lua_register(L, "ClearCaptainTargets", JASS_ClearCaptainTargets);
,
lua_register(L, "CaptainVsUnits", JASS_CaptainVsUnits);
,
lua_register(L, "CaptainVsPlayer", JASS_CaptainVsPlayer);
,
lua_register(L, "CaptainAttack", JASS_CaptainAttack);
,
lua_register(L, "CaptainGoHome", JASS_CaptainGoHome);
,
lua_register(L, "CaptainReadiness", JASS_CaptainReadiness);
,
lua_register(L, "CaptainReadinessHP", JASS_CaptainReadinessHP);
,
lua_register(L, "CaptainReadinessMa", JASS_CaptainReadinessMa);
,
lua_register(L, "RemoveInjuries", JASS_RemoveInjuries);
,
lua_register(L, "RemoveSiege", JASS_RemoveSiege);
,
lua_register(L, "DisablePathing", JASS_DisablePathing);
,
lua_register(L, "SetAmphibious", JASS_SetAmphibious);
,
lua_register(L, "InitAssault", JASS_InitAssault);
,
lua_register(L, "StartGetEnemyBase", JASS_StartGetEnemyBase);
,
lua_register(L, "GetMegaTarget", JASS_GetMegaTarget);
,
lua_register(L, "GetEnemyBase", JASS_GetEnemyBase);
,
lua_register(L, "GetExpansionFoe", JASS_GetExpansionFoe);
,
lua_register(L, "GetExpansionX", JASS_GetExpansionX);
,
lua_register(L, "GetExpansionY", JASS_GetExpansionY);
,
lua_register(L, "SetStagePoint", JASS_SetStagePoint);
,
lua_register(L, "AttackMoveKill", JASS_AttackMoveKill);
,
lua_register(L, "AttackMoveXY", JASS_AttackMoveXY);
,
lua_register(L, "LoadZepWave", JASS_LoadZepWave);
,
lua_register(L, "IgnoredUnits", JASS_IgnoredUnits);
,
lua_register(L, "CommandsWaiting", JASS_CommandsWaiting);
,
lua_register(L, "GetLastCommand", JASS_GetLastCommand);
,
lua_register(L, "GetLastData", JASS_GetLastData);
,
lua_register(L, "PopLastCommand", JASS_PopLastCommand);
,
lua_register(L, "SetCampaignAI", JASS_SetCampaignAI);
,
lua_register(L, "SetMeleeAI", JASS_SetMeleeAI);
,
lua_register(L, "LoadWidgetHandle", JASS_LoadWidgetHandle);
,
lua_register(L, "LoadDestructableHandle", JASS_LoadDestructableHandle);
,
lua_register(L, "LoadItemHandle", JASS_LoadItemHandle);
,
lua_register(L, "LoadUnitHandle", JASS_LoadUnitHandle);
,
lua_register(L, "LoadAbilityHandle", JASS_LoadAbilityHandle);
,
lua_register(L, "LoadRegionHandle", JASS_LoadRegionHandle);
,
lua_register(L, "LoadForceHandle", JASS_LoadForceHandle);
,
lua_register(L, "LoadLocationHandle", JASS_LoadLocationHandle);
,
lua_register(L, "LoadRectHandle", JASS_LoadRectHandle);
,
lua_register(L, "LoadBooleanExprHandle", JASS_LoadBooleanExprHandle);
,
lua_register(L, "LoadSoundHandle", JASS_LoadSoundHandle);
,
lua_register(L, "LoadEffectHandle", JASS_LoadEffectHandle);
,
lua_register(L, "LoadUnitPoolHandle", JASS_LoadUnitPoolHandle);
,
lua_register(L, "LoadItemPoolHandle", JASS_LoadItemPoolHandle);
,
lua_register(L, "LoadQuestHandle", JASS_LoadQuestHandle);
,
lua_register(L, "LoadQuestItemHandle", JASS_LoadQuestItemHandle);
,
lua_register(L, "LoadDefeatConditionHandle", JASS_LoadDefeatConditionHandle);
,
lua_register(L, "LoadLeaderboardHandle", JASS_LoadLeaderboardHandle);
,
lua_register(L, "LoadMultiboardHandle", JASS_LoadMultiboardHandle);
,
lua_register(L, "LoadMultiboardItemHandle", JASS_LoadMultiboardItemHandle);
,
lua_register(L, "LoadTrackableHandle", JASS_LoadTrackableHandle);
,
lua_register(L, "LoadDialogHandle", JASS_LoadDialogHandle);
,
lua_register(L, "LoadButtonHandle", JASS_LoadButtonHandle);
,
lua_register(L, "LoadTextTagHandle", JASS_LoadTextTagHandle);
,
lua_register(L, "LoadLightningHandle", JASS_LoadLightningHandle);
,
lua_register(L, "LoadImageHandle", JASS_LoadImageHandle);
,
lua_register(L, "LoadUbersplatHandle", JASS_LoadUbersplatHandle);
,
lua_register(L, "LoadFogStateHandle", JASS_LoadFogStateHandle);
,
lua_register(L, "LoadFogModifierHandle", JASS_LoadFogModifierHandle);
,
lua_register(L, "LoadHashtableHandle", JASS_LoadHashtableHandle);
,
lua_register(L, "RemoveSavedInteger", JASS_RemoveSavedInteger);
,
lua_register(L, "RemoveSavedReal", JASS_RemoveSavedReal);
,
lua_register(L, "RemoveSavedBoolean", JASS_RemoveSavedBoolean);
,
lua_register(L, "RemoveSavedString", JASS_RemoveSavedString);
,
lua_register(L, "RemoveSavedHandle", JASS_RemoveSavedHandle);
,
lua_register(L, "FlushParentHashtable", JASS_FlushParentHashtable);
,
lua_register(L, "FlushChildHashtable", JASS_FlushChildHashtable);
,
lua_register(L, "GetRandomInt", JASS_GetRandomInt);
,
lua_register(L, "GetRandomReal", JASS_GetRandomReal);
,
lua_register(L, "CreateUnitPool", JASS_CreateUnitPool);
,
lua_register(L, "DestroyUnitPool", JASS_DestroyUnitPool);
,
lua_register(L, "UnitPoolAddUnitType", JASS_UnitPoolAddUnitType);
,
lua_register(L, "UnitPoolRemoveUnitType", JASS_UnitPoolRemoveUnitType);
,
lua_register(L, "PlaceRandomUnit", JASS_PlaceRandomUnit);
,
lua_register(L, "CreateItemPool", JASS_CreateItemPool);
,
lua_register(L, "DestroyItemPool", JASS_DestroyItemPool);
,
lua_register(L, "ItemPoolAddItemType", JASS_ItemPoolAddItemType);
,
lua_register(L, "ItemPoolRemoveItemType", JASS_ItemPoolRemoveItemType);
,
lua_register(L, "PlaceRandomItem", JASS_PlaceRandomItem);
,
lua_register(L, "ChooseRandomCreep", JASS_ChooseRandomCreep);
,
lua_register(L, "ChooseRandomNPBuilding", JASS_ChooseRandomNPBuilding);
,
lua_register(L, "ChooseRandomItem", JASS_ChooseRandomItem);
,
lua_register(L, "ChooseRandomItemEx", JASS_ChooseRandomItemEx);
,
lua_register(L, "SetRandomSeed", JASS_SetRandomSeed);
,
lua_register(L, "DisplayTextToPlayer", JASS_DisplayTextToPlayer);
,
lua_register(L, "DisplayTimedTextToPlayer", JASS_DisplayTimedTextToPlayer);
,
lua_register(L, "DisplayTimedTextFromPlayer", JASS_DisplayTimedTextFromPlayer);
,
lua_register(L, "ClearTextMessages", JASS_ClearTextMessages);
,
lua_register(L, "ForceUIKey", JASS_ForceUIKey);
,
lua_register(L, "ForceUICancel", JASS_ForceUICancel);
,
lua_register(L, "DisplayLoadDialog", JASS_DisplayLoadDialog);
,
lua_register(L, "SetTerrainFog", JASS_SetTerrainFog);
,
lua_register(L, "SetUnitFog", JASS_SetUnitFog);
,
lua_register(L, "SetTerrainFogEx", JASS_SetTerrainFogEx);
,
lua_register(L, "ResetTerrainFog", JASS_ResetTerrainFog);
,
lua_register(L, "SetDayNightModels", JASS_SetDayNightModels);
,
lua_register(L, "SetSkyModel", JASS_SetSkyModel);
,
lua_register(L, "SetTimeOfDayScale", JASS_SetTimeOfDayScale);
,
lua_register(L, "GetTimeOfDayScale", JASS_GetTimeOfDayScale);
,
lua_register(L, "PingMinimap", JASS_PingMinimap);
,
lua_register(L, "SetIntroShotText", JASS_SetIntroShotText);
,
lua_register(L, "SetIntroShotModel", JASS_SetIntroShotModel);
,
lua_register(L, "PlayModelCinematic", JASS_PlayModelCinematic);
,
lua_register(L, "PlayCinematic", JASS_PlayCinematic);
,
lua_register(L, "SetAltMinimapIcon", JASS_SetAltMinimapIcon);
,
lua_register(L, "CreateTextTag", JASS_CreateTextTag);
,
lua_register(L, "DestroyTextTag", JASS_DestroyTextTag);
,
lua_register(L, "SetTextTagText", JASS_SetTextTagText);
,
lua_register(L, "SetTextTagPos", JASS_SetTextTagPos);
,
lua_register(L, "SetTextTagPosUnit", JASS_SetTextTagPosUnit);
,
lua_register(L, "SetTextTagColor", JASS_SetTextTagColor);
,
lua_register(L, "SetTextTagVelocity", JASS_SetTextTagVelocity);
,
lua_register(L, "SetTextTagAge", JASS_SetTextTagAge);
,
lua_register(L, "SetTextTagLifespan", JASS_SetTextTagLifespan);
,
lua_register(L, "SetTextTagFadepoint", JASS_SetTextTagFadepoint);
,
lua_register(L, "SetReservedLocalHeroButtons", JASS_SetReservedLocalHeroButtons);
,
lua_register(L, "GetAllyColorFilterState", JASS_GetAllyColorFilterState);
,
lua_register(L, "SetAllyColorFilterState", JASS_SetAllyColorFilterState);
,
lua_register(L, "CreateTrackable", JASS_CreateTrackable);
,
lua_register(L, "GetTriggeringTrackable", JASS_GetTriggeringTrackable);
,
lua_register(L, "CreateQuest", JASS_CreateQuest);
,
lua_register(L, "DestroyQuest", JASS_DestroyQuest);
,
lua_register(L, "QuestSetTitle", JASS_QuestSetTitle);
,
lua_register(L, "QuestSetDescription", JASS_QuestSetDescription);
,
lua_register(L, "QuestSetIconPath", JASS_QuestSetIconPath);
,
lua_register(L, "QuestCreateItem", JASS_QuestCreateItem);
,
lua_register(L, "QuestItemSetDescription", JASS_QuestItemSetDescription);
,
lua_register(L, "CreateDefeatCondition", JASS_CreateDefeatCondition);
,
lua_register(L, "DestroyDefeatCondition", JASS_DestroyDefeatCondition);
,
lua_register(L, "DefeatConditionSetDescription", JASS_DefeatConditionSetDescription);
,
lua_register(L, "FlashQuestDialogButton", JASS_FlashQuestDialogButton);
,
lua_register(L, "ForceQuestDialogUpdate", JASS_ForceQuestDialogUpdate);
,
lua_register(L, "CreateLeaderboard", JASS_CreateLeaderboard);
,
lua_register(L, "DestroyLeaderboard", JASS_DestroyLeaderboard);
,
lua_register(L, "LeaderboardGetItemCount", JASS_LeaderboardGetItemCount);
,
lua_register(L, "LeaderboardSetSizeByItemCount", JASS_LeaderboardSetSizeByItemCount);
,
lua_register(L, "LeaderboardAddItem", JASS_LeaderboardAddItem);
,
lua_register(L, "LeaderboardRemoveItem", JASS_LeaderboardRemoveItem);
,
lua_register(L, "LeaderboardRemovePlayerItem", JASS_LeaderboardRemovePlayerItem);
,
lua_register(L, "LeaderboardClear", JASS_LeaderboardClear);
,
lua_register(L, "LeaderboardGetLabelText", JASS_LeaderboardGetLabelText);
,
lua_register(L, "PlayerSetLeaderboard", JASS_PlayerSetLeaderboard);
,
lua_register(L, "PlayerGetLeaderboard", JASS_PlayerGetLeaderboard);
,
lua_register(L, "LeaderboardGetPlayerIndex", JASS_LeaderboardGetPlayerIndex);
,
lua_register(L, "LeaderboardSetLabel", JASS_LeaderboardSetLabel);
,
lua_register(L, "LeaderboardSetLabelColor", JASS_LeaderboardSetLabelColor);
,
lua_register(L, "LeaderboardSetValueColor", JASS_LeaderboardSetValueColor);
,
lua_register(L, "LeaderboardSetItemValue", JASS_LeaderboardSetItemValue);
,
lua_register(L, "LeaderboardSetItemLabel", JASS_LeaderboardSetItemLabel);
,
lua_register(L, "LeaderboardSetItemLabelColor", JASS_LeaderboardSetItemLabelColor);
,
lua_register(L, "LeaderboardSetItemValueColor", JASS_LeaderboardSetItemValueColor);
,
lua_register(L, "CreateMultiboard", JASS_CreateMultiboard);
,
lua_register(L, "DestroyMultiboard", JASS_DestroyMultiboard);
,
lua_register(L, "MultiboardClear", JASS_MultiboardClear);
,
lua_register(L, "MultiboardSetTitleText", JASS_MultiboardSetTitleText);
,
lua_register(L, "MultiboardGetTitleText", JASS_MultiboardGetTitleText);
,
lua_register(L, "MultiboardSetTitleTextColor", JASS_MultiboardSetTitleTextColor);
,
lua_register(L, "MultiboardGetRowCount", JASS_MultiboardGetRowCount);
,
lua_register(L, "MultiboardGetColumnCount", JASS_MultiboardGetColumnCount);
,
lua_register(L, "MultiboardSetColumnCount", JASS_MultiboardSetColumnCount);
,
lua_register(L, "MultiboardSetRowCount", JASS_MultiboardSetRowCount);
,
lua_register(L, "MultiboardSetItemsValueColor", JASS_MultiboardSetItemsValueColor);
,
lua_register(L, "MultiboardSetItemsValue", JASS_MultiboardSetItemsValue);
,
lua_register(L, "MultiboardSetItemsWidth", JASS_MultiboardSetItemsWidth);
,
lua_register(L, "MultiboardSetItemsIcon", JASS_MultiboardSetItemsIcon);
,
lua_register(L, "MultiboardGetItem", JASS_MultiboardGetItem);
,
lua_register(L, "MultiboardReleaseItem", JASS_MultiboardReleaseItem);
,
lua_register(L, "MultiboardSetItemValue", JASS_MultiboardSetItemValue);
,
lua_register(L, "MultiboardSetItemValueColor", JASS_MultiboardSetItemValueColor);
,
lua_register(L, "MultiboardSetItemWidth", JASS_MultiboardSetItemWidth);
,
lua_register(L, "MultiboardSetItemIcon", JASS_MultiboardSetItemIcon);
,
lua_register(L, "SetCameraBounds", JASS_SetCameraBounds);
,
lua_register(L, "SetCameraPosition", JASS_SetCameraPosition);
,
lua_register(L, "SetCameraQuickPosition", JASS_SetCameraQuickPosition);
,
lua_register(L, "ResetToGameCamera", JASS_ResetToGameCamera);
,
lua_register(L, "StopCamera", JASS_StopCamera);
,
lua_register(L, "PanCameraTo", JASS_PanCameraTo);
,
lua_register(L, "PanCameraToTimed", JASS_PanCameraToTimed);
,
lua_register(L, "PanCameraToWithZ", JASS_PanCameraToWithZ);
,
lua_register(L, "PanCameraToTimedWithZ", JASS_PanCameraToTimedWithZ);
,
lua_register(L, "SetCinematicCamera", JASS_SetCinematicCamera);
,
lua_register(L, "SetCameraField", JASS_SetCameraField);
,
lua_register(L, "AdjustCameraField", JASS_AdjustCameraField);
,
lua_register(L, "SetCameraOrientController", JASS_SetCameraOrientController);
,
lua_register(L, "SetCameraRotateMode", JASS_SetCameraRotateMode);
,
lua_register(L, "CreateCameraSetup", JASS_CreateCameraSetup);
,
lua_register(L, "CameraSetupSetField", JASS_CameraSetupSetField);
,
lua_register(L, "CameraSetupGetField", JASS_CameraSetupGetField);
,
lua_register(L, "CameraSetupSetDestPosition", JASS_CameraSetupSetDestPosition);
,
lua_register(L, "CameraSetupGetDestPositionLoc", JASS_CameraSetupGetDestPositionLoc);
,
lua_register(L, "CameraSetupGetDestPositionX", JASS_CameraSetupGetDestPositionX);
,
lua_register(L, "CameraSetupGetDestPositionY", JASS_CameraSetupGetDestPositionY);
,
lua_register(L, "CameraSetupApplyWithZ", JASS_CameraSetupApplyWithZ);
,
lua_register(L, "CameraSetupApplyForceDurationWithZ", JASS_CameraSetupApplyForceDurationWithZ);
,
lua_register(L, "CameraSetTargetNoise", JASS_CameraSetTargetNoise);
,
lua_register(L, "CameraSetSourceNoise", JASS_CameraSetSourceNoise);
,
lua_register(L, "CameraSetSmoothingFactor", JASS_CameraSetSmoothingFactor);
,
lua_register(L, "GetCameraMargin", JASS_GetCameraMargin);
,
lua_register(L, "GetCameraBoundMinX", JASS_GetCameraBoundMinX);
,
lua_register(L, "GetCameraBoundMinY", JASS_GetCameraBoundMinY);
,
lua_register(L, "GetCameraBoundMaxX", JASS_GetCameraBoundMaxX);
,
lua_register(L, "GetCameraBoundMaxY", JASS_GetCameraBoundMaxY);
,
lua_register(L, "GetCameraField", JASS_GetCameraField);
,
lua_register(L, "GetCameraTargetPositionX", JASS_GetCameraTargetPositionX);
,
lua_register(L, "GetCameraTargetPositionY", JASS_GetCameraTargetPositionY);
,
lua_register(L, "GetCameraTargetPositionZ", JASS_GetCameraTargetPositionZ);
,
lua_register(L, "GetCameraTargetPositionLoc", JASS_GetCameraTargetPositionLoc);
,
lua_register(L, "GetCameraEyePositionX", JASS_GetCameraEyePositionX);
,
lua_register(L, "GetCameraEyePositionY", JASS_GetCameraEyePositionY);
,
lua_register(L, "GetCameraEyePositionZ", JASS_GetCameraEyePositionZ);
,
lua_register(L, "GetCameraEyePositionLoc", JASS_GetCameraEyePositionLoc);
,
lua_register(L, "SetCineFilterTexture", JASS_SetCineFilterTexture);
,
lua_register(L, "SetCineFilterBlendMode", JASS_SetCineFilterBlendMode);
,
lua_register(L, "GetOwningPlayer", JASS_GetOwningPlayer);
,
lua_register(L, "UnitWakeUp", JASS_UnitWakeUp);
,
lua_register(L, "UnitApplyTimedLife", JASS_UnitApplyTimedLife);
,
lua_register(L, "DecUnitAbilityLevel", JASS_DecUnitAbilityLevel);
,
lua_register(L, "IncUnitAbilityLevel", JASS_IncUnitAbilityLevel);
,
lua_register(L, "SetUnitAbilityLevel", JASS_SetUnitAbilityLevel);
,
lua_register(L, "UnitResetCooldown", JASS_UnitResetCooldown);
,
lua_register(L, "UnitSetConstructionProgress", JASS_UnitSetConstructionProgress);
,
lua_register(L, "UnitSetUpgradeProgress", JASS_UnitSetUpgradeProgress);
,
lua_register(L, "WaygateGetDestinationX", JASS_WaygateGetDestinationX);
,
lua_register(L, "WaygateGetDestinationY", JASS_WaygateGetDestinationY);
,
lua_register(L, "WaygateSetDestination", JASS_WaygateSetDestination);
,
lua_register(L, "AddItemToAllStock", JASS_AddItemToAllStock);
,
lua_register(L, "AddItemToStock", JASS_AddItemToStock);
,
lua_register(L, "AddUnitToAllStock", JASS_AddUnitToAllStock);
,
lua_register(L, "AddUnitToStock", JASS_AddUnitToStock);
,
lua_register(L, "RemoveItemFromAllStock", JASS_RemoveItemFromAllStock);
,
lua_register(L, "RemoveItemFromStock", JASS_RemoveItemFromStock);
,
lua_register(L, "RemoveUnitFromAllStock", JASS_RemoveUnitFromAllStock);
,
lua_register(L, "RemoveUnitFromStock", JASS_RemoveUnitFromStock);
,
lua_register(L, "SetAllItemTypeSlots", JASS_SetAllItemTypeSlots);
,
lua_register(L, "SetAllUnitTypeSlots", JASS_SetAllUnitTypeSlots);
,
lua_register(L, "SetItemTypeSlots", JASS_SetItemTypeSlots);
,
lua_register(L, "SetUnitTypeSlots", JASS_SetUnitTypeSlots);
,
lua_register(L, "GetUnitUserData", JASS_GetUnitUserData);
,
lua_register(L, "SetUnitUserData", JASS_SetUnitUserData);
,
lua_register(L, "CreateItem", JASS_CreateItem);
,
lua_register(L, "RemoveItem", JASS_RemoveItem);
,
lua_register(L, "GetItemPlayer", JASS_GetItemPlayer);
,
lua_register(L, "GetItemTypeId", JASS_GetItemTypeId);
,
lua_register(L, "GetItemX", JASS_GetItemX);
,
lua_register(L, "GetItemY", JASS_GetItemY);
,
lua_register(L, "SetItemPosition", JASS_SetItemPosition);
,
lua_register(L, "GetItemLevel", JASS_GetItemLevel);
,
lua_register(L, "GetItemType", JASS_GetItemType);
,
lua_register(L, "SetItemDropID", JASS_SetItemDropID);
,
lua_register(L, "GetItemName", JASS_GetItemName);
,
lua_register(L, "GetItemCharges", JASS_GetItemCharges);
,
lua_register(L, "SetItemCharges", JASS_SetItemCharges);
,
lua_register(L, "GetItemUserData", JASS_GetItemUserData);
,
lua_register(L, "SetItemUserData", JASS_SetItemUserData);
,
lua_register(L, "Player", JASS_Player);
,
lua_register(L, "GetLocalPlayer", JASS_GetLocalPlayer);
,
lua_register(L, "GetPlayerRace", JASS_GetPlayerRace);
,
lua_register(L, "GetPlayerId", JASS_GetPlayerId);
,
lua_register(L, "SetPlayerTechMaxAllowed", JASS_SetPlayerTechMaxAllowed);
,
lua_register(L, "GetPlayerTechMaxAllowed", JASS_GetPlayerTechMaxAllowed);
,
lua_register(L, "AddPlayerTechResearched", JASS_AddPlayerTechResearched);
,
lua_register(L, "SetPlayerTechResearched", JASS_SetPlayerTechResearched);
,
lua_register(L, "SetPlayerState", JASS_SetPlayerState);
,
lua_register(L, "GetPlayerState", JASS_GetPlayerState);
,
lua_register(L, "GetPlayerScore", JASS_GetPlayerScore);
,
lua_register(L, "RemovePlayer", JASS_RemovePlayer);
,
lua_register(L, "CachePlayerHeroData", JASS_CachePlayerHeroData);
,
lua_register(L, "GetPlayerHandicap", JASS_GetPlayerHandicap);
,
lua_register(L, "SetPlayerHandicap", JASS_SetPlayerHandicap);
,
lua_register(L, "GetPlayerHandicapXP", JASS_GetPlayerHandicapXP);
,
lua_register(L, "SetPlayerHandicapXP", JASS_SetPlayerHandicapXP);
,
lua_register(L, "SetPlayerUnitsOwner", JASS_SetPlayerUnitsOwner);
,
lua_register(L, "VersionGet", JASS_VersionGet);
,
lua_register(L, "ReloadGame", JASS_ReloadGame);
,
lua_register(L, "SaveGame", JASS_SaveGame);
,
lua_register(L, "SetFloatGameState", JASS_SetFloatGameState);
,
lua_register(L, "GetFloatGameState", JASS_GetFloatGameState);
,
lua_register(L, "SetIntegerGameState", JASS_SetIntegerGameState);
,
lua_register(L, "GetIntegerGameState", JASS_GetIntegerGameState);
,
lua_register(L, "SyncSelections", JASS_SyncSelections);
,
lua_register(L, "DialogCreate", JASS_DialogCreate);
,
lua_register(L, "DialogDestroy", JASS_DialogDestroy);
,
lua_register(L, "DialogSetAsync", JASS_DialogSetAsync);
,
lua_register(L, "DialogClear", JASS_DialogClear);
,
lua_register(L, "DialogSetMessage", JASS_DialogSetMessage);
,
lua_register(L, "DialogAddButton", JASS_DialogAddButton);
,
lua_register(L, "SetCampaignMenuRace", JASS_SetCampaignMenuRace);
,
lua_register(L, "SetCampaignMenuRaceEx", JASS_SetCampaignMenuRaceEx);
,
lua_register(L, "ForceCampaignSelectScreen", JASS_ForceCampaignSelectScreen);
,
lua_register(L, "GetDefaultDifficulty", JASS_GetDefaultDifficulty);
,
lua_register(L, "SetDefaultDifficulty", JASS_SetDefaultDifficulty);
,
lua_register(L, "DoNotSaveReplay", JASS_DoNotSaveReplay);
,
lua_register(L, "InitGameCache", JASS_InitGameCache);
,
lua_register(L, "StoreInteger", JASS_StoreInteger);
,
lua_register(L, "StoreReal", JASS_StoreReal);
,
lua_register(L, "SaveInteger", JASS_SaveInteger);
,
lua_register(L, "SaveReal", JASS_SaveReal);
,
lua_register(L, "SyncStoredInteger", JASS_SyncStoredInteger);
,
lua_register(L, "SyncStoredReal", JASS_SyncStoredReal);
,
lua_register(L, "SyncStoredBoolean", JASS_SyncStoredBoolean);
,
lua_register(L, "SyncStoredUnit", JASS_SyncStoredUnit);
,
lua_register(L, "SyncStoredString", JASS_SyncStoredString);
,
lua_register(L, "GetStoredInteger", JASS_GetStoredInteger);
,
lua_register(L, "GetStoredReal", JASS_GetStoredReal);
,
lua_register(L, "RestoreUnit", JASS_RestoreUnit);
,
lua_register(L, "GetStoredString", JASS_GetStoredString);
,
lua_register(L, "FlushGameCache", JASS_FlushGameCache);
,
lua_register(L, "FlushStoredMission", JASS_FlushStoredMission);
,
lua_register(L, "FlushStoredInteger", JASS_FlushStoredInteger);
,
lua_register(L, "FlushStoredReal", JASS_FlushStoredReal);
,
lua_register(L, "FlushStoredBoolean", JASS_FlushStoredBoolean);
,
lua_register(L, "FlushStoredUnit", JASS_FlushStoredUnit);
,
lua_register(L, "FlushStoredString", JASS_FlushStoredString);
,
lua_register(L, "InitHashtable", JASS_InitHashtable);
,
lua_register(L, "LoadInteger", JASS_LoadInteger);
,
lua_register(L, "LoadReal", JASS_LoadReal);
,
lua_register(L, "LoadStr", JASS_LoadStr);
,
lua_register(L, "LoadPlayerHandle", JASS_LoadPlayerHandle);
,
lua_register(L, "GetLearnedSkill", JASS_GetLearnedSkill);
,
lua_register(L, "GetLearnedSkillLevel", JASS_GetLearnedSkillLevel);
,
lua_register(L, "GetRevivableUnit", JASS_GetRevivableUnit);
,
lua_register(L, "GetRevivingUnit", JASS_GetRevivingUnit);
,
lua_register(L, "GetSummoningUnit", JASS_GetSummoningUnit);
,
lua_register(L, "GetSummonedUnit", JASS_GetSummonedUnit);
,
lua_register(L, "GetTransportUnit", JASS_GetTransportUnit);
,
lua_register(L, "GetLoadedUnit", JASS_GetLoadedUnit);
,
lua_register(L, "GetManipulatingUnit", JASS_GetManipulatingUnit);
,
lua_register(L, "GetManipulatedItem", JASS_GetManipulatedItem);
,
lua_register(L, "GetEventPlayerChatString", JASS_GetEventPlayerChatString);
,
lua_register(L, "GetEventPlayerChatStringMatched", JASS_GetEventPlayerChatStringMatched);
,
lua_register(L, "GetEventUnitState", JASS_GetEventUnitState);
,
lua_register(L, "GetEventDamage", JASS_GetEventDamage);
,
lua_register(L, "GetEventDamageSource", JASS_GetEventDamageSource);
,
lua_register(L, "GetEventDetectingPlayer", JASS_GetEventDetectingPlayer);
,
lua_register(L, "GetEventTargetUnit", JASS_GetEventTargetUnit);
,
lua_register(L, "GetTriggeringRegion", JASS_GetTriggeringRegion);
,
lua_register(L, "GetEnteringUnit", JASS_GetEnteringUnit);
,
lua_register(L, "GetLeavingUnit", JASS_GetLeavingUnit);
,
lua_register(L, "GetTriggerWidget", JASS_GetTriggerWidget);
,
lua_register(L, "GetTriggerDestructable", JASS_GetTriggerDestructable);
,
lua_register(L, "GetTriggerUnit", JASS_GetTriggerUnit);
,
lua_register(L, "GetTriggerPlayer", JASS_GetTriggerPlayer);
,
lua_register(L, "GetTriggeringTrigger", JASS_GetTriggeringTrigger);
,
lua_register(L, "GetTriggerEventId", JASS_GetTriggerEventId);
,
lua_register(L, "GetTriggerEvalCount", JASS_GetTriggerEvalCount);
,
lua_register(L, "GetTriggerExecCount", JASS_GetTriggerExecCount);
,
lua_register(L, "GetFilterUnit", JASS_GetFilterUnit);
,
lua_register(L, "GetEnumUnit", JASS_GetEnumUnit);
,
lua_register(L, "GetEnumPlayer", JASS_GetEnumPlayer);
,
lua_register(L, "GetFilterPlayer", JASS_GetFilterPlayer);
,
lua_register(L, "GetFilterDestructable", JASS_GetFilterDestructable);
,
lua_register(L, "GetEnumDestructable", JASS_GetEnumDestructable);
,
lua_register(L, "GetFilterItem", JASS_GetFilterItem);
,
lua_register(L, "GetEnumItem", JASS_GetEnumItem);
,
lua_register(L, "CreateForce", JASS_CreateForce);
,
lua_register(L, "DestroyForce", JASS_DestroyForce);
,
lua_register(L, "ForceAddPlayer", JASS_ForceAddPlayer);
,
lua_register(L, "ForceRemovePlayer", JASS_ForceRemovePlayer);
,
lua_register(L, "ForceClear", JASS_ForceClear);
,
lua_register(L, "ForceEnumPlayers", JASS_ForceEnumPlayers);
,
lua_register(L, "ForceEnumPlayersCounted", JASS_ForceEnumPlayersCounted);
,
lua_register(L, "ForceEnumAllies", JASS_ForceEnumAllies);
,
lua_register(L, "ForceEnumEnemies", JASS_ForceEnumEnemies);
,
lua_register(L, "GetWidgetLife", JASS_GetWidgetLife);
,
lua_register(L, "SetWidgetLife", JASS_SetWidgetLife);
,
lua_register(L, "GetWidgetX", JASS_GetWidgetX);
,
lua_register(L, "GetWidgetY", JASS_GetWidgetY);
,
lua_register(L, "CreateDestructable", JASS_CreateDestructable);
,
lua_register(L, "CreateDestructableZ", JASS_CreateDestructableZ);
,
lua_register(L, "CreateDeadDestructable", JASS_CreateDeadDestructable);
,
lua_register(L, "CreateDeadDestructableZ", JASS_CreateDeadDestructableZ);
,
lua_register(L, "RemoveDestructable", JASS_RemoveDestructable);
,
lua_register(L, "KillDestructable", JASS_KillDestructable);
,
lua_register(L, "GetDestructableTypeId", JASS_GetDestructableTypeId);
,
lua_register(L, "GetDestructableX", JASS_GetDestructableX);
,
lua_register(L, "GetDestructableY", JASS_GetDestructableY);
,
lua_register(L, "SetDestructableLife", JASS_SetDestructableLife);
,
lua_register(L, "GetDestructableLife", JASS_GetDestructableLife);
,
lua_register(L, "SetDestructableMaxLife", JASS_SetDestructableMaxLife);
,
lua_register(L, "GetDestructableMaxLife", JASS_GetDestructableMaxLife);
,
lua_register(L, "QueueDestructableAnimation", JASS_QueueDestructableAnimation);
,
lua_register(L, "SetDestructableAnimation", JASS_SetDestructableAnimation);
,
lua_register(L, "SetDestructableAnimationSpeed", JASS_SetDestructableAnimationSpeed);
,
lua_register(L, "GetDestructableOccluderHeight", JASS_GetDestructableOccluderHeight);
,
lua_register(L, "SetDestructableOccluderHeight", JASS_SetDestructableOccluderHeight);
,
lua_register(L, "GetDestructableName", JASS_GetDestructableName);
,
lua_register(L, "CreateUnit", JASS_CreateUnit);
,
lua_register(L, "CreateUnitByName", JASS_CreateUnitByName);
,
lua_register(L, "CreateUnitAtLoc", JASS_CreateUnitAtLoc);
,
lua_register(L, "CreateUnitAtLocByName", JASS_CreateUnitAtLocByName);
,
lua_register(L, "CreateCorpse", JASS_CreateCorpse);
,
lua_register(L, "GetUnitState", JASS_GetUnitState);
,
lua_register(L, "GetUnitFoodUsed", JASS_GetUnitFoodUsed);
,
lua_register(L, "GetUnitFoodMade", JASS_GetUnitFoodMade);
,
lua_register(L, "GetFoodMade", JASS_GetFoodMade);
,
lua_register(L, "GetFoodUsed", JASS_GetFoodUsed);
,
lua_register(L, "GetUnitX", JASS_GetUnitX);
,
lua_register(L, "GetUnitY", JASS_GetUnitY);
,
lua_register(L, "GetUnitLoc", JASS_GetUnitLoc);
,
lua_register(L, "GetUnitRallyPoint", JASS_GetUnitRallyPoint);
,
lua_register(L, "GetUnitRallyUnit", JASS_GetUnitRallyUnit);
,
lua_register(L, "GetUnitRallyDestructable", JASS_GetUnitRallyDestructable);
,
lua_register(L, "GetUnitFacing", JASS_GetUnitFacing);
,
lua_register(L, "GetUnitMoveSpeed", JASS_GetUnitMoveSpeed);
,
lua_register(L, "GetUnitDefaultMoveSpeed", JASS_GetUnitDefaultMoveSpeed);
,
lua_register(L, "GetUnitTypeId", JASS_GetUnitTypeId);
,
lua_register(L, "GetUnitRace", JASS_GetUnitRace);
,
lua_register(L, "GetUnitName", JASS_GetUnitName);
,
lua_register(L, "GetUnitPointValue", JASS_GetUnitPointValue);
,
lua_register(L, "GetUnitPointValueByType", JASS_GetUnitPointValueByType);
,
lua_register(L, "SetUnitX", JASS_SetUnitX);
,
lua_register(L, "SetUnitY", JASS_SetUnitY);
,
lua_register(L, "SetUnitPosition", JASS_SetUnitPosition);
,
lua_register(L, "SetUnitPositionLoc", JASS_SetUnitPositionLoc);
,
lua_register(L, "SetUnitFacing", JASS_SetUnitFacing);
,
lua_register(L, "SetUnitFacingTimed", JASS_SetUnitFacingTimed);
,
lua_register(L, "SetUnitFlyHeight", JASS_SetUnitFlyHeight);
,
lua_register(L, "SetUnitMoveSpeed", JASS_SetUnitMoveSpeed);
,
lua_register(L, "SetUnitTurnSpeed", JASS_SetUnitTurnSpeed);
,
lua_register(L, "SetUnitPropWindow", JASS_SetUnitPropWindow);
,
lua_register(L, "GetUnitAcquireRange", JASS_GetUnitAcquireRange);
,
lua_register(L, "GetUnitTurnSpeed", JASS_GetUnitTurnSpeed);
,
lua_register(L, "GetUnitPropWindow", JASS_GetUnitPropWindow);
,
lua_register(L, "GetUnitFlyHeight", JASS_GetUnitFlyHeight);
,
lua_register(L, "GetUnitDefaultAcquireRange", JASS_GetUnitDefaultAcquireRange);
,
lua_register(L, "GetUnitDefaultTurnSpeed", JASS_GetUnitDefaultTurnSpeed);
,
lua_register(L, "GetUnitDefaultPropWindow", JASS_GetUnitDefaultPropWindow);
,
lua_register(L, "GetUnitDefaultFlyHeight", JASS_GetUnitDefaultFlyHeight);
,
lua_register(L, "SetUnitAcquireRange", JASS_SetUnitAcquireRange);
,
lua_register(L, "SetUnitState", JASS_SetUnitState);
,
lua_register(L, "SetUnitRescueRange", JASS_SetUnitRescueRange);
,
lua_register(L, "SetUnitColor", JASS_SetUnitColor);
,
lua_register(L, "QueueUnitAnimation", JASS_QueueUnitAnimation);
,
lua_register(L, "SetUnitAnimation", JASS_SetUnitAnimation);
,
lua_register(L, "SetUnitAnimationWithRarity", JASS_SetUnitAnimationWithRarity);
,
lua_register(L, "SetUnitAnimationByIndex", JASS_SetUnitAnimationByIndex);
,
lua_register(L, "SetUnitScale", JASS_SetUnitScale);
,
lua_register(L, "SetUnitTimeScale", JASS_SetUnitTimeScale);
,
lua_register(L, "SetUnitBlendTime", JASS_SetUnitBlendTime);
,
lua_register(L, "SetUnitVertexColor", JASS_SetUnitVertexColor);
,
lua_register(L, "SetUnitLookAt", JASS_SetUnitLookAt);
,
lua_register(L, "ResetUnitLookAt", JASS_ResetUnitLookAt);
,
lua_register(L, "GetHeroSkillPoints", JASS_GetHeroSkillPoints);
,
lua_register(L, "GetHeroXP", JASS_GetHeroXP);
,
lua_register(L, "GetHeroLevel", JASS_GetHeroLevel);
,
lua_register(L, "GetUnitLevel", JASS_GetUnitLevel);
,
lua_register(L, "GetHeroProperName", JASS_GetHeroProperName);
,
lua_register(L, "SelectHeroSkill", JASS_SelectHeroSkill);
,
lua_register(L, "GetUnitAbilityLevel", JASS_GetUnitAbilityLevel);
,
lua_register(L, "UnitAddItemById", JASS_UnitAddItemById);
,
lua_register(L, "UnitRemoveItem", JASS_UnitRemoveItem);
,
lua_register(L, "UnitRemoveItemFromSlot", JASS_UnitRemoveItemFromSlot);
,
lua_register(L, "UnitItemInSlot", JASS_UnitItemInSlot);
,
lua_register(L, "UnitInventorySize", JASS_UnitInventorySize);
,
lua_register(L, "GetUnitCurrentOrder", JASS_GetUnitCurrentOrder);
,
lua_register(L, "SetResourceAmount", JASS_SetResourceAmount);
,
lua_register(L, "AddResourceAmount", JASS_AddResourceAmount);
,
lua_register(L, "GetResourceAmount", JASS_GetResourceAmount);
,
lua_register(L, "ClearSelection", JASS_ClearSelection);
,
lua_register(L, "UnitAddIndicator", JASS_UnitAddIndicator);
,
lua_register(L, "AddIndicator", JASS_AddIndicator);
,
lua_register(L, "KillUnit", JASS_KillUnit);
,
lua_register(L, "RemoveUnit", JASS_RemoveUnit);
,
lua_register(L, "Deg2Rad", JASS_Deg2Rad);
,
lua_register(L, "Rad2Deg", JASS_Rad2Deg);
,
lua_register(L, "Sin", JASS_Sin);
,
lua_register(L, "Cos", JASS_Cos);
,
lua_register(L, "Tan", JASS_Tan);
,
lua_register(L, "Asin", JASS_Asin);
,
lua_register(L, "Acos", JASS_Acos);
,
lua_register(L, "Atan", JASS_Atan);
,
lua_register(L, "Atan2", JASS_Atan2);
,
lua_register(L, "SquareRoot", JASS_SquareRoot);
,
lua_register(L, "Pow", JASS_Pow);
,
lua_register(L, "I2R", JASS_I2R);
,
lua_register(L, "R2I", JASS_R2I);
,
lua_register(L, "I2S", JASS_I2S);
,
lua_register(L, "R2S", JASS_R2S);
,
lua_register(L, "R2SW", JASS_R2SW);
,
lua_register(L, "S2I", JASS_S2I);
,
lua_register(L, "S2R", JASS_S2R);
,
lua_register(L, "GetHandleId", JASS_GetHandleId);
,
lua_register(L, "SubString", JASS_SubString);
,
lua_register(L, "StringLength", JASS_StringLength);
,
lua_register(L, "StringHash", JASS_StringHash);
,
lua_register(L, "GetLocalizedString", JASS_GetLocalizedString);
,
lua_register(L, "GetLocalizedHotkey", JASS_GetLocalizedHotkey);
,
lua_register(L, "ConvertRace", JASS_ConvertRace);
,
lua_register(L, "ConvertAllianceType", JASS_ConvertAllianceType);
,
lua_register(L, "ConvertRacePref", JASS_ConvertRacePref);
,
lua_register(L, "ConvertIGameState", JASS_ConvertIGameState);
,
lua_register(L, "ConvertFGameState", JASS_ConvertFGameState);
,
lua_register(L, "ConvertPlayerState", JASS_ConvertPlayerState);
,
lua_register(L, "ConvertPlayerScore", JASS_ConvertPlayerScore);
,
lua_register(L, "ConvertStartLocPrio", JASS_ConvertStartLocPrio);
,
lua_register(L, "ConvertPlayerGameResult", JASS_ConvertPlayerGameResult);
,
lua_register(L, "ConvertUnitState", JASS_ConvertUnitState);
,
lua_register(L, "ConvertAIDifficulty", JASS_ConvertAIDifficulty);
,
lua_register(L, "ConvertGameEvent", JASS_ConvertGameEvent);
,
lua_register(L, "ConvertPlayerEvent", JASS_ConvertPlayerEvent);
,
lua_register(L, "ConvertPlayerUnitEvent", JASS_ConvertPlayerUnitEvent);
,
lua_register(L, "ConvertUnitEvent", JASS_ConvertUnitEvent);
,
lua_register(L, "ConvertWidgetEvent", JASS_ConvertWidgetEvent);
,
lua_register(L, "ConvertDialogEvent", JASS_ConvertDialogEvent);
,
lua_register(L, "ConvertLimitOp", JASS_ConvertLimitOp);
,
lua_register(L, "ConvertUnitType", JASS_ConvertUnitType);
,
lua_register(L, "ConvertGameSpeed", JASS_ConvertGameSpeed);
,
lua_register(L, "ConvertPlacement", JASS_ConvertPlacement);
,
lua_register(L, "ConvertGameDifficulty", JASS_ConvertGameDifficulty);
,
lua_register(L, "ConvertGameType", JASS_ConvertGameType);
,
lua_register(L, "ConvertMapFlag", JASS_ConvertMapFlag);
,
lua_register(L, "ConvertMapVisibility", JASS_ConvertMapVisibility);
,
lua_register(L, "ConvertMapSetting", JASS_ConvertMapSetting);
,
lua_register(L, "ConvertMapDensity", JASS_ConvertMapDensity);
,
lua_register(L, "ConvertMapControl", JASS_ConvertMapControl);
,
lua_register(L, "ConvertPlayerColor", JASS_ConvertPlayerColor);
,
lua_register(L, "ConvertPlayerSlotState", JASS_ConvertPlayerSlotState);
,
lua_register(L, "ConvertCameraField", JASS_ConvertCameraField);
,
lua_register(L, "ConvertBlendMode", JASS_ConvertBlendMode);
,
lua_register(L, "ConvertRarityControl", JASS_ConvertRarityControl);
,
lua_register(L, "ConvertTexMapFlags", JASS_ConvertTexMapFlags);
,
lua_register(L, "ConvertFogState", JASS_ConvertFogState);
,
lua_register(L, "ConvertEffectType", JASS_ConvertEffectType);
,
lua_register(L, "ConvertVersion", JASS_ConvertVersion);
,
lua_register(L, "ConvertItemType", JASS_ConvertItemType);
,
lua_register(L, "ConvertAttackType", JASS_ConvertAttackType);
,
lua_register(L, "ConvertDamageType", JASS_ConvertDamageType);
,
lua_register(L, "ConvertWeaponType", JASS_ConvertWeaponType);
,
lua_register(L, "ConvertSoundType", JASS_ConvertSoundType);
,
lua_register(L, "ConvertPathingType", JASS_ConvertPathingType);
,
lua_register(L, "SetMapName", JASS_SetMapName);
,
lua_register(L, "SetMapDescription", JASS_SetMapDescription);
,
lua_register(L, "SetTeams", JASS_SetTeams);
,
lua_register(L, "SetPlayers", JASS_SetPlayers);
,
lua_register(L, "SetGameSpeed", JASS_SetGameSpeed);
,
lua_register(L, "SetGamePlacement", JASS_SetGamePlacement);
,
lua_register(L, "SetGameDifficulty", JASS_SetGameDifficulty);
,
lua_register(L, "SetResourceDensity", JASS_SetResourceDensity);
,
lua_register(L, "SetCreatureDensity", JASS_SetCreatureDensity);
,
lua_register(L, "DefineStartLocation", JASS_DefineStartLocation);
,
lua_register(L, "DefineStartLocationLoc", JASS_DefineStartLocationLoc);
,
lua_register(L, "SetStartLocPrioCount", JASS_SetStartLocPrioCount);
,
lua_register(L, "SetStartLocPrio", JASS_SetStartLocPrio);
,
lua_register(L, "GetStartLocPrioSlot", JASS_GetStartLocPrioSlot);
,
lua_register(L, "GetStartLocPrio", JASS_GetStartLocPrio);
,
lua_register(L, "GetTeams", JASS_GetTeams);
,
lua_register(L, "GetPlayers", JASS_GetPlayers);
,
lua_register(L, "GetGameTypeSelected", JASS_GetGameTypeSelected);
,
lua_register(L, "GetGamePlacement", JASS_GetGamePlacement);
,
lua_register(L, "GetGameSpeed", JASS_GetGameSpeed);
,
lua_register(L, "GetGameDifficulty", JASS_GetGameDifficulty);
,
lua_register(L, "GetResourceDensity", JASS_GetResourceDensity);
,
lua_register(L, "GetCreatureDensity", JASS_GetCreatureDensity);
,
lua_register(L, "GetStartLocationX", JASS_GetStartLocationX);
,
lua_register(L, "GetStartLocationY", JASS_GetStartLocationY);
,
lua_register(L, "GetStartLocationLoc", JASS_GetStartLocationLoc);
,
lua_register(L, "SetPlayerTeam", JASS_SetPlayerTeam);
,
lua_register(L, "SetPlayerStartLocation", JASS_SetPlayerStartLocation);
,
lua_register(L, "ForcePlayerStartLocation", JASS_ForcePlayerStartLocation);
,
lua_register(L, "SetPlayerTaxRate", JASS_SetPlayerTaxRate);
,
lua_register(L, "SetPlayerRacePreference", JASS_SetPlayerRacePreference);
,
lua_register(L, "SetPlayerController", JASS_SetPlayerController);
,
lua_register(L, "SetPlayerColor", JASS_SetPlayerColor);
,
lua_register(L, "SetPlayerName", JASS_SetPlayerName);
,
lua_register(L, "GetPlayerTeam", JASS_GetPlayerTeam);
,
lua_register(L, "GetPlayerName", JASS_GetPlayerName);
,
lua_register(L, "GetPlayerStartLocation", JASS_GetPlayerStartLocation);
,
lua_register(L, "GetPlayerStartLocationX", JASS_GetPlayerStartLocationX);
,
lua_register(L, "GetPlayerStartLocationY", JASS_GetPlayerStartLocationY);
,
lua_register(L, "GetPlayerColor", JASS_GetPlayerColor);
,
lua_register(L, "GetPlayerController", JASS_GetPlayerController);
,
lua_register(L, "GetPlayerSlotState", JASS_GetPlayerSlotState);
,
lua_register(L, "GetPlayerTaxRate", JASS_GetPlayerTaxRate);
,
lua_register(L, "Location", JASS_Location);
,
lua_register(L, "RemoveLocation", JASS_RemoveLocation);
,
lua_register(L, "MoveLocation", JASS_MoveLocation);
,
lua_register(L, "GetLocationX", JASS_GetLocationX);
,
lua_register(L, "GetLocationY", JASS_GetLocationY);
,
lua_register(L, "GetLocationZ", JASS_GetLocationZ);
,
lua_register(L, "DestroyCondition", JASS_DestroyCondition);
,
lua_register(L, "DestroyFilter", JASS_DestroyFilter);
,
lua_register(L, "DestroyBoolExpr", JASS_DestroyBoolExpr);
,
lua_register(L, "And", JASS_And);
,
lua_register(L, "Or", JASS_Or);
,
lua_register(L, "Not", JASS_Not);
,
lua_register(L, "CreateRegion", JASS_CreateRegion);
,
lua_register(L, "RemoveRegion", JASS_RemoveRegion);
,
lua_register(L, "RegionAddRect", JASS_RegionAddRect);
,
lua_register(L, "RegionClearRect", JASS_RegionClearRect);
,
lua_register(L, "RegionAddCell", JASS_RegionAddCell);
,
lua_register(L, "RegionAddCellAtLoc", JASS_RegionAddCellAtLoc);
,
lua_register(L, "RegionClearCell", JASS_RegionClearCell);
,
lua_register(L, "RegionClearCellAtLoc", JASS_RegionClearCellAtLoc);
,
lua_register(L, "Rect", JASS_Rect);
,
lua_register(L, "RectFromLoc", JASS_RectFromLoc);
,
lua_register(L, "RemoveRect", JASS_RemoveRect);
,
lua_register(L, "SetRect", JASS_SetRect);
,
lua_register(L, "SetRectFromLoc", JASS_SetRectFromLoc);
,
lua_register(L, "GetRectCenterX", JASS_GetRectCenterX);
,
lua_register(L, "GetRectCenterY", JASS_GetRectCenterY);
,
lua_register(L, "MoveRectTo", JASS_MoveRectTo);
,
lua_register(L, "MoveRectToLoc", JASS_MoveRectToLoc);
,
lua_register(L, "GetRectMinX", JASS_GetRectMinX);
,
lua_register(L, "GetRectMinY", JASS_GetRectMinY);
,
lua_register(L, "GetRectMaxX", JASS_GetRectMaxX);
,
lua_register(L, "GetRectMaxY", JASS_GetRectMaxY);
,
lua_register(L, "GetWorldBounds", JASS_GetWorldBounds);
,
lua_register(L, "DestroyFogModifier", JASS_DestroyFogModifier);
,
lua_register(L, "FogModifierStart", JASS_FogModifierStart);
,
lua_register(L, "FogModifierStop", JASS_FogModifierStop);
,
lua_register(L, "CreateTrigger", JASS_CreateTrigger);
,
lua_register(L, "DestroyTrigger", JASS_DestroyTrigger);
,
lua_register(L, "ResetTrigger", JASS_ResetTrigger);
,
lua_register(L, "EnableTrigger", JASS_EnableTrigger);
,
lua_register(L, "DisableTrigger", JASS_DisableTrigger);
,
lua_register(L, "GetEventGameState", JASS_GetEventGameState);
,
lua_register(L, "GetClickedButton", JASS_GetClickedButton);
,
lua_register(L, "GetClickedDialog", JASS_GetClickedDialog);
,
lua_register(L, "GetTournamentFinishSoonTimeRemaining", JASS_GetTournamentFinishSoonTimeRemaining);
,
lua_register(L, "GetTournamentFinishNowRule", JASS_GetTournamentFinishNowRule);
,
lua_register(L, "GetTournamentFinishNowPlayer", JASS_GetTournamentFinishNowPlayer);
,
lua_register(L, "GetTournamentScore", JASS_GetTournamentScore);
,
lua_register(L, "GetSaveBasicFilename", JASS_GetSaveBasicFilename);
,
lua_register(L, "GetWinningPlayer", JASS_GetWinningPlayer);
,
lua_register(L, "GetEventPlayerState", JASS_GetEventPlayerState);
,
lua_register(L, "GetAttacker", JASS_GetAttacker);
,
lua_register(L, "GetRescuer", JASS_GetRescuer);
,
lua_register(L, "GetDyingUnit", JASS_GetDyingUnit);
,
lua_register(L, "GetKillingUnit", JASS_GetKillingUnit);
,
lua_register(L, "GetDecayingUnit", JASS_GetDecayingUnit);
,
lua_register(L, "GetConstructingStructure", JASS_GetConstructingStructure);
,
lua_register(L, "GetCancelledStructure", JASS_GetCancelledStructure);
,
lua_register(L, "GetConstructedStructure", JASS_GetConstructedStructure);
,
lua_register(L, "GetTrainedUnitType", JASS_GetTrainedUnitType);
,
lua_register(L, "GetResearchingUnit", JASS_GetResearchingUnit);
,
lua_register(L, "GetResearched", JASS_GetResearched);
,
lua_register(L, "GetTrainedUnit", JASS_GetTrainedUnit);
,
lua_register(L, "GetSellingUnit", JASS_GetSellingUnit);
,
lua_register(L, "GetSoldUnit", JASS_GetSoldUnit);
,
lua_register(L, "GetBuyingUnit", JASS_GetBuyingUnit);
,
lua_register(L, "GetSoldItem", JASS_GetSoldItem);
,
lua_register(L, "GetChangingUnit", JASS_GetChangingUnit);
,
lua_register(L, "GetChangingUnitPrevOwner", JASS_GetChangingUnitPrevOwner);
,
lua_register(L, "GetDetectedUnit", JASS_GetDetectedUnit);
,
lua_register(L, "GetOrderedUnit", JASS_GetOrderedUnit);
,
lua_register(L, "OrderId", JASS_OrderId);
,
lua_register(L, "OrderId2String", JASS_OrderId2String);
,
lua_register(L, "AbilityId", JASS_AbilityId);
,
lua_register(L, "AbilityId2String", JASS_AbilityId2String);
,
lua_register(L, "UnitId", JASS_UnitId);
,
lua_register(L, "UnitId2String", JASS_UnitId2String);
,
lua_register(L, "GetObjectName", JASS_GetObjectName);
,
lua_register(L, "GetIssuedOrderId", JASS_GetIssuedOrderId);
,
lua_register(L, "GetOrderPointX", JASS_GetOrderPointX);
,
lua_register(L, "GetOrderPointY", JASS_GetOrderPointY);
,
lua_register(L, "GetOrderPointLoc", JASS_GetOrderPointLoc);
,
lua_register(L, "GetOrderTarget", JASS_GetOrderTarget);
,
lua_register(L, "GetOrderTargetDestructable", JASS_GetOrderTargetDestructable);
,
lua_register(L, "GetOrderTargetItem", JASS_GetOrderTargetItem);
,
lua_register(L, "GetOrderTargetUnit", JASS_GetOrderTargetUnit);
,
lua_register(L, "GetSpellAbilityUnit", JASS_GetSpellAbilityUnit);
,
lua_register(L, "GetSpellAbilityId", JASS_GetSpellAbilityId);
,
lua_register(L, "GetSpellAbility", JASS_GetSpellAbility);
,
lua_register(L, "GetSpellTargetLoc", JASS_GetSpellTargetLoc);
,
lua_register(L, "GetSpellTargetX", JASS_GetSpellTargetX);
,
lua_register(L, "GetSpellTargetY", JASS_GetSpellTargetY);
,
lua_register(L, "GetSpellTargetDestructable", JASS_GetSpellTargetDestructable);
,
lua_register(L, "GetSpellTargetItem", JASS_GetSpellTargetItem);
,
lua_register(L, "GetSpellTargetUnit", JASS_GetSpellTargetUnit);
,
lua_register(L, "GetLevelingUnit", JASS_GetLevelingUnit);
,
lua_register(L, "GetLearningUnit", JASS_GetLearningUnit);
