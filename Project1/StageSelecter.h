#pragma once
#include <memory>
#include <array>
#include <TexManager.h>
#include <Sprite.h>
#include <Raki_Input.h>

//�X�e�[�W�I�����Ǘ�����
class StageSelecter
{
private:
	//�X�e�[�W�{�҂��Ǘ�����N���X�̃|�C���^�i�Q�Ƃ��Ă��邾���Ȃ̂�weak_ptr�ɂ������j

public:
	StageSelecter();
	~StageSelecter();

	//������
	void Init();
	//�X�V
	void Update();
	//�`��
	void Draw();
	//�I��
	void Finalize();

	//�Q�[���{�҂֑J�ڂ���t���O
	bool GetMoveGameMain() { return isChanging_GameMain; }

	//�Q�[�����C���֑J�ڂ���t���O
	bool isChanging_GameMain = false;

	//�I�������X�e�[�W�ԍ�(GameScene�ɓn���p)
	int SelectStageNum = 0;

	//���݂̏��
	enum NOW_SELECTER_STATE
	{
		is_selecting,				//�I�𒆁i�X�e�[�W�ԍ��̓��͂��󂯕t����j
		is_pageChange_waiting,		//�y�[�W�`�F���W���o��
		is_stageSelected_waiting,	//�X�e�[�W�I�������A�J�ډ��o���s��
	};
	NOW_SELECTER_STATE state;

private:
	//�X�e�[�W�I����ʂ̃��\�[�X
	std::array<Sprite, 20> selectImg_1_4;
	std::array<Sprite, 20> selectImg_5_8;
	std::array<Sprite, 20> selectImg_9_12;

	//���ݕ\������X�e�[�W�̃y�[�W
	enum STAGE_PAGE
	{
		page_1_4,
		page_5_8,
		page_9_12,
	};
	STAGE_PAGE nowpage;		//���݂̃y�[�W
	STAGE_PAGE nextpage;	//�O�̃y�[�W
	STAGE_PAGE displayPage;	//�\������y�[�W

	enum PAGE_MOVE_DIR
	{
		is_front,
		is_back,
	};
	PAGE_MOVE_DIR pageMoveDir;

	//�\���ԍ�
	int nowDisplayNum = 0;

	unsigned char playerTile[4] = { 0 };

	//���[�h�֐��i�A�ԉ摜�̂��߂�int -> string�ϊ��j
	void LoadSprite();

	//�y�[�W�J�ڂ̂��߂̓��͌��m�A�y�[�W��Ԑؑ�
	void CheckToPageChangeInput();

	//�y�[�W��Ԃɉ���������
	int animationFrame = 0;
	const int perFrame = 3;
	void PageChange();

	//�X�e�[�W�J�ڂ̂��߂̓��͌��m
	const int NUMBOX_START_X = 325;
	const int NUMBOX_START_Y = 285;
	const int NUMBOX_SIZE = 130;
	const int NUMBOX_SPACE = 60;
	void CheckLoadStage(int boxnum);
	void CheckToStageChangeInput();

};

