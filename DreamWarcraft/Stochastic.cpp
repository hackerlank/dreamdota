#include "stdafx.h"
#include "Stochastic.h"
#include "Tools.h"
#include <sstream>


Dice::Dice () : sides(), factor() { }

Dice::Dice (uint32_t _sides) : sides(_sides), factor(1.0f) { }

void Dice::operator *= (float scale) {factor *= scale;}

float Dice::maxValue () const {
	return sides * factor;
}

float Dice::minValue () const {
	return factor;
}

float Dice::expectValue () const{
	return (1 + sides) * factor / 2;
}

bool Dice::ident(const Dice &other) const{
	return (sides == other.sides && factor == other.factor);
}

const std::string Dice::toString() const{
	std::ostringstream s;
	s << "(" << sides << " x " << factor << ")";
	return s.str();
}

DnDAtkDist::DnDAtkDist() : _base(), _dices() { }

DnDAtkDist::DnDAtkDist(float base) : _base(base), _dices() { }

DnDAtkDist::DnDAtkDist (float base, Dice atkDice, uint32_t atkDiceCount) : _base(base), _dices() {
	if (atkDiceCount) _dices.assign(atkDiceCount, atkDice);//FIXME: 是否需要reserve
}

const std::string DnDAtkDist::toString() const{
	std::ostringstream s;
	s << _base;
	//统计所有骰子
	Dice lastDice = Dice();
	uint32_t lastDiceCount = 0;
	for (dicecontainer::const_iterator it = _dices.begin();
		it != _dices.end(); ++it)
	{
		if (!lastDice.ident(*it)){
			if (lastDiceCount){
				s << " + " << lastDiceCount << "d" << (lastDice.toString());
			}
			lastDice = *it;
			lastDiceCount = 1;
		}
		else{
			++lastDiceCount;
		}
	}
	if (lastDiceCount){
		s << " + " << lastDiceCount << "d" << (lastDice.toString());
	}
	return s.str();
}

dicecontainer *DnDAtkDist::dices () {
	return &_dices;
}

void DnDAtkDist::append (Dice d, float baseMod) {
	_base += baseMod;
	_dices.push_back(d);
}

void DnDAtkDist::operator += (float baseMod) {
	_base += baseMod;
}

void DnDAtkDist::operator *= (float factor) {
	_base *= factor;
	for (uint32_t i = 0, size = _dices.size(); i < size; ++i){
		_dices[i].factor *= factor;
	}
}

void DnDAtkDist::operator &= (DnDAtkDist & other) {
	_base += other._base;
	dicecontainer *d = other.dices();
	_dices.insert(_dices.end(), d->begin(), d->end());
}

float DnDAtkDist::maxValue () const {
	float rv = _base;
	for (uint32_t i = 0, size = _dices.size(); i < size; ++i){
		rv += _dices[i].maxValue();
	}
	return rv;
}

float DnDAtkDist::minValue () const {
	float rv = _base;
	for (uint32_t i = 0, size = _dices.size(); i < size; ++i){
		rv += _dices[i].minValue();
	}
	return rv;
}

float DnDAtkDist::expectValue () const{
	float rv = _base;
	for (uint32_t i = 0, size = _dices.size(); i < size; ++i){
		rv += _dices[i].expectValue();
	}
	return rv;
}

typedef std::map<float, float, DistributionLess> //精度
	Distribution;
static Distribution D_allSteps[0x100];//最大数量

