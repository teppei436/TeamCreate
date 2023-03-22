
#ifndef __MATH_H__
#define __MATH_H__

#include "DxLib.h"

// 2�_�Ԃ̋������v�Z���� (2D)
float GetDistance(float x1, float y1, float x2, float y2);

// �n�_�ƏI�_����x�N�g�����쐬
VECTOR VecCreate(VECTOR start, VECTOR end);

// �x�N�g���̑����Z
VECTOR VecAdd(VECTOR vec1, VECTOR vec2);

// �x�N�g���̒���
float VecLong(VECTOR vec);

// �x�N�g���̐��K��
VECTOR VecNormalize(VECTOR vec);

// �x�N�g�����X�J���[�{
VECTOR VecScale(VECTOR vec, float scale);

#endif