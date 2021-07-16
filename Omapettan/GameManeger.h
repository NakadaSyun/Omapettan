#pragma once

#include "DxLib.h"

#include "DrawCube.h"
#include "Player.h"
#include "CameraCon.h"
#include "DispUI.h"

extern VECTOR Playerposition;

class c_GameManeger
{
public:
	void f_init();				//�Q�[���̏�����
	void f_RoadModel();			//���f���̓Ǎ���
	void f_update();			//�t���[�����Ƃ̏���
	void f_output();			//�t���[�����Ƃ̕`��


	c_DrawCube* c_Dc;
	c_Player* c_player;
	c_CameraCon* c_camera;
	c_DispUI* c_dispUI;

private:
	// �摜�t�@�C���̓ǂ݂���

	int model_impostor;
	int model_Plane;
	int model_Sphere;

};