#pragma once

#include <ParticleManager2D.h>
#include "Ori_StarParticle.h"
#include "OriParticle.h"

class OriEffects
{
public:
	OriEffects();
	~OriEffects();

	//��Ԃ̏�����
	void Init();

	//�G�t�F�N�g�Đ�
	void Play(float centerPosX,float centerPosY);

	void Update();

	void Draw();

	void Finalize();

private:
	//�G�~�b�^�[
	ParticleManager2D starParticle;
	ParticleManager2D oriParticle;
	//�e�N�X�`��
	UINT starGraph;
	UINT oriGraph;
	//�v���g�^�C�v
	Ori_StarParticle* starProto;
	OriParticle* oriProto;




};

