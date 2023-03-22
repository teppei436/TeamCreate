
#ifndef __MATH_H__
#define __MATH_H__

#include "DxLib.h"

// 2点間の距離を計算する (2D)
float GetDistance(float x1, float y1, float x2, float y2);

// 始点と終点からベクトルを作成
VECTOR VecCreate(VECTOR start, VECTOR end);

// ベクトルの足し算
VECTOR VecAdd(VECTOR vec1, VECTOR vec2);

// ベクトルの長さ
float VecLong(VECTOR vec);

// ベクトルの正規化
VECTOR VecNormalize(VECTOR vec);

// ベクトルをスカラー倍
VECTOR VecScale(VECTOR vec, float scale);

#endif