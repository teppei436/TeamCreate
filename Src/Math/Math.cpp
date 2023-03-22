
#include <math.h>
#include "Math.h"

// 点P(x1, y1)から点Q(x2,y2)までの距離を返す
float GetDistance(float x1, float y1, float x2, float y2)
{
	// 点Pから点Qまでの直線を斜辺とする直角三角形を作り、
	// ピタゴラスの定理から斜辺の長さを計算する。
	// ①底辺の長さを計算する
	float base = x1 - x2;

	// ②高さの長さを計算する
	float height = y1 - y2;

	// ③ピタゴラスの定理から斜辺の長さを計算する
	//   平方根は<Math.h>のsqrtf関数で計算することができる
	//   計算結果を変数distに格納してください
	float hypotenuse = (base * base) + (height * height);
	float dist = sqrtf(hypotenuse);

	return dist;
}

// 始点と終点からベクトルを作成
VECTOR VecCreate(VECTOR start, VECTOR end)
{
	VECTOR result;

	// ①ベクトルは「終点 - 始点」で求められる
	result.x = end.x - start.x;
	result.y = end.y - start.y;
	result.z = end.z - start.z;

	return result;
}

// ベクトルの足し算
VECTOR VecAdd(VECTOR vec1, VECTOR vec2)
{
	VECTOR result;

	// ①各成分を足し算する
	result.x = vec1.x + vec2.x;
	result.y = vec1.y + vec2.y;
	result.z = vec1.z + vec2.z;

	return result;
}

// ベクトルの長さ
float VecLong(VECTOR vec)
{
	// ①ピタゴラスの定理からベクトルの長さを求める
	return sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

// ベクトルの正規化
VECTOR VecNormalize(VECTOR vec)
{
	VECTOR result = { 0 };

	// ①ベクトルの長さを求める
	float vec_long = VecLong(vec);

	// ②各成分を長さで割ることにより正規化する
	// ココを考えてみる
	result.x = vec.x / vec_long;
	result.y = vec.y / vec_long;
	result.z = vec.z / vec_long;

	return result;
}

// ベクトルをスカラー倍
VECTOR VecScale(VECTOR vec, float scale)
{
	VECTOR result;

	// ①各成分をスカラー倍する
	result.x = vec.x * scale;
	result.y = vec.y * scale;
	result.z = vec.z * scale;

	return result;
}
