#pragma once
#include "GoalPaperRain.h"
#include "GoalCracker.h"

class GoalEffects
{
public:
	GoalEffects();
	~GoalEffects();

	void Init();

	void Play();

	void Stop();

	void Update();

	void Draw();

private:
	//�v���g�^�C�v
	GoalPaperRain* rainProto;
	//�p�[�e�B�N��
	ParticleManager2D rainParticle;
	//�e�N�X�`��
	UINT prainGraph;

	enum NowEffectState
	{
		EFFECT_STANDBY,
		EFFECT_PLAYING,
	};
	NowEffectState state = EFFECT_STANDBY;

};

