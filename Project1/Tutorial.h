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

public: //�萔
	static const int backFrameWadth; //�w�i�̘g���̕�
	
	static const XMFLOAT2 moveSpriteSize;   //�ړ��̃`���[�g���A���̉摜�T�C�Y
	static const XMFLOAT2 jumpSpriteSize;   //�W�����v�̃`���[�g���A���̉摜�T�C�Y
	static const XMFLOAT2 foldSpriteSize;   //�܂�J���̃`���[�g���A���̉摜�T�C�Y
	static const XMFLOAT2 selectSpriteSize; //�J�[�\���ړ��̃`���[�g���A���̉摜�T�C�Y

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
	void StartNormalTutorial();
	// �`���[�g���A�����J�n����
	void StartSelectTutorial();
	// �`���[�g���A�������ǂ���
	inline bool GetTutorialFlag() { return isTutorial; }
private:
	// �ړ��̃`���[�g���A��
	void MoveTutorial(const XMFLOAT2& offset, bool flag);
	// �W�����v�̃`���[�g���A��
	void JumpTutorial(const XMFLOAT2& offset, bool flag);
	// �܂�J���̃`���[�g���A��
	void FoldTutorial(const XMFLOAT2& offset, bool flag);
	// �J�[�\���ړ��̃`���[�g���A��
	void SelectTutorial(const XMFLOAT2& offset, bool flag);

public: //�����o�ϐ�
	bool isFirstOnly;

private:
	bool isTutorial;
	TutorialState tutorialState;
	bool isFirst;
	bool isNormal;
	bool isSelect;

	//�摜�n���h��
	Sprite frameSprite;
	Sprite moveSprite;
	Sprite jumpSprite;
	Sprite foldSprite;
	Sprite selectSprite;
};
