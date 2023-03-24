
#include "DxLib.h"
#include "../Common/Common.h"
#include "../Effect/Effect.h"
#include "../Enemy/Enemy.h"
#include "../Judgment/Judgment.h"
#include "../Person/Person.h"
#include "../Player/Player.h"
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
int bgHandle[2] = { 0 }; //�w�i�摜�n���h��
int bgX[2] = { 0 };      //�w�i�摜X���W

//---------------------------------
//		����������
//---------------------------------
void InitPlay()
{
	// ���ʉ��ǂݍ���
	PlayBGMSoundHndl = LoadSoundMem(PLAY_BGM_PATH);

	// �w�i������
	for (int i = 0; i < 2; i++)
	{
		bgHandle[i] = LoadGraph(BG_PATH);
	}
	//�w�i�������W�ݒ�
	bgX[0] = 0;
	bgX[1] = -WINDOW_WIDTH;
	
	InitEffect();
	InitEnemy();
	LoadEnemyGraph();
	InitJudgment();
	InitPerson();
	LoadPersonGraph();
	InitPlayer();
	LoadPlayerGraph();
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
	//�w�i�̈ړ�����
	for (int i = 0; i < 2; i++)
	{
		bgX[i] +=3;
	}
	//�w�i����ʊO�ɂ͂ݏo�������̏���
	for (int i = 0; i < 2; i++)
	{
		//�Y�����̉摜���͂ݏo��
		if (bgX[i] > WINDOW_WIDTH)
		{
			//��ɖ߂��摜�̓Y����
			int upIndex = i == 0 ? 1 : 0;
			//������̉摜����ɖ߂�
			bgX[i] = bgX[upIndex] - WINDOW_WIDTH;

		}
	}



	StepEffect();
	StepEnemy();
	StepJudgment();
	StepPerson();
	StepPlayer();
	UpdateScore();

	//==========================
	// �N���A�m�F
	bool isClear = false;

	// �N���A�����Ȃ�
	if (0) {
		isClear = true;
	}

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
	if (!g_personData.isAlive) {
		isGameOver = true;
	}

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
	// �w�i����Ԍ��ɕ`��
	for (int i = 0; i < 2; i++)
	{
		DrawGraph(bgX[i],0, bgHandle[i], true);
	}
	
	
	DrawEnemy();
	DrawPerson();
	DrawPlayer();
	DrawScore();

	// �G�t�F�N�g����Ԏ�O�ɕ`��
	DrawEffect();
}

//---------------------------------
//		�I������
//---------------------------------
void FinPlay()
{
	FinEnemy();
	FinJudgment();
	FinPerson();
	FinPlayer();
	ExitScore();

	// ���ʉ��j��
	DeleteSoundMem(PlayBGMSoundHndl);

	// �w�i�j��
	/*if (bgHandle[0] == -1) {
		DeleteGraph(bgHandle[0]);
		bgHandle[0] = -1;
	}*/

	 //�������񂾂��߂Ɍ㏈���֗����Ȃ�
	if (!g_personData.isAlive) {
		// �Q�[���I�[�o�[��
		g_CurrentSceneID = SCENE_ID_INIT_GAMEOVER;
	}
	else {
		// �N���A��
		g_CurrentSceneID = SCENE_ID_INIT_CLEAR;
	}
}