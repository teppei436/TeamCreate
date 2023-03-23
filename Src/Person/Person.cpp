
#include "DxLib.h"
#include "Person.h"
#include "../Common/Common.h"
#include "../Effect/Effect.h"
#include "../Enemy/Enemy.h"
#include "../Input/Input.h"
#include "../Scene/ScenePlay.h"

PersonData g_personData;

//---------------------------------
//		����������
//---------------------------------
void InitPerson()
{
	g_personData.pos.x    = PERSON_INIT_X;
	g_personData.pos.y    = PERSON_INIT_Y;
	g_personData.m_dir    = DIR_RIGHT_PERSON;
	g_personData.hp       = PERSON_HP;
	g_personData.animCnt  = 0;
	g_personData.isAlive  = true;
	g_personData.isDamage = false;
}

//---------------------------------
//		�I������
//---------------------------------
void FinPerson()
{
	// �摜�f�[�^�̔j��
	for (int i = 0; i < PERSON_GRAPH_NUM; i++) {
		if (g_personData.hndl[i] == -1) {
			DeleteGraph(g_personData.hndl[i]);
			g_personData.hndl[i] = -1;
		}
	}
}

//---------------------------------
//		�}�b�v�`�b�v�摜�̓Ǎ���
//---------------------------------
void LoadPersonGraph()
{
	// �ꖇ�̉摜�𕪊����[�h�@�G���[�Ȃ�uret�v��-1������
	int ret = LoadDivGraph(PERSON_PATH, PERSON_GRAPH_NUM,
		PERSON_GRAPH_X, PERSON_GRAPH_Y, PERSON_SIZE, PERSON_SIZE, g_personData.hndl);
	int ret1 = LoadDivGraph(PERSON_DAMAGE_PATH, PERSON_GRAPH_NUM,
		PERSON_GRAPH_X, PERSON_GRAPH_Y, PERSON_SIZE, PERSON_SIZE, g_personData.hndl_damage);
}


//---------------------------------
//		�X�V����
//---------------------------------
void StepPerson()
{
	// �A�j���[�V�����̃J�E���g�X�V
	g_personData.animCnt++;

	// �A�j���[�V���������[�v
	if (g_personData.animCnt >= ANIM_PERSON_COUNT * 4) {
		g_personData.animCnt = 0;
	}

	// HP��0�ȉ��ɂȂ����玀��
	if (g_personData.isAlive) {
		if (g_personData.hp <= 0) {
			g_personData.isAlive = false;
		}
	}
}

//---------------------------------
//		�`�揈��
//---------------------------------
void DrawPerson()
{
	int animNum[] = { 0, 1, 2, 3 };
	int animID = g_personData.m_dir * PERSON_GRAPH_X + animNum[g_personData.animCnt / ANIM_PERSON_COUNT];

	if (g_personData.isDamage) {
		DrawRotaGraph((int)g_personData.pos.x, (int)g_personData.pos.y, 1.0, 0.0, g_personData.hndl_damage[animID], TRUE);
		g_personData.isDamage = false;
	}
	else {
		DrawRotaGraph((int)g_personData.pos.x, (int)g_personData.pos.y, 1.0, 0.0, g_personData.hndl[animID], TRUE);
	}
}

//�v���C���[�擾
PersonData* GetPersonData()
{
	return &g_personData;
}