
#include "DxLib.h"
#include "Player.h"
#include "../Common/Common.h"
#include "../Effect/Effect.h"
#include "../Enemy/Enemy.h"
#include "../Input/Input.h"
#include "../Scene/ScenePlay.h"

PlayerData g_playerData;

//---------------------------------
//		初期化処理
//---------------------------------
void InitPlayer()
{
	g_playerData.pos.x   = PLAYER_INIT_X;
	g_playerData.pos.y   = PLAYER_INIT_Y;
	g_playerData.m_dir   = DIR_FRONT_PLAYER;
	g_playerData.animCnt = 0;
}

//---------------------------------
//		終了処理
//---------------------------------
void FinPlayer()
{
	// 画像データの破棄
	for (int i = 0; i < PLAYER_GRAPH_NUM; i++) {
		if (g_playerData.hndl[i] == -1) {
			DeleteGraph(g_playerData.hndl[i]);
			g_playerData.hndl[i] = -1;
		}
	}
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
void StepPlayer()
{
	g_playerData.m_dir = DIR_FRONT_PLAYER;

	// キー入力による移動-------------------------
	// 右移動
	if (IsKeyDown(KEY_INPUT_RIGHT) == 1) {
		g_playerData.m_dir = DIR_RIGHT_PLAYER;

		// 通常スピード
		g_playerData.pos.x += PLAYER_SPD;
	}

	// 左移動
	if (IsKeyDown(KEY_INPUT_LEFT) == 1) {
		g_playerData.m_dir = DIR_LEFT_PLAYER;

		// 通常スピード
		g_playerData.pos.x -= PLAYER_SPD;
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
void DrawPlayer()
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