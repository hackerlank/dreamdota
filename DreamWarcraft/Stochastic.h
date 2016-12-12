#ifndef STOCHASTIC_H_
#define STOCHASTIC_H_

#include <vector>

struct DistributionLess {
	bool operator() (const float &lhs, const float &rhs) const
	{return lhs < rhs -1.e-5;}
};

//骰子
struct Dice {
	uint32_t	sides;		//面数，对于m面骰子，值为 1 ~ m，间隔1
	float		factor;		//缩放倍数，factor = 0.5的m面骰子值为 0.5 ~ 0.5m，间隔0.5

	Dice ();
	Dice (uint32_t _sides);	//初始化骰子为起始值1，间隔1的m面骰子
	
	void operator *= (float scale);	//设置缩放

	float		maxValue() const;
	float		minValue() const;
	float		expectValue() const;

	bool		ident(const Dice &other) const;

	const std::string toString() const;
};

typedef std::vector<Dice> dicecontainer;
//离散分布
//攻击/伤害随机分布: 基础值 + {骰子1 ... 骰子n}
class DnDAtkDist {

	float			_base;				//基础值，对于单个攻击力，对应dmgPlus + buffs。对于伤害总和，对应伤害非随机部分总和。
	dicecontainer	_dices;

public:
	DnDAtkDist ();
	DnDAtkDist (float base);
	DnDAtkDist (float base, Dice atkDice, uint32_t atkDiceCount);

	dicecontainer *dices ();

	float		maxValue() const;//TODO: 在对象中cache
	float		minValue() const;
	float		expectValue() const;

	void append (Dice d, float baseMod = 0);	//添加一个骰子并且可以改变基础值
	void operator += (float baseMod);			//改变基础值
	void operator *= (float factor);
	void operator &= (DnDAtkDist & other);		//合并两个攻击分布: 基础值相加，骰子并入集合

	float chanceGreaterEqual(float value, bool flagRoundedToInt) const;//求大于等于给定值的概率

	const std::string toString() const;
};

const float RASTER_UNIT = 0.01f;		//两个相邻的元素所对应的x值差
typedef std::vector<float> valuecontainer;
//连续分布
//函数，用描点法描述数据
class Function {

	float			_offset;			//偏移，即最左端数据对应的x值
	valuecontainer	_values;

public:

	Function ();
	Function (float start, float end, float totalValue);
	void setValueFromDiscrete (std::map<float, float, DistributionLess> *discreteValueMap, float minBase);
	std::pair<float, float> maxima (bool preferLowerKey = true);
	void convolution (std::map<float, float, DistributionLess> *discreteValueMap);
	void smooth (uint32_t radius);//一维平均平滑
	void shift(float val){_offset += val;}//位移key

	uint32_t size() const;
	void print() const;
};







#endif