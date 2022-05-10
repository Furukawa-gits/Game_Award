#include "GameScene.h"
#include "Raki_imguiMgr.h"
#include "TexManager.h"

#include "InputManger.h"
#include "NY_random.h"

GameScene::GameScene(ISceneChanger *changer) : BaseScene(changer) {
	camera->SetViewStatusEyeTargetUp(eye, target, up);

	stage->Create();
	stage->LoadStage("./Resources/stage/test.csv", playerTile);
	player->Init();
	player->BodySetUp(playerTile);

	nowState = is_Select;

	selecter.Init();
	gamemain.Init();
}

//������
void GameScene::Initialize() {

}

//�X�V
void GameScene::Update() {
	camera->SetViewStatusEyeTargetUp(eye, target, up);


	switch (nowState)
	{
	case GameScene::is_Select:
		//�X�e�[�W�Z���N�g��ʂ̏���
		selecter.Update();
		if (selecter.GetMoveGameMain()) {
			nowState = is_Game; 
		}

		break;


	case GameScene::is_Game:
		//�Q�[���{�҂̏���
		gamemain.Update();

		break;
	default:
		break;
	}
}

//�`��
void GameScene::Draw() {

	//�w�i�ɏ�ɂ���
	Raki_DX12B::Get()->StartDrawRenderTarget();

	Raki_DX12B::Get()->StartDrawBackbuffer();

	switch (nowState)
	{
	case GameScene::is_Select:
		//�X�e�[�W�Z���N�g��ʂ̏���
		selecter.Draw();

		break;
	case GameScene::is_Game:
		gamemain.Draw();

		break;
	default:
		break;
	}

	//�`��I��
	Raki_DX12B::Get()->CloseDraw();
}