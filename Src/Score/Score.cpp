
#include <DxLib.h>

// 定義関連-----------------------------------------------------------------------
static const int NUMBER        = 10;		// 読み込む画像数 「0」 ～ 「9」
static const int NUMBER_SIZE_X = 16;		// 数字サイズ横
static const int NUMBER_SIZE_Y = 32;		// 数字サイズ縦
static const int DIGIT_NUMBER  = 5;			// 表示可能な桁数
static const int ADD_SCORE_SPD = 10;		// 1フレームで加算されるスコア数
static const int START_POS_X   = 1260;		// スコア表示開始位置　横
static const int START_POS_Y   = 32;		// スコア表示開始位置　縦


//タイトル画像の構造体
typedef struct
{
	int m_graphHndl[NUMBER];
	int m_soundHndl;
	int m_score;
	int m_dispScore;
}SCORE_DATA;

//-------------------------------------------------------------------------------

// この変数に実際のスコアなどのデータを格納する
SCORE_DATA g_score = { 0 };

//--------------------------------
//		スコアの初期化
//--------------------------------
void InitScore()
{
	for (int i = 0; i < NUMBER; i++) {
		g_score.m_soundHndl = -1;
	}
	g_score.m_soundHndl = -1;
	g_score.m_score     = 0;
	g_score.m_dispScore = 0;
}


//--------------------------------
//		スコア画像のロード
//--------------------------------
void LoadScore()
{
	LoadDivGraph("Data/Number/number16x32_05.png", NUMBER, 10, 1,
		NUMBER_SIZE_X, NUMBER_SIZE_Y, g_score.m_graphHndl);
	g_score.m_soundHndl = LoadSoundMem("sound/se2.mp3");
}

//--------------------------------
//		スコアのデータ破棄
//--------------------------------
void ExitScore()
{
	for (int i = 0; i < NUMBER; i++)
	{
		if (g_score.m_graphHndl[i] != -1)
		{
			DeleteGraph(g_score.m_graphHndl[i]);
			g_score.m_graphHndl[i] = -1;
		}
	}

	if (g_score.m_soundHndl != -1)
	{
		DeleteSoundMem(g_score.m_soundHndl);
	}
}

//--------------------------------
//		スコアの描画処理
//--------------------------------
void DrawScore()
{
	// モニターに表示するスコアを仮の変数にセット
	int TempScore = g_score.m_dispScore;
	for (int i = 0; i < DIGIT_NUMBER; i++)
	{
		// 下1桁を取り出す
		int iNum = TempScore % 10;
		// 1桁目を初期位置X=580, Y=32からスコアを表示していく
		DrawRotaGraph(START_POS_X - i * NUMBER_SIZE_X, START_POS_Y,
			1.0, 0.0, g_score.m_graphHndl[iNum], TRUE);
		// 下1桁を削除
		TempScore /= 10;
	}
}

//--------------------------------
//		スコアを加算する
//--------------------------------
void AddScore(int score)
{
	g_score.m_score += score;
}

//--------------------------------
//		スコアを減算する
//--------------------------------
void SubScore(int score)
{
	g_score.m_score -= score;
}

//--------------------------------
//		スコアを強制的にセットする
//--------------------------------
void SetScore(int score)
{
	g_score.m_dispScore = score;
	g_score.m_score = score;
}


//--------------------------------
//		スコアを取得する
//--------------------------------
int GetScore()
{
	return g_score.m_score;
}

//--------------------------------
//		スコアの更新処理
//--------------------------------
void UpdateScore()
{
	// 表示スコアと実際のスコアをすり合わせていく
	if (g_score.m_score != g_score.m_dispScore)
	{
		PlaySoundMem(g_score.m_soundHndl, DX_PLAYTYPE_BACK, TRUE);

		// 効果音
		SetCurrentPositionSoundMem(1000, g_score.m_soundHndl);

		// スコアを一定の数字だけ加算する
		g_score.m_dispScore += ADD_SCORE_SPD;

		// オーバーした場合は同じにしておく
		if (g_score.m_dispScore > g_score.m_score)
		{
			g_score.m_dispScore = g_score.m_score;
		}
	}
}
