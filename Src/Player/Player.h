
#ifndef _ANINATION_H_
#define _ANINATION_H_

// ��`�֘A-------------------------------------------

#define PLAYER_SIZE			(64)	// �v���C���[�̏c���T�C�Y
#define PLAYER_GRAPH_NUM	(20)	// �v���C���[�̉摜����
#define PLAYER_GRAPH_X		(5)		// �v���C���[�̉摜����(��)
#define PLAYER_GRAPH_Y		(4)		// �v���C���[�̉摜����(�c)
#define ANIM_COUNT			(8)	    // ���̃J�E���g���҂��Ď��̉摜��

static const char PLAYER_PATH[]        = "Data/Animation/AnimationPlayer.png";
static const char PLAYER_GOLD_PATH[]   = "Data/Animation/AnimationPlayerGold.png";
static const char PLAYER_DAMAGE_PATH[] = "Data/Animation/AnimationPlayer_damage.png";

// �v���C���[�̐i�s����
enum {
	DIR_LEFT_WALK,  // �������̕��s
	DIR_RIGHT_WALK, // �E�����̕��s
};

// �v���C���[�̏��
enum PlayerInfo
{
	PLAYER_INIT_X   = 640, // ����X���W
	PLAYER_INIT_Y   = 640, // ����Y���W
	PLAYER_SPD_FAST = 4,   // �ړ�����
	PLAYER_SPD      = 3,   // �ړ��ʏ�
	PLAYER_SPD_SLOW = 1,   // �ړ��x��
	PLAYER_H        = 64,  // �c��
	PLAYER_W        = 32,  // ����
	PLAYER_RADIUS   = 32,  // ���a
};

// �v���C���[�f�[�^�̍\����
struct PlayerData {
	VECTOR pos;		                     // ���W
	VECTOR move;	                     // �ړ���
	int m_dir;					         // �v���C���[�̌���
	int hndl[PLAYER_GRAPH_NUM];          // �}�b�v�`�b�v�̉摜
	int animCnt;				         // �A�j���[�V�����̍ۂɎg�p
}; extern PlayerData g_playerData;
//----------------------------------------------------

// ����������
void InitAnimePlayer();

// �I������
void FinAnimePlayer();

// �v���C���[�摜�̓Ǎ���
void LoadPlayerGraph();

// �X�V����
void StepAnimePlayer();

// �v���C���[�̕`��
void DrawAnimePlayer();

// �v���C���[�̕`��
void DrawAnimePlayer01();

// �v���C���[�擾
PlayerData* GetPlayerData();

#endif 