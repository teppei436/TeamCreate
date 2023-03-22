
#include "DxLib.h"
#include "Scene.h"
#include "SceneGameOver.h"
#include "../Input/Input.h"

// �Q�[���I�[�o�[�w�i�摜�̃p�X
#define BG_GAMEOVER_PATH "Data/BackGround/BgGameOver.png"

// BGM�t�@�C���p�X
#define GAMEOVER_BGM_PATH "Data/Sound/BGM/GameOverBGM.mp3"

// �T�E���h�֘A
int GameOverBGMSoundHndl = 0;
// �Q�[���I�[�o�[�摜�̃n���h��
int bgGameOverHandle;

//---------------------------------
//		����������
//---------------------------------
void InitGameOver()
{
	// ���ʉ��ǂݍ���
	GameOverBGMSoundHndl = LoadSoundMem(GAMEOVER_BGM_PATH);

	// �Q�[���I�[�o�[�w�i������
	bgGameOverHandle = LoadGraph(BG_GAMEOVER_PATH);

	// BGM
	PlaySoundMem(GameOverBGMSoundHndl, DX_PLAYTYPE_LOOP, true);

	// �Q�[���I�[�o�[���[�v��
	g_CurrentSceneID = SCENE_ID_LOOP_GAMEOVER;
}

//---------------------------------
//		�X�V����
//---------------------------------
void StepGameOver()
{
	// Enter�L�[�����ꂽ�Ȃ�
	if (IsKeyPush(KEY_INPUT_RETURN) == 1) {
		// �N���A�㏈����
		g_CurrentSceneID = SCENE_ID_FIN_GAMEOVER;
		// �T�E���h
		StopSoundMem(GameOverBGMSoundHndl);
	}
}

//---------------------------------
//		�`�揈��
//---------------------------------
void DrawGamrOver()
{
	// �Q�[���I�[�o�[�w�i�摜�̕`��
	DrawGraph(0, 0, bgGameOverHandle, true);
}

//---------------------------------
//		�I������
//---------------------------------
void FinGameOver()
{
	// �^�C�g���V�[����������
	g_CurrentSceneID = SCENE_ID_INIT_TITLE;
}