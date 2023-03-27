
#include "DxLib.h"
#include "../Common/Common.h"
#include "Enemy.h"
#include "../Effect/Effect.h"
#include "../Math/Math.h"
#include "../Person/Person.h"
#include "../Player/Player.h"
#include "../Scene/ScenePlay.h"

// SEファイルパス
#define BULLET_SE_PATH "Data/Sound/SE/bullet.wav"

EnemyData       g_EnemyData;
EnemyBulletData g_EnemyBulletData[ENEMY_BULLET_MAX_NUM] = { 0 };

// 移動パターン
int Enemy_move_pattern;

// 移動速度
float EnemySpd;

// 時間
float Enemy_time;

// サウンド関連
int bulletSESoundHndl = 0;

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

	// 効果音読み込み
	bulletSESoundHndl = LoadSoundMem(BULLET_SE_PATH);

	// 移動パターン初期化
	Enemy_move_pattern = 1;

	// 移動速度初期化
	EnemySpd = ENEMY_SPD;

	// 時間初期化
	Enemy_time = 0;
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

	DeleteSoundMem(bulletSESoundHndl);
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

	// 移動パターンの制限
	if (Enemy_move_pattern != 3 && Enemy_move_pattern != 7 && Enemy_move_pattern != 12) {
		if (Enemy_move_pattern != 4 && Enemy_move_pattern != 8) {
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
		}
		else {
			// 弾を飛ばすために：処理①
			//発射間隔の時間が経った
			if (g_EnemyData.bulletInterval > ENEMY_BULLET_INTERVAL - 50) {
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

	// 時間更新
	Enemy_time += 1.0f / FRAME_RATE;

	// エネミーの移動パターン
	switch (Enemy_move_pattern) {

	case 1:

		if (g_EnemyData.pos.x < WINDOW_WIDTH - 280) {
			g_EnemyData.pos.x += EnemySpd;
			EnemySpd = EnemySpd + 0.1f;
		}
		else {
			EnemySpd = ENEMY_SPD;
			// パターン移動
			Enemy_move_pattern = 2;
		}

		if (Enemy_time >= 7.0f && Enemy_time <= 8.0f) {
			// パターン移動
			Enemy_move_pattern = 3;
		}

		break;

	case 2:

		if (g_EnemyData.pos.x > 280) {
			g_EnemyData.pos.x -= EnemySpd;
			EnemySpd = EnemySpd + 0.1f;
		}
		else {
			EnemySpd = ENEMY_SPD;
			// パターン移動
			Enemy_move_pattern = 1;
		}

		if (Enemy_time >= 22.0f && Enemy_time <= 23.0f) {
			// パターン移動
			Enemy_move_pattern = 7;
		}

		if (Enemy_time >= 42.0f && Enemy_time <= 43.0f) {
			// パターン移動
			Enemy_move_pattern = 11;
		}

		break;

	case 3:

		if (g_EnemyData.pos.x < 1400) {
			g_EnemyData.pos.x += EnemySpd;
		}
		else {
			// パターン移動
			Enemy_move_pattern = 4;
		}

		break;

	case 4:

		if (g_EnemyData.pos.x > -280) {
			g_EnemyData.pos.x -= EnemySpd;
		}
		else {
			// パターン移動
			Enemy_move_pattern = 5;
		}

		break;

	case 5:

		g_EnemyData.pos.x = ENEMY_INIT_X;
		g_EnemyData.pos.y = -280;

		if (g_EnemyData.pos.y == -280) {
			// パターン移動
			Enemy_move_pattern = 6;
		}

		break;

	case 6:

		if (g_EnemyData.pos.y < ENEMY_INIT_Y) {
			g_EnemyData.pos.y++;
		}
		else {
			// パターン移動
			Enemy_move_pattern = 1;
		}

		break;

	case 7:

		if (g_EnemyData.pos.x > -120) {
			g_EnemyData.pos.x -= EnemySpd;
		}
		else {
			// パターン移動
			Enemy_move_pattern = 8;
		}

		break;

	case 8:

		if (g_EnemyData.pos.x < 1560) {
			g_EnemyData.pos.x += EnemySpd;
		}
		else {
			// パターン移動
			Enemy_move_pattern = 9;
		}

		break;

	case 9:

		g_EnemyData.pos.x = ENEMY_INIT_X;
		g_EnemyData.pos.y = -280;

		if (g_EnemyData.pos.y == -280) {
			// パターン移動
			Enemy_move_pattern = 10;
		}

		break;

	case 10:

		if (g_EnemyData.pos.y < ENEMY_INIT_Y) {
			g_EnemyData.pos.y++;
		}
		else {
			// パターン移動
			Enemy_move_pattern = 1;
		}

		break;

	case 11:

		if (g_EnemyData.pos.x > ENEMY_INIT_X) {
			g_EnemyData.pos.x--;
		}
		else {
			// パターン移動
			Enemy_move_pattern = 12;
		}

		break;

	case 12:

		if (Enemy_time >= 48.0f && Enemy_time <= 49.0f) {
			// パターン移動
			Enemy_move_pattern = 13;
		}

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

	unsigned int color = GetColor(255, 0, 255);
	DrawFormatString(10, 70, color, "経過時間[%.2f]", Enemy_time);
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
	//効果音
	PlaySoundMem(bulletSESoundHndl, DX_PLAYTYPE_BACK, true);
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