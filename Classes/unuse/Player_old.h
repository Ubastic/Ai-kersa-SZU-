#pragma once

#ifndef _Player__OLD_H_
#define _Player__OLD_H_

#include"GameConfig.h"

class Player_ :public Node {
public:
	//��ͼ·�����������ֵ
	static Player_* create(std::string picPath, int max_hp , int armor , int power , int agility , int magic );

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
	void changeMagic(int magic);

	int getHP() { return m_hp; }	//�������ֵ
	int getMaxHP() { return m_max_hp; }	//����������ֵ
	int getArmor() { return m_Armor; }	//����ֵ
	int getPower() { return m_Power; }	//����ֵ
	int getAgility() { return m_Agility; }	//����ֵ
	int getMagic() { return m_Magic; }	//����ֵ

	bool isHaveArmor() { return m_isHaveArmor; }	//�Ƿ��л���ֵ
	bool isHavePower() { return m_isHavePower; }
	bool isHaveAgility() { return m_isHaveAgility; }
	bool isHaveMagic() { return m_isHaveMagic; }

private:
	Player_();
	~Player_();

	virtual bool init(std::string picPath, int max_hp, int armor, int power, int agility, int magic);

	//����HP_Label
	void updateHPLabel();

private:
	int m_hp;	//����ֵ
	int m_max_hp;	//�������ֵ

	int m_Armor;	//��ǰ����
	int m_Power;	//��ǰ����
	int m_Agility;	//��ǰ����
	int m_Magic;	//��ǰ����

	bool m_isDead;

	bool m_isHaveArmor;	//�Ƿ��л���
	bool m_isHavePower;	//�Ƿ�������
	bool m_isHaveAgility;	//����
	bool m_isHaveMagic;	//����

	Sprite* m_Player__sprite;	//�����ͼ
	Label* m_hp_label;	//����ֵLabel

	//����ʱ��Label��ʾ���ס����������ݺ�������������ܸ�Ϊͼ�꣬������һ��Layer����
	Label* m_armor_label;
	Label* m_power_label;
	Label* m_agility_label;
	Label* m_magic_label;
};

#endif // ! _Player__H_
