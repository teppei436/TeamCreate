
#include "DxLib.h"
#include "Scene.h"
#include "SceneGameOver.h"
#include "../Input/Input.h"
#include "../Score/Score.h"

// ゲームオーバー背景画像のパス
#define BG_GAMEOVER_PATH "Data/Background/BgGameOver.png"

// BGMファイルパス
#define GAMEOVER_BGM_PATH "Data/Sound/BGM/GameOverBGM.mp3"

// サウンド関連
int GameOverBGMSoundHndl = 0;
// ゲームオーバー画像のハンドル
int bgGameOverHandle;

//---------------------------------
//		初期化処理
//---------------------------------
void InitGameOver()
{
	// 効果音読み込み
	GameOverBGMSoundHndl = LoadSoundMem(GAMEOVER_BGM_PATH);

	// ゲームオーバー背景初期化
	bgGameOverHandle = LoadGraph(BG_GAMEOVER_PATH);

	// BGM
	PlaySoundMem(GameOverBGMSoundHndl, DX_PLAYTYPE_LOOP, true);

	// ゲームオーバーループへ
	g_CurrentSceneID = SCENE_ID_LOOP_GAMEOVER;
}

//---------------------------------
//		更新処理
//---------------------------------
void StepGameOver()
{
	// 左右同時押しされたなら
	if (IsKeyPush(KEY_INPUT_LEFT) == 1 && IsKeyPush(KEY_INPUT_RIGHT) == 1) {
		// クリア後処理へ
		g_CurrentSceneID = SCENE_ID_FIN_GAMEOVER;
		// サウンド
		StopSoundMem(GameOverBGMSoundHndl);
	}
}

//---------------------------------
//		描画処理
//---------------------------------
void DrawGamrOver()
{
	// ゲームオーバー背景画像の描画
	DrawGraph(0, 0, bgGameOverHandle, true);
}

//---------------------------------
//		終了処理
//---------------------------------
void FinGameOver()
{
	ExitScore();

	// タイトルシーン初期化へ
	g_CurrentSceneID = SCENE_ID_INIT_TITLE;
}