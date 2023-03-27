
#ifndef _ENEMY_H_
#define _ENEMY_H_

// 定義関連-------------------------------------------
#define ENEMY_SIZE		       (128) // エネミーの縦横サイズ
#define ENEMY_GRAPH_NUM	       (8)   // エネミーの画像枚数
#define ENEMY_GRAPH_X	       (4)	 // エネミーの画像枚数(横)
#define ENEMY_GRAPH_Y          (2)	 // エネミーの画像枚数(縦)
#define ENEMY_BULLET_SIZE      (24)  // バレットの縦横サイズ
#define ENEMY_BULLET_GRAPH_NUM (8)   // バレットの画像枚数
#define ENEMY_BULLET_GRAPH_X   (4)	 // バレットの画像枚数(横)
#define ENEMY_BULLET_GRAPH_Y   (2)	 // バレットの画像枚数(縦)
#define ANIM_ENEMY_COUNT       (10)  // このカウント分待って次の画像へ

static const char ENEMY_PATH[]        = "Data/Character/Enemy.png";
static const char ENEMY_BULLET_PATH[] = "Data/Character/EnemyBullet.png";

extern int Enemy_move_pattern;

// エネミーの情報
enum EnemyInfo {
	ENEMY_INIT_X = 650, // 初期X座標
	ENEMY_INIT_Y = 80,  // 初期Y座標
	ENEMY_H      = 128, // 縦幅
	ENEMY_W      = 128, // 横幅
	ENEMY_RADIUS = 64,  // 半径
	ENEMY_HP     = 12,  // ヒットポイント
	ENEMY_SPD    = 3,   // 速度
};
// エネミーの進行方向
enum {
	DIR_LEFT,  // 左方向
	DIR_RIGHT, // 右方向
};
// エネミーバレットの情報
enum GragonEnemyBulletInfo {
	ENEMY_BULLET_MAX_NUM  = 100, // 最大数（ハンドルの数）
	ENEMY_BULLET_INIT_X   = 650, // 初期X座標
	ENEMY_BULLET_INIT_Y   = 20,  // 初期Y座標
	ENEMY_BULLET_H        = 24,  // 縦幅
	ENEMY_BULLET_W        = 24,  // 横幅
	ENEMY_BULLET_RADIUS   = 12,  // 半径
	ENEMY_BULLET_INTERVAL = 60,  // 間隔ループ数
	ENEMY_BULLET_SPD      = 10,  // 速度
};

// エネミーデータを管理する構造体
struct EnemyData {
	VECTOR pos;		                  // 座標
	VECTOR move;	                  // 移動量
	int animCnt;                      // アニメーションの際に使用
	int m_dir;					      // プレイヤーの向き
	int hndl[ENEMY_GRAPH_NUM];        // マップチップの画像
	int bulletInterval;               // 発射間隔
}; extern EnemyData g_EnemyData;

// エネミーバレットデータを管理する構造体
struct EnemyBulletData {
	VECTOR pos;                       // 座標
	VECTOR move;	                  // 移動量
	int animCnt;                      // アニメーションの際に使用
	int hndl[ENEMY_BULLET_GRAPH_NUM]; // マップチップの画像
	bool isUse;                       // 使用中フラグ
}; extern EnemyBulletData g_EnemyBulletData[ENEMY_BULLET_MAX_NUM];

//----------------------------------------------------

// 初期化処理
void InitEnemy();

// 終了処理
void FinEnemy();

// エネミー画像の読込み
void LoadEnemyGraph();

// 更新処理
void StepEnemy();

// プレイヤーの描画
void DrawEnemy();

// プレイヤー取得
EnemyData* GetEnemyData();

// 弾を発射する
void FireBullet(VECTOR pos, VECTOR move);

#endif 