#include"DemoScene.h"
#include"DamageEffect.h"
#include"Player.h"
#include"BaseEnemy.h"
#include"BaseState.h"
#include"CardSystem.h"

Scene* DemoScene::createScene() {
	auto scene = Scene::create();
	auto layer = DemoScene::create();
	scene->addChild(layer);
	return scene;
}

bool DemoScene::init() {
	if (!Layer::init()) {
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();

	//����Player��
	player= Player::create("character/player.png", 80, 0, 0, 0, 9 , 3);
	player->setPosition(visibleSize.width * 1 / 4, visibleSize.height / 2);
	this->addChild(player);

	////���Ե��ˡ�
	//enemy = BaseEnemy::create("character/player.png", 100, 15, 3, 2);
	//enemy->setPosition(visibleSize.width * 3 / 4, visibleSize.height / 2);
	//this->addChild(enemy);

	//���Կ���ϵͳ��
	//��������Ǳ���������������
	//��������������Ƽס�
	//������Ů��ף����
	baseCard = CardSystem::createCardByID(CardID::Armor_Breaking);
	baseCard->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(baseCard);

	////�������Ͽ���Layer
	//m_handCard = HandCardLayer::create(5);
	//this->addChild(m_handCard);

	//ģ��غϽ����İ�ť
	auto mybutton = Button::create("CloseNormal.png", "CloseNormal.png", "CloseNormal.png");
	mybutton->setPosition( Vec2((int)(visibleSize.width / 2 ), 50) );
	mybutton->addTouchEventListener( CC_CALLBACK_2(DemoScene::testFunction, this ) );
	this->addChild(mybutton);

	//std::vector<CardID> cardID;
	//cardID.push_back(CardID::Strike);
	//cardID.push_back(CardID::Defend);
	//cardID.push_back(CardID::Inner_Strength);
	//cardID.push_back(CardID::Mortal_Strike);
	//cardID.push_back(CardID::Armor_Breaking);
	//cardID.push_back(CardID::Blessing_Of_Prince_Daughter);

	////����BaseLibrary
	//library = BaseLibrary::create("icons/library.png" , cardID);
	//library->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	//this->addChild(library);

	//BaseCard* card = library->drawCard();

	//Target target;
	//if (card->getPlayerNeed())
	//	target.players.pushBack(player);
	//switch (card->getEnemyNeed) {
	//	case 0:
	//		break;
	//	case 1:
	//		target.enemys.pushBack(enemy);
	//		break;
	//	case -1:
	//		break;
	//}
	//this->addChild(card);


	//����PowerChangeState�Ƿ���Ч��
	//powerState = PowerChangeState::create("icons/armor.png", "Demo" ,"demo", -1, 3, true);
	//player->addState(powerState);

	////���Ի���State
	//auto baseState = BaseState::create("icons/armor.png", "Armor", "armor armor ", -1);
	//baseState->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	//this->addChild(baseState);

	////����PowerUpState
	//powerUpState = PowerUpState::create("icons/armor.png", "Armor", "Get 3 Power when your rounds end", -1, 3);
	//player->addChild(powerUpState);	//��״̬������������


	//// �������ݿ��
	//std::string filename = CCFileUtils::sharedFileUtils()->fullPathForFilename("sql/sql.db");
	//std::string sql; // sql���
	//int ret;         // ִ�н����SQLITE_OK��ʾ�ɹ�ִ��

	//this->pdb = nullptr;
	//ret = sqlite3_open(filename.c_str(), &pdb);
	//if (ret != SQLITE_OK) {
	//	const char* errmsg = sqlite3_errmsg(pdb);
	//	CCLOG("sqlite open error: %s", errmsg);
	//	sqlite3_close(pdb);
	//	return false;
	//}

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(DemoScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(DemoScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(DemoScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}


//void DemoScene::onMouseMove(EventMouse* pEvent) {
//	CCLOG("%f %f", pEvent->getCursorX(), pEvent->getCursorY());
//}


//������ģ��غϽ���
bool DemoScene::onTouchBegan(Touch* pTouch, Event* pEvent) {
	////���Կ���effectЧ��
	//Target target;
	//if (baseCard->getPlayerNeed())
	//	target.players.pushBack(player);
	//switch (baseCard->getEnemyNeed()) {
	//	case 0:
	//		break;
	//	case 1:
	//		target.enemys.pushBack(enemy);
	//		break;
	//	case -1:
	//		break;
	//}
	//baseCard->effect(target);

	////CCLOG( Value(library->getLibrarySize()).asString().c_str() );
	////CCLOG( Value(baseCard->getCardID()).asString().c_str() );
	//BaseCard* card = library->drawCard();
	//card->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	////card->effect(characters);
	//this->addChild(card);


	//����PowerChangeState effct�Ƿ���Ч��
	//powerState->effect();


	////�������ݿ���ҡ�
	//std::string sql = "select * from card_zh_cn where ID = " + Value(0).asString();
	//int ret = sqlite3_exec(pdb, sql.c_str(), &callback, (void*)"para", nullptr);

	return false;
}
void DemoScene::onTouchMoved(Touch* pTouch, Event* pEvent) {

}
void DemoScene::onTouchEnded(Touch* pTouch, Event* pEvent) {

}




void DemoScene::testFunction(Ref* pSender, Widget::TouchEventType event) {
	//����DemageEffect�Ƿ���Ч
	//auto dameageEffect = DamageEffect::create(10);
	//dameageEffect->effect(player);

	//����PowerChangeState�Ƿ���Ч
}

void DemoScene::update(float dt) {

}