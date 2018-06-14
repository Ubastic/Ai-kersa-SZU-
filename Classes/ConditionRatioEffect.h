#pragma once

#ifndef _CONDITION_RATIO_EFFECT_H_
#define _CONDITION_RATIO_EFFECT_H_

#include"ConditionEffect.h"
#include"BaseEffect.h"

//��������Effect 
class ConditionRatioEffect :public BaseEffect {
public:
	//����Ŀ�꣬����ö�٣����㷽ʽ������������ֵ�����ö�٣����Ŀ�꣬Ĭ����ɽ��������������ɽ��
	static ConditionRatioEffect* create(
		TargetType condition_target, Property condition, Condition_Way condition_way, float ratio, TargetType result_target, Property result, int* defaultResult, int ratio_of_result);

	virtual void effect(Target& target);
private:
	virtual bool init(
		TargetType condition_target, Property condition, Condition_Way condition_way, float ratio, TargetType result_target, Property result, int* defaultResult, int ratio_ofresult);

	bool getFlag(BaseCharacter* character);
	void effect_(bool flag, Target& target);
	void effect_single(bool flag, BaseCharacter* character);

private:
	TargetType m_condition_target;	//����Ŀ��
	Property m_condition;	//����
	Condition_Way m_condition_way;
	float m_ratio;	//��������

	TargetType m_result_target;	//���Ŀ��
	Property m_result;	//���
	int* m_defaultResult;	//Ĭ����ɽ��
	int m_ratio_of_result;	//����������ɽ��

};


#endif // !_CONDITION_RATIO_EFFECT_H_
