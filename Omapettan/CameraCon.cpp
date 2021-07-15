#include "CameraCon.h"
#include <math.h>
#include "GameManeger.h"

#define PI 3.141592653589793


 c_CameraCon::c_CameraCon() {
	 VRotate = PI/4;         //������]
	 HRotate = 0.0f;        //������]
	 TRotate = 0.0f;         //�P���]

	 position = Cameradistance;

	 rotation = VGet(VRotate, HRotate, TRotate);
}

 void c_CameraCon::f_update() {
	 f_setPosition();
	 //f_setRotaion();

	 // �J�����̈ʒu�Ɖ�]�l���Z�b�g�A�J�����̈ʒu�͌��_
	 SetCameraPositionAndAngle(position, rotation.x, rotation.y, rotation.z );
 }

 void c_CameraCon::f_setPosition() {
	 //float CamX = 0.0f;            //�J������X��
	 //float CamY = 0.0f;            //�J������Y��
	 //float CamZ = 0.0f;            //�J������Z��

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

	 //�Y�[���C���A�E�g
	 //if (CheckHitKey(KEY_INPUT_E) == 1) {
		// CamY += 10.0f;
	 //}
	 //if (CheckHitKey(KEY_INPUT_Q) == 1) {
		// CamY -= 10.0f;
	 //}

	 float HcosTriRot = cos(HRotate);		//�J������H�p�x�̃R�T�C��
	 float HsinTriRot = sin(HRotate);		//�J������H�p�x�̃R�T�C��


	 //float MoveZ = (CamZ * HcosTriRot) + (CamX * HsinTriRot) * (-1);	//���E�̈ړ��ʂ𔽓]
	 //float MoveX = (CamX * HcosTriRot) + (CamZ * HsinTriRot);

	 Playerposition;

	 position = VGet(Playerposition.x + Cameradistance.x, Playerposition.y + Cameradistance.y, Playerposition.z + Cameradistance.z);
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

	 SetMousePoint(640 / 2, 480 / 2);
	 Oldx = 640 / 2;
	 Oldy = 480 / 2;
 }
