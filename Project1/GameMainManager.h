#pragma once

#include "Stage.h"
#include "Player.h"

class GameMainManager
{
private:
	Stage* stage;
	Player* player;

	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	UINT BackHandle;
	Sprite Back;
	unsigned char playerTile[4] = { 0 };
	const int drawOffsetX = 320, drawOffsetY = 45;

public:
	GameMainManager();
	~GameMainManager();

	void Init(Stage* stageptr, Player* playerptr);
	void Update();
	void Draw();
	void Finalize();

private:
	void GameInstanceUpdate();
	void GameInstanceDraw();

};

