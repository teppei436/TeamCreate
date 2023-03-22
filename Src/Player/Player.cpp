
#include "DxLib.h"
#include "Player.h"
#include "../Common/Common.h"
#include "../Effect/Effect.h"
#include "../Enemy/Enemy.h"
#include "../Input/Input.h"
#include "../Scene/ScenePlay.h"

PlayerData g_playerData;

// サウンド関連

//---------------------------------
//		初期化処理
//---------------------------------
void InitAnimePlayer()
{
	// SE読み込み

	g_playerData.pos.x   = 640;
	g_playerData.pos.y   = 500;
	g_playerData.m_dir   = DIR_RIGHT_WALK;
	g_playerData.animCnt = 0;
}

//---------------------------------
//		終了処理
//---------------------------------
void FinAnimePlayer()
{
	// 画像データの破棄
	for (int i = 0; i < PLAYER_GRAPH_NUM; i++) {
		if (g_playerData.hndl[i] == -1) {
			DeleteGraph(g_playerData.hndl[i]);
			g_playerData.hndl[i] = -1;
		}
	}

	// 効果音破棄
}


//---------------------------------
//		マップチップ画像の読込み
//---------------------------------
void LoadPlayerGraph()
{
	// 一枚の画像を分割ロード　エラーなら「ret」に-1が入る
	int ret = LoadDivGraph(PLAYER_PATH, PLAYER_GRAPH_NUM,
		PLAYER_GRAPH_X, PLAYER_GRAPH_Y, PLAYER_SIZE, PLAYER_SIZE, g_playerData.hndl);
}


//---------------------------------
//		更新処理
//---------------------------------
void StepAnimePlayer()
{
	// キー入力による移動-------------------------
	// 右移動
	if (IsKeyDown(KEY_INPUT_RIGHT) == 1) {
		g_playerData.m_dir = DIR_RIGHT_WALK;

		// 通常スピード
		g_playerData.pos.x += PLAYER_SPD;
	}
	//---------------------------------------------

	// アニメーションのカウント更新
	g_playerData.animCnt++;

	// アニメーションをループ
	if (g_playerData.animCnt >= ANIM_COUNT * 4) {
		g_playerData.animCnt = 0;
	}
}

//---------------------------------
//		描画処理
//---------------------------------
void DrawAnimePlayer()
{
	int animNum[] = { 0, 1, 2, 3 };
	int animID = g_playerData.m_dir * PLAYER_GRAPH_X + animNum[g_playerData.animCnt / ANIM_COUNT];

	DrawRotaGraph((int)g_playerData.pos.x, (int)g_playerData.pos.y, 1.0, 0.0, g_playerData.hndl[animID], TRUE);
}

//プレイヤー取得
PlayerData* GetPlayerData()
{
	return &g_playerData;
}