#pragma once

#include "UI.h"
#include "Raki_imguiMgr.h"

class GameMainManager
{
private:
	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	UINT BackHandle;
	Sprite Back;
	unsigned char playerTile[4] = { 0 };
	const int drawOffsetX = 320, drawOffsetY = 45;

	UI ui;

public:
	GameMainManager();
	~GameMainManager();

	void Init();
	void Update();
	void Draw();
	void Finalize();

private:
	void GameInstanceUpdate();
	void GameInstanceDraw();

};

