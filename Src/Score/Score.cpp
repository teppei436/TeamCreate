
#include <DxLib.h>

// ��`�֘A-----------------------------------------------------------------------
static const int NUMBER        = 10;		// �ǂݍ��މ摜�� �u0�v �` �u9�v
static const int NUMBER_SIZE_X = 16;		// �����T�C�Y��
static const int NUMBER_SIZE_Y = 32;		// �����T�C�Y�c
static const int DIGIT_NUMBER  = 5;			// �\���\�Ȍ���
static const int ADD_SCORE_SPD = 10;		// 1�t���[���ŉ��Z�����X�R�A��
static const int START_POS_X   = 1260;		// �X�R�A�\���J�n�ʒu�@��
static const int START_POS_Y   = 32;		// �X�R�A�\���J�n�ʒu�@�c


//�^�C�g���摜�̍\����
typedef struct
{
	int m_graphHndl[NUMBER];
	int m_soundHndl;
	int m_score;
	int m_dispScore;
}SCORE_DATA;

//-------------------------------------------------------------------------------

// ���̕ϐ��Ɏ��ۂ̃X�R�A�Ȃǂ̃f�[�^���i�[����
SCORE_DATA g_score = { 0 };

//--------------------------------
//		�X�R�A�̏�����
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
//		�X�R�A�摜�̃��[�h
//--------------------------------
void LoadScore()
{
	LoadDivGraph("Data/Number/number16x32_05.png", NUMBER, 10, 1,
		NUMBER_SIZE_X, NUMBER_SIZE_Y, g_score.m_graphHndl);
	g_score.m_soundHndl = LoadSoundMem("sound/se2.mp3");
}

//--------------------------------
//		�X�R�A�̃f�[�^�j��
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
//		�X�R�A�̕`�揈��
//--------------------------------
void DrawScore()
{
	// ���j�^�[�ɕ\������X�R�A�����̕ϐ��ɃZ�b�g
	int TempScore = g_score.m_dispScore;
	for (int i = 0; i < DIGIT_NUMBER; i++)
	{
		// ��1�������o��
		int iNum = TempScore % 10;
		// 1���ڂ������ʒuX=580, Y=32����X�R�A��\�����Ă���
		DrawRotaGraph(START_POS_X - i * NUMBER_SIZE_X, START_POS_Y,
			1.0, 0.0, g_score.m_graphHndl[iNum], TRUE);
		// ��1�����폜
		TempScore /= 10;
	}
}

//--------------------------------
//		�X�R�A�����Z����
//--------------------------------
void AddScore(int score)
{
	g_score.m_score += score;
}

//--------------------------------
//		�X�R�A�����Z����
//--------------------------------
void SubScore(int score)
{
	g_score.m_score -= score;
}

//--------------------------------
//		�X�R�A�������I�ɃZ�b�g����
//--------------------------------
void SetScore(int score)
{
	g_score.m_dispScore = score;
	g_score.m_score = score;
}


//--------------------------------
//		�X�R�A���擾����
//--------------------------------
int GetScore()
{
	return g_score.m_score;
}

//--------------------------------
//		�X�R�A�̍X�V����
//--------------------------------
void UpdateScore()
{
	// �\���X�R�A�Ǝ��ۂ̃X�R�A�����荇�킹�Ă���
	if (g_score.m_score != g_score.m_dispScore)
	{
		PlaySoundMem(g_score.m_soundHndl, DX_PLAYTYPE_BACK, TRUE);

		// ���ʉ�
		SetCurrentPositionSoundMem(1000, g_score.m_soundHndl);

		// �X�R�A�����̐����������Z����
		g_score.m_dispScore += ADD_SCORE_SPD;

		// �I�[�o�[�����ꍇ�͓����ɂ��Ă���
		if (g_score.m_dispScore > g_score.m_score)
		{
			g_score.m_dispScore = g_score.m_score;
		}
	}
}
