#include "CameraCon.h"

 c_CameraCon::c_CameraCon() {
	 VRotate = 0.0f;         //垂直回転
	 HRotate = 0.0f;        //水平回転
	 TRotate = 0.0f;         //捻り回転

	 position = VGet(320.0f, 100.0f, -200.0f);

	 rotation = VGet(VRotate, HRotate, TRotate);
}

 void c_CameraCon::f_update() {
	 f_setPosition();
	 f_setRotaion();

	 // カメラの位置と回転値をセット、カメラの位置は原点
	 SetCameraPositionAndAngle(position, rotation.x, rotation.y, rotation.z );
 }

 void c_CameraCon::f_setPosition() {
	 float CamX = 0.0f;            //カメラのX軸
	 float CamY = 0.0f;            //カメラのY軸
	 float CamZ = 0.0f;            //カメラのZ軸

	 if (CheckHitKey(KEY_INPUT_W) == 1) {
		 CamZ += 10.0f;
	 }
	 if (CheckHitKey(KEY_INPUT_A) == 1) {
		 CamX -= 10.0f;
	 }
	 if (CheckHitKey(KEY_INPUT_S) == 1) {
		 CamZ -= 10.0f;
	 }
	 if (CheckHitKey(KEY_INPUT_D) == 1) {
		 CamX += 10.0f;
	 }
	 if (CheckHitKey(KEY_INPUT_E) == 1) {
		 CamY += 10.0f;
	 }
	 if (CheckHitKey(KEY_INPUT_Q) == 1) {
		 CamY -= 10.0f;
	 }

	 printf("X = %f  Y = %f  Z = %f\n", HRotate, VRotate, TRotate);

	 position = VGet(position.x + CamX, position.y + CamY, position.z + CamZ);
 }

 void c_CameraCon::f_setRotaion() {
	 int Nowx, Nowy;
	 GetMousePoint(&Nowx, &Nowy);

	 static int Oldx = Nowx, Oldy = Nowy;

	 if (Oldx < Nowx) {
		 HRotate += (Nowx % 10) * 0.005f;
	 }
	 if (Oldx > Nowx) {
		 HRotate -= (Nowx % 10) * 0.005f;
	 }
	 if (Oldy < Nowy) {
		 VRotate += (Nowy % 10) * 0.005f;
	 }
	 if (Oldy > Nowy) {
		 VRotate -= (Nowy % 10) * 0.005f;
	 }

	 rotation = VGet(VRotate, HRotate, TRotate);
	 
	 Oldx = Nowx;
	 Oldy = Nowy;
 }