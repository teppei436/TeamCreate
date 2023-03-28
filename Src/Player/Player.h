
#ifndef _PLAYER_H_
#define _PLAYER_H_

// ��`�֘A-------------------------------------------

#define PLAYER_PATH "Data/Character/Player.png"

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
	PLAYER_H        = 128, // �c��
	PLAYER_W        = 64,  // ����
	PLAYER_RADIUS   = 64,  // ���a
};

// �v���C���[�f�[�^�̍\����
struct PlayerData {
	VECTOR pos;	// ���W
	int hndl;   // �}�b�v�`�b�v�̉摜
}; extern PlayerData g_playerData;
//----------------------------------------------------

// ����������
void InitPlayer();

// �I������
void FinPlayer();

// �X�V����
void StepPlayer();

// �v���C���[�̕`��
void DrawPlayer();

// �v���C���[�擾
PlayerData* GetPlayerData();

#endif 