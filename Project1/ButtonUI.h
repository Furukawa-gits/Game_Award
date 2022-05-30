#pragma once

#include <Sprite.h>
#include <Audio.h>

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
	//�C�[�W���O�X�P�[�����O
	const float EASE_SCALE_X = 0.7f, EASE_SCALE_Y = 0.7f;
	const float EASE_SCALE_START_X = 1.0f;
	float easeScaleX = 1.0f, easeSceleY = 1.0f;

	static SoundData _ui_push_sound;

public:
	//���̃{�^���̓��[�U�[�ɂ���ĉ����ꂽ���H
	bool isUserPushed = false;
	//���̃{�^���������ꂽ���Ƃɂ���ċN���鏈����L���������邩�H
	bool isFunctionActivate = false;

	void Reset();
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

