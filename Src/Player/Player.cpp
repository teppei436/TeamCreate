
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

	g_playerData.hndl = LoadGraph(PLAYER_PATH);
}

//---------------------------------
//		終了処理
//---------------------------------
void FinPlayer()
{
	// 画像データの破棄
	DeleteGraph(g_playerData.hndl);
	
}

//---------------------------------
//		更新処理
//---------------------------------
void StepPlayer()
{
	// キー入力による移動-------------------------
	// 右移動
	if (IsKeyDown(KEY_INPUT_RIGHT) == 1) {
		// 通常スピード
		g_playerData.pos.x += PLAYER_SPD;
	}

	// 左移動
	if (IsKeyDown(KEY_INPUT_LEFT) == 1) {
		// 通常スピード
		g_playerData.pos.x -= PLAYER_SPD;
	}

	//---------------------------------------------
}

//---------------------------------
//		描画処理
//---------------------------------
void DrawPlayer()
{
	DrawRotaGraph((int)g_playerData.pos.x, (int)g_playerData.pos.y, 1.0, 0.0, g_playerData.hndl, TRUE);
}

//プレイヤー取得
PlayerData* GetPlayerData()
{
	return &g_playerData;
}