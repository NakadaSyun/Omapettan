#include "DxLib.h"
#include "Gamebase.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_
	HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {

	GameBase gameBase;


	//デバックコンソールの表示
	//AllocConsole();
	//FILE* fp;
	//freopen_s(&fp, "CONOUT$", "w", stdout);
	//freopen_s(&fp, "CONIN$", "r", stdin);
	//printf("デバックコンソール\n");

	//ゲームの環境設定
	if (gameBase.f_init() == false) {
		return -1;
	}

	//ゲームループ
	gameBase.f_loop();

	//ゲーム終了処理
	gameBase.f_exit();

	// ソフトの終了
	return 0;
}