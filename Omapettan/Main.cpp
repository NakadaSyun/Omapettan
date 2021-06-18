//てってれー

#include"DxLib.h"
//
////プログラムはWinMainから始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	SetGraphMode(640, 480, 16);
	if (DxLib_Init() == -1) return -1;

	int Cr = GetColor(0, 0, 255);
	DrawCircle(320, 240, 150, Cr, TRUE);
	Cr = GetColor(255, 255, 255);
	DrawCircle(320, 270, 120, Cr, TRUE);
	DrawOval(290, 160, 30, 60, Cr, TRUE);
	DrawOval(350, 160, 30, 60, Cr, TRUE);
	Cr = GetColor(0, 0, 0);
	DrawOval(290, 160, 30, 60, Cr, FALSE);
	DrawOval(350, 160, 30, 60, Cr, FALSE);
	DrawCircle(290, 150, 5, Cr, TRUE);
	DrawCircle(350, 150, 5, Cr, TRUE);
	Cr = GetColor(255, 0, 0);
	DrawCircle(320, 230, 20, Cr, TRUE);
	DrawTriangle(320, 350, 260, 300, 380, 300, Cr, TRUE);
	Cr = GetColor(0, 0, 0);
	DrawLine(320, 250, 320, 300, Cr);
	DrawLine(290, 250, 200, 200, Cr);	//ひげ
	DrawLine(290, 260, 200, 250, Cr);
	DrawLine(290, 270, 200, 300, Cr);
	DrawLine(350, 250, 440, 200, Cr);
	DrawLine(350, 260, 440, 250, Cr);
	DrawLine(350, 270, 440, 300, Cr);




	WaitKey();		//キー入力待ち

	DxLib_End();	//DXライブラリ使用の終了処理

	return 0;		//ソフトの終了
}