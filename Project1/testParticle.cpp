#include "testParticle.h"
#include <NY_random.h>

void BomParticle::Init()
{
	//�J�n���W
	pos = spos;

	//�I���t���[���ݒ�
	endFrame = 60;

	//���x�ݒ�
	float xvel = NY_random::floatrand_sl(3.0f, -3.0f);
	float yvel = NY_random::floatrand_sl(3.0f, -3.0f);
	float zvel = NY_random::floatrand_sl(3.0f, -3.0f);

	vel = RVector3(xvel, yvel, zvel);
}

void BomParticle::Update()
{
	//���x�𖈃t���[�����Z
	pos += vel;
}

ParticlePrototype *BomParticle::clone(RVector3 startPos)
{
	return new BomParticle(startPos);
}
