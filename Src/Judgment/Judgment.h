
#ifndef _JUDGMENT_H_
#define _JUDGMENT_H_

// SE�t�@�C���p�X
#define DAMAGE_SE_PATH "Data/Sound/SE/DamageSE.wav"
#define GET_SE_PATH    "Data/Sound/SE/GetSE.wav"

// �C���^�[�o��
enum {
	DAMAGE_INTERVAL = 20, // �_���[�W�̃C���^�[�o��
};

// ����������
void InitJudgment();

// �X�V����
void StepJudgment();

//�I������
void FinJudgment();

// �_���[�W����
void AddDamage(int damage);

#endif