
#ifndef _COLLISION_H_
#define _COLLISION_H_

// 円の当たり判定
bool IsHitCircle(int x1, int y1, int r1, int x2, int y2, int r2);

// 矩形の当たり判定
bool IsHitRect(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);

#endif