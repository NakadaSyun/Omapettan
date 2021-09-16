#pragma once

#include "DxLib.h"

#include "DrawCube.h"
#include "Player.h"
#include "CameraCon.h"
#include "DispUI.h"
#include "Stage.h"
#include "Collision.h"
#include "HairVertexBuffer.h"
#include "DrawAcne.h"
#include "Controller.h"
#include "MainUI.h"
#include "LoadSound.h"
#include "HitCheck.h"

#include <iostream>


extern VECTOR Playerposition;

class c_GameManager
{
public:
	void f_init();				//�Q�[���̏�����
	void f_RoadModel();			//���f���̓Ǎ���
	void f_RoadImage();         //�摜�̓ǂݍ���
	void f_update();			//�t���[�����Ƃ̏���
	void f_output();			//�t���[�����Ƃ̕`��

	void f_SkyBoxDraw();			//�w�i�̕`��

	bool f_HitCheck(c_Collision col1,c_Collision col2);			//�Փ˔���

	c_DrawCube* c_Dc;
	c_Player* c_player;
	c_CameraCon* c_camera;
	c_DispUI* c_dispUI;
	c_Stage* c_stage;
	c_Hair* c_hair;
	c_Acne* c_acne;
	c_GamePad* c_pad;
	c_MainUI* c_mainUI;
	c_HitCheck* c_hitCheck;

private:
	
	// ���f��
	int model_impostor;
	int model_Plane;
	int model_Sphere;
	int model_Cylinder;
	int model_Arm;
	int model_SkyBox;
	int model_Acne;
	int model_Bandage;

	// �摜
	int image_Cylinder;
	int image_Acne;
	int image_Bansoko;
	int image_mainUI;
	int image_volumeIcon;
};