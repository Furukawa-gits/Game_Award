#include "Tutorial.h"
#include "Player.h"
#include "InputManger.h"

namespace
{
Player* player = Player::Get();
}

Tutorial::Tutorial() :
	moveHandle(0),
	foldHandle(0),
	moveSprite{},
	foldSprite{},
	isTutorial(false),
	isMoveTutorial(false),
	isFoldTutorial(false),
	isFirst(true),
	isFirstOnly(false)
{
	Init();
}

Tutorial::~Tutorial()
{
}

void Tutorial::Init()
{
	isTutorial = false;
	isMoveTutorial = true;
	isFoldTutorial = false;
	isFirst = true;
	isFirstOnly = false;
}

void Tutorial::Update()
{
	if (isTutorial == false)
	{
		return;
	}

	if (isFirstOnly && isFirst == false)
	{
		isTutorial = false;
		return;
	}

	static bool isMove = false;
	static bool isFold = false;

	isMove = player->IsWalk;
	isFold = player->IsUpFold || player->IsDownFold ||
		player->IsLeftFold || player->IsRightFold;

	if (isMoveTutorial == true)
	{
		if (isMove)
		{
			isMoveTutorial = false;
			isFoldTutorial = true;
		}
	}
	else if (isFoldTutorial == true)
	{
		if (isFold)
		{
			isFoldTutorial = false;
		}
	}

	if (isMoveTutorial == false && isFoldTutorial == false)
	{
		isFirst = false;
		isTutorial = false;
	}
}

void Tutorial::Draw(int offsetX, int offsetY)
{
	if (isTutorial == false)
	{
		return;
	}

	if (isFirstOnly && isFirst == false)
	{
		return;
	}

	if (isMoveTutorial)
	{
		moveSprite.DrawSprite(static_cast<float>(offsetX), static_cast<float>(offsetY));
		moveSprite.Draw();
	}
	if (isFoldTutorial)
	{
		foldSprite.DrawSprite(static_cast<float>(offsetX), static_cast<float>(offsetY));
		foldSprite.Draw();
	}
}

void Tutorial::Create()
{
	if ((moveSprite.spdata->size.x <= 0) || (moveSprite.spdata->size.y <= 0))
	{
		moveHandle = TexManager::LoadTexture("./Resources/tutorialMove.png");
		moveSprite.Create(moveHandle);
	}
	if ((foldSprite.spdata->size.x <= 0) || (foldSprite.spdata->size.y <= 0))
	{
		foldHandle = TexManager::LoadTexture("./Resources/tutorialFold.png");
		foldSprite.Create(foldHandle);
	}
}

void Tutorial::StartTutorial()
{
	if (isTutorial)
	{
		return;
	}

	if (isFirstOnly && isFirst == false)
	{
		isTutorial = false;
		return;
	}

	isTutorial = true;
	isMoveTutorial = true;
	isFoldTutorial = false;
}
