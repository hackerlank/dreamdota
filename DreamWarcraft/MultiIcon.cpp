#include "stdafx.h"
#include "MultiIcon.h"

#include "UISimpleFrame.h"
#include "UISimpleTexture.h"
#include "UISimpleButton.h"
#include "Label.h"
#include "Bar.h"
#include "Tools.h"
#include "UnitGroup.h"
#include "Timer.h"
#include "Observer.h"
#include "EventData.h"

const char* DisBtnPathCalc(const char* src) {
	static char RETURN_BUFFER[256];
	const char* add = "Disabled\\DIS";
	const char* path = "ReplaceableTextures\\CommandButtons";

	size_t add_size = strlen(add);
	RETURN_BUFFER[0] = 0;
	size_t src_size = strlen(src);
	if (src_size) {
		const char* pos = strrchr(src, '\\');
		if (pos != NULL) {
			size_t path_size = strlen(path);
			size_t pre_size = static_cast<size_t>(pos - src);
			size_t filename_size = src_size - pre_size - 1;
			if (pre_size + add_size + filename_size < sizeof(RETURN_BUFFER)) {
				size_t copy_offset = 0;
				memcpy_s(RETURN_BUFFER, sizeof(RETURN_BUFFER), path, path_size);
				copy_offset += path_size;
				memcpy_s(RETURN_BUFFER + copy_offset, sizeof(RETURN_BUFFER) - copy_offset, add, add_size);
				copy_offset += add_size;
				memcpy_s(RETURN_BUFFER + copy_offset, sizeof(RETURN_BUFFER) - copy_offset, pos + 1, filename_size);
				copy_offset += filename_size;
				RETURN_BUFFER[copy_offset] = 0;
			}
		}
	}
	return RETURN_BUFFER;
}

static const float CORNER_FRAME_RELSIZE = 0.4f;
static const float CORNER_FRAME_BORDER_RELOFFSET = 0.02f;
static const float CORNER_LABEL_RELSIZE = 0.85f;
//static const float BOTTOM_OBJECT_RELSIZE = 0.35f;
static const float BOTTOM_OBJECT_BORDER_RELOFFSET = 0.03f;
static char  *BOTTOM_LABEL_FONT;
	//"DreamDota3\\Fonts\\AARDV.ttf";

void MultiIconClickHandler (Observer* ob, uint32_t evtId)
{
	MultiIcon *icon = *(ob->data<MultiIcon*>());
	UnitGroup *g = icon->clickerJumpGroup;
	if (g != NULL && g->size() > 0)
	{
		bool bBreak = false;
		while (!bBreak)
		{
			if (icon->clickJumpIndex >= (int)g->size())
			{
				icon->clickJumpIndex = 0;
			}
			Unit *u = g->getUnit(icon->clickJumpIndex);
			if ( u != NULL ) //TODO
			{
				bool bIsReplay = (ReplayState() == REPLAY_STATE_STREAMINGOUT );
				if (bIsReplay)
				{
					//TODO
				}
				else
				{
					if (	Jass::IsPlayerObserver(Jass::Player(PlayerLocal())) 
						||	u->testFlag(UnitFilter::VISIBLE, PlayerLocal()) 	)
					{
						Jass::ClearSelection();
						Jass::SelectUnit(u->handleId(), true);
					}
				}
				Jass::SetCameraPosition(u->x(), u->y());
				bBreak = true;
			}
			icon->clickJumpIndex += 1;
		}
	}
}

