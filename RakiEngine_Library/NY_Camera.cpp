#include "NY_Camera.h"
#include "Raki_WinAPI.h"

NY_Camera::NY_Camera(XMFLOAT3 eye_, XMFLOAT3 target_, XMFLOAT3 up_)
{
	//�e�l�̊i�[
	_eye = eye_;
	_target = target_;
	_up = up_;

	//�r���[�s��i�[
	_matView = XMMatrixLookAtLH(XMLoadFloat3(&_eye), XMLoadFloat3(&_target), XMLoadFloat3(&_up));

	//�v���W�F�N�V�����s�񐶐�
	_matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		(float)Raki_WinAPI::window_width / (float)Raki_WinAPI::window_height,
		0.1f, 1000.0f
	);

	//���[�J�����W����
	_camRocal = XMMatrixIdentity();

	_camRocal.r[0].m128_f32[0] = _eye.x;
	_camRocal.r[0].m128_f32[1] = _eye.y;
	_camRocal.r[0].m128_f32[2] = _eye.z;
	_camRocal.r[0].m128_f32[3] = 1;

	_camRocal.r[1].m128_f32[0] = _up.x - _eye.x;
	_camRocal.r[1].m128_f32[1] = _up.y - _eye.y;
	_camRocal.r[1].m128_f32[2] = _up.z - _eye.z;
	_camRocal.r[1].m128_f32[3] = 0;

	_camRocal.r[2].m128_f32[0] = _target.x;
	_camRocal.r[2].m128_f32[1] = _target.y;
	_camRocal.r[2].m128_f32[2] = _target.z;
	_camRocal.r[2].m128_f32[3] = 1;

	_camRocal.r[3].m128_f32[3] = 0;

	UpdateViewMat();
}

void NY_Camera::SetProjecion()
{
	//�v���W�F�N�V�����s�񐶐�
	_matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		(float)Raki_WinAPI::window_width / (float)Raki_WinAPI::window_height,
		0.1f, 1000.0f
	);
	_matProjection2D = XMMatrixOrthographicOffCenterLH(
		0.0f, Raki_WinAPI::window_width, Raki_WinAPI::window_height, 0.0f, 0.0f, 1.0f);
}

void NY_Camera::SetViewStatusEyeTargetUp(XMFLOAT3 &eye, XMFLOAT3 &target, XMFLOAT3 &up)
{
	//�p�����[�^�ݒ�
	_eye	= eye;
	_target = target;
	_up		= up;

	//�X�V
	UpdateViewMat();
}

void NY_Camera::SetViewStatusEye(XMFLOAT3 &eye)
{
	//�p�����[�^�ݒ�
	_eye = eye;

	//�X�V
	UpdateViewMat();
}

void NY_Camera::SetViewStatusTarget(XMFLOAT3 &target)
{
	_target = target;

	UpdateViewMat();
}

void NY_Camera::SetViewStatusUp(XMFLOAT3 &up) 
{
	_up = up;

	UpdateViewMat();
}

XMMATRIX NY_Camera::GetMatrixView()
{
	return _matView;
}

XMMATRIX NY_Camera::GetMatrixViewProjection()
{
	return _matViewProj;
}

XMMATRIX NY_Camera::GetMatrixBillBoardAll()
{
	return _matBillBoard;
}

XMMATRIX NY_Camera::GetMatrixProjection()
{
	return _matProjection;
}

XMMATRIX NY_Camera::GetMatrixProjection2D()
{
	return _matProjection2D;
}

void NY_Camera::UpdateViewMat() {

	_matView = XMMatrixIdentity();

	_matView = XMMatrixLookAtLH(XMLoadFloat3(&_eye), XMLoadFloat3(&_target), XMLoadFloat3(&_up));

	//�v���W�F�N�V�����s�񐶐�
	_matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		(float)Raki_WinAPI::window_width / (float)Raki_WinAPI::window_height,
		0.1f, 1000.0f
	);
	//�r���[�v���W�F�N�V�����s��
	_matViewProj = _matView * _matProjection;

	// �ȉ��A�r���{�[�h�s��̌v�Z

	//XMVECTOR�Ɉړ�
	XMVECTOR eyeVec = XMLoadFloat3(&_eye);
	XMVECTOR targetVec = XMLoadFloat3(&_target);
	XMVECTOR upVec = XMLoadFloat3(&_up);

	//Z���v�Z
	XMVECTOR axisZ = XMVectorSubtract(targetVec, eyeVec);
	axisZ = XMVector3Normalize(axisZ);
	//x���v�Z
	XMVECTOR axisX = XMVector3Cross(upVec, axisZ);
	axisX = XMVector3Normalize(axisX);
	//y���v�Z
	XMVECTOR axisY = XMVector3Cross(axisZ, axisX);

	//��]�s��v�Z
	XMMATRIX camrot;
	camrot.r[0] = axisX;
	camrot.r[1] = axisY;
	camrot.r[2] = axisZ;
	camrot.r[3] = XMVectorSet(0, 0, 0, 1);
	//y���r���{�[�h�v�Z��������

	//�S�����r���{�[�h�v�Z
	_matBillBoard = camrot;

}
