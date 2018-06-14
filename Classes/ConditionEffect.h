#pragma once

#ifndef _CONDITION_EFFECT_H_
#define _CONDITION_EFFECT_H_

#include"BaseEffect.h"

////����ö��
//enum Condition{
//	If_Health,
//	If_Armor
//};
//���ڵ��ڡ����ڡ����ڡ�С�ڵ��ڡ�С��
enum Condition_Way {
	Greater_Equal,
	Greater,
	Equal,
	Less_Equal,
	Less
};
////���ö��
//enum Result {
//	Then_Damage,
//	Then_Armor,
//	Then_Heal
//};

//����Effect 
class ConditionEffect:public BaseEffect {
public:
	//����Ŀ�꣬����ö�٣����㷽ʽ������������ֵ�����ö�٣����Ŀ�꣬Ĭ����ɽ��������������ɽ��
	static ConditionEffect* create(
		TargetType condition_target, Property condition, Condition_Way condition_way,  int defaultCondition, TargetType result_target, Property result,  int* defaultResult, int ratio_of_result);

	virtual void effect( Target& target );
private:
	virtual bool init(
		TargetType condition_target, Property condition, Condition_Way condition_way, int defaultCondition, TargetType result_target, Property result,  int* defaultResult, int ratio_of_result);

	bool getFlag(BaseCharacter* character);
	void effect_( bool flag , Target& target );
	void effect_single(bool flag, BaseCharacter* character);

private:
	TargetType m_condition_target;	//����Ŀ��
	Property m_condition;	//����
	Condition_Way m_condition_way;
	int m_defaultCondition;	//��������

	TargetType m_result_target;	//���Ŀ��
	Property m_result;	//���
	int* m_defaultResult;	//Ĭ����ɽ��
	int m_ratio_of_result;	//����������ɽ��

};



#endif // !_CONDITION_EFFECT_H_