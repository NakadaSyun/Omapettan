//********************************************
//Gamebase:ゲームの土台
//********************************************
#include"Gamebase.h"


//publickなメンバ関数
//初期化(DXライブラリと画面の基本設定)
bool GameBase::f_init()
{
	//タイトル
	SetMainWindowText("こびとサロン");

	//Windowサイズの設定
	SetGraphMode(640, 480, 16);

	isRunning = TRUE;


	//Windowモード変更と初期化
	ChangeWindowMode(TRUE);
	if (DxLib_Init() != 0) {
		return false;
	}

	//音の読み込み
	if (f_LoadSound() == -1) return false;

	//裏画面設定
	SetDrawScreen(DX_SCREEN_BACK);

	// Ｚバッファを使用する
	SetUseZBufferFlag(TRUE);

	// Ｚバッファへの書き込みを行う
	SetWriteZBufferFlag(TRUE);

	//シーンマネージャー作成
	c_sm = new c_SceneManager();


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
	//c_gm->f_update();
	c_sm->f_update();
}

//ゲームオブジェクトの描画
void GameBase::f_output()
{
	//ゲーム描画
	//c_gm->f_output();
	c_sm->f_output();
}