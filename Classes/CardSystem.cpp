#include"CardSystem.h"
#include"EffectHeader.h"

BaseCard* CardSystem::createCardByID(CardID id) {
	//auto dict = Dictionary::createWithContentsOfFile("zh-cn.xml");

	std::string filename = CCFileUtils::sharedFileUtils()->fullPathForFilename("sql/sql.db");	//�������ݿ�����·��
	sqlite3* pdb;

	int ret = sqlite3_open(filename.c_str(), &pdb);	//�����ݿ�
	if (ret != SQLITE_OK) {	//��������ݿ�ʧ��
		const char* errmsg = sqlite3_errmsg(pdb);
		CCLOG("sqlite open error: %s", errmsg);
		sqlite3_close(pdb);

		return NULL;
	}

	//Ѱ��ID�������ƵĻ�����Ϣ
	std::string sql = "select * from card_zh_cn where ID=" + Value(id).asString();
	char** table; // ��ѯ���
	int r, c;     // ����������
	//��ʼ��ѯ
	sqlite3_get_table(pdb, sql.c_str(), &table, &r, &c, nullptr);

	//�������ƻ�����Ϣ
	std::string name = table[1 * c + 1];	//����
	std::string info = table[1 * c + 2];	//��Ϣ
	std::string cost = table[1 * c + 3];	//����
	std::string picPath = table[1 * c + 4];	//���Ʊ���
	// ɾ����ѯ��
	sqlite3_free_table(table);

	BaseCard* card = BaseCard::create(id, name, info, cost, picPath, m_world);

	//����ID���Ч��
	switch (id) {
		case CardID::Strike:
			card->m_Property = card->m_pre_property = { -5 , 0 , 0 };
			card->updateCardInfo();
			card->m_target_need = { 0 , 1 , 0 };
			card->m_card_type = CardType::Attack_Card;

			//��ӶԵ����˺�Effect
			card->addEffect(PropertyChangeEffect::create( TargetType::TO_ENEMY , Property::Health , &card->m_Property.damage_number /*&card->m_Property.damage_number*/));

			break;

		case CardID::Defend:
			card->m_Property = card->m_pre_property = { 0 , +5 , 0 };
			card->updateCardInfo();
			card->m_target_need = { 1 , 0 , 0 };
			card->m_card_type = CardType::Skill_Card;

			//��Ӷ��Լ�����Effect
			card->addEffect(PropertyChangeEffect::create( TargetType::TO_PLAYER , Property::Armor, &card->m_Property.armor_number /*&card->m_Property.armor_number*/));

			break;

		case CardID::Inner_Strength:
			card->m_Property = card->m_pre_property = { 0 , 0 , 0 };
			card->updateCardInfo();
			card->m_target_need = { 1 , 0 , 0 };
			card->m_card_type = CardType::Skill_Card;

			//��������ı�Effect����EffectΪ˲�����������������״̬ͼ��
			card->addEffect(PropertyChangeEffect::create( TargetType::TO_PLAYER ,Property::Power , new int(3)));
			//���״̬Effect����״̬���ڻ���������isCanEffect��Ϊfalse��ÿ�غϲ�������
			card->addEffect(StateEffect::create( TargetType::TO_PLAYER ,StateType::Property_Change , "state/inner_strength.png" , name , info , 1 , false , true , false , Property::Power , new int(3)));

			break;

		case CardID::Mortal_Strike:
			card->m_Property = card->m_pre_property = { -8 , 0 , 0 };
			card->updateCardInfo();
			card->m_target_need = { 0 , 1 , 0 };
			card->m_card_type = CardType::Attack_Card;

			//�Ե������8���˺������С�ڵ���30%�˺��������5���˺�
			card->addEffect(ConditionRatioEffect::create(
				TargetType::TO_ENEMY, Property::Health, Condition_Way::Less_Equal, 0.3, TargetType::TO_ENEMY, Property::Health, &card->m_Property.damage_number , 5));
		
			break;

		case CardID::Armor_Breaking:
			card->m_Property = card->m_pre_property = { 0 , 0 , 0 };
			card->updateCardInfo();
			card->m_target_need = { 0 , 1 , 0 };

			//����Effect
			card->addEffect(
				ConditionEffect::create(
					TargetType::TO_ENEMY, Property::Armor, Condition_Way::Less_Equal, 10, TargetType::TO_ENEMY, Property::Armor, new int(-5), 2) );
			break;

		case CardID::Blessing_Of_Prince_Daughter: 
			card->m_Property = card->m_pre_property = { 0 , 0 , 0 };
			card->updateCardInfo();
			card->m_target_need = { 1 , 0 , 0 };

			card->addEffect(StateEffect::create(TargetType::TO_PLAYER, StateType::Property_Change, "state/blessing_of_prince_daughter.png", name, info, 3, true, false, true, Property::Power, new int(1)));
			break;

		case CardID::Health_Potion:
			card->m_Property = card->m_pre_property = { 0 , 0 , 0 };
			card->updateCardInfo();
			card->m_target_need = { 1 , 0 , 0 };

			card->addEffect(StateEffect::create(TargetType::TO_PLAYER,StateType::Property_Change,  "state/health_potion.png", name, info, 6, true, false, true , Property::Health  ,new int(5)));
			break;

		case CardID::Preparation:
			card->m_Property = card->m_pre_property = { 0 , 0 , 0 };
			card->updateCardInfo();
			card->m_target_need = { 1 , 0 , 0 };

			card->addEffect(PropertyChangeEffect::create(TargetType::TO_PLAYER , Property::Cost , new int(1) ));
			break;

		case CardID::Split:
			card->m_Property = card->m_pre_property = { -4 , 0 , 0 };
			card->updateCardInfo();
			card->m_target_need = { 0 , 1 , 0 };

			card->addEffect( StateEffect::create(TargetType::TO_ENEMY, StateType::Property_Change , "state/split.png", name, info, 3, true, false,false , Property::Health, &card->m_Property.damage_number ));

			break;

		case CardID::Cleave:
			card->m_Property = card->m_pre_property = { -7 , 0 , 0 };
			card->updateCardInfo();
			card->m_target_need = { 0 , -1 , 0 };

			card->addEffect(PropertyChangeEffect::create(TargetType::TO_ENEMY, Property::Health , &card->m_Property.damage_number ));

			break;

		case CardID::Pot_of_Avarice:
			card->m_Property = card->m_pre_property = { 0 , 0 , 0 };
			card->updateCardInfo();
			card->m_target_need = { 0 , 0 , 1 };
	
			card->addEffect(DrawCardEffect::create(TargetType::TO_CARD_LAYER, 2, DrawFrom::From_Card_Library));
			break;

		case CardID::Burst_Limit:
			card->m_Property = card->m_pre_property = { 0 , 0 , 0 };
			card->updateCardInfo();
			card->m_target_need = { 1 , 0 , 0 };

			card->addEffect(PropertyChangeEffect::create(TargetType::TO_PLAYER, Property::Power, new int(0)));
			card->addEffect(StateEffect::create(TargetType::TO_PLAYER, StateType::Property_Change, "state/burst_limit.png", name, info, 1, false, true, false, Property::Power, new int(0)));
			break;

		case CardID::Tie:
			card->m_Property = card->m_pre_property = { 0 , 0 , 0 };
			card->updateCardInfo();
			card->m_target_need = { 0 , 1 , 0 };

			card->addEffect(PropertyChangeEffect::create(TargetType::TO_ENEMY, Property::Power, new int(-6)));
			card->addEffect(StateEffect::create(TargetType::TO_ENEMY,StateType::Property_Change , "state/tie.png" , name , info , 1 ,false , true , false , Property::Power, new int(-6)));
			break;

		case CardID::Magic_Book:
			card->m_Property = card->m_pre_property = { 0 , 0 , 0 };
			card->updateCardInfo();
			card->m_target_need = { 1 , 0 , 0 };

			card->addEffect(ConditionEffect::create(TargetType::TO_PLAYER, Property::Magic, Condition_Way::Greater_Equal, 10, TargetType::TO_PLAYER, Property::Magic, new int(2), 2 ));
			break;

		case CardID::Magic_Missile:
			card->m_Property = card->m_pre_property = { 0 , 0 , 0 };
			card->updateCardInfo();
			card->m_target_need = { 0 , -1 , 0 };

			//3�Σ������Ŀ�����[����]���˺�
			card->addEffect(DamageEffect::create(TargetType::TO_ENEMY, &card->m_Property.magic_number, 3, true));
			//card->addEffect(RandomTargetDamageEffect::create(TargetType::TO_ENEMY, &card->m_Property.magic_number, 3));
			break;

		case CardID::Enchanted_Weapon:
			card->m_Property = card->m_pre_property = { 0 , 0 , 0 };
			card->updateCardInfo();
			card->m_target_need = { 1 , 0 , 0 };
			card->m_card_type = CardType::Magic_Card;	//ħ������

			card->addEffect(PropertyChangeEffect::create(TargetType::TO_PLAYER, Property::Power, new int(5)));
			break;

		case CardID::Arcane_Breath:
			card->m_Property = card->m_pre_property = { 0 , 0 , 0 };
			card->updateCardInfo();
			card->m_target_need = { 0 , 1 , 0 };
			card->m_card_type = CardType::Magic_Card;	//ħ������

			//���5���������˺�����Ϊ����Ѫ��һ������0������������Զ����
			card->addEffect(ConditionEffect::create(TargetType::TO_ENEMY, Property::Health, Condition_Way::Greater_Equal, 0, TargetType::TO_ENEMY, Property::Health, &card->m_Property.magic_number, -6));
			break;

		case CardID::Backflip:
			card->m_Property = card->m_pre_property = { 0 , +3 , 0 };
			card->updateCardInfo();
			card->m_target_need = { 1 , 0 , 1 };

			card->addEffect(DrawCardEffect::create(TargetType::TO_CARD_LAYER, 4, DrawFrom::From_Card_Library));
			card->addEffect(PropertyChangeEffect::create(TargetType::TO_PLAYER, Property::Armor, &card->m_Property.armor_number));
			break;
	}

	//�ر����ݿ�
	sqlite3_close(pdb);
	return card;
}

b2World* CardSystem::m_world = new b2World(b2Vec2(0.0f, 0.0f));