MultiIcon::MultiIcon (
	IUIObject	*parent,
	float		width,
	float		height,
	const char	*texturePath,
	const char	*disabledTexturePath,
	bool		showPassive,
	bool		showBottom,
	float		bottomFactor	)
	: Texture (parent, width, height), bWantRefresh(false),
	iconWidth(width), iconHeight(height), id(0), idIndex(0xFFFFFFFF), bShowPassiveCover(showPassive), bShowBottom(showBottom), bottomFactor(bottomFactor)
{
	bCornerInited = false;

	if (BOTTOM_LABEL_FONT == NULL)
	{
		BOTTOM_LABEL_FONT = "DreamDota3\\Fonts\\AARDV.ttf";//(char *)Skin::getPathByName("MasterFont");
	}

	relFactor = 1;
	if (bShowBottom)
	{
		relFactor = height / (height + bottomFactor * height + 
			BOTTOM_OBJECT_BORDER_RELOFFSET * height
		);
	}

	//大框
	setWidth(width * relFactor);
	setHeight(height * relFactor);

	wholeFrame = UISimpleFrame::Create(parent ? parent->getFrame() : NULL);
	wholeFrame->setWidth(width * relFactor);
	wholeFrame->setHeight(height);
	wholeFrame->setRelativePosition(POS_T, Texture::getFrame(), POS_T, 0, 0);

	passiveCover = new Texture(Texture::getFrame(), 
		width * relFactor, 
		height * relFactor,
		"DreamDota3\\Textures\\PassiveButtonCover.tga",
		"DreamDota3\\Textures\\PassiveButtonCover.tga");
	passiveCover->setRelativePosition(POS_C, Texture::getFrame(), POS_C);
	passiveCover->setColor(bShowPassiveCover ? Color::WHITE : Color(0.f, 0, 0, 0));

	cornerFrame = UISimpleFrame::Create(Texture::getFrame());
	cornerFrame->setWidth(width* relFactor * CORNER_FRAME_RELSIZE);
	cornerFrame->setHeight(height* relFactor * CORNER_FRAME_RELSIZE);
	cornerFrame->setBackground("DreamDota3\\Textures\\GreyBackground.tga");
	cornerFrame->setPadding(0.002f);//TODO调整
	cornerFrame->setBorder("UI\\Widgets\\ToolTips\\Human\\human-tooltip-border.blp");
	cornerFrame->setBorderWidth(0.005f);//TODO调整
	cornerFrame->applyTextureSettings();
	cornerFrame->setRelativePosition(POS_BR, Texture::getFrame(), POS_BR, -CORNER_FRAME_BORDER_RELOFFSET * width, CORNER_FRAME_BORDER_RELOFFSET * height);
	
	cornerLabel = new Label( cornerFrame, "?", 
		relFactor * CORNER_LABEL_RELSIZE * CORNER_FRAME_RELSIZE * height, Color::WHITE );
	cornerLabel->setRelativePosition(POS_C, cornerFrame, POS_C);
	
	bottomLabel = new Label( Texture::getFrame(), "0", 
		relFactor * bottomFactor * height, Color::WHITE, LABEL_TEXT_DISABLED_COLOR, LABEL_SHADOW_COLOR, BOTTOM_LABEL_FONT, false);
	bottomLabel->setRelativePosition(POS_T, Texture::getFrame(), POS_B, 0, -BOTTOM_OBJECT_BORDER_RELOFFSET * height);
	bottomLabel->show(bShowBottom);

	bottomBar = new Bar ( 
		NULL,
		width * relFactor * 0.9f, 
		width * relFactor * 0.1875f * 0.9f,
		NULL,
		"UI\\Feedback\\BuildProgressBar\\human-buildprogressbar-border.blp",
		"UI\\Feedback\\BuildProgressBar\\human-buildprogressbar-fill.blp"
	);
	bottomBar->setParent(Texture::getFrame());
	bottomBar->setRelativePosition(POS_T, this, POS_B, 0, -bottomFactor * height);
	bottomBar->show(bShowBottom);

	//TODO refresh以下
	clickerOb = Observer::Create(MultiIconClickHandler);
	MultiIcon *_this = this;
	clickerOb->setData<MultiIcon*>(&_this);
	clicker = UISimpleButton::Create(
		wholeFrame, 
		width * relFactor, width * relFactor,
		NULL, NULL, NULL, UISimpleButton::MOUSEBUTTON_LEFT, UISimpleButton::STATE_ENABLED
	);
	clicker->setClickEventObserver(EVENT_CLICK, clickerOb);
	clicker->setRelativePosition(POS_T, wholeFrame, POS_T, 0, 0);

	clickerJumpGroup = new UnitGroup();
	clickJumpIndex = 0;
}

MultiIcon::~MultiIcon ()
{
	delete clickerJumpGroup;
	UISimpleButton::Destroy(clicker);
	Observer::Destroy(clickerOb);

	delete bottomBar;
	delete bottomLabel;
	delete cornerLabel;
	UISimpleFrame::Destroy(cornerFrame);
	delete passiveCover;
	UISimpleFrame::Destroy(wholeFrame);
}

