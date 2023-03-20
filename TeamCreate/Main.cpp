
#include "DxLib.h"	//DX���C�u�����̃C���N���[�h

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

	SetDrawScreen(DX_SCREEN_BACK);	//�`�悷��X�N���[����ݒ肷��

	//-----------------------------------------

	//�Q�[�����C�����[�v
	while (ProcessMessage() != -1)
	{
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			//�G�X�P�[�v�L�[�������ꂽ��I��
			break;
		}

		//�A��ʂɕ\�����ꂽ���̂�������
		ClearDrawScreen();


		//-----------------------------------------
		//�����ɃQ�[���̖{�̂��������ƂɂȂ�
		//-----------------------------------------

		//���[�v�̏I����
		//�B�t���b�v�֐�
		ScreenFlip();

	}

	//-----------------------------------------
	//�Ō�ɂP�񂾂���鏈���������ɏ���

	//�CDX���C�u�����̌㏈��
	DxLib_End();

	//-----------------------------------------

	return 0;
}
