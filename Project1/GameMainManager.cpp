#include "GameMainManager.h"
#include "InputManger.h"
#include "Raki_DX12B.h"
#include "Stage.h"
#include "Player.h"

namespace
{
Stage* stage = Stage::Get();
Player* player = Player::Get();
}

GameMainManager::GameMainManager()
{
}

GameMainManager::~GameMainManager()
{
}

void GameMainManager::Init()
{
	BackHandle = TexManager::LoadTexture("Resources/background03.png");
	//BackHandle = TexManager::LoadTexture("Resources/backSin.png");
	this->Back.Create(BackHandle);

	menuBGM = Audio::LoadSound_wav("Resources/sound/BGM/bgm01.wav");
	playBGM = Audio::LoadSound_wav("Resource/sound/BGM/bgm02.wav");

	ui.Init(&tutorial);

	tutorial.Create();
}

void GameMainManager::Update()
{
	//�Q�[�����C���X�^���X�̍X�V�����i�悤�͉�������ĂȂ��N���X�̍X�V�����B��₱�����Ȃ邩�烉�b�v�����j
	GameInstanceUpdate();

	//�N���A�t���O����������J�ډ��o�A�Z���N�g�Ɉړ����鏈����������������

}

void GameMainManager::Draw()
{
	GameInstanceDraw();
}

void GameMainManager::Finalize()
{
}

void GameMainManager::GameInstanceUpdate()
{
	ui.Update(player->playerTile, &Ischangecount);

	ui.Update(playerTile, &Ischangecount, NowScene);

	if (IsStart == false)
	{
		stage->Reset(playerTile);
		player->Init();
		player->BodySetUp(playerTile);
		IsStart = true;
	}


	tutorial.Update();

	//�e�X�e�[�W�̏���
#ifdef _DEBUG
	if (Input::isKeyTrigger(DIK_1))
	{
		stage->LoadStage("./Resources/stage/test.csv", player->playerTile);
		stage->drawOffsetX = 200.0f;
		stage->drawOffsetY = 0.0f;
		player->Init();
		player->BodySetUp(player->playerTile);
	}

#endif // _DEBUG

	player->Update(stage->drawOffsetX, stage->drawOffsetY);
	bool PlayerBodyStatus[4] = {};

	player->SetBodyStatus(PlayerBodyStatus);

	bool IsFolds[4] = {
		player->IsLeftFold,
		player->IsUpFold,
		player->IsRightFold,
		player->IsDownFold,
	};

	bool IsOpens[4] = {
		player->IsLeftOpen,
		player->IsUpOpen,
		player->IsRightOpen,
		player->IsDownOpen,
	};

	if (player->leg.FootIsAction == false && player->Body_Three.IsFold == true)
	{
		int test = 0;
	}

	stage->Updata();
	stage->FoldAndOpen(player->CenterPosition, player->playerTile, PlayerBodyStatus, player->leg.FootIsAction, IsFolds, player->OpenCount, IsOpens);

	//�X�e�[�W�Ƃ̘A���̂��ߊJ�������͂������ł��
	if (player->OpenCount >= 2)
	{
		if (player->IsLeftOpen == true)
		{
			player->IsLeftOpen = false;
		}
		if (player->IsUpOpen == true)
		{
			player->IsUpOpen = false;
		}
		if (player->IsRightOpen == true)
		{
			player->IsRightOpen = false;
		}
		if (player->IsDownOpen == true)
		{
			player->IsDownOpen = false;
		}
		player->OpenCount = 0;
		player->IsOpenCountStart = false;
	}

	if (player->IsGoal && !Ischangecount)
	{
		Ischangecount = true;
		changecount = 0;
	}

	if (Ischangecount)
	{
		changecount++;

		if (changecount > 20)
		{
			IsGoSelect = true;
		}
	}
}

void GameMainManager::SetSelectToGame(int SelectStageNum)
{
	//�Q�[���V�[���Ɉڂ�Ƃ��̃Z�b�g�A�b�v
	Ischangecount = false;
	IsGoSelect = false;
	changecount = 0;
	IsStart = false;
	NowScene = SelectStageNum;

	if (NowScene == 0)
	{
		tutorial.StartTutorial();
	}
}

void GameMainManager::SetGameToSelect()
{
	//�Z���N�g�V�[���ɖ߂�Ƃ��̃Z�b�g�A�b�v
	Ischangecount = false;
	IsGoSelect = false;
	changecount = 0;

	tutorial.ResetTutorial();
}

void GameMainManager::GameInstanceDraw()
{
	//�e�X�e�[�W�̏���
	SpriteManager::Get()->SetCommonBeginDraw();
	Back.DrawExtendSprite(0, 0, 1280, 720);
	Back.Draw();
	Raki_DX12B::Get()->ClearDepthBuffer();
	ui.Draw();
	stage->Draw();
	player->Draw(stage->drawOffsetX, stage->drawOffsetY);
	tutorial.Draw(tutorialOffsetX, tutorialOffsetY);
}
