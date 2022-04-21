﻿#include <Raki_Input.h>
#include "Player.h"
#include "Stage.h"
#include "InputManger.h"
#include "Raki_imguiMgr.h"

namespace
{
	static size_t i = 0;
}

Player* Player::Get()
{
	static Player instance = {};
	return &instance;
}

Player::Player() :
	FloorHeight(640.0f),
	CenterPosition{ 100.0f, 100.0f, 0.0f },
	IsLeft(),
	IsRight(),
	Body_One{},
	Body_Two{},
	Body_Three{},
	Body_Four{},
	IsOpenTwo(true),
	IsLeftFold(),
	IsUpFold(),
	IsRightFold(),
	IsDownFold(),
	SideMoveSpeed(2.0f),
	IsJump(false),
	JumpSpeed(3.0f),
	FallSpeed(3.0f),
	IsFaceFall(),
	IsAllFall(false),
	IsInputjump(false),
	Player_IsAction(false),
	FaceHandle{},
	IsGoal(false),
	IsColide(false),
	IsDownBody(false),
	leg{},
	goalParticle{}
{
	Init();

	FaceHandle[0] = TexManager::LoadTexture("Resources/player.png");
	FaceHandle[1] = TexManager::LoadTexture("Resources/playerBody02.png");

	PlayerSprite.Create(FaceHandle[0]);
	PlayerSpriteAction.Create(FaceHandle[1]);
}

Player::~Player()
{
}

void Player::Init()
{
	CenterPosition.x = static_cast<float>(Stage::GetStartPlayerPosX() * Stage::blockSize + Stage::blockSize / 2);
	CenterPosition.y = static_cast<float>(Stage::GetStartPlayerPosY() * Stage::blockSize + Stage::blockSize / 2);

	FallSpeed = 3.0f;
	IsAllFall = true;
	IsJump = false;
	Player_IsAction = false;
	IsColide = false;

	Body_One.Init(CenterPosition, BodyType::left);
	Body_Two.Init(CenterPosition, BodyType::up);
	Body_Three.Init(CenterPosition, BodyType::right);
	Body_Four.Init(CenterPosition, BodyType::down);

	leg.Init();
	IsLeft = true;
	IsRight = false;
}

