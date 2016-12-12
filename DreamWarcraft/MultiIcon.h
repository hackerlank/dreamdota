#ifndef MULTIICON_H_INCLUDED
#define MULTIICON_H_INCLUDED

#include "Texture.h"
class UISimpleFrame;
class UISimpleTexture;
class UISimpleButton;
class Label;
class Bar;
class UnitGroup;
class Timer;
class Observer;

enum MultiIconBottomType
{
	TypeNone,
	TypeText,
	TypeBar
};

//图标 + 右下角数字 + 中间数字
//支持鼠标放上变大显示

class MultiIcon : public Texture
{
private:
	UISimpleFrame	*wholeFrame;
	Texture			*passiveCover;	//把按钮处理成被动
	UISimpleFrame	*cornerFrame;	//右下角框
	Label			*cornerLabel;	//右下角字
	bool			bCornerInited;
	std::string		cornerLabelContent;
	Label			*bottomLabel;		//底下字
	Bar				*bottomBar;			//底下条
	bool			bWantRefresh;
	float			iconWidth;
	float			iconHeight;
	uint32_t		id;
	uint32_t		idIndex;
	bool			bShowPassiveCover;
	bool			bShowBottom;
	float			relFactor;
	float			bottomFactor;

	UISimpleButton	*clicker;			//按钮
	Observer		*clickerOb;

public:
	UnitGroup		*clickerJumpGroup;	//按下轮流跳转的单位组
	int				clickJumpIndex;

	MultiIcon (
		IUIObject	*parent,
		float		width,
		float		height,
		const char	*texturePath = NULL,
		const char	*disabledTexturePath = NULL,
		bool		showPassive = false,
		bool		showBottom = false,
		float		bottomFactor = 0.35f
	);
	
	virtual ~MultiIcon();
	virtual void tick();
	virtual void refresh();
	virtual void	setAbsolutePosition ( uint32_t originPos, float absoluteX, float absoluteY );
	virtual void	setRelativePosition ( uint32_t originPos, IUIObject* target, uint32_t toPos, float relativeX = 0, float relativeY = 0 );
	virtual void	setRelativePosition ( uint32_t originPos, UILayoutFrame* target, uint32_t toPos, float relativeX = 0, float relativeY = 0 );
	virtual UISimpleFrame*	getFrame ( ) const;
	
	void setTextureById ( uint32_t objectId, uint32_t index = 0 );
	uint32_t getId() const;
	void showCorner ( bool flag , Color color = Color::WHITE );
	void setCorner (const char *format, ...);
	void showBottom ( MultiIconBottomType type );
	void setBottomLabel (const char *format, ...);
	void setBottomBar (float percent);
	void setClickUnit ( Unit *u );

	virtual float	top ( ) const;
	virtual float	bottom ( ) const;
	virtual float	left ( ) const;
	virtual float	right ( ) const;
	virtual float	width ( ) const;
	virtual float	height ( ) const;
	//TODO 还有scale等需要调整
	
};

enum ProgressIconRefreshType
{
	TypeConstruction,
	TypeUpgrade,
	TypeQueue
};

class ProgressIcon : public MultiIcon
{
private:
	Timer					*refreshTimer;

public:
	ProgressIconRefreshType	refreshType;
	UnitGroup				*units;

	ProgressIcon (
		IUIObject	*parent,
		float		width,
		float		height
	);

	virtual ~ProgressIcon();

};


#endif