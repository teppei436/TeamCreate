
#include <math.h>
#include "Math.h"

// �_P(x1, y1)����_Q(x2,y2)�܂ł̋�����Ԃ�
float GetDistance(float x1, float y1, float x2, float y2)
{
	// �_P����_Q�܂ł̒������ΕӂƂ��钼�p�O�p�`�����A
	// �s�^�S���X�̒藝����Εӂ̒������v�Z����B
	// �@��ӂ̒������v�Z����
	float base = x1 - x2;

	// �A�����̒������v�Z����
	float height = y1 - y2;

	// �B�s�^�S���X�̒藝����Εӂ̒������v�Z����
	//   ��������<Math.h>��sqrtf�֐��Ōv�Z���邱�Ƃ��ł���
	//   �v�Z���ʂ�ϐ�dist�Ɋi�[���Ă�������
	float hypotenuse = (base * base) + (height * height);
	float dist = sqrtf(hypotenuse);

	return dist;
}

// �n�_�ƏI�_����x�N�g�����쐬
VECTOR VecCreate(VECTOR start, VECTOR end)
{
	VECTOR result;

	// �@�x�N�g���́u�I�_ - �n�_�v�ŋ��߂���
	result.x = end.x - start.x;
	result.y = end.y - start.y;
	result.z = end.z - start.z;

	return result;
}

// �x�N�g���̑����Z
VECTOR VecAdd(VECTOR vec1, VECTOR vec2)
{
	VECTOR result;

	// �@�e�����𑫂��Z����
	result.x = vec1.x + vec2.x;
	result.y = vec1.y + vec2.y;
	result.z = vec1.z + vec2.z;

	return result;
}

// �x�N�g���̒���
float VecLong(VECTOR vec)
{
	// �@�s�^�S���X�̒藝����x�N�g���̒��������߂�
	return sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

// �x�N�g���̐��K��
VECTOR VecNormalize(VECTOR vec)
{
	VECTOR result = { 0 };

	// �@�x�N�g���̒��������߂�
	float vec_long = VecLong(vec);

	// �A�e�����𒷂��Ŋ��邱�Ƃɂ�萳�K������
	// �R�R���l���Ă݂�
	result.x = vec.x / vec_long;
	result.y = vec.y / vec_long;
	result.z = vec.z / vec_long;

	return result;
}

// �x�N�g�����X�J���[�{
VECTOR VecScale(VECTOR vec, float scale)
{
	VECTOR result;

	// �@�e�������X�J���[�{����
	result.x = vec.x * scale;
	result.y = vec.y * scale;
	result.z = vec.z * scale;

	return result;
}
