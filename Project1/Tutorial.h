#pragma once
#include "Sprite.h"

class Tutorial
{
public: //�T�u�N���X
	enum TutorialState
	{
		NO_TUTORIAL,
		MOVE,  //�ړ��̃`���[�g���A��
		JUMP,  //�W�����v�̃`���[�g���A��
		FOLD,  //�܂�̃`���[�g���A��
		SELECT //�J�[�\���ړ��̃`���[�g���A��
	};

public: //�����o�֐�
	Tutorial();
	~Tutorial();

	// ������
	void Init();
	// �X�V
	void Update();
	// �`��
	void Draw(int offsetX = 0, int offsetY = 0);
	// ����
	void Create();
	// ���Z�b�g
	void Reset();

	// �`���[�g���A�����J�n����
	void StartTutorial();
	// �`���[�g���A�������ǂ���
	inline bool GetTutorialFlag() { return isTutorial; }

public: //�����o�ϐ�
	bool isFirstOnly;

private:
	bool isTutorial;
	TutorialState tutorialState;
	bool isMoveTutorial;
	bool isJumpTutorial;
	bool isFoldTutorial;
	bool isFirst;

	//�摜�n���h��
	Sprite moveSprite;
	Sprite jumpSprite;
	Sprite foldSprite;
	Sprite selectSprite;

	XMFLOAT2 spriteSize;
};
