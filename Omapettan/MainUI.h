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
	bool pauseFlg;		// 一時停止フラグ

	bool hairStateFlg[HAIR_NUM] = { 0 };
	bool acneStateFlg[ACNE_NUM] = { 0 };

	c_GamePad* c_Pad;

	bool isBackTitle;
	bool isNextResult;

private:
	void TimeCountUI();	// 時間カウント
	void AchievementUI();// 達成率
	void LifeUI();		// ライフ

	void Menu_Draw();
	void TimeCount_Draw();
	void Achivement_Draw();
	void Life_Draw();

	int timeLimit;		// 制限時間
	int time;			// 現在の時間
	int timer;			// 時間カウント
	int minute;			// 分
	int second;			// 秒
	float animCount;

	float rate;			// 率

	int maxLife;		// 最大ライフ
	int life;			// ライフ
	float animSpeed;		// ライフのアニメーションスピード
	int damageAnim;		// ダメージ

	int menuNum;		// ポーズ時の選択している番号

	int bansoko_Img;
	int mainUI_Img;

	int menuCount;
};