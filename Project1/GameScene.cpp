#include "GameScene.h"
#include "Raki_imguiMgr.h"
#include "TexManager.h"

#include "InputManger.h"
#include "NY_random.h"

GameScene::GameScene(ISceneChanger* changer) : BaseScene(changer)
{
	camera->SetViewStatusEyeTargetUp(eye, target, up);

	stage->Create();
	stage->LoadStage("./Resources/stage/stage1.csv", player->playerTile);
	player->Init();
	player->BodySetUp(player->playerTile);

	nowState = is_Select;

	selecter.reset(new StageSelecter);
	selecter->Init();
	gamemain.reset(new GameMainManager);
	gamemain->selecterPtr = selecter.get();
	gamemain->Init();

}

//������
void GameScene::Initialize()
{

}

//�X�V
void GameScene::Update()
{
	camera->SetViewStatusEyeTargetUp(eye, target, up);

	switch (nowState)
	{
	case GameScene::is_Select:
		//�X�e�[�W�Z���N�g��ʂ̏���
		selecter->Update();
		if (selecter->GetMoveGameMain())
		{
			gamemain->SetSelectToGame(selecter->SelectStageNum);
			selecter->isChanging_GameMain = false;
			nowState = is_Game;
			InputManger::isMenu = true;
		}

		break;


	case GameScene::is_Game:
		//�Q�[���{�҂̏���
		gamemain->Update();
		if (gamemain->IsGoSelect == true)
		{
			gamemain->SetGameToSelect();
			selecter->isChanging_GameMain = false;
			selecter->state = selecter->is_selecting;
			nowState = is_Select;
			InputManger::isMenu = false;
		}

		break;
	default:
		break;
	}
}

//�`��
void GameScene::Draw()
{

	switch (nowState)
	{
	case GameScene::is_Select:
		//�X�e�[�W�Z���N�g��ʂ̏���
		selecter->Draw();

		break;
	case GameScene::is_Game:
		gamemain->Draw();

		break;
	default:
		break;
	}

}