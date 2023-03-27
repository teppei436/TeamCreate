
#include "DxLib.h"
#include "Scene.h"
#include "SceneTitle.h"
#include "../Input/Input.h"

// タイトル背景画像のパス
#define BG_TITLE_PATH "Data/Background/BgTitle.png"

// 効果音ファイルパス
#define TITLE_BGM_PATH "Data/Sound/BGM/TITLE_BGM.mp3"

// サウンド関連
int TitleBGMSoundHndl = 0;

// タイトル画像のハンドル
int bgTitleHandle = 0;

//---------------------------------
//		初期化処理
//---------------------------------
void InitTitle()
{
	// 効果音読み込み
	TitleBGMSoundHndl = LoadSoundMem(TITLE_BGM_PATH);

	// タイトル背景初期化
	bgTitleHandle = LoadGraph(BG_TITLE_PATH);

	// TitleBGM
	PlaySoundMem(TitleBGMSoundHndl, DX_PLAYTYPE_LOOP, true);

	// タイトルループへ
	g_CurrentSceneID = SCENE_ID_LOOP_TITLE;
}

//---------------------------------
//		更新処理
//---------------------------------
void StepTitle()
{
	// 左右同時押しされたなら
	if (IsKeyPush(KEY_INPUT_LEFT) == 1 && IsKeyPush(KEY_INPUT_RIGHT) == 1) {
		// プレイシーンへ移動
		g_CurrentSceneID = SCENE_ID_FIN_TITLE;
		// サウンドを止める
		StopSoundMem(TitleBGMSoundHndl);
	}
}

//---------------------------------
//		描画処理
//---------------------------------
void DrawTitle()
{
	// タイトル背景画像の描画
	DrawGraph(0, 0, bgTitleHandle, true);
}

//---------------------------------
//		終了処理
//---------------------------------
void FinTitle()
{
	// タイトル画像破棄
	DeleteGraph(bgTitleHandle);
	// TitleBGM破棄
	DeleteSoundMem(TitleBGMSoundHndl);
	// タイトルの後はプレイへ
	g_CurrentSceneID = SCENE_ID_INIT_PLAY;
}