#include "BackGroundGraphic.h"

#include <NY_random.h>

UINT BackGroundGraphic::backGraph		= -1;
UINT BackGroundGraphic::birdGraph		= -1;
std::array<UINT, 3> BackGroundGraphic::cloudGraph = { -1,-1,-1 };

void CloudProto::Init()
{
	//���W�ݒ�
	pos.x = NY_random::intrand_sl(1280, 1280 / 2);
	pos.y = NY_random::intrand_sl(720 / 5, 720 / 20);
	//�J�n�A���t�@�ݒ�
	s_color = DirectX::XMFLOAT4(0.8, 0.8, 0.8, 0);
	e_color = DirectX::XMFLOAT4(0.8, 0.8, 0.8, 1);
	//�����ݒ�
	endFrame = NY_random::intrand_sl(1200, 600);
	//�������x�N�g���ݒ�
	vel.x = NY_random::floatrand_sl(1.0f, 0.1f);
	drawsize.x = 90;
	drawsize.y = 30;
}

void CloudProto::Update()
{
	pos -= vel;

	if (nowFrame < endFrame / 2) {
		//���[�g
		float rate = static_cast<float>(nowFrame) / static_cast<float>(endFrame / 2);
		//�F�ϊ�
		color = s_color + (e_color - s_color) * rate;
	}
	else {
		//���[�g
		float rate = static_cast<float>(nowFrame - (endFrame / 2)) / static_cast<float>(endFrame / 2);
		//�F�ϊ�
		color = e_color + (s_color - e_color) * rate;
	}

}

ParticlePrototype2D* CloudProto::clone()
{
	CloudProto* p = new CloudProto;
	//�����_���ʒu����
	return p;
}

BackGroundGraphic::BackGroundGraphic()
{
	std::string path = "Resources/backGraph/";

	if (backGraph == -1) {
		std::string fullpath = path + "background/backGround01.png";
		backGraph = TexManager::LoadTexture(fullpath);
	}
	if (birdGraph == -1) {
		std::string fullpath = path + "bird/bird.png";
		birdGraph = TexManager::LoadTexture(fullpath);
	}
	for (int i = 0; i < 3;i++) {
		if (cloudGraph[i] == -1) {
			std::string fullpath = path + "cloud/cloud0";
			fullpath += std::to_string(i + 1);
			fullpath += ".png";

			cloudGraph[i] = TexManager::LoadTexture(fullpath);
		}
	}
	//�w�i
	backGroundSprite.Create(backGraph);
	//��
	birdSprite.CreateAndSetDivisionUVOffsets(7, 7, 1, 18, 18, birdGraph);
	//�_
	CloudProto* p1 = new CloudProto;
	CloudProto* p2 = new CloudProto;
	CloudProto* p3 = new CloudProto;
	int num = 0;
	//�p�[�e�B�N���v���g�^�C�v������
	for (auto& p : cloudParticle) {
		p.Initialize(cloudGraph[num]);
		num++;
	}
	cloudParticle[0].Prototype_Set(p1);
	cloudParticle[1].Prototype_Set(p2);
	cloudParticle[2].Prototype_Set(p3);
}

BackGroundGraphic::~BackGroundGraphic()
{

}

void BackGroundGraphic::Init()
{
	frame = 0;
}

void BackGroundGraphic::Update()
{
	frame++;
	//�_�������_������
	if (frame % CLOUD_SPAWNFRAME_03 == 0) {
		cloudParticle[2].Prototype_Add();
		frame = 0;
	}
	else if (frame % CLOUD_SPAWNFRAME_02 == 0) {
		cloudParticle[1].Prototype_Add();
	}
	else if (frame % CLOUD_SPAWNFRAME_01 == 0) {
		cloudParticle[0].Prototype_Add();
	}
}

void BackGroundGraphic::Draw()
{
	//�w�i�`��
	backGroundSprite.DrawSprite(0, 0);
	backGroundSprite.Draw();

	//�_�`��
	for (auto& cloud : cloudParticle) {
		cloud.Prototype_Update();
		cloud.Prototype_Draw();
	}
}