void Player::Update(Stage& stage, int offsetX, int offsetY)
{
	//マウス左ボタンを押したときの座標
	if (Input::isMouseClickTrigger(0))
	{
		PressPos = Input::getMousePos();
		PressPos.x -= offsetX;
		PressPos.y -= offsetY;
	}

	//マウス左ボタンを離したときの座標
	if (Input::isMouseClicked(0))
	{
		ReleasePos = Input::getMousePos();
		ReleasePos.x -= offsetX;
		ReleasePos.y -= offsetY;
	}

	DragDis = { ReleasePos.x - PressPos.x , ReleasePos.y - PressPos.y };

	if (ReleasePos.x != 0.0f &&
		ReleasePos.y != 0.0f &&
		fabs(ReleasePos.x - PressPos.x) < 30 && fabs(ReleasePos.y - PressPos.y) < 30)
	{
		//IsWalk = true;
	}
	/*else
	{
		IsDragFold = true;

		if (fabs(ReleasePos.x - PressPos.x) > fabs(ReleasePos.y - PressPos.y))
		{
			if (DragDis.x > 0)
			{
				Player_IsAction = true;
				IsLeftFold = true;
				leg.Set();
			}
			else if (DragDis.x < 0)
			{
				Player_IsAction = true;
				IsRightFold = true;
				leg.Set();
			}
		}
		else
		{
			if (DragDis.y > 0)
			{
				Player_IsAction = true;
				IsUpFold = true;
				leg.Set();
			}
			else if (DragDis.y < 0)
			{
				Player_IsAction = true;
				IsDownFold = true;
				leg.Set();
			}
		}
	}*/

	if (IsWalk == true)
	{
		if (PressPos.x < CenterPosition.x)
		{
			CenterPosition.x -= SideMoveSpeed;
			IsLeft = true;
			IsRight = false;

			if (CenterPosition.x - SideMoveSpeed * 2 < PressPos.x)
			{
				IsWalk = false;
			}
		}
		else if (PressPos.x > CenterPosition.x)
		{
			CenterPosition.x += SideMoveSpeed;
			IsLeft = false;
			IsRight = true;

			if (CenterPosition.x + SideMoveSpeed * 2 > PressPos.x)
			{
				IsWalk = false;
			}
		}
		else
		{
			IsWalk = false;
		}
	}

	//左右移動
	if (InputManger::Right() && Player_IsAction == false)
	{
		CenterPosition.x += SideMoveSpeed;
		IsLeft = false;
		IsRight = true;
	}
	if (InputManger::Left() && Player_IsAction == false)
	{
		CenterPosition.x -= SideMoveSpeed;
		IsLeft = true;
		IsRight = false;
	}

	//ジャンプ入力できるかどうか
	if (IsJump == false && IsFall() == false)
	{
		IsInputjump = true;
		FallSpeed = 0.0f;
	}
	else
	{
		IsInputjump = false;
	}

	//ジャンプ
	if (InputManger::UpTrigger() && IsInputjump == true)
	{
		IsJump = true;
		FallSpeed = -5.6f;
	}

	if (IsJump == true)
	{
		if (Player_IsAction == false)
		{
			FallSpeed += 0.2f;
		}

		if (FallSpeed > 0)
		{
			IsJump = false;
			IsAllFall = true;
		}
	}

	//落下判定
	if (IsJump == false && IsAllFall == true && Player_IsAction == false)
	{
		if (FallSpeed < 5.2)
		{
			FallSpeed += 0.2f;
		}
	}

	if (IsAllFall == true && Player_IsAction == false)
	{
		CenterPosition.y += FallSpeed;
	}
	IsHitPlayerBody(stage);

	//折る入力
	if (InputManger::SubLeftTrigger() && Player_IsAction == false && Body_One.IsActivate == true && Body_One.IsFold == false)
	{
		if (IsDirectionFoldAll(stage, BodyType::left))
		{
			Player_IsAction = true;
			IsLeftFold = true;
			leg.Set();
		}
	}
	if (InputManger::SubUpTrigger() && Player_IsAction == false && Body_Two.IsActivate == true && Body_Two.IsFold == false)
	{
		if (IsDirectionFoldAll(stage, BodyType::up))
		{
			Player_IsAction = true;
			IsUpFold = true;
			leg.Set();
		}
	}
	if (InputManger::SubRightTrigger() && Player_IsAction == false && Body_Three.IsActivate == true && Body_Three.IsFold == false)
	{
		if (IsDirectionFoldAll(stage, BodyType::right))
		{
			Player_IsAction = true;
			IsRightFold = true;
			leg.Set();
		}
	}
	if (InputManger::SubDownTrigger() && Player_IsAction == false && Body_Four.IsActivate == true && Body_Four.IsFold == false)
	{
		if (IsDirectionFoldAll(stage, BodyType::down))
		{
			Player_IsAction = true;
			IsDownFold = true;
			leg.Set();
		}
	}

	//足を上げ終わったら折る
	if (leg.FootIsAction == false)
	{
		if (IsLeftFold == true)
		{
			if (Body_One.IsActivate == true)
			{
				Body_One.Ease.addTime = 0.1f;
				Body_One.Ease.maxTime = 1.2f;
				Body_One.Ease.timeRate = 0.0f;

				//折る
				if (Body_One.IsFold == false && Body_One.IsOpen == true && Body_One.IsAction == false)
				{
					Body_One.Ease.isMove = true;
					Body_One.IsFold = true;
					Body_One.IsOpen = false;
					Body_One.IsAction = true;

					if (Body_Two.IsActivate == true && Body_Two.IsFold == true)
					{
						Body_Two.Overlap++;
					}
					if (Body_Three.IsActivate == true && Body_Three.IsFold == true)
					{
						Body_Three.Overlap++;
					}
					if (Body_Four.IsActivate == true && Body_Four.IsFold == true)
					{
						Body_Four.Overlap++;
					}
				}
			}
			IsLeftFold = false;
		}
		if (IsUpFold == true)
		{
			if (Body_Two.IsActivate == true)
			{
				Body_Two.Ease.addTime = 0.1f;
				Body_Two.Ease.maxTime = 1.2f;
				Body_Two.Ease.timeRate = 0.0f;

				//折る
				if (Body_Two.IsFold == false && Body_Two.IsOpen == true && Body_Two.IsAction == false)
				{
					Body_Two.Ease.isMove = true;
					Body_Two.IsFold = true;
					Body_Two.IsOpen = false;
					Body_Two.IsAction = true;

					if (Body_One.IsActivate == true && Body_One.IsFold == true)
					{
						Body_One.Overlap++;
					}
					if (Body_Three.IsActivate == true && Body_Three.IsFold == true)
					{
						Body_Three.Overlap++;
					}
					if (Body_Four.IsActivate == true && Body_Four.IsFold == true)
					{
						Body_Four.Overlap++;
					}
				}
			}
			IsUpFold = false;
		}
		if (IsRightFold == true)
		{
			if (Body_Three.IsActivate == true)
			{
				Body_Three.Ease.addTime = 0.1f;
				Body_Three.Ease.maxTime = 1.2f;
				Body_Three.Ease.timeRate = 0.0f;

				//折る
				if (Body_Three.IsFold == false && Body_Three.IsOpen == true && Body_Three.IsAction == false)
				{
					Body_Three.Ease.isMove = true;
					Body_Three.IsFold = true;
					Body_Three.IsOpen = false;
					Body_Three.IsAction = true;

					if (Body_One.IsActivate == true && Body_One.IsFold == true)
					{
						Body_One.Overlap++;
					}
					if (Body_Two.IsActivate == true && Body_Two.IsFold == true)
					{
						Body_Two.Overlap++;
					}
					if (Body_Four.IsActivate == true && Body_Four.IsFold == true)
					{
						Body_Four.Overlap++;
					}
				}
			}
			IsRightFold = false;
		}
		if (IsDownFold == true)
		{
			if (Body_Four.IsActivate == true)
			{
				Body_Four.Ease.addTime = 0.1f;
				Body_Four.Ease.maxTime = 1.2f;
				Body_Four.Ease.timeRate = 0.0f;

				//折る
				if (Body_Four.IsFold == false && Body_Four.IsOpen == true && Body_Four.IsAction == false)
				{
					Body_Four.Ease.isMove = true;
					Body_Four.IsFold = true;
					Body_Four.IsOpen = false;
					Body_Four.IsAction = true;

					if (Body_One.IsActivate == true && Body_One.IsFold == true)
					{
						Body_One.Overlap++;
					}
					if (Body_Two.IsActivate == true && Body_Two.IsFold == true)
					{
						Body_Two.Overlap++;
					}
					if (Body_Three.IsActivate == true && Body_Three.IsFold == true)
					{
						Body_Three.Overlap++;
					}
				}
			}
			IsDownFold = false;
		}
	}

	//PlayerIsactionのfalse条件
	if (leg.FootIsAction == false &&
		Body_One.IsAction == false &&
		Body_Two.IsAction == false &&
		Body_Three.IsAction == false &&
		Body_Four.IsAction == false)
	{
		Player_IsAction = false;
		leg.IsFootUp = false;
	}

	//開く入力
	if (InputManger::SubLeftTrigger() && Body_One.IsActivate == true && Body_One.IsFold == true && Body_One.Overlap == 0)
	{
		OpenCount = 0;
		IsOpenCountStart = true;
		IsLeftOpen = true;
	}
	if (InputManger::SubUpTrigger() && Body_Two.IsActivate == true && Body_Two.IsFold == true && Body_Two.Overlap == 0 && IsOpenTwo == true)
	{
		OpenCount = 0;
		IsOpenCountStart = true;
		IsUpOpen = true;
	}
	if (InputManger::SubRightTrigger() && Body_Three.IsActivate == true && Body_Three.IsFold == true && Body_Three.Overlap == 0)
	{
		OpenCount = 0;
		IsOpenCountStart = true;
		IsRightOpen = true;
	}
	if (InputManger::SubDownTrigger() && Body_Four.IsActivate == true && Body_Four.IsFold == true && Body_Four.Overlap == 0)
	{
		OpenCount = 0;
		IsOpenCountStart = true;
		IsDownOpen = true;
	}

	if (IsOpenCountStart == true)
	{
		OpenCount++;
	}

	if (OpenCount >= 2)
	{
		if (IsLeftOpen == true)
		{
			Body_One.Ease.addTime = 0.1f;
			Body_One.Ease.maxTime = 1.2f;
			Body_One.Ease.timeRate = 0.0f;

			Body_One.Ease.isMove = true;
			Body_One.IsFold = false;
			Body_One.IsOpen = true;
			Body_One.IsAction = true;

			if (Body_Two.IsActivate == true && Body_Two.IsFold == true)
			{
				Body_Two.Overlap--;
			}
			if (Body_Three.IsActivate == true && Body_Three.IsFold == true)
			{
				Body_Three.Overlap--;
			}
			if (Body_Four.IsActivate == true && Body_Four.IsFold == true)
			{
				Body_Four.Overlap--;
			}
			//IsLeftOpen = false;
		}
		if (IsUpOpen == true)
		{
			Body_Two.Ease.addTime = 0.1f;
			Body_Two.Ease.maxTime = 1.2f;
			Body_Two.Ease.timeRate = 0.0f;

			Body_Two.Ease.isMove = true;
			Body_Two.IsFold = false;
			Body_Two.IsOpen = true;
			Body_Two.IsAction = true;

			if (Body_One.IsActivate == true && Body_One.IsFold == true)
			{
				Body_One.Overlap--;
			}
			if (Body_Three.IsActivate == true && Body_Three.IsFold == true)
			{
				Body_Three.Overlap--;
			}
			if (Body_Four.IsActivate == true && Body_Four.IsFold == true)
			{
				Body_Four.Overlap--;
			}
			//IsUpOpen = false;
		}
		if (IsRightOpen == true)
		{
			Body_Three.Ease.addTime = 0.1f;
			Body_Three.Ease.maxTime = 1.2f;
			Body_Three.Ease.timeRate = 0.0f;

			Body_Three.Ease.isMove = true;
			Body_Three.IsFold = false;
			Body_Three.IsOpen = true;
			Body_Three.IsAction = true;

			if (Body_One.IsActivate == true && Body_One.IsFold == true)
			{
				Body_One.Overlap--;
			}
			if (Body_Two.IsActivate == true && Body_Two.IsFold == true)
			{
				Body_Two.Overlap--;
			}
			if (Body_Four.IsActivate == true && Body_Four.IsFold == true)
			{
				Body_Four.Overlap--;
			}
			//IsRightOpen = false;
		}
		if (IsDownOpen == true)
		{
			Body_One.Ease.addTime = 0.1f;
			Body_One.Ease.maxTime = 1.2f;
			Body_One.Ease.timeRate = 0.0f;

			Body_One.Ease.isMove = true;
			Body_One.IsFold = false;
			Body_One.IsOpen = true;
			Body_One.IsAction = true;

			if (Body_Two.IsActivate == true && Body_Two.IsFold == true)
			{
				Body_Two.Overlap--;
			}
			if (Body_Three.IsActivate == true && Body_Three.IsFold == true)
			{
				Body_Three.Overlap--;
			}
			if (Body_Four.IsActivate == true && Body_Four.IsFold == true)
			{
				Body_Four.Overlap--;
			}
			//IsDownOpen = false;
		}
	}

	if (Body_Four.IsActivate == true && Body_Four.Body_Type == down && Body_Four.IsFold == false)
	{
		IsDownBody = true;
	}
	else
	{
		IsDownBody = false;
	}
	leg.Update(CenterPosition, (IsDownBody && !(Body_Four.IsFold)), 1);

	if (Body_One.IsActivate == true)
	{
		Body_One.IsHitBody(stage, &CenterPosition, FallSpeed, IsAllFall, IsJump, IsColide);
		Body_One.Update(CenterPosition);
	}
	if (Body_Two.IsActivate == true)
	{
		Body_Two.IsHitBody(stage, &CenterPosition, FallSpeed, IsAllFall, IsJump, IsColide);
		Body_Two.Update(CenterPosition);
	}
	if (Body_Three.IsActivate == true)
	{
		Body_Three.IsHitBody(stage, &CenterPosition, FallSpeed, IsAllFall, IsJump, IsColide);
		Body_Three.Update(CenterPosition);
	}
	if (Body_Four.IsActivate == true)
	{
		Body_Four.IsHitBody(stage, &CenterPosition, FallSpeed, IsAllFall, IsJump, IsColide);
		Body_Four.Update(CenterPosition);
	}

	if (IsGoal)
	{
		goalParticle.Init({ 0.0f, 0.0f, 0.0f }, 1.0f, 10, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f });
	}
	goalParticle.Update();
}

