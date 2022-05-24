#include "OriParticle.h"

#include <RVector.h>

OriParticle::OriParticle()
{
}

OriParticle::~OriParticle()
{
}

void OriParticle::Init()
{
	//�F
	color.w = 1.0f;

	e_color = { 1,1,1,0.1f };

	//�p�[�e�B�N���p�x
	rot = NY_random::floatrand_sl(360.0f, 0.0f);

	//���x�x�N�g���␳
	float power = NY_random::floatrand_sl(20.0f, 10.0f);
	vel.y = sinf((rot-90.0f) * (3.14 / 180.0f));
	vel.x = cosf((rot-90.0f) * (3.14 / 180.0f));
	vel.z = 0.0f;
	vel *= power;

	//�����x�x�N�g���ݒ�
	acc.x = vel.x / 40.0f;
	acc.y = vel.y / 40.0f;

	//�������W�𒆐S�����苗������
	pos += vel * 10.0f;

	scale = 1.0f;
	s_scale = 3.0f;
	e_scale = 3.0f;

	drawsize.x = 6.0f;
	drawsize.y = 18.0f;

	endFrame = 20;
}

void OriParticle::Update()
{
	pos += vel;
	vel -= acc;

	float rate = static_cast<float>(nowFrame) / static_cast<float>(endFrame);
	scale = s_scale + (e_scale - s_scale) * rate;
	color = s_color + (e_color - s_color) * rate;
}

ParticlePrototype2D* OriParticle::clone()
{
	OriParticle* p = new OriParticle;
	//���W���N���[�����p�[�e�B�N���̍��W�ɍ��킹��
	p->pos = this->pos;
	return p;
}
