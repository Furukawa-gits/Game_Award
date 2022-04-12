#include "Title.h"
#include "Raki_imguiMgr.h"
#include "TexManager.h"

#include "NY_random.h"

using namespace myImgui;

Title::Title(ISceneChanger* changer) : BaseScene(changer) {


	camera->SetViewStatusEyeTargetUp(eye, target, up);

	stage->LoadStage("./Resources/stage1.csv", playerTile);
	player->Init();
	player->bodysetup(false, BodyType::left, true, BodyType::up, true, BodyType::right, false, BodyType::down);

	BackHandle = TexManager::LoadTexture("Resources/backSin.png");
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

	if (Input::isKeyTrigger(DIK_LEFT) || Input::isKeyTrigger(DIK_UP) || Input::isKeyTrigger(DIK_RIGHT) || Input::isKeyTrigger(DIK_DOWN))
	{
		stage->FoldAndOpen(player->CenterPosition, playerTile);
	}

	stage->Updata();
	player->Update(*stage);
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
	stage->Draw(drawOffsetX, drawOffsetY);
	player->Draw(drawOffsetX, drawOffsetY);

	//�`��I��
	Raki_DX12B::Get()->CloseDraw();

}
