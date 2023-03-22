
#ifndef __SCORE_H__
#define __SCORE_H__

// スコアの初期化
void InitScore();

// スコア画像のロード
void LoadScore();

// スコアの更新
void UpdateScore();

// スコアの描画
void DrawScore();

// スコア画像の破棄
void ExitScore();

// スコアを加算する
void AddScore(int score);

// スコアを強制的にセットする
void SetScore(int score);

// スコアを取得する
int GetScore();

#endif