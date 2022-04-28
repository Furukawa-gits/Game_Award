#include "ActFlag.h"
#include "InputManger.h"
#include "Player.h"
#include "Stage.h"

namespace //�֐��Ԃ̎󂯓n���͕K�v�������ϐ�����������
{
	/*�e��t���O*/
	static bool isFold = false; //�܂�邩�ǂ���
	static bool isOpen = false; //�J���邩�ǂ���

	/*�t���O�ȊO*/
	static Player* player = Player::Get(); //�v���C���[
	static Stage* stage = Stage::Get();    //�X�e�[�W
}

bool ActFlag::isMouse = false;

ActFlag* ActFlag::Get()
{
	static ActFlag ins{};
	return &ins;
}

ActFlag::ActFlag()
{
}

ActFlag::~ActFlag()
{
}

bool ActFlag::Decision()
{
	return InputManger::DecisionTrigger();
}

bool ActFlag::Cancel()
{
	return InputManger::CancelTrigger();
}

bool ActFlag::MoveLeft()
{
	return InputManger::Left();
}

bool ActFlag::MoveRight()
{
	return InputManger::Right();
}

bool ActFlag::Jump()
{
	return false;
}

bool ActFlag::FoldUp()
{
	isFold = InputManger::SubUpTrigger() && player->Player_IsAction == false &&
		player->Body_Two.IsActivate && player->Body_Two.IsFold == false;
	//if (isFold)
	//{
	//    isFold = InputManger::SubUpTrigger();
	//}

	return isFold;
}

bool ActFlag::FoldDown()
{
	isFold = InputManger::SubDownTrigger() && player->Player_IsAction == false &&
		player->Body_Four.IsActivate && player->Body_Four.IsFold == false;
	//if (isFold)
	//{
	//    isFold = InputManger::SubDownTrigger();
	//}

	return isFold;
}

bool ActFlag::FoldLeft()
{
	isFold = InputManger::SubLeftTrigger() && player->Player_IsAction == false &&
		player->Body_One.IsActivate && player->Body_One.IsFold == false;
	//if (isFold)
	//{
	//    isFold = InputManger::SubLeftTrigger();
	//}

	return isFold;
}

bool ActFlag::FoldRight()
{
	isFold = InputManger::SubRightTrigger() && player->Player_IsAction == false &&
		player->Body_Three.IsActivate && player->Body_Three.IsFold == false;
	//if (isFold)
	//{
	//	isFold = InputManger::SubRightTrigger();
	//}

	return isFold;
}

bool ActFlag::OpenUp()
{
	// �L�[�{�[�h&�R���g���[���[����
	isOpen = InputManger::SubUpTrigger() && player->Body_Two.IsActivate &&
		player->Body_Two.IsFold && player->Body_Two.AfterBodyFoldCount == 0 && player->IsUpBlocked;
	//if (isOpen)
	//{
	//    isOpen = InputManger::SubUpTrigger();
	//}

	return isOpen;
}

bool ActFlag::OpenDown()
{
	// �L�[�{�[�h&�R���g���[���[����
	isOpen = InputManger::SubDownTrigger() && player->Body_Four.IsActivate &&
		player->Body_Four.IsFold && player->Body_Four.AfterBodyFoldCount == 0;
	//if (isOpen)
	//{
	//    isOpen = InputManger::SubDownTrigger();
	//}

	return isOpen;
}

bool ActFlag::OpenLeft()
{
	// �L�[�{�[�h&�R���g���[���[����
	isOpen = InputManger::SubLeftTrigger() && player->Body_One.IsActivate &&
		player->Body_One.IsFold && player->Body_One.AfterBodyFoldCount == 0;
	//if (isOpen)
	//{
	//    isOpen = InputManger::SubLeftTrigger();
	//}

	return isOpen;
}

bool ActFlag::OpenRight()
{
	// �L�[�{�[�h&�R���g���[���[����
	isOpen = InputManger::SubDownTrigger() && player->Body_Three.IsActivate &&
		player->Body_Three.IsFold && player->Body_Three.AfterBodyFoldCount == 0;
	//if (isOpen)
	//{
	//	isOpen = InputManger::SubRightTrigger();
	//}

	return isOpen;
}
