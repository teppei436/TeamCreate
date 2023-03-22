
#include "DxLib.h"
#include "Input.h"

#define KEY_BUF_LEN (256)

// 現在のフレームのキー情報
char currentKeyBuf[KEY_BUF_LEN] = { 0 };

// 前フレームのキー情報
char preKeyBuf[KEY_BUF_LEN] = { 0 };

//---------------------------------
//		初期化処理
//---------------------------------
void InitInput()
{
	for (int index = 0; index < KEY_BUF_LEN; index++) {
		currentKeyBuf[index] = '\0';
		preKeyBuf[index] = '\0';
	}
}

//---------------------------------
//		更新処理
//---------------------------------
// 他のStepより早く呼ぶ
void StepInput()
{
	// 前フレームのキー情報変数に記録しておく
	for (int index = 0; index < KEY_BUF_LEN; index++) {
		preKeyBuf[index] = currentKeyBuf[index];
	}

	// 現在のキー情報を取得
	GetHitKeyStateAll(currentKeyBuf);
}

// たった今押されたか
bool IsKeyPush(int key_code)
{
	// 前フレで押されてない かつ 現フレで押されている
	if (preKeyBuf[key_code] == 0 && currentKeyBuf[key_code] == 1)
		return true;

	// 押されてないので false
	return false;
}

// 押し続けられているか
bool IsKeyKeep(int key_code)
{
	// 前フレで押されている かつ 現フレで押されている
	if (preKeyBuf[key_code] == 1 && currentKeyBuf[key_code] == 1)
		return true;

	// 押されてないので false
	return false;
}

// たった今離されたか
bool IsKeyRelease(int key_code)
{
	// 前フレで押されている かつ 現フレで押されていない
	if (preKeyBuf[key_code] == 1 && currentKeyBuf[key_code] == 0)
		return true;

	// 押されてないので false
	return false;
}

// 単純に押されているか
bool IsKeyDown(int key_code)
{
	// 現フレで押されている（前フレの状態は関係なし）
	if (currentKeyBuf[key_code] == 1)
		return true;

	return false;
}