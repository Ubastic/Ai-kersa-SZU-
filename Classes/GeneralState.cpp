#include"GeneralState.h"
#include"BaseCharacter.h"

GeneralState* GeneralState::create(StateType type, std::string picPath, std::string name , std::string info, int rounds, bool isCanOverlay) {
	GeneralState* pRet = new(std::nothrow)GeneralState();
	if (pRet && pRet->init(type, picPath, name, info, rounds , isCanOverlay)) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}
bool GeneralState::init(StateType type, std::string picPath, std::string name, std::string info, int rounds, bool isCanOverlay) {
	if (!BaseState::init(type, picPath, name, info, rounds, false, false , isCanOverlay)) {
		return false;
	}
	return true;
}

void GeneralState::effect() {
	if (m_isCanEffect) {

	}
	m_left_rounds--;	//�����غ�����1
	updateRoundsLabel();
	//����������������ý�������
	if (m_left_rounds == 0) {
		effect_when_end();
	}
}
void GeneralState::effect_when_end() {	//�Ƴ�״̬
	auto parent = this->getParent();
	((BaseCharacter*)parent)->removeState(this);
}