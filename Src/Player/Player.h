
#ifndef _ANINATION_H_
#define _ANINATION_H_

// 定義関連-------------------------------------------

#define PLAYER_SIZE			(64)	// プレイヤーの縦横サイズ
#define PLAYER_GRAPH_NUM	(20)	// プレイヤーの画像枚数
#define PLAYER_GRAPH_X		(5)		// プレイヤーの画像枚数(横)
#define PLAYER_GRAPH_Y		(4)		// プレイヤーの画像枚数(縦)
#define ANIM_COUNT			(8)	    // このカウント分待って次の画像へ

static const char PLAYER_PATH[]        = "Data/Animation/AnimationPlayer.png";
static const char PLAYER_GOLD_PATH[]   = "Data/Animation/AnimationPlayerGold.png";
static const char PLAYER_DAMAGE_PATH[] = "Data/Animation/AnimationPlayer_damage.png";

// プレイヤーの進行方向
enum {
	DIR_LEFT_WALK,  // 左方向の歩行
	DIR_RIGHT_WALK, // 右方向の歩行
};

// プレイヤーの情報
enum PlayerInfo
{
	PLAYER_INIT_X   = 640, // 初期X座標
	PLAYER_INIT_Y   = 640, // 初期Y座標
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
void InitAnimePlayer();

// 終了処理
void FinAnimePlayer();

// プレイヤー画像の読込み
void LoadPlayerGraph();

// 更新処理
void StepAnimePlayer();

// プレイヤーの描画
void DrawAnimePlayer();

// プレイヤーの描画
void DrawAnimePlayer01();

// プレイヤー取得
PlayerData* GetPlayerData();

#endif 