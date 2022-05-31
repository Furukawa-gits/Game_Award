#pragma once
#include "Easing.h"
#include "Sprite.h"
#include<RVector.h>

class PlayerBody;

class PlayerFoot
{
public: //�����o�֐�
	PlayerFoot();
	~PlayerFoot();

	void Init();
	void Set();
	void Update(RVector3& DownPos, bool IsDownBody, int BodyDis);
	void Draw(int offsetX, int offsetY, bool isleft, bool isright);
	void Create();

public: //�����o�ϐ�
	RVector3 FootLeftUpPosition;
	Easing ease;

	bool FootIsAction;
	bool IsFootUp;

	bool IsWalkAnimation = false;
	size_t WalkAnimationCount = 0;

	size_t animationCount = 0;

	//�摜�n���h��
	UINT FootHandle;
	Sprite FootSprite;

	Sprite FootAnimation;
};