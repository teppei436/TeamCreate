
#include "DxLib.h"
#include "Person.h"
#include "../Common/Common.h"
#include "../Effect/Effect.h"
#include "../Enemy/Enemy.h"
#include "../Input/Input.h"
#include "../Scene/ScenePlay.h"

PersonData g_personData;

// 移動パターン
int Person_move_pattern;

// 移動速度
float PersonSpd;

// 時間
float Person_time;

//---------------------------------
//		初期化処理
//---------------------------------
void InitPerson()
{
	g_personData.pos.x    = PERSON_INIT_X;
	g_personData.pos.y    = PERSON_INIT_Y;
	g_personData.m_dir    = DIR_RIGHT_PERSON;
	g_personData.hp       = PERSON_HP;
	g_personData.animCnt  = 0;
	g_personData.isAlive  = true;
	g_personData.isDamage = false;

	// 移動パターン初期化
	Person_move_pattern = 1;

	// 移動速度初期化
	PersonSpd = ENEMY_SPD;

	// 時間初期化
	Person_time = 0;
}

//---------------------------------
//		終了処理
//---------------------------------
void FinPerson()
{
	// 画像データの破棄
	for (int i = 0; i < PERSON_GRAPH_NUM; i++) {
		if (g_personData.hndl[i] == -1) {
			DeleteGraph(g_personData.hndl[i]);
			g_personData.hndl[i] = -1;
		}
	}
}

//---------------------------------
//		マップチップ画像の読込み
//---------------------------------
void LoadPersonGraph()
{
	// 一枚の画像を分割ロード　エラーなら「ret」に-1が入る
	int ret = LoadDivGraph(PERSON_PATH, PERSON_GRAPH_NUM,
		PERSON_GRAPH_X, PERSON_GRAPH_Y, PERSON_SIZE, PERSON_SIZE, g_personData.hndl);
	int ret1 = LoadDivGraph(PERSON_DAMAGE_PATH, PERSON_GRAPH_NUM,
		PERSON_GRAPH_X, PERSON_GRAPH_Y, PERSON_SIZE, PERSON_SIZE, g_personData.hndl_damage);
}


//---------------------------------
//		更新処理
//---------------------------------
void StepPerson()
{
	// 時間更新
	Person_time += 1.0f / FRAME_RATE;

	// 移動パターン
	switch (Person_move_pattern) {

	case 1:

		if (Person_time >= 7.0f && Person_time <= 8.0f) {
			// パターン移動
			Person_move_pattern = 2;
		}

		if (Person_time >= 22.0f && Person_time <= 23.0f) {
			// パターン移動
			Person_move_pattern = 3;
		}

		break;

	case 2:

		if (g_personData.pos.x > 480) {
			g_personData.pos.x = g_personData.pos.x - 0.6f;
		}
		else {
			// パターン移動
			Person_move_pattern = 1;
		}

		break;

	case 3:

		if (g_personData.pos.x < 880) {
			g_personData.pos.x = g_personData.pos.x + 0.6f;
		}
		else {
			// パターン移動
			Person_move_pattern = 4;
		}

		break;

	case 4:

		if (g_personData.pos.x > PERSON_INIT_X) {
			g_personData.pos.x -= 0.6f;
		}
		else {
			// パターン移動
			Person_move_pattern = 5;
		}

		break;

	default:
		break;
	}
	// アニメーションのカウント更新
	g_personData.animCnt++;

	// アニメーションをループ
	if (g_personData.animCnt >= ANIM_PERSON_COUNT * 4) {
		g_personData.animCnt = 0;
	}

	// HPが0以下になったら死ぬ
	if (g_personData.isAlive) {
		if (g_personData.hp <= 0) {
			g_personData.isAlive = false;
		}
	}
}

//---------------------------------
//		描画処理
//---------------------------------
void DrawPerson()
{
	int animNum[] = { 0, 1, 2, 3 };
	int animID = g_personData.m_dir * PERSON_GRAPH_X + animNum[g_personData.animCnt / ANIM_PERSON_COUNT];

	if (g_personData.isDamage) {
		DrawRotaGraph((int)g_personData.pos.x, (int)g_personData.pos.y, 1.0, 0.0, g_personData.hndl_damage[animID], TRUE);
		g_personData.isDamage = false;
	}
	else {
		DrawRotaGraph((int)g_personData.pos.x, (int)g_personData.pos.y, 1.0, 0.0, g_personData.hndl[animID], TRUE);
	}
}

//プレイヤー取得
PersonData* GetPersonData()
{
	return &g_personData;
}