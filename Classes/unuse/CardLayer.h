#pragma once

#ifndef _CARD_LAYER_H_
#define _CARD_LAYER_H_

#include"GameConfig.h"
#include"BaseLibrary.h"
#include"BaseCard.h"

class CardLayer :public Layer {
public:
	static CardLayer* create( std::vector<CardID>& cardIDs );

	bool addCardToHand(BaseCard*& card);
	void addCardToCardLibrary(BaseCard*& card);
	void addCardToDisLibrary(BaseCard*& card);

	bool drawCard();	//�ӳ��ƿ��г���
	bool drawFromDisLibraryToHand();	//������������ƿ��г��ƷŻ�����
	bool drawFromDisLibraryToCardLibrary();	//������������ƿ��г��ƷŻس��ƿ�

	int getSizeOfHandCard() { return m_hand_cards.size(); }
	int getSizeOfCardLibrary() { return m_card_library->getLibrarySize(); }
	int getSizeOfDiscardLibrary() { return m_discard_library->getLibrarySize(); }

private:
	void updateLayout();	//���²���

	virtual bool init( std::vector<CardID>& cardIDs );
	virtual void update(float dt);

	virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);
	virtual void onTouchMoved(Touch* pTouch, Event* pEvent);
	virtual void onTouchEnded(Touch* pTouch, Event* pEvent);

	virtual void onMouseMove(EventMouse* pEvent);	//���ڼ�����ͣ���ڿ�����ͼ��ʱ�ĺ���

private:
	Size m_visibleSize;

	BaseLibrary * m_card_library;
	BaseLibrary* m_discard_library;

	Vector<BaseCard*> m_hand_cards;
	BaseCard* m_current_card;

	bool m_isHovor;	//�Ƿ�������������
	bool m_isSelect;	//�Ƿ�ѡ����һ�ſ���

};

#endif // !_CARD_LAYER_H_