void Player::Draw(int offsetX, int offsetY)
{
	leg.Draw(offsetX, offsetY, IsLeft, IsRight);
	if (IsLeft)
	{
		if (Player_IsAction == true)
		{
			PlayerSpriteAction.DrawExtendSprite(
				(CenterPosition.x - 25) + offsetX, (CenterPosition.y - 25) + offsetY,
				(CenterPosition.x + 25) + offsetX, (CenterPosition.y + 25) + offsetY);
		}
		else
		{
			PlayerSprite.DrawExtendSprite(
				(CenterPosition.x - 25) + offsetX, (CenterPosition.y - 25) + offsetY,
				(CenterPosition.x + 25) + offsetX, (CenterPosition.y + 25) + offsetY);
		}
		/*DrawExtendGraph(
			static_cast<int>(CenterPosition.x) - 25 + offsetX, static_cast<int>(CenterPosition.y) - 25 + offsetY,
			static_cast<int>(CenterPosition.x) + 25 + offsetX, static_cast<int>(CenterPosition.y) + 25 + offsetY, FaceHandle[Player_IsAction], true);*/
	}
	if (IsRight)
	{
		if (Player_IsAction == true)
		{
			PlayerSpriteAction.DrawExtendSprite(
				(CenterPosition.x + 25) + offsetX, (CenterPosition.y - 25) + offsetY,
				(CenterPosition.x - 25) + offsetX, (CenterPosition.y + 25) + offsetY);
		}
		else
		{
			PlayerSprite.DrawExtendSprite(
				(CenterPosition.x + 25) + offsetX, (CenterPosition.y - 25) + offsetY,
				(CenterPosition.x - 25) + offsetX, (CenterPosition.y + 25) + offsetY);
		}
		/*DrawExtendGraph(
			static_cast<int>(CenterPosition.x) + 25 + offsetX, static_cast<int>(CenterPosition.y) - 25 + offsetY,
			static_cast<int>(CenterPosition.x) - 25 + offsetX, static_cast<int>(CenterPosition.y) + 25 + offsetY, FaceHandle[Player_IsAction], true);*/
	}


#pragma region BodyDraw

#pragma region body_draw

	if (Body_One.Overlap == 2)
	{
		Body_One.Draw(offsetX, offsetY);
	}
	if (Body_Two.Overlap == 2)
	{
		Body_Two.Draw(offsetX, offsetY);
	}
	if (Body_Three.Overlap == 2)
	{
		Body_Three.Draw(offsetX, offsetY);
	}
	if (Body_Four.Overlap == 2)
	{
		Body_Four.Draw(offsetX, offsetY);
	}

	if (Body_One.Overlap == 1)
	{
		Body_One.Draw(offsetX, offsetY);
	}
	if (Body_Two.Overlap == 1)
	{
		Body_Two.Draw(offsetX, offsetY);
	}
	if (Body_Three.Overlap == 1)
	{
		Body_Three.Draw(offsetX, offsetY);
	}
	if (Body_Four.Overlap == 1)
	{
		Body_Four.Draw(offsetX, offsetY);
	}

	if (Body_One.Overlap == 0)
	{
		Body_One.Draw(offsetX, offsetY);
	}
	if (Body_Two.Overlap == 0)
	{
		Body_Two.Draw(offsetX, offsetY);
	}
	if (Body_Three.Overlap == 0)
	{
		Body_Three.Draw(offsetX, offsetY);
	}
	if (Body_Four.Overlap == 0)
	{
		Body_Four.Draw(offsetX, offsetY);
	}

#pragma endregion

#pragma endregion //body_draw


	PlayerSprite.Draw();
	PlayerSpriteAction.Draw();

#pragma region debug
	if (IsGoal == true)
	{
		//DrawFormatString(300, 100, YELLOW, "GOAL");
	}
	else
	{
		//DrawFormatString(300, 100, YELLOW, "NO GOAL");
	}

#pragma endregion

	goalParticle.Draw();

	ImguiMgr::Get()->StartDrawImgui("IsGoal state", 0.0f, 0.0f);
	ImGui::Text("IsGoal:%d", IsGoal);
	ImguiMgr::Get()->EndDrawImgui();
}

