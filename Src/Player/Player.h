
#ifndef _PLAYER_H_
#define _PLAYER_H_

// ��`�֘A-------------------------------------------

#define PLAYER_SIZE	     (64) // �v���C���[�̏c���T�C�Y
#define PLAYER_GRAPH_NUM (15) // �v���C���[�̉摜����
#define PLAYER_GRAPH_X	 (5)  // �v���C���[�̉摜����(��)
#define PLAYER_GRAPH_Y	 (3)  // �v���C���[�̉摜����(�c)
#define ANIM_COUNT		 (8)  // ���̃J�E���g���҂��Ď��̉摜��

static const char PLAYER_PATH[] = "Data/Character/Player.png";

// �v���C���[�̐i�s����
enum {
	DIR_LEFT_PLAYER,  // ������
	DIR_RIGHT_PLAYER, // �E����
	DIR_FRONT_PLAYER, // ���ʌ�
};

// �v���C���[�̏��
enum PlayerInfo
{
	PLAYER_INIT_X   = 640, // ����X���W
	PLAYER_INIT_Y   = 500, // ����Y���W
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
void InitPlayer();

// �I������
void FinPlayer();

// �v���C���[�摜�̓Ǎ���
void LoadPlayerGraph();

// �X�V����
void StepPlayer();

// �v���C���[�̕`��
void DrawPlayer();

// �v���C���[�擾
PlayerData* GetPlayerData();

#endif 