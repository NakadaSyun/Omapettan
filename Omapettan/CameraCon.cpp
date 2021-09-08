//Camera.cpp

#include "CameraCon.h"
#include <math.h>
#include "GameManager.h"

#define PI 3.141592653589793


c_CameraCon::c_CameraCon() {
	VRotate = 0.0f;         //������]
	HRotate = 0.0f;        //������]
	TRotate = 0.0f;         //�P���]

	position = VAdd(Playerposition, Cameradistance);	//�J�����̍��W

	rotation = VGet(VRotate, HRotate, TRotate);
}

void c_CameraCon::f_update() {
	f_setPosition();
	//f_setRotaion();

	// �J�����̈ʒu�Ɖ�]�l���Z�b�g�A�J�����̈ʒu�͌��_
	SetCameraPositionAndTarget_UpVecY(position, Playerposition);
}

void c_CameraCon::f_setPosition() {

	position = VAdd(Playerposition, Cameradistance);

	//DrawFormatString(0, 40, 0xffffff, "Playerposition.x %f", Playerposition.x);
	//DrawFormatString(0, 60, 0xffffff, "Playerposition.y %f", Playerposition.y);
	//DrawFormatString(0, 80, 0xffffff, "Playerposition.z %f", Playerposition.z);

}

void c_CameraCon::f_setRotaion() {

}