void Player::bodysetup(bool one, int one_type, bool two, int two_type, bool three, int three_type, bool four, int four_type)
{
	if (one == true)
	{
		Body_One.IsActivate = true;
		Body_One.Body_Type = one_type;
	}

	if (two == true)
	{
		Body_Two.IsActivate = true;
		Body_Two.Body_Type = two_type;
	}

	if (three == true)
	{
		Body_Three.IsActivate = true;
		Body_Three.Body_Type = three_type;
	}

	Body_One.setactivate(CenterPosition);
	Body_Two.setactivate(CenterPosition);
	Body_Three.setactivate(CenterPosition);

	CenterPosition.y += 1;
}

void Player::bodysetup(const unsigned char foldCount[4])
{
	static int bodyTile[4] = { 0 };
	static size_t j = 0;

	j = 0;

	for (size_t i = 0; i < sizeof(bodyTile) / sizeof(bodyTile[0]); i++)
	{
		bodyTile[i] = -1;

		for (; j < 4; j++)
		{
			if (foldCount[j] != 0)
			{
				bodyTile[i] = j;
				j++;
				break;
			}
		}
	}

	bodysetup(
		bodyTile[0] != -1, bodyTile[0],
		bodyTile[1] != -1, bodyTile[1],
		bodyTile[2] != -1, bodyTile[2],
		bodyTile[3] != -1, bodyTile[3]);
}

