#include"DxLib.h"
#include"LoadSound.h"

extern Sound g_Snd;

int LoadSound(void) {		//‰¹‚Ì“Ç‚İ‚İ
	if ((g_Snd.KAMISORI_Hold = LoadSoundMem("Sound/sword.mp3")) == -1)return -1;					//’ä“‚ğ\‚¦‚½‚Æ‚«‚Ì‰¹
}