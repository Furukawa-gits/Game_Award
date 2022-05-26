#pragma once
#include "Raki_Input.h"
#include <DirectXMath.h>

// ���͂��܂Ƃ߂��N���X
class InputManger final
{
public: //�V���O���g����
	static InputManger* Get();
private:
	InputManger();
	InputManger(const InputManger&) = delete;
	~InputManger()
	{
	}
	InputManger operator=(const InputManger&) = delete;

public: //�T�u�N���X
	enum StickDirection
	{
		NONE,  //�ǂ̕����ɂ��X���Ă��Ȃ�
		LEFT,  //���ɌX���Ă���
		UP,    //��ɌX���Ă���
		RIGHT, //�E�ɌX���Ă���
		DOWN   //���ɌX���Ă���
	};

public: //�ÓI�����o�֐�
	// �X�V
	static void Update();
	// �}�E�X�̓��͏�ԍX�V
	static void MouseInputUpdate();

public: //�ÓI�����o�ϐ�
	static bool isMenu; //���j���[�̗L��
private:
	static DirectX::XMFLOAT2 pressPos;
	static DirectX::XMFLOAT2 releasePos;
	static DirectX::XMFLOAT2 dragDis;

public: //�����o�֐�
	// �I��
	bool Escape();
	// �I��(�������u�Ԃ̔���)
	bool EscapeTrigger();
	// �I��(�������u�Ԃ̔���)
	bool EscapeReturn();
	// ��
	bool Up();
	// ��(�������u�Ԃ̔���)
	bool UpTrigger();
	// ��(�������u�Ԃ̔���)
	bool UpReturn();
	// ��
	bool Down();
	// ��(�������u�Ԃ̔���)
	bool DownTrigger();
	// ��(�������u�Ԃ̔���)
	bool DownReturn();
	// ��
	bool Left();
	// ��(�������u�Ԃ̔���)
	bool LeftTrigger();
	// ��(�������u�Ԃ̔���)
	bool LeftReturn();
	// �E
	bool Right();
	// �E(�������u�Ԃ̔���)
	bool RightTrigger();
	// �E(�������u�Ԃ̔���)
	bool RightReturn();
	// ��(�T�u)
	bool SubUp();
	// ��(�T�u)(�������u�Ԃ̔���)
	bool SubUpTrigger();
	// ��(�T�u)(�������u�Ԃ̔���)
	bool SubUpReturn();
	// ��(�T�u)
	bool SubDown();
	// ��(�T�u)(�������u�Ԃ̔���)
	bool SubDownTrigger();
	// ��(�T�u)(�������u�Ԃ̔���)
	bool SubDownReturn();
	// ��(�T�u)
	bool SubLeft();
	// ��(�T�u)(�������u�Ԃ̔���)
	bool SubLeftTrigger();
	// ��(�T�u)(�������u�Ԃ̔���)
	bool SubLeftReturn();
	// �E(�T�u)
	bool SubRight();
	// �E(�T�u)(�������u�Ԃ̔���)
	bool SubRightTrigger();
	// �E(�T�u)(�������u�Ԃ̔���)
	bool SubRightReturn();
	// ����
	bool Decision();
	// ����(�������u�Ԃ̔���)
	bool DecisionTrigger();
	// ����(�������u�Ԃ̔���)
	bool DecisionReturn();
	// �L�����Z��
	bool Cancel();
	// �L�����Z��(�������u�Ԃ̔���)
	bool CancelTrigger();
	// �L�����Z��(�������u�Ԃ̔���)
	bool CancelReturn();
	// ���Z�b�g
	bool Reset();
	// ���Z�b�g(�������u�Ԃ̔���)
	bool ResetTrigger();
	// ���Z�b�g(�������u�Ԃ̔���)
	bool ResetReturn();
	// ���j���[
	bool Menu();
	// ���j���[(�������u�Ԃ̔���)
	bool MenuTrigger();
	// ���j���[(�������u�Ԃ̔���)
	bool MenuReturn();
	// �W�����v
	bool Jump();
	// �W�����v(�������u�Ԃ̔���)
	bool JumpTrigger();
	// �W�����v(�������u�Ԃ̔���)
	bool JumpReturn();

	//�܂鑀��̃g���K�[
	bool FoldLeftTrigger();
	bool FoldUpTrigger();
	bool FoldRightTrigger();
	bool FoldDownTrigger();

	//�J������̃g���K�[
	bool OpenLeftTrigger();
	bool OpenUpTrigger();
	bool OpenRightTrigger();
	bool OpenDownTrigger();
};
