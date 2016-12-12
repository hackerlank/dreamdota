#include "stdafx.h"
#ifndef UNIT_STATE_TAG_INCLUDED
#define UNIT_STATE_TAG_INCLUDED
#include "UISimpleFrame.h"
#include "UISimpleFontString.h"
#include "UISimpleTexture.h"
#include "Jass.h"

class UnitStateTag {
public:
	UnitStateTag();
	~UnitStateTag();

	void setOwner(unit unitHandle);
	void show() {this->frame_->show();};
	void hide() {this->frame_->hide();};
	void update();

private:
	static bool showMaxValue_;
	unit unitHandle_;
	war3::CUnit* unitObj_;
	UISimpleFrame* frame_;
	UISimpleFontString* textHpShadow_;
	UISimpleFontString* textHp_;
	UISimpleFontString* textManaShadow_;
	UISimpleFontString* textMana_;	
};

#endif