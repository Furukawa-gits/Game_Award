#pragma once
#include "Sprite.h"

class Tutorial
{
public: //�����o�֐�
	Tutorial();
	~Tutorial();

	// �X�V
	void Update();
	// �`��
	void Draw(int offsetX = 0, int offsetY = 0);
	// ����
	void Create();

	// �`���[�g���A�����J�n����
	void StartTutorial();
	// �`���[�g���A�������ǂ���
	inline bool GetTutorialFlag() { return isTutorial; }

public: //�����o�ϐ�
	bool isFirstOnly;
private:
	//�摜�n���h��
	UINT moveHandle;
	UINT foldHandle;

	Sprite moveSprite;
	Sprite foldSprite;

	bool isTutorial;
	bool isMoveTutorial;
	bool isFoldTutorial;
	bool isFirst;
};
