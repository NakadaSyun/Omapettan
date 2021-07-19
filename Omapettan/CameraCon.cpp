#include "CameraCon.h"
#include <math.h>
#include "GameManeger.h"

#define PI 3.141592653589793


 c_CameraCon::c_CameraCon() {
	 VRotate = PI/4;         //垂直回転
	 HRotate = 0.0f;        //水平回転
	 TRotate = 0.0f;         //捻り回転

	 position = Cameradistance;	//カメラの座標

	 rotation = VGet(VRotate, HRotate, TRotate);
}

 void c_CameraCon::f_update() {
	 f_setPosition();
	 //f_setRotaion();

	 // カメラの位置と回転値をセット、カメラの位置は原点
	// SetCameraPositionAndAngle(position, rotation.x, rotation.y, rotation.z );
	 SetCameraPositionAndTarget_UpVecY(position, Playerposition);
 }

 void c_CameraCon::f_setPosition() {
	 //float CamX = 0.0f;            //カメラのX軸
	 //float CamY = 0.0f;            //カメラのY軸
	 //float CamZ = 0.0f;            //カメラのZ軸

	 //if (CheckHitKey(KEY_INPUT_W) == 1) {
		// CamZ += 10.0f;
	 //}
	 //if (CheckHitKey(KEY_INPUT_A) == 1) {
		// CamX -= 10.0f;
	 //}
	 //if (CheckHitKey(KEY_INPUT_S) == 1) {
		// CamZ -= 10.0f;
	 //}
	 //if (CheckHitKey(KEY_INPUT_D) == 1) {
		// CamX += 10.0f;
	 //}

	 //ズームインアウト
	 //if (CheckHitKey(KEY_INPUT_E) == 1) {
		// CamY += 10.0f;
	 //}
	 //if (CheckHitKey(KEY_INPUT_Q) == 1) {
		// CamY -= 10.0f;
	 //}

	 float HcosTriRot = cos(HRotate);		//カメラのH角度のコサイン
	 float HsinTriRot = sin(HRotate);		//カメラのH角度のコサイン


	 //float MoveZ = (CamZ * HcosTriRot) + (CamX * HsinTriRot) * (-1);	//左右の移動量を反転
	 //float MoveX = (CamX * HcosTriRot) + (CamZ * HsinTriRot);

	 //カメラの座標　=　(プレイヤーの座標+プレイヤーとの固定距離)
	 //position = VGet(Playerposition.x + Cameradistance.x, Playerposition.y + Cameradistance.y, Playerposition.z + Cameradistance.z);
	 //position = VGet(Nowx * PI / 180 + Cameradistance.x, Playerposition.y + Cameradistance.y, Nowx * PI / 180 + Cameradistance.z);


	 int Nowx, Nowy;		//マウスの座標変数
	 GetMousePoint(&Nowx, &Nowy);	//マウスの座標取得
	 //画面中心が原点に来るように調整
	 Nowx -= 640 / 2;
	 Nowy -= 480 / 2;
	 //カメラのY軸の上限設定 90度まで
	 if (Nowy > 90) Nowy = 90;
	 //カメラのY軸の下限設定 0度まで
	 if (Nowy < 0) Nowy = 0;

	 float Camangle_H = Nowx * PI / 90;	//カメラの水平角度
	 float Camangle_V = Nowy * PI / 90;	//カメラの垂直角度

	 DrawFormatString(0,0,0xffffff,"Nowy %d",Nowy);
	 DrawFormatString(0, 20, 0xffffff, "Nowx %d", Nowx);

	 position.x = Cameradistance.x * cos(Camangle_H) + Cameradistance.z * sin(Camangle_H);
	 position.z = -Cameradistance.x * sin(Camangle_H) + Cameradistance.z * cos(Camangle_H);
	 position.y = Cameradistance.x * sin(Camangle_V) + Cameradistance.z * cos(Camangle_V);
	 position.x += Playerposition.x;
	 position.z += Playerposition.z;
	 position.y += Playerposition.y;

	 DrawFormatString(0, 40, 0xffffff, "position.y %f", position.y);
	 DrawFormatString(0, 60, 0xffffff, "Playerposition.y %f", Playerposition.y);

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

	 //atan2(Nowx * PI/180, Nowy);

	 //カメラの座標　=　(プレイヤーの座標+プレイヤーとの固定距離)
	 //position = VGet(Nowx * PI / 180 + Cameradistance.x, Playerposition.y + Cameradistance.y, Playerposition.z + Cameradistance.z);

	 SetMousePoint(640 / 2, 480 / 2);
	 Oldx = 640 / 2;
	 Oldy = 480 / 2;
 }
