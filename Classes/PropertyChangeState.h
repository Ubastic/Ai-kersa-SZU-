#pragma once

#ifndef _PROPERTY_CHANGE_STATE_H_
#define _PROPERTY_CHANGE_STATE_H_

#include"BaseState.h"
#include"BaseCharacter.h"
#include"Player.h"

//һ��Demo��ʽ��State�����Է������д�����ָ�����State
class PropertyChangeState : public BaseState {
public:
	//״̬����·����״̬���֡�״̬��Ϣ�������غ�����ÿ�غ��Ƿ������á��Ƿ�Ϊ��ʱ״̬���Ƿ���Ե��ӡ��ı��ĸ����ԡ����Ըı�ֵ
	static PropertyChangeState* create(
		std::string picPath, std::string name, std::string info , int rounds, bool isCanEffect , bool isTemporary, bool isCanOverlay, Property property ,  int property_change );

	virtual void effect();
	virtual void effect_when_end();
private:
	bool init(std::string picPath, std::string name, std::string info , int rounds, bool isCanEffect , bool isTemporary, bool isCanOverlay, Property property, int property_change);
private:
	Property m_property;
	int m_property_change;
};

#endif // !_POWER_UP_STATE_
