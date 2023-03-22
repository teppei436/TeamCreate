
#include "DxLib.h"
#include "Scene.h"
#include "SceneTitle.h"
#include "../Input/Input.h"

// �^�C�g���w�i�摜�̃p�X
#define BG_TITLE_PATH "Data/BackGround/BgTitle.png"

// ���ʉ��t�@�C���p�X
#define TITLE_BGM_PATH "Data/Sound/BGM/TitleBGM.mp3"

// �T�E���h�֘A
int TitleBGMSoundHndl = 0;

// �^�C�g���摜�̃n���h��
int bgTitleHandle = 0;

//---------------------------------
//		����������
//---------------------------------
void InitTitle()
{
	// ���ʉ��ǂݍ���
	TitleBGMSoundHndl = LoadSoundMem(TITLE_BGM_PATH);

	// �^�C�g���w�i������
	bgTitleHandle = LoadGraph(BG_TITLE_PATH);

	// TitleBGM
	PlaySoundMem(TitleBGMSoundHndl, DX_PLAYTYPE_LOOP, true);

	// �^�C�g�����[�v��
	g_CurrentSceneID = SCENE_ID_LOOP_TITLE;
}

//---------------------------------
//		�X�V����
//---------------------------------
void StepTitle()
{
	// Enter�L�[�����ꂽ�Ȃ�
	if (IsKeyPush(KEY_INPUT_RETURN) == 1) {
		// �v���C�V�[���ֈړ�
		g_CurrentSceneID = SCENE_ID_FIN_TITLE;
		// �T�E���h���~�߂�
		StopSoundMem(TitleBGMSoundHndl);
	}
}

//---------------------------------
//		�`�揈��
//---------------------------------
void DrawTitle()
{

}

//---------------------------------
//		�I������
//---------------------------------
void FinTitle()
{
	// �^�C�g���摜�j��
	DeleteGraph(bgTitleHandle);
	// TitleBGM�j��
	DeleteSoundMem(TitleBGMSoundHndl);
	// �^�C�g���̌�̓v���C��
	g_CurrentSceneID = SCENE_ID_INIT_PLAY;
}