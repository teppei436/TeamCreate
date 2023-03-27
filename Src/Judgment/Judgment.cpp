
#include "DxLib.h"
#include "judgment.h"
#include "../Collision/Collision.h"
#include "../Effect/Effect.h"
#include "../Enemy/Enemy.h"
#include "../Person/Person.h"
#include "../Player/Player.h"
#include "../Score/Score.h"

// SEファイルパス
#define DAMEGE_SE_PATH "Data/Sound/SE/damage.wav"
#define DEFENSE_SE_PATH "Data/Sound/SE/defense.wav"



// サウンド関連
int DamageSESoundHndl;
int DefenseSESoundHndl;


// ダメージインターバル
int DamageInterval;

//---------------------------------
//		初期化処理
//---------------------------------
void InitJudgment()
{
	// インターバル初期化
	DamageInterval = 0;

	// SE初期化
	DamageSESoundHndl = 0;
	DefenseSESoundHndl = 0;

	// SE読み込み
	DamageSESoundHndl = LoadSoundMem(DAMEGE_SE_PATH);
	DefenseSESoundHndl = LoadSoundMem(DEFENSE_SE_PATH);
	
}

//---------------------------------
//		更新処理
//---------------------------------
void StepJudgment()
{
	// インターバル更新
	DamageInterval++;

	//----------------------------------------------
	//		プレイヤーとバレット
	//----------------------------------------------
	for (int weapon_index = 0; weapon_index < ENEMY_BULLET_MAX_NUM; weapon_index++) {
		if (g_EnemyBulletData[weapon_index].isUse == false)
			continue;
		// 矩形の当たり判定
		bool result = IsHitRect((int)g_EnemyBulletData[weapon_index].pos.x - ENEMY_BULLET_W / 2,
			(int)g_EnemyBulletData[weapon_index].pos.y - ENEMY_BULLET_H / 2,
			ENEMY_BULLET_W, ENEMY_BULLET_H, (int)g_playerData.pos.x - PLAYER_W / 2,
			(int)g_playerData.pos.y - PLAYER_H / 2, PLAYER_W, PLAYER_H);

		// 当たったなら
		if (result) {
			// エネミーバレットを消す
			g_EnemyBulletData[weapon_index].isUse = false;

			AddScore(100);
			

			if (DamageInterval > DAMAGE_INTERVAL) {
				
				// サウンド
				PlaySoundMem(DefenseSESoundHndl, DX_PLAYTYPE_BACK, true);

				// ダメージインターバルをリセット
				DamageInterval = 0;
			}
		}
	}

	//----------------------------------------------
    //		パーソンとバレット
    //----------------------------------------------
	for (int weapon_index = 0; weapon_index < ENEMY_BULLET_MAX_NUM; weapon_index++) {
		if (g_EnemyBulletData[weapon_index].isUse == false)
			continue;
		// 矩形の当たり判定
		bool result = IsHitRect((int)g_EnemyBulletData[weapon_index].pos.x - ENEMY_BULLET_W / 2,
			(int)g_EnemyBulletData[weapon_index].pos.y - ENEMY_BULLET_H / 2,
			ENEMY_BULLET_W, ENEMY_BULLET_H, (int)g_personData.pos.x - PLAYER_W / 2,
			(int)g_personData.pos.y - PLAYER_H / 2, PLAYER_W, PLAYER_H);

		// 当たったなら
		if (result) {
			// エネミーバレットを消す
			g_EnemyBulletData[weapon_index].isUse = false;
			
			// ダメージ処理
			AddDamage(1);

			// エフェクト
			PlayEffect(EFFECT_TYPE_EXPLOSION, (int)g_personData.pos.x, (int)g_personData.pos.y);

			if (DamageInterval > DAMAGE_INTERVAL) {
				// サウンド
				PlaySoundMem(DamageSESoundHndl, DX_PLAYTYPE_BACK, true);

				// ダメージインターバルをリセット
				DamageInterval = 0;
			}
		}
	}
}

//---------------------------------
//		終了処理
//---------------------------------
void FinJudgment()
{
	// 効果音破棄
	DeleteSoundMem(DamageSESoundHndl);
	DeleteSoundMem(DefenseSESoundHndl);

}

//---------------------------------
//		ダメージ処理
//---------------------------------
void AddDamage(int damage)
{
	// 引数分プレイヤーのHPを減らす
	g_personData.hp -= damage;

	// ダメージフラグを立てる
	g_personData.isDamage = true;
}
