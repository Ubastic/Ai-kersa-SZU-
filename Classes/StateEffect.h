#pragma once

#ifndef _STATE_EFFECT_H_
#define _STATE_EFFECT_H_

#include"BaseEffect.h"
#include"BaseState.h"

class StateEffect : public BaseEffect {
public:
	//״̬���͡�״̬ͼ�ꡢ״̬���֡�״̬˵���������غϡ��Ƿ�������á��Ƿ���ʱ״̬�����ı�����ԣ���ѡ�����ı�������ѡ��
	static StateEffect* create( TargetType target_type , StateType state_type, std::string picPath, std::string name, std::string info, int rounds, 
		bool isCanEffect, bool isTemporary , bool isCanOverlay,Property property = Property::Health, int* property_change = 0);

private:
	virtual bool init(TargetType target_type, StateType type, std::string picPath, std::string name, std::string info, int rounds, bool isCanEffect, 
		bool isTemporary, bool isCanOverlay, Property property = Property::Health, int* property_change = 0);

	virtual void effect(Target& target);
private:
	StateType m_state_type;
	std::string m_picPath;	//��������״̬ͼƬ
	std::string m_name;	//��������״̬����
	std::string m_info;	//��������״̬˵��

	int m_continues_rouds;	//�����غ�����-1Ϊ����

	bool m_isCanEffect;	//�Ƿ��������
	bool m_isTemporary;	//�Ƿ�Ϊ��ʱ״̬
	bool m_isCanOverlay;	//�Ƿ���Ե���

	Property m_property;
	int* m_property_change;
};


#endif // _STATE_EFFECT_H_
