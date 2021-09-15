#include"DxLib.h"
#include"LoadSound.h"

Sound g_Snd;


int f_LoadSound(void) {		//音の読み込み

	if ((g_Snd.KAMISORI_Hold = LoadSoundMem("Sound/sword.mp3")) == -1)return -1;						//剃刀を構えたときの音
	if ((g_Snd.HIGESORI_SE = LoadSoundMem("Sound/hige1.mp3")) == -1)return -1;							//毛を剃ったときの音
	if ((g_Snd.StageClear = LoadSoundMem("Sound/歓声と拍手.mp3")) == -1)return -1;						//ステージクリア時の音
	if ((g_Snd.Player_footStep = LoadSoundMem("Sound/footstep.mp3")) == -1)return -1;					//プレイヤーの足音
	if ((g_Snd.Player_footStep_DS = LoadSoundMem("Sound/footstep2.mp3")) == -1)return -1;				//プレイヤーの足音（倍速）
	if ((g_Snd.Menumove = LoadSoundMem("Sound/決定、ボタン押下22.mp3")) == -1)return -1;				//メニュー内の移動時SE
	if ((g_Snd.Menu_Select = LoadSoundMem("Sound/決定、ボタン押下23.mp3")) == -1)return -1;				//メニュー内の決定時SE
	if ((g_Snd.Menu_Open = LoadSoundMem("Sound/決定、ボタン押下26.mp3")) == -1)return -1;				//ポーズ画面開いたときのSE
	if ((g_Snd.Menu_Cansel = LoadSoundMem("Sound/キャンセル2.mp3")) == -1)return -1;					//メニュー内でのキャンセル時のSE
	if ((g_Snd.Customer_Damage = LoadSoundMem("Sound/グサッ1.mp3")) == -1)return -1;					//出来物を剃った時の音
	if ((g_Snd.Customer_Cry[0] = LoadSoundMem("Sound/ダメージ音.wav")) == -1)return -1;					//お客さんのダメージSE1
	if ((g_Snd.Customer_Cry[1] = LoadSoundMem("Sound/ダメージ音２.wav")) == -1)return -1;				//お客さんのダメージSE2
	if ((g_Snd.Customer_Cry[2] = LoadSoundMem("Sound/ダメージ音３.mp3")) == -1)return -1;				//お客さんのダメージSE3
	if ((g_Snd.Customer_Cry[3] = LoadSoundMem("Sound/ダメージ音４.wav")) == -1)return -1;				//お客さんのダメージSE4
	if ((g_Snd.GameOver = LoadSoundMem("Sound/sei_ge_garasu_ware03.mp3")) == -1)return -1;				//ゲームオーバー時SE
	if ((g_Snd.TitleBGM = LoadSoundMem("Sound/MusMus-BGM-128.mp3")) == -1)return -1;					//タイトルBGM
	if ((g_Snd.StageBGM = LoadSoundMem("Sound/StageBGM.mp3")) == -1)return -1;							//ステージBGM

	//下記のSE,BGMの音量を下げる
	g_Snd.SetSound();
	/*ChangeVolumeSoundMem(100, g_Snd.Player_footStep);
	ChangeVolumeSoundMem(100, g_Snd.GameOver);
	ChangeVolumeSoundMem(100, g_Snd.TitleBGM);
	ChangeVolumeSoundMem(150, g_Snd.StageBGM);*/


	return 0;
}

// 音量設定
void Sound::SetSound() {
	printf("%d\n", g_Snd.volume);

	ChangeVolumeSoundMem(int(              25.5 * float(g_Snd.volume)), g_Snd.KAMISORI_Hold);
	ChangeVolumeSoundMem(int(              25.5 * float(g_Snd.volume)), g_Snd.HIGESORI_SE);
	ChangeVolumeSoundMem(int(              25.5 * float(g_Snd.volume)), g_Snd.StageClear);
	ChangeVolumeSoundMem(int(100.0 / 255 * 25.5 * float(g_Snd.volume)), g_Snd.Player_footStep);
	ChangeVolumeSoundMem(int(              25.5 * float(g_Snd.volume)), g_Snd.Menumove);
	ChangeVolumeSoundMem(int(              25.5 * float(g_Snd.volume)), g_Snd.Menu_Select);
	ChangeVolumeSoundMem(int(              25.5 * float(g_Snd.volume)), g_Snd.Menu_Open);
	ChangeVolumeSoundMem(int(              25.5 * float(g_Snd.volume)), g_Snd.Menu_Cansel);
	ChangeVolumeSoundMem(int(              25.5 * float(g_Snd.volume)), g_Snd.Customer_Damage);
	ChangeVolumeSoundMem(int(              25.5 * float(g_Snd.volume)), g_Snd.Customer_Cry[0]);
	ChangeVolumeSoundMem(int(              25.5 * float(g_Snd.volume)), g_Snd.Customer_Cry[1]);
	ChangeVolumeSoundMem(int(              25.5 * float(g_Snd.volume)), g_Snd.Customer_Cry[2]);
	ChangeVolumeSoundMem(int(              25.5 * float(g_Snd.volume)), g_Snd.Customer_Cry[3]);
	ChangeVolumeSoundMem(int(100.0 / 255 * 25.5 * float(g_Snd.volume)), g_Snd.GameOver);
	ChangeVolumeSoundMem(int(100.0 / 255 * 25.5 * float(g_Snd.volume)), g_Snd.TitleBGM);
	ChangeVolumeSoundMem(int(150.0 / 255 * 25.5 * float(g_Snd.volume)), g_Snd.StageBGM);
}