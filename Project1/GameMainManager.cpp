#include "GameMainManager.h"
#include "InputManger.h"
#include "Raki_DX12B.h"

GameMainManager::GameMainManager()
{
}

GameMainManager::~GameMainManager()
{
}

void GameMainManager::Init(Stage* stageptr, Player* playerptr)
{
	stage = stageptr;
	player = playerptr;

	BackHandle = TexManager::LoadTexture("Resources/background03.png");
	//BackHandle = TexManager::LoadTexture("Resources/backSin.png");
	this->Back.Create(BackHandle);
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
	//�e�X�e�[�W�̏���
//#ifdef _DEBUG
	if (Input::isKeyTrigger(DIK_1))
	{
		stage->LoadStage("./Resources/stage/stage1.csv", playerTile);
		player->Init();
		player->BodySetUp(playerTile);
	}
	if (Input::isKeyTrigger(DIK_2))
	{
		stage->LoadStage("./Resources/stage/stage2.csv", playerTile);
		player->Init();
		player->BodySetUp(playerTile);
	}
#ifdef _DEBUG
	if (Input::isKeyTrigger(DIK_3))
	{
		stage->LoadStage("./Resources/stage/stage3.csv", playerTile);
		player->Init();
		player->BodySetUp(playerTile);
	}

#endif // _DEBUG

	if (InputManger::ResetTrigger())
	{
		stage->Reset(playerTile);
		player->Init();
		player->BodySetUp(playerTile);
	}
	player->Update(*stage, drawOffsetX, drawOffsetY);
	bool PlayerBodyStatus[4] = {};

	player->SetBodyStatus(PlayerBodyStatus);

	bool IsFolds[4] = {
		player->IsLeftFold,
		player->IsUpFold,
		player->IsRightFold,
		player->IsDownFold
	};

	bool IsOpens[4] = {
		player->IsLeftOpen,
		player->IsUpOpen,
		player->IsRightOpen,
		player->IsDownOpen
	};

	stage->Updata();
	stage->FoldAndOpen(player->CenterPosition, playerTile, PlayerBodyStatus, player->leg.FootIsAction, IsFolds, player->OpenCount, IsOpens);

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
}

void GameMainManager::GameInstanceDraw()
{
	//�e�X�e�[�W�̏���
	SpriteManager::Get()->SetCommonBeginDraw();
	Back.DrawExtendSprite(0, 0, 1280, 720);
	Back.Draw();
	Raki_DX12B::Get()->ClearDepthBuffer();
	stage->Draw(drawOffsetX, drawOffsetY);
	player->Draw(drawOffsetX, drawOffsetY);
}
