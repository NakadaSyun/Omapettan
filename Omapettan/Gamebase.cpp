//********************************************
//Gamebase:�Q�[���̓y��
//********************************************
#include"Gamebase.h"

//publick�ȃ����o�֐�
//������(DX���C�u�����Ɖ�ʂ̊�{�ݒ�)
bool GameBase::f_init()
{
	//�^�C�g��
	SetMainWindowText("Window");

	//Window�T�C�Y�̐ݒ�
	SetGraphMode(640, 480, 16);

	//Window���[�h�ύX�Ə�����
	ChangeWindowMode(TRUE);
	if (DxLib_Init() != 0) {
		return false;
	}
	//����ʐݒ�
	SetDrawScreen(DX_SCREEN_BACK);

	// �y�o�b�t�@���g�p����
	SetUseZBufferFlag(TRUE);

	// �y�o�b�t�@�ւ̏������݂��s��
	SetWriteZBufferFlag(TRUE);

	//�Q�[���}�l�[�W���[����
	c_gm = new c_GameManager();

	// �Q�[���}�l�W��������
	c_gm->f_init();

	return true;

}

//�Q�[�����[�v
void GameBase::f_loop()
{
	//����ʂ�\��ʂɔ��f�A���b�Z�[�W�����A��ʃN���A
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

		SetMouseDispFlag(false);
		f_input();
		f_update();
		f_output();
		//���[�v�I������
		if (!isRunning) break;
	}
}

//�I������
void GameBase::f_exit()
{
	//DX���C�u�����I������
	DxLib_End();
}

//private�ȃ����o�֐�
//���͏���
void GameBase::f_input()
{
	//�I���L�[�̏����Ɖ�ʑJ��
	if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
		isRunning = FALSE;
	}
}

//�Q�[���I�u�W�F�N�g�̍X�V
void GameBase::f_update()
{
	c_gm->f_update();
}

//�Q�[���I�u�W�F�N�g�̕`��
void GameBase::f_output()
{
	//�Q�[���`��
	c_gm->f_output();
}