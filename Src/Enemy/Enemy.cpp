
#include "DxLib.h"
#include "Enemy.h"
#include "../Effect/Effect.h"
#include "../Math/Math.h"
#include "../Person/Person.h"
#include "../Player/Player.h"

EnemyData       g_EnemyData;
EnemyBulletData g_EnemyBulletData[ENEMY_BULLET_MAX_NUM] = { 0 };

// �ړ��p�^�[��
int Enemy_move_pattern;

//---------------------------------
//		����������
//---------------------------------
void InitEnemy()
{
	// �G�l�~�[������
	g_EnemyData.pos.x          = ENEMY_INIT_X;
	g_EnemyData.pos.y          = ENEMY_INIT_Y;
	g_EnemyData.m_dir          = 0;
	g_EnemyData.animCnt        = 0;
	g_EnemyData.bulletInterval = 0;


	// �G�l�~�[�摜������
	for (int i = 0; i < ENEMY_GRAPH_NUM; i++) {
		g_EnemyData.hndl[i] = -1;
	}

	// �G�l�~�[�o���b�g�摜������
	for (int MaxIndex = 0; MaxIndex < ENEMY_BULLET_MAX_NUM; MaxIndex++) {
		g_EnemyBulletData[MaxIndex].isUse = false;
		for (int HndlIndex = 0; HndlIndex < ENEMY_BULLET_GRAPH_NUM; HndlIndex++) {
			g_EnemyBulletData[MaxIndex].hndl[HndlIndex] = -1;
		}
	}

	// �ړ��p�^�[��������
	Enemy_move_pattern = 1;
}

//---------------------------------
//		�I������
//---------------------------------
void FinEnemy()
{
	// �摜�̔j��
	for (int i = 0; i < ENEMY_GRAPH_NUM; i++) {
		if (g_EnemyData.hndl[i] == -1) {
			DeleteGraph(g_EnemyData.hndl[i]);
			g_EnemyData.hndl[i] = -1;
		}
	}

	for (int HndlIndex = 0; HndlIndex < ENEMY_BULLET_GRAPH_NUM; HndlIndex++) {
		for (int MaxIndex = 0; MaxIndex < ENEMY_BULLET_MAX_NUM; MaxIndex++) {
			if (g_EnemyBulletData[MaxIndex].hndl[HndlIndex] == -1) {
				DeleteGraph(g_EnemyBulletData[MaxIndex].hndl[HndlIndex]);
				g_EnemyBulletData[MaxIndex].hndl[HndlIndex] = -1;
			}
		}
	}
}

//---------------------------------
//		�}�b�v�`�b�v�摜�̓Ǎ���
//---------------------------------
void LoadEnemyGraph()
{
	// �ꖇ�̉摜�𕪊����[�h�@�G���[�Ȃ�uret�v��-1������
	int ret1 = LoadDivGraph(ENEMY_PATH, ENEMY_GRAPH_NUM,
		ENEMY_GRAPH_X, ENEMY_GRAPH_Y, ENEMY_SIZE, ENEMY_SIZE, g_EnemyData.hndl);

	for (int i = 0; i < ENEMY_BULLET_MAX_NUM; i++) {
		int ret2 = LoadDivGraph(ENEMY_BULLET_PATH, ENEMY_BULLET_GRAPH_NUM,
			ENEMY_BULLET_GRAPH_X, ENEMY_BULLET_GRAPH_Y, ENEMY_BULLET_SIZE, ENEMY_BULLET_SIZE, g_EnemyBulletData[i].hndl);
	}
}

