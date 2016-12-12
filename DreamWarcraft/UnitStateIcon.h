#ifndef UNIT_STATE_ICON_H_
#define UNIT_STATE_ICON_H_

#include "Frame.h"

class Unit;
class Texture;
class StateBar;

class UnitStateIcon : public Frame
{
private:
	Texture*	icon;
	StateBar*	barHP;
	StateBar*	barMana;

public:
	Unit*	unit;
	uint32_t	typeId;

	UnitStateIcon(
		IUIObject	*parent,
		float		width,
		float		height,
		Unit		*unit
	);

	virtual ~UnitStateIcon();

	virtual void	tick ( );
};

#endif