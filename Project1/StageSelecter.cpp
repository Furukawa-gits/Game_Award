#include "StageSelecter.h"
#include <string>

#include <Raki_imguiMgr.h>

#include "Stage.h"
#include "Player.h"

namespace
{
Stage* stagePtr = Stage::Get();
Player* playerPtr = Player::Get();
}

StageSelecter::StageSelecter()
{

}

StageSelecter::~StageSelecter()
{
}

void StageSelecter::Init()
{
	//���\�[�X�ǂݍ���
	LoadSprite();
	menuBGM = Audio::LoadSound_wav("Resources/sound/BGM/bgm01.wav");

	//�ŏ��̃y�[�W
	nowpage = page_1_4;
	nextpage = nowpage;

	nowDisplayNum = 0;
}

void StageSelecter::Update()
{
	//�X�e�[�W�I���̓��͂����m
	CheckToStageChangeInput();
	//�X�e�[�W�I���̃y�[�W��؂�ւ�����͂����m
	CheckToPageChangeInput();
	//�y�[�W�ɉ��������o����
	PageChange();


}

void StageSelecter::Draw()
{
	switch (displayPage)
	{
	case StageSelecter::page_1_4:
		selectImg_1_4[nowDisplayNum].DrawSprite(0, 0);
		selectImg_1_4[nowDisplayNum].Draw();
		break;
	case StageSelecter::page_5_8:
		selectImg_5_8[nowDisplayNum].DrawSprite(0, 0);
		selectImg_5_8[nowDisplayNum].Draw();
		break;
	case StageSelecter::page_9_12:
		selectImg_9_12[nowDisplayNum].DrawSprite(0, 0);
		selectImg_9_12[nowDisplayNum].Draw();
		break;
	default:
		break;
	}

	/*ImguiMgr::Get()->StartDrawImgui("mouse", 150, 100);
	ImGui::Text("pos x : %f    y : %f", Input::getMousePos().x, Input::getMousePos().y);
	ImguiMgr::Get()->EndDrawImgui();*/



}

void StageSelecter::Finalize()
{
	Audio::StopLoadedSound(menuBGM);
}

void StageSelecter::PlayAudio()
{
	//�Đ�
	Audio::PlayLoadedSound(menuBGM);
}

void StageSelecter::LoadSprite()
{
	std::string fullImgPath = "Resources/selectAnime/";
	std::string filename = ".png";

	std::string page_1_4 = "1-4/";
	std::string page_5_8 = "5-8/";
	std::string page_9_12 = "9-12/";

	std::string imageName_1_4 = "select1-4 ";
	std::string imageName_5_8 = "select5-8 ";
	std::string imageName_9_12 = "select9-12 ";

	for (int i = 0; i < 20; i++)
	{
		std::string number = std::to_string(i + 1);
		std::string fullnumber = "(" + number + ")";

		std::string fullpath_1_4 = fullImgPath + page_1_4 + imageName_1_4 + fullnumber + filename;
		std::string fullpath_5_8 = fullImgPath + page_5_8 + imageName_5_8 + fullnumber + filename;
		std::string fullpath_9_12 = fullImgPath + page_9_12 + imageName_9_12 + fullnumber + filename;

		selectImg_1_4[i].Create(TexManager::LoadTexture(fullpath_1_4));
		selectImg_5_8[i].Create(TexManager::LoadTexture(fullpath_5_8));
		selectImg_9_12[i].Create(TexManager::LoadTexture(fullpath_9_12));
	}
}

void StageSelecter::CheckToPageChangeInput()
{
	//�X�e�[�W�I�𒆂łȂ��Ȃ珈�����Ȃ�
	if (state != is_selecting)
	{
		return;
	}

	float mouse_x = Input::getMousePos().x;
	float mouse_y = Input::getMousePos().y;

	if (state == is_selecting)
	{
		//�y�[�W�J�ڂ���̂��H
		bool isMove = false;
		if (mouse_x > static_cast<float>(1280 / 2) && Input::isMouseClickTrigger(MOUSE_L))
		{
			switch (nowpage)
			{
			case StageSelecter::page_1_4:
				nextpage = page_5_8;
				isMove = true;
				break;
			case StageSelecter::page_5_8:
				nextpage = page_9_12;
				isMove = true;
				break;
			case StageSelecter::page_9_12:
				break;
			default:
				break;
			}
			if (isMove) { pageMoveDir = is_front; }

		}
		else if (mouse_x < static_cast<float>(1280 / 2) && Input::isMouseClickTrigger(MOUSE_L))
		{
			switch (nowpage)
			{
			case StageSelecter::page_1_4:
				break;
			case StageSelecter::page_5_8:
				nextpage = page_1_4;
				isMove = true;
				break;
			case StageSelecter::page_9_12:
				nextpage = page_5_8;
				isMove = true;
				break;
			default:
				break;
			}
			if (isMove) { pageMoveDir = is_back; }
		}
	}

}

