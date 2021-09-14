#include "MainScene.h"
#include "ResultScene.h"
#include "LoadSound.h"
#include "TitleScene.h"

extern Sound g_Snd;
//DATEDATA Date;
//
//static int yeah;
//static int mon;
//static int day;
//static int hour;
//static int minute;
//static int sec;
int LightHandle;
c_Main::c_Main() {
	//�Q�[���}�l�[�W���[����
	c_gm = new c_GameManager();// ���C�g�n���h���̃��C�g�̌��ʂ��킩��Ղ��悤�ɕW�����C�g�𖳌���
	SetLightEnable(FALSE);

	// �f�B���N�V���i���^�C�v�̃��C�g�n���h�����쐬
	LightHandle = CreateDirLightHandle(VGet(1.0f, -1.0f, 1.0f));

	// ���C�g�n���h���̃f�B�t���[�Y�J���[��F�ɂ���
	SetLightDifColorHandle(LightHandle, GetColorF(0.0f, 0.0f, 1.0f, 0.0f));

	// �Q�[���}�l�W��������
	c_gm->f_init();
	IsNextScene = false;

	//
	StageOverImage = LoadGraph("images/GameOver.png");
	StageClearImage = LoadGraph("images/StageClear.png");
	
	//�f�o�b�O���[�h���\��
	DebugFlg = false;
	//�L�[��������ĂȂ���Ԃ�
	KeyDownFlg = false;
	//�p�b�h�̃L�[��������Ă��邩
	padKeyFlg = false;

	//GetDateTime(&Date);
	//yeah = Date.Year;
	//mon = Date.Mon;
	//day = Date.Day;
	//hour = Date.Hour;
	//minute = Date.Min;
	//sec = Date.Sec;



	

}

c_Main::~c_Main() {
	delete c_gm;
}

c_Scene* c_Main::f_update() {
	c_gm->f_update();

	const char data[] = __DATE__;
	const char time[] = __TIME__;
	DrawFormatString(500, 420, 0x0000ff, "%c%c%c%c %c%c%c %c%c\n %s",
		data[7], data[8], data[9], data[10],
		data[0], data[1], data[2],
		data[4], data[5],
		time);
	

	//DrawFormatString(300, 460, 0x0000ff, "�r���h�쐬����%d�N%d��%d��%d��%d��%d�b\n", yeah, mon, day, hour, minute, sec);

	//�X�e�[�WBGM����
	if (CheckSoundMem(g_Snd.StageBGM) == 0) {
		PlaySoundMem(g_Snd.StageBGM, DX_PLAYTYPE_LOOP);
	}

	if (CheckHitKey(KEY_INPUT_SPACE) == 1 && IsNextScene) {
		StopSoundMem(g_Snd.StageBGM);
		return new c_Result(c_gm->c_mainUI->rate);
	}
	
	if (CheckHitKey(KEY_INPUT_SPACE) == 0 && !IsNextScene) {
		IsNextScene = true;
	}

	//�f�o�b�O���[�h�̎�t����
	//if (DebugLoadTime > 120)
	{
		//if (c_gm->c_player->c_pad->crossKey == LEFT) {
		//	//�f�o�b�O���[�h�\��
		//	if (!DebugFlg && !KeyDownFlg)
		//	{
		//		DebugFlg = true;
		//		KeyDownFlg = true;
		//	}
		//	//�f�o�b�O���[�h��\��
		//	else if (DebugFlg && !KeyDownFlg)
		//	{
		//		DebugFlg = false;
		//		KeyDownFlg = true;
		//	}
		//}
		//if (c_gm->c_player->c_pad->crossKey == 0) {
		//	KeyDownFlg = false;
		//}
		//if (CheckHitKey(KEY_INPUT_RETURN) == 1) {
		//	//�f�o�b�O���[�h�\��
		//	if (!DebugFlg && !KeyDownFlg)
		//	{
		//		DebugFlg = true;
		//		KeyDownFlg = true;
		//	}
		//	//�f�o�b�O���[�h��\��
		//	else if (DebugFlg && !KeyDownFlg)
		//	{
		//		DebugFlg = false;
		//		KeyDownFlg = true;
		//	}
		//}
		//if (CheckHitKey(KEY_INPUT_RETURN) == 0) {
		//	KeyDownFlg = false;
		//}
	}
	//else
	{
		//�ǂݍ��ݎ��ԉ��Z
		//DebugLoadTime++;
	}

	//�f�o�b�O���[�h��\�����邩���Ȃ���
	f_debug(DebugFlg);


	//�т��S�����ꂽ��ԂȂ�Result�V�[����
	if (c_gm->c_hair->f_hairStatusSee()) {
		isClearFlg = true;

		if (StageClearTime < 120)
		{
			StageClearTime++;
		}
		else if (StageClearTime < 240)
		{
			StageClearTime++;
			DrawGraph(0, 0, StageClearImage, true);
			if (CheckSoundMem(g_Snd.StageClear) == 0) {
				PlaySoundMem(g_Snd.StageClear, DX_PLAYTYPE_BACK);
			}
			
		}
		else
		{

			StopSoundMem(g_Snd.StageBGM);
			return new c_Result(c_gm->c_mainUI->rate);
		}
	}
	
	//�����o�����S�����ꂽ��ԂȂ�Result�V�[����
	if (c_gm->c_acne->AcneStatus() && isClearFlg == false) {
		c_gm->c_player->IsMove = false;
		
		if (StageClearTime < 120)
		{
			StageClearTime++;
		}
		else if (StageClearTime < 240)
		{
			StageClearTime++;
			DrawGraph(0, 0, StageOverImage, false);
			if (CheckSoundMem(g_Snd.GameOver) == 0) {
				PlaySoundMem(g_Snd.GameOver, DX_PLAYTYPE_BACK);
			}
			
		}
		else
		{
			StopSoundMem(g_Snd.StageBGM);
			return new c_Result(c_gm->c_mainUI->rate);
		}
	}

	// �|�[�Y���j���[����^�C�g����
	if (c_gm->c_mainUI->isBackTitle) {
		StopSoundMem(g_Snd.StageBGM);
		return new c_Title();
	}
	// �^�C���I�[�o�[�Ń��U���g��
	if (c_gm->c_mainUI->isNextResult) {
		c_gm->c_player->IsMove = false;
		StopSoundMem(g_Snd.StageBGM);

		if (StageClearTime < 180)
		{
			StageClearTime++;
			SetFontSize(64);// �T�C�Y64
			DrawFormatString(190, 220, 0x00ff00, "TIME UP!");
			SetFontSize(16);// �T�C�Y16
		}
		else
		{
			return new c_Result(c_gm->c_mainUI->rate);
		}
	}

	return this;
}

