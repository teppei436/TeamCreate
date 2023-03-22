
#include "DxLib.h"
#include "Collision.h"
#include "../Common/Common.h"
#include "../Effect/Effect.h"
#include "../Input/Input.h"

// ‰~‚Ì“–‚½‚è”»’è
bool IsHitCircle(int x1, int y1, int r1, int x2, int y2, int r2)
{
	int sum_radius = r1 + r2;
	sum_radius *= sum_radius;

	int len_x = x1 - x2;
	len_x *= len_x;

	int len_y = y1 - y2;
	len_y *= len_y;

	if (sum_radius > len_x + len_y)
	{
		return true;
	}

	return false;
}

// ‹éŒ`‚Ì“–‚½‚è”»’è
bool IsHitRect(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	if (x1 < x2 + w2 && x1 + w1 > x2 &&
		y1 + h1 > y2 && y1 < y2 + h2)
	{
		return true;
	}

	return false;
}