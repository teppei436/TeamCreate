
#ifndef _ENEMY_H_
#define _ENEMY_H_

// ��`�֘A-------------------------------------------
#define ENEMY_SIZE		       (128) // �G�l�~�[�̏c���T�C�Y
#define ENEMY_GRAPH_NUM	       (8)   // �G�l�~�[�̉摜����
#define ENEMY_GRAPH_X	       (4)	 // �G�l�~�[�̉摜����(��)
#define ENEMY_GRAPH_Y          (2)	 // �G�l�~�[�̉摜����(�c)
#define ENEMY_BULLET_SIZE      (24)  // �o���b�g�̏c���T�C�Y
#define ENEMY_BULLET_GRAPH_NUM (8)   // �o���b�g�̉摜����
#define ENEMY_BULLET_GRAPH_X   (4)	 // �o���b�g�̉摜����(��)
#define ENEMY_BULLET_GRAPH_Y   (2)	 // �o���b�g�̉摜����(�c)
#define ANIM_ENEMY_COUNT       (10)  // ���̃J�E���g���҂��Ď��̉摜��

static const char ENEMY_PATH[]        = "Data/Character/Enemy.png";
static const char ENEMY_BULLET_PATH[] = "Data/Character/EnemyBullet.png";

extern int Enemy_move_pattern;

// �G�l�~�[�̏��
enum EnemyInfo {
	ENEMY_INIT_X = 650, // ����X���W
	ENEMY_INIT_Y = 80,  // ����Y���W
	ENEMY_H      = 128, // �c��
	ENEMY_W      = 128, // ����
	ENEMY_RADIUS = 64,  // ���a
	ENEMY_HP     = 12,  // �q�b�g�|�C���g
	ENEMY_SPD    = 3,   // ���x
};
// �G�l�~�[�̐i�s����
enum {
	DIR_LEFT,  // ������
	DIR_RIGHT, // �E����
};
// �G�l�~�[�o���b�g�̏��
enum GragonEnemyBulletInfo {
	ENEMY_BULLET_MAX_NUM  = 100, // �ő吔�i�n���h���̐��j
	ENEMY_BULLET_INIT_X   = 650, // ����X���W
	ENEMY_BULLET_INIT_Y   = 20,  // ����Y���W
	ENEMY_BULLET_H        = 24,  // �c��
	ENEMY_BULLET_W        = 24,  // ����
	ENEMY_BULLET_RADIUS   = 12,  // ���a
	ENEMY_BULLET_INTERVAL = 60,  // �Ԋu���[�v��
	ENEMY_BULLET_SPD      = 10,  // ���x
};

// �G�l�~�[�f�[�^���Ǘ�����\����
struct EnemyData {
	VECTOR pos;		                  // ���W
	VECTOR move;	                  // �ړ���
	int animCnt;                      // �A�j���[�V�����̍ۂɎg�p
	int m_dir;					      // �v���C���[�̌���
	int hndl[ENEMY_GRAPH_NUM];        // �}�b�v�`�b�v�̉摜
	int bulletInterval;               // ���ˊԊu
}; extern EnemyData g_EnemyData;

// �G�l�~�[�o���b�g�f�[�^���Ǘ�����\����
struct EnemyBulletData {
	VECTOR pos;                       // ���W
	VECTOR move;	                  // �ړ���
	int animCnt;                      // �A�j���[�V�����̍ۂɎg�p
	int hndl[ENEMY_BULLET_GRAPH_NUM]; // �}�b�v�`�b�v�̉摜
	bool isUse;                       // �g�p���t���O
}; extern EnemyBulletData g_EnemyBulletData[ENEMY_BULLET_MAX_NUM];

//----------------------------------------------------

// ����������
void InitEnemy();

// �I������
void FinEnemy();

// �G�l�~�[�摜�̓Ǎ���
void LoadEnemyGraph();

// �X�V����
void StepEnemy();

// �v���C���[�̕`��
void DrawEnemy();

// �v���C���[�擾
EnemyData* GetEnemyData();

// �e�𔭎˂���
void FireBullet(VECTOR pos, VECTOR move);

#endif 