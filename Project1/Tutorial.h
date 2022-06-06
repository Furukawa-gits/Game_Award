#pragma once
#include "Sprite.h"
#include "RVector.h"
#include "Easing.h"

class Tutorial
{
public: //�T�u�N���X
	// �`���[�g���A���̏��
	enum TutorialState
	{
		NO_TUTORIAL,
		MOVE,  //�ړ��̃`���[�g���A��
		JUMP,  //�W�����v�̃`���[�g���A��
		FOLD,  //�܂�̃`���[�g���A��
		SELECT //�J�[�\���ړ��̃`���[�g���A��
	};
	enum TutorialType
	{
		NORMAL_TYPE, //���ʂ̃`���[�g���A��
		FOLD_TYPE,   //�܂�̃`���[�g���A��
		SELECT_TYPE  //�J�[�\���ړ��̃`���[�g���A��
	};

public: //�萔
	static const int backFrameWadth; //�w�i�̘g���̕�
	static const int frameWadth;     //�g���̕�
	static const XMFLOAT2 frameSize; //�g�̃T�C�Y
	
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
	// �`���[�g���A�����J�n����(�܂�)
	void StartFoldTutorial();
	// �`���[�g���A�����J�n����(�X�e�[�W�̑I��)
	void StartSelectTutorial();
	// �`���[�g���A�����X�L�b�v����
	void SkipTutorial(const TutorialType& tutorialType);

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
	// �����̕`��
	void CharacterDraw();

public: //�����o�ϐ�
	bool isFirstOnly;

private:
	bool isTutorial;
	TutorialState tutorialState;
	bool isFirst;
	TutorialType tutorialType;

	//�摜�n���h��
	Sprite frameSprite;
	Sprite moveSprite;
	Sprite moveFontSprite;
	Sprite jumpSprite;
	Sprite jumpFontSprite;
	Sprite foldSprite;
	Sprite foldFontSprite;
	Sprite selectSprite;
	Sprite selectFontSprite;

	XMFLOAT2 frameOffset;
	float drawScale;

	bool isEase;             //�C�[�W���O�����ǂ���
	TutorialState easeState; //�ǂ̃`���[�g���A���������Ă��邩
	float timeRate;
	RVector3 startPos; //�C�[�W���O�̊J�n�ʒu
	RVector3 endPos;   //�C�[�W���O�̏I���ʒu
	RVector3 easePos;  //�C�[�W���O���̍��W
};
