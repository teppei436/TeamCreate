
#include "DxLib.h"
#include "../Effect/Effect.h"
#include "Scene.h"
#include "SceneClear.h"
#include "SceneGameOver.h"
#include "ScenePlay.h"
#include "SceneTitle.h"
#include "../Score/Score.h"

// BGM�t�@�C���p�X
#define PLAY_BGM_PATH "Data/Sound/BGM/PlayBGM.mp3"

// �T�E���h�֘A
int PlayBGMSoundHndl = 0;

// �w�i�֘A
int bgHandle = 0;

//---------------------------------
//		����������
//---------------------------------
void InitPlay()
{
	// ���ʉ��ǂݍ���
	PlayBGMSoundHndl = LoadSoundMem(PLAY_BGM_PATH);

	// �w�i������
	bgHandle = LoadGraph(BG_PATH);

	InitScore();
	LoadScore();

	//�G�t�F�N�g�̓ǂݍ���
	LoadEffect(EFFECT_TYPE_EXPLOSION, 10);

	// BGM
	PlaySoundMem(PlayBGMSoundHndl, DX_PLAYTYPE_LOOP, true);

	// �^�C�g�����[�v��
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//---------------------------------
//		�X�V����
//---------------------------------
void StepPlay()
{
	UpdateScore();

	//==========================
	// �N���A�m�F
	bool isClear = false;

	// �N���A�����Ȃ�
	/*if () {
		isClear = true;
	}*/

	if (isClear) {
		// �N���A��
		g_CurrentSceneID = SCENE_ID_FIN_PLAY;

		// �T�E���h
		StopSoundMem(PlayBGMSoundHndl);
	}

	//==========================
	// �Q�[���I�[�o�[�m�F
	bool isGameOver = false;

	// �v���C���[���񂾂Ȃ�
	/*if () {
		isGameOver = true;
	}*/

	if (isGameOver) {
		// �Q�[���I�[�o�[��
		g_CurrentSceneID = SCENE_ID_FIN_PLAY;

		// �T�E���h
		StopSoundMem(PlayBGMSoundHndl);
	}
}

//---------------------------------
//		�`�揈��
//---------------------------------
void DrawPlay()
{
	// �w�i����Ԍ��
	DrawGraph(0, 0, bgHandle, true);
	DrawScore();
}

//---------------------------------
//		�I������
//---------------------------------
void FinPlay()
{
	ExitScore();

	// ���ʉ��j��
	DeleteSoundMem(PlayBGMSoundHndl);

	// �w�i�j��
	if (bgHandle == -1) {
		DeleteGraph(bgHandle);
		bgHandle = -1;
	}

	// �����Z�Z���߂Ɍ㏈���֗����Ȃ�
	//if () {
	//	// �Q�[���I�[�o�[��
	//	g_CurrentSceneID = SCENE_ID_INIT_GAMEOVER;
	//}
	//else {
	//	// �N���A��
	//	g_CurrentSceneID = SCENE_ID_INIT_CLEAR;
	//}
}