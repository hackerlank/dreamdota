#include "stdafx.h"
#include "Bar.h"
#include "Texture.h"
#include "Label.h"
#include "Timer.h"
#include "Unit.h"

// UI\Feedback\BuildProgressBar\human-buildprogressbar-border.blp
// UI\Feedback\BuildProgressBar\human-buildprogressbar-fill.blp

Bar::Bar( IUIObject *parent, float width, float height, const char *textureBackground, const char *textureBorder, const char *textureFill, float initPercent /* = 0 */ )
	: Frame(parent, width, height)
{
	fillbarColor = Color::WHITE;
	percent = initPercent;
	if ( percent < 0 ) percent = 0;
	if ( percent > 1 ) percent = 1;

	background = new Texture( parent, width, height, textureBackground );
	background->setOwner(this);
	if (textureBackground == NULL)
	{
		background->fillColor(Color::BLACK);
	}
	background->setRelativePosition(POS_C, this, POS_C);

	fillbar = new Texture ( background, width * percent, height, textureFill );
	fillbar->setOwner(this);
	fillbar->setRelativePosition(POS_L, this, POS_L);
	if ( textureFill == NULL )
	{
		fillbar->fillColor(Color::WHITE);
	}

	border = new Texture ( fillbar, width, height, textureBorder );
	border->setOwner(this);
	border->setRelativePosition(POS_C, this, POS_C);
	if ( textureBorder == NULL )
	{
		//border->fillColor(Color::BLACK);
	}
}

Bar::~Bar()
{
	delete fillbar;
	delete border;
	delete background;
}

void Bar::setPercent( float percent )
{
	float _percent = min(max(percent, 0.f), 1.f);
	if (this->percent != _percent)
	{
		this->percent = _percent;
		if (_percent > 0)
		{
			fillbar->setColor(Color(fillbarColor.r,fillbarColor.g,fillbarColor.b, 0xFF));
			fillbar->setWidth( background->width() * _percent );
		}
		else
		{
			fillbar->setColor(Color(fillbarColor.r,fillbarColor.g,fillbarColor.b, 0x0));
		}
		fillbar->setRelativePosition(POS_L, this, POS_L);
		border->setRelativePosition(POS_C, this, POS_C);
	}
}

float Bar::getPercent() const
{
	return percent;
}

void Bar::show( bool flag )
{
	Frame::show(flag);
	border->show(flag);
	fillbar->show(flag);
	background->show(flag);
}

void Bar::setParent( IUIObject *parent )
{
	Frame::setParent(parent);
	background->setParent(parent);
	fillbar->setParent(background);
	border->setParent(fillbar);
}

void Bar::setParent( UISimpleFrame *parent )
{
	Frame::setParent(parent);
	background->setParent(parent);
	fillbar->setParent(background);
	border->setParent(fillbar);
}

UISimpleFrame* Bar::getTopFrame() const
{
	return border->getTopFrame();
}

void Bar::setColor( Color c )
{
	if (fillbarColor != c)
	{
		fillbarColor = c;
		float percent = getPercent();
		setPercent(0);
		setPercent(percent);
	}
}


BarValued::BarValued( IUIObject *parent, float width, float height, const char *textureBackground, const char *textureBorder, const char *textureFill, float labelHeight )
	: Bar(parent, width, height, textureBackground, textureBorder, textureFill, 0)
{
	label = new Label( Bar::getTopFrame(), "", labelHeight, Color::WHITE );
	label->setRelativePosition(POS_C, this, POS_C);
	label->show(true);
}

BarValued::~BarValued()
{
	delete label;
}

void BarValued::setValue( int value, int maxValue )
{
	label->setText("%d", value);
	Bar::setPercent( (float)value / (float)maxValue );
}

BarIndicator::BarIndicator( IUIObject *parent, float width, float height, const char *borderPath, float borderWidth, float padding, const char *textureFill, float labelHeight )
	: BarValued(parent, width-borderWidth-0.0008f, height-borderWidth-0.0008f, NULL, NULL, textureFill, labelHeight)
{
	border = new Frame(this, width, height, NULL, borderPath, borderWidth, padding);
	border->setRelativePosition(POS_C, this, POS_C);
}

BarIndicator::~BarIndicator()
{
	delete border;
}

UISimpleFrame * BarIndicator::getFrame()
{
	return border->getFrame();
}

float BarIndicator::top() const
{
	return border->top();
}

float BarIndicator::bottom() const
{
	return border->bottom();
}

float BarIndicator::left() const
{
	return border->left();
}

float BarIndicator::right() const
{
	return border->right();
}

float BarIndicator::width() const
{
	return border->width();
}

float BarIndicator::height() const
{
	return border->height();
}

void RefreshStateBar ( Timer *tm )
{
	StateBar *bar = *tm->data<StateBar *>();
	if (bar)
	{
		Unit *u = bar->unit;
		float hpMax, manaMax;
		float percent;
		if (u)
		{
			switch (bar->type)
			{
			case StateBarHP:
				hpMax = u->lifeMax();
				if (hpMax > 0 && u->abilityLevel('Avul')==0)
				{
					bar->show(true);
					percent = u->life() / hpMax;
					percent = floor(percent * 100) / 100.f;
					bar->setPercent(percent);
					bar->setColor(Color(1.f-percent, percent, 0, 1));
				}
				else
				{
					bar->show(false);
				}
				break;
			case StateBarMana:
				manaMax = u->manaMax();
				if (manaMax > 0)
				{
					bar->show(true);
					percent = u->mana() / manaMax;
					percent = floor(percent * 100) / 100.f;
					bar->setPercent(percent);
					bar->setColor(Color(0, 0, 1.f, 1));
				}
				else
				{
					bar->show(false);
				}
				break;
			default: break;
			}
		}
	}
}

StateBar::StateBar( IUIObject *parent, float width, float height, Unit *unit, StateBarTypes type )
	: Bar(parent, width, height, NULL, NULL, "UI\\Feedback\\HPBarConsole\\human-healthbar-fill.blp", 0.5f)
{
	this->unit = unit;
	this->type = type;

	refreshTimer = GetTimer(0.1, RefreshStateBar, true, TimeLocal);
	StateBar *bar = this;
	refreshTimer->setData<StateBar *>(&bar);
	refreshTimer->start();
}

StateBar::~StateBar()
{
	refreshTimer->destroy();
}
