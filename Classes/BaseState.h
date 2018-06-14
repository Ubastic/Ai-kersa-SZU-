#pragma once

#ifndef _BASE_STATE_H_
#define _BASE_STATE_H_

#include"GameConfig.h"

//��ʱ����ö����������ʾ���е�״̬
enum StateType {
	Weak = 0,	//����
	Vulnerable,	//����
	Ghost,	//���黯
	Property_Change	//�ı�������״̬
};

//����״̬��Ļ��࣬���ڸ�������͵�������
//��������һ��ͼ�꣬���Ա�����֣������غ���
class BaseState :public Node {
public:
	//״̬���͡�ͼ��·����״̬���֡�״̬��Ϣ�������غϡ��غϽ���ʱ�Ƿ�������á��Ƿ�Ϊ��ʱ״̬���Ƿ���Ե���
	bool init( StateType type, std::string picPath , std::string name , std::string info , int rounds , bool isCanEffect , bool isTemporary , bool isCanOverlay );

	virtual void effect() = 0;	//ÿ�غϽ������õĺ���
	virtual void effect_when_end() = 0;	//�����غϽ�������õĺ�����һ���ǴӸ��ڵ���ȥ����ɾ��״̬

	void changeContinuesRound(int rounds) { m_left_rounds += rounds; m_continues_rounds += rounds; updateRoundsLabel(); }

	std::string getName() { return m_name; }
	int getContinuesRound() { return m_continues_rounds; }
	bool isCanOverLay() { return m_isCanOverLay; }

	StateType getStateType() { return m_type; }
private:

	virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);
	virtual void onTouchEnded(Touch* pTouch, Event* pEvent);

protected:
	void updateRoundsLabel() {
		m_continues_rouds_label->setString(Value(m_left_rounds).asString());
	}

protected:
	StateType m_type;	//��ʾ״̬IDֵ

	Sprite * m_icon_sprite;	//ͼ�꾫��
	Label* m_continues_rouds_label;	//�����غ�Label

	std::string m_name;	//״̬����
	std::string m_info;	//״̬��Ϣ
	int m_continues_rounds;	//�����غϣ�-1Ϊ����
	int m_left_rounds;	//ʣ��غ���

	bool m_isCanEffect;	//ÿ�غϽ����Ƿ������ã����Ա�ʾ�غϽ��������״̬����ÿ�غ�������ɵ�������
	bool m_isTemporary;	//�����غϽ������Ƿ���Ҫ��ԭ��ʩ��״̬ǰ������ʱ���3������2�غ�
	bool m_isCanOverLay;	//�Ƿ���Ե���״̬
};

#endif // !_BASE_STATE_H_