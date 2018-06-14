#include"PropertyChangeState.h"

PropertyChangeState* PropertyChangeState::create(std::string picPath, std::string name, std::string info , int rounds,bool isCanEffect , bool isTemporary, bool isCanOverlay, Property property, int property_change) {
	PropertyChangeState* pRet = new(std::nothrow)PropertyChangeState();
	if (pRet && pRet->init(picPath, name, info , rounds,  isCanEffect , isTemporary , isCanOverlay, property, property_change) ) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool PropertyChangeState::init(std::string picPath, std::string name, std::string info , int rounds,  bool isCanEffect , bool isTemporary , bool isCanOverlay ,Property property, int property_change) {
	if (!BaseState::init(StateType::Property_Change, picPath, name, info , rounds, isCanEffect , isTemporary , isCanOverlay )) {
		return false;
	}
	m_property = property;
	m_property_change = property_change;
	return true;
}

void PropertyChangeState::effect() {
	if (m_isCanEffect) {
		//��ȡ���ڵ�Ӷ��޸ĸ��ڵ����Ӧ����
		auto parent = (BaseCharacter*)(this->getParent());
		switch (m_property) {
			case Property::Health:
				if (m_property_change > 0) {
					parent->heal(m_property_change);
				}
				else if (m_property_change < 0) {
					parent->hurt(-m_property_change);
				}
				break;

			case Property::Armor:
				if( m_property_change == 0 ){
					parent->changeArmor(parent->getArmor());
				}
				else {
					parent->changeArmor(m_property_change);
				}
				break;

			case Property::Power:
				if (m_property_change == 0) {
					parent->changePower(parent->getPower());
				}
				else {
					parent->changePower(m_property_change);
				}
				break;
			case Property::Agility:
				if (m_property_change == 0) {
					parent->changeAgility(parent->getAgility());
				}
				else {
					parent->changeAgility(m_property_change);
				}
				break;
			case Property::Magic:
				if (m_property_change == 0) {
					((Player*)parent)->changeMagic(((Player*)parent)->getMagic());
				}
				else {
					((Player*)parent)->changeMagic(m_property_change);
				}
				break;
		}
	}
	m_left_rounds--;	//�����-1����ʾ��Զ������ʧ����ô--Ҳû��ϵ
	updateRoundsLabel();
	//����������������ý�������
	if (m_left_rounds == 0) {
		effect_when_end();
	}
}

void PropertyChangeState::effect_when_end() {
	auto parent = (BaseCharacter*)(this->getParent());
	if (m_isTemporary) {	//�����ߵ���������ʱ�ģ���ȥ�����ӵ�����ֵ
		switch (m_property) {
			case Property::Health:
				if (m_property_change > 0) {
					parent->hurt( m_property_change * m_continues_rounds );
				}
				else if (m_property_change < 0) {
					parent->heal( -m_property_change * m_continues_rounds );
				}
				break;

			case Property::Armor:
				if (m_property_change == 0) {
					parent->changeArmor( -parent->getArmor()/2 );
				}
				else {
					parent->changeArmor(-m_property_change * m_continues_rounds);
				}
				break;

			case Property::Power:
				if (m_property_change == 0) {
					parent->changePower( -parent->getPower()/2 );
				}
				else {
					parent->changePower(-m_continues_rounds * m_property_change);
				}
				break;

			case Property::Agility:
				if (m_property_change == 0) {
					parent->changeAgility( -parent->getAgility() / 2);
				}
				else {
					parent->changeAgility(-m_continues_rounds * m_property_change);
				}
				break;

			case Property::Magic:
				if (m_property_change == 0) {
					((Player*)parent)->changeMagic(-((Player*)parent)->getMagic()/2);
				}
				else {
					((Player*)parent)->changeMagic(-m_continues_rounds * m_property_change);
				}
				break;
		}
	}
	//�Ӹ��ڵ�ɾ��״̬
	parent->removeState(this);
}