#pragma once
#include "RVector.h"
#include "ParticleManager.h"
#include "Sprite.h"

class GoalParticle
{
public: //�T�u�N���X
	class ParticleClass : public ParticlePrototype
	{
	public:
		//�J�n�ʒu�ۑ��p
		RVector3 spos;

		ParticleClass();
		~ParticleClass();

		void Init();
		void Update();
		ParticlePrototype* clone(RVector3 start);
	};

public: //�����o�֐�
	GoalParticle();
	~GoalParticle();

	void Init(ParticleGrainState* pgState, const float spawnRange, const size_t& spawnCount);
	void Init(const RVector3& pos, const float spawnRange, const size_t& spawnCount,
		const RVector3& vel, const RVector3& accel, const int aliveTime = 60, const XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f }, const float scale = 1.0f);
	void Create();
	void Update();
	void Draw();

private: //�����o�ϐ�
	ParticleManager* particleManager;

	UINT particleHandle;
	Sprite particleSprite;
};
