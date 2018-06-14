#pragma once

#ifndef _CARD_DISPLAY_LAYER_H_
#define _CARD_DISPLAY_LAYER_H_

#include"GameConfig.h"
#include"BaseCard.h"

#include"cocos-ext.h"
USING_NS_CC_EXT;

class CardDisplayLayer : public Layer , public ScrollViewDelegate {
public:
	static CardDisplayLayer* create(Vector<BaseCard*> cards);

private:
	virtual bool init(Vector<BaseCard*> cards);

	virtual void scrollViewDidScroll(ScrollView* view); //����ʱ��Ӧ�Ļص�����
	virtual void scrollViewDidZoom(ScrollView* view);   //����ʱ��Ӧ�Ļص�����

	virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);
private:
	Vector<BaseCard*> m_cards;
	
	Size m_scrollView_visibleSize;
};


#endif // !_CARD_DISPLAY_LAYER_H_
