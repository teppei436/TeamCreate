
#ifndef _HUD_H_
#define _HUD_H_

// 定義関連-------------------------------------------

#define HEART_HUD "Data/HUD/Heart.png" // 体力HUDのパス

// 体力表示HUDの情報
enum HeartHUDInfo {
	HEART_HUD_INIT_X  = 10,  // 初期X座標
	HEART_HUD_INIT_Y  = 660, // 初期Y座標
	HEART_HUD_MAX_NUM = 10,  // 体力表示HUDの最大数
};

// 体力表示HUDデータの構造体
struct HeartHUD_Data {
	int hndl;   // 画像ハンドル
	VECTOR pos; // 座標
}; extern HeartHUD_Data g_heartHUD_Data[HEART_HUD_MAX_NUM];

// 初期化処理
void InitHUD();

// 更新処理
void StepHUD();

// 描画処理
void DrawHUD();

// 終了処理
void FinHUD();

#endif _HUD_H_