void Player::IsHitPlayerBody(Stage& stage)
{
	//ステージの数
	size_t i = 0;
	//タイルの数
	size_t j = 0;

	//上下左右(プレイヤーの顔)
	int left_mapchip = (int)((CenterPosition.x - 25) - stage.offset.x) / 60;
	int up_mapchip = (int)((CenterPosition.y - 25) - stage.offset.y) / 60;
	int right_mapchip = (int)((CenterPosition.x + 25) - stage.offset.x) / 60;
	int down_mapchip = (int)((CenterPosition.y + 33) - stage.offset.y) / 60;

	//タイル内のマップチップ座標
	int left_mapchip_tile;
	int up_mapchip_tile;
	int right_mapchip_tile;
	int down_mapchip_tile;
	//マップチップの場所(共通)
	int MapchipPos = 0;

	//マップチップの場所(ゴール用)
	int MapchipPos_Goal[3] = { 0 };

	//押し出す方向を決めるための距離
	float BuriedX = 0;
	float BuriedY = 0;

	int FallCount = 0;

	if (CenterPosition.x - 30 <= stage.offset.x)
	{
		CenterPosition.x = 30;
	}
	if (CenterPosition.y - 30 <= stage.offset.y)
	{
		CenterPosition.y = 30;
	}

	for (i = 0; i < stage.GetStageDataSize(); i++)
	{
		for (j = 0; j < stage.GetStageTileDataSize(i); j++)
		{
			//左上
			if (stage.GetPositionTile({ CenterPosition.x - 25,CenterPosition.y - 30,0.0f }, i, j))
			{
				left_mapchip_tile = left_mapchip % stage.GetStageTileWidth(i, j);
				up_mapchip_tile = up_mapchip % stage.GetStageTileHeight(i, j);

				MapchipPos = (up_mapchip_tile)*stage.GetStageTileWidth(i, j) + (left_mapchip_tile);
				if (stage.GetStageMapchip(i, j, MapchipPos) == MapchipData::BLOCK)
				{
					BuriedX = (left_mapchip * 60) - (CenterPosition.x - 30);
					BuriedY = (up_mapchip * 60) - (CenterPosition.y - 30);

					if (BuriedX > BuriedY)
					{
						CenterPosition.y = static_cast<float>(up_mapchip + 1) * stage.blockSize + 25.0f;
					}
					else if (BuriedX < BuriedY)
					{
						CenterPosition.x = static_cast<float>(left_mapchip + 1) * stage.blockSize + 25.0f;
					}
				}
				if (up_mapchip_tile > 0)
				{
					MapchipPos = (up_mapchip_tile - 1) * stage.GetStageTileWidth(i, j) + (left_mapchip_tile);
					if (stage.GetStageMapchip(i, j, MapchipPos) == MapchipData::BLOCK)
					{
						if (Body_Two.IsActivate == true && Body_Two.IsFold == true && Body_Two.Overlap == 0)
						{
							IsOpenTwo = false;
						}
					}
					else
					{
						IsOpenTwo = true;
					}
				}
			}
			//左下
			if (stage.GetPositionTile({ CenterPosition.x - 25,CenterPosition.y + 33,0.0f }, i, j))
			{
				left_mapchip_tile = left_mapchip % stage.GetStageTileWidth(i, j);
				down_mapchip_tile = down_mapchip % stage.GetStageTileHeight(i, j);

				MapchipPos = (down_mapchip_tile)*stage.GetStageTileWidth(i, j) + (left_mapchip_tile);
				if (stage.GetStageMapchip(i, j, MapchipPos) == MapchipData::BLOCK)
				{
					BuriedX = (left_mapchip * 60) - (CenterPosition.x - 30);
					BuriedY = ((CenterPosition.y + 29) - 60) - (down_mapchip * 60);

					if (BuriedX > BuriedY)
					{
						CenterPosition.y = static_cast<float>(down_mapchip * stage.blockSize) - 33.0f;
						FallCount++;
					}
					else if (BuriedX < BuriedY)
					{
						CenterPosition.x = static_cast<float>(left_mapchip + 1) * stage.blockSize + 25.0f;
					}
				}
			}
			//右上
			if (stage.GetPositionTile({ CenterPosition.x + 25,CenterPosition.y - 30,0.0f }, i, j))
			{
				right_mapchip_tile = right_mapchip % stage.GetStageTileWidth(i, j);
				up_mapchip_tile = up_mapchip % stage.GetStageTileHeight(i, j);

				MapchipPos = (up_mapchip_tile)*stage.GetStageTileWidth(i, j) + (right_mapchip_tile);
				if (stage.GetStageMapchip(i, j, MapchipPos) == MapchipData::BLOCK)
				{
					BuriedX = ((CenterPosition.x + 29) - 60) - (right_mapchip * 60);
					BuriedY = (up_mapchip * 60) - (CenterPosition.y - 30);

					if (BuriedX > BuriedY)
					{
						CenterPosition.y = static_cast<float>(up_mapchip + 1) * stage.blockSize + 25.0f;
					}
					else if (BuriedX < BuriedY)
					{
						CenterPosition.x = static_cast<float>(right_mapchip * stage.blockSize) - 25.0f;
					}
				}
				if (up_mapchip_tile > 0)
				{
					MapchipPos = (up_mapchip_tile - 1) * stage.GetStageTileWidth(i, j) + (right_mapchip_tile);
					if (stage.GetStageMapchip(i, j, MapchipPos) == MapchipData::BLOCK)
					{
						if (Body_Two.IsActivate == true && Body_Two.IsFold == true && Body_Two.Overlap == 0)
						{
							IsOpenTwo = false;
						}
					}
					else
					{
						IsOpenTwo = true;
					}
				}

			}
			//右下
			if (stage.GetPositionTile({ CenterPosition.x + 25,CenterPosition.y + 33,0.0f }, i, j))
			{
				right_mapchip_tile = right_mapchip % stage.GetStageTileWidth(i, j);
				down_mapchip_tile = down_mapchip % stage.GetStageTileHeight(i, j);

				MapchipPos = (down_mapchip_tile)*stage.GetStageTileWidth(i, j) + (right_mapchip_tile);
				if (stage.GetStageMapchip(i, j, MapchipPos) == MapchipData::BLOCK)
				{
					BuriedX = ((CenterPosition.x + 29) - 60) - (right_mapchip * 60);
					BuriedY = ((CenterPosition.y + 29) - 60) - (down_mapchip * 60);

					if (BuriedX > BuriedY)
					{
						CenterPosition.y = static_cast<float>(down_mapchip * stage.blockSize) - 33.0f;
						FallCount++;
					}
					else if (BuriedX < BuriedY)
					{
						CenterPosition.x = static_cast<float>(right_mapchip * stage.blockSize) - 25.0f;
					}
				}
			}

			//ゴール判定
			if (stage.GetPositionTile(CenterPosition, i, j))
			{
				left_mapchip_tile = left_mapchip % stage.GetStageTileWidth(i, j);
				up_mapchip_tile = up_mapchip % stage.GetStageTileHeight(i, j);
				right_mapchip_tile = right_mapchip % stage.GetStageTileWidth(i, j);
				down_mapchip_tile = down_mapchip % stage.GetStageTileHeight(i, j);

				//左上
				MapchipPos = up_mapchip_tile * stage.GetStageTileWidth(i, j) + (left_mapchip_tile);
				MapchipPos_Goal[0] = up_mapchip_tile * stage.GetStageTileWidth(i, j) + (right_mapchip_tile);
				MapchipPos_Goal[1] = down_mapchip_tile * stage.GetStageTileWidth(i, j) + (left_mapchip_tile);
				MapchipPos_Goal[2] = down_mapchip_tile * stage.GetStageTileWidth(i, j) + (right_mapchip_tile);

				if (stage.GetStageMapchip(i, j, MapchipPos) == MapchipData::GOAL)
				{
					IsGoal = true;
				}
				//右上
				else if (stage.GetStageMapchip(i, j, MapchipPos_Goal[0]) == MapchipData::GOAL)
				{
					IsGoal = true;
				}
				//左下
				else if (stage.GetStageMapchip(i, j, MapchipPos_Goal[1]) == MapchipData::GOAL)
				{
					IsGoal = true;
				}
				//右下
				else if (stage.GetStageMapchip(i, j, MapchipPos_Goal[2]) == MapchipData::GOAL)
				{
					IsGoal = true;
				}
				else
				{
					IsGoal = false;
				}
			}
		}
	}

	if (FallCount > 0)
	{
		IsFaceFall = false;
	}
	else
	{
		IsFaceFall = true;
	}
}

