#ifndef BAR_H_
#define BAR_H_

#include "Frame.h"

class Texture;
class Label;
class Timer;

class Bar : public Frame
{
private:
	float	percent;
	Color	fillbarColor;

public:
	Texture *background;	//±³¾°
	Texture *fillbar;		//Ìõ
	Texture *border;		//±ß¿ò

	Bar (
		IUIObject		*parent,
		float			width,
		float			height,
		const char		*textureBackground,
		const char		*textureBorder,
		const char		*textureFill,
		float			initPercent = 0
	);

	virtual ~Bar();

	void setPercent ( float percent );
	float getPercent ( ) const;
	void setColor ( Color c );

	virtual void	show ( bool flag );
	virtual void	setParent ( IUIObject *parent );
	virtual void	setParent ( UISimpleFrame *parent );
	virtual UISimpleFrame*	getTopFrame ( ) const;

};

class BarValued : public Bar
{
private:
	Label	*label;

public:
	BarValued (
		IUIObject		*parent,
		float			width,
		float			height,
		const char		*textureBackground,
		const char		*textureBorder,
		const char		*textureFill,
		float			labelHeight
	);

	virtual ~BarValued ( );

	void setValue ( int value, int maxValue );
};

class BarIndicator : public BarValued
{
private:
	Frame	*border;

public:
	BarIndicator (
		IUIObject		*parent,
		float			width,
		float			height,
		const char		*borderPath,
		float			borderWidth,
		float			padding,
		const char		*textureFill,
		float			labelHeight
	);

	virtual ~BarIndicator ( );

	virtual UISimpleFrame *getFrame ( );
	virtual float	top ( ) const;
	virtual float	bottom ( ) const;
	virtual float	left ( ) const;
	virtual float	right ( ) const;
	virtual float	width ( ) const;
	virtual float	height ( ) const;
};

enum StateBarTypes
{
	StateBarHP,
	StateBarMana
};

class StateBar : public Bar
{
private:
	Timer*			refreshTimer;

public:
	StateBarTypes	type;
	Unit*			unit;

	StateBar(
		IUIObject		*parent,
		float			width,
		float			height,
		Unit*			unit,
		StateBarTypes	type
	);

	virtual ~StateBar();
};

#endif