void MultiIcon::setTextureById ( uint32_t objectId, uint32_t index )
{
	if (id == objectId && idIndex == index)
	{
		return;
	}
	id = objectId;
	idIndex = index;
	char *iconPath = ((id>>0x18) & 0xFF)=='B' ?
		GetBuffIconFromFuncProfile(id, idIndex) :
		GetIconFromFuncProfile(id, idIndex);
	const char *iconDisPath;
	if (iconPath)
	{
		iconDisPath = DisBtnPathCalc(iconPath);
		setTexture (iconPath, iconDisPath);
	}
	bWantRefresh = true;
}

void MultiIcon::showCorner( bool flag , Color color /*= Color::WHITE */ )
{
	cornerLabel->setTextColor(color);
	if (flag) cornerFrame->show( );
	else cornerFrame->hide( );
}

void MultiIcon::setCorner (const char *format, ...)
{
	char buffer[8];
	va_list args;
	va_start(args, format);
	vsprintf_s(buffer, 8, format, args);
	va_end(args);
	if (cornerLabelContent.compare(buffer)==0)
	{
		if ( !bCornerInited )
		{
			bCornerInited = true;
		}
		else
		{
			return;
		}
	}
	cornerLabelContent.assign(buffer);
	cornerLabel->setText(cornerLabelContent.c_str());
	bWantRefresh = true;
}

void MultiIcon::showBottom ( MultiIconBottomType type )
{
	switch (type)
	{
	case TypeNone:
		bottomLabel->show( false );
		bottomBar->show( false );
		break;
	case TypeText:
		bottomLabel->show( true );
		bottomBar->show( false );
		break;
	case TypeBar:
		bottomLabel->show( false );
		bottomBar->show( true );
		break;
	default:
		bottomLabel->show( false );
		bottomBar->show( false );
		break;
	}
}

void MultiIcon::setBottomLabel (const char *format, ...)
{
	char buffer[16];
	va_list args;
	va_start(args, format);
	vsprintf_s(buffer, 16, format, args);
	va_end(args);
	bottomLabel->setText(buffer);
}

void MultiIcon::setBottomBar( float percent )
{
	bottomBar->setPercent(percent);
}

void MultiIcon::tick()
{
	Texture::tick();
	if (bWantRefresh)
	{
		refresh();
		bWantRefresh = false;
	}
}

void MultiIcon::refresh()
{
	Texture::refresh();

	wholeFrame->setParent(Frame::getFrame());
	wholeFrame->setWidth(Texture::getShouldWidth());
	wholeFrame->setRelativePosition(POS_T, Texture::getFrame(), POS_T, 0, 0);

	passiveCover->setParent(Texture::getFrame());
	passiveCover->setWidth(Texture::getShouldWidth());
	passiveCover->setHeight(Texture::height());
	passiveCover->setRelativePosition(POS_C, Texture::getFrame(), POS_C, 0, 0);
	passiveCover->setColor(bShowPassiveCover ? Color::WHITE : Color(0.f, 0, 0, 0));

	cornerFrame->setParent(bShowPassiveCover ? passiveCover->getFrame() : Texture::getFrame());
	cornerFrame->setWidth( 
		max(Texture::getShouldWidth() * CORNER_FRAME_RELSIZE, 
		cornerLabel->getTextWidth() / CORNER_LABEL_RELSIZE + 0.002f )
	);
	cornerFrame->setRelativePosition(POS_BR, wholeFrame, POS_BR, 
		-CORNER_FRAME_BORDER_RELOFFSET * Texture::getShouldWidth(), 
		(CORNER_FRAME_BORDER_RELOFFSET + (1 - relFactor)) * iconHeight);
	cornerLabel->setParent(cornerFrame);
	cornerLabel->setRelativePosition(POS_C, cornerFrame, POS_C);
	bottomLabel->setParent(Texture::getFrame());
	bottomLabel->setRelativePosition(POS_T, Texture::getFrame(), POS_B, 0, -BOTTOM_OBJECT_BORDER_RELOFFSET * Texture::height());
	bottomBar->setParent(Texture::getFrame());
	bottomBar->setRelativePosition(POS_C, Texture::getFrame(), POS_B, 0, -bottomFactor * Texture::height()/2);
}

void MultiIcon::setAbsolutePosition( uint32_t originPos, float absoluteX, float absoluteY )
{
	Texture::setAbsolutePosition(originPos, absoluteX, 
		absoluteY + bShowBottom ? (Texture::height() / relFactor - Texture::height())/2 : 0
	);
	bWantRefresh = true;
}

