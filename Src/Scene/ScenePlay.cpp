
#include "DxLib.h"
#include "Scene.h"
#include "SceneClear.h"
#include "SceneGameOver.h"
#include "ScenePlay.h"
#include "SceneTitle.h"
#include "../Common/Common.h"
#include "../Effect/Effect.h"
#include "../Enemy/Enemy.h"
#include "../HUD/HUD.h"
#include "../Judgment/Judgment.h"
#include "../Person/Person.h"
#include "../Player/Player.h"
#include "../Score/Score.h"

// BGM�t�@�C���p�X
#define PLAY_BGM_PATH "Data/Sound/BGM/PLAY_BGM.mp3"


// �T�E���h�֘A
int PlayBGMSoundHndl = 0;

// �w�i�֘A
int BgHndl[2] = { 0 };
int BgX[2]    = { 0 };

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
		BgHndl[i] = LoadGraph(BG_PATH);
	}
	//�w�i�������W�ݒ�
	BgX[0] = 0;
	BgX[1] = -WINDOW_WIDTH;

	InitEffect();
	InitEnemy();
	LoadEnemyGraph();
	InitHUD();
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
	for (int i = 0; i < 2; i++) {
		BgX[i] -= 1;
	}

	//�w�i�����ɂ͂ݏo�����̏���
	for (int i = 0; i < 2; i++) {
		//�Y�����̉摜���͂ݏo��
		if (BgX[i] + WINDOW_WIDTH < 0) {
			//��ɖ߂��摜�̓Y�����ϐ�
			int upIndex = 0;

			//�͂ݏo���摜���Y����0�ԂȂ�
			if (i == 0)
				upIndex = 1; //��ɖ߂��͓̂Y����1

			//��ɖ߂��i������̉摜���
			BgX[i] = BgX[upIndex] + WINDOW_WIDTH;
		}
	}
	

	StepEffect();
	StepEnemy();
	StepHUD();
	StepJudgment();
	StepPerson();
	StepPlayer();
	UpdateScore();

	//==========================
	// �N���A�m�F
	bool isClear = false;

	// �N���A�����Ȃ�
	if (Enemy_move_pattern == 13) {
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
	//�w�i����ԍŏ��ɕ`��
	for (int i = 0; i < 2; i++)
		DrawGraph(BgX[i], 0, BgHndl[i], true);
	
	DrawEnemy();
	DrawPerson();
	DrawPlayer();
	DrawScore();

	// ��Ԏ�O�ɕ`��
	DrawEffect();
	DrawHUD();
}

//---------------------------------
//		�I������
//---------------------------------
void FinPlay()
{
	FinEnemy();
	FinHUD();
	FinJudgment();
	FinPerson();
	FinPlayer();
	ExitScore();

	// ���ʉ��j��
	DeleteSoundMem(PlayBGMSoundHndl);
	

	// �w�i�摜�j��
	for (int i = 0; i < 2; i++)
	{
		DeleteGraph(BgHndl[i]);
	}

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