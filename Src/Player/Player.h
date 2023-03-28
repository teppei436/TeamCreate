
#ifndef _PLAYER_H_
#define _PLAYER_H_

// 定義関連-------------------------------------------

#define PLAYER_PATH "Data/Character/Player.png"

// プレイヤーの進行方向
enum {
	DIR_LEFT_PLAYER,  // 左方向
	DIR_RIGHT_PLAYER, // 右方向
	DIR_FRONT_PLAYER, // 正面向
};

// プレイヤーの情報
enum PlayerInfo
{
	PLAYER_INIT_X   = 640, // 初期X座標
	PLAYER_INIT_Y   = 500, // 初期Y座標
	PLAYER_H        = 128, // 縦幅
	PLAYER_W        = 64,  // 横幅
	PLAYER_RADIUS   = 64,  // 半径
};

// プレイヤーデータの構造体
struct PlayerData {
	VECTOR pos;	// 座標
	int hndl;   // マップチップの画像
}; extern PlayerData g_playerData;
//----------------------------------------------------

// 初期化処理
void InitPlayer();

// 終了処理
void FinPlayer();

// 更新処理
void StepPlayer();

// プレイヤーの描画
void DrawPlayer();

// プレイヤー取得
PlayerData* GetPlayerData();

#endif 