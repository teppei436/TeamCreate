
#include "DxLib.h"
#include "../Effect/Effect.h"
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
int bgHandle = 0;

//---------------------------------
//		初期化処理
//---------------------------------
void InitPlay()
{
	// 効果音読み込み
	PlayBGMSoundHndl = LoadSoundMem(PLAY_BGM_PATH);

	// 背景初期化
	bgHandle = LoadGraph(BG_PATH);

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
	UpdateScore();

	//==========================
	// クリア確認
	bool isClear = false;

	// クリアしたなら
	/*if () {
		isClear = true;
	}*/

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
	/*if () {
		isGameOver = true;
	}*/

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
	// 背景が一番後ろ
	DrawGraph(0, 0, bgHandle, true);
	DrawScore();
}

//---------------------------------
//		終了処理
//---------------------------------
void FinPlay()
{
	ExitScore();

	// 効果音破棄
	DeleteSoundMem(PlayBGMSoundHndl);

	// 背景破棄
	if (bgHandle == -1) {
		DeleteGraph(bgHandle);
		bgHandle = -1;
	}

	// もし〇〇ために後処理へ来たなら
	//if () {
	//	// ゲームオーバーへ
	//	g_CurrentSceneID = SCENE_ID_INIT_GAMEOVER;
	//}
	//else {
	//	// クリアへ
	//	g_CurrentSceneID = SCENE_ID_INIT_CLEAR;
	//}
}