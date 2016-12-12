#ifndef ABILITY_H_
#define ABILITY_H_
class Unit;

class Ability {
public:
	Ability* nextNode ( ) const;			//下一个技能，没有为NULL
	uint32_t		typeId( ) const;			//技能ID
	const char*		typeIdChar ( ) const;
	const char*		name ( ) const;				//名称
	uint32_t		baseTypeId( ) const;		//模板技能ID
	const char*		className( ) const;			//所属类名, TODO继续研究6f028f40

	uint32_t		level( ) const;				//等级 从0开始
	float			cooldown( ) const;			//冷却时间
	float			cooldownRemain( ) const;	//剩余冷却时间
	bool			isAvailable( ) const;		//是否可用
	const Unit*		owner( ) const;				//所有者
	const char*		iconPath( ) const;			//图标
	uint32_t		flag ( ) const;
	bool			isSpell () const;
	float			mana () const;				//耗魔
	int				iconPositionValue( ) const;	//图标排列优先级, TODO
	bool			isSpellBook ( ) const;
	int getSpellBookSpells( std::set<uint32_t> *pSpellIdSet );
	uint32_t		order ( ) const;			//命令

	const char*		tooltip(int level = -1) const;
	const char*		description(int level = -1) const;
	uint32_t		hotkey(int level = -1) const;


};

inline Ability* GetAbility(void* obj) {
	return (Ability*)obj;
}

/*
	0x1
	0x2
	0x4
	0x8
	0x10		ability
	0x20		item
	0x40
	0x80		buff?
	0x100		unuseable?
	0x200		in cd
	0x400		using?
	0x800
	0x1000
	0x2000		active???
	0x4000
	0x8000
	0x10000
	0x20000
	0x40000
	0x80000
	0x100000
	0x200000
	0x400000
	0x800000
	0x1000000
	0x2000000
	0x4000000
	0x8000000
	0x10000000
	0x20000000
	0x40000000
	0x80000000	passive ?
*/

#endif