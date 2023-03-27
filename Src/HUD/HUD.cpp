
#include "DxLib.h"
#include "HUD.h"
#include "../Enemy/Enemy.h"
#include "../Input/Input.h"
#include "../judgment/judgment.h"
#include "../Person/Person.h"

HeartHUD_Data  g_heartHUD_Data[HEART_HUD_MAX_NUM] = { 0 };

//---------------------------------
//		初期化処理
//---------------------------------
void InitHUD()
{
	// 体力表示HUD初期化
	for (int index = 0; index < HEART_HUD_MAX_NUM; index++) {
		g_heartHUD_Data[index].hndl = LoadGraph(HEART_HUD);
		g_heartHUD_Data[index].pos.x = index * 50.0f;
		g_heartHUD_Data[index].pos.y = HEART_HUD_INIT_Y;
	}
}

//---------------------------------
//		更新処理
//---------------------------------
void StepHUD()
{

}

//---------------------------------
//		描画処理
//---------------------------------
void DrawHUD()
{
	// 体力表示HUDの画像描画
	for (int index = 0; index < g_personData.hp; index++) {
		DrawGraph((int)g_heartHUD_Data[index].pos.x, (int)g_heartHUD_Data[index].pos.y, g_heartHUD_Data[index].hndl, TRUE);
	}
}

//---------------------------------
//		終了処理
//---------------------------------
void FinHUD()
{
	// 画像データの破棄
	for (int index = 0; index < HEART_HUD_MAX_NUM; index++) {
		DeleteGraph(g_heartHUD_Data[index].hndl);
	}
}