

#include "DxLib.h"	//DX���C�u�����̃C���N���[�h
#include "Common/Common.h"
#include "Input/Input.h"
#include "Scene/Scene.h"
#include "Scene/SceneClear.h"
#include "Scene/SceneGameOver.h"
#include "Scene/ScenePlay.h"
#include "Scene/SceneTitle.h"
#include "Score/Score.h"

// �t���[�����[�g���
struct Frame_Rate_Info {
	int currentTime;
	int lastFrameTime;
	int count;
	int calcFpsTime;
	float fps;
};

// �t���[�����[�g���ϐ�
Frame_Rate_Info frameRateInfo;

// FPS�v�Z
void CalcFPS();

// FPS�\���i�f�o�b�O�p�j
void DrawFPS();

// ���݂̃V�[��ID
int g_CurrentSceneID = SCENE_ID_INIT_TITLE;

// Win32�A�v���P�[�V������ WinMain�֐� ����n�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//�E�B���h�E�̏�Ԃ�ݒ肷��
	ChangeWindowMode(true);

	//-----------------------------------------
	//��ԍŏ��ɂP�񂾂���鏈���������ɏ���

	//�@DX���C�u�����̏�����
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	// �E�B���h�E�̏�Ԃ�ݒ肷��
	ChangeWindowMode(true);

	// �������ƃ��[�h����񂾂��s��
	InitScore();
	LoadScore();

	// ���͏�����
	InitInput();

	// ��ԍŏ��ɂP�񂾂���鏈��
	SetTransColor(255, 0, 255);	// ���ߐF�w��

	// �E�B���h�E�T�C�Y��ύX
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);

	// �`�悷��X�N���[����ݒ�
	SetDrawScreen(DX_SCREEN_BACK); //�`�悷��X�N���[����ݒ肷��

	//-----------------------------------------

	//�Q�[�����C�����[�v
	while (ProcessMessage() != -1)
	{
		Sleep(1); // �V�X�e���ɏ�����Ԃ�

		//-----------------------------------------
		//�����ɃQ�[���̖{�̂��������ƂɂȂ�
		//-----------------------------------------
		// ���݂̎��Ԃ��擾
		frameRateInfo.currentTime = GetNowCount();

		// �ŏ��̃��[�v�Ȃ�
		// ���݂̎��Ԃ��AFPS�̌v�Z���������Ԃɐݒ�
		if (frameRateInfo.calcFpsTime == 0.0f) {
			frameRateInfo.calcFpsTime = frameRateInfo.currentTime;
			frameRateInfo.fps = (float)FRAME_RATE;
		}

		// ���݂̎��Ԃ��A�O��̃t���[�������
		// 1000/60�~���b(1/60�b)�ȏ�o�߂��Ă����珈�������s����
		if (frameRateInfo.currentTime - frameRateInfo.lastFrameTime >= FRAME_TIME) {
			// �t���[�����s���̎��Ԃ��X�V
			frameRateInfo.lastFrameTime = frameRateInfo.currentTime;

			// �t���[�������J�E���g
			frameRateInfo.count++;

			if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			{
				//�G�X�P�[�v�L�[�������ꂽ��I��
				break;
			}

			//�A��ʂɕ\�����ꂽ���̂�������
			ClearDrawScreen();

			// ���̓X�e�b�v
			StepInput();

			// �V�[��ID�ɂ���ď����̐U�蕪��
			switch (g_CurrentSceneID) {

			case SCENE_ID_INIT_TITLE: {
				// �^�C�g��������
				InitTitle();
			}
			break;

			case SCENE_ID_LOOP_TITLE: {
				// �^�C�g���ʏ폈��
				StepTitle();

				// �^�C�g���`�揈��
				DrawTitle();
			}
			break;

			case SCENE_ID_FIN_TITLE: {
				// �^�C�g���㏈��
				FinTitle();
			}
			break;

			case SCENE_ID_INIT_PLAY: {
				// �v���C������
				InitPlay();
			}
			break;

			case SCENE_ID_LOOP_PLAY: {
				// �v���C�ʏ폈��
				StepPlay();

				// �v���C�`�揈��
				DrawPlay();
			}
			break;

			case SCENE_ID_FIN_PLAY: {
				// �^�C�g���㏈��
				FinPlay();
			}
		    break;

			case SCENE_ID_INIT_CLEAR: {
				// �N���A������
				InitClear();
			}
			break;

			case SCENE_ID_LOOP_CLEAR: {
				// �N���A�ʏ폈��
				StepClear();

				// �N���A�`�揈��
				DrawClear();
			}
			break;

			case SCENE_ID_FIN_CLEAR: {
				// �N���A�㏈��
				FinClear();
			}
			break;

			case SCENE_ID_INIT_GAMEOVER: {
				// �Q�[���I�[�o�[������
				InitGameOver();
			}
			break;

			case SCENE_ID_LOOP_GAMEOVER: {
				// �Q�[���I�[�o�[�ʏ폈��
				StepGameOver();

				// �Q�[���I�[�o�[�`�揈��
				DrawGamrOver();
			}
			break;

			case SCENE_ID_FIN_GAMEOVER: {
				// �Q�[���I�[�o�[�㏈��
				FinGameOver();
			}
			break;
			}

			//���[�v�̏I����
			// FPS�v�Z
			CalcFPS();

			// FPS�\��
			DrawFPS();

			//�B�t���b�v�֐�
			ScreenFlip();
		}
	}

	//-----------------------------------------
	//�Ō�ɂP�񂾂���鏈���������ɏ���

	//�CDX���C�u�����̌㏈��
	DxLib_End();

	//-----------------------------------------

	return 0;
}

// FPS�v�Z
void CalcFPS()
{
	// �O���FPS���v�Z�������Ԃ���̌o�ߎ��Ԃ����߂�
	int difTime = frameRateInfo.currentTime - frameRateInfo.calcFpsTime;
	// �O���FPS���v�Z�������Ԃ���
	// �P�b�ȏ�o�߂��Ă�����FPS���v�Z����
	if (difTime > 1000) {
		// �t���[���񐔂��~���b�ɍ��킹��
		// �����܂ŏo�������̂�float�ɃL���X�g
		float frameCount = (float)(frameRateInfo.count * 1000.0f);
		// FPS�����߂�
		// ���z�̐��l�� 60000 / 1000 �� 60 �ƂȂ�
		frameRateInfo.fps = frameCount / difTime;
		// �t���[�����[�g�J�E���g���N���A
		frameRateInfo.count = 0;
		// FPS���v�Z�������Ԃ��X�V
		frameRateInfo.calcFpsTime = frameRateInfo.currentTime;
	}
}

// FPS�\��(�f�o�b�O�p)
void DrawFPS()
{
	unsigned int color = GetColor(255, 30, 30);
	DrawFormatString(1180, 700, color, "FPS[%.2f]", frameRateInfo.fps);
}