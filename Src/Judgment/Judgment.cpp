
#include "DxLib.h"
#include "judgment.h"
#include "../Collision/Collision.h"
#include "../Effect/Effect.h"
#include "../Enemy/Enemy.h"
#include "../Person/Person.h"
#include "../Player/Player.h"
#include "../Score/Score.h"

// SE�t�@�C���p�X
#define DAMEGE_SE_PATH "Data/Sound/SE/damage.wav"
#define DEFENSE_SE_PATH "Data/Sound/SE/defense.wav"



// �T�E���h�֘A
int DamageSESoundHndl;
int DefenseSESoundHndl;


// �_���[�W�C���^�[�o��
int DamageInterval;

//---------------------------------
//		����������
//---------------------------------
void InitJudgment()
{
	// �C���^�[�o��������
	DamageInterval = 0;

	// SE������
	DamageSESoundHndl = 0;
	DefenseSESoundHndl = 0;

	// SE�ǂݍ���
	DamageSESoundHndl = LoadSoundMem(DAMEGE_SE_PATH);
	DefenseSESoundHndl = LoadSoundMem(DEFENSE_SE_PATH);
	
}

//---------------------------------
//		�X�V����
//---------------------------------
void StepJudgment()
{
	// �C���^�[�o���X�V
	DamageInterval++;

	//----------------------------------------------
	//		�v���C���[�ƃo���b�g
	//----------------------------------------------
	for (int weapon_index = 0; weapon_index < ENEMY_BULLET_MAX_NUM; weapon_index++) {
		if (g_EnemyBulletData[weapon_index].isUse == false)
			continue;
		// ��`�̓����蔻��
		bool result = IsHitRect((int)g_EnemyBulletData[weapon_index].pos.x - ENEMY_BULLET_W / 2,
			(int)g_EnemyBulletData[weapon_index].pos.y - ENEMY_BULLET_H / 2,
			ENEMY_BULLET_W, ENEMY_BULLET_H, (int)g_playerData.pos.x - PLAYER_W / 2,
			(int)g_playerData.pos.y - PLAYER_H / 2, PLAYER_W, PLAYER_H);

		// ���������Ȃ�
		if (result) {
			// �G�l�~�[�o���b�g������
			g_EnemyBulletData[weapon_index].isUse = false;

			AddScore(100);
			

			if (DamageInterval > DAMAGE_INTERVAL) {
				
				// �T�E���h
				PlaySoundMem(DefenseSESoundHndl, DX_PLAYTYPE_BACK, true);

				// �_���[�W�C���^�[�o�������Z�b�g
				DamageInterval = 0;
			}
		}
	}

	//----------------------------------------------
    //		�p�[�\���ƃo���b�g
    //----------------------------------------------
	for (int weapon_index = 0; weapon_index < ENEMY_BULLET_MAX_NUM; weapon_index++) {
		if (g_EnemyBulletData[weapon_index].isUse == false)
			continue;
		// ��`�̓����蔻��
		bool result = IsHitRect((int)g_EnemyBulletData[weapon_index].pos.x - ENEMY_BULLET_W / 2,
			(int)g_EnemyBulletData[weapon_index].pos.y - ENEMY_BULLET_H / 2,
			ENEMY_BULLET_W, ENEMY_BULLET_H, (int)g_personData.pos.x - PLAYER_W / 2,
			(int)g_personData.pos.y - PLAYER_H / 2, PLAYER_W, PLAYER_H);

		// ���������Ȃ�
		if (result) {
			// �G�l�~�[�o���b�g������
			g_EnemyBulletData[weapon_index].isUse = false;
			
			// �_���[�W����
			AddDamage(1);

			// �G�t�F�N�g
			PlayEffect(EFFECT_TYPE_EXPLOSION, (int)g_personData.pos.x, (int)g_personData.pos.y);

			if (DamageInterval > DAMAGE_INTERVAL) {
				// �T�E���h
				PlaySoundMem(DamageSESoundHndl, DX_PLAYTYPE_BACK, true);

				// �_���[�W�C���^�[�o�������Z�b�g
				DamageInterval = 0;
			}
		}
	}
}

//---------------------------------
//		�I������
//---------------------------------
void FinJudgment()
{
	// ���ʉ��j��
	DeleteSoundMem(DamageSESoundHndl);
	DeleteSoundMem(DefenseSESoundHndl);

}

//---------------------------------
//		�_���[�W����
//---------------------------------
void AddDamage(int damage)
{
	// �������v���C���[��HP�����炷
	g_personData.hp -= damage;

	// �_���[�W�t���O�𗧂Ă�
	g_personData.isDamage = true;
}
