#include"DxLib.h"
#include"LoadSound.h"

Sound g_Snd;


int f_LoadSound(void) {		//音の読み込み

	if ((g_Snd.KAMISORI_Hold = LoadSoundMem("Sound/sword.mp3")) == -1)return -1;					//剃刀を構えたときの音
	if ((g_Snd.HIGESORI_SE = LoadSoundMem("Sound/hige1.mp3")) == -1)return -1;					//剃刀を構えたときの音
	if ((g_Snd.StageClear = LoadSoundMem("Sound/歓声と拍手.mp3")) == -1)return -1;					//剃刀を構えたときの音
	if ((g_Snd.Player_footStep = LoadSoundMem("Sound/footstep.mp3")) == -1)return -1;					//剃刀を構えたときの音
	if ((g_Snd.Menumove = LoadSoundMem("Sound/決定、ボタン押下22.mp3")) == -1)return -1;					//剃刀を構えたときの音
	if ((g_Snd.Menu_Select = LoadSoundMem("Sound/決定、ボタン押下23.mp3")) == -1)return -1;					//剃刀を構えたときの音
	if ((g_Snd.Menu_Open = LoadSoundMem("Sound/決定、ボタン押下26.mp3")) == -1)return -1;					//剃刀を構えたときの音
	if ((g_Snd.Menu_Cansel = LoadSoundMem("Sound/キャンセル2.mp3")) == -1)return -1;					//剃刀を構えたときの音
	if ((g_Snd.Customer_Damage = LoadSoundMem("Sound/グサッ1.mp3")) == -1)return -1;					//剃刀を構えたときの音

	ChangeVolumeSoundMem(100, g_Snd.Player_footStep);


	return 0;
}