float DnDAtkDist::chanceGreaterEqual(float value, bool flagRoundedToInt) const{
	//原问题：base + {骰子...} >= value， 转化问题：{骰子...} >= value - base
	//diceMax = 所有骰子最大值；diceMin = 所有骰子最小值
	//distribution d = 空
	//对每个骰子loop:
	//	diceMax, diceMin -= 当前骰子max, min
	//	d 叠加 骰子: iter.first + dice每个面的点数为新的键值，iter.second * dice概率为新的概率
	//	如果新键值 + diceMax < x则特殊保存概率到键值-∞
	//	如果新键值 + diceMin > x则特殊保存概率到键值∞
	//	否则保存(新键值, 新概率)

	/*	TODO:
	1. 对于一系列攻击，从平均值最可能杀死目标的那次开始算，往前和往后各推到概率小于1%之后忽略其它，再进行整理数据
	（降低2～3倍时间，数据精确度>99%）
	2. 使用一个新线程计算（对多核cpu降低~1倍时间并且不影响主线程）
	*/

	float diceMax = maxValue(), diceMin = minValue();
	if (diceMax < value) return 0;//预先验证一下是否已经为简单情况，返回0或者1
	if (diceMin >= value) return 1;
	diceMax -= _base;
	diceMin -= _base;
	float valueTransformed = value - _base;

	uint32_t stepCount = _dices.size();
	//Distribution *d_allSteps = new Distribution[stepCount];
	float chanceLesser = 0, chanceGreater = 0;

	//循环所有骰子
	Distribution start;	start[0] = 1;//初始化一个分布
	Distribution *distributionLast = &start;
	Distribution *distributionCurrent;


	uint32_t stepCurrent = 0;
	dicecontainer::const_iterator diceIter = _dices.begin(), diceIterEnd = _dices.end();

	while (	diceIter != diceIterEnd) 
	{
	
		diceMax -= diceIter->maxValue();
		diceMin -= diceIter->minValue();
		//现在distributionCurrent等于d_allSteps[stepCurrent]
		//distributionCurrent等于distributionLast的每个元素与当前骰子叠加
		float diceChance = 1.f/diceIter->sides;//骰子每个面的概率都是1/side
		Distribution::iterator distValueIter, distValueIterEnd;

		distributionCurrent = &(D_allSteps[stepCurrent]);
		distributionCurrent->clear();
		
		if (!distributionLast->empty()){
			
			distValueIter = distributionLast->begin();
			distValueIterEnd = distributionLast->end();
			while(distValueIter!=distValueIterEnd) {
				float currentKeyVal = distValueIter->first;//键值
				float newKeyVal;
				float dicePoint = diceIter->minValue();
				for (uint32_t i = 0; i < diceIter->sides; ++i, dicePoint+=diceIter->factor) {
					newKeyVal = currentKeyVal + dicePoint;
					if (newKeyVal + diceMax < valueTransformed) {
						chanceLesser += distValueIter->second * diceChance;
					}
					else if (newKeyVal + diceMin > valueTransformed) {
						chanceGreater += distValueIter->second * diceChance;
					}
					else {
						if (flagRoundedToInt) newKeyVal = floor(newKeyVal + 0.5f);
						distributionCurrent->operator[](newKeyVal) += distValueIter->second * diceChance;
					}
				}//当前骰子点数循环
				++distValueIter;
			}//当前分布元素循环
			//现在概率分布形成了3部分，过小概率，过大概率和其它概率（在map中）
		}
		distributionLast = distributionCurrent;
		++diceIter;
		++stepCurrent;
		if (stepCurrent >= 0x100) break;//避免过长
	}//所有骰子循环
	
	//返回过大概率 + distributionLast概率中大于等于valueTransformed的概率和
	float rvChance = chanceGreater;

	if (!distributionLast->empty()) {
		Distribution::iterator distValueIter, distValueIterEnd;
		for (	distValueIter = distributionLast->begin(),
				distValueIterEnd = distributionLast->end(); 
				distValueIter != distValueIterEnd; 
				++distValueIter	)
		{
			if (distValueIter->first >= valueTransformed){
				rvChance += distValueIter->second;
			}
		}
	}
	return rvChance;
}

Function::Function () : _offset(), _values() { }

Function::Function (float start, float end, float totalValue) {
	int count = (int)(floor((end-start)/RASTER_UNIT));
	_values.assign(count, totalValue/count);
	_offset = start;
}

