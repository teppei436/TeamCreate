
#include "DxLib.h"
#include "Player.h"
#include "../Common/Common.h"
#include "../Effect/Effect.h"
#include "../Enemy/Enemy.h"
#include "../Input/Input.h"
#include "../Scene/ScenePlay.h"

PlayerData g_playerData;

//---------------------------------
//		����������
//---------------------------------
void InitPlayer()
{
	g_playerData.pos.x   = PLAYER_INIT_X;
	g_playerData.pos.y   = PLAYER_INIT_Y;

	g_playerData.hndl = LoadGraph(PLAYER_PATH);
}

//---------------------------------
//		�I������
//---------------------------------
void FinPlayer()
{
	// �摜�f�[�^�̔j��
	DeleteGraph(g_playerData.hndl);
	
}

//---------------------------------
//		�X�V����
//---------------------------------
void StepPlayer()
{
	// �L�[���͂ɂ��ړ�-------------------------
	// �E�ړ�
	if (IsKeyDown(KEY_INPUT_RIGHT) == 1) {
		// �ʏ�X�s�[�h
		g_playerData.pos.x += PLAYER_SPD;
	}

	// ���ړ�
	if (IsKeyDown(KEY_INPUT_LEFT) == 1) {
		// �ʏ�X�s�[�h
		g_playerData.pos.x -= PLAYER_SPD;
	}

	//---------------------------------------------
}

//---------------------------------
//		�`�揈��
//---------------------------------
void DrawPlayer()
{
	DrawRotaGraph((int)g_playerData.pos.x, (int)g_playerData.pos.y, 1.0, 0.0, g_playerData.hndl, TRUE);
}

//�v���C���[�擾
PlayerData* GetPlayerData()
{
	return &g_playerData;
}