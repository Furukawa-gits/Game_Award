#include "Title.h"
#include "Raki_imguiMgr.h"
#include "TexManager.h"

#include "InputManger.h"
#include "NY_random.h"

using namespace myImgui;

Title::Title(ISceneChanger* changer) : BaseScene(changer) {


	camera->SetViewStatusEyeTargetUp(eye, target, up);

	stage->Create();
	stage->LoadStage("./Resources/stage/test.csv", playerTile);
	player->Init();
	player->BodySetUp(playerTile);

	BackHandle = TexManager::LoadTexture("Resources/background03.png");
	//BackHandle = TexManager::LoadTexture("Resources/backSin.png");
	this->Back.Create(BackHandle);
}

//������
void Title::Initialize() {
	/// <summary>
	/// �t�B�[���h�Ǘ���������
	/// </summary>

	//StageMoveParticle::Get()->Init(&cam);
}

void Title::Finalize()
{

}

//�X�V
void Title::Update() {
	camera->SetViewStatusEyeTargetUp(eye, target, up);

	//#ifdef _DEBUG
	if (Input::isKeyTrigger(DIK_1))
	{
		stage->LoadStage("./Resources/stage/stage1.csv", playerTile);
		player->Init();
		player->BodySetUp(playerTile);
	}
	if (Input::isKeyTrigger(DIK_2))
	{
		stage->LoadStage("./Resources/stage/stage5.csv", playerTile);
		player->Init();
		player->BodySetUp(playerTile);
	}
#ifdef _DEBUG
	if (Input::isKeyTrigger(DIK_3))
	{
		stage->LoadStage("./Resources/stage/stage6.csv", playerTile);
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
		player->IsUpFold,
		player->IsDownFold,
		player->IsLeftFold,
		player->IsRightFold };

	bool IsOpens[4] = {
		player->IsUpOpen,
		player->IsDownOpen,
		player->IsLeftOpen,
		player->IsRightOpen,
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

//�`��
void Title::Draw() {

	//�w�i�ɏ�ɂ���
	Raki_DX12B::Get()->StartDrawRenderTarget();

	Raki_DX12B::Get()->StartDrawBackbuffer();

	// �`�揈��
	//DrawGraph(0, 0, Back, true);
	//DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), true);
	SpriteManager::Get()->SetCommonBeginDraw();
	Back.DrawExtendSprite(0, 0, 1280, 720);
	Back.Draw();
	Raki_DX12B::Get()->ClearDepthBuffer();
	stage->Draw(drawOffsetX, drawOffsetY);
	player->Draw(drawOffsetX, drawOffsetY);

	//�`��I��
	Raki_DX12B::Get()->CloseDraw();

}
