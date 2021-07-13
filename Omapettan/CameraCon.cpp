#include "CameraCon.h"

#define PI 3.141592653589793

 c_CameraCon::c_CameraCon() {
	 VRotate = 0.0f;         //������]
	 HRotate = 0.0f;        //������]
	 TRotate = 0.0f;         //�P���]

	 position = VGet(320.0f, 100.0f, -200.0f);

	 rotation = VGet(VRotate, HRotate, TRotate);
}

 void c_CameraCon::f_update() {
	 f_setPosition();
	 f_setRotaion();

	 // �J�����̈ʒu�Ɖ�]�l���Z�b�g�A�J�����̈ʒu�͌��_
	 SetCameraPositionAndAngle(position, rotation.x, rotation.y, rotation.z );
 }

 void c_CameraCon::f_setPosition() {
	 float CamX = 0.0f;            //�J������X��
	 float CamY = 0.0f;            //�J������Y��
	 float CamZ = 0.0f;            //�J������Z��

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

	 //printf("HRotate X = %f		X = %f\n", HRotate, HRotate * 180.0 / PI);
	 position = VGet(position.x + CamX, position.y + CamY, position.z + CamZ);
 }

 void c_CameraCon::f_setRotaion() {
	 int Nowx, Nowy;
	 GetMousePoint(&Nowx, &Nowy);

	 static int Oldx = Nowx, Oldy = Nowy;
	 printf("Nowx = %d		Oldx = %d\n", Nowx, Nowy);

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

	 SetMousePoint(640 / 2, 480 / 2);
	 Oldx = 640 / 2;
	 Oldy = 480 / 2;
 }