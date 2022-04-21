#pragma once

//#include "DxLib.h"
#include "Vector3.h"

// MATRIX �^�� Matrix4 �^�Ƃ��Ĉ��� ���݊����̊m��&�g���̂���
using Matrix4 = MATRIX;

// �P�ʍs������߂�
Matrix4 Identity();

// �t�s������߂�
Matrix4 Inverse(const Matrix4& m);

// �g��k���s��̐ݒ�
Matrix4 scale(const Vector3& s);

// ��]�s��̐ݒ�
Matrix4 rotateX(float angle);
Matrix4 rotateY(float angle);
Matrix4 rotateZ(float angle);

// ���s�ړ��s��̍쐬
Matrix4 translate(const Vector3& t);

// ���W�ϊ��i�x�N�g���ƍs��̊|���Z������j
Vector3 transform(const Vector3& v, const Matrix4& m);

// ������Z�q�I�[�o�[���[�h
Matrix4& operator *= (Matrix4& m1, const Matrix4& m2);

// 2�����Z�q�I�[�o�[���[�h
Matrix4 operator * (const Matrix4& m1, const Matrix4& m2);
Vector3 operator * (const Vector3& v, const Matrix4& m);