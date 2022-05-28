#pragma once

#include <Sprite.h>

//�{�^���N���X�i���쎩�͓̂����ŁA�O���t�B�b�N��T�C�Y�Ȃǂ������ւ��邱�ƂŎg���񂷁j
class UI_Button
{
private:
	//�{�^���̕`��T�C�Y
	float width = 0.0f, height = 0.0f;
	//�X�v���C�g
	Sprite uiSprite;
	//���[�U�[�������Ă��珈����L��������܂ł̃��O(frame��)
	int activateTimerag = 0;
	//�t���[���J�E���g
	int count = 0;

public:
	//���̃{�^���̓��[�U�[�ɂ���ĉ����ꂽ���H
	bool isUserPushed = false;
	//���̃{�^���������ꂽ���Ƃɂ���ċN���鏈����L���������邩�H
	bool isFunctionActivate = false;


	//������
	void Init(int activateTimerag, UINT graphHandle, float baseWidth, float baseHeight);
	//�X�V
	void Update();
	//�`��
	void Draw(float centerX, float centerY, float x_scale = 1.0f, float y_scale = 1.0f);

	//�I���i���邩�H�j
	void Finalize() {}

	//����
	void UI_Push();

};

