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

	static bool isInversionX; //X�����]
	static bool isInversionY; //Y�����]
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
	bool EscapeRelease();
	// ��
	bool Up();
	// ��(�������u�Ԃ̔���)
	bool UpTrigger();
	// ��(�������u�Ԃ̔���)
	bool UpRelease();
	// ��
	bool Down();
	// ��(�������u�Ԃ̔���)
	bool DownTrigger();
	// ��(�������u�Ԃ̔���)
	bool DownRelease();
	// ��
	bool Left();
	// ��(�������u�Ԃ̔���)
	bool LeftTrigger();
	// ��(�������u�Ԃ̔���)
	bool LeftRelease();
	// �E
	bool Right();
	// �E(�������u�Ԃ̔���)
	bool RightTrigger();
	// �E(�������u�Ԃ̔���)
	bool RightRelease();
	// ��(�T�u)
	bool SubUp();
	// ��(�T�u)(�������u�Ԃ̔���)
	bool SubUpTrigger();
	// ��(�T�u)(�������u�Ԃ̔���)
	bool SubUpRelease();
	// ��(�T�u)
	bool SubDown();
	// ��(�T�u)(�������u�Ԃ̔���)
	bool SubDownTrigger();
	// ��(�T�u)(�������u�Ԃ̔���)
	bool SubDownRelease();
	// ��(�T�u)
	bool SubLeft();
	// ��(�T�u)(�������u�Ԃ̔���)
	bool SubLeftTrigger();
	// ��(�T�u)(�������u�Ԃ̔���)
	bool SubLeftRelease();
	// �E(�T�u)
	bool SubRight();
	// �E(�T�u)(�������u�Ԃ̔���)
	bool SubRightTrigger();
	// �E(�T�u)(�������u�Ԃ̔���)
	bool SubRightRelease();
	// ����
	bool Decision();
	// ����(�������u�Ԃ̔���)
	bool DecisionTrigger();
	// ����(�������u�Ԃ̔���)
	bool DecisionRelease();
	// �L�����Z��
	bool Cancel();
	// �L�����Z��(�������u�Ԃ̔���)
	bool CancelTrigger();
	// �L�����Z��(�������u�Ԃ̔���)
	bool CancelRelease();
	// ���Z�b�g
	bool Reset();
	// ���Z�b�g(�������u�Ԃ̔���)
	bool ResetTrigger();
	// ���Z�b�g(�������u�Ԃ̔���)
	bool ResetRelease();
	// ���j���[
	bool Menu();
	// ���j���[(�������u�Ԃ̔���)
	bool MenuTrigger();
	// ���j���[(�������u�Ԃ̔���)
	bool MenuRelease();
	// �W�����v
	bool Jump();
	// �W�����v(�������u�Ԃ̔���)
	bool JumpTrigger();
	// �W�����v(�������u�Ԃ̔���)
	bool JumpRelease();

	//�܂鑀��̃g���K�[
	bool FoldLeftTrigger();
	bool FoldUpTrigger();
	bool FoldRightTrigger();
	bool FoldDownTrigger();

	//�܂鑀��̃����[�X
	bool FoldLeftRelease();
	bool FoldUpRelease();
	bool FoldRightRelease();
	bool FoldDownRelease();

	//�J������̃g���K�[
	bool OpenLeftTrigger();
	bool OpenUpTrigger();
	bool OpenRightTrigger();
	bool OpenDownTrigger();

	//�J������̃����[�X
	bool OpenLeftRelease();
	bool OpenUpRelease();
	bool OpenRightRelease();
	bool OpenDownRelease();

	//�܂�J���̃Z���N�g
	bool FoldSelectTrigger();
};