bool Player::IsFall()
{
	int FallCount = 0;

	if (Body_One.IsActivate == true && Body_One.BodyIsFall == false)
	{
		FallCount++;
	}
	if (Body_Two.IsActivate == true && Body_Two.BodyIsFall == false)
	{
		FallCount++;
	}
	if (Body_Three.IsActivate == true && Body_Three.BodyIsFall == false)
	{
		FallCount++;
	}
	if (Body_Four.IsActivate == true && Body_Four.BodyIsFall == false)
	{
		FallCount++;
	}
	if (IsFaceFall == false)
	{
		FallCount++;
	}

	if (FallCount > 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Player::SetBodyStatus(PlayerBody* arrangement, int size)
{
	arrangement[0] = Body_Two;
	arrangement[1] = Body_Four;
	arrangement[2] = Body_One;
	arrangement[3] = Body_Three;
}

bool Player::IsReverseHitFace(Stage& stage, const unsigned char& direction)
{
	//顔の四辺
	float BodyLeft;
	float BodyRight;
	float BodyUp;
	float BodyDown;

	BodyLeft = CenterPosition.x - 25;
	BodyRight = CenterPosition.x + 25;
	BodyUp = CenterPosition.y - 25;
	BodyDown = CenterPosition.y + 25;

	//上下左右(プレイヤーの顔)
	int left_mapchip = (int)(BodyLeft - stage.offset.x) / 60;
	int up_mapchip = (int)(BodyUp - stage.offset.y) / 60;
	int right_mapchip = (int)(BodyRight - stage.offset.x) / 60;
	int down_mapchip = (int)(BodyDown - stage.offset.y) / 60;

	//タイル内のマップチップ座標
	int left_mapchip_tile;
	int up_mapchip_tile;
	int right_mapchip_tile;
	int down_mapchip_tile;

	//反転したマップチップたち
	char* ReverseMapchips = { 0 };

	//折れるかどうか(プレイヤーの中心座標)
	int CenterPositionFold = stage.FoldSimulation(CenterPosition, direction, &ReverseMapchips);

	//playerの中心座標
	if (CenterPositionFold == -1)
	{
		return false;
	}

	//マップチップの場所(25個)
	int MapchipPos = 0;

	//反転したブロックマップチップと顔の四隅との判定
	for (int i = 0; i < stage.GetStageDataSize(); i++)
	{
		for (int j = 0; j < stage.GetStageTileDataSize(i); j++)
		{
			//左上
			if (stage.GetPositionTile({ CenterPosition.x - 25,CenterPosition.y - 30,0.0f }, i, j))
			{
				left_mapchip_tile = left_mapchip % stage.GetStageTileWidth(i, j);
				up_mapchip_tile = up_mapchip % stage.GetStageTileHeight(i, j);

				MapchipPos = (up_mapchip_tile)*stage.GetStageTileWidth(i, j) + (left_mapchip_tile);

				if (ReverseMapchips[MapchipPos] == MapchipData::BLOCK)
				{
					return false;
				}
			}
			//左下
			if (stage.GetPositionTile({ CenterPosition.x - 25,CenterPosition.y + 33,0.0f }, i, j))
			{
				left_mapchip_tile = left_mapchip % stage.GetStageTileWidth(i, j);
				down_mapchip_tile = down_mapchip % stage.GetStageTileHeight(i, j);

				MapchipPos = (down_mapchip_tile)*stage.GetStageTileWidth(i, j) + (left_mapchip_tile);

				if (ReverseMapchips[MapchipPos] == MapchipData::BLOCK)
				{
					return false;
				}
			}
			//右上
			if (stage.GetPositionTile({ CenterPosition.x + 25,CenterPosition.y - 30,0.0f }, i, j))
			{
				right_mapchip_tile = right_mapchip % stage.GetStageTileWidth(i, j);
				up_mapchip_tile = up_mapchip % stage.GetStageTileHeight(i, j);

				MapchipPos = (up_mapchip_tile)*stage.GetStageTileWidth(i, j) + (right_mapchip_tile);

				if (ReverseMapchips[MapchipPos] == MapchipData::BLOCK)
				{
					return false;
				}
			}
			//右下
			if (stage.GetPositionTile({ CenterPosition.x + 25,CenterPosition.y + 33,0.0f }, i, j))
			{
				right_mapchip_tile = right_mapchip % stage.GetStageTileWidth(i, j);
				down_mapchip_tile = down_mapchip % stage.GetStageTileHeight(i, j);

				MapchipPos = (down_mapchip_tile)*stage.GetStageTileWidth(i, j) + (right_mapchip_tile);

				if (ReverseMapchips[MapchipPos] == MapchipData::BLOCK)
				{
					return false;
				}
			}
		}
	}

	return true;
}

bool Player::IsDirectionFoldAll(Stage& stage, BodyType foldtype)
{
	int BodyCanFoldCount = 0;

	if (Body_One.IsActivate == true && Body_One.IsReverseHitBody(stage, foldtype) == false)
	{
		BodyCanFoldCount++;
	}
	if (Body_Two.IsActivate == true && Body_Two.IsReverseHitBody(stage, foldtype) == false)
	{
		BodyCanFoldCount++;
	}
	if (Body_Three.IsActivate == true && Body_Three.IsReverseHitBody(stage, foldtype) == false)
	{
		BodyCanFoldCount++;
	}
	if (Body_Four.IsActivate == true && Body_Four.IsReverseHitBody(stage, foldtype) == false)
	{
		BodyCanFoldCount++;
	}

	bool ReverseHitFace = IsReverseHitFace(stage, foldtype);

	if (ReverseHitFace == true && BodyCanFoldCount <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Player::ActivateBodyCount()
{
	int count = 0;

	if (Body_One.IsActivate == true)
	{
		count++;
	}
	if (Body_Two.IsActivate == true)
	{
		count++;
	}
	if (Body_Three.IsActivate == true)
	{
		count++;
	}
	if (Body_Four.IsActivate == true)
	{
		count++;
	}

	return count;
}