void Function::setValueFromDiscrete (std::map<float, float, DistributionLess> *discreteValueMap, float minBase) {
	_offset = 0;
	_values.clear();

	//discreteValueMap的每个值标志着从这时开始的新连续值。
	if (!discreteValueMap->size()) return;
	
	_offset = discreteValueMap->begin()->first;
	uint32_t index = 0;
	float prevY = 0.f, currX = 0.f, currY = 0.f;
	for (std::map<float, float, DistributionLess>::const_iterator 
		iter = discreteValueMap->begin(); 
		iter != discreteValueMap->end(); 
		++iter) 
	{
		currX = iter->first;
		currY = iter->second; 
		while (_offset + index * RASTER_UNIT < currX) {
			_values.push_back(prevY);
			++index;
		}
		prevY = currY;
	}
	_values.push_back(0);
}

std::pair<float, float> Function::maxima (bool preferLowerKey){
	uint32_t size = _values.size();
	if (size){
		float val; float maxVal = _values[0]; uint32_t maxIndex = 0;
		bool improve;
		uint32_t i = 0;
		for (i = 0; i < size; ++i){
			val = _values[i];
			improve = preferLowerKey? (maxVal < val) : (maxVal <= val);
			if (improve){
				maxVal = val;
				maxIndex = i;
			}
		}
		return std::pair<float, float> (RASTER_UNIT * maxIndex + _offset, maxVal);
	}
	return std::pair<float, float>(-1.f,-1.f);
}

void Function::convolution (std::map<float, float, DistributionLess> *discreteValueMap){
	uint32_t size = _values.size();
	if (_offset && size && discreteValueMap->size()){
		std::map<float, float, DistributionLess> tempValMap;
		float key, value;
		std::map<float, float, DistributionLess>::iterator mapIter;
		for (uint32_t i = 0; i < size; ++i){
			value = _values[i];
			key = RASTER_UNIT * i + _offset;
			for (mapIter = discreteValueMap->begin(); mapIter != discreteValueMap->end(); ++mapIter){
				tempValMap[(int)((key + mapIter->first) / RASTER_UNIT) * RASTER_UNIT] += value * mapIter->second;//TODO 是否要判断不为0?
			}
		}
		setValueFromDiscrete(&tempValMap, 0);
	}
}

void Function::smooth (uint32_t radius) {//TODO 扩展size !
	if (radius == 0) return; //什么也不需要做
	uint32_t size = _values.size();
	uint32_t smoothSize = (radius*2+1);
	//每个新值等于老值向两端各延伸radius格的值的平均值
	valuecontainer tempValues = _values;
	float tmp, subVal, addVal; uint32_t tmpIndex;
	bool initCalc = false;
	for (uint32_t i = 0; i < size; ++i){
		tmp = 0;
		if (!initCalc) {
			for (uint32_t rangeIndex = i - radius; rangeIndex <= i + radius; ++rangeIndex){
				tmp += (rangeIndex >= 0 && rangeIndex < size) ?
					tempValues[rangeIndex] : 0;
			}
			_values[i] = (tmp / smoothSize);
			initCalc = true;
		}
		else{
			tmpIndex = i-radius-1;
			subVal = (tmpIndex >= 0 && tmpIndex < size) ? tempValues[tmpIndex] / smoothSize : 0;
			tmpIndex = i+radius;
			addVal = (tmpIndex >= 0 && tmpIndex < size) ? tempValues[tmpIndex] / smoothSize : 0;
			_values[i] = _values[i-1] - subVal + addVal;
		}
	}

}

uint32_t Function::size() const {
	return _values.size();
}

void Function::print () const {//似乎有bug
	uint32_t size = _values.size();
	float valueX = _offset;
	float valueXold = 0;
	float valueY, valueYold = -1.f;

	for (uint32_t i = 0; i < size; ++i) {
		valueY = _values[i];
		valueX += RASTER_UNIT;
		if (valueY!=valueYold){
			OutputScreen(10, "values from [%.2f ~ %.2f] = %.3f", valueXold, valueX-RASTER_UNIT, valueY);
			valueYold = valueY;
			valueXold = valueX;
		}
	}
}