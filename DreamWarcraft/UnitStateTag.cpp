#include "stdafx.h"
#include "UnitStateTag.h"
#include "Tools.h"
#include "Player.h"
#include "Profile.h"
//#define max(a,b) (((a) > (b)) ? (a) : (b))	//这是干吗?

static const float FRAME_PADDING			= 0.002f;
static const float PLAYERNAME_FONT_HEIGHT	= 0.012f;

static const float TEXT_MARGIN_X			= 0.0016f;//0.0075f;
static const float TEXT_MARGIN_Y			= 0.0004f;//0.005f;
static const float TEXT_SHADOW_OFFSET_X		= 0.00115f;
static const float TEXT_SHADOW_OFFSET_Y		= -0.00115f;
static UILayoutFrame TempLF;
static UISimpleFrame TempSF;
static UISimpleTexture TempST;

bool UnitStateTag::showMaxValue_ = false;
static bool showMaxValueInitDone = false;

UnitStateTag::UnitStateTag() {
	if(!showMaxValueInitDone) { showMaxValue_ = ProfileFetchInt("StateTag", "ShowMaxValues", 0) >= 1; showMaxValueInitDone = true; }

	const char *font = ProfileFetchInt("StateTag", "UseCustomFont", 1) ?
		ProfileFetchString("StateTag", "CustomFont", 
		"DreamDota3\\Fonts\\AARDV.ttf"
		):
		UIObject::GetPathByName("MasterFont");

	float fontSize = ProfileFetchFloat("StateTag", "FontSize", 4.f);
	float fontHeight = (float)(fontSize * 0.0234375 / 10);

	this->frame_ = UISimpleFrame::Create(UIObject::GetGameSimpleConsole());//TODO create到血条上
	this->frame_->setHeight((fontHeight + TEXT_MARGIN_Y) * 2);
	
	float y = 0.f;
	y -= (TEXT_MARGIN_Y);

	this->textHpShadow_ = UISimpleFontString::Create(this->frame_);
	this->textHpShadow_->initFont(font, fontHeight, 1);
	this->textHpShadow_->setRelativePosition(UILayoutFrame::POSITION_TOP_CENTER, this->frame_, UILayoutFrame::POSITION_TOP_CENTER, TEXT_SHADOW_OFFSET_X, TEXT_SHADOW_OFFSET_Y);
	this->textHpShadow_->setColor(0xFF000000);

	this->textHp_ = UISimpleFontString::Create(this->frame_);
	this->textHp_->initFont(font, fontHeight, 1);
	this->textHp_->setRelativePosition(UILayoutFrame::POSITION_TOP_CENTER, this->frame_, UILayoutFrame::POSITION_TOP_CENTER, 0, y);	

	y -= (fontHeight);

	this->textManaShadow_ = UISimpleFontString::Create(this->frame_);
	this->textManaShadow_->initFont(font, fontHeight, 1);
	this->textManaShadow_->setRelativePosition(UILayoutFrame::POSITION_TOP_CENTER, this->frame_, UILayoutFrame::POSITION_TOP_CENTER, TEXT_SHADOW_OFFSET_X, TEXT_SHADOW_OFFSET_Y + y);
	this->textManaShadow_->setColor(0xFF000000);

	this->textMana_ = UISimpleFontString::Create(this->frame_);
	this->textMana_->initFont(font, fontHeight, 1);
	this->textMana_->setRelativePosition(UILayoutFrame::POSITION_TOP_CENTER, this->frame_, UILayoutFrame::POSITION_TOP_CENTER, 0, y);
	this->textMana_->setColor(0xFFFFFFFF);

	this->frame_->hide();
}

UnitStateTag::~UnitStateTag() {
	UISimpleFontString::Destroy(this->textHp_);
	UISimpleFontString::Destroy(this->textHpShadow_);
	UISimpleFontString::Destroy(this->textMana_);
	UISimpleFontString::Destroy(this->textManaShadow_);
	UISimpleFrame::Destroy(this->frame_);
}

