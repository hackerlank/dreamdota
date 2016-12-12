#include "stdafx.h"
#ifndef PRESELECTUIBIND_H_INCLUDED
#define PRESELECTUIBIND_H_INCLUDED

#include "RefreshManager.h"
#include "GameStructs.h"
#include "UIStructs.h"
class Unit;
class UnitStateTag;

namespace PreselectUIBind {
	class PreselectUIBindRefreshObject : public RefreshObject {
	public:
		PreselectUIBindRefreshObject();

		~PreselectUIBindRefreshObject();

		void refresh();

		bool isCompleted();
	private:
		struct PreselectUIBindInfo {
			uint32_t marker;			//标记单位是否有preSelectUI

			war3::CStatBar* manaBar;
			uint32_t marker_manaBar;	//标记单位是否要显示蓝条

			UnitStateTag* stateTag;
			uint32_t marker_stateTag;	//标记单位是否显示状态信息
		};

		std::map<war3::CUnit*, PreselectUIBindInfo> unitBindMap_;
	};
	void Init();
	void Cleanup();
}

#endif