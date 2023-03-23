
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
	g_playerData.m_dir   = DIR_FRONT_PLAYER;
	g_playerData.animCnt = 0;
}

//---------------------------------
//		�I������
//---------------------------------
void FinPlayer()
{
	// �摜�f�[�^�̔j��
	for (int i = 0; i < PLAYER_GRAPH_NUM; i++) {
		if (g_playerData.hndl[i] == -1) {
			DeleteGraph(g_playerData.hndl[i]);
			g_playerData.hndl[i] = -1;
		}
	}
}

//---------------------------------
//		�}�b�v�`�b�v�摜�̓Ǎ���
//---------------------------------
void LoadPlayerGraph()
{
	// �ꖇ�̉摜�𕪊����[�h�@�G���[�Ȃ�uret�v��-1������
	int ret = LoadDivGraph(PLAYER_PATH, PLAYER_GRAPH_NUM,
		PLAYER_GRAPH_X, PLAYER_GRAPH_Y, PLAYER_SIZE, PLAYER_SIZE, g_playerData.hndl);
}


//---------------------------------
//		�X�V����
//---------------------------------
void StepPlayer()
{
	g_playerData.m_dir = DIR_FRONT_PLAYER;

	// �L�[���͂ɂ��ړ�-------------------------
	// �E�ړ�
	if (IsKeyDown(KEY_INPUT_RIGHT) == 1) {
		g_playerData.m_dir = DIR_RIGHT_PLAYER;

		// �ʏ�X�s�[�h
		g_playerData.pos.x += PLAYER_SPD;
	}

	// ���ړ�
	if (IsKeyDown(KEY_INPUT_LEFT) == 1) {
		g_playerData.m_dir = DIR_LEFT_PLAYER;

		// �ʏ�X�s�[�h
		g_playerData.pos.x -= PLAYER_SPD;
	}

	//---------------------------------------------

	// �A�j���[�V�����̃J�E���g�X�V
	g_playerData.animCnt++;

	// �A�j���[�V���������[�v
	if (g_playerData.animCnt >= ANIM_COUNT * 4) {
		g_playerData.animCnt = 0;
	}
}

//---------------------------------
//		�`�揈��
//---------------------------------
void DrawPlayer()
{
	int animNum[] = { 0, 1, 2, 3 };
	int animID = g_playerData.m_dir * PLAYER_GRAPH_X + animNum[g_playerData.animCnt / ANIM_COUNT];

	DrawRotaGraph((int)g_playerData.pos.x, (int)g_playerData.pos.y, 1.0, 0.0, g_playerData.hndl[animID], TRUE);
}

//�v���C���[�擾
PlayerData* GetPlayerData()
{
	return &g_playerData;
}