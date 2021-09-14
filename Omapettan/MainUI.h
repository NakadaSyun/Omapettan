#pragma once
#include "DxLib.h"
#include "HairVertexBuffer.h"
#include "DrawAcne.h"
#include "Controller.h"

class c_MainUI {
public:
	c_MainUI(int bansokoImg, int mainUIImg);
	~c_MainUI();
	void f_init();		// 初期化
	void f_update();	// 更新
	void f_draw();		// 描画

	void MenuUI();		// メニュー

	int f_GetStartFlg();//startFlgを取得する関数

	bool pauseFlg;		// 一時停止フラグ

	bool hairStateFlg[HAIR_NUM] = { 0 };
	bool acneStateFlg[ACNE_NUM] = { 0 };

	c_GamePad* c_Pad;

	bool isBackTitle;
	bool isNextResult;

	int timeLimit;		// 制限時間
	float rate;			// 率

	int f_getTimer(); //timerの値を取得

	int startFlg;

private:
	void TimeCountUI();	// 時間カウント
	void AchievementUI();// 達成率
	void LifeUI();		// ライフ
	void ThreeCount();	// 3秒カウント

	void Menu_Draw();
	void TimeCount_Draw();
	void Achivement_Draw();
	void Life_Draw();
	void ThreeCount_Draw();

	int time;			// 現在の時間
	int timer;			// 時間カウント
	int minute;			// 分
	int second;			// 秒
	float animCount;

	int maxLife;		// 最大ライフ
	int life;			// ライフ
	float animSpeed;		// ライフのアニメーションスピード
	int damageAnim;		// ダメージ

	int menuNum;		// ポーズ時の選択している番号

	int bansoko_Img;
	int mainUI_Img;

	int menuCount;

	int threeCountTime;
};