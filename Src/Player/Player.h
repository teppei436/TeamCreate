
#ifndef _PLAYER_H_
#define _PLAYER_H_

// 定義関連-------------------------------------------

#define PLAYER_SIZE	     (64) // プレイヤーの縦横サイズ
#define PLAYER_GRAPH_NUM (15) // プレイヤーの画像枚数
#define PLAYER_GRAPH_X	 (5)  // プレイヤーの画像枚数(横)
#define PLAYER_GRAPH_Y	 (3)  // プレイヤーの画像枚数(縦)
#define ANIM_COUNT		 (8)  // このカウント分待って次の画像へ

static const char PLAYER_PATH[] = "Data/Character/Player.png";

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
	PLAYER_SPD_FAST = 4,   // 移動速め
	PLAYER_SPD      = 3,   // 移動通常
	PLAYER_SPD_SLOW = 1,   // 移動遅め
	PLAYER_H        = 64,  // 縦幅
	PLAYER_W        = 32,  // 横幅
	PLAYER_RADIUS   = 32,  // 半径
};

// プレイヤーデータの構造体
struct PlayerData {
	VECTOR pos;		                     // 座標
	VECTOR move;	                     // 移動量
	int m_dir;					         // プレイヤーの向き
	int hndl[PLAYER_GRAPH_NUM];          // マップチップの画像
	int animCnt;				         // アニメーションの際に使用
}; extern PlayerData g_playerData;
//----------------------------------------------------

// 初期化処理
void InitPlayer();

// 終了処理
void FinPlayer();

// プレイヤー画像の読込み
void LoadPlayerGraph();

// 更新処理
void StepPlayer();

// プレイヤーの描画
void DrawPlayer();

// プレイヤー取得
PlayerData* GetPlayerData();

#endif 