void UnitStateTag::setOwner(unit unitHandle) {
	if (NULL != (this->unitObj_ = UnitGetObject(unitHandle))) {
		this->unitHandle_ = unitHandle;
	} else {
		this->unitHandle_ = NULL;
	}

	if (this->unitHandle_ == NULL)
		this->frame_->hide();
	else
		this->frame_->show();
}

static char Buffer[100];
void UnitStateTag::update() {
	if (this->unitHandle_) {
		war3::CStatBar* hpBar = this->unitObj_->preSelectUI->statBarHP;
		if (hpBar && hpBar->baseSimpleStatusBar.baseSimpleFrame.visible) {
			
			float hp = Jass::GetUnitState(this->unitHandle_, Jass::UNIT_STATE_LIFE);
			float hpMax = Jass::GetUnitState(this->unitHandle_, Jass::UNIT_STATE_MAX_LIFE);
			float mp = Jass::GetUnitState(this->unitHandle_, Jass::UNIT_STATE_MANA);
			float mpMax = Jass::GetUnitState(this->unitHandle_, Jass::UNIT_STATE_MAX_MANA);
			
			if (showMaxValue_) sprintf_s(Buffer, 99, "%.0f / %.0f", hp, hpMax);
			else sprintf_s(Buffer, 99, "%.0f", hp);
			this->textHp_->setText(Buffer);
			this->textHpShadow_->setText(Buffer);
			
			war3::CSimpleTexture *hpbarColorTexture = this->unitObj_->preSelectUI->statBarHP->baseSimpleStatusBar.texture;
			war3::CSimpleRegion *hpbarRegion = &(hpbarColorTexture->baseSimpleRegion);
			this->textHp_->setColor(
				hpbarRegion->colorAlpha << 0x18	| 
				hpbarRegion->colorRed << 0x10	|	
				hpbarRegion->colorGreen << 0x8	|
				hpbarRegion->colorBlue
			);

			if (ProfileGetBool("ManaBar", "Enable", true) && mpMax > 0 ){
				if (showMaxValue_) sprintf_s(Buffer, 99, "%.0f / %.0f", mp, mpMax);
				else sprintf_s(Buffer, 99, "%.0f", mp);
				this->textMana_->setText(Buffer);
				this->textManaShadow_->setText(Buffer);
			}
			else {
				this->textMana_->setText("");
				this->textManaShadow_->setText("");
			}

			float textWidth = max(this->textHp_->getTextWidth(), this->textMana_->getTextWidth());
			this->frame_->setWidth(textWidth + (2 * TEXT_MARGIN_X));
			TempLF.setBase(hpBar);
			this->frame_->setRelativePosition(UILayoutFrame::POSITION_CENTER, &TempLF, UILayoutFrame::POSITION_BOTTOM_CENTER, 0.f, 0.f);

			this->frame_->show();

			//移动默认的UnitTip使之不挡住数字
			if (ObjectUnderCursorGet() == this->unitObj_) {
				TempSF.setBase(DefaultUnitTipGet());
				TempSF.setRelativePosition(UILayoutFrame::POSITION_BOTTOM_CENTER, this->frame_, UILayoutFrame::POSITION_TOP_CENTER, 0.f, 0.004f);

				////change color for unit under mouse selection
				//Jass::SetUnitVertexColor(this->unitHandle_, 192, 255, 192, 255);
				//float f = 1.2f;
				//Jass::SetUnitScale(this->unitHandle_, f, f, f);
			}
			//else
			//{
			//	Jass::SetUnitVertexColor(this->unitHandle_, 255, 255, 255, 255);
			//	Jass::SetUnitScale(this->unitHandle_, 1.f, 1.f, 1.f);
			//}
			
		} else
			this->frame_->hide();
	}
}