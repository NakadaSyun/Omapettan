#include"DxLib.h"
#include"LoadSound.h"

Sound g_Snd;


int f_LoadSound(void) {		//���̓ǂݍ���

	if ((g_Snd.KAMISORI_Hold = LoadSoundMem("Sound/sword.mp3")) == -1)return -1;					//�䓁���\�����Ƃ��̉�
	if ((g_Snd.HIGESORI_SE = LoadSoundMem("Sound/hige1.mp3")) == -1)return -1;					//�䓁���\�����Ƃ��̉�
	if ((g_Snd.StageClear = LoadSoundMem("Sound/�����Ɣ���.mp3")) == -1)return -1;					//�䓁���\�����Ƃ��̉�
	if ((g_Snd.Player_footStep = LoadSoundMem("Sound/footstep.mp3")) == -1)return -1;					//�䓁���\�����Ƃ��̉�
	if ((g_Snd.Menumove = LoadSoundMem("Sound/����A�{�^������22.mp3")) == -1)return -1;					//�䓁���\�����Ƃ��̉�
	if ((g_Snd.Menu_Select = LoadSoundMem("Sound/����A�{�^������23.mp3")) == -1)return -1;					//�䓁���\�����Ƃ��̉�
	if ((g_Snd.Menu_Open = LoadSoundMem("Sound/����A�{�^������26.mp3")) == -1)return -1;					//�䓁���\�����Ƃ��̉�
	if ((g_Snd.Menu_Cansel = LoadSoundMem("Sound/�L�����Z��2.mp3")) == -1)return -1;					//�䓁���\�����Ƃ��̉�
	if ((g_Snd.Customer_Damage = LoadSoundMem("Sound/�O�T�b1.mp3")) == -1)return -1;					//�䓁���\�����Ƃ��̉�
	if ((g_Snd.GameOver = LoadSoundMem("Sound/sei_ge_garasu_ware03.mp3")) == -1)return -1;					//�䓁���\�����Ƃ��̉�

	ChangeVolumeSoundMem(100, g_Snd.Player_footStep);
	ChangeVolumeSoundMem(100, g_Snd.GameOver);


	return 0;
}

