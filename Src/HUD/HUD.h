
#ifndef _HUD_H_
#define _HUD_H_

// ��`�֘A-------------------------------------------

#define HEART_HUD "Data/HUD/Heart.png" // �̗�HUD�̃p�X

// �̗͕\��HUD�̏��
enum HeartHUDInfo {
	HEART_HUD_INIT_X  = 10,  // ����X���W
	HEART_HUD_INIT_Y  = 660, // ����Y���W
	HEART_HUD_MAX_NUM = 10,  // �̗͕\��HUD�̍ő吔
};

// �̗͕\��HUD�f�[�^�̍\����
struct HeartHUD_Data {
	int hndl;   // �摜�n���h��
	VECTOR pos; // ���W
}; extern HeartHUD_Data g_heartHUD_Data[HEART_HUD_MAX_NUM];

// ����������
void InitHUD();

// �X�V����
void StepHUD();

// �`�揈��
void DrawHUD();

// �I������
void FinHUD();

#endif _HUD_H_