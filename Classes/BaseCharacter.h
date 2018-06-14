#pragma once

#ifndef _BASE_CHARACTER_H_
#define _BASE_CHARACTER_H_

#include"GameConfig.h"
#include"BaseState.h"

#define STATE_NUM_PER_ROW 5	//ÿ����������״̬

enum Property {
	Health,
	Armor,

	Power,
	Agility,
	Magic,

	Cost
};
struct CharacterState {
	bool is_weak;
	bool is_vulnerable;
};

class BaseCharacter :public Node {
public:
	BaseCharacter();
	~BaseCharacter();

	//��ͼ·�������HP�����ס�����������
	virtual bool init( std::string picPath, int max_hp , bool isEnemy , int armor , int power, int agility );
	
	//�˺�������
	void hurt(int damage);
	void heal(int health);

	//�ı��������ֵ
	void changeMaxHP(int max_hp);
	//�ı令��ֵ
	void changeArmor(int armor);

	//�ı����������ݡ�����ֵ
	void changePower(int power);
	void changeAgility(int agility);

	void addState(BaseState* state );
	void removeState(BaseState* state);
	void toEffectState();	//�غϽ�������ã���������State��effect

	int getHP() { return m_hp; }	//�������ֵ
	int getMaxHP() { return m_max_hp; }	//����������ֵ
	int getArmor() { return m_Armor; }	//����ֵ
	int getPower() { return m_Power; }	//����ֵ
	int getAgility() { return m_Agility; }	//����ֵ

	bool isHaveArmor() { return m_isHaveArmor; }	//�Ƿ��л���ֵ
	bool isHavePower() { return m_isHavePower; }	//�Ƿ�������ֵ
	bool isHaveAgility() { return m_isHaveAgility; }	//�Ƿ�������ֵ

	void effect_when_round_end();	//�غϽ���֮����õĺ���

	bool isEnemy() { return m_isEnemy; }

	virtual Size getContentSize() { return m_sprite->getContentSize(); }	//override
	virtual Rect getBoundingBox() { 
		Rect rect = Rect(
			this->getPositionX() - getContentSize().width / 2 , this->getPositionY() - getContentSize().height /2 , 
			getContentSize().width, getContentSize().height);
		return rect; 
	}	//overide
private:
	//����HP_Label
	void updateHPLabel();

	void updateStateLayout();
protected:
	int m_hp;	//����ֵ
	int m_max_hp;	//�������ֵ

	int m_Armor;	//��ǰ����
	int m_Power;	//��ǰ����
	int m_Agility;	//��ǰ����

	bool m_isDead;
	bool m_isEnemy;	//�Ƿ�Ϊ����

	bool m_isHaveArmor;	//�Ƿ��л���
	bool m_isHavePower;	//�Ƿ�������
	bool m_isHaveAgility;	//����

	Sprite* m_sprite;	//������ͼ
	Label* m_hp_label;	//����ֵLabel

	Vector<BaseState*> m_state_vector;

	//����ʱ��Label��ʾ���ס����������ݣ����������ͼ�����ʽ���֣�������һ��Layer����
	Label* m_armor_label;
	Label* m_power_label;
	Label* m_agility_label;
};

#endif // !_BASE_CHARACTER_H_
