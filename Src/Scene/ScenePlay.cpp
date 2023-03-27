
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

// BGMファイルパス
#define PLAY_BGM_PATH "Data/Sound/BGM/PLAY_BGM.mp3"


// サウンド関連
int PlayBGMSoundHndl = 0;

// 背景関連
int BgHndl[2] = { 0 };
int BgX[2]    = { 0 };

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
		BgHndl[i] = LoadGraph(BG_PATH);
	}
	//背景初期座標設定
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
	for (int i = 0; i < 2; i++) {
		BgX[i] -= 1;
	}

	//背景が下にはみ出た時の処理
	for (int i = 0; i < 2; i++) {
		//添え字の画像がはみ出た
		if (BgX[i] + WINDOW_WIDTH < 0) {
			//上に戻す画像の添え字変数
			int upIndex = 0;

			//はみ出た画像が添え字0番なら
			if (i == 0)
				upIndex = 1; //上に戻すのは添え字1

			//上に戻す（もう一つの画像より
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
	// クリア確認
	bool isClear = false;

	// クリアしたなら
	if (Enemy_move_pattern == 13) {
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
	//背景を一番最初に描く
	for (int i = 0; i < 2; i++)
		DrawGraph(BgX[i], 0, BgHndl[i], true);
	
	DrawEnemy();
	DrawPerson();
	DrawPlayer();
	DrawScore();

	// 一番手前に描画
	DrawEffect();
	DrawHUD();
}

//---------------------------------
//		終了処理
//---------------------------------
void FinPlay()
{
	FinEnemy();
	FinHUD();
	FinJudgment();
	FinPerson();
	FinPlayer();
	ExitScore();

	// 効果音破棄
	DeleteSoundMem(PlayBGMSoundHndl);
	

	// 背景画像破棄
	for (int i = 0; i < 2; i++)
	{
		DeleteGraph(BgHndl[i]);
	}

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