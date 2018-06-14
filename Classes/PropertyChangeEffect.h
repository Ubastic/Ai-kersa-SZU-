#pragma once

#ifndef _PROPERTY_CHANGE_EFFECT_H_
#define _PROPERTY_CHANGE_EFFECT_H_

#include"BaseEffect.h"
#include"Player.h"
#include"PropertyChangeState.h"

class PropertyChangeEffect :public BaseEffect {
public:
	//�Ƿ������ڵ��ˡ��ı��ĸ����ԡ������Ըı�ֵ��������ΪPropertyChangeState��ز�����
	static PropertyChangeEffect* create( TargetType type, Property property, int *property_change);

	virtual void effect( Target& target );
private:
	virtual bool init( TargetType type, Property property,  int *property_change);
private:
	Property m_property;	//�ı������
	int* m_property_change;	// �ı��������

};

#endif // !_POWER_CHANGE_EFFECT_H_