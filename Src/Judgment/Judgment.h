
#ifndef _JUDGMENT_H_
#define _JUDGMENT_H_

// SEファイルパス
#define DAMAGE_SE_PATH "Data/Sound/SE/DamageSE.wav"
#define GET_SE_PATH    "Data/Sound/SE/GetSE.wav"

// インターバル
enum {
	DAMAGE_INTERVAL = 20, // ダメージのインターバル
};

// 初期化処理
void InitJudgment();

// 更新処理
void StepJudgment();

//終了処理
void FinJudgment();

// ダメージ処理
void AddDamage(int damage);

#endif