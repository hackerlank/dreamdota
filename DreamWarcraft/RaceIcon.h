#ifndef RACEICON_H_
#define RACEICON_H_

#include "Texture.h"
#include "Label.h"

class RaceIcon : public Frame
{
private:
	Texture *colorTexture;
	Texture *raceIcon;
	Label	*playerId;
	int		playerNumber;
	bool bWantRefresh;
public:
	RaceIcon(IUIObject *parent, float width, float height, int player);
	virtual ~RaceIcon();
	virtual void	setAbsolutePosition ( uint32_t originPos, float absoluteX, float absoluteY );
	virtual void	setRelativePosition ( uint32_t originPos, IUIObject* target, uint32_t toPos, float relativeX = 0, float relativeY = 0 );
	virtual void	setRelativePosition ( uint32_t originPos, UILayoutFrame* target, uint32_t toPos, float relativeX = 0, float relativeY = 0 );
	virtual void	setParent ( IUIObject *parent );
	virtual void	setParent ( UISimpleFrame *parent );
	virtual void	setHeight ( float height );
	virtual void	tick();
	virtual void	refresh();

	int player() const;
	void setPlayer( int player );//TODO
};

#endif