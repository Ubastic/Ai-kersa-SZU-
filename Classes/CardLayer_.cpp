#include"CardLayer_.h"
#include"CardDisplayLayer.h"

CardLayer_* CardLayer_::create(std::vector<CardID>& cardIDs) {
	CardLayer_* pRet = new(std::nothrow)CardLayer_();
	if (pRet && pRet->init(cardIDs)) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool CardLayer_::init(std::vector<CardID> cardIDs) {
	if (!Layer::init()) {
		return false;
	}
	m_visibleSize = _director->getVisibleSize();

	m_card_library_button = MenuItemImage::create(
		"icons/library.png",
		"icons/library.png",
		CC_CALLBACK_1(CardLayer_::checkCardLibrary, this));
	m_card_library_button->setName("card_library_button");
	m_card_library_button->setPosition(m_visibleSize.width * 1 / 16, m_visibleSize.height * 1 / 8);

	m_dis_library_button = MenuItemImage::create(
		"icons/discard.png",
		"icons/discard.png",
		CC_CALLBACK_1(CardLayer_::checkCardLibrary, this));
	m_dis_library_button->setName("discard_library_button");
	m_dis_library_button->setPosition(m_visibleSize.width * 15 / 16, m_visibleSize.height * 1 / 8);

	auto menu = Menu::create(m_card_library_button, m_dis_library_button, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	m_card_library_label = Label::create("0" , "Arical" , 16);
	m_card_library_label->setPosition(m_card_library_button->getContentSize().width / 2, -m_card_library_button->getContentSize().height / 2);
	m_card_library_button->addChild(m_card_library_label);


	m_discard_library_label = Label::create("0", "Arical", 16);
	m_discard_library_label->setPosition(m_dis_library_button->getContentSize().width / 2, -m_dis_library_button->getContentSize().height / 2);
	m_dis_library_button->addChild(m_discard_library_label);

	for (CardID id : cardIDs) {
		auto card = CardSystem::createCardByID(id);
		addCardToCardLibrary(card);
	}

	auto listener = EventListenerMouse::create();
	listener->onMouseMove = CC_CALLBACK_1(CardLayer_::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto listener_ = EventListenerTouchOneByOne::create();
	listener_->onTouchBegan = CC_CALLBACK_2(CardLayer_::onTouchBegan, this);
	listener_->onTouchMoved = CC_CALLBACK_2(CardLayer_::onTouchMoved, this);
	listener_->onTouchEnded = CC_CALLBACK_2(CardLayer_::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener_, this);

	this->scheduleUpdate();

	return true;
}

BaseCard* CardLayer_::drawFromCardLibrary() {
	return drawFromCardLibraryAtID((rand() * 101) % m_card_library.size());
}
BaseCard* CardLayer_::drawFromCardLibraryAtID(int index) {
	if (m_card_library.size() == 0) {
		return NULL;
	}
	if (index < 0 || index >= m_card_library.size()) {
		return NULL;
	}
	BaseCard* card = m_card_library.at(index);
	m_card_library.eraseObject(card);
	m_card_library_label->setString(Value(m_card_library.size()).asString());
	return card;
}


BaseCard* CardLayer_::drawFromDisLibrary() {
	return drawFromDisLibraryAtID((rand() * 101) % m_discard_library.size());
}
BaseCard* CardLayer_::drawFromDisLibraryAtID(int index) {
	if (m_discard_library.size() == 0) {
		return NULL;
	}

	if (index < 0 || index >= m_discard_library.size()) {
		return NULL;
	}
	BaseCard* card = m_discard_library.at(index);
	m_discard_library.eraseObject(card);
	m_discard_library_label->setString(Value(m_discard_library.size()).asString());
	return card;
}


bool CardLayer_::drawCardAtID(int index) {	//һ����˵�������index���ڵģ���Ϊ��Ҫָ��ĳ�ſ���
	//����������Ѵﵽ����
	if (m_hand_cards.size() == MAX_HAND_CARD_NUM) {
		return false;
	}

	auto card = drawFromCardLibraryAtID(index);
	if (card == NULL) {
		return false;
	}
	m_hand_cards.pushBack(card);
	card->setPosition(m_card_library_button->getPosition());
	card->setRotation(90 + rand() % 10);
	card->setScale(0);

	updateLayout();
	return true;
}
bool CardLayer_::drawCard() {
	//����������Ѵﵽ����
	if (m_hand_cards.size() == MAX_HAND_CARD_NUM) {
		return false;
	}
	//������ƿ�����ƿⶼû�����ˣ��Ǿ�û�취������
	if (m_card_library.size() == 0 && m_discard_library.size() == 0) {
		return false;
	}

	//���ֻ�ǳ��ƿ�û���ƣ����ȴ����ƿ��л�����п��������ƿ�
	if (m_card_library.size() == 0) {
		while (m_discard_library.size() != 0) {
			m_card_library.pushBack(drawFromDisLibrary());
			//m_card_library.pushBack(m_discard_library.back());
			//m_discard_library.popBack();
		}
	}

	return drawCardAtID((rand() * 101) % m_card_library.size());
}
bool CardLayer_::drawCard( int num ) {
	if (num == 0) {
		return true;
	}
	//����������ƿ�����ƿ���������ѹΪ���ֵ
	if (num > m_card_library.size() + m_discard_library.size()) {
		num = m_card_library.size() + m_discard_library.size();
	}
	if (num == 0) {	//û���κ��Ƶ������
		return false;
	}

	for (int i = 0; i < num; i++) {
		drawCard();
	}
	return true;
}
void CardLayer_::drawFull() {
	while (drawCard()) {	//һֱ���ƣ�ֱ��������û��Ϊֹ

	}
}


bool CardLayer_::discardAtID( int index , bool isDestory ) {
	if (m_hand_cards.size() == 0) {
		return false;
	}

	if (index < 0 || index >= m_hand_cards.size()) {
		return false;
	}
	auto card = m_hand_cards.at(index);
	card->setVisible(false);	//��Ϊ���ɼ�
	m_hand_cards.eraseObject(card);	//��������ȥ��
	updateLayout();
	if (!isDestory) {
		m_discard_library.pushBack(card);
		m_discard_library_label->setString(Value(m_discard_library.size()).asString());
	}
	else {
		m_destory_library.pushBack(card);
	}
	return true;
}
bool CardLayer_::discard(bool isDestory) {
	return discardAtID((rand() * 101) % m_hand_cards.size(), isDestory);
}
void CardLayer_::discardAll(bool isDestory) {
	while (discard(isDestory)) {

	}
}


bool CardLayer_::drawFromDisLibraryToHand() {
	if (m_discard_library.size() == 0) {
		return false;
	}
	return drawFromDisLibraryToHandAtID((rand() * 101) % m_discard_library.size());
}
bool CardLayer_::drawFromDisLibraryToHand( int num ) {
	if (num == 0) {
		return true;
	}
	bool flag;
	for (int i = 0; i < num; i++) {
		flag = drawFromDisLibraryToHand();
	}
	return flag;
}
bool CardLayer_::drawFromDisLibraryToHandAtID(int index) {
	if (m_hand_cards.size() == MAX_HAND_CARD_NUM) {
		return false;
	}

	auto card = drawFromDisLibraryAtID(index);
	if (card == NULL) {
		return false;
	}

	m_hand_cards.pushBack(card);
	card->setPosition(m_dis_library_button->getPosition());
	card->setRotation(90 + rand() % 10);
	card->setScale(0);

	updateLayout();
	return true;

}
bool CardLayer_::drawFromDisLibraryToCardLibrary() {
	if (m_discard_library.size() == 0) {
		return false;
	}
	return drawFromDisLibraryToCardLibraryatID((rand() * 101) % m_discard_library.size());
}
bool CardLayer_::drawFromDisLibraryToCardLibraryatID(int index) {
	auto card = drawFromDisLibraryAtID(index);
	if (card == NULL) {
		return false;
	}

	m_card_library.pushBack(card);
	m_card_library_label->setString(Value(m_card_library.size()).asString());

	return true;
}



//Ŀǰ�Ľ���������ӿ��Ƶ�ʱ����Ѿ�ȫ��addChild��
//���ʵ���ʱ����Ϊ�ɼ��Ͳ��ɼ�
bool CardLayer_::addCardToHandCard(BaseCard*& card) {
	if (m_hand_cards.size() == MAX_HAND_CARD_NUM) {	//������ڿ����������������ƿ�
		addCardToDisLibrary(card);
		return false;
	}
	else {
		this->addChild(card);

		m_hand_cards.pushBack(card);	//�ѿ��Ž�������
		updateLayout();	//���²��֣�����Ϊ�ɼ�
		return true;
	}
}
void CardLayer_::addCardToCardLibrary(BaseCard*& card) {
	this->addChild(card);	//���������ڵ㣬����Ϊ���ɼ�
	card->setVisible(false);

	m_card_library.pushBack(card);
	m_card_library_label->setString(Value(m_card_library.size()).asString());
}
void CardLayer_::addCardToDisLibrary(BaseCard*& card) {
	this->addChild(card);	//���������ڵ㣬����Ϊ���ɼ�
	card->setVisible(false);

	m_discard_library.pushBack(card);
	m_discard_library_label->setString( Value(m_discard_library.size()).asString() );
}


//���²��ֺ���
void CardLayer_::updateLayout() {
	int card_num = m_hand_cards.size();
	if (card_num == 0)	return;

	int mid = card_num / 2;
	float space = m_visibleSize.width * touchableSize.width / (m_hand_cards.size() + 1) * card_num / MAX_HAND_CARD_NUM;

	for (int i = 0; i < card_num; i++) {
		BaseCard* card = m_hand_cards.at(i);
		card->stopAllActions();
		card->setVisible(true);	//�Ѹÿ���Ϊ�ɼ�

		float x;
		float x_;
		if (i <= mid) {
			x = -(mid - i) * space;
			if (i != mid) {
				x_ = -(mid - i - 1) * space + m_visibleSize.width / 2;
			}
			else {
				x_ = x + m_visibleSize.width / 2;
			}
		}
		else {
			x = (i - mid) * space;
			x_ = (i - mid - 1) * space + m_visibleSize.width / 2;
		}
		//����һ�����κ�������x����y��
		float y = -2 * card->getContentSize().height / (m_visibleSize.width * touchableSize.width) / (m_visibleSize.width * touchableSize.width) * x * x +
			card->getContentSize().height * 3 / 7;

		card->runAction( Spawn::create( 
			EaseInOut::create( MoveTo::create( 0.2f , Vec2(x + m_visibleSize.width / 2, y)) , 1.0f) , 
			ScaleTo::create(0.2f, 1.0f), NULL )
		);
		//card->runAction(ScaleTo::create(0.2f, 1.0f));
		//card->setPosition(x + m_visibleSize.width / 2, y);
		Vec2 rot = Vec2(x + m_visibleSize.width / 2, y) - Vec2(x_, -m_visibleSize.height / 3);
		//������ת�Ƕ�
		if (i < mid && (90 - CC_RADIANS_TO_DEGREES(rot.getAngle()) ) != card->getRotation()  ) {
			card->runAction(RotateTo::create(0.2f, 90 - CC_RADIANS_TO_DEGREES(rot.getAngle()) ) );
			//card->setRotation(CC_RADIANS_TO_DEGREES(rot.getAngle() - 90));
		}
		else if( (90 - CC_RADIANS_TO_DEGREES(rot.getAngle())) != card->getRotation() ) {
			card->runAction(RotateTo::create(0.2f, 90 - CC_RADIANS_TO_DEGREES( rot.getAngle())));
			//card->setRotation(90 - CC_RADIANS_TO_DEGREES(rot.getAngle()));
		}
	}
}
void CardLayer_::checkCardLibrary(Ref* pSender) {
	Vector<BaseCard*> cards;
	if (((Node*)pSender)->getName() == "card_library_button") {
		for (BaseCard* card : m_card_library) {
			cards.pushBack(CardSystem::createCardByID(card->getCardID()));
		}
	}
	else {
		for (BaseCard* card : m_discard_library) {
			cards.pushBack(CardSystem::createCardByID(card->getCardID()));
		}
	}

	Layer* card_display_layer;
	card_display_layer = CardDisplayLayer::create(cards);
	this->addChild(card_display_layer, 103);
}

//void CardLayer_::useCard() {
//	//���������Ƴ����ƣ�����Ϊ���ɼ�
//	m_hand_cards.eraseObject(m_current_card);
//	m_discard_library.pushBack(m_current_card);
//	m_current_card->setVisible(false);
//}

void CardLayer_::update(float dt) {
	for (int i = 0; i < m_hand_cards.size(); i++) {
		BaseCard* card = m_hand_cards.at(i);
		if (card != m_current_card) {
			card->setScale(1.0f);
			card->setZOrder(i);
		}
	}
}

bool CardLayer_::onTouchBegan(Touch* pTouch, Event* pEvent) {
	CCLOG("CARDLAYER-TOUCH");
	if (m_isHovor) {
		m_isSelect = true;
		return true;
	}
	else {
		return false;
	}
}
void CardLayer_::onTouchMoved(Touch* pTouch, Event* pEvent) {
	m_current_card->setPosition(pTouch->getLocation());
}
void CardLayer_::onTouchEnded(Touch* pTouch, Event* pEvent) {
	CCLOG("CARDLAYER-TOUCH-END");
	if (pTouch->getLocation().y > m_visibleSize.height * touchableSize.height) {
		//�������ƽ���effect
		auto scene = (GameSceneDemo*)getParent();
		Target target = scene->getTarget(m_current_card);	//�Ӹ��ڵ��ȡTarget
		if (target.isReady) {
			//�ȴ�������ȥ��
			m_hand_cards.eraseObject(m_current_card);
			m_discard_library.pushBack(m_current_card);
			m_discard_library_label->setString(Value(m_discard_library.size()).asString());
			m_current_card->setVisible(false);

			//Ȼ������
			m_current_card->effect(target);

			//m_current_card->runAction(MoveTo::create(0.2f, m_discard_library_sprite->getPosition()));
			//m_current_card->runAction( RotateTo::create(0.2f, 90 + rand()));

			/*m_current_card->runAction( Sequence::create( 
				Spawn::create( MoveTo::create(0.2f, m_discard_library_sprite->getPosition()), RotateTo::create(0.2f, 90 + rand()) , NULL),
				CallFunc::create( CC_CALLBACK_0( CardLayer_::useCard , this ) ) , 
				NULL)
			);*/
			//���������Ƴ����ƣ�����Ϊ���ɼ�
		}
	}
	updateLayout();
	m_isSelect = false;
	m_isHovor = false;
	m_current_card = NULL;
}

void CardLayer_::onMouseMove(EventMouse* pEvent) {
	if (!m_isSelect) {
		b2AABB touchAABB;	//������AABB
		touchAABB.lowerBound.Set(pEvent->getCursorX() / PTM_RATIO - 0.0001, pEvent->getCursorY() / PTM_RATIO - 0.0001);
		touchAABB.upperBound.Set(pEvent->getCursorX() / PTM_RATIO + 0.0001, pEvent->getCursorY() / PTM_RATIO + 0.0001);

		for (int i = m_hand_cards.size() - 1; i >= 0; i--) {
			BaseCard* card = m_hand_cards.at(i);
			if (card->getBody()->GetFixtureList()->GetAABB(0).Contains(touchAABB)) {
				card->setScale(1.25f);
				card->setZOrder(10);

				m_current_card = card;
				m_isHovor = true;
				return;
			}
		}
		m_current_card = NULL;
		m_isHovor = false;
		return;
	}
}

void CardLayer_::effect_when_round_end() {
	for (int i = 0; i < m_draw_when_round_end; i++) {
		drawCard();
	}
}