

#include "DxLib.h"	//DXライブラリのインクルード
#include "Common/Common.h"
#include "Input/Input.h"
#include "Scene/Scene.h"
#include "Scene/SceneClear.h"
#include "Scene/SceneGameOver.h"
#include "Scene/ScenePlay.h"
#include "Scene/SceneTitle.h"
#include "Score/Score.h"

// フレームレート情報
struct Frame_Rate_Info {
	int currentTime;
	int lastFrameTime;
	int count;
	int calcFpsTime;
	float fps;
};

// フレームレート情報変数
Frame_Rate_Info frameRateInfo;

// FPS計算
void CalcFPS();

// FPS表示（デバッグ用）
void DrawFPS();

// 現在のシーンID
int g_CurrentSceneID = SCENE_ID_INIT_TITLE;

// Win32アプリケーションは WinMain関数 から始まる
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//ウィンドウの状態を設定する
	ChangeWindowMode(true);

	//-----------------------------------------
	//一番最初に１回だけやる処理をここに書く

	//①DXライブラリの初期化
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	// ウィンドウの状態を設定する
	ChangeWindowMode(true);

	// 初期化とロードを一回だけ行う
	InitScore();
	LoadScore();

	// 入力初期化
	InitInput();

	// 一番最初に１回だけやる処理
	SetTransColor(255, 0, 255);	// 透過色指定

	// ウィンドウサイズを変更
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);

	// 描画するスクリーンを設定
	SetDrawScreen(DX_SCREEN_BACK); //描画するスクリーンを設定する

	//-----------------------------------------

	//ゲームメインループ
	while (ProcessMessage() != -1)
	{
		Sleep(1); // システムに処理を返す

		//-----------------------------------------
		//ここにゲームの本体を書くことになる
		//-----------------------------------------
		// 現在の時間を取得
		frameRateInfo.currentTime = GetNowCount();

		// 最初のループなら
		// 現在の時間を、FPSの計算をした時間に設定
		if (frameRateInfo.calcFpsTime == 0.0f) {
			frameRateInfo.calcFpsTime = frameRateInfo.currentTime;
			frameRateInfo.fps = (float)FRAME_RATE;
		}

		// 現在の時間が、前回のフレーム時より
		// 1000/60ミリ秒(1/60秒)以上経過していたら処理を実行する
		if (frameRateInfo.currentTime - frameRateInfo.lastFrameTime >= FRAME_TIME) {
			// フレーム実行時の時間を更新
			frameRateInfo.lastFrameTime = frameRateInfo.currentTime;

			// フレーム数をカウント
			frameRateInfo.count++;

			if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			{
				//エスケープキーが押されたら終了
				break;
			}

			//②画面に表示されたものを初期化
			ClearDrawScreen();

			// 入力ステップ
			StepInput();

			// シーンIDによって処理の振り分け
			switch (g_CurrentSceneID) {

			case SCENE_ID_INIT_TITLE: {
				// タイトル初期化
				InitTitle();
			}
			break;

			case SCENE_ID_LOOP_TITLE: {
				// タイトル通常処理
				StepTitle();

				// タイトル描画処理
				DrawTitle();
			}
			break;

			case SCENE_ID_FIN_TITLE: {
				// タイトル後処理
				FinTitle();
			}
			break;

			case SCENE_ID_INIT_PLAY: {
				// プレイ初期化
				InitPlay();
			}
			break;

			case SCENE_ID_LOOP_PLAY: {
				// プレイ通常処理
				StepPlay();

				// プレイ描画処理
				DrawPlay();
			}
			break;

			case SCENE_ID_FIN_PLAY: {
				// タイトル後処理
				FinPlay();
			}
		    break;

			case SCENE_ID_INIT_CLEAR: {
				// クリア初期化
				InitClear();
			}
			break;

			case SCENE_ID_LOOP_CLEAR: {
				// クリア通常処理
				StepClear();

				// クリア描画処理
				DrawClear();
			}
			break;

			case SCENE_ID_FIN_CLEAR: {
				// クリア後処理
				FinClear();
			}
			break;

			case SCENE_ID_INIT_GAMEOVER: {
				// ゲームオーバー初期化
				InitGameOver();
			}
			break;

			case SCENE_ID_LOOP_GAMEOVER: {
				// ゲームオーバー通常処理
				StepGameOver();

				// ゲームオーバー描画処理
				DrawGamrOver();
			}
			break;

			case SCENE_ID_FIN_GAMEOVER: {
				// ゲームオーバー後処理
				FinGameOver();
			}
			break;
			}

			//ループの終わりに
			// FPS計算
			CalcFPS();

			// FPS表示
			DrawFPS();

			//③フリップ関数
			ScreenFlip();
		}
	}

	//-----------------------------------------
	//最後に１回だけやる処理をここに書く

	//④DXライブラリの後処理
	DxLib_End();

	//-----------------------------------------

	return 0;
}

// FPS計算
void CalcFPS()
{
	// 前回のFPSを計算した時間からの経過時間を求める
	int difTime = frameRateInfo.currentTime - frameRateInfo.calcFpsTime;
	// 前回のFPSを計算した時間から
	// １秒以上経過していたらFPSを計算する
	if (difTime > 1000) {
		// フレーム回数をミリ秒に合わせる
		// 小数まで出したいのでfloatにキャスト
		float frameCount = (float)(frameRateInfo.count * 1000.0f);
		// FPSを求める
		// 理想の数値は 60000 / 1000 で 60 となる
		frameRateInfo.fps = frameCount / difTime;
		// フレームレートカウントをクリア
		frameRateInfo.count = 0;
		// FPSを計算した時間を更新
		frameRateInfo.calcFpsTime = frameRateInfo.currentTime;
	}
}

// FPS表示(デバッグ用)
void DrawFPS()
{
	unsigned int color = GetColor(255, 30, 30);
	DrawFormatString(1180, 700, color, "FPS[%.2f]", frameRateInfo.fps);
}