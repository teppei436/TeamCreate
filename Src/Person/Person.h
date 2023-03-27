
#ifndef _PERSON_H_
#define _PERSON_H_

// 定義関連-------------------------------------------

#define PERSON_SIZE	      (64) // 縦横サイズ
#define PERSON_GRAPH_NUM  (15) // 画像枚数
#define PERSON_GRAPH_X	  (5)  // 画像枚数(横)
#define PERSON_GRAPH_Y	  (3)  // 画像枚数(縦)
#define ANIM_PERSON_COUNT (8)  // このカウント分待って次の画像へ

static const char PERSON_PATH[]        = "Data/Character/Person.png";
static const char PERSON_DAMAGE_PATH[] = "Data/Character/Person_damage.png";

// プレイヤーの進行方向
enum {
	DIR_LEFT_PERSON,  // 左方向
	DIR_RIGHT_PERSON, // 右方向
};

// プレイヤーの情報
enum PersonInfo
{
	PERSON_INIT_X   = 640, // 初期X座標
	PERSON_INIT_Y   = 640, // 初期Y座標
	PERSON_SPD_FAST = 4,   // 移動速め
	PERSON_SPD      = 3,   // 移動通常
	PERSON_SPD_SLOW = 1,   // 移動遅め
	PERSON_H        = 64,  // 縦幅
	PERSON_W        = 32,  // 横幅
	PERSON_RADIUS   = 32,  // 半径
	PERSON_HP       = 5,   // HP
};

// プレイヤーデータの構造体
struct PersonData {
	VECTOR pos;		                   // 座標
	VECTOR move;	                   // 移動量
	int m_dir;				           // 向き
	int hp;                            // HP
	int hndl[PERSON_GRAPH_NUM];        // マップチップの画像
	int hndl_damage[PERSON_GRAPH_NUM]; // マップチップの画像
	int animCnt;				       // アニメーションの際に使用
	bool isAlive;                      // 生存フラグ
	bool isDamage;                     // ダメージフラグ
}; extern PersonData g_personData;
//----------------------------------------------------

// 初期化処理
void InitPerson();

// 終了処理
void FinPerson();

// 画像の読込み
void LoadPersonGraph();

// 更新処理
void StepPerson();

// 描画
void DrawPerson();

// 取得
PersonData* GetPersonData();

#endif 