#include "stdafx.h"

#ifndef DEBUG_TEXT_PANEL_H_INCLUDED
#define DEBUG_TEXT_PANEL_H_INCLUDED

#include <math.h>
#include <string>

#include "UISimpleFrame.h"
#include "UISimpleFontString.h"
#include "UISimpleTexture.h"

#include "GameStructs.h"
#include "RefreshManager.h"
#include "Unit.h"
#include "Tools.h"

#include "IUIObject.h"

#define FONT_HEIGHT 0.010f
#define NAME_VALUE_MARGIN 0.01f

class DebugPanel;

struct DebugPanelRow {
	UISimpleFontString* name;
	UISimpleFontString* value;
};

class DebugPanelRowMapKeyCompare {
	public:
		bool operator()(const std::string& l, const std::string& r) const { return strcmp(l.c_str(), r.c_str()) < 0; }
};

typedef std::list<DebugPanel*> DebugPanelListType;
typedef std::map<std::string, DebugPanelRow, DebugPanelRowMapKeyCompare> DebugPanelRowMapType; 
typedef void (*DebugPanelUpdateFunctionType)(DebugPanel* t);

extern DebugPanelListType InstanceList;
extern FramePoint TempFramePoint;

class DebugPanel {
public:
	DebugPanel() {
		this->needRearrange_ = false;
		this->hideName_ = false;
		this->maxNameWidth_ = 0.0f;
		this->frame_ = UISimpleFrame::Create();
		this->bg_ = UISimpleTexture::Create(this->frame_);
		this->bg_->fillColor(0x90000000);
		this->bg_->setRelativeObject(this->frame_);
		this->parent_ = NULL;
		this->updateFunc_ = NULL;
	}

	~DebugPanel() {
		clear();
		UISimpleFrame::Destroy(this->frame_);
	}

	void clear() {
		for (DebugPanelRowMapType::iterator iter = this->rowMap_.begin();
			iter != this->rowMap_.end();
			++iter)
		{
			UISimpleFontString::Destroy(iter->second.name);
			UISimpleFontString::Destroy(iter->second.value);
		}
		rowMap_.clear();
	}

	UISimpleFrame* frame() {return this->frame_;}

	void setUpdateFunction(DebugPanelUpdateFunctionType func) {
		this->updateFunc_ = func;
	}

	void update() {
		if (this->needRearrange_) {
			this->needRearrange_ = false;
			this->arrangeRows();
		}

		if (this->parent_) {
			if (GetUnitFramePoint(UnitGetObject(this->parent_->handleId()), &TempFramePoint)) {
				this->frame_->show();
				this->frame_->setAbsolutePosition(UILayoutFrame::POSITION_BOTTOM_CENTER, TempFramePoint.x, TempFramePoint.y);
			} else {
				this->frame_->hide();
			}

			if (this->updateFunc_)
				this->updateFunc_(this);
		}
	}

	void set(std::string key, const char *format, ...)
	{
		char buffer[256];
		int rv;
		va_list args;
		va_start(args, format);
		rv = vsprintf_s(buffer, 255, format, args);
		va_end(args);

		if (this->rowMap_.count(key) == 0) {
			DebugPanelRow& row = this->rowMap_[key];
			row.name = UISimpleFontString::Create(this->frame_);
			row.name->initFont(UIObject::GetPathByName("MasterFont"), FONT_HEIGHT, false);
			row.name->setText(key.c_str());
			float w = row.name->getTextWidth();
			this->maxNameWidth_ = max(this->maxNameWidth_, w);
			
			row.value = UISimpleFontString::Create(this->frame_);
			row.value->initFont(UIObject::GetPathByName("MasterFont"), FONT_HEIGHT, false);
		}

		this->rowMap_[key].value->setText(buffer);
		this->needRearrange_ = true;
	}

	void setShowName(bool flag) {
		this->hideName_ = !flag;
		this->needRearrange_ = true;
	}

	Unit* parent() {return this->parent_;}
	void setParent(Unit* parent) {this->parent_ = parent;}
private:
	void arrangeRows() {
		float maxRowWidth = 0.0;
		float y = 0.0;
		float x = 0.0;
		bool hideName = this->hideName_;

		//¿í¶Èµ÷Õû
		for (DebugPanelRowMapType::iterator iter = this->rowMap_.begin();
			iter != this->rowMap_.end();
			++iter)
		{
			float rowWidth = 
				(hideName ? 0 : this->maxNameWidth_ )
				+ iter->second.value->getTextWidth() + NAME_VALUE_MARGIN;
			maxRowWidth = max(rowWidth, maxRowWidth);

			DebugPanelRow& row = iter->second;
			row.name->setRelativePosition(POS_UL, this->frame_, POS_UL, x, -y);
			if (hideName)row.name->setColorFloat(0,0,0,0);
			row.value->setRelativePosition(
				POS_UL, 
				row.name, 
				POS_UL, 
				hideName ? (x + NAME_VALUE_MARGIN / 2) : (x + this->maxNameWidth_ + NAME_VALUE_MARGIN), 
				0.f
			);

			y += FONT_HEIGHT;
		}

		this->frame_->setWidth(maxRowWidth);
		this->frame_->setHeight(y);
		this->frame_->applyPosition();
	}

	UISimpleTexture* bg_;
	UISimpleFrame* frame_;
	Unit* parent_;
	DebugPanelRowMapType rowMap_;
	bool needRearrange_;
	bool hideName_;
	float maxNameWidth_;
	DebugPanelUpdateFunctionType updateFunc_;
};

class DebugPanelRefeshObject : public RefreshObject {
public:
	DebugPanelRefeshObject() : RefreshObject(true) {

	}

	virtual void refresh() {
		for (DebugPanelListType::iterator iter = InstanceList.begin(); iter != InstanceList.end(); ++iter) {
			(*iter)->update();
		}
	}

	virtual bool isCompleted() {
		return false;	
	}
};

inline DebugPanel* GetDebugPanel(Unit* parent = NULL, DebugPanelUpdateFunctionType updateFunc = NULL) {
	DebugPanel* rv = new DebugPanel();
	if (parent)
		rv->setParent(parent);
	if (updateFunc)
		rv->setUpdateFunction(updateFunc);
	InstanceList.push_back(rv);
	return rv;
}

extern DebugPanel* DefaultDebugPanel;

inline void DebugPanel_Init() {
	RefreshManager_AddObject(new DebugPanelRefeshObject());
#ifndef _VMP
	DefaultDebugPanel = GetDebugPanel();
	DefaultDebugPanel->frame()->setRelativePosition(
		UILayoutFrame::POSITION_TOP_RIGHT, 
		&UISimpleFrame(GameUIObjectGet()->resourceBar), 
		UILayoutFrame::POSITION_BOTTOM_RIGHT, 
		-.01f, 
		-.03f
	);
#endif
}

inline void DebugPanel_Cleanup() {
	for (DebugPanelListType::iterator iter = InstanceList.begin(); iter != InstanceList.end(); ++iter) {
		delete *iter;
	}

	InstanceList.clear();
}

#endif