#include "stdafx.h"
#include "UnitPanel.h"
#include "UISimpleFrame.h"

// 
// UnitPanel::UnitPanel( IUIObject *parent, float height, int player )
// 	: Frame(parent, 0.01f, height), ownerPlayer(player), height(height),currentWidth(),
// 	units(NULL), bWantRefresh(false)
// {
// 	refresh();
// 	bWantRefresh = true;
// }
// 
// UnitPanel::~UnitPanel()
// {
// 	for (std::map<uint32_t, MultiIcon*>::iterator iter = typedIcons.begin(); 
// 		iter != typedIcons.end(); ++iter)
// 	{
// 		if(iter->second) delete iter->second;
// 	}
// 	if (units) GroupDestroy(units);
// }
// 
// void UnitPanel::refresh()
// {
// 	Frame::refresh();
// 	
// 	UnitGroup *g_Current = GroupUnits(NULL, NULL, PlayerGroupSingle(ownerPlayer), NULL, 
// 		UnitFilter(
// 		NULL, 
// 		UnitFilter::STRUCTURE | UnitFilter::WARD
// 		)
// 	);
// 
// 	if (units)
// 	{
// 		units->remove(g_Current);//判断上一次是否有单位类型消失了
// 		uint32_t typeId;
// 		GroupForEachUnit(units, u,
// 			typeId = u->typeId();
// 			if (typedIcons.count(typeId) && typedIcons[typeId] != NULL)
// 			{
// 				delete typedIcons[typeId];
// 				typedIcons.erase(typeId);
// 			}
// 		);
// 		GroupDestroy(units);
// 	}
// 	units = g_Current;
// 
// 	std::map<uint32_t, uint32_t> unitCountMap;
// 	GroupForEachUnit(units, u,
// 		if (u->abilityLevel('Aloc') > 0)//蝗虫
// 		{
// 			continue;
// 		}
// 		unitCountMap[u->typeId()]+=1; 
// 	);
// 
// 	uint32_t iconCount = unitCountMap.size();
// 	float padding = 0.001f * height / 0.03f;
// 	float w = iconCount * (height) + (iconCount-1) * padding;
// 	setWidth(w);
// 	currentWidth = w;
// 	getFrame()->applyPosition();
// 
// 	MultiIcon *last = NULL;
// 	for (std::map<uint32_t, uint32_t>::iterator iter = unitCountMap.begin();
// 		iter != unitCountMap.end(); ++iter)
// 	{
// 		uint32_t typeId = iter->first;
// 		MultiIcon *mi;
// 		if (!typedIcons.count(typeId))
// 		{
// 			mi = new MultiIcon(this, height, height);
// 			mi->setTextureById(iter->first);
// 			mi->setCorner("%d", iter->second);
// 			mi->showMiddle(false);
// 			mi->showCorner(true);
// 			mi->setOwner(this);
// 			typedIcons[typeId] = mi;
// 		}
// 		else
// 		{
// 			mi = typedIcons[typeId];
// 			mi->setCorner("%d", iter->second);//设置数量
// 			//TODO 更多状态例如死亡等
// 		}
// 
// 		if (last)
// 			mi->setRelativePosition(POS_L, last, POS_R, padding, 0);
// 		else
// 			mi->setRelativePosition(POS_L, this, POS_L);
// 		last = mi;
// 	}
// 	
// }
// 
// void UnitPanel::tick()
// {
// 	Frame::tick();
// 	if (bWantRefresh)
// 	{
// 		bWantRefresh = false;
// 		refresh();
// 	}
// }
// 
// void UnitPanel::setAbsolutePosition( uint32_t originPos, float absoluteX, float absoluteY )
// {
// 	Frame::setAbsolutePosition(originPos, absoluteX, absoluteY);
// 	bWantRefresh = true;
// }
// 
// void UnitPanel::setRelativePosition( uint32_t originPos, IUIObject* target, uint32_t toPos, float relativeX /*= 0*/, float relativeY /*= 0 */ )
// {
// 	Frame::setRelativePosition(originPos, target, toPos, relativeX, relativeY);
// 	bWantRefresh = true;
// }
// 
// void UnitPanel::setRelativePosition( uint32_t originPos, UILayoutFrame* target, uint32_t toPos, float relativeX /*= 0*/, float relativeY /*= 0 */ )
// {
// 	Frame::setRelativePosition(originPos, target, toPos, relativeX, relativeY);
// 	bWantRefresh = true;
// }
