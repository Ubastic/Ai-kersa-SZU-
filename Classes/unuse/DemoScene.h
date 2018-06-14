#pragma once

#ifndef _DEMO_SCENE_H_
#define _DEMO_SCENE_H_

#include"GameConfig.h"

#include"BaseCard.h"
#include"Player.h"
#include"BaseEnemy.h"

#include"StateHeader.h"
#include"EffectHeader.h"

#include"BaseLibrary.h"

#include"sqlite3\sqlite3.h"	//����sqlite3�Ƿ����

#include"ui\CocosGUI.h"
using namespace cocos2d::ui;

//���Գ��������ڲ��Ը��ָ����Ķ����Ƿ��������
class DemoScene :public Layer {
public:
	static Scene* createScene();

	virtual bool init();
	virtual void update(float dt);
	CREATE_FUNC(DemoScene);

	void testFunction( Ref* pSender, Widget::TouchEventType event );

private:

	virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);
	virtual void onTouchMoved(Touch* pTouch, Event* pEvent);
	virtual void onTouchEnded(Touch* pTouch, Event* pEvent);

private:
	Size visibleSize;

	BaseCard * baseCard;

	Player* player;
	BaseEnemy* enemy;

	BaseLibrary* library;

	PropertyChangeState* powerState;
	//HandCardLayer* m_handCard;


	//sqlite3* pdb;	//�������ݿ�
};


//int callback(void* para, int col_num, char** col_value, char** col_name);
#endif // !_DEMO_SCENE_H_