void StageSelecter::PageChange()
{
	//�y�[�W�؂�ւ����o�̏���

	//�y�[�W���ς��Ƃ�
	if (nowpage != nextpage)
	{
		animationFrame++;
		//���̃y�[�W
		if (pageMoveDir == is_front)
		{
			//���o���͌��݃y�[�W��\��
			displayPage = nowpage;
			//���o�ҋ@
			state = is_pageChange_waiting;
			if (animationFrame % perFrame == 0)
			{
				nowDisplayNum++;
			}
			if (nowDisplayNum >= 20)
			{
				//�`�悷����؂�ւ�
				displayPage = nextpage;
				//���݃y�[�W��ݒ�
				nowpage = nextpage;
				//������
				nowDisplayNum = 0;
				//���͂���t
				state = is_selecting;

				animationFrame = 0;
			}
		}
		//�O�̃y�[�W
		else
		{
			//�y�[�W�J�ڔ���ɂ���^�C�~���O�ŉ�����������
			if (state != is_pageChange_waiting)
			{
				state = is_pageChange_waiting;
				nowDisplayNum = 19;
				displayPage = nextpage;
			}
			//�A�j���[�V�����i�s
			if (animationFrame % perFrame == 0)
			{
				nowDisplayNum--;
			}
			//���o�I��
			if (nowDisplayNum <= 0)
			{
				nowDisplayNum = 0;
				state = is_selecting;
				nowpage = nextpage;
				animationFrame = 0;
			}
		}
	}
}

