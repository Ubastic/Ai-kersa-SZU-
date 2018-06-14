#pragma once

#ifndef _BASE_EFFECT_H_
#define _BASE_EFFECT_H_

#include"GameConfig.h"
#include"Target.h"


//����Effect�Ļ��࣬��Ҫ���ڿ�������
//���Լ̳�������ಢ����Լ��ĳ�Ա֮�������ɸ��ָ�����Ч��������effect()Ϊ������������
//�ɲ���DamageEffect
class BaseEffect:public Node {
public:
	//���麯��effect������Ϊ��Һ͵��˵Ļ���BaseCharacter���ɸ���ʵ����Ҫǿ��ת������
	virtual void effect(  Target& target ) = 0;
	virtual bool init( TargetType type  );
protected:
	TargetType m_type;	//��Effect�Ƿ���Ե���
};


#endif // !_BASE_EFFECT_H_

