#pragma once

class Tutorial
{
public: //�����o�֐�
	Tutorial();
	~Tutorial();

	void Update();

	// �`���[�g���A�����J�n����
	void StartTutorial();
	// �`���[�g���A�������ǂ���
	inline bool GetTutorialFlag() { return isTutorial; }

private: //�����o�ϐ�
	bool isTutorial;
	bool isMoveTutorial;
	bool isFoldTutorial;
};
