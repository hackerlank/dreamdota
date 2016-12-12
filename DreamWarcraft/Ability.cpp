#include "stdafx.h"
#include "Ability.h"
#include "Tools.h"
#include "GameStructs.h"
#include "Unit.h"
#include <fp_call.h>

#define THIS_ABILITY ((war3::CAbility*)this)
#define THIS_ABILITYSPELL ((war3::CAbilitySpell*)this)

//技能ID
uint32_t Ability::typeId( ) const 
{
	if (this) 
	{
		return (THIS_ABILITY->id);
	}
	return NULL;
}

//技能ID (字符串)
const char *Ability::typeIdChar ( ) const
{
	return IntegerIdToChar(typeId());
}

//模板技能ID
uint32_t Ability::baseTypeId( ) const 
{
	if (this) 
	{
		return (AgentTypeIdGet((war3::CAgent*)this));
		//war3::AbilityDefData *data = THIS_ABILITY->defData;
		//if(data)
		//{
		//	return (data->abilityBaseTypeId);
		//}
	}
	return NULL;
}

//等级 从0开始
uint32_t Ability::level( ) const 
{
	if (this) 
	{
		return (THIS_ABILITY->level);
	}
	return NULL;
}

//冷却时间
float Ability::cooldown( ) const 
{
	if (this) 
	{
		return (AbilityCooldownGet(THIS_ABILITY));
	}
	return 0;
}

//剩余冷却时间
float Ability::cooldownRemain( ) const 
{
	//if (this && IsAbilitySpell(THIS_ABILITY)) 
	if (this && ObjectIsAgent((void *)this) && IsAbilitySpell(THIS_ABILITY))
	{
		uint32_t flagValue = THIS_ABILITY->flag2;
		if (
				(flagValue & 0x200)
			&&	!(flagValue & 0x400) //TODO 6F34F800 也就是vtable 0x2E0是如此判断的
			//此外6F34F760的开头还能从command button读取ability
		)
		{
			return AgentTimerRemainingTimeGet(&(THIS_ABILITYSPELL->timer_cooldown));
		}
	}
	return 0;
}

//是否CD中
bool Ability::isAvailable( ) const //FIXME 只判断了在CD中一种情况
{ 
	if (this) 
	{
		return (0x200 & THIS_ABILITY->flag2) == 0;
	}
	return 0;
}

bool Ability::isSpell () const
{
	if (this)
	{
		return IsAbilitySpell(THIS_ABILITY);
	}
	return false;
}

//所有者
const Unit* Ability::owner() const
{
	if (this && THIS_ABILITY->abilityOwner) 
	{
		return GetUnit(ObjectToHandle(THIS_ABILITY->abilityOwner)); //TODO 不使用handle?
	}
	return NULL;
}

//图标
const char* Ability::iconPath() const //TODO 更好方式判断buff
{
	if (this) 
	{
		return IsAbilityBuff(THIS_ABILITY) ?
			GetBuffIconFromFuncProfile(typeId()) : 
			GetIconFromFuncProfile(typeId());
	}
	return "";
}

Ability* Ability::nextNode() const
{
	if (this)
	{
		return GetAbility(AgentFromHash(&(THIS_ABILITY->nextAbilityHash)));
	}
	return NULL;
}

std::uint32_t Ability::flag() const
{
	if (this)
	{
		return THIS_ABILITY->flag2;
	}
	return NULL;
}

//图标顺序
int Ability::iconPositionValue() const
{
	uint32_t x, y;
	GetIconPos(typeId(), x, y);
	if (x >= 0 && x <= 3 && y >= 0 && y <= 2)
	{
		return y*4+x;
	}
	return -1;
}

bool Ability::isSpellBook() const
{
	return this && (AgentTypeIdGet((war3::CAgent*)this) == 'Aspb');
}

int Ability::getSpellBookSpells( std::set<uint32_t> *pSpellIdSet )
{
	int count = 0;
	if (isSpellBook())
	{
		uint32_t id;
		pSpellIdSet->clear();
		for (uint32_t i = 0; i < 11; ++i)
		{
			id = ((war3::CAbilitySpellBook*)this)->SpellTypeId[i];
			if (id) {
				pSpellIdSet->insert(id);
				count++;
			}
		}
	}
	return count;
}

std::uint32_t Ability::order() const//FIXME 可能对特殊技能无效
{
	if (!this) return 0;
	if (isSpell())
		return aero::generic_this_call<uint32_t>(VTBL(THIS_ABILITY)[0x348 / 4], THIS_ABILITY);
	return NULL;
}

const char* Ability::className() const
{
	if (!this) return 0;
	return aero::generic_this_call<const char *>(VTBL(THIS_ABILITY)[0x58 / 4], THIS_ABILITY);
}

const char* Ability::name() const
{
	return ObjectIdToNameChar(typeId());
}

const char*	Ability::tooltip(int level) const {
	if (!this) return "";

	if (level == -1)
		level = this->level();
	war3::AbilityUIDef* UIDef = AbilityUIDefGet(THIS_ABILITY);
	if (UIDef && UIDef->tooltip_levels) {
		return UIDef->tooltip_items[min((int)(UIDef->tooltip_levels) - 1, level)];
	} else
		return "Ability tooltip missing!";
}

const char*	Ability::description(int level) const {
	if (!this) return "";

	if (level == -1)
		level = this->level();
	war3::AbilityUIDef* UIDef = AbilityUIDefGet(THIS_ABILITY);
	if (UIDef && UIDef->desc_levels) {
		return UIDef->desc_items[min((int)(UIDef->desc_levels) - 1, level)];
	} else
		return "Ability description missing!";
}

uint32_t Ability::hotkey(int level) const {
	if (!this) return 0;

	if (level == -1)
		level = this->level();
	war3::AbilityUIDef* UIDef = AbilityUIDefGet(THIS_ABILITY);
	if (UIDef && UIDef->hotkey_levels) {
		return UIDef->hotkey_items[min((int)(UIDef->hotkey_levels) - 1, level)];
	} else
		return 0;
}

float Ability::mana() const
{
	return AbilityManaCostGet(THIS_ABILITY);
}