void MultiIcon::setRelativePosition( uint32_t originPos, IUIObject* target, uint32_t toPos, float relativeX /*= 0*/, float relativeY /*= 0 */ )
{
	Texture::setRelativePosition(originPos, target, toPos, relativeX, 
		relativeY + bShowBottom ? (Texture::height() / relFactor - Texture::height())/2 : 0
	);
	bWantRefresh = true;
}

void MultiIcon::setRelativePosition( uint32_t originPos, UILayoutFrame* target, uint32_t toPos, float relativeX /*= 0*/, float relativeY /*= 0 */ )
{
	Texture::setRelativePosition(originPos, target, toPos, relativeX, 
		relativeY + bShowBottom ? (Texture::height() / relFactor - Texture::height())/2 : 0
	);
	bWantRefresh = true;
}

std::uint32_t MultiIcon::getId() const
{
	return id;
}

UISimpleFrame* MultiIcon::getFrame() const
{
	return wholeFrame;
}

float MultiIcon::top() const
{
	return wholeFrame->base<war3::CSimpleFrame*>()->baseLayoutFrame.borderU;
}

float MultiIcon::bottom() const
{
	return wholeFrame->base<war3::CSimpleFrame*>()->baseLayoutFrame.borderB;
}

float MultiIcon::left() const
{
	return wholeFrame->base<war3::CSimpleFrame*>()->baseLayoutFrame.borderL;
}

float MultiIcon::right() const
{
	return wholeFrame->base<war3::CSimpleFrame*>()->baseLayoutFrame.borderR;
}

float MultiIcon::width() const
{
	return Texture::getShouldWidth();//wholeFrame->width();//base<war3::CSimpleFrame*>()->baseLayoutFrame.width;
}

float MultiIcon::height() const
{
	return wholeFrame->height();//base<war3::CSimpleFrame*>()->baseLayoutFrame.height;
}

void MultiIcon::setClickUnit( Unit *u )
{
	clickerJumpGroup->clear();
	if ( u != NULL )
		clickerJumpGroup->add(u);
}

void RefreshProgressIcons( Timer *tm )
{
	ProgressIcon *icon = *tm->data<ProgressIcon *>();
	Unit *u;
	float percent, maxPercent = 0;
	int count = 0;
	bool showCount = true;
	for ( UnitGroup::iterator iter = icon->units->begin(); iter != icon->units->end();
		++iter )
	{
		u = *iter;
		switch (icon->refreshType)
		{
		case TypeQueue:
			if (u->abilityLevel('Aque') > 0)
			{
				percent = u->queuePercent();
				if (percent < 1.0f)
				{
					maxPercent = max(maxPercent, percent);
					uint32_t queueType = u->queueType();
					if (showCount && (queueType>>0x18)=='R')
					{
						showCount = false;
					}
					else if (showCount && Jass::IsHeroUnitId(queueType))
					{
						showCount = false;
					}
					count++;
				}
			}
			break;
		case TypeUpgrade:
			if (u->abilityLevel('AUnP') > 0)
			{
				percent = u->upgradePercent();
				if (percent < 1.0f)
				{
					maxPercent = max(maxPercent, percent);
					showCount = false;
					count++;
				}
			}
			break;
		case TypeConstruction:
			if (u->abilityLevel('ABnP') > 0)
			{
				percent = u->constructionPercent();
				if (percent < 1.0f)
				{
					maxPercent = max(maxPercent, percent);
					count++;
				}
			}
			break;
		default:
			break;
		}
	}

	if ( count > 0 )
	{
		icon->show(true);
		icon->setBottomBar(maxPercent);
		if ( showCount || count > 1 )
		{
			icon->showCorner(true);
			icon->setCorner("%d", count);
		}
		else
		{
			icon->showCorner(false);
		}
	}
	else
	{
		icon->show(false);
	}
}

ProgressIcon::ProgressIcon( IUIObject *parent, float width, float height )
	: MultiIcon( parent, width, height, NULL, NULL, true, true, 0.15f)
{
	refreshType = TypeQueue;
	units = new UnitGroup();
	showCorner(true);
	showBottom(TypeBar);

	refreshTimer = GetTimer(0.01, RefreshProgressIcons, true, TimeLocal);
	ProgressIcon *icon = this;
	refreshTimer->setData<ProgressIcon *>(&icon);
	refreshTimer->start();
}

ProgressIcon::~ProgressIcon()
{
	refreshTimer->destroy();
	GroupDestroy(units);
}
