#pragma once
#ifndef _GENERAL_STATE_H_
#define _GENERAL_STATE_H_

#include"BaseEffect.h"

//��������һ���State����������һ��State�������õ�ʱ���ܲ�������
class GeneralState : public BaseState {
public:
	//״̬����ID��״̬����·����״̬���֡�״̬��Ϣ�������غ������Ƿ���Ե���
	static GeneralState* create(
		StateType type, std::string picPath, std::string name, std::string info, int rounds, bool isCanOverlay);

	virtual void effect();
	virtual void effect_when_end();
private:
	bool init( StateType type , std::string picPath, std::string name, std::string info, int rounds , bool isCanOverlay);
private:
};

#endif // !_GENERAL_STATE_H_