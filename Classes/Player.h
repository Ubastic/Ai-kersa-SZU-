#pragma once

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include"BaseCharacter.h"

class Player :public BaseCharacter {
public:
	//ͼƬ·�������HP�����ס����������ݡ���������߷���
	static Player* create(std::string picPath, int max_hp, int armor, int power, int agility, int magic , int max_cost );

	//�ı�����
	void changeMagic(int magic);
	//�ı����
	void changeCost(int cost);
	//���÷���
	void resetCost() { m_cost = m_max_cost; }
	//�ı�������
	void changeMaxCost(int max_cost);

	int getMagic() { return m_Magic; }
	int getCost() { return m_cost; }
	int getMaxCost() { return m_max_cost; }
	//�Ƿ�������ֵ
	bool isHaveMagic() { return m_isHaveMagic; }

	void effect_when_round_end();
private:
	Player();
	~Player();

	//ͼƬ·�������HP�����ס����������ݡ�����
	bool init(std::string picPath, int max_hp, int armor, int power, int agility, int magic , int max_cost );
private:
	int m_Magic;	//����ֵ
	bool m_isHaveMagic;	//�Ƿ�������ֵ

	Label* m_magic_label;	//����Label

	int m_max_cost;
	int m_cost;
};
#endif // !_PLAYER_H_