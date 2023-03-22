
#include "DxLib.h"
#include "Scene.h"
#include "SceneClear.h"
#include "../Input/Input.h"

// �N���A�w�i�摜�̃p�X
#define BG_CLEAR_PATH "Data/BackGround/BgClear.png"

// BGM�t�@�C���p�X
#define CLEAR_BGM_PATH "Data/Sound/BGM/ClearBGM.mp3"

// �T�E���h�֘A
int ClearBGMSoundHndl = 0;

// �N���A�摜�̃n���h��
int bgClearHandle;

//---------------------------------
//		����������
//---------------------------------
void InitClear()
{
	// ���ʉ��ǂݍ���
	ClearBGMSoundHndl = LoadSoundMem(CLEAR_BGM_PATH);

	// �N���A�w�i������
	bgClearHandle = LoadGraph(BG_CLEAR_PATH);

	// BGM
	PlaySoundMem(ClearBGMSoundHndl, DX_PLAYTYPE_LOOP, true);

	// �N���A���[�v��
	g_CurrentSceneID = SCENE_ID_LOOP_CLEAR;
}

//---------------------------------
//		�X�V����
//---------------------------------
void StepClear()
{
	// Enter�L�[�����ꂽ�Ȃ�
	if (IsKeyPush(KEY_INPUT_RETURN) == 1) {
		// �v���C�V�[���ֈړ�
		g_CurrentSceneID = SCENE_ID_FIN_CLEAR;
		// �T�E���h���~�߂�
		StopSoundMem(ClearBGMSoundHndl);
	}
}

//---------------------------------
//		�`�揈��
//---------------------------------
void DrawClear()
{
	// �N���A�w�i�摜�̕`��
	DrawGraph(0, 0, bgClearHandle, true);
}

//---------------------------------
//		�I������
//---------------------------------
void FinClear()
{
	// �N���A�摜�j��
	DeleteGraph(bgClearHandle);

	// ���ʉ��j��
	DeleteSoundMem(ClearBGMSoundHndl);

	// �^�C�g���V�[����������
	g_CurrentSceneID = SCENE_ID_INIT_TITLE;
}