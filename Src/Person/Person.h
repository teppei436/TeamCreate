
#ifndef _PERSON_H_
#define _PERSON_H_

// ��`�֘A-------------------------------------------

#define PERSON_SIZE	      (128) // �c���T�C�Y
#define PERSON_GRAPH_NUM  (15) // �摜����
#define PERSON_GRAPH_X	  (5)  // �摜����(��)
#define PERSON_GRAPH_Y	  (3)  // �摜����(�c)
#define ANIM_PERSON_COUNT (8)  // ���̃J�E���g���҂��Ď��̉摜��

static const char PERSON_PATH[]        = "Data/Character/Person.png";
static const char PERSON_DAMAGE_PATH[] = "Data/Character/Person_damage.png";

// �̗͂̏�
enum {
	DAMAGE1,
	DAMAGE2,
	DAMAGE3,
};

// �v���C���[�̏��
enum PersonInfo
{
	PERSON_INIT_X   = 640, // ����X���W
	PERSON_INIT_Y   = 640, // ����Y���W
	PERSON_SPD_FAST = 4,   // �ړ�����
	PERSON_SPD      = 3,   // �ړ��ʏ�
	PERSON_SPD_SLOW = 1,   // �ړ��x��
	PERSON_H        = 128, // �c��
	PERSON_W        = 128, // ����
	PERSON_RADIUS   = 64,  // ���a
	PERSON_HP       = 5,   // HP
};

// �v���C���[�f�[�^�̍\����
struct PersonData {
	VECTOR pos;		                   // ���W
	VECTOR move;	                   // �ړ���
	int m_dir;				           // ����
	int hp;                            // HP
	int hndl[PERSON_GRAPH_NUM];        // �}�b�v�`�b�v�̉摜
	int hndl_damage[PERSON_GRAPH_NUM]; // �}�b�v�`�b�v�̉摜
	int animCnt;				       // �A�j���[�V�����̍ۂɎg�p
	bool isAlive;                      // �����t���O
	bool isDamage;                     // �_���[�W�t���O
}; extern PersonData g_personData;
//----------------------------------------------------

// ����������
void InitPerson();

// �I������
void FinPerson();

// �摜�̓Ǎ���
void LoadPersonGraph();

// �X�V����
void StepPerson();

// �`��
void DrawPerson();

// �擾
PersonData* GetPersonData();

#endif 