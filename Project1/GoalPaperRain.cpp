#include "GoalPaperRain.h"

#include <NY_random.h>

void GoalPaperRain::Init()
{
	//��ʏ�̃����_���Ȉʒu�ɐݒ�
	pos.x = NY_random::floatrand_sl(1280, 0);
	//y�͉�ʊO
	pos.y = NY_random::floatrand_sl(0, -50);

	//x���ǂ̂����肩��o���������ɂ���đ��x�x�N�g����ݒ肷�鏈��

	float spawnPosRate = pos.x / 1280.0f; //�ǂ̂����肩�������ŎZ�o
	float veldig = 180.0f * spawnPosRate; //�ォ��i���p�x�����߂�

	vel.x = cosf(veldig - 90.0f * 3.14f / 180.0f);
	vel.y = sinf(veldig - 90.0f * 3.14f / 180.0f);
	vel.z = 0.0f;

	//���x�␳
	float power = NY_random::floatrand_sl(5.0f, 1.0f);
	vel *= power;

	//�`��T�C�Y�ݒ�
	drawsize.x = 8.0f;
	drawsize.y = 16.0f;

	//��]���x
	radacc = NY_random::floatrand_sl(6.0f, -6.0f);

	//�F
	color = { NY_random::floatrand_sl(1.0f, 0.0f) ,NY_random::floatrand_sl(1.0f, 0.0f) ,NY_random::floatrand_sl(1.0f, 0.0f) ,1.0f };

	endFrame = 180.0f;
}

void GoalPaperRain::Update()
{
	//���W
	pos += vel;
	//��]�p
	rot += radacc;
}

ParticlePrototype2D* GoalPaperRain::clone()
{
	GoalPaperRain* p = new GoalPaperRain;
	return p;
}
