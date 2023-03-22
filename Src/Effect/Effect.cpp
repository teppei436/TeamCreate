
#include <DxLib.h>
#include "Effect.h"
#include "../Common/Common.h"

#define EFFECT_MAX_NUM       (20)
#define EFFECT_ANIME_MAX_NUM (4)

struct EffectInfo
{
	EFFECT_TYPE effectType;

	int handle[EFFECT_ANIME_MAX_NUM];

	int x, y;
	bool isUse;

	int animeNum;
	int currentAnimeIndex;

	float changeTime;
	float currentChangeTime;
};

EffectInfo effectInfo[EFFECT_MAX_NUM];

const char effectFilePath[EFFECT_TYPE_NUM][256] =
{
	"Data/Effect/EffectExplosion.png",
};

const int effectAnimeImgNum[EFFECT_TYPE_NUM] =
{
	4,
};

const int effectImageSplitNum[EFFECT_TYPE_NUM][2] =
{
	{ 2, 2, },
};

const int effectImageSize[EFFECT_TYPE_NUM] =
{
	64,
};

const float effectChangeTime[EFFECT_TYPE_NUM] =
{
	0.05f,
};

//エフェクトの読み込み
//引数	：エフェクトの種類、作成数
void LoadEffect(EFFECT_TYPE type, int create_num)
{
	for (int create_index = 0; create_index < create_num; create_index++) {
		for (int effect_index = 0; effect_index < EFFECT_MAX_NUM; effect_index++) {
			if (effectInfo[effect_index].handle[0] == 0) {
				int success_flg = LoadDivGraph(effectFilePath[type],
					effectAnimeImgNum[type],
					effectImageSplitNum[type][0],
					effectImageSplitNum[type][1],
					effectImageSize[type],
					effectImageSize[type],
					effectInfo[effect_index].handle);

				if (success_flg == 0) {
					effectInfo[effect_index].animeNum = effectAnimeImgNum[type];
					effectInfo[effect_index].changeTime = effectChangeTime[type];
					effectInfo[effect_index].effectType = type;
				}

				break;
			}
		}
	}
}

//エフェクトの初期化
void InitEffect()
{
	for (int effect_index = 0; effect_index < EFFECT_MAX_NUM; effect_index++) {
		for (int anime_index = 0; anime_index < EFFECT_ANIME_MAX_NUM; anime_index++) {
			effectInfo[effect_index].handle[anime_index] = 0;
			effectInfo[effect_index].x = effectInfo[effect_index].y = 0;
			effectInfo[effect_index].isUse = false;
			effectInfo[effect_index].animeNum = 0;
			effectInfo[effect_index].currentAnimeIndex = 0;
			effectInfo[effect_index].changeTime = 0.0f;
			effectInfo[effect_index].currentChangeTime = 0.0f;
		}
	}
}

//エフェクト通常処理
void StepEffect()
{
	for (int effect_index = 0; effect_index < EFFECT_MAX_NUM; effect_index++) {
		if (effectInfo[effect_index].isUse == true) {
			if (effectInfo[effect_index].currentChangeTime >= effectInfo[effect_index].changeTime) {
				effectInfo[effect_index].currentAnimeIndex++;
				effectInfo[effect_index].currentChangeTime = 0.0f;

				if (effectInfo[effect_index].currentAnimeIndex >= effectInfo[effect_index].animeNum) {
					effectInfo[effect_index].isUse = false;
					continue;
				}
			}
			effectInfo[effect_index].currentChangeTime += 1.0f / FRAME_RATE;
		}
	}
}

//エフェクト描画処理
void DrawEffect()
{
	for (int effect_index = 0; effect_index < EFFECT_MAX_NUM; effect_index++) {
		if (effectInfo[effect_index].isUse == true) {
			DrawRotaGraph(effectInfo[effect_index].x, effectInfo[effect_index].y, 1.0, 0.0, effectInfo[effect_index].handle[effectInfo[effect_index].currentAnimeIndex], true);
		}
	}
}

//エフェクトの後処理
void FinEffect()
{
	for (int effect_index = 0; effect_index < EFFECT_MAX_NUM; effect_index++) {
		for (int anime_index = 0; anime_index < EFFECT_ANIME_MAX_NUM; anime_index++) {
			if (effectInfo[effect_index].handle[anime_index] != 0) {
				DeleteGraph(effectInfo[effect_index].handle[anime_index]);
				effectInfo[effect_index].handle[anime_index] = 0;
			}
		}
	}
}

//エフェクトの再生
//引数	：エフェクトの種類, Ｘ座標, Ｙ座標, １枚あたりの表示時間
void PlayEffect(EFFECT_TYPE type, int x, int y)
{
	for (int effect_index = 0; effect_index < EFFECT_MAX_NUM; effect_index++) {
		if (effectInfo[effect_index].isUse == true)
			continue;

		if (effectInfo[effect_index].effectType == type) {
			effectInfo[effect_index].x = x;
			effectInfo[effect_index].y = y;
			effectInfo[effect_index].currentAnimeIndex = 0;
			effectInfo[effect_index].currentChangeTime = 0.0f;
			effectInfo[effect_index].isUse = true;

			break;
		}
	}
}