void StageSelecter::CheckLoadStage(int boxnum)
{
	switch (nowpage)
	{
	case StageSelecter::page_1_4:
		if (boxnum == 0)
		{
			stagePtr->LoadStage("./Resources/stage/stage1.csv", playerPtr->playerTile);
			stagePtr->drawOffsetX = 0.0f;
			stagePtr->drawOffsetY = 0.0f;
			playerPtr->Init();
			playerPtr->BodySetUp(playerPtr->playerTile);
		}
		else if (boxnum == 1)
		{
			stagePtr->LoadStage("./Resources/stage/stage2.csv", playerPtr->playerTile);
			stagePtr->drawOffsetX = 500.0f;
			stagePtr->drawOffsetY = 75.0f;
			playerPtr->Init();
			playerPtr->BodySetUp(playerPtr->playerTile);
		}
		else if (boxnum == 2)
		{
			stagePtr->LoadStage("./Resources/stage/stage3.csv", playerPtr->playerTile);
			stagePtr->drawOffsetX = 0.0f;
			stagePtr->drawOffsetY = 0.0f;
			playerPtr->Init();
			playerPtr->BodySetUp(playerPtr->playerTile);
		}
		else
		{
			stagePtr->LoadStage("./Resources/stage/stage4.csv", playerPtr->playerTile);
			stagePtr->drawOffsetX = 0.0f;
			stagePtr->drawOffsetY = 0.0f;
			playerPtr->Init();
			playerPtr->BodySetUp(playerPtr->playerTile);
		}
		break;



	case StageSelecter::page_5_8:
		if (boxnum == 0)
		{
			stagePtr->LoadStage("./Resources/stage/stage5.csv", playerPtr->playerTile);
			stagePtr->drawOffsetX = 0.0f;
			stagePtr->drawOffsetY = 0.0f;
			playerPtr->Init();
			playerPtr->BodySetUp(playerPtr->playerTile);
		}
		else if (boxnum == 1)
		{
			stagePtr->LoadStage("./Resources/stage/stage6.csv", playerPtr->playerTile);
			stagePtr->drawOffsetX = 0.0f;
			stagePtr->drawOffsetY = 0.0f;
			playerPtr->Init();
			playerPtr->BodySetUp(playerPtr->playerTile);
		}
		else if (boxnum == 2)
		{
			stagePtr->LoadStage("./Resources/stage/stage7.csv", playerPtr->playerTile);
			stagePtr->drawOffsetX = 0.0f;
			stagePtr->drawOffsetY = 0.0f;
			playerPtr->Init();
			playerPtr->BodySetUp(playerPtr->playerTile);
		}
		else
		{
			stagePtr->LoadStage("./Resources/stage/stage8.csv", playerPtr->playerTile);
			stagePtr->drawOffsetX = 0.0f;
			stagePtr->drawOffsetY = 0.0f;
			playerPtr->Init();
			playerPtr->BodySetUp(playerPtr->playerTile);
		}
		break;



	case StageSelecter::page_9_12:
		if (boxnum == 0)
		{
			stagePtr->LoadStage("./Resources/stage/stage9.csv", playerPtr->playerTile);
			stagePtr->drawOffsetX = 0.0f;
			stagePtr->drawOffsetY = 0.0f;
			playerPtr->Init();
			playerPtr->BodySetUp(playerPtr->playerTile);
		}
		else if (boxnum == 1)
		{
			stagePtr->LoadStage("./Resources/stage/stage10.csv", playerPtr->playerTile);
			stagePtr->drawOffsetX = 0.0f;
			stagePtr->drawOffsetY = 0.0f;
			playerPtr->Init();
			playerPtr->BodySetUp(playerPtr->playerTile);
		}
		else if (boxnum == 2)
		{
			stagePtr->LoadStage("./Resources/stage/stage11.csv", playerPtr->playerTile);
			stagePtr->drawOffsetX = 0.0f;
			stagePtr->drawOffsetY = 0.0f;
			playerPtr->Init();
			playerPtr->BodySetUp(playerPtr->playerTile);
		}
		else
		{
			stagePtr->LoadStage("./Resources/stage/stage12.csv", playerPtr->playerTile);
			stagePtr->drawOffsetX = 0.0f;
			stagePtr->drawOffsetY = 0.0f;
			playerPtr->Init();
			playerPtr->BodySetUp(playerPtr->playerTile);
		}
		break;


	default:
		break;
	}

}

void StageSelecter::CheckToStageChangeInput()
{
	//�I�𒆈ȊO�͂����������s���Ȃ�
	if (state != is_selecting)
	{
		return;
	}

	//�e�{�b�N�X�̍������W���v�Z
	std::array<int, 4> boxLeft;
	for (int i = 0; i < 4; i++)
	{
		boxLeft[i] = NUMBOX_START_X + (NUMBOX_SIZE * i) + (NUMBOX_SPACE * i);
	}

	int selectingBoxNum = 0;
	bool isHit = false;
	//�N���b�N���ɂǂ̃{�b�N�X���N���b�N���Ă��邩���߂�
	if (Input::isMouseClickTrigger(MOUSE_L) == true)
	{
		int mouse_x = static_cast<int>(Input::getMousePos().x);
		int mouse_y = static_cast<int>(Input::getMousePos().y);

		//�X�e�[�W�Ƀq�b�g���Ă���
		for (int i = 0; i < 4; i++)
		{
			if (mouse_x > boxLeft[i] && mouse_x < boxLeft[i] + NUMBOX_SIZE && mouse_y > NUMBOX_START_Y && mouse_y < NUMBOX_START_Y + NUMBOX_SIZE)
			{
				selectingBoxNum = i;
				//�Q�[���{�҂ւ̑J�ڂ�����
				isChanging_GameMain = true;
				//�q�b�g
				isHit = true;
				//�X�e�[�W�J�ڊJ�n
				state = is_stageSelected_waiting;
				break;
			}
		}
		//����q�b�g���Ă��Ȃ��ꍇ�͏I��
		if (!isHit) { return; }
	}
	else
	{//���͂��Ȃ��Ȃ�I��
		return;
	}

	//�N���b�N����Ă���{�b�N�X�ƁA���݂̃y�[�W����A�ǂ̃X�e�[�W�Ɉړ�����̂������߂�
	if (isHit)
	{
		CheckLoadStage(selectingBoxNum);
		SelectStageNum = selectingBoxNum;
	}

}