void c_Main::f_output() const{
	
	c_gm->f_output();
}

void c_Main::f_debug(bool flg) {

	{
		//�\���L�[���������Ɩт��c�ɕ���
		if (c_gm->c_player->c_pad->crossKey == LEFT && !padKeyFlg && !DebugFlg)
		{
			DebugFlg = true;
			padKeyFlg = true;
		}
		else if (c_gm->c_player->c_pad->crossKey == LEFT && !padKeyFlg && DebugFlg)
		{
			DebugFlg = false;
			padKeyFlg = true;
		}

		if (c_gm->c_player->c_pad->crossKey == 0 && padKeyFlg)
		{
			padKeyFlg = false;
			//DebugFlg = false;
		}

		if (DebugFlg)
		{
			//�т̓����蔻��\��
			c_gm->c_hair->CubeDraw();
			//�v���C���[�i�䓁�j�̓����蔻��\��
			c_gm->c_player->c_colision->f_PolyDraw(c_gm->c_player->f_GetPlayerRotationY());

			//�����o���̓����蔻��\��
			for (int num = 0; num < ACNE_NUM; num++)
			{
				// �����o���̓����蔻��\��
				c_gm->c_acne->c_collision[num]->f_CubeDraw();
			}

			//padKeyFlg = true;

		}
	}


	//�\���L�[���������Ɩт��c�ɕ���
	if (c_gm->c_player->c_pad->crossKey == DOWN && !padKeyFlg)
	{
		padKeyFlg = true;
		c_gm->c_hair->f_DebugHair(padKeyFlg, false);
	}
	else if (c_gm->c_player->c_pad->crossKey == 0 && padKeyFlg)
	{
		padKeyFlg = false;
	}

	//�\���L�[��������Ɩт�S�ď���
	if (c_gm->c_player->c_pad->crossKey == UP && !padKeyFlg)
	{
		padKeyFlg = true;
		c_gm->c_hair->f_DebugHair(padKeyFlg, true);
	}
	else if (c_gm->c_player->c_pad->crossKey == 0 && padKeyFlg)
	{
		padKeyFlg = false;
	}


	//�\���L�[�E�������ƃv���C���[�̃_�b�V���̔{����؂�ւ��ł���
	if (c_gm->c_player->c_pad->crossKey == RIGHT && !padKeyFlg)
	{
		//�v���C���[�̃_�b�V���̔{����������
		playerDebug = c_gm->c_player->f_PlayerDebug(padKeyFlg, playerDebug);
		padKeyFlg = true;
	}
	else if (c_gm->c_player->c_pad->crossKey == 0 && padKeyFlg)
	{
		padKeyFlg = false;
	}

	//Y�{�^���������Ǝ��Ԃ��O�ɂȂ�
	if (c_gm->c_player->c_pad->IsButton4)
	{
		f_debugUI();
	}

}

void c_Main::f_debugUI() {
	int timeLimit = 2;
	c_gm->c_mainUI->timeLimit = timeLimit + (c_gm->c_mainUI->f_getTimer() / 1000);
}


void c_Main::f_fadein() {
	static int c = 0;
	c += 3;
	if (c > 255)c = 255;
	SetDrawBright(c, c, c);
}

void c_Main::f_fadeout() {
	static int c = 255;
	c -= 3;
	if (c < 0)c = 0;
	SetDrawBright(c, c, c);
}