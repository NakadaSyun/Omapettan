#include"DxLib.h"
#include"LoadSound.h"

extern Sound g_Snd;

int LoadSound(void) {		//音の読み込み
	if ((g_Snd.KAMISORI_Hold = LoadSoundMem("Sound/sword.mp3")) == -1)return -1;					//剃刀を構えたときの音
}