#include "CameraCon.h"
#include <math.h>
#include "GameManeger.h"

#define PI 3.141592653589793


 c_CameraCon::c_CameraCon() {
	 VRotate = PI/4;         //������]
	 HRotate = 0.0f;        //������]
	 TRotate = 0.0f;         //�P���]

	 position = Cameradistance;	//�J�����̍��W

	 rotation = VGet(VRotate, HRotate, TRotate);
}

 void c_CameraCon::f_update() {
	 f_setPosition();
	 //f_setRotaion();

	 // �J�����̈ʒu�Ɖ�]�l���Z�b�g�A�J�����̈ʒu�͌��_
	// SetCameraPositionAndAngle(position, rotation.x, rotation.y, rotation.z );
	 SetCameraPositionAndTarget_UpVecY(position, Playerposition);
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

	 //�J�����̍��W�@=�@(�v���C���[�̍��W+�v���C���[�Ƃ̌Œ苗��)
	 //position = VGet(Playerposition.x + Cameradistance.x, Playerposition.y + Cameradistance.y, Playerposition.z + Cameradistance.z);
	 //position = VGet(Nowx * PI / 180 + Cameradistance.x, Playerposition.y + Cameradistance.y, Nowx * PI / 180 + Cameradistance.z);


	 int Nowx, Nowy;		//�}�E�X�̍��W�ϐ�
	 GetMousePoint(&Nowx, &Nowy);	//�}�E�X�̍��W�擾
	 //��ʒ��S�����_�ɗ���悤�ɒ���
	 Nowx -= 640 / 2;
	 Nowy -= 480 / 2;
	 //�J������Y���̏���ݒ� 90�x�܂�
	 if (Nowy > 90) Nowy = 90;
	 //�J������Y���̉����ݒ� 0�x�܂�
	 if (Nowy < 0) Nowy = 0;

	 Camangle_H = Nowx * PI / 90;	//�J�����̐����p�x
	 Camangle_V = Nowy * PI / 90;	//�J�����̐����p�x

	 DrawFormatString(0,0,0xffffff,"Nowy %d",Nowy);
	 DrawFormatString(0, 20, 0xffffff, "Nowx %d", Nowx);

	 position.x = Cameradistance.x * cos(Camangle_H) + Cameradistance.z * sin(Camangle_H);
	 position.z = -Cameradistance.x * sin(Camangle_H) + Cameradistance.z * cos(Camangle_H);
	 position.y = Cameradistance.x * sin(Camangle_V) + Cameradistance.z * cos(Camangle_V);
	 position.x += Playerposition.x;
	 position.z += Playerposition.z;
	 position.y -= Playerposition.y - 500.0f;

	 DrawFormatString(0, 40, 0xffffff, "position.x %f", position.x);
	 DrawFormatString(0, 60, 0xffffff, "Playerposition.y %f", Playerposition.y);
	 DrawFormatString(0, 80, 0xffffff, "Camangle_V %f", Camangle_V);

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

	 //�J�����̍��W�@=�@(�v���C���[�̍��W+�v���C���[�Ƃ̌Œ苗��)
	 //position = VGet(Nowx * PI / 180 + Cameradistance.x, Playerposition.y + Cameradistance.y, Playerposition.z + Cameradistance.z);

	 SetMousePoint(640 / 2, 480 / 2);
	 Oldx = 640 / 2;
	 Oldy = 480 / 2;
 }
