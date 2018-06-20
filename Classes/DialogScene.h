#pragma once

#ifndef _DIALOG_SCENE_H_
#define _DIALOG_SCENE_H_

#include"GameConfig.h"

#define TAG_DIALOG_COLOR_LAYER 1000
#define TAG_NAME_COLOR_LAYER 1001

class DialogScene :public Layer {
//public:
//	static Scene* createScene( );	//���Բ���ʹ��
//	static Scene* createScene(std::string dialog_form_name );	//dialog����

protected:
	static DialogScene* create(std::string dialog_form_name );
	virtual bool init( std::string dialog_form_name );

private:

	//�����ݿ��г�ʼ��
	bool initDialogFromSQL( std::string dialog_form_name );
	//���¶Ի���ʹ����ʾ��
	void toUpdateDialog();
	//�����Ի�����
	virtual void endDialogScene(Ref* ref) = 0;

	virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);
	virtual void onTouchEnded(Touch* pTouch, Event* pEvent);

protected:
	LayerColor * m_mask_layer;

private:
	Size m_visibleSize;

	std::vector<std::string> m_background_picPaths;
	std::vector<std::string> m_character_picPaths;
	std::vector<std::string> m_names;
	std::vector<std::string> m_dialogs;

	std::string m_pre_background_picPath;
	std::string m_pre_character_picPath;
	std::string m_pre_name;

	int m_counter = 0;
	int m_n;	//��������ʾdialog

	Sprite* m_background_sprite;
	Sprite* m_character_sprite;
	Label* m_name_label;
	Label* m_dialog_label;

	bool m_is_dialog_showing;
};


#endif // !_DIALOG_SCENE_H_
