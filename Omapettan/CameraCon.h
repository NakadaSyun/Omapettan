//Cameracon.h


#pragma once
#include "Dxlib.h"

class c_CameraCon {
public:
	c_CameraCon();
	void f_update();

	void f_setPosition();
	void f_setRotaion();

	float Camangle_H = 0.0f;	//�J�����̐����p�x
	float Camangle_V = 0.0f;	//�J�����̐����p�x

	VECTOR position;


private:
	//VECTOR position;
	VECTOR rotation;

	const VECTOR Cameradistance = VGet(0.0f, 800.0f, -100.0f);	//�J�����ƃv���C���[�̋���

	float HRotate, VRotate, TRotate;			//�����F�����F�Ђ˂�
};
