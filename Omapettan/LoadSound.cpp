#include"DxLib.h"
#include"LoadSound.h"

Sound g_Snd;


int f_LoadSound(void) {		//���̓ǂݍ���

	if ((g_Snd.KAMISORI_Hold = LoadSoundMem("Sound/sword.mp3")) == -1)return -1;						//�䓁���\�����Ƃ��̉�
	if ((g_Snd.HIGESORI_SE = LoadSoundMem("Sound/hige1.mp3")) == -1)return -1;							//�т������Ƃ��̉�
	if ((g_Snd.StageClear = LoadSoundMem("Sound/�����Ɣ���.mp3")) == -1)return -1;						//�X�e�[�W�N���A���̉�
	if ((g_Snd.Player_footStep = LoadSoundMem("Sound/footstep.mp3")) == -1)return -1;					//�v���C���[�̑���
	if ((g_Snd.Menumove = LoadSoundMem("Sound/����A�{�^������22.mp3")) == -1)return -1;				//���j���[���̈ړ���SE
	if ((g_Snd.Menu_Select = LoadSoundMem("Sound/����A�{�^������23.mp3")) == -1)return -1;				//���j���[���̌��莞SE
	if ((g_Snd.Menu_Open = LoadSoundMem("Sound/����A�{�^������26.mp3")) == -1)return -1;				//�|�[�Y��ʊJ�����Ƃ���SE
	if ((g_Snd.Menu_Cansel = LoadSoundMem("Sound/�L�����Z��2.mp3")) == -1)return -1;					//���j���[���ł̃L�����Z������SE
	if ((g_Snd.Customer_Damage = LoadSoundMem("Sound/�O�T�b1.mp3")) == -1)return -1;					//�o�������������̉�
	if ((g_Snd.Customer_Cry[0] = LoadSoundMem("Sound/�_���[�W��.wav")) == -1)return -1;					//���q����̃_���[�WSE1
	if ((g_Snd.Customer_Cry[1] = LoadSoundMem("Sound/�_���[�W���Q.wav")) == -1)return -1;				//���q����̃_���[�WSE2
	if ((g_Snd.Customer_Cry[2] = LoadSoundMem("Sound/�_���[�W���R.mp3")) == -1)return -1;				//���q����̃_���[�WSE3
	if ((g_Snd.Customer_Cry[3] = LoadSoundMem("Sound/�_���[�W���S.wav")) == -1)return -1;				//���q����̃_���[�WSE4
	if ((g_Snd.GameOver = LoadSoundMem("Sound/sei_ge_garasu_ware03.mp3")) == -1)return -1;				//�Q�[���I�[�o�[��SE
	if ((g_Snd.TitleBGM = LoadSoundMem("Sound/MusMus-BGM-128.mp3")) == -1)return -1;					//�^�C�g��BGM
	if ((g_Snd.StageBGM = LoadSoundMem("Sound/StageBGM.mp3")) == -1)return -1;							//�X�e�[�WBGM

	//���L��SE,BGM�̉��ʂ�������
	ChangeVolumeSoundMem(100, g_Snd.Player_footStep);
	ChangeVolumeSoundMem(100, g_Snd.GameOver);
	ChangeVolumeSoundMem(100, g_Snd.TitleBGM);
	ChangeVolumeSoundMem(150, g_Snd.StageBGM);


	return 0;
}

