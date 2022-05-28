#pragma once

#include <memory>

//�S�[�����o
#include "GoalEffects.h"
#include "Player.h"
#include "ButtonUI.h"

//�X�e�[�W�N���A���̋������Ǘ�����N���X
class StageClearedControler
{
private:
	///�v���C���[�̍��W���Q�Ɓi���������֎~�j
	const RVector3* pCenterPos = &Player::Get()->CenterPosition;

public:
	StageClearedControler(){}
	~StageClearedControler(){}

	//������
	void Init();

	void Update();

	void Draw();

	//�N���A�������L����
	void ControlActivate();
	//������
	void ControlDisable();

	//UI�R���g���[���̏�Ԓ�`
	enum STAGE_CLEARED_CONTROL_STATE
	{
		CONTROL_NOT_ALLOW,	//�����Ȃ��A�`������Ȃ�
		CONTROL_DIRECING,	//���o���Ȃ̂ŃX�L�b�v�̂݋���
		CONTROL_ACTIVE,		//UI���������
		CONTROL_UI_SELECTED,
	};

	//���[�U�[�I��
	enum STAGE_CLEARED_USER_SELECTING
	{
		USER_SELECT_NEXT,
		USER_SELECT_BACK,
	};
	STAGE_CLEARED_USER_SELECTING _user_selecting = USER_SELECT_NEXT;

	//�؂�ւ����t���O
	bool isAllowSwitching = false;

private:
	STAGE_CLEARED_CONTROL_STATE ctrl_state = CONTROL_NOT_ALLOW;
	
	//�S�[�������o����N���X
	std::shared_ptr<GoalEffects> goalEffect;

	//UI�{�^��
	UI_Button _go_select_button;
	float x1 = 0.0f, y1 = 0.0f;
	UI_Button _go_next_button;
	float x2 = 0.0f, y2 = 0.0f;

	const float SELECTING_SCALE = 1.2f;

	//UI�R���g���[���̏�Ԃ��擾�A�ύX
	void Update_CheckControlStates();
	int frameCount = 0;
	const int DIRECTING_FRAME = 60;

	//��Ԃɉ��������ۂ̏���
	void Update_ControlMain();

	void Draw_UI();


};

