//Camera.cpp

#include "CameraCon.h"
#include <math.h>
#include "GameManager.h"

#define PI 3.141592653589793
static const float ROTATE_SPEED = PI / 75;//��]�X�s�[�h
int startangleflg;

c_CameraCon::c_CameraCon() {
	VRotate = 0.0f;         //������]
	HRotate = 0.0f;        //������]
	TRotate = 0.0f;        //�P���]

	position = VAdd(Playerposition, Cameradistance);	//�J�����̍��W

	rotation = VGet(VRotate, HRotate, TRotate);

	c_mainui = new c_MainUI(0,0,0);

}
void c_CameraCon::f_rotate(float* x, float* y, const float ang, const float mx, const float my) {
	const float ox = *x - mx, oy = *y - my;
	*x = ox * cos(ang) + oy * sin(ang);
	*y = -ox * sin(ang) + oy * cos(ang);
	*x += mx;
	*y += my;
}

int c_MainUI::f_GetStartFlg() {
	startangleflg = startFlg;
	return  startFlg;
}

void c_CameraCon::f_update() {
	//f_setPosition();
	//f_setRotaion();

	static VECTOR initialposition = position;

	// �J�����̈ʒu�Ɖ�]�l���Z�b�g�A�J�����̈ʒu�͌��_
	//SetCameraPositionAndTarget_UpVecY(position, Playerposition);

	


	if (startangleflg == 0) {//�Q�[���X�^�[�g���ɃX�e�[�W��������悤�ȃJ�����ړ��t���O��true�̎�
		f_rotate(&position.x, &position.y, +ROTATE_SPEED, 0, 0);//��]
		//�������̎��_����������̃^�[�Q�b�g������p�x�ɃJ������ݒu
		SetCameraPositionAndTarget_UpVecY(VGet(position.x, position.y, 4000), VGet(0, 0, 6000));
	}
	else {
		f_setPosition();
		// �J�����̈ʒu�Ɖ�]�l���Z�b�g�A�J�����̈ʒu�͌��_
		SetCameraPositionAndTarget_UpVecY(position, Playerposition);
	}




	//DrawFormatString(0,70,0xffffff,"�J����X���W %f", position.x);
	//DrawFormatString(0, 90, 0xffffff, "�J����Y���W %f", position.y);

}


void c_CameraCon::f_setPosition() {

	position = VAdd(Playerposition, Cameradistance);

	//DrawFormatString(0, 40, 0xffffff, "Playerposition.x %f", Playerposition.x);
	//DrawFormatString(0, 60, 0xffffff, "Playerposition.y %f", Playerposition.y);
	//DrawFormatString(0, 80, 0xffffff, "Playerposition.z %f", Playerposition.z);

}

void c_CameraCon::f_setRotaion() {

}
