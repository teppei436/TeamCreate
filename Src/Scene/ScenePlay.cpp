
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

// BGMファイルパス
#define PLAY_BGM_PATH "Data/Sound/BGM/PlayBGM.mp3"

// サウンド関連
int PlayBGMSoundHndl = 0;

// 背景関連
int bgHandle[2] = { 0 }; //背景画像ハンドル
int bgX[2] = { 0 };      //背景画像X座標

//---------------------------------
//		初期化処理
//---------------------------------
void InitPlay()
{
	// 効果音読み込み
	PlayBGMSoundHndl = LoadSoundMem(PLAY_BGM_PATH);

	// 背景初期化
	for (int i = 0; i < 2; i++)
	{
		bgHandle[i] = LoadGraph(BG_PATH);
	}
	//背景初期座標設定
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

	//エフェクトの読み込み
	LoadEffect(EFFECT_TYPE_EXPLOSION, 10);

	// BGM
	PlaySoundMem(PlayBGMSoundHndl, DX_PLAYTYPE_LOOP, true);

	// タイトルループへ
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//---------------------------------
//		更新処理
//---------------------------------
void StepPlay()
{
	//背景の移動処理
	for (int i = 0; i < 2; i++)
	{
		bgX[i] +=3;
	}
	//背景が画面外にはみ出した時の処理
	for (int i = 0; i < 2; i++)
	{
		//添え字の画像がはみ出た
		if (bgX[i] > WINDOW_WIDTH)
		{
			//上に戻す画像の添え字
			int upIndex = i == 0 ? 1 : 0;
			//もう一つの画像より上に戻す
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
	// クリア確認
	bool isClear = false;

	// クリアしたなら
	if (0) {
		isClear = true;
	}

	if (isClear) {
		// クリアへ
		g_CurrentSceneID = SCENE_ID_FIN_PLAY;

		// サウンド
		StopSoundMem(PlayBGMSoundHndl);
	}

	//==========================
	// ゲームオーバー確認
	bool isGameOver = false;

	// プレイヤー死んだなら
	if (!g_personData.isAlive) {
		isGameOver = true;
	}

	if (isGameOver) {
		// ゲームオーバーへ
		g_CurrentSceneID = SCENE_ID_FIN_PLAY;

		// サウンド
		StopSoundMem(PlayBGMSoundHndl);
	}
}

//---------------------------------
//		描画処理
//---------------------------------
void DrawPlay()
{
	// 背景が一番後ろに描画
	for (int i = 0; i < 2; i++)
	{
		DrawGraph(bgX[i],0, bgHandle[i], true);
	}
	
	
	DrawEnemy();
	DrawPerson();
	DrawPlayer();
	DrawScore();

	// エフェクトが一番手前に描画
	DrawEffect();
}

//---------------------------------
//		終了処理
//---------------------------------
void FinPlay()
{
	FinEnemy();
	FinJudgment();
	FinPerson();
	FinPlayer();
	ExitScore();

	// 効果音破棄
	DeleteSoundMem(PlayBGMSoundHndl);

	// 背景破棄
	/*if (bgHandle[0] == -1) {
		DeleteGraph(bgHandle[0]);
		bgHandle[0] = -1;
	}*/

	 //もし死んだために後処理へ来たなら
	if (!g_personData.isAlive) {
		// ゲームオーバーへ
		g_CurrentSceneID = SCENE_ID_INIT_GAMEOVER;
	}
	else {
		// クリアへ
		g_CurrentSceneID = SCENE_ID_INIT_CLEAR;
	}
}