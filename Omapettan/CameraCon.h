#pragma once
#include "Dxlib.h"

class c_CameraCon {
public:
	c_CameraCon();
	void f_update();

	void f_setPosition();
	void f_setRotaion();


private:
	VECTOR position;
	VECTOR rotation;

	const VECTOR Cameradistance = VGet(0.0f,0.0f,-250);	//�J�����ƃv���C���[�̋���

	float HRotate, VRotate,TRotate;			//�����F�����F�Ђ˂�
};
