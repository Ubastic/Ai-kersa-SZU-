#pragma once
#ifndef _BASE_LIBRARY_H_
#define _BASE_LIBRARY_H_

#include"GameConfig.h"
#include"BaseCard.h"
#include"CardSystem.h"
#include<vector>

class BaseLibrary :public Node{
public:
	static BaseLibrary* create(std::string picPath);
	static BaseLibrary* create(std::string picPath, std::vector<CardID>& cardID);

	//��ӿ���
	void addCard(BaseCard*& card);
	void addCard(CardID cardID);
	void addCard(int cardID);

	//��ȡ���ƣ�������ƿ��С�Ƿ�����
	BaseCard*& drawCard();

	int getLibrarySize() { return m_library.size(); }	//����ƿ��С
private:
	virtual bool init(std::string picPath, std::vector<CardID>& cardID);
	virtual bool init(std::string picPath);

	virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);	//���Դ���һ���鿴���п��Ƶ�Layer

private:
	Vector<BaseCard*> m_library;

	Sprite * m_library_sprite;

};

#endif // !_BASE_LIBRARY_H_
