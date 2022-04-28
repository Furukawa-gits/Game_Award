#pragma once
#include "Raki_Input.h"

// ���͂��܂Ƃ߂��N���X
class InputManger final
{
private: //�V���O���g����
	InputManger() {}
	InputManger(const InputManger&) = delete;
	~InputManger() {}
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

	// �I��
	static bool Escape();
	// �I��(�������u�Ԃ̔���)
	static bool EscapeTrigger();
	// �I��(�������u�Ԃ̔���)
	static bool EscapeReturn();
	// ��
	static bool Up();
	// ��(�������u�Ԃ̔���)
	static bool UpTrigger();
	// ��(�������u�Ԃ̔���)
	static bool UpReturn();
	// ��
	static bool Down();
	// ��(�������u�Ԃ̔���)
	static bool DownTrigger();
	// ��(�������u�Ԃ̔���)
	static bool DownReturn();
	// ��
	static bool Left();
	// ��(�������u�Ԃ̔���)
	static bool LeftTrigger();
	// ��(�������u�Ԃ̔���)
	static bool LeftReturn();
	// �E
	static bool Right();
	// �E(�������u�Ԃ̔���)
	static bool RightTrigger();
	// �E(�������u�Ԃ̔���)
	static bool RightReturn();
	// ��(�T�u)
	static bool SubUp();
	// ��(�T�u)(�������u�Ԃ̔���)
	static bool SubUpTrigger();
	// ��(�T�u)(�������u�Ԃ̔���)
	static bool SubUpReturn();
	// ��(�T�u)
	static bool SubDown();
	// ��(�T�u)(�������u�Ԃ̔���)
	static bool SubDownTrigger();
	// ��(�T�u)(�������u�Ԃ̔���)
	static bool SubDownReturn();
	// ��(�T�u)
	static bool SubLeft();
	// ��(�T�u)(�������u�Ԃ̔���)
	static bool SubLeftTrigger();
	// ��(�T�u)(�������u�Ԃ̔���)
	static bool SubLeftReturn();
	// �E(�T�u)
	static bool SubRight();
	// �E(�T�u)(�������u�Ԃ̔���)
	static bool SubRightTrigger();
	// �E(�T�u)(�������u�Ԃ̔���)
	static bool SubRightReturn();
	// ����
	static bool Decision();
	// ����(�������u�Ԃ̔���)
	static bool DecisionTrigger();
	// ����(�������u�Ԃ̔���)
	static bool DecisionReturn();
	// �L�����Z��
	static bool Cancel();
	// �L�����Z��(�������u�Ԃ̔���)
	static bool CancelTrigger();
	// �L�����Z��(�������u�Ԃ̔���)
	static bool CancelReturn();
	/*�ȉ��L�[�{�[�h�I�����[*/
	// ���Z�b�g
	static bool Reset();
	// ���Z�b�g(�������u�Ԃ̔���)
	static bool ResetTrigger();
	// ���Z�b�g(�������u�Ԃ̔���)
	static bool ResetReturn();
};
