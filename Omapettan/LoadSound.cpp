#include"DxLib.h"
#include"LoadSound.h"

Sound g_Snd;


int f_LoadSound(void) {		//���̓ǂݍ���

	if ((g_Snd.KAMISORI_Hold = LoadSoundMem("Sound/sword.mp3")) == -1)return -1;						//�䓁���\�����Ƃ��̉�
	if ((g_Snd.HIGESORI_SE = LoadSoundMem("Sound/hige1.mp3")) == -1)return -1;							//�т������Ƃ��̉�
	if ((g_Snd.StageClear = LoadSoundMem("Sound/�����Ɣ���.mp3")) == -1)return -1;						//�X�e�[�W�N���A���̉�
	if ((g_Snd.Player_footStep = LoadSoundMem("Sound/footstep.mp3")) == -1)return -1;					//�v���C���[�̑���
	if ((g_Snd.Player_footStep_DS = LoadSoundMem("Sound/footstep2.mp3")) == -1)return -1;				//�v���C���[�̑����i�{���j
	if ((g_Snd.Menumove = LoadSoundMem("Sound/����A�{�^������22.mp3")) == -1)return -1;				//���j���[���̈ړ���SE
	if ((g_Snd.Menu_Select = LoadSoundMem("Sound/����A�{�^������23.mp3")) == -1)return -1;				//���j���[���̌��莞SE
	if ((g_Snd.Menu_Open = LoadSoundMem("Sound/����A�{�^������26.mp3")) == -1)return -1;				//�|�[�Y��ʊJ�����Ƃ���SE
	if ((g_Snd.Menu_Cansel = LoadSoundMem("Sound/�L�����Z��2.mp3")) == -1)return -1;					//���j���[���ł̃L�����Z������SE
	if ((g_Snd.Customer_Damage = LoadSoundMem("Sound/�O�T�b1.mp3")) == -1)return -1;					//�o�������������̉�
	if ((g_Snd.Customer_Cry[0] = LoadSoundMem("Sound/�_���[�W��.wav")) == -1)return -1;					//���q����̃_���[�WSE1
	if ((g_Snd.Customer_Cry[1] = LoadSoundMem("Sound/�_���[�W���Q.wav")) == -1)return -1;				//���q����̃_���[�WSE2
	if ((g_Snd.Customer_Cry[2] = LoadSoundMem("Sound/�_���[�W���R.mp3")) == -1)return -1;				//���q����̃_���[�WSE3
	if ((g_Snd.Customer_Cry[3] = LoadSoundMem("Sound/�_���[�W���S.wav")) == -1)return -1;				//���q����̃_���[�WSE4
	if ((g_Snd.TimeUp = LoadSoundMem("Sound/�����I���̃S���O.mp3")) == -1)return -1;					//�^�C���A�b�v��SE
	if ((g_Snd.ThreeCount = LoadSoundMem("Sound/Countdown01-5.mp3")) == -1)return -1;					//3�b�J�E���gSE
	if ((g_Snd.ThreeCountStart = LoadSoundMem("Sound/Countdown01-6.mp3")) == -1)return -1;				//3�b�J�E���g(�Q�[���J�n)SE
	if ((g_Snd.GameOver = LoadSoundMem("Sound/sei_ge_garasu_ware03.mp3")) == -1)return -1;				//�Q�[���I�[�o�[��SE
	if ((g_Snd.TitleBGM = LoadSoundMem("Sound/MusMus-BGM-128.mp3")) == -1)return -1;					//�^�C�g��BGM
	if ((g_Snd.StageBGM = LoadSoundMem("Sound/StageBGM.mp3")) == -1)return -1;							//�X�e�[�WBGM

	//���L��SE,BGM�̉��ʂ�������
	g_Snd.SetSound();
	/*ChangeVolumeSoundMem(100, g_Snd.Player_footStep);
	ChangeVolumeSoundMem(100, g_Snd.GameOver);
	ChangeVolumeSoundMem(100, g_Snd.TitleBGM);
	ChangeVolumeSoundMem(150, g_Snd.StageBGM);*/


	return 0;
}

// ���ʐݒ�
void Sound::SetSound() {

	ChangeVolumeSoundMem(int(              25.5 * float(g_Snd.volume)), g_Snd.KAMISORI_Hold);
	ChangeVolumeSoundMem(int(              25.5 * float(g_Snd.volume)), g_Snd.HIGESORI_SE);
	ChangeVolumeSoundMem(int(              25.5 * float(g_Snd.volume)), g_Snd.StageClear);
	ChangeVolumeSoundMem(int(150.0 / 255 * 25.5 * float(g_Snd.volume)), g_Snd.Player_footStep);
	ChangeVolumeSoundMem(int(150.0 / 255 * 25.5 * float(g_Snd.volume)), g_Snd.Player_footStep_DS);
	ChangeVolumeSoundMem(int(              25.5 * float(g_Snd.volume)), g_Snd.Menumove);
	ChangeVolumeSoundMem(int(              25.5 * float(g_Snd.volume)), g_Snd.Menu_Select);
	ChangeVolumeSoundMem(int(              25.5 * float(g_Snd.volume)), g_Snd.Menu_Open);
	ChangeVolumeSoundMem(int(              25.5 * float(g_Snd.volume)), g_Snd.Menu_Cansel);
	ChangeVolumeSoundMem(int(              25.5 * float(g_Snd.volume)), g_Snd.Customer_Damage);
	ChangeVolumeSoundMem(int(              25.5 * float(g_Snd.volume)), g_Snd.Customer_Cry[0]);
	ChangeVolumeSoundMem(int(              25.5 * float(g_Snd.volume)), g_Snd.Customer_Cry[1]);
	ChangeVolumeSoundMem(int(              25.5 * float(g_Snd.volume)), g_Snd.Customer_Cry[2]);
	ChangeVolumeSoundMem(int(              25.5 * float(g_Snd.volume)), g_Snd.Customer_Cry[3]);
	ChangeVolumeSoundMem(int(              25.5 * float(g_Snd.volume)), g_Snd.TimeUp);
	ChangeVolumeSoundMem(int(              25.5 * float(g_Snd.volume)), g_Snd.ThreeCount);
	ChangeVolumeSoundMem(int(              25.5 * float(g_Snd.volume)), g_Snd.ThreeCountStart);
	ChangeVolumeSoundMem(int(100.0 / 255 * 25.5 * float(g_Snd.volume)), g_Snd.GameOver);
	ChangeVolumeSoundMem(int(100.0 / 255 * 25.5 * float(g_Snd.volume)), g_Snd.TitleBGM);
	ChangeVolumeSoundMem(int(150.0 / 255 * 25.5 * float(g_Snd.volume)), g_Snd.StageBGM);
}

// ���ʐݒ�
void Sound::SetSound_Menumove(int volume) {
	ChangeVolumeSoundMem(int(              25.5 * float(volume)), g_Snd.Menumove);
	ChangeVolumeSoundMem(int(150.0 / 255 * 25.5 * float(volume)), g_Snd.StageBGM);
}