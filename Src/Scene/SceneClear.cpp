
#include "DxLib.h"
#include "Scene.h"
#include "SceneClear.h"
#include "../Input/Input.h"
#include "../Score/Score.h"

// クリア背景画像のパス
#define BG_CLEAR_PATH "Data/Background/BgClear.png"

// BGMファイルパス
#define CLEAR_BGM_PATH "Data/Sound/BGM/ClearBGM.mp3"

// サウンド関連
int ClearBGMSoundHndl = 0;

// クリア画像のハンドル
int bgClearHandle;

//---------------------------------
//		初期化処理
//---------------------------------
void InitClear()
{
	// 効果音読み込み
	ClearBGMSoundHndl = LoadSoundMem(CLEAR_BGM_PATH);

	// クリア背景初期化
	bgClearHandle = LoadGraph(BG_CLEAR_PATH);

	// BGM
	PlaySoundMem(ClearBGMSoundHndl, DX_PLAYTYPE_LOOP, true);

	// クリアループへ
	g_CurrentSceneID = SCENE_ID_LOOP_CLEAR;
}

//---------------------------------
//		更新処理
//---------------------------------
void StepClear()
{
	// 左右同時押しされたなら
	if (IsKeyPush(KEY_INPUT_LEFT) == 1 && IsKeyPush(KEY_INPUT_RIGHT) == 1) {
		// プレイシーンへ移動
		g_CurrentSceneID = SCENE_ID_FIN_CLEAR;
		// サウンドを止める
		StopSoundMem(ClearBGMSoundHndl);
	}
}

//---------------------------------
//		描画処理
//---------------------------------
void DrawClear()
{
	// クリア背景画像の描画
	DrawGraph(0, 0, bgClearHandle, true);

	DrawScore();
}

//---------------------------------
//		終了処理
//---------------------------------
void FinClear()
{
	// クリア画像破棄
	DeleteGraph(bgClearHandle);

	// 効果音破棄
	DeleteSoundMem(ClearBGMSoundHndl);

	ExitScore();

	// タイトルシーン初期化へ
	g_CurrentSceneID = SCENE_ID_INIT_TITLE;
}