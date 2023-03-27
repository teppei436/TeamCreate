
#include "DxLib.h"
#include "HUD.h"
#include "../Enemy/Enemy.h"
#include "../Input/Input.h"
#include "../judgment/judgment.h"
#include "../Person/Person.h"

HeartHUD_Data  g_heartHUD_Data[HEART_HUD_MAX_NUM] = { 0 };

//---------------------------------
//		����������
//---------------------------------
void InitHUD()
{
	// �̗͕\��HUD������
	for (int index = 0; index < HEART_HUD_MAX_NUM; index++) {
		g_heartHUD_Data[index].hndl = LoadGraph(HEART_HUD);
		g_heartHUD_Data[index].pos.x = index * 50.0f;
		g_heartHUD_Data[index].pos.y = HEART_HUD_INIT_Y;
	}
}

//---------------------------------
//		�X�V����
//---------------------------------
void StepHUD()
{

}

//---------------------------------
//		�`�揈��
//---------------------------------
void DrawHUD()
{
	// �̗͕\��HUD�̉摜�`��
	for (int index = 0; index < g_personData.hp; index++) {
		DrawGraph((int)g_heartHUD_Data[index].pos.x, (int)g_heartHUD_Data[index].pos.y, g_heartHUD_Data[index].hndl, TRUE);
	}
}

//---------------------------------
//		�I������
//---------------------------------
void FinHUD()
{
	// �摜�f�[�^�̔j��
	for (int index = 0; index < HEART_HUD_MAX_NUM; index++) {
		DeleteGraph(g_heartHUD_Data[index].hndl);
	}
}