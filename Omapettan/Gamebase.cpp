//********************************************
//Gamebase:ゲームの土台
//********************************************
#include"Gamebase.h"

//publickなメンバ関数
//初期化(DXライブラリと画面の基本設定)
bool GameBase::f_init()
{
	//タイトル
	SetMainWindowText("Window");

	//Windowサイズの設定
	SetGraphMode(640, 480, 16);

	//Windowモード変更と初期化
	ChangeWindowMode(TRUE);
	if (DxLib_Init() != 0) {
		return false;
	}
	//裏画面設定
	SetDrawScreen(DX_SCREEN_BACK);

	//ゲームマネージャー生成
	c_gm = new c_GameManeger();

	// ゲームマネジャ初期化
	c_gm->f_init();

	return true;

}

//ゲームループ
void GameBase::f_loop()
{
	//裏画面を表画面に反映、メッセージ処理、画面クリア
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

		SetMouseDispFlag(false);
		f_input();
		f_update();
		f_output();
		//ループ終了判定
		if (!isRunning) break;
	}
}

//終了判定
void GameBase::f_exit()
{
	//DXライブラリ終了処理
	DxLib_End();
}

//privateなメンバ関数
//入力処理
void GameBase::f_input()
{
	//終了キーの処理と画面遷移
	if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
		isRunning = FALSE;
	}
}

//ゲームオブジェクトの更新
void GameBase::f_update()
{
	c_gm->f_update();
}

//ゲームオブジェクトの描画
void GameBase::f_output()
{
	//ゲーム描画
	c_gm->f_output();
}