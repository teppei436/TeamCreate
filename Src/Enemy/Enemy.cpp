
#include "DxLib.h"
#include "Enemy.h"
#include "../Effect/Effect.h"
#include "../Math/Math.h"
#include "../Person/Person.h"
#include "../Player/Player.h"

EnemyData       g_EnemyData;
EnemyBulletData g_EnemyBulletData[ENEMY_BULLET_MAX_NUM] = { 0 };

// 移動パターン
int Enemy_move_pattern;

//---------------------------------
//		初期化処理
//---------------------------------
void InitEnemy()
{
	// エネミー初期化
	g_EnemyData.pos.x          = ENEMY_INIT_X;
	g_EnemyData.pos.y          = ENEMY_INIT_Y;
	g_EnemyData.m_dir          = 0;
	g_EnemyData.animCnt        = 0;
	g_EnemyData.bulletInterval = 0;


	// エネミー画像初期化
	for (int i = 0; i < ENEMY_GRAPH_NUM; i++) {
		g_EnemyData.hndl[i] = -1;
	}

	// エネミーバレット画像初期化
	for (int MaxIndex = 0; MaxIndex < ENEMY_BULLET_MAX_NUM; MaxIndex++) {
		g_EnemyBulletData[MaxIndex].isUse = false;
		for (int HndlIndex = 0; HndlIndex < ENEMY_BULLET_GRAPH_NUM; HndlIndex++) {
			g_EnemyBulletData[MaxIndex].hndl[HndlIndex] = -1;
		}
	}

	// 移動パターン初期化
	Enemy_move_pattern = 1;
}

//---------------------------------
//		終了処理
//---------------------------------
void FinEnemy()
{
	// 画像の破棄
	for (int i = 0; i < ENEMY_GRAPH_NUM; i++) {
		if (g_EnemyData.hndl[i] == -1) {
			DeleteGraph(g_EnemyData.hndl[i]);
			g_EnemyData.hndl[i] = -1;
		}
	}

	for (int HndlIndex = 0; HndlIndex < ENEMY_BULLET_GRAPH_NUM; HndlIndex++) {
		for (int MaxIndex = 0; MaxIndex < ENEMY_BULLET_MAX_NUM; MaxIndex++) {
			if (g_EnemyBulletData[MaxIndex].hndl[HndlIndex] == -1) {
				DeleteGraph(g_EnemyBulletData[MaxIndex].hndl[HndlIndex]);
				g_EnemyBulletData[MaxIndex].hndl[HndlIndex] = -1;
			}
		}
	}
}

//---------------------------------
//		マップチップ画像の読込み
//---------------------------------
void LoadEnemyGraph()
{
	// 一枚の画像を分割ロード　エラーなら「ret」に-1が入る
	int ret1 = LoadDivGraph(ENEMY_PATH, ENEMY_GRAPH_NUM,
		ENEMY_GRAPH_X, ENEMY_GRAPH_Y, ENEMY_SIZE, ENEMY_SIZE, g_EnemyData.hndl);

	for (int i = 0; i < ENEMY_BULLET_MAX_NUM; i++) {
		int ret2 = LoadDivGraph(ENEMY_BULLET_PATH, ENEMY_BULLET_GRAPH_NUM,
			ENEMY_BULLET_GRAPH_X, ENEMY_BULLET_GRAPH_Y, ENEMY_BULLET_SIZE, ENEMY_BULLET_SIZE, g_EnemyBulletData[i].hndl);
	}
}

//---------------------------------
//		更新処理
//---------------------------------
void StepEnemy()
{
	// 弾の発射間隔を更新
	g_EnemyData.bulletInterval++;

	// 弾を飛ばすために：処理①
	//発射間隔の時間が経った
	if (g_EnemyData.bulletInterval > ENEMY_BULLET_INTERVAL) {
		//ボスの弾情報を先頭から順番に回す
		for (int i = 0; i < ENEMY_BULLET_MAX_NUM; i++) {
			//未使用のボスの弾情報があった
			if (g_EnemyBulletData[i].isUse == false) {
				// バレットの移動量をこの変数に代入する
				VECTOR bullet_move = { 0 };

				// ①エネミーからプレイヤーまでのベクトルを作成
				bullet_move = VecCreate(g_EnemyData.pos, g_personData.pos);

				// ②作成したベクトルを正規化し、長さを1にする
				bullet_move = VecNormalize(bullet_move);

				// ③正規化したベクトルをBULLET_SPEEDでスカラー倍し、移動量とする
				bullet_move = VecScale(bullet_move, ENEMY_BULLET_SPD);

				//敵の弾の発射間隔をリセット
				g_EnemyData.bulletInterval = 0;

				// 発射
				FireBullet(g_EnemyData.pos, bullet_move);

				//ループを抜ける
				break;
			}
		}
	}
	
	//弾を飛ばすために：処理②
	//弾情報を先頭から順番に回す
	for (int i = 0; i < ENEMY_BULLET_MAX_NUM; i++) {
		//使用中の弾なら
		if (g_EnemyBulletData[i].isUse == true) {
			//X座標を更新
			g_EnemyBulletData[i].pos.x += g_EnemyBulletData[i].move.x;
			//Y座標を更新
			g_EnemyBulletData[i].pos.y += g_EnemyBulletData[i].move.y;
		}
	}

	int EnemySpd = ENEMY_SPD;

	// エネミーの移動パターン
	switch (Enemy_move_pattern) {

	case 1:

		break;

	case 2:

		break;

	case 3:

		break;

	default:
		break;
	}

	// アニメーションのカウント更新
	g_EnemyData.animCnt++;
	if (g_EnemyData.animCnt >= ANIM_ENEMY_COUNT * 4) {
		g_EnemyData.animCnt = 0;
	}
}

//---------------------------------
//		描画処理
//---------------------------------
void DrawEnemy()
{
	// アニメーション
	int animNum[] = { 0, 1, 2, 3 };
	int animEnemyID = g_EnemyData.m_dir * ENEMY_GRAPH_X + animNum[g_EnemyData.animCnt / ANIM_ENEMY_COUNT];

	// エネミーの描画
	DrawRotaGraph((int)g_EnemyData.pos.x, (int)g_EnemyData.pos.y, 1.0, 0.0, g_EnemyData.hndl[animEnemyID], TRUE);

	for (int index = 0; index < ENEMY_BULLET_MAX_NUM; index++) {
		if (g_EnemyBulletData[index].isUse) {
			DrawRotaGraph((int)g_EnemyBulletData[index].pos.x, (int)g_EnemyBulletData[index].pos.y, 1.0, 0.0, g_EnemyBulletData[index].hndl[animEnemyID], TRUE);
		}
	}
}

//---------------------------------
//		エネミー取得
//---------------------------------
EnemyData* GetEnemyData() {
	return &g_EnemyData;
}

//---------------------------------
//		敵の弾を発射する
//---------------------------------
void FireBullet(VECTOR pos, VECTOR move)
{
	EnemyBulletData* enemyBullet = g_EnemyBulletData;

	// 未使用の敵の弾を探す
	for (int i = 0; i < ENEMY_BULLET_MAX_NUM; i++, enemyBullet++) {
		// 未使用かどうか
		if (!enemyBullet->isUse) {
			// 基本情報を設定
			enemyBullet->isUse = true;
			enemyBullet->pos = pos;
			enemyBullet->move = move;

			break;
		}
	}
}