//---------------------------------
//		�X�V����
//---------------------------------
void StepEnemy()
{
	// �e�̔��ˊԊu���X�V
	g_EnemyData.bulletInterval++;

	// �e���΂����߂ɁF�����@
	//���ˊԊu�̎��Ԃ��o����
	if (g_EnemyData.bulletInterval > ENEMY_BULLET_INTERVAL) {
		//�{�X�̒e����擪���珇�Ԃɉ�
		for (int i = 0; i < ENEMY_BULLET_MAX_NUM; i++) {
			//���g�p�̃{�X�̒e��񂪂�����
			if (g_EnemyBulletData[i].isUse == false) {
				// �o���b�g�̈ړ��ʂ����̕ϐ��ɑ������
				VECTOR bullet_move = { 0 };

				// �@�G�l�~�[����v���C���[�܂ł̃x�N�g�����쐬
				bullet_move = VecCreate(g_EnemyData.pos, g_personData.pos);

				// �A�쐬�����x�N�g���𐳋K�����A������1�ɂ���
				bullet_move = VecNormalize(bullet_move);

				// �B���K�������x�N�g����BULLET_SPEED�ŃX�J���[�{���A�ړ��ʂƂ���
				bullet_move = VecScale(bullet_move, ENEMY_BULLET_SPD);

				//�G�̒e�̔��ˊԊu�����Z�b�g
				g_EnemyData.bulletInterval = 0;

				// ����
				FireBullet(g_EnemyData.pos, bullet_move);

				//���[�v�𔲂���
				break;
			}
		}
	}
	
	//�e���΂����߂ɁF�����A
	//�e����擪���珇�Ԃɉ�
	for (int i = 0; i < ENEMY_BULLET_MAX_NUM; i++) {
		//�g�p���̒e�Ȃ�
		if (g_EnemyBulletData[i].isUse == true) {
			//X���W���X�V
			g_EnemyBulletData[i].pos.x += g_EnemyBulletData[i].move.x;
			//Y���W���X�V
			g_EnemyBulletData[i].pos.y += g_EnemyBulletData[i].move.y;
		}
	}

	int EnemySpd = ENEMY_SPD;

	// �G�l�~�[�̈ړ��p�^�[��
	switch (Enemy_move_pattern) {

	case 1:

		break;

	case 2:

		break;

	case 3:

		break;

	default:
		break;
	}

	// �A�j���[�V�����̃J�E���g�X�V
	g_EnemyData.animCnt++;
	if (g_EnemyData.animCnt >= ANIM_ENEMY_COUNT * 4) {
		g_EnemyData.animCnt = 0;
	}
}

//---------------------------------
//		�`�揈��
//---------------------------------
void DrawEnemy()
{
	// �A�j���[�V����
	int animNum[] = { 0, 1, 2, 3 };
	int animEnemyID = g_EnemyData.m_dir * ENEMY_GRAPH_X + animNum[g_EnemyData.animCnt / ANIM_ENEMY_COUNT];

	// �G�l�~�[�̕`��
	DrawRotaGraph((int)g_EnemyData.pos.x, (int)g_EnemyData.pos.y, 1.0, 0.0, g_EnemyData.hndl[animEnemyID], TRUE);

	for (int index = 0; index < ENEMY_BULLET_MAX_NUM; index++) {
		if (g_EnemyBulletData[index].isUse) {
			DrawRotaGraph((int)g_EnemyBulletData[index].pos.x, (int)g_EnemyBulletData[index].pos.y, 1.0, 0.0, g_EnemyBulletData[index].hndl[animEnemyID], TRUE);
		}
	}
}

//---------------------------------
//		�G�l�~�[�擾
//---------------------------------
EnemyData* GetEnemyData() {
	return &g_EnemyData;
}

//---------------------------------
//		�G�̒e�𔭎˂���
//---------------------------------
void FireBullet(VECTOR pos, VECTOR move)
{
	EnemyBulletData* enemyBullet = g_EnemyBulletData;

	// ���g�p�̓G�̒e��T��
	for (int i = 0; i < ENEMY_BULLET_MAX_NUM; i++, enemyBullet++) {
		// ���g�p���ǂ���
		if (!enemyBullet->isUse) {
			// ��{����ݒ�
			enemyBullet->isUse = true;
			enemyBullet->pos = pos;
			enemyBullet->move = move;

			break;
		}
	}
}