
#include "DxLib.h"	//DXライブラリのインクルード

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

	SetDrawScreen(DX_SCREEN_BACK);	//描画するスクリーンを設定する

	//-----------------------------------------

	//ゲームメインループ
	while (ProcessMessage() != -1)
	{
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			//エスケープキーが押されたら終了
			break;
		}

		//②画面に表示されたものを初期化
		ClearDrawScreen();


		//-----------------------------------------
		//ここにゲームの本体を書くことになる
		//-----------------------------------------

		//ループの終わりに
		//③フリップ関数
		ScreenFlip();

	}

	//-----------------------------------------
	//最後に１回だけやる処理をここに書く

	//④DXライブラリの後処理
	DxLib_End();

	//-----------------------------------------

	return 0;
}
