#ifndef TEXTTAGMANAGER_H_
#define TEXTTAGMANAGER_H_

#include "TextTagManagerStructs.h"

void TextTagManager_Init();
void TextTagManager_Update(); //时机找不准

war3::CTextTagManager* GetJassTTM();
war3::CTextTagManager* GetMapTTM();

war3::CTextTagManager* CreateTextTagManager(const char* fontName, double size); //创建出来除非替换系统原有的，否则不显示
void DestroyTextTagManager(war3::CTextTagManager* m);

uint32_t TTMCreateTag(war3::CTextTagManager* m, const char* text, double size);
void TTMSetTagPos(war3::CTextTagManager* m, uint32_t tagId, float x, float y, float heightOffset);
void TTMSetTagPos3D(war3::CTextTagManager* m, uint32_t tagId, float x, float y, float z);
void TTMSetTagText(war3::CTextTagManager* m, uint32_t tagId, const char* text, float size);
void TTMSetTagColor(war3::CTextTagManager* m, uint32_t tagId, uint32_t color);
void TTMSetTagVelocity(war3::CTextTagManager* m, uint32_t tagId, float x, float y);
void TTMSetTagVisibility(war3::CTextTagManager* m, uint32_t tagId, bool v);
void TTMSetTagSuspended(war3::CTextTagManager* m, uint32_t tagId, bool v);
void TTMSetTagPermanent(war3::CTextTagManager* m, uint32_t tagId, bool v);
void TTMSetTagAge(war3::CTextTagManager* m, uint32_t tagId, float v);
void TTMSetTagLifespan(war3::CTextTagManager* m, uint32_t tagId, float v);
void TTMSetTagFadepoint(war3::CTextTagManager* m, uint32_t tagId, float v);
uint32_t TTMDestroyTag(war3::CTextTagManager* m, uint32_t tagId);


#endif