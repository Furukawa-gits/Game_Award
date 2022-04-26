#pragma once

class ActFlag final
{
public: //�V���O���g����
	static ActFlag* Get();
private:
	ActFlag();
	ActFlag(const ActFlag*) = delete;
	~ActFlag();
	ActFlag operator=(const ActFlag*) = delete;

public: //�����o�֐�
	// ����
	bool Decision();
	// �L�����Z��
	bool Cancel();

	// ���ɓ���
	bool MoveLeft();
	// �E�ɓ���
	bool MoveRight();
	// �W�����v
	bool Jump();
	// ��ɐ܂��
	bool FoldUp();
	// ���ɐ܂��
	bool FoldDown();
	// ���ɐ܂��
	bool FoldLeft();
	// �E�ɐ܂��
	bool FoldRight();
	// ��ɊJ��
	bool OpenUp();
	// ���ɊJ��
	bool OpenDown();
	// ���ɊJ��
	bool OpenLeft();
	// �E�ɊJ��
	bool OpenRight();
};
