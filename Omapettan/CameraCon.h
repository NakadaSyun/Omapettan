//Cameracon.h


#pragma once
#include "Dxlib.h"

class c_CameraCon {
public:
	c_CameraCon();
	void f_update();

	void f_setPosition();
	void f_setRotaion();

	float Camangle_H;	//�J�����̐����p�x
	float Camangle_V;	//�J�����̐����p�x

	////Y���̉�]
	float HcosTriRot;		//�J������H�p�x�̃R�T�C��
	float HsinTriRot;		//�J������H�p�x�̃R�T�C��

	VECTOR position;


private:
	//VECTOR position;
	VECTOR rotation;

	const VECTOR Cameradistance = VGet(0.0f, 0.0f, -500);	//�J�����ƃv���C���[�̋���

	float HRotate, VRotate, TRotate;			//�����F�����F�Ђ˂�
};
